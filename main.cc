#include<iostream>
#include<string>
#include"Node.h"
#include"Scanner.h"
#include"Parser.h"
#include"Calc.h"
#include"Exception.h"

int main(int argc, char* argv[]){
	Calc calc;
	STATUS status=STATUS_OK;
	do{
		std::cout<<"> ";
		std::string buf;
		std::getline(std::cin,buf);
		//std::cout<<buf<<std::endl;
		Scanner scanner(buf);
		if(!scanner.IsEmpty()){
			Parser parser(scanner,calc);

			try{
				status=parser.Parse();
				if(status==STATUS_OK){	//此处可以不需要判定，属于C语言的思想
					std::cout<<parser.Calculate()<<std::endl;
				}
			}catch(SyntaxError& se){
				std::cout<<se.what()<<std::endl;
				std::cout<<se.StackTrace()<<std::endl;	//栈回溯
			}catch(Exception& e){
				std::cout<<e.what()<<std::endl;
			}catch(...){
				std::cout<<"Internal error."<<std::endl;
			}

			/*
			if(status==STATUS_OK){
				std::cout<<parser.Calculate()<<std::endl;
			}else{
				std::cout<<"Syntax Error."<<std::endl;
			}*/
		}else{
			std::cout<<"Expression is empty"<<std::endl;
		}
	}while(status!=STATUS_QUIT);
	return 0;
}
