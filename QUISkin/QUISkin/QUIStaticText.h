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
	UINT m_uAlign;//������뷽ʽ
	UINT m_uVlign;//������뷽ʽ
	DWORD m_dwLightColor;//������ʾ���ı���ɫ

	BOOL m_bLightColor;//�Ƿ���Ҫ������ʾ

	RECT m_rcText;//�ı�����
};












#endif