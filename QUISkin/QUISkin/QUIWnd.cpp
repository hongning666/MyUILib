#include"stdafx.h"
#include"QUIWnd.h"


CQUIWnd::CQUIWnd()
{
	m_hWnd = NULL;
	m_hInst = NULL;
	m_hRgn = NULL;
	m_bDrag = FALSE;
}

CQUIWnd::~CQUIWnd()
{

}

HWND CQUIWnd::Create(HWND hWndParent, LPCTSTR lpszCaption, const RECT rc,DWORD dwStyle, HINSTANCE hInst)
{
	m_hInst = hInst;
	if (!RegisterWndClass())
	  return NULL;
	dwStyle |= WS_CLIPSIBLINGS;
	dwStyle |= WS_CLIPCHILDREN;
	m_hWnd = CreateWindow(GetWndClassName(), lpszCaption, dwStyle, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, hWndParent, NULL, hInst, this);
	return m_hWnd ;
}

BOOL CQUIWnd::RegisterWndClass()
{
	WNDCLASS wc = { 0 };
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hbrBackground =CreateSolidBrush(RGB(255,0,0)) ;
	wc.hCursor = LoadCursor(NULL,IDC_ARROW);
	wc.hIcon = NULL;
	wc.hInstance = m_hInst;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = GetWndClassName();
	wc.style = CS_VREDRAW | CS_HREDRAW;
	wc.lpszMenuName = NULL;
	return 0 != RegisterClass(&wc);//注册成功返回0
}

