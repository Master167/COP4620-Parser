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

bool Parser::acceptToken(std::string token) {
    return true;
}

void Parser::throwBadAcceptToken(std::string badToken, std::string expectedToken) {
    return;
}

void Parser::throwException(){
    return;
}

// Grammar Methods
void Parser::program() {
    return;
}

void Parser::declarationList() {
    return;
}

void Parser::declarationListPrime() {
    return;
}

void Parser::declaration() {
    return;
}

void Parser::callDeclaration() {
    return;
}

void Parser::idSpecifier() {
    return;
}

void Parser::typeSpecifier() {
    return;
}

void Parser::params() {
    return;
}

void Parser::paramList() {
    return;
}

void Parser::paramListPrime() {
    return;
}

void Parser::param() {
    return;
}

void Parser::array() {
    return;
}

void Parser::compountStmt() {
    return;
}

void Parser::localDeclarations() {
    return;
}

void Parser::localDeclarationsPrime() {
    return;
}

void Parser::statementList() {
    return;
}

void Parser::statementListPrime() {
    return;
}

void Parser::statement() {
    return;
}

void Parser::expressionStmt() {
    return;
}

void Parser::selectionStmt() {
    return;
}

void Parser::danglingElse() {
    return;
}

void Parser::iterationStmt() {
    return;
}

void Parser::returnStmt() {
    return;
}

void Parser::returnStmtEnd() {
    return;
}

void Parser::expression() {
    return;
}

void Parser::variable() {
    return;
}

void Parser::variableFactor() {
    return;
}

void Parser::varArray() {
    return;
}

void Parser::relopExpression() {
    return;
}

void Parser::relop() {
    return;
}

void Parser::additiveExpression() {
    return;
}

void Parser::additiveExpressionPrime() {
    return;
}

void Parser::addop() {
    return;
}

void Parser::term() {
    return;
}

void Parser::termPrime() {
    return;
}

void Parser::mulop() {
    return;
}

void Parser::varCall() {
    return;
}

void Parser::args() {
    return;
}

void Parser::argList() {
    return;
}

void Parser::argListPrime() {
    return;
}
