#pragma once


// CTipFeeAndBookDlg �Ի���
class CTipFeeAndBookDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CTipFeeAndBookDlg)

public:
	CTipFeeAndBookDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTipFeeAndBookDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TIPFEEBOOKS_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	
	BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nID);
	DECLARE_MESSAGE_MAP()
public:
	// ѧ��Ƿ��������鼮
	CString debtBooksName;
	// ��ʾ�ۿ�Ľ��
	CString debtAmount;
	//���ݿۿ��鼮��Ϣ
	CString t_debtBooksinfo;
	float debtfamount;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	CFont m_Font;
	CString m_student;
	CString t_student;
	// ��ʱ��������
	CString TimeTick;
	afx_msg void OnEnChangeEdit4();
};
