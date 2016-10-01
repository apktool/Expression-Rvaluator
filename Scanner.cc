#include<cstdio>
#include<cstdlib>
#include<iostream>
#include"Scanner.h"

/*
Scanner::Scanner(const std::string& buf):buf_(buf),curPos_(0){
	Accept();
	IsEmpty_=(token_==TOKEN_END);
}
*/

Scanner::Scanner(std::istream& in):in_(in){
	Accept();
	IsEmpty_=(token_==TOKEN_END);
}

bool Scanner::IsEmpty() const{
	return IsEmpty_;
}

bool Scanner::IsDone() const{
	return 	token_==TOKEN_END;
}

double Scanner::Number() const{
	return number_;
}

std::string Scanner::GetSymbol() const{
	return symbol_;
}

EToken Scanner::Token() const{
	return token_;
}

/*
void Scanner::SkipWhite(){
	while(isspace(buf_[curPos_])){
		++curPos_;
	}
}
*/
void Scanner::ReadChar(){
	look_=in_.get();
	while(look_==' '||look_=='\t'){
		look_=in_.get();
	}
}

/*
void Scanner::Accept(){
	SkipWhite();
	switch(buf_[curPos_]){
		case '+':
			token_=TOKEN_PLUS;
			++curPos_;
			break;
		case '-':
			token_=TOKEN_MINUS;
			++curPos_;
			break;
		case '*':
			token_=TOKEN_MULTIPLY;
			++curPos_;
			break;
		case '/':
			token_=TOKEN_DIVIDE;
			++curPos_;
			break;
		case '(':
			token_=TOKEN_LPARENTHESIS;
			++curPos_;
			break;
		case ')':
			token_=TOKEN_RPARENTHESIS;
			++curPos_;
			break;
		case '=':
			token_=TOKEN_ASSIGN;
			++curPos_;
			break;
		case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': case '.':
			token_=TOKEN_NUMBER;
			char* p;
			number_=strtod(&buf_[curPos_],&p);	//字符型转double
			curPos_=p-&buf_[0];
			break;
		case '\0': case '\n': case '\r': case EOF:
			token_=TOKEN_END;
			break;
		default:
			if(isalpha(buf_[curPos_])||buf_[curPos_]=='_'){	//如果以字母或者下划线开头的，则表示标识符合法
				token_=TOKEN_IDENTIFIER;
				symbol_.erase();
				char ch=buf_[curPos_];
				do{
					symbol_+=ch;
					++curPos_;
					ch=buf_[curPos_];
				}while(isalnum(ch)||ch=='_');
			}else{
				token_=TOKEN_ERROR;
			}
			break;
	}
}
*/
void Scanner::Accept(){
	ReadChar();
	switch(look_){
		case '+':
			token_=TOKEN_PLUS;
			break;
		case '-':
			token_=TOKEN_MINUS;
			break;
		case '*':
			token_=TOKEN_MULTIPLY;
			break;
		case '/':
			token_=TOKEN_DIVIDE;
			break;
		case '(':
			token_=TOKEN_LPARENTHESIS;
			break;
		case ')':
			token_=TOKEN_RPARENTHESIS;
			break;
		case '=':
			token_=TOKEN_ASSIGN;
			break;
		case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': case '.':
			token_=TOKEN_NUMBER;
			in_.putback(look_);
			in_>>number_;
			break;
		case '\0': case '\n': case '\r': case EOF:
			token_=TOKEN_END;
			break;
		default:
			if(isalpha(look_)||look_=='_'){	//如果以字母或者下划线开头的，则表示标识符合法
				token_=TOKEN_IDENTIFIER;
				symbol_.erase();
				do{
					symbol_+=look_;
					look_=in_.get();
				}while(isalnum(look_)||look_=='_');
				in_.putback(look_);//会多获取一个字符，因此将该字符归还至流中，避免影响下次解析
			}else{
				token_=TOKEN_ERROR;
			}
			break;
	}
}
