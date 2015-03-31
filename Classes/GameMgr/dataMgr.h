#pragma once
#include "character/BasicChar.h"
class dataMgr
{
public:
	static dataMgr* getInstance();
	Vector<BasicChar*> getCurList() const{return curPlayerList;} 
	BasicChar* getCharByName( std::string name);

	BasicChar* getSelf(){return selfPlayer;};
	Vector<BasicChar*> getAIList();
	void initPlayer();

	void setMpByName(const std::string name,int mp);
	void setHpByName(const std::string name,int hp);

	bool isContinue;
	void clearPlayer();
private:
	bool init();
	static dataMgr* _instance;

	Vector<BasicChar*> curPlayerList;

	BasicChar* selfPlayer;

};

