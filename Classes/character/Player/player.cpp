#include "player.h"


player::player(void)
{
}


player::~player(void)
{
}

player* player::create(const std::string& str)
{
	player* p = new player();
	if(p && p->init(str))
	{
		p->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(p);
	}

	return p;
}

bool player::init(const std::string& str)
{
	BasicChar::init(str);
	type = PlayerType::PLAYER_SELF;
	return true;
}