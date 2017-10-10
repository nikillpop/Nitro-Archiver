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

int main()
{
	std::cout << "Narc-Archiver, Commit #15, By Jes" << char(163) << "s (Jes)\n"
	          << std::endl;

	std::cout << "Enter filename to open: ";
	std::string fileName;
	std::getline(std::cin, fileName);

	std::fstream narc(fileName, std::ios::binary | std::ios::in);

	if (narc.fail())
	{
		std::cerr << "Error opening \"" << fileName << "\"" << std::endl;
		return 1;
	}
	else
	{
		std::cout << "File opened correctly\n" << std::endl;
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
