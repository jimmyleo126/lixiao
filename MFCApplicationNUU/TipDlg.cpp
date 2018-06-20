// TipDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplicationNUU.h"
#include "TipDlg.h"
#include "afxdialogex.h"

extern BOOL g_tipfeeandbookflag;
// CTipDlg 对话框

IMPLEMENT_DYNAMIC(CTipDlg, CDialogEx)

CTipDlg::CTipDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TIP_DIALOG, pParent)
	, m_tipMsg(_T(""))
	, m_TimeTick(_T(""))
{

}

CTipDlg::~CTipDlg()
{
}

void CTipDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_tipMsg);
	DDX_Text(pDX, IDC_EDIT2, m_TimeTick);
}



BEGIN_MESSAGE_MAP(CTipDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDCANCEL, &CTipDlg::OnBnClickedCancel)
END_MESSAGE_MAP()

BOOL CTipDlg::OnInitDialog()
{
	SetTimer(1, 1000, NULL);
	m_Font.CreatePointFont(160, _T("微软雅黑"), NULL);
	//m_readingbook.SetFont(&m_Font, FALSE);//m_ControlEdit为需要改变字体的edit控件control变量
	CEdit *m_Edit = (CEdit *)GetDlgItem(IDC_EDIT1);
	m_Edit->SetFont(&m_Font, FALSE);


	//判断欠款消费模块是否能返回到主界面
	g_tipfeeandbookflag = TRUE;
	CRect rtClient;
	GetWindowRect(rtClient);
	::SetWindowPos(m_hWnd, HWND_TOPMOST, rtClient.left, rtClient.top, rtClient.Width(), rtClient.Height(), SWP_SHOWWINDOW);

	UpdateData(TRUE);
	m_TimeTick = "10";
	m_tipMsg = t_tipMsg;
	UpdateData(FALSE);
		
	return TRUE;
}

void CTipDlg::OnPaint()
{
	CPaintDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	dc.FillSolidRect(rect, RGB(30, 144, 255));
}
extern int kj;
void CTipDlg::OnTimer(UINT nID)
{
	UpdateData(TRUE);
	m_TimeTick.Format("%d", kj);
	UpdateData(FALSE);
	if (kj < 0)
	{
		OnBnClickedCancel();
	}
	kj--;
}

// CTipDlg 消息处理程序


void CTipDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
}


void CTipDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	kj = 10;
	g_tipfeeandbookflag = FALSE;
	CDialogEx::OnCancel();
}
