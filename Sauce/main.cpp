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

#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

#define FILE_SELECTED_WITH_ARGUMENTS true
#define FILE_SELECTED_WITH_NITRO_ARCHIVER false

enum class arg
{
	// Usados como flags
	NO_ARG,
	ERROR,

	// Comandos
	HELP,        //-h
	HEADER_DATA, //-d
};

void readHeaderData(std::fstream &narc);
void chekFile(std::fstream &narc, bool openedViaArgument);

int main(int argc, char *argv[])
{
	std::cout << "\nNitro-Archiver v1.9beta - Copyright (C) 2017 Jes\n"
	          << "This software is distributed under "
	          << "GNU General Public Licence v3\n"
	          << "You can get a copy of the source code in "
	          << "<https://github.com/JesMJM/Nitro-Archiver>\n"
	          << std::endl;

	std::fstream narc;

	//If the user simply opens the program.
	if (argc == 1)
	{
		std::cout << "Enter filename to open: ";
		std::string fileName;
		std::getline(std::cin, fileName);

		narc.open(fileName, std::ios::binary | std::ios::in);

		if (narc.fail())
		{
			std::cerr << "Error opening \"" << fileName << "\"" << std::endl;
			return 1;
		}
		chekFile(narc, FILE_SELECTED_WITH_NITRO_ARCHIVER);
	}
	//If the user opens the program dragging a narc in the exe file.
	else if (argc == 2)
	{
		narc.open(argv[1], std::ios::binary | std::ios::in);

		if (narc.fail())
		{
			std::cerr << "Error opening \"" << argv[1] << "\"" << std::endl;
			return 1;
		}
		chekFile(narc, FILE_SELECTED_WITH_ARGUMENTS);
	}
	//If the user opens the program calling it with args from command line.
	else
	{
		std::vector<std::string> arguments(argv, argv + argc);
		narc.open(arguments.at(1), std::ios::binary | std::ios::in);

		if (narc.fail())
		{
			std::cerr << "Error opening \"" << arguments.at(1) << "\""
			          << std::endl;
			return 1;
		}
		//Deletes args "X:\...\Narc-Archiver" & "X:\...\filename.narc".
		arguments.erase(arguments.begin(), arguments.begin() + 2);

		chekFile(narc, FILE_SELECTED_WITH_ARGUMENTS);
	}

	//Ask args if user do not open the program with args from command line.
	if (argc < 3)
	{
		std::vector<std::string> arguments;

		std::string tempString{};
		std::string tempStringSearch{};
		std::cout << "Enter arguments: ";
		getline(std::cin, tempString);

		while (!tempString.empty())
		{
			arguments.push_back(tempString.substr(0, tempString.find(' ')));

			tempString.erase(0, (tempString.find(' ') + 1));
		}
	}

	std::cin.get();
}


void chekFile(std::fstream &narc, bool openedViaArgument)
{
	bool invalidInput{false}; //If true at the end of the func, trows a warn.
	char buffer[4]{};         //Temporal storage for using read();.
	std::string tempString{}; //For comparing buffer with == or !=.

	//First 0x4 bytes of narc header must say "NARC".
	narc.seekg(0x0, std::ios::beg);
	narc.read(buffer, 0x4);
	tempString.assign(buffer, 4);
	if (tempString != "NARC") invalidInput = true;

	//First 0x4 bytes of FAT must say "BTAF".
	narc.seekg(0x10, std::ios::beg);
	narc.read(buffer, 0x4);
	tempString.assign(buffer, 4);
	if (tempString != "BTAF") invalidInput = true;

	//The FAT chunk size must make sense whit the number of files.
	uint16_t files{};
	uint32_t chunkSize{};

	narc.seekg(0x18, std::ios::beg);
	narc.read(buffer, 0x2);
	files = buffer[1] * 256 + buffer[0];

	narc.seekg(0x14, std::ios::beg);
	narc.read(buffer, 0x4);
	chunkSize = buffer[3] * 256 * 256 * 256 + buffer[2] * 256 * 256 +
	            buffer[1] * 256 + buffer[0];

	if (((files * 8u) + 0xCu) != chunkSize) invalidInput = true;

	//End of checks.
	if (invalidInput)
	{
		std::cout << "Error:\tThe file is invalid or is corrupted\n"
		          << "\tyou continue at your own risk.\n\n";

		if (openedViaArgument)
		{
			std::cout << "Press enter to continue.";
			if (std::cin.get() == '\n') return;
			exit(0);
		}
	}
}
