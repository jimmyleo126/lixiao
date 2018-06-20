// CancelDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplicationNUU.h"
#include "CancelDlg.h"
#include "afxdialogex.h"
#include "TipFeeAndBookDlg.h"


// CCancelDlg 对话框

IMPLEMENT_DYNAMIC(CCancelDlg, CDialogEx)

CCancelDlg::CCancelDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_CANCEL_DIALOG, pParent)
{
	
}

CCancelDlg::~CCancelDlg()
{
}

void CCancelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CCancelDlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDCANCEL, &CCancelDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


BOOL CCancelDlg::OnInitDialog()
{
	SetTimer(1, 2000, NULL);
	/*CString strBmpPath = TEXT("./image/studentmoney.jpeg");
	CImage img;
	img.Load(strBmpPath);
	CRect rc;
	GetWindowRect(&rc);
	MoveWindow(0, 0, img.GetWidth(), img.GetHeight());
	//MoveWindow(0, 0, rc.left, rc.bottom);
	CBitmap bmpTmp;
	bmpTmp.Attach(img.Detach());
	m_bkBrush.CreatePatternBrush(&bmpTmp);
	*/

	m_Font.CreatePointFont(250, _T("微软雅黑"), NULL);
	GetDlgItem(IDCANCEL)->SetFont(&m_Font);

	OnFull();

	return TRUE;
}


HBRUSH CCancelDlg::OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd == this)
	{
		return m_bkBrush;
	}

	return hbr;
}

void CCancelDlg::OnPaint()
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
		if (mImage.Load(TEXT("./image/duedate.jpg")) == S_OK)
		{
			//这里让图片绘制区域和窗口大小一致
			mImage.Draw(GetDC()->GetSafeHdc(), CRect(0, 0, rc.Width(), rc.Height()));
		}
		CDialogEx::OnPaint();
	}
}

void CCancelDlg::OnTimer(UINT nID)
{
	extern BOOL TimeFlag;
	extern int TimeCount;
	if (TimeFlag)
	{
		TimeFlag = FALSE;
		TimeCount = 0;
		OnBnClickedCancel();
	}
}

void CCancelDlg::OnFull()
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


// CCancelDlg 消息处理程序


void CCancelDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	//MessageBox("请关闭窗口");
	extern BOOL g_tipfeeandbookflag;
	if(!g_tipfeeandbookflag)
		CDialogEx::OnCancel();
}
