#pragma once
#include "afxcmn.h"


// CTipDlg 对话框

class CTipDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTipDlg)

public:
	CTipDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTipDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TIP_DIALOG };
#endif

protected:
	CFont m_Font;
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nID);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnCbnSelchangeCombo1();
	// 开始消费之后，提示的窗口
	CString m_tipMsg;
	CString t_tipMsg;
	afx_msg void OnBnClickedCancel();
	// 倒计时计数变量
	CString m_TimeTick;
};
