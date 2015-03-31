#include "exitBox.h"


bool exitBox::onInitDialog(const ccMenuCallback& callback)
{
	CCSize winSize = CCDirector::getInstance()->getWinSize();

	label1 = Label::create("are you sure to exit?","Arial",64);
	label1->setPosition(winSize.width/2,winSize.height/2+50);
	this->addChild(label1);

	auto okitem = CCMenuItemFont::create("ok",callback);
	okitem->setPosition(winSize.width/2-100,winSize.height/2 - 50);

	auto cancelitem = CCMenuItemFont::create("cancel",CC_CALLBACK_1(exitBox::cancelMenuItemCallback,this));
	cancelitem->setPosition(winSize.width/2+100,winSize.height/2 - 50);

	auto menu = Menu::create(okitem,cancelitem,NULL);
	menu->setPosition(CCPointZero);
	this->addChild(menu);
//	pushMenu(okitem);
//	pushMenu(cancelitem);

	setColor(Color3B::RED);
	setOpacity(128);

	return true;
}
exitBox::~exitBox()
{
//	CC_SAFE_DELETE(label1);
}
void exitBox::setLabelString(const std::string& text)
{
	label1->setString(text);
}
exitBox* exitBox::createWithFun(const ccMenuCallback& callback)
{
	if(isOpen)
	{
		return NULL;
	}
	isOpen = true;
//	va_list args;
//	va_start(args,callback);
//	auto i = va_arg(args, ccMenuCallback&);
//	 va_end(args);

	exitBox* exit = new exitBox();
	if(exit && exit->init(callback))
	{
		exit->autorelease();
		return exit;
	}
	else
	{
		delete exit;
		exit = NULL;
		return NULL;
	}
}

void exitBox::cancelMenuItemCallback(CCObject *obj)
{

    removeFromParentAndCleanup(true);
}
