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