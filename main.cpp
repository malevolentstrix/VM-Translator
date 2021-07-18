#include <iostream>
#include <string>
#include "Parser.h"
#include "CodeWriter.h"
#include "Parser.cpp"
#include "CodeWriter.cpp"
#include <boost/algorithm/string.hpp>
using namespace std;

int main()
{
	char filename[100];
	CodeWriter CodewriterObj;
	Parser ParserObj;
	string Name, OutFile;
	cout << "Enter the File/Directory Name: ";
	getline(cin, Name);
	strcpy(filename, Name.c_str());
	string Extension = (Name.substr(Name.length() - 3));
	if (boost::iequals(Extension, ".vm") == true)
	{
		ParserObj.setFileName(filename);
		CodewriterObj.setFileName(filename);
	}
	else
	{
		CodewriterObj.setOutputFileName(filename);
	}
	while (ParserObj.hasMoreCommands())
	{
		ParserObj.advance();
		if (ParserObj.commandType() == C_ARITHMETIC)
		{
			CodewriterObj.WArithmetic(ParserObj.arg1());
		}
		else if (ParserObj.commandType() == C_POP)
		{
			CodewriterObj.WPushPop(C_POP, ParserObj.arg1(), ParserObj.arg2());
		}
		else if (ParserObj.commandType() == C_PUSH)
		{
			CodewriterObj.WPushPop(C_PUSH, ParserObj.arg1(), ParserObj.arg2());
		}
		else if (ParserObj.commandType() == C_LABEL)
		{
			CodewriterObj.WLabel(ParserObj.arg1());
		}
		else if (ParserObj.commandType() == C_GOTO)
		{
			CodewriterObj.WGoto(ParserObj.arg1());
		}
		else if (ParserObj.commandType() == C_IF)
		{
			CodewriterObj.WIf(ParserObj.arg1());
		}
		else if (ParserObj.commandType() == C_FUNCTION)
		{
			CodewriterObj.WFunction(ParserObj.arg1(), ParserObj.arg2());
		}
		else if (ParserObj.commandType() == C_RETURN)
		{
			CodewriterObj.WReturn();
		}
		else if (ParserObj.commandType() == C_CALL)
		{
			CodewriterObj.WCall(ParserObj.arg1(), ParserObj.arg2());
		}
	}
}
