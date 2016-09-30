#include<cstdio>
#include<cassert>
#include<iostream>
#include<memory>
#include<string>
#include"Calc.h"
#include"Parser.h"
#include"Scanner.h"
#include"Node.h"
#include"Exception.h"
//#include"DebugNew.h"

Parser::Parser(Scanner& scanner,Calc& calc):scanner_(scanner),calc_(calc),tree_(0),status_(STATUS_OK){

}

Parser::~Parser(){
	//delete tree_;
}

STATUS Parser::Parse(){
	//tree_=Expr();
	tree_=Expr();
	if(!scanner_.IsDone()){
		status_=STATUS_ERROR;
	}
	return status_;
}

//Node* Parser::Expr(){
std::auto_ptr<Node> Parser::Expr(){
	//Node* node=Term();
	std::auto_ptr<Node> node=Term();
	EToken token=scanner_.Token();
	/*
	if(token==TOKEN_PLUS){
		scanner_.Accept();
		Node* nodeRight=Expr();
		node= new AddNode(node,nodeRight);
	}else if(token==TOKEN_MINUS){
		scanner_.Accept();
		Node* nodeRight=Expr();
		node=new SubNode(node,nodeRight);
	}
	*/

	if(token==TOKEN_PLUS||token==TOKEN_MINUS){
		//Expr:=Term{('+'|'-')Term}
		//MultipleNode* multipleNode=new SumNode(node);
		std::auto_ptr<MultipleNode> multipleNode(new SumNode(node));
		do{
			scanner_.Accept();
			//Node* nextNode=Term();
			std::auto_ptr<Node> nextNode=Term();
			multipleNode->AppendChild(nextNode,(token==TOKEN_PLUS));
			token=scanner_.Token();
		}while(token==TOKEN_PLUS||token==TOKEN_MINUS);
		node=multipleNode;
	}else if(token==TOKEN_ASSIGN){
		//Expr:=Term=Expr
		scanner_.Accept();
		//Node* nodeRight=Expr();
		std::auto_ptr<Node> nodeRight=Expr();
		if(node->IsLvalue()){
			//node=new AssignNode(node, nodeRight);
			node=std::auto_ptr<Node>(new AssignNode(node, nodeRight));
		}else{
			status_=STATUS_ERROR;
			//std::cout<<"The left-hand side of an assignment must be a variable"<<std::endl;
			//Tod 抛出异常
			throw SyntaxError("lThe left-hand side of an assignment must be a variable");
		}
	}
	return node;
}

//Node* Parser::Term(){
std::auto_ptr<Node> Parser::Term(){
	//Node* node=Factor();
	std::auto_ptr<Node> node=Factor();
	EToken token=scanner_.Token();
	/*
	if(token==TOKEN_MULTIPLY){
		scanner_.Accept();
		Node* nodeRight=Term();
		node= new MultiplyNode(node,nodeRight);
	}else if(token==TOKEN_DIVIDE){
		scanner_.Accept();
		Node* nodeRight=Expr();
		node=new DivideNode(node,nodeRight);
	}
	*/

	if(token==TOKEN_MULTIPLY||token==TOKEN_DIVIDE){
		//Term:=Factor{('*'|'/')Factor}
		//MultipleNode* multipleNode=new ProductNode(node);
		std::auto_ptr<MultipleNode> multipleNode(new ProductNode(node));
		do{
			scanner_.Accept();
			//Node* nextNode=Factor();
			std::auto_ptr<Node> nextNode=Factor();
			multipleNode->AppendChild(nextNode,(token==TOKEN_MULTIPLY));
			token=scanner_.Token();
		}while(token==TOKEN_MULTIPLY||token==TOKEN_DIVIDE);
		node=multipleNode;
	}
	return node;
}

//Node* Parser::Factor(){
std::auto_ptr<Node> Parser::Factor(){
	//Node* node;
	std::auto_ptr<Node> node;
	EToken token=scanner_.Token();
	if(token==TOKEN_LPARENTHESIS){
		scanner_.Accept();	//accpet '('
		node=Expr();
		if(scanner_.Token()==TOKEN_RPARENTHESIS){
			scanner_.Accept();	//accept ')'
		}else{
			status_=STATUS_ERROR;
			//std::cout<<"missing parenthesis "<<std::endl;
			//Todo:抛出异常
			throw SyntaxError("missing parenthesis");
			//node=0;
		}
	}else if(token==TOKEN_NUMBER){
		//node=new NumberNode(scanner_.Number());
		node=std::auto_ptr<Node>(new NumberNode(scanner_.Number()));
		scanner_.Accept();
	}else if(token==TOKEN_IDENTIFIER){
		std::string symbol=scanner_.GetSymbol();
		unsigned int id=calc_.FindSymbol(symbol);
		scanner_.Accept();

		//解析函数
		//4+log(e*e)
		if(scanner_.Token()==TOKEN_LPARENTHESIS){
			scanner_.Accept();
			node=Expr();
			if(scanner_.Token()==TOKEN_RPARENTHESIS){
				scanner_.Accept();
				if(id!=SymbolTable::IDNOTFOUND && calc_.IsFunction(id)){
					//node=new FunctionNode(node,calc_.GetFunction(id));
					node=std::auto_ptr<Node>(new FunctionNode(node,calc_.GetFunction(id)));
				}else{
					status_=STATUS_ERROR;
					//std::cout<<"Unknow function"<<"\""<<symbol<<"\""<<std::endl;
					char buf[128]={0};
					sprintf(buf,"Unknow function \" %s \".",symbol.c_str());
					throw SyntaxError(buf);
					//node=0;
				}
			}else{
				status_=STATUS_ERROR;
				//std::cout<<"Missing parenthesis in a funciton call."<<std::endl;
				throw SyntaxError("Missing parenthesis in a funciton call.");
			}
		}else{
			if(id==SymbolTable::IDNOTFOUND){
				id=calc_.AddSymbol(symbol);
			}
			//node=new VariableNode(id,calc_.GetStorage());
			node=std::auto_ptr<Node>(new VariableNode(id,calc_.GetStorage()));

		}

	}else if(token==TOKEN_MINUS){
		scanner_.Accept();	//accept minus
		//node=new UMinusNode(Factor());
		node=std::auto_ptr<Node>(new UMinusNode(Factor()));
	}else{
		status_=STATUS_ERROR;
		//std::cout<<"not a valid expression"<<std::endl;
		//Todo:抛出异常
		throw SyntaxError("not a valid expression");
		//node=0;
	}
	return node;
}

double Parser::Calculate() const{
	//assert(tree_!=0);
	assert(tree_.get()!=0);
	return tree_->Calc();
}
