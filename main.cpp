#include <utility>
#include <iostream> 
#include <string> 
#include <map>

int 		main(int argc, char const *argv[])
{
	std::map<std::pair<int,int>, std::string> myMap;
	myMap[std::make_pair(10,20)] = "#bingo#";

	if (argc > 1)
		myMap[std::make_pair(10,20)] = argv[1];
	
	std::cout << myMap[std::make_pair(10,20)] << std::endl;
	return (0);
}