
// gui客户端Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "gui客户端.h"
#include "gui客户端Dlg.h"
#include "afxdialogex.h"


#pragma  comment(lib,"ws2_32.lib")


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cgui客户端Dlg 对话框




Cgui客户端Dlg::Cgui客户端Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cgui客户端Dlg::IDD, pParent)
	, m_Text(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	//  m_tcmd = _T("");
	m_tcmd = _T("");
}

void Cgui客户端Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TEXT, m_Text);
	DDX_Control(pDX, IDC_SERVERIP, m_ServerIp);
	//  DDX_Text(pDX, IDC_TCMD, m_tcmd);
	DDX_Text(pDX, IDC_TCMD, m_tcmd);
}

BEGIN_MESSAGE_MAP(Cgui客户端Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_UP, &Cgui客户端Dlg::OnBnClickedButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, &Cgui客户端Dlg::OnBnClickedButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, &Cgui客户端Dlg::OnBnClickedButtonRight)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, &Cgui客户端Dlg::OnBnClickedButtonDown)
	ON_BN_CLICKED(IDCANCEL, &Cgui客户端Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_SEND, &Cgui客户端Dlg::OnBnClickedSend)
END_MESSAGE_MAP()


// Cgui客户端Dlg 消息处理程序

BOOL Cgui客户端Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	//为IP地址框赋初值
	CString  strIP="192.168.1.101";  
	DWORD  dwIP; 
	dwIP  =  inet_addr(strIP);
	unsigned  char  *pIP  =  (unsigned  char*)&dwIP;
	m_ServerIp.SetAddress(*pIP,  *(pIP+1),  *(pIP+2),  *(pIP+3));

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void Cgui客户端Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR Cgui客户端Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cgui客户端Dlg::OnBnClickedButtonUp()
{
	// TODO: 在此添加控件通知处理程序代码
	sendCmd("U");
}


void Cgui客户端Dlg::OnBnClickedButtonLeft()
{
	// TODO: 在此添加控件通知处理程序代码
	sendCmd("L");
}


void Cgui客户端Dlg::OnBnClickedButtonRight()
{
	// TODO: 在此添加控件通知处理程序代码
	sendCmd("R");
}


void Cgui客户端Dlg::OnBnClickedButtonDown()
{
	// TODO: 在此添加控件通知处理程序代码
	sendCmd("D");
}


void Cgui客户端Dlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();

}



void Cgui客户端Dlg::sendCmd(char* cmd)
{
	
	
	//初始化WSA
	WORD sockVersion= MAKEWORD(2,2);
	WSADATA data;
	if(WSAStartup(sockVersion, &data) != 0)
	{
		AfxMessageBox("失败!");
		
	}

	//创建套接字
	SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sclient == INVALID_SOCKET)
	{
		AfxMessageBox("无效的 socket !");
	}

	//绑定IP和端口
    sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(8888);
	unsigned  char  *pIP;
	DWORD  dwIP;
	CString  strIP;
	m_ServerIp.GetAddress(dwIP);//控件获取DWORD型IP
	pIP  =  (unsigned  char*)&dwIP;  
	strIP.Format("%u.%u.%u.%u",*(pIP+3),  *(pIP+2),  *(pIP+1),  *pIP);//转换为IP格式
	serAddr.sin_addr.S_un.S_addr = inet_addr(strIP);
	if (connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
	{
		//AfxMessageBox("连接失败\n");
		m_Text="连接失败\n";
		UpdateData(FALSE);
		//AfxMessageBox(inet_ntoa(serAddr.sin_addr));
	}
	else
	{
		//AfxMessageBox("连接成功\n");
		char *sendData;
		sendData =cmd;
		send(sclient, sendData, strlen(sendData), 0);
		char recData[255];
		int ret = recv(sclient, recData, 255, 0);
		if(ret > 0)
		{
			recData[ret] = 0x00;
			m_Text=recData;
			UpdateData(FALSE);
		}
		sendData ="";
		closesocket(sclient);//关闭一个套接口
		WSACleanup();//终止Winsock 2 DLL (Ws2_32.dll) 的使用
	}
	
}

void Cgui客户端Dlg::OnBnClickedSend()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	char *ch = m_tcmd.GetBuffer(m_tcmd.GetLength() + 1);
    m_tcmd.ReleaseBuffer();
	sendCmd(ch);
	UpdateData(FALSE);
}
