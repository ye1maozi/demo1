#pragma once
#include "cocos2d.h"
#include "Utility/exitBox.h"
USING_NS_CC;

class BasicChar:public Node
{
public:
	enum PlayerType
	{
		PLAYER_SELF = 0,
		PLAYER_AI = 1,
		PLAYER_OTHER = 2,
	};
	BasicChar();
	~BasicChar();

	virtual void Attack();

	void UseSkill();
	PlayerType GetType();

	void setData(ValueMap data);
	int getHP(){return hp;};
	int getMP(){return mp;};
	void setHP(int v);
	void setMP(int v);
protected:
	bool init(const std::string& str);
	CCSprite* m_sprite;

	Label* m_labelHp;
	Label* m_labelMP;
	static int num;
	int mp;
	int hp;
private:
	//名字 （对应显示）
	CC_SYNTHESIZE(std::string,name,Name);
	//hp
//	CC_SYNTHESIZE(int,hp,HP);
	//mp
//	CC_SYNTHESIZE(int,mp,MP);
	
	CC_SYNTHESIZE(bool,die,Die);

	PlayerType type;
};

