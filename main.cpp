#include <fstream>
#include <iomanip>
#include <iostream>

/**
 * Idea para convertir los comandos que el usuario
 * introduzca en "tempCmds" en algo manejable, convirtiendo
 * los comandos en un array de enumeradores
 *
enum class cmds
{
	NO_CMDS,
	ERROR,
	HELP,
	HEADER,
};
*/

int main()
{
	std::cout << "Narc-Archiver, Commit #7, By Jes" << char(163) << "s (Jes)\n"
	          << std::endl;

	std::cout << "Enter file name: ";
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

	std::string tempCmds;

	std::cout << "Enter commands: ";
	std::getline(std::cin, tempCmds);

	std::cin.get();
}
