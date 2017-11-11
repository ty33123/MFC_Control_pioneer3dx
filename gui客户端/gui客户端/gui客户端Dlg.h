
// gui客户端Dlg.h : 头文件
//
#include <WINSOCK2.H>
#include <STDIO.H>
#include <conio.h>

#pragma once


// Cgui客户端Dlg 对话框
class Cgui客户端Dlg : public CDialogEx
{
// 构造
public:
	Cgui客户端Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_GUI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	// 用于显示信息
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
