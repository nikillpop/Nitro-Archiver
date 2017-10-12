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

	int s = 2;

	std::string tohexed = ToHex(std::string(readedData, s));

	std::cout << "Byte Order:\t0x" << tohexed << std::endl;


	std::cout << "\n__File Alocation Table___" << std::endl;


	narc.seekg(0x18, std::ios::beg);
	narc.read(readedData, 0x2);
	std::cout << "Files:\t\t" << std::dec << readedData[0] + readedData[1]
	          << std::endl;
}

std::string ToHex(const std::string &s)
{
	std::ostringstream ret;

	for (std::string::size_type i = 0; i < s.length(); ++i)
	{
		int z = s[i] & 0xff;
		ret << std::hex << std::setfill('0') << std::setw(2) << std::uppercase
		    << z;
	}

	return ret.str();
}
