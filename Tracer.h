#ifndef _TRACER_H_
#define _TRACER_H_

#include<map>

void* operator new(size_t size);
void* operator new(size_t size, const char* file, long line);
void* operator new[](size_t size, const char* file, long line);
void* operator new[](size_t size);
void operator delete(void* p) noexcept;
void operator delete(void* p, const char*, long) noexcept;
void operator delete[](void* p, const char*, long) noexcept;
void operator delete[](void* p) noexcept;


class Tracer{
	public:
		Tracer();
		~Tracer();

		static bool Ready;

		void Add(void* p, const char* file, long line);
		void Remove(void* p);
		void Dump();
	private:
		class Entry{
			public:
				Entry(const char* file=0, long line=0):file_(file),line_(line){}
				const char* File() const{
					return file_;
				}
				long Line() const{
					return line_;
				}
			private:
				const char* file_;
				long line_;
		};
		class Lock{
			public:
				Lock(Tracer& tracer):tracer_(tracer){
					tracer.lock();
				}
				~Lock(){
					tracer_.unLock();
				}
			private:
				Tracer& tracer_;

		};
		friend class Lock;
	private:
		std::map<void*, Entry> mapEntry_;
		int lockCount_;
		void lock(){
			++lockCount_;
		}
		void unLock(){
			--lockCount_;
		}
};

extern Tracer NewTrace;
#endif //_TRACER_H_

/*
 * 友元函数破坏了封装性，但是它提高了效率；
 * 友元类提高了类的封装性
 */
