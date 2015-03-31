#pragma once
#include "../BasicChar.h"

class AIplayer :
	public BasicChar
{
public:
	AIplayer(void);
	~AIplayer(void);

	void Attack();
	static AIplayer* create(const std::string& str);
//	bool init(const std::string& str);
protected:
	bool init(const std::string& str);
};

