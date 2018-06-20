#pragma once
#include "nuu_mainbus.h"

// CReadingBooksDlg �Ի���

class CReadingBooksDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CReadingBooksDlg)

public:
	CReadingBooksDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CReadingBooksDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_READINGBOOKS_DIALOG };
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
	HBRUSH OnCtlColor(CDC *pDC, CWnd *pWnd, UINT nCtlColor);
	void OnFull();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedCancel();
};
