#ifndef _PARSER_H_
#define _PARSER_H_

#include<iostream>
#include<memory>

class Scanner;	//可以使用包含头文件的方式，不过这样会使得可执行文件变大
class Node;
class Calc;

enum STATUS{
	STATUS_OK,
	STATUS_ERROR,
	STATUS_QUIT
};

class Parser{
	public:
		Parser(Scanner& scanner, Calc& calc);
		~Parser();
		STATUS Parse();
		//Node* Expr();
		//Node* Term();
		//Node* Factor();
		std::auto_ptr<Node> Expr();
		std::auto_ptr<Node> Term();
		std::auto_ptr<Node> Factor();
		double Calculate() const;
	private:
		Scanner& scanner_;
		Calc& calc_;
		//Node* tree_; //表达式树
		std::auto_ptr<Node> tree_;
		STATUS status_;
};

#endif
