#include <string>
#include <iostream>
#include <vector>
#include "stack.h"
#include <fstream>
#include <cstdio>



struct matrix
{
public:
	int** board;
	int row;	// The location of last peace that was put.
	int column;
	int size;

	// Default constructor
	matrix()
	{
		this->board = nullptr;
		this->row = -1;
		this->column = -1;
		this->size = -1;

	}
	matrix(int n)
	{
		this->row = -1;
		this->column = -1;
		this->board = new int* [n];
		this->size = n;
		for (unsigned int i = 0; i < n; i++)
		{
			this->board[i] = new int[n];
			for (unsigned int k = 0; k < n; k++)
			{
				this->board[i][k] = 0;
			}
		}
	}

	matrix(const matrix& other) // Copy constructor.
	{
		this->row = other.row;
		this->column = other.column;
		this->size = other.size;
		this->board = new int* [this->size];
		for (int i = 0; i < this->size; i++)
		{
			board[i] = new int[this->size];
			for (int k = 0; k < this->size; k++)
			{
				board[i][k] = other.board[i][k];
			}
		}

	}

	// For deep copy because we use dynamic memory.
	matrix& operator= (const matrix& other)
	{
		if (this == &other) return *this;

		for (int i = 0; i < this->size; i++)
		{
			delete[] this->board[i];
		}
		delete[] this->board;

		this->size = other.size;
		this->row = other.row;
		this->column = other.column;

		this->board = new int* [this->size];
		for (int i = 0; i < this->size; i++)
		{
			board[i] = new int[this->size];
			for (int k = 0; k < this->size; k++)
			{
				board[i][k] = other.board[i][k];
			}
		}
		return *this;
	}


	~matrix()
	{
		for (unsigned int i = 0; i < this->size; i++)
		{
			delete[] this->board[i];
		}
		delete[] this->board;
	}


	// I think i used this for debug reasons, i do not remember.
	void print()
	{
		std::cout << "This is the row: " << this->row << std::endl;
		std::cout << "This is the column: " << this->column << std::endl;
		std::cout << "This is the size: " << this->size << std::endl;
		std::cout << "This is the board: " << std::endl;
		if (this->board == nullptr);
		else
		{
			for (int i = 0; i < this->size; i++)
			{
				for (int k = 0; k < this->size; k++)
				{
					std::cout << this->board[i][k];
				}
				std::cout << std::endl;
			}
		}
	}
private:
};


// Update of safe matrix. Returns true if the piece can be put.
bool putable(int** board, int board_size, const int& row, const int& column)
{
	int current_row = row;
	int current_column = column;
	if (board[row][column] == 0)
	{
		for (int i = 0; i < board_size; i++)
		{
			board[i][column]++;
			board[row][i]++;
			if (((current_row + i) < board_size) and ((current_column + i) < board_size))
			{
				board[current_row + i][current_column + i]++;
			}

			if (((current_row - i) >= 0) and ((current_column - i) >= 0))
			{
				board[current_row - i][current_column - i]++;
			}
			if (((current_row + i) < board_size) and ((current_column - i) >= 0))
			{
				board[current_row + i][current_column - i]++;
			}
			if (((current_row - i) >= 0) and ((current_column + i) < board_size))
			{
				board[current_row - i][current_column + i]++;
			}
		}
		board[row][column] -= 5;
		return true;
	}
	else return false;
}

// To write all of the solutions.
void show_vector_solutions_2(const std::vector<std::vector<int>>& Solutions, std::ofstream& outfile, const std::string& file_name)
{
	int total_iteration = Solutions.size();
	outfile.open(file_name, std::ios::app);
	for (int i = 0; i < total_iteration; i++)
	{
		int inside_iteration = Solutions[i].size();
		outfile << "Solution " << i + 1 << ": [";
		for (int k = 0; k < inside_iteration - 1; k++)
		{
			outfile << Solutions[i][k] << ", ";
		}
		outfile << Solutions[i][inside_iteration - 1] << "]" << '\n';
	}
	outfile.close();
}


