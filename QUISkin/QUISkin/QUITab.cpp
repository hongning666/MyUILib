#include"stdafx.h"
#include"QUITab.h"


/******************************************************
Tab°´Å¥
*******************************************************/

CQUITabButton::CQUITabButton()
{

}

CQUITabButton::~CQUITabButton()
{

}
/******************************************************
TabÒ³
*******************************************************/
CQUITabPage::CQUITabPage()
{

}
CQUITabPage::~CQUITabPage()
{

}
/******************************************************
Tab¿Ø¼þ
*******************************************************/
CQUITab::CQUITab()
{

}

CQUITab::~CQUITab()
{

}

void CQUITab::SetStyle(enTabStyle eStyle)
{
	m_eStyle = eStyle;
}
void CQUITab::InsertTab(int iIndex, CQUITabButton* pTabBtn, CQUITabPage* pTabPage)
{
	//1.
	ResetIndex(iIndex);
	TTabItem tItem;
	tItem.button = pTabBtn;
	tItem.page = pTabPage;
	m_tTabs[iIndex] = tItem;
}
void CQUITab::ResetIndex(int iIndex)
{
	if (m_tTabs.size() == 0)
		return;
	TabItemMap::iterator it = m_tTabs.find(iIndex);
	if (it != m_tTabs.end())
	{
		TabItemMap::reverse_iterator tmpIt = m_tTabs.rbegin();
		--tmpIt;
		while ((*tmpIt).first <= (*it).first)
		{
			m_tTabs[(*tmpIt).first + 1] = (*tmpIt).second;
			--tmpIt;
		}
		++it;
	}
}