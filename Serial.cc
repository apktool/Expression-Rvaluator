#include<fstream>
#include<string>
#include"Serial.h"
#include"Exception.h"

const int TruePattern=0x1;
const int FalsePattern=0x0;

//========================Serializer================================//
Serializer::Serializer(const std::string& fileName):stream_(fileName.c_str(),std::ofstream::out | std::ofstream::binary){
	if(!stream_){
		throw FileStreamError("Couldn't open file");
	}
}

Serializer& Serializer::Put(int x){
	stream_.write(reinterpret_cast<char*>(&x),sizeof(int));
	if(stream_.bad()){
		throw FileStreamError("Write file failed.");
	}
	return *this;
}
Serializer& Serializer::Put(unsigned int x){
	stream_.write(reinterpret_cast<char*>(&x),sizeof(unsigned int));
	if(stream_.bad()){
		throw FileStreamError("Write file failed.");
	}
	return *this;
}

Serializer& Serializer::Put(long x){
	stream_.write(reinterpret_cast<char*>(&x),sizeof(long));
	if(stream_.bad()){
		throw FileStreamError("Write file failed.");
	}
	return *this;
}

Serializer& Serializer::Put(unsigned long x){
	stream_.write(reinterpret_cast<char*>(&x),sizeof(unsigned long));
	if(stream_.bad()){
		throw FileStreamError("Write file failed.");
	}
	return *this;
}

Serializer& Serializer::Put(const std::string x){
	int len=x.length();
	Put(len);
	stream_.write(x.data(),x.length());
	if(stream_.bad()){
		throw FileStreamError("Write file failed.");
	}
	return *this;
}

Serializer& Serializer::Put(bool x){
	int n=x?TruePattern:FalsePattern;
	Put(n);
	return *this;
}

Serializer& Serializer::operator<< (int x){
	return Put(x);
}

Serializer& Serializer::operator<< (unsigned int x){
	return Put(x);

}

Serializer& Serializer::operator<< (long x){
	return Put(x);

}

Serializer& Serializer::operator<< (unsigned long x){
	return Put(x);
}

Serializer& Serializer::operator<< (const std::string x){
	return Put(x);
}

Serializer& Serializer::operator<< (bool x){
	return Put(x);
}

//========================DeSerializer================================//

DeSerializer::DeSerializer(const std::string& fileName):stream_(fileName.c_str(),std::ofstream::out | std::ofstream::binary){
	if(!stream_){
		throw FileStreamError("Couldn't open file");
	}
}

DeSerializer& DeSerializer::Get(int& x){
	if(stream_.eof()){
		throw FileStreamError("Unexpected end of fiile.");//为了避免已经读到末尾了还继续读取的错误
	}
	stream_.read(reinterpret_cast<char*>(&x),sizeof(int));
	if(stream_.bad()){
		throw FileStreamError("Read file failed.");
	}
	return *this;
}

DeSerializer& DeSerializer::Get(unsigned int& x){
	stream_.read(reinterpret_cast<char*>(&x),sizeof(unsigned int));
	if(stream_.bad()){
		throw FileStreamError("Read file failed.");
	}
	return *this;
}

DeSerializer& DeSerializer::Get(long& x){
	stream_.read(reinterpret_cast<char*>(&x),sizeof(long));
	if(stream_.bad()){
		throw FileStreamError("Read file failed.");
	}
	return *this;
}

DeSerializer& DeSerializer::Get(unsigned long& x){
	stream_.read(reinterpret_cast<char*>(&x),sizeof(unsigned long));
	if(stream_.bad()){
		throw FileStreamError("Write file failed.");
	}
	return *this;
}

DeSerializer& DeSerializer::Get(std::string& x){
	int len;
	Get(len);
	if(stream_.eof()){
		throw FileStreamError("Unexpected end of fiile.");//为了避免已经读到末尾了还继续读取的错误
	}
	x.resize(len);
	stream_.read(&x[0],len);
	if(stream_.bad()){
		throw FileStreamError("Read file failed.");
	}
	return *this;
}

DeSerializer& DeSerializer::Get(bool& x){
	int n;
	Get(n);
	if(n==TruePattern){
		x=true;
	}else if(n==FalsePattern){
		x=false;
	}else{
		throw  CheckNumberError("Data error.");
	}
	return *this;
}

DeSerializer& DeSerializer::operator>> (int& x){
	return Get(x);
}

DeSerializer& DeSerializer::operator>> (unsigned int& x){
	return Get(x);

}

DeSerializer& DeSerializer::operator>> (long& x){
	return Get(x);

}

DeSerializer& DeSerializer::operator>> (unsigned long& x){
	return Get(x);
}

DeSerializer& DeSerializer::operator>> (std::string& x){
	return Get(x);
}

DeSerializer& DeSerializer::operator>> (bool& x){
	return Get(x);
}

//========================DeDeSerializer================================//
