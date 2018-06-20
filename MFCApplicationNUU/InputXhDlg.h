#pragma once


// CInputXhDlg 对话框

class CInputXhDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInputXhDlg)

public:
	CInputXhDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CInputXhDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INPUTXH_DLG };
#endif

protected:
	CFont m_Font;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nID);

	DECLARE_MESSAGE_MAP()
public:
	// 输入学生的学号
	CString m_Xh;
	afx_msg void OnBnClickedOk();
};
