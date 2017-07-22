#include"stdafx.h"
#include"QUIListh.h"

////////////////////////////
//列表头
CListColunm::CListColunm(CQUIList* pParent)
:m_pParent(pParent)
{

}
CListColunm::~CListColunm()
{

}

void CListColunm::Init(int iHeight, DWORD dwBackColor)
{
	m_iHeight = iHeight;
	m_dwBackColor = dwBackColor;
}
void CListColunm::Insert(int iIndex, const TCHAR* szName, int iWidth, const TCHAR* szIcon)
{
	TColunm tCol;
	if (szName)
		tCol.name = szName;
	tCol.iWidth = iWidth;
	if (szIcon)
		tCol.icon = szIcon;
	m_tCols[iIndex] = tCol;
}
int CListColunm::GetColunmWidth(int iCol)
{
	TColMap::iterator it = m_tCols.find(iCol);
	if (it == m_tCols.end())
		return 0;
	return (*it).second.iWidth;
}

void CListColunm::Draw(Gdiplus::Graphics& grx)
{	
	//计算区域
	RECT rcParent;
	m_pParent->GetBound(&rcParent);
	//1.画背景
	Gdiplus::SolidBrush fillbrush(Gdiplus::Color(GetRValue(m_dwBackColor), GetGValue(m_dwBackColor), GetBValue(m_dwBackColor)));
	grx.FillRectangle(&fillbrush, rcParent.left, rcParent.top, rcParent.right - rcParent.left, m_iHeight);

	//2.画列表头
	Gdiplus::FontFamily family(L"宋体");
	Gdiplus::Font font(&family, 10);
	DWORD dwTxtColor = m_pParent->GetTextColor();
	Gdiplus::SolidBrush fbrush(Gdiplus::Color(GetRValue(dwTxtColor), GetGValue(dwTxtColor), GetBValue(dwTxtColor)));

	//文本对齐格式
	Gdiplus::StringFormat format;
	format.SetAlignment(Gdiplus::StringAlignmentNear);
	format.SetLineAlignment(Gdiplus::StringAlignmentFar);

	int iLeft = rcParent.left;
	TColMap::iterator it = m_tCols.begin();
	while (it != m_tCols.end())
	{
		//图标没画
		if ((*it).second.iWidth != 0)
		{
			Gdiplus::RectF rcTxt(iLeft, rcParent.top, (*it).second.iWidth, m_iHeight);
			grx.DrawString((*it).second.name.c_str(), (*it).second.name.length(), &font, rcTxt, &format, &fbrush);
			iLeft += (*it).second.iWidth;//下一个列头的左边

			//画一根线
			Gdiplus::Pen pen(Gdiplus::Color(0xf2, 0xf2, 0xf2), 1);
			grx.DrawLine(&pen, Gdiplus::Point(iLeft, rcParent.top + 4), Gdiplus::Point(iLeft, rcParent.top + m_iHeight - 4));

		}
		++it;
	}
}

BOOL CListColunm::OnMouseMove(POINT pt)
{
	RECT rcCol;
	m_pParent->GetBound(&rcCol);
	rcCol.bottom = rcCol.top + m_iHeight;
	//光标是否在列头区域
	if (!PtInRect(&rcCol, pt))
	{
		//光标不在列头区域，恢复就光标
		if (m_hOldCursor)
		{
			SetClassLong(m_pParent->GetHostWnd(), GCL_HCURSOR, (LONG)m_hOldCursor);
			m_hOldCursor = NULL;
		}
	}
	if (m_bDrag)
	{//当前在拖拽状态
		int iSubWidth = pt.x - m_tDragPt.x;//计算拖拽距离

		//改变当前拖拽列的宽度
		SubColWidth(m_iCurCol, iSubWidth);
		m_tDragPt = pt;
		return TRUE;
	}
	//判断光标在哪个列
	int iLeft = rcCol.left;
	TColMap::iterator it = m_tCols.begin();
	while (it != m_tCols.end())
	{
		rcCol.left =iLeft+ (*it).second.iWidth - 2;
		rcCol.right = rcCol.left + 4;
		if (PtInRect(&rcCol, pt))
		{
			if (m_hOldCursor == NULL)
				m_hOldCursor = (HCURSOR)SetClassLong(m_pParent->GetHostWnd(), GCL_HCURSOR, (LONG)LoadCursor(nullptr, IDC_SIZEWE));
			return TRUE;
		}
		iLeft += (*it).second.iWidth;
		++it;
	}
	//不在两列之间，恢复旧光标
	if (m_hOldCursor)
	{
		SetClassLong(m_pParent->GetHostWnd(), GCL_HCURSOR, (LONG)m_hOldCursor);
		m_hOldCursor = NULL;
	}
	return FALSE;
}

