windres icon.rc -O coff -o icon.res

g++ -std=c++17 -static -o Narc-Archiver.exe -O3 main.cpp commands/header_data.cpp icon.res