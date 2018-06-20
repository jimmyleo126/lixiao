// ReadingBooksDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "MFCApplicationNUU.h"
#include "ReadingBooksDlg.h"
#include "afxdialogex.h"
#include "TipBooksDlg.h"
// CReadingBooksDlg �Ի���
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
	m_Font.CreatePointFont(250, _T("΢���ź�"), NULL);
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
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CRect rc;
		GetWindowRect(&rc);
		CImage mImage;
		if (mImage.Load(TEXT("./image/readingbooks.jpg")) == S_OK)
		{
			//������ͼƬ��������ʹ��ڴ�Сһ��
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
	//����ȫ����ʾ��ʶ
	m_bFullScreen = !m_bFullScreen;
	LONG style = ::GetWindowLong(this->m_hWnd, GWL_STYLE);
	if (m_bFullScreen)//ȫ����ʾ
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

// CReadingBooksDlg ��Ϣ�������


void CReadingBooksDlg::OnBnClickedCancel()
{
	extern BOOL g_tipfeeandbookflag;
	if(!g_tipfeeandbookflag)
		CDialogEx::OnCancel();
}