BOOL CListColunm::SetDrag(POINT pt)
{
	RECT rcCol;
	m_pParent->GetBound(&rcCol);
	rcCol.bottom = rcCol.top + m_iHeight;

	//光标是否在我们列头区域
	if (!PtInRect(&rcCol, pt))
	{
		m_bDrag = FALSE;
		return FALSE;
	}

	int iLeft = rcCol.left;
	TColMap::iterator it = m_tCols.begin();
	while (it != m_tCols.end())
	{
		rcCol.left = iLeft + (*it).second.iWidth - 2;
		rcCol.right = rcCol.left + 4;
		if (PtInRect(&rcCol, pt))
		{//找到了，开启拖拽状态
			m_bDrag = TRUE;
			//如果后面一个列的宽度为0，我们要优先拖后面一列
			TColMap::iterator tmpIt = it;
			++tmpIt;
			if (tmpIt != m_tCols.end() && (*tmpIt).second.iWidth == 0)
				it = tmpIt;
			m_iCurCol = (*it).first;
			m_tDragPt = pt;
			return TRUE;
		}
		iLeft += (*it).second.iWidth;
		++it;
	}
	m_bDrag = FALSE;
	return FALSE;
}

void CListColunm::SubColWidth(int iCol, int iSubWidth)
{
	TColMap::iterator it = m_tCols.find(iCol);
	if (it == m_tCols.end())
		return;

	(*it).second.iWidth += iSubWidth;

	if ((*it).second.iWidth < 0)
		(*it).second.iWidth = 0;
}

BOOL CListColunm::CancleDrag()
{
	if (m_bDrag)
	{
		m_bDrag = FALSE;
		if (m_hOldCursor)
		{
			SetClassLong(m_pParent->GetHostWnd(), GCL_HCURSOR, (LONG)m_hOldCursor);
			m_hOldCursor = NULL;
		}
		return TRUE;
	}
	return FALSE;
}

//////////////////
//行
CListItem::CListItem(CQUIList* pParent)
:m_pParent(pParent)
{

}
CListItem::~CListItem()
{

}
void CListItem::Insert(int iItem, const TCHAR* szName, const TCHAR* szIcon)
{
	TItem tItem;
	tItem.iItem = iItem;
	if (szName)
		tItem.name = szName;
	if (szIcon)
		tItem.icon = szIcon;
	m_tItems[iItem] = tItem;
}

void CListItem::Draw(Gdiplus::Graphics& grx, int iItem, const RECT& rc)
{
	if (rc.left == rc.right)
		return;
	TItemMap::iterator it = m_tItems.find(iItem);
	if (it == m_tItems.end())
		return;
	//创建字体
	Gdiplus::FontFamily family(m_pParent->GetFamily());
	Gdiplus::Font font(&family, m_pParent->GetFontSize());

	//文本对齐风格
	Gdiplus::StringFormat format;
	format.SetAlignment(Gdiplus::StringAlignmentNear);
	format.SetLineAlignment(Gdiplus::StringAlignmentCenter);

	//画刷
	DWORD dwTxtColor = m_pParent->GetTextColor();
	Gdiplus::SolidBrush fbrush(Gdiplus::Color(GetRValue(dwTxtColor), GetGValue(dwTxtColor), GetBValue(dwTxtColor)));

	//画文字
	grx.DrawString((*it).second.name.c_str(), (*it).second.name.length(), &font, Gdiplus::RectF(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top), &format, &fbrush);
}


////////////////////////////////
//列表框

