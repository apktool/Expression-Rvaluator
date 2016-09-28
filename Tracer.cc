#include<cstdlib>
#include<iostream>
#include"Tracer.h"

bool Tracer::Ready=false;

Tracer::Tracer():lockCount_(0){
	Ready=true;
}

Tracer::~Tracer(){
	Ready=false;
	Dump();
}


void Tracer::Add(void* p, const char* file, long line){
	if(lockCount_>0){
		return;
	}
	//lock();
	Tracer::Lock Lock(*this);	//局部对象析构函数调用的确定性，因此该对象销毁时会调用析构函数，完成解锁
	mapEntry_[p]=Entry(file,line);
	//unLock();
}

void Tracer::Remove(void* p){
	if(lockCount_>0){
		return;
	}
	//lock();
	Tracer::Lock Lock(*this);
	std::map<void*, Entry>::iterator it;
	it=mapEntry_.find(p);
	if(it!=mapEntry_.end()){
		mapEntry_.erase(it);
	}
	//unLock();
}

void Tracer::Dump(){
	if(mapEntry_.size()>0){
		std::cout<<"*** Memory leak(s):"<<std::endl;
		std::map<void*, Entry>::iterator it;
		for(it=mapEntry_.begin();it!=mapEntry_.end();++it){
			const char* file=it->second.File();
			long line=it->second.Line();
			//int addr=reinterpret_cast<int>(it->first);
			long addr=reinterpret_cast<long>(it->first);
			std::cout<<"0x"<<std::hex<<addr<<": "<<file<<"| "<<std::dec<<line<<std::endl;
		}
		std::cout<<std::endl;
	}
}

Tracer NewTrace;

void* operator new(size_t size){
	void* p=malloc(size);
	if(Tracer::Ready){
		NewTrace.Add(p,"?",0);
	}
	return p;
}

void operator delete(void* p) noexcept{
	if(Tracer::Ready){
		NewTrace.Remove(p);
	}
	free(p);
}

void* operator new(size_t size, const char* file, long line){
	void* p=malloc(size);
	if(Tracer::Ready){
		NewTrace.Add(p,file,line);
	}
	return p;
}

void operator delete(void* p, const char*, long) noexcept{
	if(Tracer::Ready){
		NewTrace.Remove(p);
	}
	free(p);
}

void* operator new[](size_t size){
	void* p=malloc(size);
	if(Tracer::Ready){
		NewTrace.Add(p,"?",0);
	}
	return p;
}

void operator delete[](void* p) noexcept{
	if(Tracer::Ready){
		NewTrace.Remove(p);
	}
	free(p);
}

void* operator new[](size_t size, const char* file, long line){
	void* p=malloc(size);
	if(Tracer::Ready){
		NewTrace.Add(p,file,line);
	}
	return p;
}

void operator delete[](void* p, const char*, long) noexcept{
	if(Tracer::Ready){
		NewTrace.Remove(p);
	}
	free(p);
}
