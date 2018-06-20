
// MFCApplicationNUUDlg.cpp : ʵ���ļ�
#pragma once
#include "stdafx.h"
#include "MFCApplicationNUU.h"
#include "MFCApplicationNUUDlg.h"
#include "LibServicePortBinding.nsmap"
#include "nuu_mainbus.h"
#include "CancelDlg.h"
#include "ReadingBooksDlg.h"
#include "LogoutDlg.h"
#include "FileLogger.h"
#include "LogManager.h"
#include <windows.h>


#define WM_SHOWTASK     WM_USER + 100 //������Ϣ��ֵ

#ifdef _DEBUG
	#define DBG_NEW new (_NORMAL_BLOCK , __FILE__ , __LINE__)
	#define new DEBUG_NEW
#endif

extern string  result;
extern long tip1;

//string readURL();

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMFCApplicationNUUDlg �Ի���



CMFCApplicationNUUDlg::CMFCApplicationNUUDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MFCAPPLICATIONNUU_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCApplicationNUUDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFCApplicationNUUDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCApplicationNUUDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_RADIO2, &CMFCApplicationNUUDlg::OnBnClickedRadio2)
	ON_BN_CLICKED(IDC_RADIO1, &CMFCApplicationNUUDlg::OnBnClickedRadio1)
	ON_MESSAGE(WM_SHOWTASK, onShowTask)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCApplicationNUUDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_CANCEL_BUTTON, &CMFCApplicationNUUDlg::OnBnClickedCancelButton)
	ON_BN_CLICKED(IDC_BUTTON3, &CMFCApplicationNUUDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDCANCEL, &CMFCApplicationNUUDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CMFCApplicationNUUDlg ��Ϣ�������
CRect m_rect;
BOOL CMFCApplicationNUUDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	InitInstance(); //ʵ������ֻ����һ��

	//��ʧУ�����ò���
	if (!PathFileExists("./Config1.ini")) {
		CheckDlgButton(IDC_RADIO1, 1);
		OnBnClickedRadio1();
	}
	else {
		int isValidStu = -1;
		isValidStu = GetPrivateProfileInt(TEXT("Service"), TEXT("isValidStu"), -1, TEXT("./Config1.ini"));
		//isValidStuΪ1��ʾ���ǹ�ʧУ�顱Ϊ0��ʾ�����ʧУ�顱
		if (isValidStu == 1) {
			CheckDlgButton(IDC_RADIO2, 1);
		}
		else if (isValidStu == 0) {
			CheckDlgButton(IDC_RADIO1, 1);
		}
		else {
			MessageBox("��������!");
		}
	}
	
	Initnuu();
	
	PostMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);//�������С��

	//��ȡ�Ի���Ĵ�Сԭʼ��
	GetClientRect(&m_rect);

	//��������ť�ϵ�����ı�
	m_Font.CreatePointFont(250, _T("΢���ź�"), NULL);
	GetDlgItem(IDC_CANCEL_BUTTON)->SetFont(&m_Font);
	GetDlgItem(IDC_BUTTON2)->SetFont(&m_Font);
	GetDlgItem(IDC_BUTTON3)->SetFont(&m_Font);

	//������������
	//CWnd* pWnd = CWnd::FindWindow(_T("Shell_TrayWnd"), NULL);
	//pWnd->CWnd::ShowWindow(SW_HIDE);

	//����ȫ����ʾ
	//OnFull();

	//�Զ��Բ�������,������window�������һ����ԣ�����Զ�����������
	APPBARDATA apBar;
	memset(&apBar, 0, sizeof(apBar));
	apBar.cbSize = sizeof(apBar);
	apBar.lParam = ABS_AUTOHIDE;
	SHAppBarMessage(ABM_SETSTATE, &apBar);

	
	//SetAutoRun(TRUE); //��������

	PostMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

