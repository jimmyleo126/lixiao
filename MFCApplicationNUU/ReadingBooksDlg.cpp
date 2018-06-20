// ReadingBooksDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplicationNUU.h"
#include "ReadingBooksDlg.h"
#include "afxdialogex.h"
#include "TipBooksDlg.h"
// CReadingBooksDlg 对话框
IMPLEMENT_DYNAMIC(CReadingBooksDlg, CDialogEx)

CReadingBooksDlg::CReadingBooksDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_READINGBOOKS_DIALOG, pParent)
{

}

CReadingBooksDlg::~CReadingBooksDlg()
{
}

void CReadingBooksDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CReadingBooksDlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDCANCEL, &CReadingBooksDlg::OnBnClickedCancel)
END_MESSAGE_MAP()

BOOL CReadingBooksDlg::OnInitDialog()
{
	SetTimer(1, 2000, NULL);
	/*CString strBmpPath = TEXT("./image/duedate.jpg");
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

HBRUSH CReadingBooksDlg::OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd == this)
	{
		return m_bkBrush;
	}
	return hbr;
}

void CReadingBooksDlg::OnPaint()
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
		if (mImage.Load(TEXT("./image/readingbooks.jpg")) == S_OK)
		{
			//这里让图片绘制区域和窗口大小一致
			mImage.Draw(GetDC()->GetSafeHdc(), CRect(0, 0, rc.Width(), rc.Height()));
		}
		CDialogEx::OnPaint();
	}
}

void CReadingBooksDlg::OnTimer(UINT nID)
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

void CReadingBooksDlg::OnFull()
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

// CReadingBooksDlg 消息处理程序


void CReadingBooksDlg::OnBnClickedCancel()
{
	extern BOOL g_tipfeeandbookflag;
	if(!g_tipfeeandbookflag)
		CDialogEx::OnCancel();
}
