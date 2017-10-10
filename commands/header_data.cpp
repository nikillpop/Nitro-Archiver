#include <fstream>
#include <iomanip>
#include <iostream>

void readHeaderData(std::fstream &narc)
{
	char readedData[4]{};

	std::cout << "\n_______Narc Header_______" << std::endl;


	narc.seekg(0x0, std::ios::beg);
	narc.read(readedData, 0x4);
	std::cout << "Chunk Name:\t\"";
	for (auto &letter : readedData)
	{
		std::cout << letter;
	}
	std::cout << "\"" << std::endl;


	narc.seekg(0x4, std::ios::beg);
	narc.read(readedData, 0x2);
	std::cout << "Byte Order:\t0x" << std::hex
	          << static_cast<unsigned>(readedData[0])
	          << static_cast<unsigned>(readedData[1]) << std::endl;
	//No funciona como debe, imprime 0xFFFFFFXXFFFFFFYY en vez de 0xXXYY

	std::cout << "\n__File Alocation Table___" << std::endl;


	narc.seekg(0x18, std::ios::beg);
	narc.read(readedData, 0x2);
	std::cout << "Files:\t\t" << std::dec << readedData[0] + readedData[1]
	          << std::endl;
}