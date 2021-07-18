#include "CodeWriter.h"
#include <string>
#include <iostream>
#include <fstream>
#include <assert.h>
#include <bits/stdc++.h>
using namespace std;

CodeWriter::CodeWriter()
{
	labelno = 0;
	line = 0;
}
CodeWriter::CodeWriter(string FileName)
{
	labelno = 0;
	line = 0;
	FileName = FileName + ".asm";
	outf.open(FileName.c_str());
	if (!outf.is_open())
		cerr << "Could not open output file " << FileName << ".\n";
	WInit();
}

void CodeWriter::setFileName(string FileName)
{
	char Name_arr[100];
	strcpy(Name_arr, FileName.c_str());
	char *ptr = strrchr(Name_arr, '.');
	FileName = FileName.substr(0, ptr - Name_arr + 1);
	FileName = FileName + "asm";
	outf.open(FileName.c_str());
}

void CodeWriter::WArithmetic(string command)
{
	if (command == "add")
	{
		outf << "@SP" << endl
			 << "M=M-1" << endl
			 << "A=M" << endl
			 << "D=M" << endl
			 << "@SP" << endl
			 << "M=M-1" << endl
			 << "A=M" << endl
			 << "M=D+M" << endl
			 << "@SP" << endl
			 << "M=M+1" << endl;
	}
	else if (command == "sub")
	{
		outf << "@SP" << endl
			 << "M=M-1" << endl
			 << "A=M" << endl
			 << "D=M" << endl
			 << "@SP" << endl
			 << "M=M-1" << endl
			 << "A=M" << endl
			 << "M=M-D" << endl
			 << "@SP" << endl
			 << "M=M+1" << endl;
	}
	else if (command == "and")
	{
		outf << "@SP" << endl
			 << "M=M-1" << endl
			 << "A=M" << endl
			 << "D=M" << endl
			 << "@SP" << endl
			 << "M=M-1" << endl
			 << "A=M" << endl
			 << "M=D&M" << endl
			 << "@SP" << endl
			 << "M=M+1" << endl;
	}
	else if (command == "or")
	{
		outf << "@SP" << endl
			 << "M=M-1" << endl
			 << "A=M" << endl
			 << "D=M" << endl
			 << "@SP" << endl
			 << "M=M-1" << endl
			 << "A=M" << endl
			 << "M=D|M" << endl
			 << "@SP" << endl
			 << "M=M+1" << endl;
	}
	else if (command == "neg")
	{
		outf << "D=0" << endl
			 << "@SP" << endl
			 << "A=M-1" << endl
			 << "M=D-M" << endl;
	}
	else if (command == "not")
	{
		outf << "@SP" << endl
			 << "A=M-1" << endl
			 << "M=!M" << endl;
	}
	else if (command == "gt")
	{
		outf << "@SP" << endl
			 << "M=M-1" << endl
			 << "A=M" << endl
			 << "D=M" << endl
			 << "@SP" << endl
			 << "M=M-1" << endl
			 << "A=M" << endl
			 << "D=D-M" << endl
			 << "@IF" << labelno << endl
			 << "D;JLT" << endl
			 << "@SP" << endl
			 << "A=M" << endl
			 << "M=0" << endl
			 << "@END" + labelno << endl
			 << "0;JMP" << endl
			 << "(IF" + labelno << ")" << endl
			 << "@SP" << endl
			 << "A=M" << endl
			 << "M=-1" << endl
			 << "(END" + labelno << ")" << endl
			 << "@SP" << endl
			 << "M=M+1" << endl;
		labelno++;
	}
	else if (command == "lt")
	{
		outf << "@SP" << endl
			 << "M=M-1" << endl
			 << "A=M" << endl
			 << "D=M" << endl
			 << "@SP" << endl
			 << "M=M-1" << endl
			 << "A=M" << endl
			 << "D=D-M" << endl
			 << "@IF" << labelno << endl
			 << "D;JGT" << endl
			 << "@SP" << endl
			 << "A=M" << endl
			 << "M=0" << endl
			 << "@END" + labelno << endl
			 << "0;JMP" << endl
			 << "(IF" + labelno << ")" << endl
			 << "@SP" << endl
			 << "A=M" << endl
			 << "M=-1" << endl
			 << "(END" + labelno << ")" << endl
			 << "@SP" << endl
			 << "M=M+1" << endl;
		labelno++;
	}
	else if (command == "eq")
	{
		outf << "@SP" << endl
			 << "M=M-1" << endl
			 << "A=M" << endl
			 << "D=M" << endl
			 << "@SP" << endl
			 << "M=M-1" << endl
			 << "A=M" << endl
			 << "D=D-M" << endl
			 << "@IF" << labelno << endl
			 << "D;JEQ" << endl
			 << "@SP" << endl
			 << "A=M" << endl
			 << "M=0" << endl
			 << "@END" + labelno << endl
			 << "0;JMP" << endl
			 << "(IF" + labelno << ")" << endl
			 << "@SP" << endl
			 << "A=M" << endl
			 << "M=-1" << endl
			 << "(END" + labelno << ")" << endl
			 << "@SP" << endl
			 << "M=M+1" << endl;
		labelno++;
	}
}

