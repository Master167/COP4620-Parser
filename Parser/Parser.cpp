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
            std::cout << "Int Exception thrown" << std::endl;
            result = false;
        }
        catch (std::string e) {
            std::cout << e << std::endl;
            result = false;
        }
    }
    else {
        std::cout << "Unable to pull first token" << std::endl;
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
    
    if (token.compare("id") == 0) {
        findResult = this->currentToken.find("ID:");
        if (findResult != std::string::npos) {
            result = this->getNextToken();
        }
        else {
            this->throwBadAcceptToken(this->currentToken, token);
            result = false;
        }
    }
    else if (this->currentToken.compare(token) == 0) {
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

bool Parser::searchArray(int arraySize, std::string *array, std::string key) {
    bool result = false;
    // Need to clean the key a tad. To remove text added by LexicalAnalyzer
    //  -Ex: Remove 'KEYWORD: ' from a keyword
    std::string temp;
    std::string compareToken = this->currentToken;
    std::size_t findResult = compareToken.find("KEYWORD: ", 0);
    if (findResult != std::string::npos) {
        compareToken.erase(findResult, 9);
    }
    else {
        findResult = compareToken.find("INT: ", 0);
        if (findResult != std::string::npos) {
            compareToken = "int";
        }
        else {
            findResult = compareToken.find("FLOAT: ", 0);
            if (findResult != std::string::npos) {
                compareToken = "float";
            }
            else {
                findResult = compareToken.find("ID: ", 0);
                if (findResult != std::string::npos) {
                    compareToken = "id";
                }
            }
        }
    }
    
    for (int i = 0; i < arraySize; i++) {
        temp = array[i];
        if (temp.compare(compareToken) == 0) {
            result = true;
            break;
        }
    }
    return result;
}

// Grammar Methods
void Parser::program() {
    this->declarationList();
    return;
}

void Parser::declarationList() {
    this->declaration();
    this->declarationListPrime();
    return;
}

void Parser::declarationListPrime() {
    std::string firstSet[3] = { "int", "float", "void" };
    if (this->searchArray(3, firstSet, this->currentToken)) {
        this->declaration();
        this->declarationListPrime();
    }
    else {
        // Follow set for declaration-list-prime is the end of file and it can go empty
        return;
    }
    return;
}

void Parser::declaration() {
    std::string firstSet[3] = { "int", "float", "void" };
    if (this->searchArray(3, firstSet, this->currentToken)) {
        this->typeSpecifier();
        this->acceptToken("id");
        this->callDeclaration();
    }
    else {
        this->throwException();
    }
    return;
}

void Parser::callDeclaration() {
    std::string idFirst[2] = { ";", "[" };
    if (this->searchArray(2, idFirst, this->currentToken)) {
        this->idSpecifier();
    }
    else if (this->currentToken.compare("(") == 0) {
        this->acceptToken("(");
        this->params();
        this->acceptToken(")");
        this->compountStmt();
    }
    else {
        this->throwException();
    }
    return;
}

void Parser::idSpecifier() {
    if (this->currentToken.compare(";") == 0) {
        this->acceptToken(";");
    }
    else if (this->currentToken.compare("[") == 0) {
        this->acceptToken("[");
        this->acceptToken("NUM");
        this->acceptToken("]");
        this->compountStmt();
    }
    else {
        this->throwException();
    }
    return;
}

void Parser::typeSpecifier() {
    std::string first[1] = { "int" };
    std::string second[1] = { "float" };
    std::string third[1] = { "void" };
    if (this->searchArray(1, first, this->currentToken)) {
        this->acceptToken("int");
    }
    else if (this->searchArray(1, second, this->currentToken)) {
        this->acceptToken("float");
    }
    else if (this->searchArray(1, third, this->currentToken)) {
        this->acceptToken("void");
    }
    else {
        this->throwException();
    }
    return;
}

void Parser::params() {
    std::string first[1] = { "int" };
    std::string second[1] = { "float" };
    std::string third[1] = { "void" };
    if (this->searchArray(1, first, this->currentToken)) {
        this->acceptToken("int");
        this->acceptToken("id");
        this->array();
        this->paramListPrime();
    }
    else if (this->searchArray(1, second, this->currentToken)) {
        this->acceptToken("float");
        this->acceptToken("id");
        this->array();
        this->paramListPrime();
    }
    else if (this->searchArray(1, third, this->currentToken)) {
        this->acceptToken("void");
        this->paramList();
    }
    else {
        this->throwException();
    }
    return;
}

void Parser::paramList() {
    std::string first[1] = { "id" };
    if (this->searchArray(1, first, this->currentToken)) {
        this->acceptToken("id");
        this->array();
        this->paramListPrime();
    }
    else if (this->currentToken.compare(")")) {
        // Go to empty
        return;
    }
    else {
        this->throwException();
    }
    return;
}

void Parser::paramListPrime() {
    if (this->currentToken.compare(",") == 0) {
        this->acceptToken(",");
        this->param();
        this->paramListPrime();
    }
    else if (this->currentToken.compare(")") == 0) {
        // Go to empty
        return;
    }
    else {
        this->throwException();
    }
    return;
}

void Parser::param() {
    std::string first[3] = { "int", "float", "void" };
    if (this->searchArray(3, first, this->currentToken)) {
        this->typeSpecifier();
        this->acceptToken("id");
        this->array();
    }
    else {
        this->throwException();
    }
    return;
}

void Parser::array() {
    std::string follow[2] = { ",", ")" };
    if (this->currentToken.compare("[") == 0) {
        this->acceptToken("[");
        this->acceptToken("]");
    }
    else if (this->searchArray(2, follow, this->currentToken)) {
        // Go to empty
        return;
    }
    else {
        this->throwException();
    }
    return;
}

// Pause here and parse
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
