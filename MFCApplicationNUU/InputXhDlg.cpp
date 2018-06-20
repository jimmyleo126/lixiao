// InputXhDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplicationNUU.h"
#include "InputXhDlg.h"
#include "afxdialogex.h"


// CInputXhDlg �Ի���

IMPLEMENT_DYNAMIC(CInputXhDlg, CDialogEx)

CInputXhDlg::CInputXhDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_INPUTXH_DLG, pParent)
	, m_Xh(_T(""))
{

}

CInputXhDlg::~CInputXhDlg()
{
}

void CInputXhDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Xh);
}


BEGIN_MESSAGE_MAP(CInputXhDlg, CDialogEx)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDOK, &CInputXhDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CInputXhDlg ��Ϣ�������

BOOL CInputXhDlg::OnInitDialog()
{
	SetTimer(1, 10000, NULL);
	m_Font.CreatePointFont(120, _T("΢���ź�"), NULL);
	//m_readingbook.SetFont(&m_Font, FALSE);//m_ControlEditΪ��Ҫ�ı������edit�ؼ�control����
	CEdit *m_Edit = (CEdit *)GetDlgItem(IDC_EDIT1); 
	CStatic *m_Static = (CStatic *)GetDlgItem(IDC_STATIC);
	m_Static->SetFont(&m_Font, FALSE);
	m_Edit->SetFont(&m_Font, FALSE);
	m_Edit->SetFocus();

	//�ж�Ƿ������ģ���Ƿ��ܷ��ص�������

	CRect rtClient;
	GetWindowRect(rtClient);
	::SetWindowPos(m_hWnd, HWND_TOPMOST, rtClient.left, rtClient.top, rtClient.Width(), rtClient.Height(), SWP_SHOWWINDOW);


	return FALSE;
}

void CInputXhDlg::OnPaint()
{
	CPaintDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	dc.FillSolidRect(rect, RGB(30, 144, 255));
}

void CInputXhDlg::OnTimer(UINT nID)
{
	CDialogEx::OnCancel();
}

void CInputXhDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//UpdateData(TRUE);

	CDialogEx::OnOK();
}
