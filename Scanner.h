#ifndef _SCANNER_H_
#define _SCANNER_H_
#include<string>
#include<iostream>

enum EToken{
	TOKEN_COMMAND,
	TOKEN_END,
	TOKEN_ERROR,
	TOKEN_NUMBER,
	TOKEN_PLUS,
	TOKEN_MINUS,
	TOKEN_MULTIPLY,
	TOKEN_DIVIDE,
	TOKEN_LPARENTHESIS,
	TOKEN_RPARENTHESIS,
	TOKEN_IDENTIFIER,
	TOKEN_ASSIGN
};

class Scanner{
	public:
		//Scanner(const std::string& buf);
		Scanner(std::istream& in);
		
		void Accept();
		void AcceptCommand();
		bool IsEmpty() const;
		bool IsDone() const;
		bool IsCommand() const;
		double Number() const;
		std::string GetSymbol() const;
		EToken Token() const;
	private:
		void ReadChar();
		//void SkipWhite();//被ReadChar所替换
		//const std::string buf_;
		std::istream& in_;
		int look_;
		//unsigned int curPos_;
		EToken token_;
		double number_;
		std::string symbol_;
		bool IsEmpty_;
};

#endif //_SCANNER_H_
