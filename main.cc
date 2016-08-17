#include<iostream>
#include<string>
#include"Node.h"
#include"Scanner.h"
#include"Parser.h"

int main(int argc, char* argv[]){
	do{
		std::cout<<"> ";
		std::string buf;
		std::getline(std::cin,buf);
		std::cout<<buf<<std::endl;
		Scanner scanner(buf);
		Parser parser(scanner);
		parser.Parse();
		parser.Calculate();
	}while(1);
	return 0;
}
