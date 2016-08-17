#ifndef _NODE_H_
#define _NODE_H_

class Node{
	public:
		virtual double Calc() const=0;
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
		BinaryNode(Node* left, Node* right):left_(left),right_(right){}
		~BinaryNode();
	protected:
		Node* const left_;
		Node* const right_;
};

class UnaryNode:public Node{
	public:
		UnaryNode(Node* child):child_(child){}
		~UnaryNode();
	protected:
		Node* const child_;
};

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

class UMinusNode:public UnaryNode{
	public:
		UMinusNode(Node* child):UnaryNode(child){}
		double Calc() const;
};

#endif	//_NODE_H_

/*
 * 虚基类中，基类指针指向派生类对象，如果析构函数不声明为虚函数的话，会导致通过基类指针释放派生类对象时出错。
 * 比如：
 * Node* p=new AddNode
 * delete p;
 *
 * 如果不使用虚析构函数的话，会导致AddNode类中的析构函数没办法执行。
 * 即只会执行基类的析构函数，而不会执行派生类的析构函数
 */
