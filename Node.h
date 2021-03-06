#ifndef _NODE_H_
#define _NODE_H_
#include<cassert>
#include<iostream>
#include<memory>
#include<vector>
#include"FunctionTable.h"

class Noncopyable{
	protected:
		Noncopyable(){}
		~Noncopyable(){}
	private:
		Noncopyable(const Noncopyable&);//实现禁止拷贝
		const Noncopyable& operator= (const Noncopyable&);
};

class Node:private Noncopyable{	//不是接口继承，而是实现继承
	public:
		virtual double Calc() const=0;
		virtual bool IsLvalue() const{
			return false;
		}
		virtual void Assign(double){
			assert(!"Assign called incorrectlly.");
		}
		virtual ~Node(){};
};

class NumberNode:public Node{
	public:
		NumberNode(double number):number_(number){};
		double Calc() const;
	private:
		double number_;
};

class BinaryNode:public Node{
	public:
		//BinaryNode(Node* left, Node* right):left_(left),right_(right){}
		BinaryNode(std::auto_ptr<Node>& left, std::auto_ptr<Node>& right):left_(left),right_(right){}
		~BinaryNode();
	protected:
		//Node* const left_;
		//Node* const right_;
		std::auto_ptr<Node> left_;
		std::auto_ptr<Node> right_;
};

class UnaryNode:public Node{
	public:
		//UnaryNode(Node* child):child_(child){}
		UnaryNode(std::auto_ptr<Node>& child):child_(child){}
		~UnaryNode();
	protected:
		//Node* const child_;
		std::auto_ptr<Node> child_;
};

class FunctionNode:public UnaryNode{
	public:
		//FunctionNode(Node* child, PtrFun pFun):UnaryNode(child), pFun_(pFun){}
		FunctionNode(std::auto_ptr<Node>& child, PtrFun pFun):UnaryNode(child), pFun_(pFun){}
		double Calc() const;
	private:
		PtrFun pFun_;
};

/*
class AddNode:public BinaryNode{
	public:
		AddNode(Node* left, Node* right):BinaryNode(left,right){}
		double Calc() const;
	private:
};

class SubNode:public BinaryNode{
	public:
		SubNode(Node* left, Node* right):BinaryNode(left, right){}
		double Calc() const;
};

class MultiplyNode:public BinaryNode{
	public:
		MultiplyNode(Node* left, Node* right):BinaryNode(left,right){}
		double Calc() const;
	private:
};

class DivideNode:public BinaryNode{
	public:
		DivideNode(Node* left, Node* right):BinaryNode(left, right){}
		double Calc() const;
};
*/
class UMinusNode:public UnaryNode{
	public:
		//UMinusNode(Node* child):UnaryNode(child){}
		UMinusNode(std::auto_ptr<Node> child):UnaryNode(child){}
		double Calc() const;
};

class MultipleNode:public Node{
	public:
		//MultipleNode(Node* node){
		MultipleNode(std::auto_ptr<Node>& node){
			AppendChild(node, true);
		}
		//void AppendChild(Node* node, bool positive){
		void AppendChild(std::auto_ptr<Node>& node, bool positive){
			childs_.push_back(node.release());
			positives_.push_back(positive);
		}
		~MultipleNode();
	protected:
		std::vector<Node*> childs_;
		std::vector<bool> positives_;
};

class SumNode:public MultipleNode{
	public:
		//SumNode(Node* node):MultipleNode(node){}
		SumNode(std::auto_ptr<Node>& node):MultipleNode(node){}
		double Calc() const;
};

class ProductNode:public MultipleNode{
	public:
		//ProductNode(Node* node):MultipleNode(node){}
		ProductNode(std::auto_ptr<Node>& node):MultipleNode(node){}
		double Calc() const;
};

class Storage;
class VariableNode: public Node{
	public:
		VariableNode(unsigned int id, Storage& storage):id_(id),storage_(storage){}
		double Calc() const;
		bool IsLvalue() const;
		void Assign(double val);
	private:
		const unsigned int id_;
		Storage& storage_;
};

class AssignNode:public BinaryNode{
	public:
		//AssignNode(Node* left, Node* right):BinaryNode(left,right){
		AssignNode(std::auto_ptr<Node>& left, std::auto_ptr<Node>& right):BinaryNode(left,right){
			assert(left_->IsLvalue());//引入只能指针之后，指针left的所有权在执行完会转移，如果继续使用left会导致运行时错误，因此这里需要使用left_
		}
		double Calc() const;
};
#endif	//_NODE_H_
