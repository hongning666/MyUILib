#ifndef QUITAB_H_
#define QUITAB_H_
#include"QUIButton.h"
#include<map>
/*
Tab按钮
*/
class QUISKIN_API CQUITabButton :public CQUIButton
{
public:
	CQUITabButton();
	~CQUITabButton();

};
/*
Tab页
*/
class QUISKIN_API CQUITabPage :public CUIElement
{
public:
	CQUITabPage();
	~CQUITabPage();
};
/*
Tab控件
*/
enum enTabStyle
{
	E_TabStyle_HBtn=1,//控件按钮横向排列
	E_TabStyle_VBtn=2,//控件按钮纵向排列
};
class QUISKIN_API CQUITab :public CUIElement
{
	typedef struct _tagTabItem
	{
		CQUITabButton* button;
		CQUITabPage*   page;
		_tagTabItem()
		{
			memset(this, 0, sizeof(_tagTabItem));
		}
	}TTabItem;
	typedef std::map<int, TTabItem> TabItemMap;
public:
	CQUITab();
	~CQUITab();
public:
	void SetStyle(enTabStyle eStyle);
	void InsertTab(int iIndex, CQUITabButton* pTabBtn, CQUITabPage* pTabPage);
protected:
	void ResetIndex(int iIndex);
protected:
	TabItemMap m_tTabs;
	enTabStyle m_eStyle;
};










#endif