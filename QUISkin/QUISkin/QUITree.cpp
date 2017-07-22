#include"stdafx.h"
#include"QUITree.h"

////////////////////////////////////
//结点数据
CVLNode::CVLNode()
{
	m_iWidth = 100;
}
CVLNode::~CVLNode()
{

}
void CVLNode::SetName(const TCHAR* szName)
{
	if (szName)
		m_strName = szName;
}
const TCHAR* CVLNode::GetName()
{
	return m_strName.c_str();
}
void CVLNode::SetIcon(const TCHAR* szIcon)
{
	if (szIcon)
		m_strIcon = szIcon;
}
const TCHAR* CVLNode::GetIcon()
{
	return m_strIcon.c_str();
}

void CVLNode::SetHeight(int iHeight)
{
	m_iHeight = iHeight;
}
void CVLNode::SetWidth(int iWidth)
{
	m_iWidth = iWidth;
}
///////////////////////////////////
//树型结点
CVLTree::CVLTree(CVLNode* pNode)
:m_pNode(pNode)
{
	m_pParent = NULL;
	m_pNext = NULL;
	m_pPre = NULL;

	m_pFirstChild = NULL;
	m_iLevel = -1;
	m_bExpend = FALSE;
	m_iChildCounts = 0;
}
CVLTree::~CVLTree()
{
	if (m_pNode)
		delete m_pNode;
	m_pNode = NULL;
	ReleaseChild();
}
int CVLTree::GetChildCount()
{
	return m_iChildCounts;
}
CVLTree* CVLTree::GetFirstChild()
{
	return m_pFirstChild;
}
CVLTree* CVLTree::GetTailChild()
{
	return m_pTailChild;
}
int CVLTree::GetLevel()
{
	return m_iLevel;
}
void CVLTree::Expend(BOOL bExpend)
{
	m_bExpend = bExpend;
}
BOOL CVLTree::IsExpend()
{
	return m_bExpend;
}
CVLTree* CVLTree::GetNextNode(CVLTree* pTreeNode)
{
	if (pTreeNode == NULL)
		return NULL;

	return pTreeNode->m_pNext;
}
CVLNode* CVLTree::GetNode()
{
	return m_pNode;
}
CVLTree* CVLTree::GetParentNode()
{
	return m_pParent;
}
void CVLTree::ReleaseChild()
{
	CVLTree* pTreeNode = m_pFirstChild;
	while (pTreeNode)
	{
		CVLTree* pTmpNode = pTreeNode;
		pTreeNode = pTreeNode->m_pNext;
		delete pTmpNode;
	}
}
CVLTree* CVLTree::DetachChildNode()
{
	CVLTree* pTmp = m_pFirstChild;
	m_pFirstChild = NULL;
	m_pTailChild = NULL;
	return pTmp;
}
CVLTree* CVLTree::InsertChildNode(CVLNode* pNode, CVLTree* pInsNode)
{
	if (pNode == NULL)
		return NULL;
	CVLTree* pNewTreeNode = new CVLTree(pNode);
	pNewTreeNode->m_pParent = this;
	pNewTreeNode->m_iLevel = m_iLevel + 1;
	if (pInsNode)
	{//插入到pInsNode后面
		pNewTreeNode->m_pNext = pInsNode->m_pNext;
		pNewTreeNode->m_pPre = pInsNode;
		pInsNode->m_pNext = pNewTreeNode;
		if (pNewTreeNode->m_pNext != NULL)
			pNewTreeNode->m_pNext->m_pPre = pNewTreeNode;
		if (m_pTailChild == pInsNode)
			m_pTailChild = pNewTreeNode;
	}
	else
	{//默认插入最末尾
		pNewTreeNode->m_pPre = m_pTailChild;
		if (m_pFirstChild == NULL)
			m_pFirstChild = pNewTreeNode;
		else
			m_pTailChild->m_pNext = pNewTreeNode;
		m_pTailChild = pNewTreeNode;
	}
	m_iChildCounts++;
	return pNewTreeNode;
}
void CVLTree::AttachChildNode(CVLTree* pTreeNode, CVLTree* pInsNode)
{
	if (pTreeNode == NULL)
		return;
	//重新计算深度
	CalcLevel(pTreeNode);
	int iNewCount = 0;
	CVLTree* pTailNode = NULL;
	CVLTree* pTmpNode = pTreeNode;
	while (pTmpNode)
	{//查找最后一个兄弟节点
		pTmpNode->m_pParent = this;
		pTailNode = pTmpNode;
		pTmpNode = pTmpNode->m_pNext;
		iNewCount++;
	}
	if (pInsNode != NULL)
	{
		pTmpNode = pInsNode->m_pNext;
		pInsNode->m_pNext = pTreeNode;
		pTreeNode->m_pPre = pInsNode;
		pTailNode->m_pNext = pTmpNode;
		if (pTmpNode != NULL)
			pTmpNode->m_pPre = pTailNode;

		if (m_pTailChild == pInsNode)
			m_pTailChild = pTailNode;
	}
	else
	{
		pTailNode->m_pPre = m_pTailChild;
		if (m_pFirstChild == NULL)
			m_pFirstChild = pTreeNode;
		else
			m_pTailChild->m_pNext = pTreeNode;

		m_pTailChild = pTailNode;
	}
	m_iChildCounts += iNewCount;
}
void CVLTree::CalcLevel(CVLTree* pTreeNode)
{
	CVLTree* pTmpNode = pTreeNode;
	while (pTreeNode)
	{
		pTreeNode->m_iLevel = m_iLevel + 1;
		pTmpNode->CalcLevel(pTmpNode->m_pFirstChild);
		pTmpNode = pTmpNode->m_pNext;
	}
}
////////////////////////////////////
//树型控件UI
CQUITree::CQUITree()
{
	m_pRoot = new CVLTree();//生成一个空的根节点
	m_iItemHeight = 30;
	m_iLastY = 0;
	m_dwItemOverColor = RGB(255, 0, 0);
	m_dwItemSelColor = RGB(0, 255, 0);
	m_pItemOver = NULL;
	m_pItemSel = NULL;
}
CQUITree::~CQUITree()
{
	if (m_pRoot)
		delete m_pRoot;
	m_pRoot = NULL;
}
void CQUITree::SetItemHeight(int iItemHeight)
{
	m_iItemHeight = iItemHeight;
}

