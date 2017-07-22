#ifndef UIELEMENT_H_
#define UIELEMENT_H_
#include"QUISkin.h"
#include<gdiplus.h>

class CUIElement;
class IQUIEventCallBack
{
public:
	virtual void OnNotifyCmd(CUIElement* pElement) = 0;//按钮事件
};
/*
界面元素基类
*/
class QUISKIN_API CUIElement
{
public:
	CUIElement();
	virtual~CUIElement();
public:
	/*
	功能:创建界面元素
	*/
	virtual void Create(const TCHAR* szEleID,const RECT& rc,HWND hHostWnd,IQUIEventCallBack* pCallBack);
	void SetCaption(const TCHAR* szCaption);
	const TCHAR* GetCaption();
	void SetBound(const RECT& rc);
	void GetBound(RECT* lpRect);
	void SetID(const TCHAR* szID);
	const TCHAR* GetID();
	void SetVisible(BOOL bVisible);
	void SetEnable(BOOL bEnable);
	void SetBackColor(DWORD dwColor);
	void SetToolText(const TCHAR* szToolText);
	void SetBorderSize(DWORD dwBorderSize);
	void SetBorderColor(DWORD dwBorderColor);
	void SetBgImage(const TCHAR* szImage);
	void SetHostWnd(HWND hWnd);
	HWND GetHostWnd();

	void SetFontSize(DWORD dwFontSize);
	DWORD GetFontSize(){ return m_dwFontSize; };
	void SetFamily(const TCHAR* szFamily);
	const TCHAR* GetFamily(){ return m_strFont.c_str(); };
	void SetTextColor(DWORD dwTxtColor);
	DWORD GetTextColor(){ return m_dwTextColor; };
public:
	virtual void DoPaint(Gdiplus::Graphics& grx);
	/*
	功能：给控件一个处理与自己相关的系统消息
	返回值：
			S_OK：子控件成功处理此消息，宿主窗口无需再处理
			S_FALSE:此消息与子控件无关，继续由宿主窗口处理
	*/
	virtual LRESULT OnControlMessage(UINT message,WPARAM wParam,LPARAM lParam);
	/*
	功能:重绘我们的元素区域
	*/
	virtual void InvalidBounds();
	//判断鼠标点是否在元素区域内
	virtual BOOL HitTest(POINT pt);
	BOOL IsVisible();
protected:
	

	virtual void DrawBkColor(Gdiplus::Graphics& grx);
	virtual void DrawBkImage(Gdiplus::Graphics& grx);
	virtual void DrawStatusImage(Gdiplus::Graphics& grx);//给子类重写
	virtual void DrawText(Gdiplus::Graphics& grx);
	virtual void DrawBorder(Gdiplus::Graphics& grx);
protected:
	HWND m_hHostWnd;//宿主窗体
	
	RECT      m_bound;//坐标位置
	StdString m_strID;//ID号
	BOOL      m_bVisible;//是否可见
	BOOL      m_bEnable;//是否禁用

	StdString m_strCaption;//标题
	DWORD     m_dwBackColor;//背景颜色
	StdString m_strBgImage;//背景图
	DWORD     m_dwBorderColor;//边框颜色
	DWORD     m_dwBorder;//边框

	DWORD     m_dwTextColor;//文本颜色
	StdString m_strFont;//字体
	DWORD     m_dwFontSize;//字体大小
	StdString m_strToolTips;

	IQUIEventCallBack* m_pCallBack;
};


#endif