// bmp_reader.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>

#include <string>
#include <fstream>
#include <vector>
#include <errno.h>
#include "BMPreader.h"

int main(int argc, char *argv[])
{
    if (argc == 1) {
        std::cerr << "no input file\n";
        return 0;
    }
    
    BMPreader bmp;
    bmp.openBMP(argv[1]);
    bmp.displayBMP();
    // 24 and 32 dont have pallete
    
    
    return 0;
}

