#pragma once
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui\CocosGUI.h"
#include "extensions/cocos-ext.h"
#include "GameMgr/ConfMgr.h"
#include "GameMgr/dataMgr.h"
#include "GameMgr/Utility.h"
#include "Utility/exitBox.h"
USING_NS_CC;
using namespace ui;
using namespace cocostudio;
class BasicScene :
    public Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();  
	virtual void createUI();
    CREATE_FUNC(BasicScene);

    virtual void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
   	virtual void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

   	virtual void OnBackCallBack();
};

