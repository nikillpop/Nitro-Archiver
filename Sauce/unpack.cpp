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
	narc.seekg(0x18, std::ios::beg);
	uint16_t numOfFiles{};
	narc.read(reinterpret_cast<char *>(&numOfFiles), 0x2);

	if (args.empty()) //If user only provide "-u"
	{
		std::cout << "The number of files is " << numOfFiles;
		return;
	}

	std::vector<int> fileIndex;
	fileIndex.resize(args.size());

	int i{0};
	for (const auto &fileNumber : args)
	{
		fileIndex.at(i) = std::stoi(fileNumber);
		++i;
	}

	long fimgStartAdress{0x14};
	uint32_t tempRead{};

	//FAT size
	narc.seekg(fimgStartAdress, std::ios::beg);
	narc.read(reinterpret_cast<char *>(&tempRead), 0x4);
	fimgStartAdress += tempRead;

	//FNT size
	narc.seekg(fimgStartAdress, std::ios::beg);
	narc.read(reinterpret_cast<char *>(&tempRead), 0x4);
	fimgStartAdress += tempRead + 0x4;


	uint32_t fatStartEntry{};
	uint32_t fatFinalEntry{};
	int fileSize{};
	int nameIndex{};

	for (const auto &fileToExtract : fileIndex)
	{
		if (fileToExtract > numOfFiles)
		{
			std::cout << "The file N" << char(167) << ' ' << fileToExtract
			          << " doesn't exist\n";
			++nameIndex;
			continue;
		}
		//To know how many bytes long is the file to extract
		narc.seekg((fileToExtract * 8) + 0x1c, std::ios::beg);
		narc.read(reinterpret_cast<char *>(&fatStartEntry), 0x4);
		narc.read(reinterpret_cast<char *>(&fatFinalEntry), 0x4);
		fileSize = fatFinalEntry - fatStartEntry;

		//Prepare the read container
		narc.seekg(fimgStartAdress + fatStartEntry, std::ios::beg);
		std::string contents;
		contents.resize(fileSize);

		narc.read(&contents[0], fileSize);
		std::ofstream outputFile(args[nameIndex]);
		outputFile.write(&contents[0], fileSize);
		++nameIndex;
	}
}