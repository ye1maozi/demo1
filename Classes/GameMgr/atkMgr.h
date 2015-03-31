#pragma once
#include "character/BasicChar.h"
class atkMgr //;public Ref
{
public:
	enum SkillType
	{
		SKILL_ATK = 0,
		SKILL_DEF = 1,
		SKILL_HEL = 2,
	};
	static atkMgr* getInstance();

	bool PlayerAttack(BasicChar* cha,int sklid);

	void setAttackback(const std::function<void()> &func){_function = func;};

	void clearAll();
private:
	bool init();

	void dealAttack();
	static atkMgr* _instance;
	
	int playerNum;
	ValueVector playerList;

	Map<std::string,BasicChar*> nameToChar;

	//Vector<BasicChar*> AiPlayerList;
	std::function<void()> _function;
};

