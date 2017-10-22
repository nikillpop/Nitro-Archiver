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
#include <string>
#include <vector>

void unpackFiles(std::fstream &narc, std::vector<std::string> &args)
{
	/** BUG: crash if only "-u" is provided,
	 *  make code to show number of files instead */

	std::vector<int> fileIndex;
	fileIndex.resize(args.size());

	int i{0};
	for (const auto &fileNumber : args)
	{
		fileIndex.at(i) = std::stoi(fileNumber);
		++i;
	}

	uint32_t startAdress{};
	uint32_t finalAdress{};
	int fileSize{};
	for (const auto &fileToExtract : fileIndex)
	{
		narc.seekg((fileToExtract * 8) + 0x1c, std::ios::beg);
		narc.read(reinterpret_cast<char *>(&startAdress), 0x4);
		narc.read(reinterpret_cast<char *>(&finalAdress), 0x4);
	}
}