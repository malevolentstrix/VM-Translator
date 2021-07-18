#ifndef _PARSER_
#define _PARSER_

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

enum VMcommand
{
	C_ARITHMETIC,
	C_PUSH,
	C_POP,
	C_LABEL,
	C_GOTO,
	C_IF,
	C_FUNCTION,
	C_RETURN,
	C_CALL
};

class Parser
{
public:
	Parser();
	Parser(string filename);
	~Parser();

	bool hasMoreCommands(void);
	void advance(void);
	VMcommand commandType(void);
	string arg1(void);
	int arg2(void);
	void setFileName(string filename);

private:
	string filename;
	string CurrLine;
	ifstream inf;
};

#endif