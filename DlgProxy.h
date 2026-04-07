
// DlgProxy.h: header file
//

#pragma once

class CMessengerApplicationDlg;


// CMessengerApplicationDlgAutoProxy command target

class CMessengerApplicationDlgAutoProxy : public CCmdTarget
{
	DECLARE_DYNCREATE(CMessengerApplicationDlgAutoProxy)

	CMessengerApplicationDlgAutoProxy();           // protected constructor used by dynamic creation

// Attributes
public:
	CMessengerApplicationDlg* m_pDialog;

// Operations
public:

// Overrides
	public:
	virtual void OnFinalRelease();

// Implementation
protected:
	virtual ~CMessengerApplicationDlgAutoProxy();

	// Generated message map functions

	DECLARE_MESSAGE_MAP()
	DECLARE_OLECREATE(CMessengerApplicationDlgAutoProxy)

	// Generated OLE dispatch map functions

	DECLARE_DISPATCH_MAP()
	DECLARE_INTERFACE_MAP()
};

