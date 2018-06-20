
// MFCApplicationNUUDlg.cpp : 实现文件
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


#define WM_SHOWTASK     WM_USER + 100 //定义消息的值

#ifdef _DEBUG
	#define DBG_NEW new (_NORMAL_BLOCK , __FILE__ , __LINE__)
	#define new DEBUG_NEW
#endif

extern string  result;
extern long tip1;

//string readURL();

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	

// 实现
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


// CMFCApplicationNUUDlg 对话框



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


// CMFCApplicationNUUDlg 消息处理程序
CRect m_rect;
BOOL CMFCApplicationNUUDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	InitInstance(); //实例化，只生成一个

	//挂失校验配置操作
	if (!PathFileExists("./Config1.ini")) {
		CheckDlgButton(IDC_RADIO1, 1);
		OnBnClickedRadio1();
	}
	else {
		int isValidStu = -1;
		isValidStu = GetPrivateProfileInt(TEXT("Service"), TEXT("isValidStu"), -1, TEXT("./Config1.ini"));
		//isValidStu为1表示“是挂失校验”为0表示“否挂失校验”
		if (isValidStu == 1) {
			CheckDlgButton(IDC_RADIO2, 1);
		}
		else if (isValidStu == 0) {
			CheckDlgButton(IDC_RADIO1, 1);
		}
		else {
			MessageBox("参数错误!");
		}
	}
	
	Initnuu();
	
	PostMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0);//打开软件最小化

	//获取对话框的大小原始的
	GetClientRect(&m_rect);

	//将三个按钮上的字体改变
	m_Font.CreatePointFont(250, _T("微软雅黑"), NULL);
	GetDlgItem(IDC_CANCEL_BUTTON)->SetFont(&m_Font);
	GetDlgItem(IDC_BUTTON2)->SetFont(&m_Font);
	GetDlgItem(IDC_BUTTON3)->SetFont(&m_Font);

	//将任务栏隐藏
	//CWnd* pWnd = CWnd::FindWindow(_T("Shell_TrayWnd"), NULL);
	//pWnd->CWnd::ShowWindow(SW_HIDE);

	//窗口全屏显示
	//OnFull();

	//自动以藏任务栏,类似于window任务栏右击属性，点击自动隐藏任务栏
	APPBARDATA apBar;
	memset(&apBar, 0, sizeof(apBar));
	apBar.cbSize = sizeof(apBar);
	apBar.lParam = ABS_AUTOHIDE;
	SHAppBarMessage(ABM_SETSTATE, &apBar);

	
	//SetAutoRun(TRUE); //开机自启

	PostMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

HANDLE m_hMutex;
BOOL CMFCApplicationNUUDlg::InitInstance()
{
	const char *str = "Demo";
	//string str = "demo";
	CString temp = str;
	LPCWSTR app = (LPCWSTR)(temp.AllocSysString());
	//创建互斥量
	m_hMutex = ::CreateMutexW(NULL, FALSE, app);
	//判断互斥量是否存在
	if (GetLastError() == ERROR_ALREADY_EXISTS)
	{
		AfxMessageBox(_T("应用程序已经运行!"));
		// 关闭信号量句柄
		CloseHandle(m_hMutex);

		// 寻找先前实例的主窗口
		HWND hWndPrevious = ::GetWindow(::GetDesktopWindow(), GW_CHILD);
		while (::IsWindow(hWndPrevious))
		{
			// 检查窗口是否有预设的标记?
			// 有，则是我们寻找的主窗
			if (::GetProp(hWndPrevious, _T("Demo")))
			{
				// 主窗口已最小化，则恢复其大小
				if (::IsIconic(hWndPrevious))
					::ShowWindow(hWndPrevious, SW_RESTORE);
				// 将主窗激活
				::SetForegroundWindow(hWndPrevious);
				// 将主窗的对话框激活
			}
		}
		return false;
	}
	else
	{
		//AfxMessageBox(_T("应用程序第一次运行"));
	}
	
	return FALSE;
}

int CMFCApplicationNUUDlg::ExitInstance()
{
	// TODO: 在此添加专用代码和/或调用基类
	if (m_hMutex != NULL)
	{
		CloseHandle(m_hMutex);	//关闭句柄
	}

	return CMFCApplicationNUUDlg::ExitInstance();
}