int main()
{
	// Input of the board and input check. Return if board size is <= 0;
	int board_size;
	std::cout << "Enter the value of N for the N-Queens problem: ";
	std::cin >> board_size;
	if (board_size <= 0)
	{
		std::cout << "Invalid input. Plase enter a positive integer";
		return 0;
	}

	// To record pieces for solution.
	std::vector<int> vector_solution;


	// To output
	std::ofstream outfile;
	std::string file_name = std::to_string(board_size) + "queens_solutions.txt";
	std::cout << "Solutions have been saved to '" << file_name << "'";
	outfile.open(file_name);
	outfile << "Total solutions for N=" << board_size << ": ";
	outfile.close();

	// To understand wheter the game is finished or we are dealing with poped situation
	// If we are in the poped situation we should remember the last column, so we can from there.
	bool finished = false;
	bool poped = false;

	// Variables for program.
	int last_row;			// Row location of piece that was put last.
	int last_column;		// Column location of piece that was put last.
	int** last_board;		// Last safe matrix that is constructed when the last piece was put.

	int current_row = 0;	// The row that we are doing operations now.
	int current_column = 0;	// The column that we are doing operations now.

	// Stack created. Matrix_struct pushed into the stack.
	stack<matrix> stack_matrix;
	matrix initial_matrix = matrix(board_size);
	stack_matrix.push(initial_matrix);

	// Solution Vector
	std::vector<std::vector<int>> vector_solutions2;


	// The main loop must continue until all solutions found.
	while (!finished)
	{
		matrix temp_matrix = stack_matrix.get_data();
		// Save all data.
		last_row = temp_matrix.row;
		last_column = temp_matrix.column;
		last_board = temp_matrix.board;
		
		// DEBUG std::cout << "Matrix is collected" << '\n';
		// DEBUG std::cout << last_row << " and " << last_column << '\n';
		// DEBUG std::cout << "Stack size in MAIN is: " << stack_matrix.get_size() << '\n';
		

		if (last_row == board_size - 1)
		{
			
			// DEBUG std::cout << "We found one solution" << '\n';
			// This means solution
			// DEBUG std::cout << "We pop the last because of the solution and pop the vector." << '\n';
			
			stack_matrix.pop();

			// We poped so we should record the last column position
			poped = true;
			current_column = vector_solution[board_size - 1];

			// Push back the solution and delete the last piece that was written on solutoion.
			vector_solutions2.push_back(vector_solution);
			vector_solution.pop_back();

			
			// DEBUG std::cout << "We found one solution //This is end of that" << '\n';
		}
		else
		{
			current_row = last_row + 1;
			if (poped)
			{
				// If it is poped.
				if (current_row == 0)
				{
					// If we are in row 0.
					if (current_column == board_size - 1) finished = true;
					else current_column++;
				}
				else
				{
					current_column++;
				}
			}
			// If it is not poped than we are in new row.
			else
			{
				current_column = 0;
			}
			
			// DEBUG std::cout << "Current column is: " << current_column << '\n';
			// DEBUG std::cout << "Current row is: " << current_row << '\n';
			

			bool go = true;
			while (go and !finished)
				if (current_column == board_size)
				{
					// DEBUG std::cout << "Matrix is poped" << '\n';
					current_column = last_column;
					poped = true;
					go = false;
					stack_matrix.pop();
					vector_solution.pop_back();
					
				}
				else
				{
					if (putable(last_board, board_size, current_row, current_column))
					{
						// DEBUG std::cout << "We put a value at " << current_row << " " << current_column << '\n';
						poped = false;
						go = false;
						// Update the row and column of the matrix_struct.
						// The board is already updated in the putable function
						// Push the matrix_struct into stack.
						temp_matrix.row = current_row;
						temp_matrix.column = current_column;
						stack_matrix.push(temp_matrix);
						vector_solution.push_back(current_column);
					}
					else
					{
						// DEBUG std::cout << "We cannot put a value" << '\n';
						current_column++;
					}
				}
		}
	}
	

	// Update the file with total solution number. And write the solutions.
	outfile.open(file_name, std::ios::app);
	outfile << vector_solutions2.size() << '\n' << '\n';
	outfile.close();
	show_vector_solutions_2(vector_solutions2, outfile, file_name);
	return 0;
}
