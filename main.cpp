#include <fstream>
#include <iomanip>
#include <iostream>

int main()
{
	std::cout << "Enter file name:";
	std::string fileName;
	std::cin >> fileName;

	std::fstream narc(fileName, std::ios::binary | std::ios::in);

	if (narc.fail())
	{
		std::cerr << "Error opening \"" << fileName << "\"" << std::endl;
		return 1;
	}

	std::cin.clear();
	std::cin.ignore(32767, '\n');
	std::cin.get();
}