cd ..

mkdir Bin

windres NARC-Archiver.rc -O coff -F pe-x86-64 -o Bin/metaData.64res

windres NARC-Archiver.rc -O coff -F pe-i386 -o Bin/metaData32.res

x86_64-w64-mingw32-g++ -std=c++17 -static -o Bin/Narc-Archiver-x64.exe -O3 Sauce/main.cpp Sauce/header_data.cpp Bin/metaData.64res

i686-w64-mingw32-g++ -std=c++17 -static -o Bin/Narc-Archiver-x32.exe -O3 Sauce/main.cpp Sauce/header_data.cpp Bin/metaData32.res

cd Bin

del "metaData.64res"

del "metaData32.res"