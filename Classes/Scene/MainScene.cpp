#include "MainScene.h"
#include "Utility/LSLog.h"
#include "JoinScene.h"
#include "GameMgr/Utility.h"
MainScene::~MainScene()
{

	dataMgr::getInstance()->clearPlayer();
	LSLog::info("~MainScene");
	btnlist.clear();
	TextureCache::getInstance()->removeUnusedTextures();
	this->_eventDispatcher->removeEventListenersForTarget(this,true);
}
Scene* MainScene::createScene()
{
	CCScene* scene = NULL;

	scene = CCScene::create();

	MainScene* thisLyaer = MainScene::create();
	 scene->addChild(thisLyaer);
	return scene;
}

bool MainScene::init()
{
	if ( !BasicScene::init() )
    {
        return false;
    }
	lastName = "";
	needStop = true;
	createUI();
	str1 = "";
	atkMgr::getInstance()->setAttackback(CC_CALLBACK_0(MainScene::attackBack,this));
	DelayTime* act = DelayTime::create(2.5f);
	CallFunc* call =  CallFunc::create(CC_CALLBACK_0(MainScene::delay,this));
	Sequence* seq = Sequence::create(act,call,NULL);
	this->runAction(seq);
	return true;
}
void MainScene::delay()
{
	dataMgr::getInstance()->initPlayer();
	needStop = false;
	bool v = Utility::getInstance()->IsPlayMusic();
	if(v)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/bgmain.mp3");
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/bgmain.mp3");
	}
}

