#ifndef UIELEMENT_H_
#define UIELEMENT_H_
#include"QUISkin.h"
#include<gdiplus.h>

class CUIElement;
class IQUIEventCallBack
{
public:
	virtual void OnNotifyCmd(CUIElement* pElement) = 0;//��ť�¼�
};
/*
����Ԫ�ػ���
*/
class QUISKIN_API CUIElement
{
public:
	CUIElement();
	virtual~CUIElement();
public:
	/*
	����:��������Ԫ��
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
	���ܣ����ؼ�һ���������Լ���ص�ϵͳ��Ϣ
	����ֵ��
			S_OK���ӿؼ��ɹ��������Ϣ���������������ٴ���
			S_FALSE:����Ϣ���ӿؼ��޹أ��������������ڴ���
	*/
	virtual LRESULT OnControlMessage(UINT message,WPARAM wParam,LPARAM lParam);
	/*
	����:�ػ����ǵ�Ԫ������
	*/
	virtual void InvalidBounds();
	//�ж������Ƿ���Ԫ��������
	virtual BOOL HitTest(POINT pt);
	BOOL IsVisible();
protected:
	

	virtual void DrawBkColor(Gdiplus::Graphics& grx);
	virtual void DrawBkImage(Gdiplus::Graphics& grx);
	virtual void DrawStatusImage(Gdiplus::Graphics& grx);//��������д
	virtual void DrawText(Gdiplus::Graphics& grx);
	virtual void DrawBorder(Gdiplus::Graphics& grx);
protected:
	HWND m_hHostWnd;//��������
	
	RECT      m_bound;//����λ��
	StdString m_strID;//ID��
	BOOL      m_bVisible;//�Ƿ�ɼ�
	BOOL      m_bEnable;//�Ƿ����

	StdString m_strCaption;//����
	DWORD     m_dwBackColor;//������ɫ
	StdString m_strBgImage;//����ͼ
	DWORD     m_dwBorderColor;//�߿���ɫ
	DWORD     m_dwBorder;//�߿�

	DWORD     m_dwTextColor;//�ı���ɫ
	StdString m_strFont;//����
	DWORD     m_dwFontSize;//�����С
	StdString m_strToolTips;

	IQUIEventCallBack* m_pCallBack;
};


#endif