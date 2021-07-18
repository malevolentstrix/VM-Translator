#include "Parser.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;

Parser::Parser()
{
	filename="";
}

Parser::Parser(string filename)
{
	inf.open(filename.c_str());
	if (!inf.is_open())
		cerr << "Error: Could not open " << filename << ".\n";
}

Parser::~Parser()
{
	if (inf.is_open())
		inf.close();
}

bool Parser::hasMoreCommands(void)
{
	return !inf.eof();
}

void Parser::advance(void)
{
	if (hasMoreCommands())
	{
		getline(inf, CurrLine);
		while (((CurrLine.substr(0, 2) == "//") || (CurrLine.substr(0, 1) == "")) && hasMoreCommands())
			getline(inf, CurrLine);
	}
}

VMcommand Parser::commandType(void)
{
	if ((CurrLine.substr(0, 3) == "add") || (CurrLine.substr(0, 3) == "sub") || (CurrLine.substr(0, 3) == "neg") || (CurrLine.substr(0, 3) == "and") || (CurrLine.substr(0, 3) == "not") || (CurrLine.substr(0, 2) == "eq") || (CurrLine.substr(0, 2) == "gt") || (CurrLine.substr(0, 2) == "lt") || (CurrLine.substr(0, 2) == "or"))
		return C_ARITHMETIC;
	else if ((CurrLine.substr(0, 4) == "push"))
		return C_PUSH;
	else if ((CurrLine.substr(0, 3) == "pop"))
		return C_POP;
	else if ((CurrLine.substr(0, 5) == "label"))
		return C_LABEL;
	else if ((CurrLine.substr(0, 4) == "goto"))
		return C_GOTO;
	else if ((CurrLine.substr(0, 2) == "if"))
		return C_IF;
	else if ((CurrLine.substr(0, 8) == "function"))
		return C_FUNCTION;
	else if ((CurrLine.substr(0, 6) == "return"))
		return C_RETURN;
	else if ((CurrLine.substr(0, 4) == "call"))
		return C_CALL;
}

string Parser::arg1(void)
{
	VMcommand ct = commandType();
	if (ct == C_ARITHMETIC)
	{
		int sp1 = CurrLine.find(" ",0);
		string a1 = CurrLine.substr(0,sp1);
		return a1;
	}
	else if (ct != C_RETURN)
	{
		int sp1 = CurrLine.find(" ", 0);
		int sp2 = CurrLine.find(" ", sp1 + 1);
		string a1 = CurrLine.substr(sp1 + 1, sp2 - sp1 - 1);
		return a1;
	}
}

int Parser::arg2(void)
{
	VMcommand ct = commandType();
	if (ct == C_PUSH || ct == C_POP || ct == C_FUNCTION || ct == C_CALL)
	{
		int sp1 = CurrLine.find(" ", 0);
		int sp2 = CurrLine.find(" ", sp1 + 1);
		int sp3 = CurrLine.find(" ", sp2 + 1);
		string a2 = CurrLine.substr(sp2 + 1, sp3 - sp2 - 1);
		int a2i = stoi(a2);
		return a2i;
	}
}

void Parser::setFileName(string filename)
{
	if(inf.is_open())
		inf.close();
	inf.open(filename.c_str());
}