#include <fstream>
#include <iomanip>
#include <iostream>

int main()
{
	std::cout << "Narc-Archiver, Commit #7, By Jes" << char(163) << "s (Jes)\n"
	          << std::endl;

	std::cout << "Enter file name: ";
	std::string fileName;
	std::cin >> fileName;

	std::fstream narc(fileName, std::ios::binary | std::ios::in);

	if (narc.fail())
	{
		std::cerr << "Error opening \"" << fileName << "\"" << std::endl;
		return 1;
	}
	else
	{
		std::cout << "File opened correctly\n" << std::endl;
	}

	std::string cmds;

	std::cout << "Enter commands: ";
	std::cin.ignore();
	std::getline(std::cin, cmds);

	std::cin.ignore(32767, '\n');
	std::cin.get();
}
