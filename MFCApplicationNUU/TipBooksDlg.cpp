// TipBooksDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplicationNUU.h"
#include "TipBooksDlg.h"
#include "afxdialogex.h"
extern BOOL g_tipfeeandbookflag;

// CTipBooksDlg 对话框

IMPLEMENT_DYNAMIC(CTipBooksDlg, CDialogEx)

CTipBooksDlg::CTipBooksDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TIPBOOKS_DIALOG, pParent)
	, m_readingbook(_T(""))
	, m_studentid(_T(""))
	, TimeTick(_T(""))
{

}

CTipBooksDlg::~CTipBooksDlg()
{
}

void CTipBooksDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_readingbook);
	DDX_Text(pDX, IDC_EDIT2, m_studentid);
	DDX_Text(pDX, IDC_EDIT3, TimeTick);
}


BEGIN_MESSAGE_MAP(CTipBooksDlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &CTipBooksDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT1, &CTipBooksDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()

BOOL CTipBooksDlg::OnInitDialog()
{
	SetTimer(1, 1000, NULL);
	//对话框初始化的时候将flag改为true，表示对话框在打开状态
	g_tipfeeandbookflag = TRUE;

	CRect rtClient;
	GetWindowRect(rtClient);
	::SetWindowPos(m_hWnd, HWND_TOPMOST, rtClient.left, rtClient.top, rtClient.Width(), rtClient.Height(), SWP_SHOWWINDOW);
	
	UpdateData(TRUE);
	TimeTick.Format("%d", 10);
	m_readingbook = t_readingbook;
	m_studentid = "学号：" + t_studentid;
	UpdateData(FALSE);

	//改变字体
	m_Font.CreatePointFont(130, _T("微软雅黑"), NULL);
	//m_readingbook.SetFont(&m_Font, FALSE);//m_ControlEdit为需要改变字体的edit控件control变量
	CEdit *m_Edit = (CEdit *)GetDlgItem(IDC_EDIT1);
	m_Edit->SetFont(&m_Font, FALSE);
	CEdit *m_Edit2 = (CEdit *)GetDlgItem(IDC_EDIT2);
	m_Edit2->SetFont(&m_Font, FALSE);
	CEdit *m_Edit3 = (CEdit *)GetDlgItem(IDC_EDIT3);
	m_Edit3->SetFont(&m_Font, FALSE);
	CEdit *m_Static = (CEdit *)GetDlgItem(IDC_STATIC);
	m_Static->SetFont(&m_Font, FALSE);

	return TRUE;
}

HBRUSH CTipBooksDlg::OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (pWnd == this)
	{
		return m_bkBrush;
	}

	return hbr;
}


void CTipBooksDlg::OnPaint()
{
	CPaintDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	dc.FillSolidRect(rect, RGB(30, 144, 255));
}
int kj = 10;
void CTipBooksDlg::OnTimer(UINT nID)
{
	UpdateData(TRUE);
	TimeTick.Format("%d", kj);
	UpdateData(FALSE);
	if (kj < 0)
	{
		OnBnClickedOk();
	}
	kj--;
}


// CTipBooksDlg 消息处理程序

void CTipBooksDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	kj = 10;
	g_tipfeeandbookflag = FALSE;
	CDialogEx::OnOK();
}


void CTipBooksDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
