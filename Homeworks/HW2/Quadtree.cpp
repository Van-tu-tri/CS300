#include "Quadtree.h"
#include <sstream>


// Default constructor
quadTree::quadTree()
{
	this->root = nullptr;
}


// Destructor
quadTree::~quadTree()
{
	delete this->root;
}


// Create the quadTree with the file input.
// I do not have any idea why we have dimensions since homework document do not spesify invalid input checking
void quadTree::createTree(std::ifstream& ifile, const std::string& ifile_name, int& right, int& top)
{
	int x;
	int y;
	std::string cityname;

	ifile.open(ifile_name);

	// Take the dimension input out of way
	ifile >> right >> top;

	//Prepare the root
	ifile >> cityname >> x >> y;
	this->root = new treeNode(x, y, cityname);

	while (ifile >> cityname >> x >> y)
	{
		// Pointer for root;
		treeNode* current = root;

		while (current != nullptr)
		{
			if (x < current->city.x and y >= current->city.y)			//NW
			{
				if (current->NW == nullptr)
				{
					current->NW = new treeNode(x, y, cityname);
					current = nullptr;
				}
				else
				{
					current = current->NW;
				}
			}
			else if (x >= current->city.x and y >= current->city.y)		//NE
			{
				if (current->NE == nullptr)
				{
					current->NE = new treeNode(x, y, cityname);
					current = nullptr;
				}
				else
				{
					current = current->NE;
				}
			}
			else if (x < current->city.x and y < current->city.y)		//SW
			{
				if (current->SW == nullptr)
				{
					current->SW = new treeNode(x, y, cityname);
					current = nullptr;
				}
				else
				{
					current = current->SW;
				}
			}
			else // x >= current->city.x and y < current->city.y		//SE
			{
				if (current->SE == nullptr)
				{
					current->SE = new treeNode(x, y, cityname);
					current = nullptr;
				}
				else
				{
					current = current->SE;
				}
			}
		}
	}
	ifile.close();
	return;
}


// It prints the tree with an ugly way.
void quadTree::printTree()
{
	this->printTree_actual(this->root);
}

// Since this is a recursive function, i can not directly call it. So printTree() function call this.
void quadTree::printTree_actual(treeNode* root)
{
	if (root != nullptr)
	{
		std::cout << root->city.cityname << std::endl;
		printTree_actual(root->SE);
		printTree_actual(root->SW);
		printTree_actual(root->NE);
		printTree_actual(root->NW);
	}
	else return;
}


// Same logic with the printing. 
// This function takes a query and two vectors. Than call recursive_find_actual
void quadTree::recursive_find(const int& x_0, const int& y_0, const int& r, std::vector<std::string>& collision, std::vector<std::string>& traveled)
{
	this->recursive_find_actual(this->root, x_0,  y_0, r, collision, traveled);
}