CQUIList::CQUIList() 
:m_Colunm(this), m_VscrollBar(this)
{
	m_iItemCurrent = -1;
	m_iItemOver = -1;
	m_VscrollBar.SetScrollBarStyle(E_ScrollBar_VBar);
}
CQUIList::~CQUIList()
{

}
void CQUIList::Create(const TCHAR* szEleID, const RECT& rc, HWND hHostWnd, IQUIEventCallBack* pCallBack)
{
	CUIElement::Create(szEleID, rc, hHostWnd, pCallBack);
	RECT rcScroll;
	rcScroll.left = m_bound.right - 16;
	rcScroll.top = m_bound.top;
	rcScroll.right = rcScroll.left+16;
	rcScroll.bottom = m_bound.bottom;
	m_VscrollBar.Create(NULL, rcScroll, hHostWnd, pCallBack);
}
void CQUIList::InitColunm(int iHeight, DWORD dwBackColor)
{
	m_Colunm.Init(iHeight, dwBackColor);
}
void CQUIList::InsertColunm(int iIndex, const TCHAR* szName, int iWidth, const TCHAR* szIcon)
{
	m_Colunm.Insert(iIndex, szName, iWidth, szIcon);
}
void CQUIList::DrawText(Gdiplus::Graphics& grx)
{
	m_Colunm.Draw(grx);
	size_t count = m_tListItem.size();
	int iTotalHeight = count * m_iHeight1 ;
	if (m_iItemCurrent != -1)
		iTotalHeight += (m_iHeight2 - m_iHeight1);
	if (m_iItemOver != -1)
		iTotalHeight += (m_iHeight2 - m_iHeight1);

	Gdiplus::Bitmap membmp(m_bound.right - m_bound.left, iTotalHeight);
	Gdiplus::Graphics* pGrx = Gdiplus::Graphics::FromImage(&membmp);
	DrawItems(*pGrx);

	int iY = 0;
	if (m_VscrollBar.IsVisible())
	{
		iY = m_VscrollBar.GetPos();
	}
	int iWidth = m_bound.right - m_bound.left;
	int iHeight = m_bound.bottom - m_bound.top - m_Colunm.GetHeight();
	grx.DrawImage(&membmp, m_bound.left, m_bound.top + m_Colunm.GetHeight(),
		0, iY, iWidth, iHeight, Gdiplus::UnitPixel);

	delete pGrx;
	pGrx = NULL;
	
	m_VscrollBar.DoPaint(grx);
}
void CQUIList::DrawItems(Gdiplus::Graphics& grx)
{
	//画行
	int iTop = 0;

	TListItemMap::iterator it = m_tListItem.begin();
	while (it != m_tListItem.end())
	{
		DWORD dwColor = m_dwBackColor;
		int iHeight = m_iHeight1;
		if (m_iItemCurrent == (*it).first)
		{
			dwColor = m_dwBackColor2;
			iHeight = m_iHeight2;
		}
		else if (m_iItemOver == (*it).first)
		{
			dwColor = m_dwBackColor1;
			iHeight = m_iHeight2;
		}

		//计算行的坐标
		RECT rcItem;
		rcItem.left = 0;
		rcItem.top = iTop;
		rcItem.right = m_bound.right - m_bound.left;
		rcItem.bottom = iTop + iHeight;


		Gdiplus::SolidBrush fillbrush(Gdiplus::Color(GetRValue(dwColor), GetGValue(dwColor), GetBValue(dwColor)));
		grx.FillRectangle(&fillbrush, Gdiplus::Rect(rcItem.left, rcItem.top, rcItem.right - rcItem.left, rcItem.bottom - rcItem.top));

		Gdiplus::Pen pen(Gdiplus::Color(99, GetRValue(m_dwTextColor), GetGValue(m_dwTextColor), GetBValue(m_dwTextColor)));
		grx.DrawRectangle(&pen, Gdiplus::Rect(rcItem.left, rcItem.top, rcItem.right - rcItem.left, rcItem.bottom - rcItem.top));
		


		int iLeft = rcItem.left;
		int iCols = m_Colunm.GetCols();
		for (int i = 0; i < iCols; i++)
		{
			RECT rcSubItem;
			rcSubItem.left = iLeft;
			rcSubItem.top = rcItem.top;
			rcSubItem.right = iLeft + m_Colunm.GetColunmWidth(i);
			rcSubItem.bottom = rcItem.bottom;
			(*it).second->Draw(grx, i, rcSubItem);
			iLeft += m_Colunm.GetColunmWidth(i);
		}
		++it;
		iTop += iHeight;

	}
}
void CQUIList::SetItemBackColor(DWORD dwColor1, DWORD dwColor2)
{
	m_dwBackColor1 = dwColor1;
	m_dwBackColor2 = dwColor2;
}
void CQUIList::SetItemHeight(int iHeight1, int iHeight2)
{
	m_iHeight1 = iHeight1;
	m_iHeight2 = iHeight2;
}
void CQUIList::InsertItem(int iItem, const TCHAR* szName, const TCHAR* szIcon)
{
	CListItem* pListItem = new CListItem(this);
	pListItem->Insert(0, szName, szIcon);
	m_tListItem[iItem] = pListItem;

	size_t count = m_tListItem.size();
	int iTotalHeight = count* m_iHeight1;

	if (m_iItemCurrent != -1)
		iTotalHeight += (m_iHeight2 - m_iHeight1);
	if (m_iItemOver != -1)
		iTotalHeight += (m_iHeight2 - m_iHeight1);

	if (iTotalHeight > m_bound.bottom - m_bound.top - m_Colunm.GetHeight())
	{
		m_VscrollBar.SetRang(iTotalHeight - (m_bound.bottom - m_bound.top )*3/4);
		m_VscrollBar.SetVisible(TRUE);
	}
}
void CQUIList::SetItemText(int iItem, int iSubItem, const TCHAR* szName, const TCHAR* szIcon)
{
	TListItemMap::iterator it = m_tListItem.find(iItem);
	if (it == m_tListItem.end())
		return;
	(*it).second->Insert(iSubItem, szName, szIcon);
}
LRESULT CQUIList::OnControlMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	 __super::OnControlMessage(message, wParam, lParam);
	 if (m_VscrollBar.OnControlMessage(message, wParam, lParam) == S_OK)
		 return S_OK;
	switch (message)
	{
	  case WM_MOUSEMOVE:
	  {
		 POINT pt;
		 pt.x = LOWORD(lParam);
		 pt.y = HIWORD(lParam);
		 if (HitTest(pt))
		 {
			 if (m_Colunm.OnMouseMove(pt))
			 {
				 InvalidBounds();
				 return S_OK;
			 }
			 int Item = FindItemByPoint(pt);
			 if (Item >=0)
			 {
				 m_iItemOver = Item;
				 InvalidBounds();
			 }
			 return S_OK;
		 }
	  }
		break;
	  case WM_LBUTTONDOWN:
	  {
		POINT pt;
		pt.x = LOWORD(lParam);
		pt.y = HIWORD(lParam);
		if (HitTest(pt))
		{
			if (m_Colunm.SetDrag(pt))
				return S_OK;
			int Item = FindItemByPoint(pt);
			if (Item >= 0)
			{
				m_iItemCurrent = Item;
				InvalidBounds();
			}
			return S_OK;
		}
	  }
		  break;
	  case WM_LBUTTONUP:
	  {
		if (m_Colunm.CancleDrag())
			return S_OK;
	  }
		  break;
	}
	return S_FALSE;
}
int CQUIList::FindItemByPoint(const POINT& pt)
{
	int Item = -1;
	int iTop = m_bound.top + m_Colunm.GetHeight();
	TListItemMap::iterator it = m_tListItem.begin();
	int iPos = m_VscrollBar.GetPos();
	int iTotalHeight = 0;
	while (it != m_tListItem.end())
	{
		int iHeight = m_iHeight1;
		if (m_iItemCurrent == (*it).first || m_iItemOver == (*it).first)
			iHeight = m_iHeight2;
		iTotalHeight += iHeight;
		if (iTotalHeight >= iPos)
		{//只比较在控件可见范围之内的行
			RECT rcItem;
			rcItem.left = m_bound.left;
			rcItem.top = iTop;
			rcItem.right = m_bound.right;
			rcItem.bottom = iTop + iHeight;

			if (PtInRect(&rcItem, pt))
			{
				Item = (*it).first;
				break;
			}
			iTop += iHeight;
		}
		
		++it;
		//下一行的Y轴坐标超过控件的最低端，遍历结束
		if (iTop >= m_bound.bottom)
			break;
	}
	return Item;
}
void CQUIList::OnHScrollBar(const TScrollInfo* pScrollInfo)
{

}
void CQUIList::OnVScrollBar(const TScrollInfo* pScrollInfo)
{
	InvalidBounds();
}
void CQUIList::SetVScrollImage(const TCHAR* szImage)
{
	m_VscrollBar.SetStateImage(szImage);
}