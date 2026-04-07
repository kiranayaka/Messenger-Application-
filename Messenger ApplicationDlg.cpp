
// Messenger ApplicationDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Messenger Application.h"
#include "Messenger ApplicationDlg.h"
#include "DlgProxy.h"
#include "afxdialogex.h"

#include <WinSock2.h>
#include <iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace std;

// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMessengerApplicationDlg dialog


IMPLEMENT_DYNAMIC(CMessengerApplicationDlg, CDialogEx);

CMessengerApplicationDlg::CMessengerApplicationDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MESSENGER_APPLICATION_DIALOG, pParent)
	, m_RcvMsg(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_pAutoProxy = nullptr;
}

CMessengerApplicationDlg::~CMessengerApplicationDlg()
{
	// If there is an automation proxy for this dialog, set
	//  its back pointer to this dialog to null, so it knows
	//  the dialog has been deleted.
	if (m_pAutoProxy != nullptr)
		m_pAutoProxy->m_pDialog = nullptr;
}

void CMessengerApplicationDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_RcvMsg, m_RcvMsg);
}

BEGIN_MESSAGE_MAP(CMessengerApplicationDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_Receive_Message, &CMessengerApplicationDlg::OnBnClickedReceiveMessage)
END_MESSAGE_MAP()


// CMessengerApplicationDlg message handlers

BOOL CMessengerApplicationDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMessengerApplicationDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMessengerApplicationDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMessengerApplicationDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// Automation servers should not exit when a user closes the UI
//  if a controller still holds on to one of its objects.  These
//  message handlers make sure that if the proxy is still in use,
//  then the UI is hidden but the dialog remains around if it
//  is dismissed.

void CMessengerApplicationDlg::OnClose()
{
	if (CanExit())
		CDialogEx::OnClose();
}

void CMessengerApplicationDlg::OnOK()
{
	if (CanExit())
		CDialogEx::OnOK();
}

void CMessengerApplicationDlg::OnCancel()
{
	if (CanExit())
		CDialogEx::OnCancel();
}

BOOL CMessengerApplicationDlg::CanExit()
{
	// If the proxy object is still around, then the automation
	//  controller is still holding on to this application.  Leave
	//  the dialog around, but hide its UI.
	if (m_pAutoProxy != nullptr)
	{
		ShowWindow(SW_HIDE);
		return FALSE;
	}

	return TRUE;
}





void CMessengerApplicationDlg::OnBnClickedReceiveMessage()
{
	// TODO: Add your control notification handler code here
	WSADATA wsa;
	SOCKET serverSocket, clientSocket;
	sockaddr_in serverAddr{}, clientAddr{};
	int clientSize = sizeof(clientAddr);

	char buffer[1024] = {' '};


	// Initialize Winsock
	WSAStartup(MAKEWORD(2, 2), &wsa);

	// Create socket
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);

	// Setup server address
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(54000);
	serverAddr.sin_addr.s_addr = INADDR_ANY;


	// Bind
	bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr));

	// Listen
	listen(serverSocket, SOMAXCONN);
	cout << "Server listening...\n";


	// Accept client
	clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientSize);


	// Receive message
	recv(clientSocket, buffer, sizeof(buffer), 0);
	cout << "Client says: " << buffer << endl;
	m_RcvMsg = CString(buffer);
	UpdateData(false);
	// Cleanup
	closesocket(clientSocket);
	closesocket(serverSocket);
	WSACleanup();
}