CVLTree* CQUITree::Insert(const TCHAR* szName, const TCHAR* szIcon, CVLTree* pParent)
{
	CVLTree* pTreeNode = NULL;
	CVLNode* pNode = new CVLNode();
	pNode->SetName(szName);
	pNode->SetIcon(szIcon);
	pNode->SetHeight(m_iItemHeight);

	if (pParent)
	{
		pTreeNode = pParent->InsertChildNode(pNode);
		pNode->SetX(m_bound.left + pTreeNode->GetLevel() * 10);
	}	
	else
	{
		int iCount = m_pRoot->GetChildCount();
		pNode->SetX(m_bound.left);
		pNode->SetY(m_iLastY);
		m_iLastY += m_iItemHeight;//更新Y坐标
		pTreeNode = m_pRoot->InsertChildNode(pNode);
	} 
	return pTreeNode;

}
void CQUITree::DrawText(Gdiplus::Graphics& grx)
{
	//遍历树
	CVLTree* pTreeNode = m_pRoot->GetFirstChild();
	while (pTreeNode)
	{
		DrawItems(grx, pTreeNode);
		pTreeNode = m_pRoot->GetNextNode(pTreeNode);
	}
}
void CQUITree::Expend(CVLTree* pTreeNode, BOOL bExpend)
{
	if (pTreeNode == NULL)
		return;
	pTreeNode->Expend(TRUE);
	CalcNodeRect();
	InvalidBounds();
}
void CQUITree::DrawItems(Gdiplus::Graphics& grx, CVLTree* pTreeNode)
{
	if (pTreeNode == NULL)
		return;
	CVLTree* pTmpNode = pTreeNode;
	while (pTmpNode)
	{
		CVLNode* pNode = pTmpNode->GetNode();
		DrawItem(grx, pNode);
		if (pTmpNode->IsExpend())
		{//如果展开了，要画子节点
			DrawItems(grx, pTmpNode->GetFirstChild());
		}
		pTmpNode = pTreeNode->GetNextNode(pTmpNode);
	}
}
void CQUITree::DrawItem(Gdiplus::Graphics& grx, CVLNode* pNode)
{
	RECT rc;
	rc.left = pNode->GetX();
	rc.top = pNode->GetY();
	rc.right = m_bound.right;
	rc.bottom = rc.top + pNode->GetHeight();
	//绘制背景
	if (m_pItemSel&&m_pItemSel->GetNode() == pNode)
	{
		Gdiplus::SolidBrush fillbrush(Gdiplus::Color(50,GetRValue(m_dwItemSelColor), GetGValue(m_dwItemSelColor), GetBValue(m_dwItemSelColor)));
		grx.FillRectangle(&fillbrush, Gdiplus::RectF(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top));
	}
	else if (m_pItemOver&&m_pItemOver->GetNode() == pNode)
	{
		Gdiplus::SolidBrush fillbrush(Gdiplus::Color(50, GetRValue(m_dwItemOverColor), GetGValue(m_dwItemOverColor), GetBValue(m_dwItemOverColor)));
		grx.FillRectangle(&fillbrush, Gdiplus::RectF(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top));
	}
	//1.字体
	Gdiplus::FontFamily family(m_strFont.c_str());	
	Gdiplus::Font font(&family, m_dwFontSize);
	//2.文本对齐格式
	Gdiplus::StringFormat format;
	format.SetAlignment(Gdiplus::StringAlignmentNear);
	format.SetLineAlignment(Gdiplus::StringAlignmentCenter);
	
	Gdiplus::SolidBrush fbrush(Gdiplus::Color(GetRValue(m_dwTextColor), GetGValue(m_dwTextColor), GetBValue(m_dwTextColor)));
	
	std::basic_string<TCHAR> strName = pNode->GetName();
	grx.DrawString(strName.c_str(), strName.length(), &font, Gdiplus::RectF(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top), &format, &fbrush);
}

