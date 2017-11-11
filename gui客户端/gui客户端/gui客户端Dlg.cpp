
// gui�ͻ���Dlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "gui�ͻ���.h"
#include "gui�ͻ���Dlg.h"
#include "afxdialogex.h"


#pragma  comment(lib,"ws2_32.lib")


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Cgui�ͻ���Dlg �Ի���




Cgui�ͻ���Dlg::Cgui�ͻ���Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(Cgui�ͻ���Dlg::IDD, pParent)
	, m_Text(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	//  m_tcmd = _T("");
	m_tcmd = _T("");
}

void Cgui�ͻ���Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TEXT, m_Text);
	DDX_Control(pDX, IDC_SERVERIP, m_ServerIp);
	//  DDX_Text(pDX, IDC_TCMD, m_tcmd);
	DDX_Text(pDX, IDC_TCMD, m_tcmd);
}

BEGIN_MESSAGE_MAP(Cgui�ͻ���Dlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_UP, &Cgui�ͻ���Dlg::OnBnClickedButtonUp)
	ON_BN_CLICKED(IDC_BUTTON_LEFT, &Cgui�ͻ���Dlg::OnBnClickedButtonLeft)
	ON_BN_CLICKED(IDC_BUTTON_RIGHT, &Cgui�ͻ���Dlg::OnBnClickedButtonRight)
	ON_BN_CLICKED(IDC_BUTTON_DOWN, &Cgui�ͻ���Dlg::OnBnClickedButtonDown)
	ON_BN_CLICKED(IDCANCEL, &Cgui�ͻ���Dlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_SEND, &Cgui�ͻ���Dlg::OnBnClickedSend)
END_MESSAGE_MAP()


// Cgui�ͻ���Dlg ��Ϣ�������

BOOL Cgui�ͻ���Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	//ΪIP��ַ�򸳳�ֵ
	CString  strIP="192.168.1.101";  
	DWORD  dwIP; 
	dwIP  =  inet_addr(strIP);
	unsigned  char  *pIP  =  (unsigned  char*)&dwIP;
	m_ServerIp.SetAddress(*pIP,  *(pIP+1),  *(pIP+2),  *(pIP+3));

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void Cgui�ͻ���Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR Cgui�ͻ���Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void Cgui�ͻ���Dlg::OnBnClickedButtonUp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	sendCmd("U");
}


void Cgui�ͻ���Dlg::OnBnClickedButtonLeft()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	sendCmd("L");
}


void Cgui�ͻ���Dlg::OnBnClickedButtonRight()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	sendCmd("R");
}


void Cgui�ͻ���Dlg::OnBnClickedButtonDown()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	sendCmd("D");
}


void Cgui�ͻ���Dlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();

}



void Cgui�ͻ���Dlg::sendCmd(char* cmd)
{
	
	
	//��ʼ��WSA
	WORD sockVersion= MAKEWORD(2,2);
	WSADATA data;
	if(WSAStartup(sockVersion, &data) != 0)
	{
		AfxMessageBox("ʧ��!");
		
	}

	//�����׽���
	SOCKET sclient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(sclient == INVALID_SOCKET)
	{
		AfxMessageBox("��Ч�� socket !");
	}

	//��IP�Ͷ˿�
    sockaddr_in serAddr;
	serAddr.sin_family = AF_INET;
	serAddr.sin_port = htons(8888);
	unsigned  char  *pIP;
	DWORD  dwIP;
	CString  strIP;
	m_ServerIp.GetAddress(dwIP);//�ؼ���ȡDWORD��IP
	pIP  =  (unsigned  char*)&dwIP;  
	strIP.Format("%u.%u.%u.%u",*(pIP+3),  *(pIP+2),  *(pIP+1),  *pIP);//ת��ΪIP��ʽ
	serAddr.sin_addr.S_un.S_addr = inet_addr(strIP);
	if (connect(sclient, (sockaddr *)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
	{
		//AfxMessageBox("����ʧ��\n");
		m_Text="����ʧ��\n";
		UpdateData(FALSE);
		//AfxMessageBox(inet_ntoa(serAddr.sin_addr));
	}
	else
	{
		//AfxMessageBox("���ӳɹ�\n");
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
		closesocket(sclient);//�ر�һ���׽ӿ�
		WSACleanup();//��ֹWinsock 2 DLL (Ws2_32.dll) ��ʹ��
	}
	
}

void Cgui�ͻ���Dlg::OnBnClickedSend()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	char *ch = m_tcmd.GetBuffer(m_tcmd.GetLength() + 1);
    m_tcmd.ReleaseBuffer();
	sendCmd(ch);
	UpdateData(FALSE);
}
