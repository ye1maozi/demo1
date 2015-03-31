#pragma once
#include "cocos2d.h"
#include "tinyxml2\tinyxml2.h"
#include "atkMgr.h"
USING_NS_CC;
using namespace tinyxml2;
class ConfMgr//:public Ref
{
public:
	
	static ConfMgr* getInstance();

	ValueMap parseXMlFIle(const char* file);

	ValueMap getSkillConf(int id);

	ValueMap getAtkConf();

	std::string getStringByKey(std::string);

	ValueVector getCanUseSkill(atkMgr::SkillType type,int curmp);
private:
	ValueMap parseXML(XMLElement* xmlEle);
	bool init();
	ConfMgr();
	static ConfMgr* _instance;
	ValueMap _lan;
	ValueMap _skill;
	ValueMap _conf;
};

