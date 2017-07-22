#ifndef QUITREE_H_
#define QUITREE_H_
#include"UIElement.h"

/*
结点数据
*/
class QUISKIN_API CVLNode
{
public:
	CVLNode();
	~CVLNode();
public:
	void SetName(const TCHAR* szName);
	const TCHAR* GetName();
	void SetIcon(const TCHAR* szIcon);
	const TCHAR* GetIcon();
	void SetX(int x){ m_iLeft = x; };
	void SetY (int y){ m_iTop = y; };
	int GetX(){ return m_iLeft; };
	int GetY(){ return m_iTop; };
	void SetHeight(int iHeight);
	int GetHeight(){ return m_iHeight; };
	void SetWidth(int iWidth);
	int GetWidth(){ return m_iWidth; };
protected:
	std::basic_string<TCHAR> m_strName;
	std::basic_string<TCHAR> m_strIcon;
	//父节点没展开的话，x和y是无效的，每次展开，我们去更新它的一个实时坐标
	int m_iLeft;//x
	int m_iTop;//y
	int m_iHeight;//高度
	int m_iWidth;//宽度
};
/*
树型结点的类
*/
class QUISKIN_API CVLTree
{
public:
	CVLTree(CVLNode* pNode=NULL);
	~CVLTree();

public:
	/*
	功能:插入子节点
	参数:
	     @pNode:是要插入新节点数据
		 @pInsNode:新节点插入到这个节点后面
		  如果pInsNode为NULL，默认插入最末尾
	返回值:成功返回新插入的节点，失败返回0
	*/
	CVLTree* InsertChildNode(CVLNode* pNode, CVLTree* pInsNode=NULL);

	int GetChildCount();
	/*
	功能:把子节点跟父节点脱离关系
	*/
	CVLTree* DetachChildNode();
	/*
	功能:附加子节点
	参数:
	     @pTreeNode:链表头
		 @pInsNode:新节点插入到这个节点后面
		  如果pInsNode为NULL，默认插入最末尾
	*/
	void     AttachChildNode(CVLTree* pTreeNode,CVLTree* pInsNode=NULL);
	/*
	功能：查找子节点的尾节点
	*/
	CVLTree* GetTailChild();
	/*
	功能:获取子节点的首节点
	*/
	CVLTree* GetFirstChild();
	/*
	功能：获取下一个子节点
	*/
	CVLTree* GetNextNode(CVLTree* pTreeNode);
	/*
	功能：获取节点数据
	*/
	CVLNode* GetNode();
	/*
	功能：获取父节点
	*/
	CVLTree* GetParentNode();
	int GetLevel();
	void Expend(BOOL bExpend);
	BOOL IsExpend();
protected:
	void CalcLevel(CVLTree* pTreeNode);
protected:
	void ReleaseChild();
protected:
	CVLNode*    m_pNode;//结点数据

	CVLTree*    m_pParent;//父结点
	CVLTree*    m_pNext;//下一个兄弟结点
	CVLTree*    m_pPre;//前一个兄弟结点

	CVLTree*    m_pFirstChild;//第一个子结点
	CVLTree*    m_pTailChild;//最后一个子结点

	int         m_iChildCounts;//子结点个数

	int         m_iLevel;//深度
	BOOL        m_bExpend;//是否展开
};


/*
树形控件的UI
*/
class QUISKIN_API CQUITree :public CUIElement
{
public:
	CQUITree();
	~CQUITree();
public:
	void SetItemHeight(int iItemHeight);
	CVLTree* Insert(const TCHAR* szName, const TCHAR* szIcon, CVLTree* pParent = NULL);
	virtual void DrawText(Gdiplus::Graphics& grx);
	void Expend(CVLTree* pTreeNode, BOOL bExpend=TRUE);
public:
	virtual LRESULT OnControlMessage(UINT message, WPARAM wParam, LPARAM lParam);
protected:
	void DrawItems(Gdiplus::Graphics& grx,CVLTree* pTreeNode);
	void DrawItem(Gdiplus::Graphics& grx, CVLNode* pNode);
	CVLTree* FindNodeByPoint(POINT pt, CVLTree* pNode=NULL);
	void CalcNodeRect();
	BOOL CalcNodeRect(CVLTree* pTreeNode, int& y);
private:
	CVLTree*  m_pRoot;//树的根节点

	int       m_iItemHeight;

	int       m_iLastY;//记录下一次插入节点的Y坐标

	DWORD     m_dwItemOverColor;//鼠标移动上去的颜色
	DWORD     m_dwItemSelColor;//当前选择项的背景
	CVLTree*  m_pItemOver;
	CVLTree*  m_pItemSel;
};











#endif