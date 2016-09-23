#ifndef _PARSER_H_
#define _PARSER_H_

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
		STATUS Parse();
		Node* Expr();
		Node* Term();
		Node* Factor();
		double Calculate() const;
	private:
		Scanner& scanner_;
		Calc& calc_;
		Node* tree_; //表达式树
		STATUS status_;
};

#endif
