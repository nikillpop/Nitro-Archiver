This project aims to full support of write/read Nitro Archives for NDS rom hacking purposes, also learn C++ programing.

# Nitro Archive
Nitro ARChives are files with a mini virtual filesystem to handle containing multiple files inside them, used in Nintendo DS games, very common in 4gen Pokémon games.  
R/W of NARCs (and NitroROM filesystem) its needed in order to modify some NDS games using tools, if not, you would have to search and extract the files manually, however, there already are some tools can do this (ex: ndstool, tinke ).

# Features
  - Read Header, FAT & FNT info (WIP).

# TODO
  - Extract files from narcs.
  - Extract narcs from NDS ROMS.
  - Make new empty narcs.
  - Over/write files to narcs.
  - Over/write narcs to NDS ROMs.
  - Support calling the tool with arguments.

# how to build

Run make.bat

You need the basic installation of MinGW/64.  
This project is compiled with MinGW64 5.0.2 (gcc 7.1.0)
