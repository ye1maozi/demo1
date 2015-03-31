#include "ConfMgr.h"
#include "Utility/LSLog.h"
ConfMgr* ConfMgr::_instance = NULL;
ConfMgr::ConfMgr()
{
}


ConfMgr* ConfMgr::getInstance()
{
	if(NULL == _instance)
	{
		_instance = new ConfMgr();
		if(!(_instance &&_instance->init()))
		{
			delete _instance;
			return NULL;
		}
	}
	return _instance;
}
bool ConfMgr::init()
{
	_lan = parseXMlFIle("lan.xml");
	_skill = parseXMlFIle("skill.xml");
	_conf = parseXMlFIle("conf.xml");
	return true;
}
ValueMap ConfMgr::parseXMlFIle(const char* file)
{ 
	std::string filepath =  file;

	tinyxml2::XMLDocument* xmlDoc = new tinyxml2::XMLDocument();
	Data data = CCFileUtils::sharedFileUtils()->getDataFromFile(file);
	unsigned char* pBuffer = data.getBytes();
	//pBuffer[data.getSize()-1] = '\0';
	XMLError err = xmlDoc->Parse((const char*)(pBuffer),data.getSize());

	if( 0 != err)
	{
		CCLOG(CCString::createWithFormat("parsexml %s error: %d",file,err)->getCString());
		LSLog::error("error in parseXMlFIle");
		return ValueMap();;
	}
	XMLElement* rootele = xmlDoc->RootElement();
	return parseXML(rootele);
	
//	ValueVector b = a.at("createPro").asValueVector();
//	CCLOG(((b[0]).asValueMap().at("tp").asString()).c_str());
}

ValueMap ConfMgr::parseXML(tinyxml2::XMLElement* ele)
{
	ValueMap valuemap;
	
	const XMLAttribute* att = ele->FirstAttribute();
	while(att != NULL)//atts
	{
		valuemap[att->Name()] = att->Value();
		CCLOG(att->Name());
		att = att->Next();
	}

	tinyxml2::XMLElement* cldEle = ele->FirstChildElement();
	while(cldEle != NULL)//eles
	{
		const char* nm = cldEle->Name();
		CCLOG(nm);
		if(valuemap.find(nm) != valuemap.end())
		{
			(valuemap[nm]).asValueVector().push_back(Value(parseXML(cldEle)));
		}
		else
		{
			ValueVector val;
			val.push_back(Value(parseXML(cldEle)));
			valuemap[nm] = val;
		}
		cldEle = cldEle->NextSiblingElement();
	}
	return valuemap;
}
ValueMap ConfMgr::getSkillConf(int id)
{
	ValueVector val1 = _skill.at("skill").asValueVector();
	for(Value obj:val1)
	{
		ValueMap a1 = obj.asValueMap();
		if(a1.at("id").asInt() == id)
		{
			return a1;
		}
	}
	return ValueMap();
}

ValueMap ConfMgr::getAtkConf()
{
	ValueVector val1 = _conf.at("commom").asValueVector();
	return val1[0].asValueMap();
}

std::string ConfMgr::getStringByKey(const std::string key)
{
	if(_lan.find("lan") != _lan.end())
	{
	//	LSLog::info("222");
	}
	ValueVector val1 = _lan.at("lan").asValueVector();
	CCLOG("%d",val1.size());
//	LSLog::info("111");
	for(Value obj:val1)
	{
		ValueMap a1 = obj.asValueMap();
		if(a1.at("key").asString() == key)
		{
			return a1.at("val").asString();
		}
	}
	return "";
}

ValueVector ConfMgr::getCanUseSkill(atkMgr::SkillType type,int curmp)
{
	ValueVector val1 = _skill.at("skill").asValueVector();
	ValueVector tmp;
	for(Value obj:val1)
	{
		ValueMap a1 = obj.asValueMap();
		if(a1.at("type").asInt() == type)
		{
			if(a1.at("mp").asInt() <= curmp)
			{
				tmp.push_back(Value(a1));
			}
		}
	}
	return tmp;
}
