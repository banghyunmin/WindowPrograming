
// C_A_v0.1.h : C_A_v0.1 ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CC_A_v01App:
// �� Ŭ������ ������ ���ؼ��� C_A_v0.1.cpp�� �����Ͻʽÿ�.
//

class CC_A_v01App : public CWinAppEx
{
public:
	CC_A_v01App();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CC_A_v01App theApp;
