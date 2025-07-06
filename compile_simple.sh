#!/bin/bash

# Script simple para compilar con g++ main.cpp -o test
# Navega al directorio src y compila

cd src
g++ main.cpp -o test
echo "Compilación completada. Ejecuta './src/test' para correr el programa." 