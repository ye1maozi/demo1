#pragma once
#include "msgBox.h"
class exitBox :
	public msgBox
{
public:
		~exitBox();
	virtual bool onInitDialog(const ccMenuCallback& callback);
	static exitBox* createWithFun(const ccMenuCallback& callback);
	//CREATE_FUNC(exitBox);


//	void okMenuItemCallback(Ref* obj);
	void cancelMenuItemCallback(Ref* obj);

	void setLabelString(const std::string& text);
private:
	Label* label1;
};

