// MyPhysics.h : MyPhysics Ӧ�ó������ͷ�ļ�
//
#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"       // ������


// CMyPhysicsApp:
// �йش����ʵ�֣������ MyPhysics.cpp
//

class CMyPhysicsApp : public CWinApp
{
public:
	CMyPhysicsApp();
	~CMyPhysicsApp();


// ��д
public:
	virtual BOOL InitInstance();

// ʵ��
	afx_msg void OnAppAbout();

	//afx_msg void OnBnClickedButton1();
	//afx_msg void OnUpdateEdit1(CCmdUI *pCmdUI);

	DECLARE_MESSAGE_MAP()

public:
	CString edit1str;

};

extern CMyPhysicsApp theApp;