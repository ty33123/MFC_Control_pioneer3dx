
// gui�ͻ���Dlg.h : ͷ�ļ�
//
#include <WINSOCK2.H>
#include <STDIO.H>
#include <conio.h>

#pragma once


// Cgui�ͻ���Dlg �Ի���
class Cgui�ͻ���Dlg : public CDialogEx
{
// ����
public:
	Cgui�ͻ���Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_GUI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// ������ʾ��Ϣ
	CString m_Text;
	afx_msg void OnBnClickedButtonUp();
	afx_msg void OnBnClickedButtonLeft();
	void sendCmd(char* cmd);
	afx_msg void OnBnClickedButtonRight();
	afx_msg void OnBnClickedButtonDown();
	afx_msg void OnBnClickedCancel();
	CIPAddressCtrl m_ServerIp;
	CString m_tcmd;
	afx_msg void OnBnClickedSend();
};
