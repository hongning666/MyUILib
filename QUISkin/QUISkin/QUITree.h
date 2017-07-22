#ifndef QUITREE_H_
#define QUITREE_H_
#include"UIElement.h"

/*
�������
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
	//���ڵ�ûչ���Ļ���x��y����Ч�ģ�ÿ��չ��������ȥ��������һ��ʵʱ����
	int m_iLeft;//x
	int m_iTop;//y
	int m_iHeight;//�߶�
	int m_iWidth;//���
};
/*
���ͽ�����
*/
class QUISKIN_API CVLTree
{
public:
	CVLTree(CVLNode* pNode=NULL);
	~CVLTree();

public:
	/*
	����:�����ӽڵ�
	����:
	     @pNode:��Ҫ�����½ڵ�����
		 @pInsNode:�½ڵ���뵽����ڵ����
		  ���pInsNodeΪNULL��Ĭ�ϲ�����ĩβ
	����ֵ:�ɹ������²���Ľڵ㣬ʧ�ܷ���0
	*/
	CVLTree* InsertChildNode(CVLNode* pNode, CVLTree* pInsNode=NULL);

	int GetChildCount();
	/*
	����:���ӽڵ�����ڵ������ϵ
	*/
	CVLTree* DetachChildNode();
	/*
	����:�����ӽڵ�
	����:
	     @pTreeNode:����ͷ
		 @pInsNode:�½ڵ���뵽����ڵ����
		  ���pInsNodeΪNULL��Ĭ�ϲ�����ĩβ
	*/
	void     AttachChildNode(CVLTree* pTreeNode,CVLTree* pInsNode=NULL);
	/*
	���ܣ������ӽڵ��β�ڵ�
	*/
	CVLTree* GetTailChild();
	/*
	����:��ȡ�ӽڵ���׽ڵ�
	*/
	CVLTree* GetFirstChild();
	/*
	���ܣ���ȡ��һ���ӽڵ�
	*/
	CVLTree* GetNextNode(CVLTree* pTreeNode);
	/*
	���ܣ���ȡ�ڵ�����
	*/
	CVLNode* GetNode();
	/*
	���ܣ���ȡ���ڵ�
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
	CVLNode*    m_pNode;//�������

	CVLTree*    m_pParent;//�����
	CVLTree*    m_pNext;//��һ���ֵܽ��
	CVLTree*    m_pPre;//ǰһ���ֵܽ��

	CVLTree*    m_pFirstChild;//��һ���ӽ��
	CVLTree*    m_pTailChild;//���һ���ӽ��

	int         m_iChildCounts;//�ӽ�����

	int         m_iLevel;//���
	BOOL        m_bExpend;//�Ƿ�չ��
};


/*
���οؼ���UI
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
	CVLTree*  m_pRoot;//���ĸ��ڵ�

	int       m_iItemHeight;

	int       m_iLastY;//��¼��һ�β���ڵ��Y����

	DWORD     m_dwItemOverColor;//����ƶ���ȥ����ɫ
	DWORD     m_dwItemSelColor;//��ǰѡ����ı���
	CVLTree*  m_pItemOver;
	CVLTree*  m_pItemSel;
};











#endif