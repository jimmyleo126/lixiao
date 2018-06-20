// TipFeeAndBookDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplicationNUU.h"
#include "TipFeeAndBookDlg.h"
#include "afxdialogex.h"


BOOL g_tipfeeandbookflag = FALSE;

// CTipFeeAndBookDlg �Ի���

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
	debtAmount.Format("�ܶ %.2fԪ", debtfamount);
	m_student = "ѧ�ţ�" + t_student;
	UpdateData(FALSE);

	g_tipfeeandbookflag = TRUE;

	//�ı�����
	m_Font.CreatePointFont(130, _T("΢���ź�"), NULL);
	//m_readingbook.SetFont(&m_Font, FALSE);//m_ControlEditΪ��Ҫ�ı������edit�ؼ�control����
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


// CTipFeeAndBookDlg ��Ϣ�������


void CTipFeeAndBookDlg::OnBnClickedOk()
{
	//���ȷ����ťʱ����flagˢ��false��cancelDlg�����flag�ж��Ƿ��ҳ��
	kj = 10;
	g_tipfeeandbookflag = FALSE;
	CDialogEx::OnOK();
}


void CTipFeeAndBookDlg::OnBnClickedCancel()
{
	//���ȡ����ťʱ����flagˢ��false��cancelDlg�����flag�ж��Ƿ��ҳ��
	kj = 10;
	g_tipfeeandbookflag = FALSE;
	CDialogEx::OnCancel();
}


void CTipFeeAndBookDlg::OnEnChangeEdit4()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
