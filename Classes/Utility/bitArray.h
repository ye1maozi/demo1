#pragma once
#include "cocos2d.h"

typedef unsigned int uint;
class bitArray
{
public:
	bitArray();
	~bitArray();
	bitArray(bitArray* a);
	bitArray(unsigned char* v,ssize_t s);
	void write_bool(bool v);
	void write_int(int v,uint bit);
	void write_str(std::string s);

	bool read_bool();
	int read_int(int bits);
	std::string read_str();

	char* getByteArray()const{return byte_ary;};

	void init(int len);

	uint getSize(){return byte_size;};
private:
	void write_char(char* dest,const char* src,int pos,int len);
	void read_char(char* dest,const char* src,int pos,char flag);
	char* byte_ary;
	uint byte_size	;
	uint read_byte_pos	;
	uint bit_pos;
	bool _init;

};