void MainScene::createUI()
{
	Widget* widget = (GUIReader::getInstance()->widgetFromJsonFile("Main/Json/Main_1.json")); 
	widget->setPosition(Vec2(0,0));
	this->addChild(widget);

	skill_layer = dynamic_cast<Layout*>(widget->getChildByName("skill_layer"));

	Button* btn = NULL;
	//start continue set help about
	btn = dynamic_cast<Button*>(skill_layer->getChildByName("atk_btn"));
	btn->addTouchEventListener(this, toucheventselector(MainScene::onMouseEnd));
	btn = dynamic_cast<Button*>(skill_layer->getChildByName("def_btn"));
	btn->addTouchEventListener(this, toucheventselector(MainScene::onMouseEnd));
	btn = dynamic_cast<Button*>(skill_layer->getChildByName("hel_btn"));
	btn->addTouchEventListener(this, toucheventselector(MainScene::onMouseEnd));

	list = dynamic_cast<ListView*>(skill_layer->getChildByName("list"));
	list->setClippingType(Layout::ClippingType::SCISSOR);
	text = dynamic_cast<Text*>(widget->getChildByName("text"));
	text->setText("");
	//pro_1 = dynamic_cast<LoadingBar*>(widget->getChildByName("pro_1"));
	//pro_1->setPercent(100);
	//pro_2 = dynamic_cast<LoadingBar*>(widget->getChildByName("pro_2"));
	//pro_2->setPercent(0);
	_initpos = list->getPosition();
	_initSize = list->getSize();
	//	list->set

	EventListenerCustom* evt = EventListenerCustom::create("test",CC_CALLBACK_1(MainScene::defevt,this));
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(evt,this);

	EventListenerCustom* evt1 = EventListenerCustom::create("playerdie",CC_CALLBACK_1(MainScene::playerDie,this));
	this->_eventDispatcher->addEventListenerWithSceneGraphPriority(evt1,this);
}
void MainScene::defevt(EventCustom* evt)
{
	void* data = evt->getUserData();
	ValueVector playerList = *(ValueVector*)(data);
	for(Value o:playerList)
	{
		ValueMap obj = o.asValueMap();
		int sklid = obj.at("id").asInt();
		const std::string name = obj.at("name").asString();
		
		str1 +=StringUtils::format("name:%s,skiid: %d\n",name.c_str(),sklid);
	}
	text->setString(str1);
	needStop = false;
}
void MainScene::onMouseEnd(Ref* psend,Widget::TouchEventType type)
{
	if(Widget::TouchEventType::ENDED != type || needStop)
	{
		return;
	}
	Button* btn = dynamic_cast<Button*>(psend);
	const std::string str = btn->getName();

	if(lastName == str)
	{
		list->setVisible(!list->isVisible());
		lastName = "";
	}
	else
	{
		lastName = str;
		list->setVisible(true);
		
		atkMgr::SkillType type1;
		int offy = 0;
		std::string s;
		if("atk_btn" == str )
		{
			type1 = atkMgr::SkillType::SKILL_ATK;
			offy = 0;
			s = "g";
		}
		else if("def_btn" == str)
		{
			type1 = atkMgr::SkillType::SKILL_DEF;
			offy = 450;
			s = "d";
		}
		else if("hel_btn" == str)
		{
			type1 = atkMgr::SkillType::SKILL_HEL;
			offy = 900;
			s = "h";
		}
		int curmap = dataMgr::getInstance()->getSelf()->getMP();
		ValueVector v = ConfMgr::getInstance()->getCanUseSkill(type1,curmap);
		
		while(btnlist.size() < v.size())
		{
			Button* btn = Button::create();
			btn->addTouchEventListener(this,toucheventselector(MainScene::skillbtn_event));
			
			btnlist.pushBack(btn);
			btn->setTitleFontSize(60);
			btn->setTitleColor(Color3B::RED);
			btn->setTitleText(CCString::createWithFormat("%d",btnlist.size())->getCString());
		}
		list->removeAllChildren();
		for(int i=0;i<v.size();++i)
		{
			Button* btn1 = btnlist.at(i);

			CCString* t1 = CCString::createWithFormat("public/%s.png",s.c_str());
			CCString* t2 = CCString::createWithFormat("public/%s1.png",s.c_str());
			btn1->loadTextureNormal(t1->getCString());
			btn1->loadTexturePressed(t2->getCString());
			btn1->setTag(v[i].asValueMap().at("id").asInt());
			
			//btn->setBackgroundSpriteForState(highlightSPr,Control::State::HIGH_LIGHTED);
			list->addChild(btn1);
		}
		int t = v.size();
		if(v.size() <= 0)
		{
			t = 1;
		}
		else if(v.size() >3)
		{
			t = 3;
		}
		_initSize.width = 230*t;
		list->setSize(_initSize);
		Vec2 pos = _initpos;
		pos.y -= offy; 
		pos.x -= 230*(t-1);
		list->setPosition(pos);
		

	}
	CCLOG(str.c_str());
}
void MainScene::skillbtn_event(Ref* pSender,Widget::TouchEventType type)
{
	if(Widget::TouchEventType::ENDED != type || needStop)
	{
		return;
	}
	Button* btn = dynamic_cast<Button*>(pSender);
	
	list->setVisible(false);
	lastName = "";
	needStop = true;
	atkMgr::getInstance()->PlayerAttack(dataMgr::getInstance()->getSelf(),btn->getTag());
	CCLOG("%d",btn->getTag());
}

void MainScene::OnBackCallBack()
{
	exitBox* a = exitBox::createWithFun([this](Ref* obj)
		{

		//todo save


			Utility::getInstance()->SavePlayInfo();
			LSLog::info("click ok ");
			Director::getInstance()->replaceScene(JoinScene::createScene());


		});
	if(NULL != a)
	{
		a->setLabelString("save game?");
		this->addChild(a);

	}

}
void MainScene::playerDie(EventCustom* evt)
{
	//todo ºÏ²¢
	exitBox* a = exitBox::createWithFun([this](Ref* obj)
			{

		//todo save


		Utility::getInstance()->SavePlayInfo();
		LSLog::info("click ok ");
		Director::getInstance()->replaceScene(JoinScene::createScene());


			});
	if(NULL != a)
	{
		void* data = evt->getUserData();
		std::string ss((char*)(data));
		a->setLabelString(ss);
		this->addChild(a);

	}
}