HANDLE m_hMutex;
BOOL CMFCApplicationNUUDlg::InitInstance()
{
	const char *str = "Demo";
	//string str = "demo";
	CString temp = str;
	LPCWSTR app = (LPCWSTR)(temp.AllocSysString());
	//����������
	m_hMutex = ::CreateMutexW(NULL, FALSE, app);
	//�жϻ������Ƿ����
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		AfxMessageBox(_T("Ӧ�ó����Ѿ�����!"));
		// �ر��ź������
		CloseHandle(m_hMutex);

		// Ѱ����ǰʵ����������
		HWND hWndPrevious = ::GetWindow(::GetDesktopWindow(), GW_CHILD);
		while (::IsWindow(hWndPrevious))
		{
			// ��鴰���Ƿ���Ԥ��ı��?
			// �У���������Ѱ�ҵ�����
			if (::GetProp(hWndPrevious, _T("Demo")))
			{
				// ����������С������ָ����С
				if (::IsIconic(hWndPrevious))
					::ShowWindow(hWndPrevious, SW_RESTORE);
				// ����������
				::SetForegroundWindow(hWndPrevious);
				// �������ĶԻ��򼤻�
			}
		}
		return false;
	}
	else
	{
		//AfxMessageBox(_T("Ӧ�ó����һ������"));
	}
	
	return FALSE;
}

int CMFCApplicationNUUDlg::ExitInstance()
{
	// TODO: �ڴ����ר�ô����/����û���
	if (m_hMutex != NULL)
	{
		CloseHandle(m_hMutex);	//�رվ��
	}

	return CMFCApplicationNUUDlg::ExitInstance();
}


LRESULT    CMFCApplicationNUUDlg::onShowTask(WPARAM    wParam, LPARAM    lParam)        //wParam���յ���ͼ���ID����lParam���յ���������Ϊ       
{        
	if (wParam != IDR_MAINFRAME)
		return 1;
	switch (lParam)
	{
	case WM_RBUTTONUP:                                        // �Ҽ�����ʱ�����˵�
	{
		LPPOINT lpoint = new tagPOINT;
		::GetCursorPos(lpoint);                    // �õ����λ��
		CMenu menu;
		menu.CreatePopupMenu();                    // ����һ������ʽ�˵�
		menu.AppendMenu(MF_STRING, WM_DESTROY, _T("�˳�"));
		menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x, lpoint->y, this);
		HMENU hmenu = menu.Detach();
		menu.DestroyMenu();
		delete lpoint;
	}
	break;
	case WM_LBUTTONDBLCLK:                                 // ˫������Ĵ���
	{
		this->ShowWindow(SW_SHOWNORMAL);         // ��ʾ������
	}
	break;
	}
	return 0;
}

void CMFCApplicationNUUDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else if(nID == SC_MINIMIZE)
	{
		
		nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
		nid.hWnd = this->m_hWnd;
		nid.uID = IDR_MAINFRAME;
		nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
		nid.uCallbackMessage = WM_SHOWTASK;//�Զ������Ϣ����
		nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
		//strcpy(nid.szTip,"�ƻ���������");//��Ϣ��ʾ��Ϊ���ƻ��������ѡ�
		
		lstrcpy(nid.szTip, _T("����ϵͳ"));
		Shell_NotifyIcon(NIM_ADD, &nid);//�����������ͼ��
		ShowWindow(SW_HIDE);//����������
	}
	else {
		Shell_NotifyIcon(NIM_DELETE, &nid);
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CMFCApplicationNUUDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC dc;
	dc.Attach(lpDrawItemStruct->hDC);
	ASSERT(lpDrawItemStruct->CtlType == ODT_BUTTON);

	CString strText;
	((CButton *)GetDlgItem(nIDCtl))->GetWindowText(strText);


	SetBkMode(lpDrawItemStruct->hDC, TRANSPARENT);
	//if (lpDrawItemStruct->itemState&ODS_SELECTED)
	{
		CBrush brush;
		if (nIDCtl == IDC_CANCEL_BUTTON) {
			//�����ڷ��ť��ɫ
			brush.CreateSolidBrush(RGB(241, 185, 99));
		}
		else if (nIDCtl == IDC_BUTTON2)
		{
			//����ҵ��֤��ť��ɫ
			brush.CreateSolidBrush(RGB(239, 126, 86));
		}
		else if (nIDCtl == IDC_BUTTON3)
		{
			//���ڽ��ѯ��ѯ��ť��ɫ
			brush.CreateSolidBrush(RGB(248, 243, 152));
		}
		else if (nIDCtl == IDCANCEL)
		{
			//���˳���ť��ɫ
			brush.CreateSolidBrush(RGB(205 ,92 ,92));
		}
		dc.FillRect(&(lpDrawItemStruct->rcItem), &brush);
		DrawText(lpDrawItemStruct->hDC, strText, strText.GetLength(),
			&lpDrawItemStruct->rcItem, DT_SINGLELINE | DT_VCENTER | DT_CENTER);
		SetBkMode(lpDrawItemStruct->hDC, TRANSPARENT);
	}
	dc.Detach();
}

