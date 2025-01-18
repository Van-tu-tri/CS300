#include "Quadtree.h"



int main()
{
	std::vector<std::string> collision;
	std::vector<std::string> traveled;

	std::ifstream ifile;
	std::ofstream ofile;

	// File names.
	std::string ifile_name_cities = "cities.txt";
	std::string ifile_name_queries = "queries.txt";
	std::string ofile_name = "output.txt";

	// Dimensions.
	int right, top;

	// Empty quadTree object.
	quadTree cities;

	
	cities.createTree(ifile, ifile_name_cities, right, top);
	cities.printTree();
	std::cout << '\n';
	cities.print_console(ifile, ifile_name_queries);

	return 0;
}