void CodeWriter::WPushPop(VMcommand PushOrPop, string segment, int index)
{
	if (PushOrPop == C_PUSH)
	{
		if (segment == "constant")
		{
			outf << "// push " << segment + " " << index << endl;
			outf << "@" << index << endl
				 << "D=A" << endl
				 << "@SP" << endl
				 << "A=M" << endl
				 << "M=D" << endl
				 << "@SP" << endl
				 << "M=M+1" << endl;
		}
		else if (segment == "local")
		{
			PushInPushOrPop("LCL", index);
		}
		else if (segment == "argument")
		{
			PushInPushOrPop("ARG", index);
		}
		else if (segment == "this")
		{
			PushInPushOrPop("THIS", index);
		}
		else if (segment == "that")
		{
			PushInPushOrPop("THAT", index);
		}
		else if (segment == "pointer")
		{
			PushInPushOrPop("3", index);
		}
		else if (segment == "temp")
		{
			PushInPushOrPop("5", index);
		}
		else if (segment == "static")
		{
			outf << "@" << FileName << "." << index << endl
				 << "D=M" << endl
				 << "@SP" << endl
				 << "A=M" << endl
				 << "M=D" << endl
				 << "@SP" << endl
				 << "M=M+1" << endl;
		}
	}
	else if (PushOrPop == C_POP)
	{
		if (segment == "local")
		{
			PopInPushOrPop("LCL", index);
		}
		else if (segment == "argument")
		{
			PopInPushOrPop("ARG", index);
		}
		else if (segment == "this")
		{
			PopInPushOrPop("THIS", index);
		}
		else if (segment == "that")
		{
			PopInPushOrPop("THAT", index);
		}
		else if (segment == "pointer")
		{
			PopInPushOrPop("3", index);
		}
		else if (segment == "temp")
		{
			PopInPushOrPop("5", index);
		}
		else if (segment == "static")
		{
			outf << "@" << FileName << "." << index << endl
				 << "D=A" << endl
				 << "@R13" << endl
				 << "M=D" << endl
				 << "@SP" << endl
				 << "M=M-1" << endl
				 << "A=M" << endl
				 << "D=M" << endl
				 << "@R13" << endl
				 << "A=M" << endl
				 << "M=D" << endl;
		}
	}
}

void CodeWriter::PopToGeneralPurposeRegister(int regNum)
{
	assert(regNum >= 13 && regNum <= 15);
	outf << "@" << regNum << endl
		 << "M=D" << endl;
}

void CodeWriter::WInit(void)
{
	outf << "//init"
		 << "@256" << endl
		 << "D=A" << endl
		 << "@SP" << endl
		 << "M=D" << endl;
	WCall("Sys.init", 0);
}

void CodeWriter::PushInPushOrPop(string loc, int i)
{
	if (loc == "3" || loc == "5")
	{
		outf << "@" << loc << endl
			 << "D=A" << endl
			 << "@" << i << endl
			 << "A=D+A" << endl
			 << "D=M" << endl
			 << "@SP" << endl
			 << "A=M" << endl
			 << "M=D" << endl
			 << "@SP" << endl
			 << "M=M+1" << endl;
	}
	else
	{
		outf << "@" << loc << endl
			 << "D=M" << endl
			 << "@" << i << endl
			 << "A=D+A" << endl
			 << "D=M" << endl
			 << "@SP" << endl
			 << "A=M" << endl
			 << "M=D" << endl
			 << "@SP" << endl
			 << "M=M+1" << endl;
	}
}

void CodeWriter::PopInPushOrPop(string loc, int i)
{
	if (loc == "3" || loc == "5")
	{
		outf << "@" << loc << endl
			 << "D=A" << endl
			 << "@" << i << endl
			 << "D=D+A" << endl;
		PopToGeneralPurposeRegister(13);
		outf << "@SP" << endl
			 << "M=M-1"
			 << "A=M" << endl
			 << "D=M" << endl
			 << "@R13" << endl
			 << "A=M" << endl
			 << "M=D" << endl;
	}
	else
	{
		outf << "@" << loc << endl
			 << "D=M" << endl
			 << "@" << i << endl
			 << "D=D+A" << endl;
		PopToGeneralPurposeRegister(13);
		outf << "@SP" << endl
			 << "M=M-1"
			 << "A=M" << endl
			 << "D=M" << endl
			 << "@R13" << endl
			 << "A=M" << endl
			 << "M=D" << endl;
	}
}

