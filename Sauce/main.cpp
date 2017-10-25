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

void NARCinfo(std::fstream &narc);
void chekFile(std::fstream &narc, bool openedViaArgument);
void unpackFiles(std::fstream &narc, std::vector<std::string> &args);
void usageHelp();

int main(int argc, char *argv[])
{
	std::cout << "\nNitro-Archiver v1.9beta - Copyright (C) 2017 Jes\n"
	          << "This software is distributed under "
	          << "GNU General Public License v3\n"
	          << "You can get a copy of the source code in "
	          << "<https://github.com/JesMJM/Nitro-Archiver>\n\n";

	std::fstream narc;
	std::vector<std::string> arguments(argv, argv + argc);

	//If the user simply opens the program.
	if (argc == 1)
	{
		std::cout << "Enter filename to open: ";
		std::string fileName;
		std::getline(std::cin, fileName);

		narc.open(fileName, std::ios::binary | std::ios::in);

		if (narc.fail())
		{
			std::cerr << "Error opening \"" << fileName << "\"";
			return 1;
		}
		chekFile(narc, FILE_SELECTED_WITH_NITRO_ARCHIVER);
	}
	//If the user opens the program dragging a narc in the exe file.
	else if (argc == 2)
	{
		narc.open(arguments.at(1), std::ios::binary | std::ios::in);

		if (narc.fail())
		{
			std::cerr << "Error opening \"" << arguments.at(1) << "\"";
			return 1;
		}
		chekFile(narc, FILE_SELECTED_WITH_ARGUMENTS);
	}
	//If the user opens the program calling it with args from command line.
	else
	{
		narc.open(arguments.at(1), std::ios::binary | std::ios::in);

		if (narc.fail())
		{
			std::cerr << "Error opening \"" << arguments.at(1) << "\"";
			return 1;
		}
		//Deletes args "X:\...\Narc-Archiver" & "X:\...\filename.narc".
		arguments.erase(arguments.begin(), arguments.begin() + 2);

		chekFile(narc, FILE_SELECTED_WITH_ARGUMENTS);
	}

	//Ask args if user do not open the program with args from command line.
	if (argc < 3)
	{
		if (argc == 1)
		{
			arguments.erase(arguments.begin(), arguments.begin() + 1);
		}
		else
		{
			arguments.erase(arguments.begin(), arguments.begin() + 2);
		}

		std::string tempString{};
		std::cout << "Enter arguments: ";
		getline(std::cin, tempString);

		while (!tempString.empty())
		{
			arguments.push_back(tempString.substr(0, tempString.find(' ')));

			tempString.erase(0, (tempString.find(' ') + 1));
			if (tempString.find(' ') == std::string::npos &&
			    !tempString.empty())
			{
				arguments.push_back(tempString.substr(0, tempString.find(' ')));
				tempString.clear();
			}
		}
	}


	if (arguments.at(0) == "-d")
		NARCinfo(narc);
	else if (arguments.at(0) == "-h")
		usageHelp();
	else if (arguments.at(0) == "-u")
	{
		arguments.erase(arguments.begin());
		unpackFiles(narc, arguments);
	}
	else
	{
		std::cout << "\nCommand \"" << arguments.at(0)
		          << "\" not recognized.\n"
		             "Type '-h' to see command usage.\n"
		             "Type '-h [command]' to see detailed information about "
		             "one command.";
	}
	std::cin.get();
}


void chekFile(std::fstream &narc, bool openedViaArgument)
{
	bool invalidInput{false};
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
	narc.read(reinterpret_cast<char *>(&files), 0x2);

	narc.seekg(0x14, std::ios::beg);
	narc.read(reinterpret_cast<char *>(&chunkSize), 0x4);

	if (((files * 8u) + 0xCu) != chunkSize) invalidInput = true;

	//End of checks.
	if (invalidInput)
	{
		//TODO: try '\a' audible bell
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
