#include "JoinScene.h"
#include "MainScene.h"
#include "GameMgr/ConfMgr.h"
#include "character/Player/player.h"
#include "Utility/LSLog.h"
JoinScene::~JoinScene()
{

	TextureCache::getInstance()->removeUnusedTextures();
	LSLog::info("~JoinScene");
}

void JoinScene::onExit()
{
	 ActionManagerEx::getInstance()->releaseActionsByJsonName("menu.json");
	Layer::onExit();
}
CCScene* JoinScene::createScene()
{
	LSLog::info("createScene1");
	CCScene* scene = NULL;

	scene = CCScene::create();

	JoinScene* thisLyaer = JoinScene::create();
	LSLog::info("createScene2");
	 scene->addChild(thisLyaer);
	return scene;
}


bool JoinScene::init()
{
	if ( !BasicScene::init() )
    {
        return false;
    }
	//ConfMgr::getInstance()->parseXMlFIle("outgame.xml");
	createUI();
	return true;
}


void JoinScene::createUI()
{

	Widget* widget = (GUIReader::getInstance()->widgetFromJsonFile("menu/Json/menu.json")); 
	widget->setPosition(Vec2(0,0));
	this->addChild(widget);
	bglayer = dynamic_cast<Layout*>(widget->getChildByName("bglayer"));
	firstlayer = dynamic_cast<Layout*>(widget->getChildByName("firstlayer"));
	secondlayer = dynamic_cast<Layout*>(widget->getChildByName("secondlayer"));
	setlayer = dynamic_cast<Layout*>(widget->getChildByName("setlayer"));
	label = dynamic_cast<Text*>(secondlayer->getChildByName("label"));

	LSLog::info("dynamic_cast end");
	Button* btn = NULL;
	//start continue set help about
	btn = dynamic_cast<Button*>(firstlayer->getChildByName("start_btn"));
	btn->addTouchEventListener(this, toucheventselector(JoinScene::onMouseEnd));
	btn = dynamic_cast<Button*>(firstlayer->getChildByName("continue_btn"));
	btn->addTouchEventListener(this, toucheventselector(JoinScene::onMouseEnd));
	btn = dynamic_cast<Button*>(firstlayer->getChildByName("set_btn"));
	btn->addTouchEventListener(this, toucheventselector(JoinScene::onMouseEnd));
	btn = dynamic_cast<Button*>(firstlayer->getChildByName("help_btn"));
	btn->addTouchEventListener(this, toucheventselector(JoinScene::onMouseEnd));
	btn = dynamic_cast<Button*>(firstlayer->getChildByName("about_btn"));
	btn->addTouchEventListener(this, toucheventselector(JoinScene::onMouseEnd));

	CheckBox* music = dynamic_cast<CheckBox*>(setlayer->getChildByName("music"));
	music->addEventListener(CheckBox::ccCheckBoxCallback(CC_CALLBACK_2(JoinScene::onCheckBos,this)));
	CheckBox* audio = dynamic_cast<CheckBox*>(setlayer->getChildByName("audio"));
	audio->addEventListener(CheckBox::ccCheckBoxCallback(CC_CALLBACK_2(JoinScene::onCheckBos,this)));

	ani = ActionManagerEx::getInstance()->getActionByName("menu.json","Animation0");
	if(!ani->isPlaying())
	{
		LSLog::info("ani");
		ani->play();
	}
	LSLog::info("ani end");
	bool v = Utility::getInstance()->IsPlayMusic();
	if(v)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/bgjoin.mp3");
	}
	else
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic("audio/bgjoin.mp3");
	}
	music->setSelectedState(v);
	v =Utility::getInstance()->IsPlayAudio();
	audio->setSelectedState(v);

	setlayer->addTouchEventListener(Widget::ccWidgetTouchCallback(CC_CALLBACK_2(JoinScene::onMouseEnd,this)));
	//this->keyBackClicked()
	//auto keyEvt = EventListenerKeyboard::create();
//	keyEvt->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event)
//			{
//				log("Key with keycode %d pressed", keyCode);
//			};
//	keyEvt->onKeyReleased = CC_CALLBACK_2(JoinScene::onKeyReleased,this);
//	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyEvt,this);

}
void JoinScene::onCheckBos(Ref* psend,CheckBox::EventType type)
{
	bool state = CheckBox::EventType::SELECTED == type;
	CheckBox* btn = dynamic_cast<CheckBox*>(psend);
	if(state)
	{
		CCLOG("true");
	}
	else
	{
		CCLOG("false");
	}
	const std::string str = btn->getName();
	if("music" == str)
	{
		Utility::getInstance()->setMusic(state);
		if(state && !CocosDenshion::SimpleAudioEngine::getInstance()->isBackgroundMusicPlaying())
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic("audio/bgjoin.mp3");
		}
		else
		{
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
		}
	}
	else if("audio" == str)
	{
		Utility::getInstance()->setAudio(state);
	}
}
void JoinScene::onMouseEnd(Ref* psend,Widget::TouchEventType type)
{
	if(Widget::TouchEventType::ENDED != type)
	{
		return;
	}
	Widget* btn = dynamic_cast<Widget*>(psend);
	const std::string str = btn->getName();

	CCLOG(str.c_str());
	if("start_btn" == str)
	{
		dataMgr::getInstance()->isContinue = false;
		Director::getInstance()->replaceScene(CCTransitionCrossFade::create(2.0f,MainScene::createScene()));
	}
	else if("continue_btn" == str)
	{
		dataMgr::getInstance()->isContinue = true;
		Director::getInstance()->replaceScene(CCTransitionCrossFade::create(2.0f,MainScene::createScene()));
	}
	else if("set_btn" == str)
	{
		setlayer->setVisible(!setlayer->isVisible());
	}
	else if("help_btn" == str)
	{
		showMsg(MsgType::msg_help);
	}
	else if("about_btn" == str)
	{
		showMsg(MsgType::msg_about);
	}
	else 
	{
		this->setlayer->setVisible(false);
	}
}
void JoinScene::showMsg(MsgType type)
{

	if(secondlayer->isVisible() && _lastMsg==type)
	{
		secondlayer->setVisible(false);
	}
	else
	{
		_lastMsg = type;
		secondlayer->setVisible(true);
		std::string t1 = ConfMgr::getInstance()->getStringByKey(CCString::createWithFormat("ui_%d",type)->getCString());
		CCLOG(t1.c_str());
		label->setString(t1);
	}
}
void JoinScene::OnBackCallBack()
{
	exitBox* a = exitBox::createWithFun([this](Ref* obj)
		{
			LSLog::info("click ok");
			Director::getInstance()->end();
		});
	if(NULL != a)
		this->addChild(a);
}
