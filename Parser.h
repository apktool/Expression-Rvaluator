#ifndef _PARSER_H_
#define _PARSER_H_

class Scanner;	//可以使用包含头文件的方式，不过这样会使得可执行文件变大
class Parser{
	public:
		Parser(Scanner& scanner);
		void Parse();
		double Calculate() const;
	private:
		Scanner& scanner_;
};

#endif
