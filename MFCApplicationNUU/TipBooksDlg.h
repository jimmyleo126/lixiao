#pragma once


// CTipBooksDlg 对话框
class CTipBooksDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTipBooksDlg)

public:
	CTipBooksDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTipBooksDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TIPBOOKS_DIALOG };
#endif

protected:
	CBrush m_bkBrush;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nID);
	HBRUSH OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()
public:
	CString m_readingbook;
	CString t_readingbook;
	BOOL tipBooksflag;
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdit1();
	CFont m_Font;
	// 表示学号
	CString m_studentid;
	CString t_studentid;
	// 倒计时秒数
	CString TimeTick;
};
