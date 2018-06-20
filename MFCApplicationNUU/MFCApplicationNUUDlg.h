
// MFCApplicationNUUDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"



// CMFCApplicationNUUDlg �Ի���
class CMFCApplicationNUUDlg : public CDialogEx
{
// ����
public:
	CMFCApplicationNUUDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCAPPLICATIONNUU_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

	NOTIFYICONDATA nid;

// ʵ��
protected:
	HICON m_hIcon;
	bool m_bFullScreen;
	CFont m_Font;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	BOOL InitInstance();
	int ExitInstance();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg void OnFull();
	//afx_msg void SetAutoRun(BOOL bAutoRun);
	afx_msg void OnSize(UINT nID, int x, int y);
	afx_msg void ChangeSize(UINT nID, int x, int y);
	afx_msg HCURSOR OnQueryDragIcon();
	void OnCancel();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedRadio2();
	afx_msg void OnBnClickedRadio1();
	afx_msg LRESULT onShowTask(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBnClickedButton2();
	afx_msg void DealData();
	//LRESULT OnUpdateMyData(WPARAM wParam, LPARAM lParam);
	//static DWORD CALLBACK ThreadFunc(LPVOID pPara);
	afx_msg void OnBnClickedCancelButton();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedCancel();
};