LRESULT    CMFCApplicationNUUDlg::onShowTask(WPARAM    wParam, LPARAM    lParam)        //wParam接收的是图标的ID，而lParam接收的是鼠标的行为       
{        
	if (wParam != IDR_MAINFRAME)
		return 1;
	switch (lParam)
	{
	case WM_RBUTTONUP:                                        // 右键起来时弹出菜单
	{
		LPPOINT lpoint = new tagPOINT;
		::GetCursorPos(lpoint);                    // 得到鼠标位置
		CMenu menu;
		menu.CreatePopupMenu();                    // 声明一个弹出式菜单
		menu.AppendMenu(MF_STRING, WM_DESTROY, _T("退出"));
		menu.TrackPopupMenu(TPM_LEFTALIGN, lpoint->x, lpoint->y, this);
		HMENU hmenu = menu.Detach();
		menu.DestroyMenu();
		delete lpoint;
	}
	break;
	case WM_LBUTTONDBLCLK:                                 // 双击左键的处理
	{
		this->ShowWindow(SW_SHOWNORMAL);         // 显示主窗口
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
		nid.uCallbackMessage = WM_SHOWTASK;//自定义的消息名称
		nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME));
		//strcpy(nid.szTip,"计划任务提醒");//信息提示条为“计划任务提醒”
		
		lstrcpy(nid.szTip, _T("读卡系统"));
		Shell_NotifyIcon(NIM_ADD, &nid);//在托盘区添加图标
		ShowWindow(SW_HIDE);//隐藏主窗口
	}
	else {
		Shell_NotifyIcon(NIM_DELETE, &nid);
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

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
			//给超期罚款按钮上色
			brush.CreateSolidBrush(RGB(241, 185, 99));
		}
		else if (nIDCtl == IDC_BUTTON2)
		{
			//给毕业清证按钮上色
			brush.CreateSolidBrush(RGB(239, 126, 86));
		}
		else if (nIDCtl == IDC_BUTTON3)
		{
			//给在借查询查询按钮上色
			brush.CreateSolidBrush(RGB(248, 243, 152));
		}
		else if (nIDCtl == IDCANCEL)
		{
			//给退出按钮上色
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
		//加载位图  
		CBitmap bitmap;
		bitmap.LoadBitmap(144);

		//选入DC  
		CClientDC cdc(this);
		CDC comdc;
		comdc.CreateCompatibleDC(&cdc);
		comdc.SelectObject(&bitmap);

		//生成BITMAP  
		BITMAP bit;
		bitmap.GetBitmap(&bit);

		//客户区域  
		CRect rect;
		GetClientRect(&rect);

		//用客户区的DC绘制所生成的BITMAP，并适应为窗口大小  
		cdc.StretchBlt(0, 0, rect.Width(), rect.Height(), &comdc, 0, 0, bit.bmWidth, bit.bmHeight, SRCCOPY);

		//CRect rc;
		//GetWindowRect(&rc);
		//CImage mImage;
		//char strinfo[64];
		//std::memset(strinfo, 0, sizeof(strinfo));
		//long aa = mImage.Load(TEXT("./image/mainframe.jpg"));
		//if (aa == S_OK)
		//{
		//	sprintf_s(strinfo, 64, "加载背景图，正确加载到图片！, %d", aa);
		//	
		//	//这里让图片绘制区域和窗口大小一致
		//	mImage.Draw(GetDC()->GetSafeHdc(), CRect(0, 0, rc.Width(), rc.Height()));
		//}
		//else {
		//	sprintf_s(strinfo, 64, "加载背景图，未能正确加载到图片！, %d", aa);
		//}

		//INFO(strinfo);
		CDialogEx::OnPaint();
	}
}

void CMFCApplicationNUUDlg::OnFull()
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

//void CMFCApplicationNUUDlg::SetAutoRun(BOOL bAutoRun)
//{
//	HKEY hKey;
//	CString strRegPath = "SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";//找到系统的启动项  
//	if (bAutoRun)
//	{
//		if (RegOpenKeyEx(HKEY_CURRENT_USER, strRegPath, 0, KEY_ALL_ACCESS, &hKey) == ERROR_SUCCESS) //打开启动项       
//		{
//			TCHAR szModule[_MAX_PATH];
//			GetModuleFileName(NULL, szModule, _MAX_PATH);//得到本程序自身的全路径  
//			RegSetValueEx(hKey, "Client", 0, REG_SZ, (const BYTE*)(LPCSTR)szModule, strlen(szModule)); //添加一个子Key,并设置值，"Client"是应用程序名字（不加后缀.exe）  
//			RegCloseKey(hKey); //关闭注册表  
//		}
//		else
//		{
//			AfxMessageBox("系统参数错误,不能随系统启动");
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

void CMFCApplicationNUUDlg::OnSize(UINT nType, int cx, int cy) //cx,cy就是当前对话框的长和宽
{
	//CMFCApplicationNUUDlg::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
	if (nType != SIZE_MINIMIZED) //判断窗口是不是最小化了，因为窗口最小化之后 ，窗口的长和宽会变成0，当前一次变化的时就会出现除以0的错误操作
	{
		ChangeSize(IDC_CANCEL_BUTTON, cx, cy);
		ChangeSize(IDC_BUTTON2, cx, cy);
		GetClientRect(&m_rect); //最后要更新对话框的大小，当做下一次变化的旧坐标
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
		ScreenToClient(&rec); //将控件大小装换位在对话框中的区域坐标
		rec.left = rec.left*x / m_rect.Width(); //按照比例调整空间的新位置
		rec.top = rec.top*y / m_rect.Height();
		rec.bottom = rec.bottom*y / m_rect.Height();
		rec.right = rec.right*x / m_rect.Width();
		pWnd->MoveWindow(rec); //伸缩控件
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
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
	//MessageBox(_T("记录同步失败!"), _T("提示"), MB_OK);
}

void CMFCApplicationNUUDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	// TODO: Add your control notification handler code here
	OpenOrClose();

}

void CMFCApplicationNUUDlg::OnBnClickedRadio2()
{
	// TODO: 在此添加控件通知处理程序代码 是
	WritePrivateProfileString("Service", "isValidStu", "1", "./Config1.ini");
}

void CMFCApplicationNUUDlg::OnBnClickedRadio1()
{
	// TODO: 在此添加控件通知处理程序代码 否
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
	// TODO: 在此添加控件通知处理程序代码
	//ExitInstance();

	//自动以藏任务栏,类似于window任务栏右击属性，点击自动隐藏任务栏
	APPBARDATA apBar;
	memset(&apBar, 0, sizeof(apBar));
	apBar.cbSize = sizeof(apBar);
	apBar.lParam = ABS_ALWAYSONTOP;
	SHAppBarMessage(ABM_SETSTATE, &apBar);
	

	CDialogEx::OnCancel();
}
