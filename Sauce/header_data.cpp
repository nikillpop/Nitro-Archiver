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

std::string ToHex(const std::string &s);

void readHeaderData(std::fstream &narc)
{
	char readedData[4]{};

	std::cout << "\n_______Narc Header_______" << std::endl;


	//Chunk Name----------------------------------------------------------------
	narc.seekg(0x0, std::ios::beg);
	narc.read(readedData, 0x4);
	std::cout << "Chunk Name:\t\"";
	for (auto &letter : readedData)
	{
		std::cout << letter;
	}
	std::cout << "\"" << std::endl;


	//Byte Order----------------------------------------------------------------
	narc.seekg(0x5, std::ios::beg);
	narc.read(readedData, 0x2);

	std::string tohexed = ToHex(std::string(readedData, narc.gcount()));

	std::cout << "Byte Order:\t0x" << tohexed << std::endl;


	//Version-------------------------------------------------------------------
	std::cout << "Version:\t0x";

	narc.seekg(0x7, std::ios::beg);
	std::cout << std::setfill('0') << std::setw(2) << std::hex << narc.peek();
	narc.seekg(0x6, std::ios::beg);
	std::cout << std::setfill('0') << std::setw(2) << std::hex << narc.peek()
	          << std::endl;


	//File Size-----------------------------------------------------------------
	std::cout << "File Size:\t0x";

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

	uint32_t x = buffer[3] * 256 * 256 * 256 + buffer[2] * 256 * 256 +
	             buffer[1] * 256 + buffer[0];

	std::cout << " (" << std::dec << x << " bytes)";


	//File Alocation Table======================================================
	std::cout << "\n__File Alocation Table___" << std::endl;

	narc.seekg(0x18, std::ios::beg);
	narc.read(readedData, 0x2);
	std::cout << "Files:\t\t" << std::dec << readedData[0] + readedData[1]
	          << std::endl;
}

std::string ToHex(const std::string &s)
{
	std::ostringstream ret;

	for (std::string::size_type i = s.length(); i > 0; --i)
	{
		int z = s[i - 1] & 0xff;
		ret << std::hex << std::setfill('0') << std::setw(2) << std::uppercase
		    << z;
	}

	return ret.str();
}
