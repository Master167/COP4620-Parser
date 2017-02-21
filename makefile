compiler: LexicalAnalyzer.cpp main.cpp Symbol.cpp SymbolTable.cpp
	g++ -o compiler main.cpp LexicalAnalyzer.cpp Symbol.cpp SymbolTable.cpp