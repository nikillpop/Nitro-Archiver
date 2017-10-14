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
void caller(arg[], const int, std::fstream &);
void readHeaderData(std::fstream &);

int main(int argc, char *argv[])
{
	std::cout << "\nNitro-Archiver v1.1beta - Copyright (C) 2017 Jes\n"
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
	}
	else
	{
		std::cerr << "Something bad happened, this program only suports "
		          << "opening with one argument which must be a filename.";
		return 1;
	}

	/** "string TempArgs" guardara los argumentos en línea
	 * para luego almacenarlos en "arg argument" de una
	 * manera que se puedan utilizar mejor */
	std::string tempArgs;
	std::cout << "Enter arguments: ";
	std::getline(std::cin, tempArgs);

	/** El numero máximo de argumentos simultáneos
	 * serán 2 por ahora, luego intentare usar std::array*/
	const int maxArgs{2};
	arg arguments[maxArgs]{arg::NO_ARG};

	parseTempArgs(tempArgs, arguments, maxArgs);

	caller(arguments, maxArgs, narc);

	std::cin.get();
}

void parseTempArgs(std::string argsToParse, arg finalArgs[], const int maxArgs)
{
	if (argsToParse.compare(0, 2, "-h") == 0)
	{
		finalArgs[0] = arg::HELP;
	}

	if (argsToParse.compare(0, 2, "-d") == 0)
	{
		finalArgs[0] = arg::HEADER_DATA;
	}
}

void caller(arg arguments[], const int maxArgs, std::fstream &narc)
{
	if (arguments[0] == arg::HEADER_DATA)
	{
		readHeaderData(narc);
	}
}
