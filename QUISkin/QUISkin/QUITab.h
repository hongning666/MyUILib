#ifndef QUITAB_H_
#define QUITAB_H_
#include"QUIButton.h"
#include<map>
/*
Tab��ť
*/
class QUISKIN_API CQUITabButton :public CQUIButton
{
public:
	CQUITabButton();
	~CQUITabButton();

};
/*
Tabҳ
*/
class QUISKIN_API CQUITabPage :public CUIElement
{
public:
	CQUITabPage();
	~CQUITabPage();
};
/*
Tab�ؼ�
*/
enum enTabStyle
{
	E_TabStyle_HBtn=1,//�ؼ���ť��������
	E_TabStyle_VBtn=2,//�ؼ���ť��������
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