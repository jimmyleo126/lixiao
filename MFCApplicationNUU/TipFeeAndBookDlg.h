#pragma once


// CTipFeeAndBookDlg 对话框
class CTipFeeAndBookDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTipFeeAndBookDlg)

public:
	CTipFeeAndBookDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CTipFeeAndBookDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TIPFEEBOOKS_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	
	BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nID);
	DECLARE_MESSAGE_MAP()
public:
	// 学生欠款的所有书籍
	CString debtBooksName;
	// 表示扣款的金额
	CString debtAmount;
	//传递扣款书籍信息
	CString t_debtBooksinfo;
	float debtfamount;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CFont m_Font;
	CString m_student;
	CString t_student;
	// 定时，计数器
	CString TimeTick;
	afx_msg void OnEnChangeEdit4();
};
