/* 
 * File:   main.cpp
 * Author: Michael Frederick (n00725913)
 *
 * Created on Febuary 20, 2017, 2:41 PM
 */
#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include "LexicalAnalyzer.h"
#include "SymbolTable.h"

/*
 * Main Starting point of the program
 */
int main(int argc, char** argv) {
    if (argc > 1) {
        std::string filename = argv[1];
        std::fstream inputFile(argv[1]);
        if (inputFile.is_open()) {
            SymbolTable* symTab = new SymbolTable(100);
            LexicalAnalyzer* lexy = new LexicalAnalyzer(inputFile, filename);
            if (lexy->isReady()) {
                lexy->scanFile(symTab);
                //symTab->printTable();
            }
            else {
                std::cout << "Unable to allocate memory for lexical analyzer";
            }
            delete lexy;
            delete symTab;
        }
        else {
            std::cout << "Bad Input file" << std::endl;
        }
    }
    else {
        std::cout << "No Input file given" << std::endl;
    }
    return 0;
}

