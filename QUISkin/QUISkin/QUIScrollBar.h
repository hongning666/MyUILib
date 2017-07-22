#ifndef QUISCROLLBAR_H_
#define QUISCROLLBAR_H_
#include"UIElement.h"

enum enScrollBarStyle
{
	E_ScrollBar_HBar=1,//横向滚动条
	E_ScrollBar_VBar=2,//竖向滚动条
};

enum enScrollBarState
{
	E_ScrollBarState_Normal = 1,
	E_ScrollBarState_Over=2,
	E_ScrollBarState_Down=3,
	E_ScrollBarState_Disable=4,
};
//做一个回调接口
typedef struct _tagScrollInfo
{
	int iPos;//当前的位置

	int iMaxPos;//最大
}TScrollInfo;
class IScrollbarCallback
{
public:
	virtual void OnHScrollBar(const TScrollInfo* pScrollInfo) = 0;
	virtual void OnVScrollBar(const TScrollInfo* pScrollInfo) = 0;
};

class QUISKIN_API CQUIScrollBar :public CUIElement
{
public:
	CQUIScrollBar(IScrollbarCallback* pCallback=NULL);
	~CQUIScrollBar();
public:
	void SetScrollBarStyle(enScrollBarStyle eBarStyle);
	enScrollBarStyle GetScrollBar();
	void SetStateImage(const TCHAR* szImage);
	void SetState(enScrollBarState eState);
	enScrollBarState GetState();
	virtual LRESULT OnControlMessage(UINT message, WPARAM wParam, LPARAM lParam);
protected:
	virtual void DrawStatusImage(Gdiplus::Graphics& grx);
	/*
	功能:绘制横向滚动条
	*/
	void DrawHScroll(Gdiplus::Graphics& grx);
	/*
	功能:绘制竖向滚动条
	*/
	void DrawVScroll(Gdiplus::Graphics& grx);
	/*
	功能：获取滑块左边的坐标
	*/
	int GetThumLeft();
	/*
	功能:获取滑块坐标
	*/
	void GetThumRect( RECT& rcThum);
	/*
	功能:获取左边/顶端按钮坐标
	*/
	void GetLeftBtnRect(RECT& rcBtn);
	/*
	功能：获取右边/底端按钮坐标
	*/
	void GetRightBtnRect(RECT& rcBtn);
public:
	void SetRang(int iRang);
	int GetRang();
	void SetPos(int iPos);
	int GetPos();
protected:
	enScrollBarStyle          m_eBarStyle;
	std::basic_string<TCHAR>  m_strStateImage;
	enScrollBarState          m_eState;

	int                       m_iRang;//滑动的范围
	int                       m_iScrollPos;//滑块当前位置 m_iScrollPos/m_iRang(百分比)
	BOOL                      m_bThumPress;//鼠标按下滑块

	IScrollbarCallback*       m_pCallBack;
};







#endif