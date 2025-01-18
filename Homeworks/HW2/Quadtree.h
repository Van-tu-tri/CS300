#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

// Our city dimensions are here.
struct CityData
{
	int x;
	int y;
	std::string cityname;
	// Constructor.
	CityData(int x, int y, std::string cityname)
	{
		this->x = x;
		this->y = y;
		this->cityname = cityname;
	}
	// Default constructor.
	CityData()
	{
		this->x = 0;
		this->y = 0;
		this->cityname = "null";
	}
};

// Actual quadTree Node.
struct treeNode
{
	// Our city and directions.
	CityData city;
	treeNode* NW;
	treeNode* NE;
	treeNode* SW;
	treeNode* SE;
	// Constructor
	treeNode(int x, int y, std::string cityname)
	{
		this->city.x = x;
		this->city.y = y;
		this->city.cityname = cityname;
		NW = nullptr;
		NE = nullptr;
		SW = nullptr;
		SE = nullptr;
	}

	// Destructor for dealing with dynamic memory. This is recursive.
	// No need to check for null value because C++ is safe deleting null.
	~treeNode()
	{
		//std::cout << "DEBUG: I AM DELETING THIS: " << this->city.cityname << '\n';
		delete this->SE;
		delete this->SW;
		delete this->NE;
		delete this->NW;
	}
};

class quadTree
{
public:
	quadTree();
	~quadTree();

	// Create the quadTree with the input file.
	void createTree(std::ifstream& ifile, const std::string& ifile_name, int& right, int& top);

	// Actual printing implementation. Since it is recursive it needs a inside caller.
	void printTree_actual(treeNode* root);
	
	// To access actual print implementation.
	void printTree();

	// Actual recursive find implementation. Since it is recursive it needs a inside caller.
	void recursive_find_actual(treeNode* root, const int& x_0, const int& y_0, const int& r, std::vector<std::string>& collision, std::vector<std::string>& traveled);

	// To acess actual recursive find implementation
	void recursive_find(const int& x_0, const int& y_0, const int& r, std::vector<std::string>& collision, std::vector<std::string>& traveled);

	// It takes an input query file. And with the above functions, it prints the collision vector and traveled vector in an ordered way.
	void print_console(std::ifstream& ifile, std::string ifile_name);
	

private:
	treeNode* root;
};