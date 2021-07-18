#ifndef _CODEWRITER_
#define _CODEWRITER_

#include <iostream>
#include <string>
#include <fstream>
#include "Parser.h"
using namespace std;

class CodeWriter
{
public:
	
	CodeWriter(string filename); 
	CodeWriter();
	~CodeWriter();
	void setFileName(string filename); 
	void WArithmetic(string command); 
	void WPushPop(VMcommand PushOrPop, string segment, int index);
	void WInit(void); 
	void WLabel(string label); 
	void WGoto(string label); 
	void WIf(string label); 
	void WCall(string functionName, int numArgs); 
	void WReturn(void); 
	void WFunction(string functionName, int numLocals); 
	void PopToGeneralPurposeRegister(int regNum); 
	void PushInPushOrPop(string loc, int i); 
	void PopInPushOrPop(string loc, int i); 
	void setOutputFileName(string outname); 
	
private:
	string FileName;
	string FunctionName;
	ofstream outf;
	int labelno;
	int line;
};

#endif
