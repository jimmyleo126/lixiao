#pragma once


// CInputXhDlg �Ի���

class CInputXhDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInputXhDlg)

public:
	CInputXhDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInputXhDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_INPUTXH_DLG };
#endif

protected:
	CFont m_Font;

	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nID);

	DECLARE_MESSAGE_MAP()
public:
	// ����ѧ����ѧ��
	CString m_Xh;
	afx_msg void OnBnClickedOk();
};
