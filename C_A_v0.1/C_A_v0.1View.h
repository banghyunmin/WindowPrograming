
// C_A_v0.1View.h : CC_A_v01View Ŭ������ �������̽�
//

#pragma once
#include "atltypes.h"


class CC_A_v01View : public CView
{
protected: // serialization������ ��������ϴ�.
	CC_A_v01View();
	DECLARE_DYNCREATE(CC_A_v01View)

// Ư���Դϴ�.
public:
	CC_A_v01Doc* GetDocument() const;

// �۾��Դϴ�.
public:

// �������Դϴ�.
public:
	virtual void OnDraw(CDC* pDC);  // �� �並 �׸��� ���� �����ǵǾ����ϴ�.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// �����Դϴ�.
public:
	virtual ~CC_A_v01View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
protected:
	DECLARE_MESSAGE_MAP()
public:
	bool IsInBox(int nx, int ny, CRect rect);
	void setRect();
	CPoint WhatIsPos();
	int WhatIsThere(int vector);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void DrawMap(CDC* pDC);
	void DrawHome(CDC* pDC);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	int m_nViewMode;
	CRect rect_1P;
	CRect rect_2P;
	CRect rect_Map;
	CRect rect_Help;
	CRect rect_Start;
	CRect rect_SelectMode;
	int m_nClickWhat;
	int m_nX;
	int m_nY;
	int m_nSelectMap;
	static int Map_Wall[15][15];
	static int Map_Base[15][15];
	int m_nX2;
	int m_nY2;
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	CPoint WhatIsPos2();
	int WhatIsThere2(int vector);
//	afx_msg void OnSysKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	void DrawEnding(CDC* pDC);
	CRect rect_ReStart;
	CRect rect_Exit;
	void SetPos();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void DrawHelp(CDC* pDC);
	int m_nVector1;
	int m_nVector2;
	int m_nDie;
};

#ifndef _DEBUG  // C_A_v0.1View.cpp�� ����� ����
inline CC_A_v01Doc* CC_A_v01View::GetDocument() const
   { return reinterpret_cast<CC_A_v01Doc*>(m_pDocument); }
#endif

