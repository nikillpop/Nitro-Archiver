#include <fstream>
#include <iomanip>
#include <iostream>

void readHeaderData(std::fstream &narc)
{
	std::cout << std::endl;

	char readedData[4]{};


	narc.seekg(0x0, std::ios::beg);
	narc.read(readedData, 0x4);

	std::cout << "Chunk Name:\t\"";
	for (auto &letter : readedData)
	{
		std::cout << letter;
	}
	std::cout << "\"" << std::endl;


	narc.seekg(0x18, std::ios::beg);
	narc.read(readedData, 0x2);

	std::cout << "Files:\t\t" << static_cast<int>(readedData[0]) + static_cast<int>(readedData[1]) << std::endl;
}