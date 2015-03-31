#pragma once
#include "../BasicChar.h"
class player:public BasicChar
{
public:
	player(void);
	~player(void);

	//CREATE_FUNC(player);
	static player* create(const std::string& str);
protected:
	bool init(const std::string& str);
};

