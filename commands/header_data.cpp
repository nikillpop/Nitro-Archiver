#include <fstream>
#include <iomanip>
#include <iostream>

void readHeaderData(std::fstream &narc)
{
	narc.seekg(0x18, std::ios::beg);

	char read[2];

	narc.read(read, 0x2);

	std::cout << "Files:\t" << static_cast<int>(read[0]) + static_cast<int>(read[1]) << std::endl;
}