// TipDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplicationNUU.h"
#include "TipDlg.h"
#include "afxdialogex.h"

extern BOOL g_tipfeeandbookflag;
// CTipDlg �Ի���

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
	m_Font.CreatePointFont(160, _T("΢���ź�"), NULL);
	//m_readingbook.SetFont(&m_Font, FALSE);//m_ControlEditΪ��Ҫ�ı������edit�ؼ�control����
	CEdit *m_Edit = (CEdit *)GetDlgItem(IDC_EDIT1);
	m_Edit->SetFont(&m_Font, FALSE);


	//�ж�Ƿ������ģ���Ƿ��ܷ��ص�������
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

// CTipDlg ��Ϣ�������


void CTipDlg::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CTipDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	kj = 10;
	g_tipfeeandbookflag = FALSE;
	CDialogEx::OnCancel();
}
