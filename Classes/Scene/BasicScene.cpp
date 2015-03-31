#include "BasicScene.h"

#include "Utility/LSLog.h"
CCScene* BasicScene::createScene()
{
	CCScene* scene = NULL;

	scene = CCScene::create();

	BasicScene* thisLyaer = BasicScene::create();
	 scene->addChild(thisLyaer);
	return scene;
}



bool BasicScene::init()
{
	if ( !Layer::init() )
    {
        return false;
    }
	this->setKeyboardEnabled(true);

	return true;
}
void BasicScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	LSLog::info("Key with keycode %d pressed", keyCode);
}
void BasicScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	LSLog::info("Key with keycode %d onKeyReleased", keyCode);
	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_ESCAPE:
		case EventKeyboard::KeyCode::KEY_BACKSPACE:   //���ؼ���
		{
			OnBackCallBack();
		//	LSLog::info("KEY_BACKSPACE");
			break;
		}
		case EventKeyboard::KeyCode::KEY_MENU:      //�˵�����
		{
			LSLog::info("KEY_MENU");
			break;
		}
		case::EventKeyboard::KeyCode::KEY_HOME:
		{
			LSLog::info("KEY_HOME");
			break;
		}
		default:
			break;
	}
}

void BasicScene::createUI()
{
	
	
}


void BasicScene::OnBackCallBack()
{


}
