
// Kmeans.h : Kmeans Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CKmeansApp:
// �йش����ʵ�֣������ Kmeans.cpp
//

class CKmeansApp : public CWinAppEx
{
public:
	CKmeansApp();


// ��д
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// ʵ��
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CKmeansApp theApp;
