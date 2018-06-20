#pragma once
#include "nuu_mainbus.h"

// CReadingBooksDlg 对话框

class CReadingBooksDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CReadingBooksDlg)

public:
	CReadingBooksDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CReadingBooksDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_READINGBOOKS_DIALOG };
#endif

protected:
	HICON m_hIcon;
	CBrush m_bkBrush;
	BOOL m_bFullScreen;
	CFont m_Font;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nID);
	HBRUSH OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor);
	void OnFull();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
};
