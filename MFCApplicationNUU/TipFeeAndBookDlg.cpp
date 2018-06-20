// TipFeeAndBookDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "MFCApplicationNUU.h"
#include "TipFeeAndBookDlg.h"
#include "afxdialogex.h"


BOOL g_tipfeeandbookflag = FALSE;

// CTipFeeAndBookDlg 对话框

IMPLEMENT_DYNAMIC(CTipFeeAndBookDlg, CDialogEx)

CTipFeeAndBookDlg::CTipFeeAndBookDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TIPFEEBOOKS_DIALOG, pParent)
	, debtBooksName(_T(""))
	, debtAmount(_T(""))
	, m_student(_T(""))
	, TimeTick(_T(""))
{
#ifndef _WIN32_WCE
	EnableActiveAccessibility();
#endif

}

CTipFeeAndBookDlg::~CTipFeeAndBookDlg()
{
}

void CTipFeeAndBookDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, debtBooksName);
	DDX_Text(pDX, IDC_EDIT2, debtAmount);
	DDX_Text(pDX, IDC_EDIT3, m_student);
	DDX_Text(pDX, IDC_EDIT4, TimeTick);
}


BEGIN_MESSAGE_MAP(CTipFeeAndBookDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &CTipFeeAndBookDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CTipFeeAndBookDlg::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_EDIT4, &CTipFeeAndBookDlg::OnEnChangeEdit4)
END_MESSAGE_MAP()

BOOL CTipFeeAndBookDlg::OnInitDialog()
{
	SetTimer(1, 1000, NULL);
	CRect rtClient;
	GetWindowRect(rtClient);
	::SetWindowPos(m_hWnd, HWND_TOPMOST, rtClient.left, rtClient.top, rtClient.Width(), rtClient.Height(), SWP_SHOWWINDOW);
	UpdateData(TRUE);
	TimeTick.Format("%d", 10);
	debtBooksName = t_debtBooksinfo;
	debtAmount.Format("总额： %.2f元", debtfamount);
	m_student = "学号：" + t_student;
	UpdateData(FALSE);

	g_tipfeeandbookflag = TRUE;

	//改变字体
	m_Font.CreatePointFont(130, _T("微软雅黑"), NULL);
	//m_readingbook.SetFont(&m_Font, FALSE);//m_ControlEdit为需要改变字体的edit控件control变量
	CEdit *m_Edit = (CEdit *)GetDlgItem(IDC_EDIT1);
	CEdit *m_Edit2 = (CEdit *)GetDlgItem(IDC_EDIT2);
	CEdit *m_Edit3 = (CEdit *)GetDlgItem(IDC_EDIT3);
	m_Edit->SetFont(&m_Font, FALSE);
	m_Edit2->SetFont(&m_Font, FALSE);
	m_Edit3->SetFont(&m_Font, FALSE);
	CEdit *m_Edit4 = (CEdit *)GetDlgItem(IDC_EDIT4);
	m_Edit4->SetFont(&m_Font, FALSE);
	CEdit *m_Static = (CEdit *)GetDlgItem(IDC_STATIC);
	m_Static->SetFont(&m_Font, FALSE);

	return TRUE;
}

void CTipFeeAndBookDlg::OnPaint()
{
	CPaintDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	dc.FillSolidRect(rect, RGB(30, 144, 255));
}

extern int kj;
void CTipFeeAndBookDlg::OnTimer(UINT nID)
{
	UpdateData(TRUE);
	TimeTick.Format("%d", kj);
	UpdateData(FALSE);
	if (kj < 0) {
		OnBnClickedCancel();
	}
	kj--;
}


// CTipFeeAndBookDlg 消息处理程序


void CTipFeeAndBookDlg::OnBnClickedOk()
{
	//点击确定按钮时，将flag刷成false，cancelDlg会根据flag判断是否关页面
	kj = 10;
	g_tipfeeandbookflag = FALSE;
	CDialogEx::OnOK();
}


void CTipFeeAndBookDlg::OnBnClickedCancel()
{
	//点击取消按钮时，将flag刷成false，cancelDlg会根据flag判断是否关页面
	kj = 10;
	g_tipfeeandbookflag = FALSE;
	CDialogEx::OnCancel();
}


void CTipFeeAndBookDlg::OnEnChangeEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
