#include "AIplayer.h"
#include "GameMgr\dataMgr.h"
#include "GameMgr/ConfMgr.h"
AIplayer::AIplayer(void)
{
}


AIplayer::~AIplayer(void)
{
}

void AIplayer::Attack()
{
	Vector<BasicChar*> curPlayerList = dataMgr::getInstance()->getCurList();
	int moreNum = 0;
	int moreNum2 = 0;
	int lessNum = 0;
	int lessNum2 = 0;
	int maxMp = 0;
	ValueMap conf = ConfMgr::getInstance()->getAtkConf();
	int m = conf.at("force").asInt();
	for(BasicChar* cha : curPlayerList)
	{
		if(cha->getName() == this->getName())
		{
			continue;
		}
		int mp = cha->getMP();
		if(maxMp < mp)
		{
			maxMp = mp;
		}
		if(mp > getMP() + m)
		{
			++moreNum2;
		}
		else if(mp > getMP())
		{
			++moreNum;
		}
		else if(mp < getMP() - m)
		{
			++lessNum2;
		}
		else if(mp < getMP())
		{
			++lessNum;
		}
	}

	if(maxMp == 0 && getMP() == 0)
	{
		atkMgr::getInstance()->PlayerAttack(this,21);
	}
	else if(maxMp ==0 && getMP() > 0)
	{
		atkMgr::getInstance()->PlayerAttack(this,1);
	}
	else 
	{
		int randa = 100;
		int randh = 100;
		int randd = 100;
		bool useMaxAtk = false;
		bool useMaxDef = false;
		if(getMP() > 0 )
		{
			int len = curPlayerList.size();
			float max = moreNum2/len;

			
			if(max >= 0.5)
			{
				randa += 20;
				randh += 30;
			}
			else
			{
				max = moreNum/len;
				if(max >= 0.5)
				{
					randa -= 20;
					randd += 50;
					useMaxDef = true;
				}
				else 
				{
					float min = lessNum2/len;
					if(min > 0.5)
					{
						randh -=20;
						randa += 50;
						useMaxAtk = true;
					}
					else 
					{
						min = lessNum/len;
						if(min > 0.5)
						{
							randh -= 20;
							randa += 30;
						}
					}
					
				}
			}
		}
		else
		{
			randa = 0;
		}

		int maxrand = randa + randd + randh;
		int randt = CCRANDOM_0_1()* maxrand;
		int skiid=0;
		if(randt < randa)
		{
		//	if(useMaxAtk)
		//	{
				skiid = getMP();
				if(skiid > 5)
				{
					skiid = 5;
				}
		//	}
		//	else
		//	{
		//		skiid = 
		//	}
		}
		else if(randt < randd)
		{
			skiid = getMP()+10;
			if(skiid > 15)
			{
				skiid = 15;
			}
		}
		else
		{
			skiid = 21;
		}
		atkMgr::getInstance()->PlayerAttack(this,skiid);
	}
}
AIplayer* AIplayer::create(const std::string& str)
{
	AIplayer* p = new AIplayer();
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
//bool AIplayer::init(const std::string& str)
//{
//	m_sprite = CCSprite::create(str);
//	
//	m_labelHp = Label::createWithSystemFont("HP:","arial",60);
//	m_labelHp->setPosition(0,-10);
//	m_labelMP = Label::create("MP:","arial",60);
//	m_labelHp->setPosition(0,-30);
//	this->addChild(m_sprite);
//	this->addChild(m_labelHp);
//	this->addChild(m_labelMP);
//	return true;
//}

bool AIplayer::init(const std::string& str)
{
	BasicChar::init(str);
	type = PlayerType::PLAYER_AI;
	return true;
}
