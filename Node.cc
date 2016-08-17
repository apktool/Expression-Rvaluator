#include"Node.h"
#include<iostream>
#include<cmath>

double NumberNode::Calc() const{
	return number_;
}

BinaryNode::~BinaryNode(){
	delete left_;
	delete right_;
}

double AddNode::Calc() const{
	return left_->Calc()+right_->Calc();
}

double SubNode::Calc() const{
	return left_->Calc()-right_->Calc();
}

double MultiplyNode::Calc() const{
	return left_->Calc()*right_->Calc();
}

double DivideNode::Calc() const{
	double divisor=right_->Calc();
	if(divisor!=0.0){
		return left_->Calc()/divisor;
	}else{
		std::cout<<"Eorror: Divisor by zero"<<std::endl;
		return HUGE_VAL; //头文件<cmath>中定义的一个最大数
	}
}