void CMFCApplicationNUUDlg::OnPaint()
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
		//����λͼ  
		CBitmap bitmap;
		bitmap.LoadBitmap(144);

		//ѡ��DC  
		CClientDC cdc(this);
		CDC comdc;
		comdc.CreateCompatibleDC(&cdc);
		comdc.SelectObject(&bitmap);

		//����BITMAP  
		BITMAP bit;
		bitmap.GetBitmap(&bit);

		//�ͻ�����  
		CRect rect;
		GetClientRect(&rect);

		//�ÿͻ�����DC���������ɵ�BITMAP������ӦΪ���ڴ�С  
		cdc.StretchBlt(0, 0, rect.Width(), rect.Height(), &comdc, 0, 0, bit.bmWidth, bit.bmHeight, SRCCOPY);

		//CRect rc;
		//GetWindowRect(&rc);
		//CImage mImage;
		//char strinfo[64];
		//std::memset(strinfo, 0, sizeof(strinfo));
		//long aa = mImage.Load(TEXT("./image/mainframe.jpg"));
		//if (aa == S_OK)
		//{
		//	sprintf_s(strinfo, 64, "���ر���ͼ����ȷ���ص�ͼƬ��, %d", aa);
		//	
		//	//������ͼƬ��������ʹ��ڴ�Сһ��
		//	mImage.Draw(GetDC()->GetSafeHdc(), CRect(0, 0, rc.Width(), rc.Height()));
		//}
		//else {
		//	sprintf_s(strinfo, 64, "���ر���ͼ��δ����ȷ���ص�ͼƬ��, %d", aa);
		//}

		//INFO(strinfo);
		CDialogEx::OnPaint();
	}
}

void CMFCApplicationNUUDlg::OnFull()
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

//void CMFCApplicationNUUDlg::SetAutoRun(BOOL bAutoRun)
//{
//	HKEY hKey;
//	CString strRegPath = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";//�ҵ�ϵͳ��������  
//	if (bAutoRun)
//	{
//		if (RegOpenKeyEx(HKEY_CURRENT_USER, strRegPath, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) //��������       
//		{
//			TCHAR szModule[_MAX_PATH];
//			GetModuleFileName(NULL, szModule, _MAX_PATH);//�õ������������ȫ·��  
//			RegSetValueEx(hKey, "Client", 0, REG_SZ, (const BYTE*)(LPCSTR)szModule, strlen(szModule)); //���һ����Key,������ֵ��"Client"��Ӧ�ó������֣����Ӻ�׺.exe��  
//			RegCloseKey(hKey); //�ر�ע���  
//		}
//		else
//		{
//			AfxMessageBox("ϵͳ��������,������ϵͳ����");
//		}
//	}
//	else
//	{
//		if (RegOpenKeyEx(HKEY_CURRENT_USER, strRegPath, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS)
//		{
//			RegDeleteValue(hKey, "Client");
//			RegCloseKey(hKey);
//		}
//	}
//}

