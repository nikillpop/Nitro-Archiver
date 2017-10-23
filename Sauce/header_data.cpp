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

//TODO: make an arg to select if FAT is showed.
//TODO: make a general "std::hex" and "std::setfill() << std::setw()"

void NARCinfo(std::fstream &narc)
{
	char charBuffer[5]{'\0'};
	uint16_t buffer16{};
	uint32_t buffer32{};
	narc.seekg(0x0, std::ios::beg);

	std::cout.unsetf(std::ios::dec);
	std::cout.setf(std::ios::hex);  //Most used output format.
	std::cout << std::setfill('0'); //Most used padding char.

	//Narc Header chunk=<0x0-0xF>=(16-bytes)====================================
	std::cout << "\n_________Narc Header__________" << std::endl;

	//Chunk Name-<0x0-0x3>-(4-bytes)--------------------------------------------
	std::cout << "Chunk Name:\t\t";
	narc.read(charBuffer, 0x4);
	std::cout << "\"" << charBuffer << "\"" << std::endl;

	//Byte Order-<0x4-0x5>-(2-bytes)--------------------------------------------
	std::cout << "Byte Order:\t\t0x";
	narc.read(reinterpret_cast<char *>(&buffer16), 0x2);
	std::cout << std::setw(4) << buffer16 << std::endl;

	//Version-<0x6-0x7>-(2-bytes)-----------------------------------------------
	std::cout << "Version:\t\t0x";
	narc.read(reinterpret_cast<char *>(&buffer16), 0x2);
	std::cout << std::setw(4) << buffer16 << std::endl;

	//File Size-<0x8-0xb>-(4-bytes)---------------------------------------------
	std::cout << "File Size:\t\t0x";
	narc.read(reinterpret_cast<char *>(&buffer32), 0x4);
	std::cout << std::setw(4) << buffer32 << " (" << std::dec << buffer32
	          << " bytes)" << std::endl;

	//chunk size-<0xc-0xd>-(2-bytes)--------------------------------------------
	std::cout << "Chunk size:\t\t0x";
	narc.read(reinterpret_cast<char *>(&buffer16), 0x2);
	std::cout << std::setw(4) << buffer16 << std::endl;

	//Number of following chunks-<0xe-0xf>-(2-bytes)----------------------------
	std::cout << "Following chunks:\t0x";
	narc.read(reinterpret_cast<char *>(&buffer16), 0x2);
	std::cout << std::setw(4) << buffer16 << std::endl;



	//File Allocation Table chunk=<0x10-0x??>=(??-bytes)========================
	std::cout << "\n_____File Allocation Table_____" << std::endl;

	//Chunk Name-<0x10-0x13>-(4-bytes)------------------------------------------
	narc.read(charBuffer, 0x4);
	std::cout << "Chunk Name:\t\t";
	std::cout << "\"" << charBuffer << "\"" << std::endl;

	//Chunk Size-<0x14-0x17>-(4-bytes)------------------------------------------
	std::cout << "Chunk size:\t\t0x";
	narc.read(reinterpret_cast<char *>(&buffer32), 0x4);
	std::cout << std::setw(4) << buffer32 << " (" << std::dec << buffer32
	          << " bytes)" << std::endl;

	//Number of Files-<0x18-0x19>-(2-bytes)-------------------------------------
	uint16_t numOfFiles{}; //Used later to iterate trough FAT

	narc.read(reinterpret_cast<char *>(&numOfFiles), 0x2);
	std::cout << "Files:\t\t\t" << std::dec << numOfFiles << std::endl;

	//Reserved-<0x1a-0x1b>-(2-bytes)--------------------------------------------
	std::cout << "Reserved: \t\t0x";
	narc.read(reinterpret_cast<char *>(&buffer16), 0x2);
	std::cout << std::setw(4) << buffer16 << std::endl;

	//FAT-<0x1c-0x??>-(??-bytes)------------------------------------------------
	std::cout << "FAT" << std::endl;
	for (int file{1}; file <= numOfFiles; file++)
	{
		std::cout << std::dec << file << ":\t";

		narc.read(reinterpret_cast<char *>(&buffer32), 0x4);
		std::cout << std::setw(8) << buffer32 << " - ";

		narc.read(reinterpret_cast<char *>(&buffer32), 0x4);
		std::cout << std::setw(8) << buffer32 << std::endl;
	}



	//File Name Table chunk=<??>=(??-bytes)=====================================
	std::cout << "\n________File Name Table________" << std::endl;

	//Chunk Name-<??>-(4-bytes)-------------------------------------------------
	narc.read(charBuffer, 0x4);
	std::cout << "Chunk Name:\t\t";
	std::cout << "\"" << charBuffer << "\"" << std::endl;

	//Chunk Size-<??>-(4-bytes)-------------------------------------------------
	std::cout << "Chunk size:\t\t0x";
	narc.read(reinterpret_cast<char *>(&buffer32), 0x4);
	std::cout << std::setw(4) << buffer32 << " (" << std::dec << buffer32
	          << " bytes)" << std::endl;
}
