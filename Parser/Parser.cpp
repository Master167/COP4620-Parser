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
    bool result = true;
    if (this->getNextToken()) {
        try {
            this->program();
        }
        catch (int e) {
            result = false;
        }
        catch (std::string e) {
            std::cout << e << std::endl;
            result = false;
        }
    }
    else {
        result = false;
    }
    return result;
}

bool Parser::getNextToken() {
    bool result = false;
    std::string temp;
    while (temp.length() <= 0) {
        if (!std::getline(this->filestream, temp)) {
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
    bool result = true;
    std::size_t findResult;
    std::string keyword;
    //search.compare(this->keywords[i]) == 0
    if (this->currentToken.compare(token) == 0) {
        result = this->getNextToken();
    }
    else {
        /*
         * Check for NUM, ID, KEYWORD, and ERROR
         */
        findResult = this->currentToken.find(token);
        if (findResult != std::string::npos) {
            //ID: We're not checking if ID has been declared, that's a semantic problem.
            //ERROR: We're never going to accept a error token. Therefore it never be found in .find()
            //KEYWORD: we need to check the KEYWORD
            //NUM: can be INT or FLOAT and indicates a Number constant
            findResult = this->currentToken.find("KEYWORD: ");
            if (findResult != std::string::npos) {
                // Need to remove "KEYWORD: " from string to check if token is the same
                keyword = this->currentToken.erase(findResult, 9);
                if (keyword.compare(token) == 0) {
                    result = this->getNextToken();
                }
                else {
                    // Not the same keyword
                    this->throwBadAcceptToken(this->currentToken, token);
                    result = false;
                }
            }
            else {
                // Not a keyword, could be a NUM
                findResult = this->currentToken.find("FLOAT");
                if (findResult == std::string::npos) {
                    // Ok, FLOAT is not in the currentToken
                    findResult = this->currentToken.find("INT");
                    if (findResult == std::string::npos) {
                        // INT is not in the currentToken. This is not a NUM
                        this->throwBadAcceptToken(this->currentToken, token);
                        result = false;
                    }
                    else {
                        result = this->getNextToken();
                    }
                }
                else {
                    result = this->getNextToken();
                }
            }
        }
        else {
            // token is not inside this->currentToken
            this->throwBadAcceptToken(this->currentToken, token);
            result = false;
        }
    }
    return result;
}

void Parser::throwBadAcceptToken(std::string badToken, std::string expectedToken) throw(std::string) {
    std::string message = "Expected: " + expectedToken + " Found: " + badToken;
    throw message;
    return;
}

void Parser::throwException() throw (int) {
    throw -1;
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
