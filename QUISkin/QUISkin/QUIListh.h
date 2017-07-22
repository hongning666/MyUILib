#ifndef QUILIST_H_
#define QUILIST_H_
#include"UIElement.h"
#include"QUIScrollBar.h"
#include<map>

class CQUIList;
class QUISKIN_API CListColunm
{
	//��ͷ
	typedef struct _tagColunm
	{
		std::basic_string<TCHAR> name;//����
		int iWidth;//���
		std::basic_string<TCHAR> icon;//ͼ��
	}TColunm;
	typedef std::map<int, TColunm> TColMap;
public:
	CListColunm(CQUIList* pParent);
	~CListColunm();
public:
	void Init(int iHeight, DWORD dwBackColor);
	void Insert(int iIndex, const TCHAR* szName, int iWidth, const TCHAR* szIcon = NULL);

	void Draw(Gdiplus::Graphics& grx);
	int GetHeight(){ return m_iHeight; };
	int GetCols(){ return m_tCols.size(); };
	int GetColunmWidth(int iCol);
	/*
	����:����Ƶ���������ͷ���м�λ�ã��ı���Ϊ�϶�״̬
	*/
	BOOL OnMouseMove(POINT pt);

	/*
	����:����������������ק״̬
	*/
	BOOL SetDrag(POINT pt);
	/*
	����:��ֹ��ק
	*/
	BOOL CancleDrag();
protected:
	/*
	����:�ı�ָ���ж�Ŀ��
	����:
	     @iCol:��
		 @iSubWidth:��ԭ��Ȼ�����Ҫ�ı�Ŀ��
	*/
	void SubColWidth(int iCol, int iSubWidth);
private:
	TColMap   m_tCols;
	DWORD     m_dwBackColor;//��ͷ����
	int       m_iHeight;//��ͷ�߶�
	CQUIList* m_pParent;//

	HCURSOR   m_hOldCursor;//����ɵĹ��

	BOOL      m_bDrag;//������ק״̬��ʶ

	int       m_iCurCol;//��ȡ��ǰ��

	POINT     m_tDragPt;

};
//��
class QUISKIN_API CListItem
{
	typedef struct _tagItem
	{
		int iItem;
		std::basic_string<TCHAR> name;
		std::basic_string<TCHAR> icon;
	}TItem;
	typedef std::map<int, TItem> TItemMap;
public:
	CListItem(CQUIList* pParent);
	~CListItem();
public:
	void Insert(int iItem, const TCHAR* szName, const TCHAR* szIcon = NULL);
	void Draw(Gdiplus::Graphics& grx, int iItem, const RECT& rc);
protected:
	CQUIList* m_pParent;
	TItemMap m_tItems;
};

class QUISKIN_API CQUIList :public CUIElement, public IScrollbarCallback
{
	typedef std::map<int, CListItem*> TListItemMap;
public:
	CQUIList();
	~CQUIList();
public:
	virtual void Create(const TCHAR* szEleID, const RECT& rc, HWND hHostWnd, IQUIEventCallBack* pCallBack);
	/*
	����:��ʼ����ͷ
	*/
	void InitColunm(int iHeight, DWORD dwBackColor);
	/*
	����:������ͷ��
	*/
	void InsertColunm(int iIndex, const TCHAR* szName, int iWidth, const TCHAR* szIcon = NULL);
    
	void SetItemBackColor(DWORD dwColor1, DWORD dwColor2);
	void SetItemHeight(int iHeight1, int iHeight2);


	/*
	���ܣ�����һ��
	*/
	void InsertItem(int iItem, const TCHAR* szName, const TCHAR* szIcon = NULL);
	/*
	����:����ĳһ�е��ı�
	*/
	void SetItemText(int iItem, int iSubItem, const TCHAR* szName, const TCHAR* szIcon=NULL);

	virtual LRESULT OnControlMessage(UINT message, WPARAM wParam, LPARAM lParam);
public:
	void DrawText(Gdiplus::Graphics& grx);
	/*
	����:����������������
	����:
	    @pt���������
	����ֵ:�����������һ�����棬û�ҵ�����-1
	*/
	int FindItemByPoint(const POINT& pt);

	void SetVScrollImage(const TCHAR* szImage);
protected:
	void OnHScrollBar(const TScrollInfo* pScrollInfo);
	void OnVScrollBar(const TScrollInfo* pScrollInfo);

	void DrawItems(Gdiplus::Graphics& grx);
protected:
	CListColunm  m_Colunm;
	TListItemMap m_tListItem;

	DWORD m_dwBackColor1;
	DWORD m_dwBackColor2;

	int   m_iHeight1;//��������µ��и�
	int   m_iHeight2;//�������ȥ���и�

	int   m_iItemCurrent;//��ǰѡ����
	int   m_iItemOver;//��ǰ����ƶ���ȥ����

	CQUIScrollBar m_VscrollBar;//��ֱ������
};










#endif