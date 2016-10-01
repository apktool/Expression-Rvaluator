#ifndef _CALC_H_
#define _CALC_H_
#include"SymbolTable.h"
#include"Storage.h"
#include"FunctionTable.h"

class Parser;
class Calc{
	friend class Parser;
	public:
		Calc():funTbl_(symTbl_),storage_(symTbl_){}
		void ListFun() const;
		void ListVar() const;
	private:
		bool GetVariableValue(unsigned int id, double& val) const;
		Storage& GetStorage(){
			return storage_;
		}
		PtrFun GetFunction(unsigned int id) const{
			return funTbl_.GetFunction(id);
		}
		bool IsFunction(unsigned int id) const{
			return id<funTbl_.Size();
		}
		unsigned int AddSymbol(const std::string& str);
		unsigned int FindSymbol(const std::string& str) const;
		SymbolTable symTbl_;
		FunctionTable funTbl_;
		Storage storage_;
};

#endif //_CALC_H_
