#ifndef QUISTATICTEXT_H_
#define QUISTATICTEXT_H_
#include"UIElement.h"

class QUISKIN_API CQUIStaticText :public CUIElement
{
public:
	CQUIStaticText();
	~CQUIStaticText();
public:
	void SetAlign(UINT uAStyle);
	void SetVlign(UINT uVStyle);
	void SetLightColor(DWORD dwColor);

	virtual void DrawText(Gdiplus::Graphics& grx);

	virtual LRESULT OnControlMessage(UINT message, WPARAM wParam, LPARAM lParam);

	virtual BOOL HitTest(POINT pt);
private:
	UINT m_uAlign;//横向对齐方式
	UINT m_uVlign;//竖向对齐方式
	DWORD m_dwLightColor;//高亮显示的文本颜色

	BOOL m_bLightColor;//是否需要高亮显示

	RECT m_rcText;//文本区域
};












#endif