LRESULT CALLBACK CQUIWnd::WndProc(HWND hWnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	//把窗口过程函数绑定到窗口实例
	CQUIWnd* pThis = NULL;
	if (msg == WM_NCCREATE)
	{
		LPCREATESTRUCT lpcs = (LPCREATESTRUCT)lparam;
		pThis = (CQUIWnd*)lpcs->lpCreateParams;
		pThis->m_hWnd = hWnd;
		::SetWindowLongPtr(hWnd, GWLP_USERDATA, (LPARAM)pThis);
	}
	else
	{
		pThis = (CQUIWnd*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
	}
	if (pThis != NULL)
		return pThis->HandleMessage(msg, wparam, lparam);
	else
	    return DefWindowProc(hWnd, msg, wparam, lparam);
}

LPCTSTR CQUIWnd::GetWndClassName()
{
	return L"QUIWnd";
}

LRESULT CQUIWnd::HandleMessage(UINT message, WPARAM wparam, LPARAM lparam)
{
	switch (message)
	{
	case WM_SIZE:
		OnSize(wparam, lparam);
		break;
	case WM_CREATE:
		OnCreate(wparam, lparam);
		break;
	case WM_PAINT:
		OnPaint(wparam, lparam);
		break;
	case WM_LBUTTONDOWN:
		OnLButtonDown(wparam, lparam);
		break;
	case WM_LBUTTONUP:
		OnLButtonUp(wparam, lparam);
		break;
	case WM_MOUSEMOVE:
		OnMouseMove(wparam, lparam);
		break;
	case WM_CLOSE://窗口关闭消息，这个时候窗口没有销毁
		OnClose(wparam, lparam);
		break;
	case WM_DESTROY:
		OnDestoryWindow(wparam, lparam);
		break;
	case WM_ACTIVATE:
		OnActivate(wparam, lparam);
		break;
	case WM_KILLFOCUS:
		OnKillFocus(wparam, lparam);
		break;
	case WM_SETFOCUS:
		OnSetFocus(wparam, lparam);
		break;
	case WM_SHOWWINDOW:
		OnShowWindow(wparam, lparam);
		break;
	case WM_KEYDOWN:
		OnKeyDown(wparam, lparam);
		break;
	/*case WM_CTLCOLOREDIT:
		return (LRESULT)OnCtrlColorEdit(wparam, lparam);
		break;*/
	}
	return DefWindowProc(m_hWnd,message,wparam,lparam);
}

void CQUIWnd::SetIcon(UINT iRes)
{
	//1.加载图标
	int icx = GetSystemMetrics(SM_CXICON);
	int icy = GetSystemMetrics(SM_CYICON);
	HICON hIcon = (HICON)LoadImage(m_hInst, MAKEINTRESOURCE(iRes), IMAGE_ICON, icx, icy, LR_DEFAULTCOLOR);
	//2.设置图标
	SendMessage(m_hWnd, WM_SETICON, (WPARAM)TRUE, (LPARAM)hIcon);
}
void CQUIWnd::SetMiniSize(int iWidth, int iHeight)
{
	m_iMinWidth = iWidth;
	m_iMinHeight = iHeight;
}
void CQUIWnd::OnSize(WPARAM wparam, LPARAM lparam)
{
	
}
void CQUIWnd::SetWindowRgn(POINT* lpPoint, int count)
{
	m_hRgn = CreatePolygonRgn(lpPoint, count, ALTERNATE);
}
void CQUIWnd::OnCreate(WPARAM wparam, LPARAM lparam)
{
	if (m_hRgn)
		::SetWindowRgn(m_hWnd, m_hRgn, TRUE);
}
void CQUIWnd::SetDragRect(const RECT& rc)
{
	m_tDragRc.left = rc.left;
	m_tDragRc.bottom = rc.bottom;
	m_tDragRc.right = rc.right;
	m_tDragRc.top = rc.top;
}
void CQUIWnd::OnLButtonDown(WPARAM wparam, LPARAM lparam)
{
	//1.获取鼠标按下的坐标
	POINT pt;
	::GetCursorPos(&pt);
	m_tPt = pt;
	//2.把坐标转化为窗口坐标
	ScreenToClient(m_hWnd, &pt);
	//3.判断坐标点是否在拖动区域
	if (!PtInRect(&m_tDragRc, pt))
		return;
	m_bDrag = TRUE;
	SetCapture(m_hWnd);//设置捕捉鼠标,即使鼠标不在窗口上面
}
void CQUIWnd::OnLButtonUp(WPARAM wparam, LPARAM lparam)
{
	if (m_bDrag)
	{//退出拖动状态
		m_bDrag = FALSE;
		ReleaseCapture();
	}
}
void CQUIWnd::OnMouseMove(WPARAM wparam, LPARAM lparam)
{
	if (!m_bDrag)
		return;
	POINT pt;
	::GetCursorPos(&pt);

	int iLeft = pt.x - m_tPt.x;
	int iTop = pt.y - m_tPt.y;
	m_tPt = pt;
	RECT rcWnd;
	GetWindowRect(&rcWnd);

	//计算窗口新坐标
	rcWnd.left += iLeft;
	rcWnd.right += iLeft;
	rcWnd.top += iTop;
	rcWnd.bottom += iTop;
	//移动窗口
	::MoveWindow(m_hWnd, rcWnd.left, rcWnd.top, rcWnd.right - rcWnd.left, rcWnd.bottom - rcWnd.top, TRUE);
}
void CQUIWnd::ShowWindow(UINT nCmd)
{
	::ShowWindow(m_hWnd, nCmd);
}
void CQUIWnd::UpdateWindow()
{
	::UpdateWindow(m_hWnd);
}
void CQUIWnd::OnClose(WPARAM wparam, LPARAM lparam)
{
	DestroyWindow(m_hWnd);
}
void CQUIWnd::OnDestoryWindow(WPARAM wparam, LPARAM lparam)
{

}
void CQUIWnd::OnPaint(WPARAM wparam, LPARAM lparam)
{
	PAINTSTRUCT pcs;
	HDC hdc = BeginPaint(m_hWnd, &pcs);

	RECT rc;
	GetClientRect(&rc);
	//gdi+的双缓冲绘制,先把界面所有的元素在内存里面绘制一张图片
	//绘制完之后，把缓冲图片一次性绘制到窗口上面

	//内存位图
	Gdiplus::Bitmap membmp(rc.right - rc.left, rc.bottom - rc.top);

	//根据内存位图生成一个内存绘图器
	Gdiplus::Graphics* pGrx = Gdiplus::Graphics::FromImage(&membmp);
	if (m_szBground.length())
	{
		//把背景图绘制在内存绘图器上面
		Gdiplus::Image im(m_szBground.c_str());
		pGrx->DrawImage(&im, Gdiplus::Rect(rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top));
	}
	//把界面元素绘制在内存绘图器上面
	OnPaintControl(*pGrx);//绘制元素

	//把内存位图一次性绘制在窗口上面
	Gdiplus::Graphics grx(hdc);
	grx.DrawImage(&membmp, Gdiplus::Rect(0, 0, membmp.GetWidth(), membmp.GetHeight()));

	delete pGrx;
	pGrx = NULL;

	::EndPaint(m_hWnd, &pcs);
}
void CQUIWnd::MoveWindow(const RECT& rc,BOOL bRepaint)
{
	::MoveWindow(m_hWnd, rc.left, rc.top, rc.right - rc.left, rc.bottom - rc.top, bRepaint);
}
void CQUIWnd::OnActivate(WPARAM wparam, LPARAM lparam)
{

}
void CQUIWnd::OnKillFocus(WPARAM wparam, LPARAM lparam)
{

}
void CQUIWnd::OnSetFocus(WPARAM wparam, LPARAM lparam)
{

}
void  CQUIWnd::EnableWindow(BOOL bEnable)
{
	::EnableWindow(m_hWnd, bEnable);
}
void CQUIWnd::OnShowWindow(WPARAM wparam, LPARAM lparam)
{

}
void CQUIWnd::OnKeyDown(WPARAM wparam, LPARAM lparam)
{

}
void CQUIWnd::SetBground(const StdString& strFile)
{
	m_szBground = strFile;
}
BOOL CQUIWnd::GetClientRect(RECT* rc)
{
	if (m_hWnd == nullptr)
		return FALSE;
	::GetClientRect(m_hWnd, rc);
	return TRUE;
}
BOOL CQUIWnd::GetWindowRect(RECT* rc)
{
	if (m_hWnd == nullptr)
		return FALSE;
	::GetWindowRect(m_hWnd, rc);
	return TRUE;
}
void CQUIWnd::OnPaintControl(Gdiplus::Graphics& grx)
{

}
HBRUSH CQUIWnd::OnCtrlColorEdit(WPARAM wparam, LPARAM lparam)
{
	HWND hEdit = (HWND)lparam;
	HDC hdc = (HDC)wparam;
	SetBkMode(hdc, TRANSPARENT);
	SetBkColor(hdc, RGB(255, 0, 0));
	return (HBRUSH)CreateSolidBrush(RGB(255, 0, 0));
}