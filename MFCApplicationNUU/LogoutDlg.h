#pragma once


// CLogoutDlg �Ի���

class CLogoutDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLogoutDlg)

public:
	CLogoutDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CLogoutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_LOGOUT_DIALOG };
#endif

protected:
	HICON m_hIcon;
	CBrush m_bkBrush;
	BOOL m_bFullScreen;
	CFont m_Font;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nID);
	afx_msg BOOL CLogoutDlg::PreTranslateMessage(MSG* pMsg);
	//HBRUSH OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor);
	void OnFull();

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
};
