
// gui�ͻ���.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// Cgui�ͻ���App:
// �йش����ʵ�֣������ gui�ͻ���.cpp
//

class Cgui�ͻ���App : public CWinApp
{
public:
	Cgui�ͻ���App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern Cgui�ͻ���App theApp;