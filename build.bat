@echo off
echo Compilando proyecto...

:: Crear carpeta build si no existe
if not exist build mkdir build

:: Compilar todos los cpp
g++ -std=c++17 -Iinclude src/estructuras/*.cpp src/general/*.cpp -o build/ProyectoFinal.exe

echo Compilacion finalizada.
pause
