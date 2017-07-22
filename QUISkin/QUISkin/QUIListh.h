#ifndef QUILIST_H_
#define QUILIST_H_
#include"UIElement.h"
#include"QUIScrollBar.h"
#include<map>

class CQUIList;
class QUISKIN_API CListColunm
{
	//列头
	typedef struct _tagColunm
	{
		std::basic_string<TCHAR> name;//列名
		int iWidth;//宽度
		std::basic_string<TCHAR> icon;//图标
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
	功能:鼠标移到相邻两列头的中间位置，改变光标为拖动状态
	*/
	BOOL OnMouseMove(POINT pt);

	/*
	功能:鼠标左键按下设置拖拽状态
	*/
	BOOL SetDrag(POINT pt);
	/*
	功能:终止拖拽
	*/
	BOOL CancleDrag();
protected:
	/*
	功能:改变指定列额的宽度
	参数:
	     @iCol:列
		 @iSubWidth:在原宽度基础上要改变的宽度
	*/
	void SubColWidth(int iCol, int iSubWidth);
private:
	TColMap   m_tCols;
	DWORD     m_dwBackColor;//列头背景
	int       m_iHeight;//列头高度
	CQUIList* m_pParent;//

	HCURSOR   m_hOldCursor;//保存旧的光标

	BOOL      m_bDrag;//开启拖拽状态标识

	int       m_iCurCol;//获取当前列

	POINT     m_tDragPt;

};
//行
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
	功能:初始化列头
	*/
	void InitColunm(int iHeight, DWORD dwBackColor);
	/*
	功能:插入列头项
	*/
	void InsertColunm(int iIndex, const TCHAR* szName, int iWidth, const TCHAR* szIcon = NULL);
    
	void SetItemBackColor(DWORD dwColor1, DWORD dwColor2);
	void SetItemHeight(int iHeight1, int iHeight2);


	/*
	功能：插入一行
	*/
	void InsertItem(int iItem, const TCHAR* szName, const TCHAR* szIcon = NULL);
	/*
	功能:设置某一列的文本
	*/
	void SetItemText(int iItem, int iSubItem, const TCHAR* szName, const TCHAR* szIcon=NULL);

	virtual LRESULT OnControlMessage(UINT message, WPARAM wParam, LPARAM lParam);
public:
	void DrawText(Gdiplus::Graphics& grx);
	/*
	功能:根据鼠标坐标查找行
	参数:
	    @pt：鼠标坐标
	返回值:返回鼠标在哪一行上面，没找到返回-1
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

	int   m_iHeight1;//正常情况下的行高
	int   m_iHeight2;//鼠标移上去的行高

	int   m_iItemCurrent;//当前选择项
	int   m_iItemOver;//当前鼠标移动上去的项

	CQUIScrollBar m_VscrollBar;//垂直滚动条
};










#endif