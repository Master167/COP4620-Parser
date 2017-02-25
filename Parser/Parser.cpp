/* 
 * File:   Parser.cpp
 * Author: Michael Frederick (n00725913)
 * 
 * Created on February 24, 2017, 6:15 PM
 */

#include "Parser.h"


Parser::Parser(std::fstream& inputFile) : filestream(inputFile) {
}

bool Parser::parseFile() {
    while (this->getNextToken()) {
        std::cout << this->currentToken << std::endl;
    }
    return true;
}

bool Parser::getNextToken() {
    bool result = false;
    std::string temp;
    while (temp.length() <= 0) {
        if (!std::getline(this->filestream,temp)) {
            break;
        }
    }
    if (temp.length() > 0) {
        result = true;
        this->currentToken = temp;
    }
    else {
        this->currentToken = "";
    }
    return result;
}