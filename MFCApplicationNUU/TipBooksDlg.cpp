// TipBooksDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplicationNUU.h"
#include "TipBooksDlg.h"
#include "afxdialogex.h"
extern BOOL g_tipfeeandbookflag;

// CTipBooksDlg �Ի���

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
	//�Ի����ʼ����ʱ��flag��Ϊtrue����ʾ�Ի����ڴ�״̬
	g_tipfeeandbookflag = TRUE;

	CRect rtClient;
	GetWindowRect(rtClient);
	::SetWindowPos(m_hWnd, HWND_TOPMOST, rtClient.left, rtClient.top, rtClient.Width(), rtClient.Height(), SWP_SHOWWINDOW);
	
	UpdateData(TRUE);
	TimeTick.Format("%d", 10);
	m_readingbook = t_readingbook;
	m_studentid = "ѧ�ţ�" + t_studentid;
	UpdateData(FALSE);

	//�ı�����
	m_Font.CreatePointFont(130, _T("΢���ź�"), NULL);
	//m_readingbook.SetFont(&m_Font, FALSE);//m_ControlEditΪ��Ҫ�ı������edit�ؼ�control����
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


// CTipBooksDlg ��Ϣ�������

void CTipBooksDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	kj = 10;
	g_tipfeeandbookflag = FALSE;
	CDialogEx::OnOK();
}


void CTipBooksDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
