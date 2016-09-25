//异常处理
#ifndef _EXCEPTION_H_
#define _EXCEPTION_H_

#include<exception>
#include<string>

class Exception:public std::exception{
	public:
		explicit Exception(const char* message):message_(message){
			FillStackTrace();	//将栈信息写入
		}
		virtual ~Exception() throw(){	//不抛出异常

		}
		virtual const char* what() const throw();	//不抛出异常
		const char* StackTrace() const throw();

	private:
		void FillStackTrace();
		std::string message_;	
		std::string stackTrace_;	//抛出异常时，打印错误位置信息
};

class SyntaxError:public Exception{
	public:
		explicit SyntaxError(const char* message):Exception(message){

		}
		virtual ~SyntaxError() throw(){

		}
};

#endif //_EXCEPTION_H_
