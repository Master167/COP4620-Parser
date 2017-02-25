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
#include <cstdio>
#include "LexicalAnalyzer.h"
#include "SymbolTable.h"
#include "Parser.h"

/*
 * Main Starting point of the program
 */
int main(int argc, char** argv) {
    if (argc > 1) {
        bool continueCompile = false;
        std::string filename = argv[1];
        std::fstream inputFile(argv[1]);
        if (inputFile.is_open()) {
            SymbolTable* symTab = new SymbolTable(100);
            LexicalAnalyzer* lexy = new LexicalAnalyzer(inputFile, filename);
            if (lexy->isReady()) {
                continueCompile = lexy->scanFile(symTab);
                if (continueCompile) {
                    // Transition from input to MY temp file
                    std::string tempFilename = filename.append(".temp");
                    std::fstream tempFilestream(tempFilename.c_str());
                    inputFile.flush();
                    inputFile.close();
                    Parser* percy = new Parser(tempFilestream);
                    percy->parseFile();
                    delete percy;
                }
                //symTab->printTable();
            }
            else {
                std::cout << "Unable to allocate memory for compiler";
            }
            delete lexy;
            delete symTab;
            remove(filename.append(".temp").c_str());
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