void CodeWriter::WLabel(string label)
{
	outf << "// label" << label << endl;
	outf << "(" << label << ")" << endl;
}

void CodeWriter::WGoto(string label)
{

	outf << "// goto " << label << endl;
	outf << "@" << label << endl;
	outf << "0;JMP" << endl;
}

void CodeWriter::WIf(string label)
{
	outf << "// if-goto" << label << endl;
	outf << "@SP" << endl
		 << "M=M-1" << endl
		 << "A=M" << endl
		 << "D=M" << endl
		 << "@" << label << endl
		 << "D;JNE" << endl;
}

void CodeWriter::WCall(string FunctionName, int numArgs)
{
	outf << "// Call " << FunctionName << " " << numArgs << endl;
	outf << "@RETURN" << labelno << endl
		 << "D=A" << endl
		 << "@SP" << endl
		 << "A=M" << endl
		 << "M=D" << endl
		 << "@SP" << endl
		 << "M=M+1" << endl
		 << "@LCL" << endl
		 << "D=M" << endl
		 << "@SP" << endl
		 << "A=M" << endl
		 << "M=D" << endl
		 << "@SP" << endl
		 << "M=M+1" << endl
		 << "@ARG" << endl
		 << "D=M" << endl
		 << "@SP" << endl
		 << "A=M" << endl
		 << "M=D" << endl
		 << "@SP" << endl
		 << "M=M+1" << endl
		 << "@THIS" << endl
		 << "D=M" << endl
		 << "@SP" << endl
		 << "A=M" << endl
		 << "M=D" << endl
		 << "@SP" << endl
		 << "M=M+1" << endl
		 << "@THAT" << endl
		 << "D=M" << endl
		 << "@SP" << endl
		 << "A=M" << endl
		 << "M=D" << endl
		 << "@SP" << endl
		 << "M=M+1" << endl
		 << "@" << numArgs << endl
		 << "D=A" << endl
		 << "@SP" << endl
		 << "D=M-D" << endl
		 << "@5" << endl
		 << "D=D-A" << endl
		 << "@ARG" << endl
		 << "M=D" << endl
		 << "@SP" << endl
		 << "D=M" << endl
		 << "@LCL" << endl
		 << "M=D" << endl
		 << "@" << FunctionName << endl
		 << "0;JMP" << endl
		 << "(RETURN" << labelno << ")" << endl;
	labelno++;
}

void CodeWriter::WReturn(void)
{
	outf << "@LCL" << endl
		 << "D=M" << endl
		 << "@FRAME" << endl
		 << "M=D" << endl
		 << "@5" << endl
		 << "D=A" << endl
		 << "@FRAME" << endl
		 << "A=M-D" << endl
		 << "D=M" << endl
		 << "@RET" << endl
		 << "M=D" << endl
		 << "@SP" << endl
		 << "M=M-1"
		 << "A=M" << endl
		 << "D=M" << endl
		 << "@ARG" << endl
		 << "A=M" << endl
		 << "M=D" << endl
		 << "@ARG" << endl
		 << "D=M+1" << endl
		 << "@SP" << endl
		 << "M=D" << endl
		 << "@FRAME" << endl
		 << "A=M-1" << endl
		 << "D=M" << endl
		 << "@THAT" << endl
		 << "M=D" << endl
		 << "@2" << endl
		 << "D=A" << endl
		 << "@FRAME" << endl
		 << "A=M-D" << endl
		 << "D=M" << endl
		 << "@THIS" << endl
		 << "M=D" << endl
		 << "@3" << endl
		 << "D=A" << endl
		 << "@FRAME" << endl
		 << "A=M-D" << endl
		 << "D=M" << endl
		 << "@ARG" << endl
		 << "M=D" << endl
		 << "@4" << endl
		 << "D=A" << endl
		 << "@FRAME" << endl
		 << "A=M-D" << endl
		 << "D=M" << endl
		 << "@LCL" << endl
		 << "M=D" << endl
		 << "@RET" << endl
		 << "A=M" << endl
		 << "0;JMP" << endl;
}

void CodeWriter::WFunction(string FunctionName, int numLocals)
{
	FunctionName = FunctionName;
	outf << "(" << FunctionName << ")" << endl;
	for (int i = 0; i < numLocals; i++)
		WPushPop(C_PUSH, "constant", 0);
}

void CodeWriter::setOutputFileName(string outname)
{
	FileName = outname;
	outname = outname + ".asm";
	outf.open(outname.c_str());
	WInit();
	line++;
}
CodeWriter::~CodeWriter()
{
	if (outf.is_open())
		outf.close();
}