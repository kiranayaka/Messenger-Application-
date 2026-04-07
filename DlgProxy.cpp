
// DlgProxy.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Messenger Application.h"
#include "DlgProxy.h"
#include "Messenger ApplicationDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMessengerApplicationDlgAutoProxy

IMPLEMENT_DYNCREATE(CMessengerApplicationDlgAutoProxy, CCmdTarget)

CMessengerApplicationDlgAutoProxy::CMessengerApplicationDlgAutoProxy()
{
	EnableAutomation();

	// To keep the application running as long as an automation
	//	object is active, the constructor calls AfxOleLockApp.
	AfxOleLockApp();

	// Get access to the dialog through the application's
	//  main window pointer.  Set the proxy's internal pointer
	//  to point to the dialog, and set the dialog's back pointer to
	//  this proxy.
	ASSERT_VALID(AfxGetApp()->m_pMainWnd);
	if (AfxGetApp()->m_pMainWnd)
	{
		ASSERT_KINDOF(CMessengerApplicationDlg, AfxGetApp()->m_pMainWnd);
		if (AfxGetApp()->m_pMainWnd->IsKindOf(RUNTIME_CLASS(CMessengerApplicationDlg)))
		{
			m_pDialog = reinterpret_cast<CMessengerApplicationDlg*>(AfxGetApp()->m_pMainWnd);
			m_pDialog->m_pAutoProxy = this;
		}
	}
}

CMessengerApplicationDlgAutoProxy::~CMessengerApplicationDlgAutoProxy()
{
	// To terminate the application when all objects created with
	// 	with automation, the destructor calls AfxOleUnlockApp.
	//  Among other things, this will destroy the main dialog
	if (m_pDialog != nullptr)
		m_pDialog->m_pAutoProxy = nullptr;
	AfxOleUnlockApp();
}

void CMessengerApplicationDlgAutoProxy::OnFinalRelease()
{
	// When the last reference for an automation object is released
	// OnFinalRelease is called.  The base class will automatically
	// deletes the object.  Add additional cleanup required for your
	// object before calling the base class.

	CCmdTarget::OnFinalRelease();
}

BEGIN_MESSAGE_MAP(CMessengerApplicationDlgAutoProxy, CCmdTarget)
END_MESSAGE_MAP()

BEGIN_DISPATCH_MAP(CMessengerApplicationDlgAutoProxy, CCmdTarget)
END_DISPATCH_MAP()

// Note: we add support for IID_IMessenger_Application to support typesafe binding
//  from VBA.  This IID must match the GUID that is attached to the
//  dispinterface in the .IDL file.

// {dd61008d-0fe2-4952-a13d-6b9b4bc35684}
static const IID IID_IMessenger_Application =
{0xdd61008d,0x0fe2,0x4952,{0xa1,0x3d,0x6b,0x9b,0x4b,0xc3,0x56,0x84}};

BEGIN_INTERFACE_MAP(CMessengerApplicationDlgAutoProxy, CCmdTarget)
	INTERFACE_PART(CMessengerApplicationDlgAutoProxy, IID_IMessenger_Application, Dispatch)
END_INTERFACE_MAP()

// The IMPLEMENT_OLECREATE2 macro is defined in pch.h of this project
// {7cb982e1-4680-4229-8651-59624ae35a0e}
IMPLEMENT_OLECREATE2(CMessengerApplicationDlgAutoProxy, "Messenger_Application.Application", 0x7cb982e1,0x4680,0x4229,0x86,0x51,0x59,0x62,0x4a,0xe3,0x5a,0x0e)


// CMessengerApplicationDlgAutoProxy message handlers
