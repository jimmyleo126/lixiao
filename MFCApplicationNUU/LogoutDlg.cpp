// LogoutDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplicationNUU.h"
#include "LogoutDlg.h"
#include "afxdialogex.h"
#include "InputXhDlg.h"
#include "nuu_mainbus.h"


// CLogoutDlg 对话框

IMPLEMENT_DYNAMIC(CLogoutDlg, CDialogEx)

CLogoutDlg::CLogoutDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LOGOUT_DIALOG, pParent)
{

}

CLogoutDlg::~CLogoutDlg()
{
}

void CLogoutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLogoutDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDCANCEL, &CLogoutDlg::OnBnClickedCancel)
END_MESSAGE_MAP()

BOOL CLogoutDlg::OnInitDialog()
{
	SetTimer(1, 2000, NULL);
	/*CString strBmpPath = TEXT("./image/checkout.jpg");
	CImage img;
	img.Load(strBmpPath);
	MoveWindow(0, 0, img.GetWidth(), img.GetHeight());
	CBitmap bmpTmp;
	bmpTmp.Attach(img.Detach());
	m_bkBrush.CreatePatternBrush(&bmpTmp);*/



	m_Font.CreatePointFont(250, _T("微软雅黑"), NULL);
	GetDlgItem(IDCANCEL)->SetFont(&m_Font);

	OnFull();

	

	return TRUE;
}

void CLogoutDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CRect rc;
		GetWindowRect(&rc);
		CImage mImage;
		if (mImage.Load(TEXT("./image/checkout.jpg")) == S_OK)
		{
			//这里让图片绘制区域和窗口大小一致
			mImage.Draw(GetDC()->GetSafeHdc(), CRect(0, 0, rc.Width(), rc.Height()));
		}
		CDialogEx::OnPaint();
	}
}

//监听发送消息，用来捕获ctrl + D按键，打开输入学号输入框
BOOL CLogoutDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
		return TRUE;
	if (::GetAsyncKeyState(VK_CONTROL) && pMsg->message == WM_KEYDOWN && pMsg->wParam == 'D')
	{
		CInputXhDlg inputxhDlg;
		INT_PTR nRes;
		ControlReadThread(0);
		nRes = inputxhDlg.DoModal();
		CString xh = inputxhDlg.m_Xh;
		int a = 0;

		if (IDCANCEL == nRes)
		{
			a = 1;
		}
		else if (IDOK == nRes)
		{
			LogOutSchool((LPCSTR)(xh));
		}
		ControlReadThread(1);
		return TRUE;
	}
	else
		return CDialog::PreTranslateMessage(pMsg);
}

void CLogoutDlg::OnTimer(UINT nID)
{
	extern BOOL TimeFlag;
	//用来定时的一个变量，
	extern int TimeCount;
	if (TimeFlag)
	{
		TimeFlag = FALSE;
		TimeCount = 0;
		OnBnClickedCancel();
	}
}

void CLogoutDlg::OnFull()
{
	//设置全屏显示标识
	m_bFullScreen = !m_bFullScreen;
	LONG style = ::GetWindowLong(this->m_hWnd, GWL_STYLE);
	if (m_bFullScreen)//全屏显示
	{
		style &= ~(WS_DLGFRAME | WS_THICKFRAME);
		SetWindowLong(this->m_hWnd, GWL_STYLE, style);
		this->ShowWindow(SW_SHOWMAXIMIZED);
		CRect rect;
		this->GetWindowRect(&rect);
		::SetWindowPos(this->m_hWnd, HWND_NOTOPMOST,
			rect.left - 1, rect.top - 1, rect.right - rect.left + 3, rect.bottom - rect.top + 3,
			SWP_FRAMECHANGED);
	}
	else
	{
		style |= WS_DLGFRAME | WS_THICKFRAME;
		SetWindowLong(this->m_hWnd, GWL_STYLE, style);
		this->ShowWindow(SW_NORMAL);
	}
}



// CLogoutDlg 消息处理程序


void CLogoutDlg::OnBnClickedCancel()
{
	//g_tipfeeandbookflag变量用来判定是否改返回的
	extern  BOOL g_tipfeeandbookflag;
	if(!g_tipfeeandbookflag)
		CDialogEx::OnCancel();
}
