/* 
 * File:   Parser.h
 * Author: Michael Frederick (n00725913)
 *
 * Created on February 24, 2017, 6:15 PM
 */

#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <string>
#include <iostream>
#include <new>
#include <cctype>
#include <sstream>
#include "SymbolTable.h"
#include "Symbol.h"

class Parser {
public:
    Parser(std::fstream& inputFile);
    bool parseFile();
private:
    std::string currentToken;
    std::fstream& filestream;
    
    bool getNextToken();
};

#endif /* PARSER_H */

