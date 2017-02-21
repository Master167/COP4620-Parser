Project 1 Compiler
COP 4620/5625
CONSTRUCTION OF LANGUAGE TRANSLATORS
Dr. Roger Eggen
Due: 2/2/17

Michael Frederick
N00725913

Overall Design:
This project is to build and design a Lexical Analyzer for C-. This program will generate
tokens to be used by the next project's parser. This is done by iterating through an input
file line by line and outputing each C- token or identifier it recognizes. Tokens are identified
according to the Lexical Conventions of C- in "Compiler Construction, Principles and Practice"
by Kenneth C. Louden on pages 491-492. With the added ability to determine between float and integer numbers and allowing nested multiline comments

How to Run:
Issue make command in terminal.
Invoke Program with Bash command:
./p1 [filename]
	with [filename] being the file to execute the lexical analysis.

Files Created:
None all output will be to terminal.

Files Required:
LexicalAnalyzer.cpp
LexicalAnalyzer.h
main.cpp
Symbol.cpp
Symbol.h
SymbolTable.cpp
SymbolTable.h
-A file to analyze

Special Concerns:
Program will output to terminal "Bad file" if it is unable to open the file and "No Input
file given" if no file is passed in through command-line.