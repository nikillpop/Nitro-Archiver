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

enum class arg
{
	// Usados como flags
	NO_ARG,
	ERROR,

	// Comandos
	HELP,        //-h
	HEADER_DATA, //-d
};

void parseTempArgs(std::string, arg[], const int);
void caller(arg[], const int, std::fstream &narc);
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
		else
		{
			std::cout << "File opened correctly\n" << std::endl;
			//False means the file was selected with Nitro-Archiver
			chekFile(narc, false);
		}
	}
	else if (argc == 2)
	{

		narc.open(argv[1], std::ios::binary | std::ios::in);

		if (narc.fail())
		{
			std::cerr << "Error opening \"" << argv[1] << "\"" << std::endl;
			return 1;
		}
		//True means the file was selected via argument
		chekFile(narc, true);
	}
	else
	{
		std::cerr << "Something bad happened, this program only suports "
		          << "opening with one argument which must be a filename.";
		return 1;
	}

	std::string tempArgs;
	std::cout << "Enter arguments: ";
	std::getline(std::cin, tempArgs);

	const int maxArgs{2};
	arg arguments[maxArgs]{arg::NO_ARG};

	parseTempArgs(tempArgs, arguments, maxArgs);

	caller(arguments, maxArgs, narc);

	std::cin.get();
}

void parseTempArgs(std::string argsToParse, arg finalArgs[], const int maxArgs)
{
	if (argsToParse.compare(0, 2, "-h") == 0) finalArgs[0] = arg::HELP;

	if (argsToParse.compare(0, 2, "-d") == 0) finalArgs[0] = arg::HEADER_DATA;
}

void caller(arg arguments[], const int maxArgs, std::fstream &narc)
{
	if (arguments[0] == arg::HEADER_DATA) readHeaderData(narc);
}

void chekFile(std::fstream &narc, bool openedViaArgument)
{
	bool invalidInput{false}; //If true at the end of the func, trows a warn
	char buffer[4]{};         //Temporal storage for using read();
	std::string tempSting{};  //For comparing buffer with == or !=

	//First 0x4 bytes of narc header must say "NARC"
	narc.seekg(0x0, std::ios::beg);
	narc.read(buffer, 0x4);
	tempSting.assign(buffer, 4);
	if (tempSting != "NARC") invalidInput = true;

	//First 0x4 bytes of FAT must say "BTAF"
	narc.seekg(0x10, std::ios::beg);
	narc.read(buffer, 0x4);
	tempSting.assign(buffer, 4);
	if (tempSting != "BTAF") invalidInput = true;

	//The FAT chunk size must make sense whit the number of files
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

	//End of checks
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
