
// Messenger ApplicationDlg.h : header file
//

#pragma once

class CMessengerApplicationDlgAutoProxy;


// CMessengerApplicationDlg dialog
class CMessengerApplicationDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMessengerApplicationDlg);
	friend class CMessengerApplicationDlgAutoProxy;

// Construction
public:
	CMessengerApplicationDlg(CWnd* pParent = nullptr);	// standard constructor
	virtual ~CMessengerApplicationDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MESSENGER_APPLICATION_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	CMessengerApplicationDlgAutoProxy* m_pAutoProxy;
	HICON m_hIcon;

	BOOL CanExit();

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnClose();
	virtual void OnOK();
	virtual void OnCancel();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedReceiveMessage();
	CString m_RcvMsg;
};