void quadTree::recursive_find_actual(treeNode* root, const int& x_0, const int& y_0, const int& r, std::vector<std::string>& collision, std::vector<std::string>& traveled)
{
	// If current node is null, we are at the end. Return
	if (root == nullptr) return;
	else
	{
		// Take the current root dimensions.
		int x = root->city.x;
		int y = root->city.y;
		std::string cityname = root->city.cityname;
		treeNode* current = nullptr;

		// NW NE SW SE
		int directions[4] = { 0, 0, 0, 0 };

		if (x > (x_0 + r) and y <= (y_0 - r)) directions[0] = 1;	//NW
		if (x <= (x_0 - r) and y <= (y_0 - r)) directions[1] = 1;	//NE
		if (x > (x_0 + r) and y > (y_0 + r)) directions[2] = 1;		//SW
		if (x <= (x_0 - r) and y > (y_0 + r)) directions[3] = 1;	//SE

		// Below we compare the query with our current Node dimensions. 
		// After spesifying where is our Node comparing to query, we decide which directions should be visited.

		if (x <= (x_0 + r) and x > (x_0 - r) and y <= (y_0 - r))	//NW, NE
		{
			directions[0] = 1;
			directions[1] = 1;
		}
		if ((x > (x_0 + r) and y > (y_0 - r) and y <= (y_0 + r)) or (x == (x_0 + r) and y == y_0))	//NW, SW
		{
			directions[0] = 1;
			directions[2] = 1;
		}
		if (x <= (x_0 - r) and y <= (y_0 + r) and y > (y_0 - r))	//NE, SE
		{
			directions[1] = 1;
			directions[3] = 1;
		}
		if ((x > (x_0 - r) and x <= (x_0 + r) and y > (y_0 + r)) or (x == x_0 and y == (y_0 + r)))	//SW, SE
		{
			directions[2] = 1;
			directions[3] = 1;
		}

		if (x > x_0 and x <= (x_0 + r) and y < y_0 and y >(y_0 - r) and ((x - x_0) * (x - x_0) + (y - y_0) * (y - y_0) >= r * r))	//NW, NE, SW
		{
			directions[0] = 1;
			directions[1] = 1;
			directions[2] = 1;
		}

		if (x > x_0 and x <= (x_0 + r) and y > y_0 and y <= (y_0 + r) and ((x - x_0) * (x - x_0) + (y - y_0) * (y - y_0) >= r * r)) //NW, SW, SE
		{
			directions[0] = 1;
			directions[2] = 1;
			directions[3] = 1;
		}
		if (x > (x_0 - r) and x < x_0 and y > y_0 and y <= (y_0 + r) and ((x - x_0) * (x - x_0) + (y - y_0) * (y - y_0) >= r * r))	//NE, SW, SE
		{
			directions[1] = 1;
			directions[2] = 1;
			directions[3] = 1;
		}
		if (x > (x_0 - r) and x < x_0 and y < y_0 and y >(y_0 - r) and ((x - x_0) * (x - x_0) + (y - y_0) * (y - y_0) >= r * r))	//NW, NE, SE
		{
			directions[0] = 1;
			directions[1] = 1;
			directions[3] = 1;
		}
		if ((x - x_0) * (x - x_0) + (y - y_0) * (y - y_0) <= r * r) //It is inside, all directions
		{
			directions[0] = 1;
			directions[1] = 1;
			directions[2] = 1;
			directions[3] = 1;
		}

		// In here, we check wheter is it inside of the query area or not.
		// If it is, we found a collision. Than we should add it to the vector.
		if ((x - x_0) * (x - x_0) + (y - y_0) * (y - y_0) <= r * r)
		{
			collision.push_back(cityname);
		}
		// In either case, we traveled this node. So we also should add this to traveled vector.
		traveled.push_back(cityname);

		// We start searching with SE, and than SW, NE, NW.
		// We change the current node to the next node according to direction we set above.
		// Than recursively continue until the node is null.
		if (directions[3])
		{
			current = root->SE;
			recursive_find_actual(current, x_0, y_0, r, collision, traveled);
		}
		if (directions[2])
		{
			current = root->SW;
			recursive_find_actual(current, x_0, y_0, r, collision, traveled);
		}
		if (directions[1])
		{
			current = root->NE;
			recursive_find_actual(current, x_0, y_0, r, collision, traveled);
		}
		if (directions[0])
		{
			current = root->NW;
			recursive_find_actual(current, x_0, y_0, r, collision, traveled);
		}
	}
}

// This use the above recursive_find_actual function in order to read the query and print it to the console.
void quadTree::print_console(std::ifstream& ifile, std::string ifile_name)
{
	// First we open the file.
	ifile.open(ifile_name);

	int x;
	int y;
	int r;
	std::string sentence;

	while (std::getline(ifile, sentence)) //Expected input = x, y, r
	{
		// Parse the sentence to get x, y, and r
		std::istringstream ss(sentence);
		std::string x_str, y_str, r_str;

		std::getline(ss, x_str, ',');
		std::getline(ss, y_str, ',');
		std::getline(ss, r_str, ',');

		// Convert to integers
		x = std::stoi(x_str);
		y = std::stoi(y_str);
		r = std::stoi(r_str);

		// Setting our two vector
		std::vector<std::string> collision;
		std::vector<std::string> traveled;

		// Calling the recursive find function. This will call actual one.
		this->recursive_find(x, y, r, collision, traveled);

		// Getting the size of vector for loop.
		int collision_size = collision.size();
		int traveled_size = traveled.size();

		if (collision.size() == 0) std::cout << "<None>" << '\n';
		else
		{
			for (int i = 0; i < collision_size; i++)
			{
				if (i < collision_size - 1) std::cout << collision[i] << ", ";
				else std::cout << collision[i] << '\n';
			}
		}
		for (int i = 0; i < traveled_size; i++)
		{
			if (i < traveled_size - 1) std::cout << traveled[i] << ", ";
			else
			{
				std::cout << traveled[i];
				if (!ifile.eof()) std::cout << '\n';	// If we are not end of the file, go to next line.
			}
		}
		if (!ifile.eof()) std::cout << '\n';	
		//Again if we are not at the end of the file, go to next line. These are for output. Nothing important.
	}
	// Do not forge to close the file.
	ifile.close();
}