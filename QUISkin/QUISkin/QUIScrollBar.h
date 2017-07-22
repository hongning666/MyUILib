#ifndef QUISCROLLBAR_H_
#define QUISCROLLBAR_H_
#include"UIElement.h"

enum enScrollBarStyle
{
	E_ScrollBar_HBar=1,//���������
	E_ScrollBar_VBar=2,//���������
};

enum enScrollBarState
{
	E_ScrollBarState_Normal = 1,
	E_ScrollBarState_Over=2,
	E_ScrollBarState_Down=3,
	E_ScrollBarState_Disable=4,
};
//��һ���ص��ӿ�
typedef struct _tagScrollInfo
{
	int iPos;//��ǰ��λ��

	int iMaxPos;//���
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
	����:���ƺ��������
	*/
	void DrawHScroll(Gdiplus::Graphics& grx);
	/*
	����:�������������
	*/
	void DrawVScroll(Gdiplus::Graphics& grx);
	/*
	���ܣ���ȡ������ߵ�����
	*/
	int GetThumLeft();
	/*
	����:��ȡ��������
	*/
	void GetThumRect( RECT& rcThum);
	/*
	����:��ȡ���/���˰�ť����
	*/
	void GetLeftBtnRect(RECT& rcBtn);
	/*
	���ܣ���ȡ�ұ�/�׶˰�ť����
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

	int                       m_iRang;//�����ķ�Χ
	int                       m_iScrollPos;//���鵱ǰλ�� m_iScrollPos/m_iRang(�ٷֱ�)
	BOOL                      m_bThumPress;//��갴�»���

	IScrollbarCallback*       m_pCallBack;
};







#endif