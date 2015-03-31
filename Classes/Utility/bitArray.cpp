#include "bitArray.h"
#include "LSLog.h"
bitArray::bitArray():byte_ary(NULL),byte_size(0),
read_byte_pos(0),bit_pos(0),_init(false)
{

}

bitArray::bitArray(bitArray* other):byte_ary(NULL),byte_size(0),
read_byte_pos(0),bit_pos(0)
{
	if(this->byte_ary == other->getByteArray())
	{
		return;
	}
	if(this->byte_ary != NULL)
		delete byte_ary;

	byte_ary = other->getByteArray();
	byte_size = other->byte_size;
	read_byte_pos = 0;
	bit_pos = 0;
	_init = true;
}
void bitArray::init(int i)
{
	if(_init)
		return;
	_init = true;
	byte_ary = new char[i];
}
bitArray::~bitArray()
{
	if(byte_ary != NULL)
	{
		delete[] byte_ary;
	}
	byte_ary = NULL;
}
void bitArray::write_bool(bool b )
{


	if(b)
		byte_ary[byte_size] |= (0x1<<bit_pos);
	else
		byte_ary[byte_size] &= ~(0x1<<bit_pos);

	++bit_pos;
	if(bit_pos >= 8)
	{
		++byte_size;
		bit_pos &= 0x7;
	}

	//return b;
}
void bitArray::write_int(int i,uint bits)
{
	if(bits > 32)
	{
		bits = 32;
	}

	int rest_bits = bits;
	for(; rest_bits > 0;)
	{
		int empty_bits = 8 - bit_pos;
		int to_fill_bits = empty_bits > rest_bits ? rest_bits : empty_bits;

		byte_ary[byte_size] = (byte_ary[byte_size] & ((0x1<<bit_pos) - 1)) | (((i >> (bits-rest_bits)) & ((0x1<<to_fill_bits) - 1))<<bit_pos);

		bit_pos += to_fill_bits;
		if(bit_pos >= 8)
		{
			++byte_size;
			bit_pos &= 0x7;
		}

		rest_bits -= to_fill_bits;
	}
}

void bitArray::write_str(std::string str)
{
	const char* t = str.c_str();

	int leng = strlen(str.c_str())+1;
	if(bit_pos > 0)
	{
		++byte_size;
		bit_pos = 0; // give up rest bits in current byte
	}

	write_char(byte_ary,t,byte_size,leng);

	byte_size += leng;
	byte_ary[byte_size-1] = '\0';//'\0'; // put /0
//	byte_size;
}

bool bitArray::read_bool()
{
	bool ret = bool(byte_ary[read_byte_pos] & (0x1<<bit_pos));

	++bit_pos;
	if(bit_pos >= 8)
	{
		++read_byte_pos;
		bit_pos &= 0x7;
	}

	return ret;
}
int bitArray::read_int(int bits)
{
	if(bits > 32)
	{
		bits = 32;
	}

	int ret = 0;
	int rest_bits = int(bits);
	for(; rest_bits > 0;)
	{
		int next_bits = 8 - bit_pos;
		int to_read_bits = next_bits > rest_bits ? rest_bits : next_bits;

		ret |= ((byte_ary[read_byte_pos] >> bit_pos) & ((0x1<<to_read_bits)-1)) << (bits-rest_bits);

		bit_pos += to_read_bits;
		if(bit_pos >= 8)
		{
			++read_byte_pos;
			bit_pos &= 0x7;
		}

		rest_bits -= to_read_bits;
	}

	return ret;
}
std::string bitArray::read_str()
{
	std::string ret;

	if(bit_pos > 0)
	{
		++read_byte_pos;
		bit_pos = 0; // give up rest bits in current byte
	}
	char* s = new char(100);
	read_char(s,byte_ary,read_byte_pos,'\0');

	ret = std::string(s);

	read_byte_pos += strlen(s)+1;

	return ret;
}
void bitArray::write_char(char* dest,const char* src,int pos,int len)
{
	for(int i=0;i<len;++i)
	{
		dest[pos++] = src[i];
	}
}
void bitArray::read_char(char* dest,const char* src,int pos,char flag)
{
	for(int i=0;i<100;++i)
	{
		char c = src[pos++];

		dest[i] = c;
		if(flag == c)
		{
			break;
		}
	}
}
bitArray::bitArray(unsigned char* b,ssize_t s):byte_ary(NULL),byte_size(0),
		read_byte_pos(0),bit_pos(0)
{
//todo err


    if (s > 0)
    {
    	LSLog::info("size:%d",s);

        byte_size = s;
        byte_ary =new char[byte_size];
        write_char(byte_ary,(const char*)b,0,byte_size);
    }
}