LRESULT CQUITree::OnControlMessage(UINT message, WPARAM wParam, LPARAM lParam)
{
	__super::OnControlMessage(message, wParam, lParam);
	switch (message)
	{
		case WM_LBUTTONDOWN:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			if (HitTest(pt))
			{
				//1.查找
				CVLTree* pTreeNode = FindNodeByPoint(pt);
				if (pTreeNode)
				{
					//鼠标点击的不是分组，不需要进行展开
					if (pTreeNode->GetChildCount() > 0)
					{
						//2.设置展开标记
						BOOL bExpend = pTreeNode->IsExpend();
						if (pTreeNode)
							pTreeNode->Expend(!bExpend);
						//3.重新计算坐标
						CalcNodeRect();
					}
					m_pItemSel = pTreeNode;
					InvalidBounds();
					return S_OK;
				}
			}
		}
			break;
		case WM_MOUSEMOVE:
		{
			POINT pt;
			pt.x = LOWORD(lParam);
			pt.y = HIWORD(lParam);
			if (HitTest(pt))
			{
				CVLTree* pTreeNode = FindNodeByPoint(pt);
				if (pTreeNode)
				{
					m_pItemOver = pTreeNode;
					InvalidBounds();
				}		
				return S_OK;
			}
		}
			break;
	}
	return S_FALSE;
}
CVLTree* CQUITree::FindNodeByPoint(POINT pt, CVLTree* pNode)
{
	CVLTree* pFindNode = NULL;
	CVLTree* pTreeNode = NULL;
	if (pNode == NULL)
		pTreeNode = m_pRoot->GetFirstChild();
	else
		pTreeNode = pNode;
	while (pTreeNode)
	{
		CVLNode* pNode = pTreeNode->GetNode();
		RECT rc;
		rc.left = pNode->GetX();
		rc.top = pNode->GetY();
		rc.right = m_bound.right;
		rc.bottom = rc.top + pNode->GetHeight();
		if (PtInRect(&rc, pt))
		{//找到了
			pFindNode = pTreeNode;
			break;
		}
		//如果展开了，子节点也要展开
		if (pTreeNode->IsExpend()&&pTreeNode->GetFirstChild())
			pFindNode = FindNodeByPoint(pt,pTreeNode->GetFirstChild());
		if (pFindNode)
			break;
		pTreeNode = pFindNode->GetNextNode(pTreeNode);
	}
	return pFindNode;
}
void CQUITree::CalcNodeRect()
{
	int y = m_bound.top;
	
	CalcNodeRect(m_pRoot->GetFirstChild(), y);
	m_iLastY = y;
}
/*
返回值:返回TRUE，代表结束遍历
*/
BOOL CQUITree::CalcNodeRect(CVLTree* pTreeNode, int& y)
{
	BOOL bRet = FALSE;
	CVLTree* pChild = pTreeNode;
	while (pChild)
	{
		pChild->GetNode()->SetY(y);
		y += m_iItemHeight;
		//遍历展开节点的子节点
		if (pChild->IsExpend())
		   CalcNodeRect(pChild->GetFirstChild(), y);
		
		pChild = pTreeNode->GetNextNode(pChild);
	}
	return bRet;
}