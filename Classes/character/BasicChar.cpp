#include "BasicChar.h"
#include "GameMgr/Utility.h"
#include "Utility/LSLog.h"
//#include "Scene/JoinScene.h"
int BasicChar::num = 0;
BasicChar::BasicChar()
{
	
}


BasicChar::~BasicChar()
{
	LSLog::info("~BasicChar");
	m_sprite = NULL;
	m_labelMP = NULL;
	m_labelMP = NULL;
}
void BasicChar::Attack()
{
	
}

void BasicChar::UseSkill()
{
	
}
BasicChar::PlayerType BasicChar::GetType()
{
	return type;
}
bool BasicChar::init(const std::string& str)
{
	num++;
	CCString* s = CCString::createWithFormat("name%d",num);
	setName(s->getCString());
	
	mp = 0;
	hp = 1;
	die = false;
	m_sprite = CCSprite::create(str);
	
	CCString* hps = CCString::createWithFormat("HP:%d",hp);
	CCString* mps = CCString::createWithFormat("MP:%d",mp);
	m_labelHp = Label::createWithSystemFont(hps->getCString(),"arial",60);
	m_labelHp->setPosition(0,-60);
	m_labelHp->setColor(Color3B::RED);

	m_labelMP = Label::create(mps->getCString(),"arial",60);
	m_labelMP->setColor(Color3B::RED);
	m_labelMP->setPosition(0,-120);
	this->addChild(m_sprite);
	this->addChild(m_labelHp);
	this->addChild(m_labelMP);
	return true;
}

void BasicChar::setData(ValueMap data)
{
	this->mp = data.at("mp").asInt();
	this->hp = data.at("hp").asInt();

	m_labelHp->setString( CCString::createWithFormat("HP:%d",hp)->getCString());
	m_labelMP->setString( CCString::createWithFormat("MP:%d",mp)->getCString());
}

void BasicChar::setMP(int mp)
{
	if(mp > this->mp)
	{
		CCParticleSystem* d = ParticleExplosion::createWithTotalParticles(2000);
		d->setEmitterMode(kCCParticleModeRadius);
		d->setEmissionRate(1000);
		d->setStartRadius(0);
		d->setEndRadius(100);
		d->setLife(0.5f);
		d->setDuration(0.5f);
		d->setPosition(100,100);
		d->setAutoRemoveOnFinish(true);
		m_sprite->addChild(d);
		bool plyadu = Utility::getInstance()->IsPlayAudio();
		if(plyadu)
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/help.wav");
	}
	this->mp = mp;
	m_labelMP->setString( CCString::createWithFormat("MP:%d",mp)->getCString());

}
void BasicChar::setHP(int mp)
{
	this->hp = mp;
	m_labelHp->setString( CCString::createWithFormat("HP:%d",hp)->getCString());
	if(hp == 0)
	{
		CCMoveBy* ma = CCMoveBy::create(0.1f,Vec2(-10,10));
		CCMoveBy* mb = ma->reverse();

	//	TintTo* ac =TintTo::create(0.1f,255, 0, 0);
	//	TintTo* ad = ac->reverse();

		Sequence* aa = Sequence::create(ma,mb,NULL);
	//	Sequence* bb = Sequence::create(ac,ad,NULL);

		//Spawn* s = Spawn::create(aa,bb,NULL);
		this->runAction(aa);
		bool plyadu = Utility::getInstance()->IsPlayAudio();
		if(plyadu)
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("audio/die.wav");


		std::string ss;
		if(this->type == PlayerType::PLAYER_SELF)
		{
			ss = "you win";
		}
		else
		{
			ss = "you lose";
		}
		EventCustom event("playerdie");
		event.setUserData((void*)ss.c_str());
		Director::getInstance()->getEventDispatcher()->dispatchEvent(&event);
	}
}
