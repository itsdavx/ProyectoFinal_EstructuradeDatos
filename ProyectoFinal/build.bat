@echo off
echo Compilando proyecto...
if not exist build mkdir build
g++ -std=c++17 -Iinclude src/estructuras/*.cpp src/general/*.cpp -o build/ProyectoFinal.exe
if %errorlevel% neq 0 (
    echo Hubo errores durante la compilacion.
    pause
    exit /b %errorlevel%
)
echo Compilacion exitosa.
echo Ejecutando programa...
build\ProyectoFinal.exe
pause