void CMFCApplicationNUUDlg::OnSize(UINT nType, int cx, int cy) //cx,cy���ǵ�ǰ�Ի���ĳ��Ϳ�
{
	//CMFCApplicationNUUDlg::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if (nType != SIZE_MINIMIZED) //�жϴ����ǲ�����С���ˣ���Ϊ������С��֮�� �����ڵĳ��Ϳ����0����ǰһ�α仯��ʱ�ͻ���ֳ���0�Ĵ������
	{
		ChangeSize(IDC_CANCEL_BUTTON, cx, cy);
		ChangeSize(IDC_BUTTON2, cx, cy);
		GetClientRect(&m_rect); //���Ҫ���¶Ի���Ĵ�С��������һ�α仯�ľ�����
	}
}

void CMFCApplicationNUUDlg::ChangeSize(UINT nID, int x, int y)
{
	CWnd *pWnd;
	pWnd = GetDlgItem(nID);
	if (pWnd != NULL)
	{
		CRect rec;
		pWnd->GetWindowRect(&rec);
		ScreenToClient(&rec); //���ؼ���Сװ��λ�ڶԻ����е���������
		rec.left = rec.left*x / m_rect.Width(); //���ձ��������ռ����λ��
		rec.top = rec.top*y / m_rect.Height();
		rec.bottom = rec.bottom*y / m_rect.Height();
		rec.right = rec.right*x / m_rect.Width();
		pWnd->MoveWindow(rec); //�����ؼ�
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CMFCApplicationNUUDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMFCApplicationNUUDlg::OnCancel()
{
	// TODO: Add extra cleanup here

	Endnuu();
	
	CDialog::OnCancel();
}

void CMFCApplicationNUUDlg::DealData()
{
	//Sleep(1000);
	//OnBnClickedButton2();
	//UpdateData(TRUE);
	//m_customerinfo_ye = info.Ye;
	//UpdateData(FALSE);
	//MessageBox(_T("��¼ͬ��ʧ��!"), _T("��ʾ"), MB_OK);
}

void CMFCApplicationNUUDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// TODO: Add your control notification handler code here
	OpenOrClose();

}

void CMFCApplicationNUUDlg::OnBnClickedRadio2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ���������� ��
	WritePrivateProfileString("Service", "isValidStu", "1", "./Config1.ini");
}

void CMFCApplicationNUUDlg::OnBnClickedRadio1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ���������� ��
	WritePrivateProfileString("Service", "isValidStu", "0", "./Config1.ini");
}

void CMFCApplicationNUUDlg::OnBnClickedButton2()
{
	extern int model;
	model = 1;
	INT_PTR	nRes;
	CReadingBooksDlg readingbooksDlg;
	ControlReadThread(1);
	nRes = readingbooksDlg.DoModal();
	if (IDCANCEL == nRes)
	{
		ControlReadThread(0);
	}
	else if (IDOK == nRes)
	{
		ControlReadThread(0);
	}
}

void CMFCApplicationNUUDlg::OnBnClickedCancelButton()
{
	extern int model;
	model = 0;
	CCancelDlg cancelDlg;
	INT_PTR nRes;
	ControlReadThread(1);
	nRes = cancelDlg.DoModal();
	if (IDCANCEL == nRes)
	{
		ControlReadThread(0);
		return;
	}
	
}


void CMFCApplicationNUUDlg::OnBnClickedButton3()
{
	extern int model;
	model = 2;
	INT_PTR nRes;
	CLogoutDlg logoutdlg;
	ControlReadThread(1);
	nRes = logoutdlg.DoModal();
	if (IDCANCEL == nRes)
	{
		ControlReadThread(0);
		return;
	}
}

void CMFCApplicationNUUDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//ExitInstance();

	//�Զ��Բ�������,������window�������һ����ԣ�����Զ�����������
	APPBARDATA apBar;
	memset(&apBar, 0, sizeof(apBar));
	apBar.cbSize = sizeof(apBar);
	apBar.lParam = ABS_ALWAYSONTOP;
	SHAppBarMessage(ABM_SETSTATE, &apBar);
	

	CDialogEx::OnCancel();
}
