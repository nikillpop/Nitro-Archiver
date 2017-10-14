/** This file is part of Nitro-Archiver.
 * 		Copyright © 2017 Jes
 *
 *  Nitro-Archiver is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Nitro-Archiver is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Nitro-Archiver.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <fstream>
#include <iomanip>
#include <iostream>


void readHeaderData(std::fstream &narc)
{
	char readedData[4]{};

	std::cout << "\n_________Narc Header__________" << std::endl;

	//Chunk Name----------------------------------------------------------------
	narc.seekg(0x0, std::ios::beg);
	narc.read(readedData, 0x4);
	std::cout << "Chunk Name:\t\t\"";
	for (auto &letter : readedData)
	{
		std::cout << letter;
	}
	std::cout << "\"" << std::endl;

	//Byte Order----------------------------------------------------------------
	std::cout << "Byte Order:\t\t0x";
	narc.seekg(0x5, std::ios::beg);
	std::cout << std::setfill('0') << std::setw(2) << std::hex << narc.peek();
	narc.seekg(0x4, std::ios::beg);
	std::cout << std::setfill('0') << std::setw(2) << std::hex << narc.peek()
	          << std::endl;

	//Version-------------------------------------------------------------------
	std::cout << "Version:\t\t0x";
	narc.seekg(0x7, std::ios::beg);
	std::cout << std::setfill('0') << std::setw(2) << std::hex << narc.peek();
	narc.seekg(0x6, std::ios::beg);
	std::cout << std::setfill('0') << std::setw(2) << std::hex << narc.peek()
	          << std::endl;

	//File Size-----------------------------------------------------------------
	std::cout << "File Size:\t\t0x";
	uint8_t buffer[4]{};
	narc.seekg(0xb, std::ios::beg);
	buffer[3] = narc.peek();
	std::cout << std::hex << narc.peek();
	narc.seekg(0xa, std::ios::beg);
	buffer[2] = narc.peek();
	std::cout << std::hex << narc.peek();
	narc.seekg(0x9, std::ios::beg);
	buffer[1] = narc.peek();
	std::cout << std::hex << narc.peek();
	narc.seekg(0x8, std::ios::beg);
	buffer[0] = narc.peek();
	std::cout << std::hex << narc.peek();

	uint32_t concatenatedTemp = buffer[3] * 256 * 256 * 256 +
	                            buffer[2] * 256 * 256 + buffer[1] * 256 +
	                            buffer[0];

	std::cout << " (" << std::dec << concatenatedTemp << " bytes)" << std::endl;

	//chunk size----------------------------------------------------------------
	std::cout << "Chunk size:\t\t0x";
	narc.seekg(0xd, std::ios::beg);
	std::cout << std::setfill('0') << std::setw(2) << std::hex << narc.peek();
	narc.seekg(0xc, std::ios::beg);
	std::cout << std::setfill('0') << std::setw(2) << std::hex << narc.peek()
	          << std::endl;

	//Number of following chunks------------------------------------------------
	std::cout << "Following chunks:\t0x";
	narc.seekg(0xf, std::ios::beg);
	std::cout << std::setfill('0') << std::setw(2) << std::hex << narc.peek();
	narc.seekg(0xe, std::ios::beg);
	std::cout << std::setfill('0') << std::setw(2) << std::hex << narc.peek()
	          << std::endl;



	//File Alocation Table######################################################
	std::cout << "\n_____File Alocation Table_____" << std::endl;

	//Chunk Name----------------------------------------------------------------
	narc.seekg(0x10, std::ios::beg);
	narc.read(readedData, 0x4);
	std::cout << "Chunk Name:\t\t\"";
	for (auto &letter : readedData)
	{
		std::cout << letter;
	}
	std::cout << "\"" << std::endl;

	//Chunk Size----------------------------------------------------------------
	std::cout << "Chunk size:\t\t0x";
	narc.seekg(0x17, std::ios::beg);
	buffer[3] = narc.peek();
	std::cout << std::hex << narc.peek();
	narc.seekg(0x16, std::ios::beg);
	buffer[2] = narc.peek();
	std::cout << std::hex << narc.peek();
	narc.seekg(0x15, std::ios::beg);
	buffer[1] = narc.peek();
	std::cout << std::hex << narc.peek();
	narc.seekg(0x14, std::ios::beg);
	buffer[0] = narc.peek();
	std::cout << std::hex << narc.peek();

	concatenatedTemp = buffer[3] * 256 * 256 * 256 + buffer[2] * 256 * 256 +
	                   buffer[1] * 256 + buffer[0];

	std::cout << " (" << std::dec << concatenatedTemp << " bytes)" << std::endl;

	//Number of Files-----------------------------------------------------------
	int numOfFiles{}; //Used later to read the FAT

	narc.seekg(0x19, std::ios::beg);
	numOfFiles += (narc.peek() * 256);
	narc.seekg(0x18, std::ios::beg);
	numOfFiles += narc.peek();

	std::cout << "Files:\t\t\t" << std::dec << numOfFiles << std::endl;

	//Reserved------------------------------------------------------------------
	std::cout << "Reserved: \t\t0x";
	narc.seekg(0x1b, std::ios::beg);
	std::cout << std::setfill('0') << std::setw(2) << std::hex << narc.peek();
	narc.seekg(0x1A, std::ios::beg);
	std::cout << std::setfill('0') << std::setw(2) << std::hex << narc.peek()
	          << std::endl;

	//FAT-----------------------------------------------------------------------
	std::cout << "FAT" << std::endl;

	uint32_t temp{};
	int offset{0x1c};

	for (int file{1}; file <= numOfFiles; file++)
	{
		std::cout << std::dec << file << ":\t" << std::hex;

		narc.seekg(offset, std::ios::beg);
		narc.read(reinterpret_cast<char *>(&temp), sizeof temp);
		std::cout << std::setfill('0') << std::setw(4) << temp << " - ";

		offset += 4;

		narc.seekg(offset, std::ios::beg);
		narc.read(reinterpret_cast<char *>(&temp), sizeof temp);
		std::cout << std::setfill('0') << std::setw(4) << temp << std::endl;

		offset += 4;
	}
}
