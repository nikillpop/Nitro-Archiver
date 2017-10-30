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
#include <vector>

void fillVirtualFat(std::fstream &narc, std::vector<uint32_t> virtualFat[]);

void writeFiles(std::fstream &narc, std::vector<std::string> &args)
{
	std::vector<uint32_t> virtualFat[2];
	uint16_t numOfFiles{};
	fillVirtualFat(narc, virtualFat);
}

void fillVirtualFat(std::fstream &narc, std::vector<uint32_t> virtualFat[]) {}