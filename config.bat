@echo off
if not exist build mkdir build
cd build
cmake -G "Visual Studio 17 2022" ..  %*  # Adjust for your version of Visual Studio
cd ..
