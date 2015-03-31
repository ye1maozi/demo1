#include "atkMgr.h"
#include "dataMgr.h"
#include "ConfMgr.h"
#include "Utility.h"
#include "Utility/LSLog.h"
atkMgr* atkMgr::_instance = NULL;

atkMgr* atkMgr::getInstance()
{
	if(NULL == _instance)
	{
		_instance = new atkMgr();
		_instance->init();
	}
	return _instance;
}

bool atkMgr::init()
{
//	_function = NULL;
	return true;
}
bool atkMgr::PlayerAttack(BasicChar* cha,int sklid)
{
	const std::string name = cha->getName();
	if(cha->getDie())
	{
		return false;
	}
	for(Value o:playerList)
	{
		ValueMap obj = o.asValueMap();
		if(obj.at("name").asString() == name)
		{
			return false;
		}
	}
	ValueMap skiconf = ConfMgr::getInstance()->getSkillConf(sklid);
	if(cha->getMP()  < skiconf.at("mp").asInt() )
	{
		return false;
	}
	
	ValueMap val;
	val["name"] = name;
	val["id"] = sklid;
	playerList.push_back(Value(val));

	if(playerList.size() == dataMgr::getInstance()->getCurList().size())
	{
		dealAttack();
		playerList.clear();
	}
	if(cha->GetType() == BasicChar::PlayerType::PLAYER_SELF)
	{
		Vector<BasicChar*> AiPlayerList = dataMgr::getInstance()->getAIList();
		//todo通知ai
		for(BasicChar* ai:AiPlayerList)
		{
			if(ai->GetType() == BasicChar::PlayerType::PLAYER_AI)
			{ 
				ai->Attack();
			}
		}
	}
	return true;
}

void atkMgr::dealAttack()
{
	int maxAtk = 0;//最大攻击等级

	for(Value o:playerList)
	{
		ValueMap obj = o.asValueMap();
		int sklid = obj.at("id").asInt();
		ValueMap skiconf = ConfMgr::getInstance()->getSkillConf(sklid);
		int type = skiconf.at("type").asInt();
		BasicChar* cha = dataMgr::getInstance()->getCharByName(obj.at("name").asString());
		cha->UseSkill();
		if(SkillType::SKILL_ATK == type)
		{
			int lvl = skiconf.at("lvl").asInt();
			if(maxAtk < lvl)
			{
				maxAtk = lvl;
				sklid = sklid;
			}
		}
	}

	bool plyadu = Utility::getInstance()->IsPlayAudio();
	//todo优化
	for(Value o:playerList)
	{
		ValueMap obj = o.asValueMap();
		int sklid = obj.at("id").asInt();
		ValueMap skiconf = ConfMgr::getInstance()->getSkillConf(sklid);
		int type = skiconf.at("type").asInt();
		BasicChar* cha = dataMgr::getInstance()->getCharByName(obj.at("name").asString());
		int lvl = skiconf.at("lvl").asInt();
		int cost = skiconf.at("mp").asInt();
		switch (type)
		{
			case SkillType::SKILL_ATK:
				if(lvl < maxAtk)
				{
					cha->setDie(true);
					dataMgr::getInstance()->setHpByName(cha->getName(),0);
					
				}
				else
				{
					if(plyadu)
						CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/atk.wav");
				}
				dataMgr::getInstance()->setMpByName(cha->getName(),cha->getMP()-cost);//...
				break;
			case SkillType::SKILL_DEF:
				if(lvl < maxAtk-2)
				{
					cha->setDie(true);
					dataMgr::getInstance()->setHpByName(cha->getName(),0);//...
				}
				else
				{
					//todo
					if(plyadu)
						CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/def.wav");
				}
				dataMgr::getInstance()->setMpByName(cha->getName(),cha->getMP()-cost);//...
				break;
			case SkillType::SKILL_HEL:
				if(maxAtk > 0)
				{
					cha->setDie(true);
					dataMgr::getInstance()->setHpByName(cha->getName(),0);
				}
				else
				{
					//todo
					dataMgr::getInstance()->setMpByName(cha->getName(),cha->getMP()+1);
				}
				break;
			default:
				break;
		}
	}
	EventCustom event("test");
	event.setUserData(&playerList);
	Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
	if(NULL != _function)
		_function();
}

void atkMgr::clearAll()
{
	LSLog::info("clearAll");
	playerNum = 0;
	playerList.clear();

}
