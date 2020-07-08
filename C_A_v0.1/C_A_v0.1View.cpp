
// C_A_v0.1View.cpp : CC_A_v01View 클래스의 구현
//

#include "stdafx.h"
// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "C_A_v0.1.h"
#endif

#include "C_A_v0.1Doc.h"
#include "C_A_v0.1View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//그리기 모드 종류
#define HOME_MODE 0
#define MAP_MODE 1
#define ENDING_MODE 2
#define HELP_MODE 3

//HomeDraw에 필요한 정의들
#define RECT_1P 1
#define RECT_2P 2
#define RECT_MAP 3
#define RECT_HELP 4
#define RECT_START 5
#define RECT_SELECTMODE 6

//DrawEnding에 필요한 정의들
#define RECT_RESTART 11
#define RECT_EXIT 12


//Map 데이터에 필요한 정의
#define WALL 4
#define FIRE 3
#define BOX 1
#define ITEM_SPEED 5
#define ITEM_BOMB 6
#define ITEM_POWER 7
#define ROAD 8
#define BOMB_0 10
#define BOMB_1 11
#define BOMB_2 12
#define BOMB_3 13
#define BOMB_4 14
#define BOMB_5 15
#define BOMB_6 16
#define BOMB_7 17
#define BOMB_8 18
#define BOMB_9 19

//SelectMapdml 종류들
#define MAP_BASE 0
#define MAP_WALL 1

//방향
#define LEFT 1
#define DOWN 0
#define RIGHT 2
#define UP 3

//죽은 플레이어
#define DIE1 1
#define DIE2 2


int CC_A_v01View::Map_Wall[15][15] = {
	{ 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 1, 8, 1, 8, 1 },
	{ 8, 1, 8, 1, 8, 4, 8, 8, 8, 4, 8, 8, 8, 8, 8 },
	{ 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 1, 8, 1, 8, 1 },
	{ 8, 1, 8, 1, 8, 4, 8, 8, 8, 4, 8, 8, 8, 8, 8 },
	{ 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 1, 8, 1, 8, 1 },
	{ 8, 1, 8, 1, 8, 4, 8, 8, 8, 4, 8, 8, 8, 8, 8 },
	{ 4, 8, 4, 8, 4, 8, 8, 8, 8, 8, 1, 8, 1, 8, 1 },
	{ 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8 },
	{ 1, 8, 1, 8, 1, 8, 8, 8, 8, 8, 4, 8, 4, 8, 4 },
	{ 8, 8, 8, 8, 8, 4, 8, 8, 8, 4, 8, 1, 8, 1, 8 },
	{ 1, 8, 1, 8, 1, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8 },
	{ 8, 8, 8, 8, 8, 4, 8, 8, 8, 4, 8, 1, 8, 1, 8 },
	{ 1, 8, 1, 8, 1, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8 },
	{ 8, 8, 8, 8, 8, 4, 8, 8, 8, 4, 8, 1, 8, 1, 8 },
	{ 1, 8, 1, 8, 1, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8 }
};

int CC_A_v01View::Map_Base[15][15] = {
	{ 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8 },
	{ 8, 4, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 8 },
	{ 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8 },
	{ 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8 },
	{ 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8 },
	{ 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8 },
	{ 8, 8, 8, 8, 8, 8, 4, 4, 4, 8, 8, 8, 8, 8, 8 },
	{ 8, 8, 8, 8, 8, 8, 4, 4, 4, 8, 8, 8, 8, 8, 8 },
	{ 8, 8, 8, 8, 8, 8, 4, 4, 4, 8, 8, 8, 8, 8, 8 },
	{ 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8 },
	{ 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8 },
	{ 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8 },
	{ 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8 },
	{ 8, 4, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 4, 8 },
	{ 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8 },
};

// CC_A_v01View

IMPLEMENT_DYNCREATE(CC_A_v01View, CView)

BEGIN_MESSAGE_MAP(CC_A_v01View, CView)
	// 표준 인쇄 명령입니다.
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_TIMER()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_CHAR()
	ON_WM_SYSKEYDOWN()
	ON_WM_SIZE()
END_MESSAGE_MAP()

// CC_A_v01View 생성/소멸

CC_A_v01View::CC_A_v01View()
	: m_nViewMode(0)
	, m_nClickWhat(0)
	, m_nX(0)
	, m_nY(0)
	, m_nSelectMap(0)
	, m_nX2(0)
	, m_nY2(0)
	, m_nVector1(0)
	, m_nVector2(0)
	, m_nDie(0)
{
	// TODO: 여기에 생성 코드를 추가합니다.

}

CC_A_v01View::~CC_A_v01View()
{
}

BOOL CC_A_v01View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	return CView::PreCreateWindow(cs);
}

// CC_A_v01View 그리기

void CC_A_v01View::OnDraw(CDC* pDC)
{
	CC_A_v01Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 여기에 원시 데이터에 대한 그리기 코드를 추가합니다.
	CRect rect;
	GetClientRect(&rect);

	CDC memDC;
	CBitmap bitmap, *oldbitmap;

	memDC.CreateCompatibleDC(pDC);
	bitmap.CreateCompatibleBitmap(pDC, rect.Width(), rect.Height());

	oldbitmap = memDC.SelectObject(&bitmap);
	memDC.PatBlt(0, 0, rect.Width(), rect.Height(), WHITENESS);

	if (m_nViewMode == HOME_MODE)
	{
		DrawHome(&memDC);
	}
	else if (m_nViewMode == MAP_MODE)
	{
		DrawMap(&memDC);
	}
	else if (m_nViewMode == ENDING_MODE)
	{
		DrawEnding(&memDC);
	}
	else if (m_nViewMode == HELP_MODE)
	{
		DrawHelp(&memDC);
	}

	pDC->BitBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, SRCCOPY);

	memDC.SelectObject(oldbitmap);
	memDC.DeleteDC();
	bitmap.DeleteObject();
}


// CC_A_v01View 인쇄

BOOL CC_A_v01View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 기본적인 준비
	return DoPreparePrinting(pInfo);
}

void CC_A_v01View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄하기 전에 추가 초기화 작업을 추가합니다.
}

void CC_A_v01View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 인쇄 후 정리 작업을 추가합니다.
}


// CC_A_v01View 진단

#ifdef _DEBUG
void CC_A_v01View::AssertValid() const
{
	CView::AssertValid();
}

void CC_A_v01View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CC_A_v01Doc* CC_A_v01View::GetDocument() const // 디버그되지 않은 버전은 인라인으로 지정됩니다.
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CC_A_v01Doc)));
	return (CC_A_v01Doc*)m_pDocument;
}
#endif //_DEBUG


// CC_A_v01View 메시지 처리기


bool CC_A_v01View::IsInBox(int nx, int ny, CRect rect)
{
	if ((rect.left < nx) && (nx < rect.right))
	{
		if ((rect.top < ny) && (ny < rect.bottom))
		{
			return true;
		}
	}
	return false;
}


void CC_A_v01View::setRect()
{
	//Rect값들을 세팅합니다.
	CRect rect;
	GetClientRect(&rect);

	rect_1P.left = rect.Width() * 1 / 20;
	rect_1P.top = rect.Height() * 1 / 10;
	rect_1P.right = rect.Width() * 6 / 20;
	rect_1P.bottom = rect.Height() * 7 / 10;

	rect_2P.left = rect.Width() * 8 / 20;
	rect_2P.top = rect.Height() * 1 / 10;
	rect_2P.right = rect.Width() * 13 / 20;
	rect_2P.bottom = rect.Height() * 7 / 10;

	rect_Map.left = rect.Width() * 15 / 20;
	rect_Map.top = rect.Height() * 1 / 10;
	rect_Map.right = rect.Width() * 19 / 20;
	rect_Map.bottom = rect.Height() * 5 / 10;

	rect_Help.left = rect.Width() * 15 / 20;
	rect_Help.top = rect.Height() * 6 / 10;
	rect_Help.right = rect.Width() * 19 / 20;
	rect_Help.bottom = rect.Height() * 7 / 10;

	rect_Start.left = rect.Width() * 15 / 20;
	rect_Start.top = rect.Height() * 8 / 10;
	rect_Start.right = rect.Width() * 19 / 20;
	rect_Start.bottom = rect.Height() * 9 / 10;

	rect_SelectMode.left = rect.Width() * 1 / 20;
	rect_SelectMode.top = rect.Height() * 8 / 10;
	rect_SelectMode.right = rect.Width() * 13 / 20;
	rect_SelectMode.bottom = rect.Height() * 9 / 10;

	rect_ReStart.left = rect.Width() * 1 / 4;
	rect_ReStart.top = rect.Height() * 4 / 8;
	rect_ReStart.right = rect.Width() * 3 / 4;
	rect_ReStart.bottom = rect.Height() * 5 / 8;

	rect_Exit.left = rect.Width() * 1 / 4;
	rect_Exit.top = rect.Height() * 6 / 8;
	rect_Exit.right = rect.Width() * 3 / 4;
	rect_Exit.bottom = rect.Height() * 7 / 8;
}


CPoint CC_A_v01View::WhatIsPos()
{
	CPoint Pos;
	CRect rect;
	GetClientRect(&rect);

	int i, j;

	for (i = 0; i < 15; i++)
	{
		for (j = 0; j < 15; j++)
		{
			if (rect.Height()*j / 15 <= m_nX && m_nX < rect.Height()*(j + 1) / 15)
			{
				Pos.y = j;
			}

			if (rect.Height()*i / 15 <= m_nY && m_nY < rect.Height()*(i + 1) / 15)
			{
				Pos.x = i;
			}
		}
	}

	return Pos;
}


int CC_A_v01View::WhatIsThere(int vector)
{
	CRect rect;
	GetClientRect(&rect);

	switch (m_nSelectMap)
	{
	case MAP_BASE:
		switch (vector)
		{
		case LEFT:
			if (WhatIsPos().y == 0)
			{
				return 0;
			}
			else
			{
				return Map_Base[WhatIsPos().x][WhatIsPos().y - 1];
			}
			break;
		case DOWN:
			if (WhatIsPos().x == 14)
			{
				return 0;
			}
			else
			{
				return Map_Base[WhatIsPos().x + 1][WhatIsPos().y];
			}
			break;
		case RIGHT:
			if (WhatIsPos().y == 14)
			{
				return 0;
			}
			else
			{
				return Map_Base[WhatIsPos().x][WhatIsPos().y + 1];
			}
			break;
		case UP:
			if (WhatIsPos().x == 0)
			{
				return 0;
			}
			else
			{
				return Map_Base[WhatIsPos().x - 1][WhatIsPos().y];
			}
			break;
		}
		break;
	case MAP_WALL:
		switch (vector)
		{
		case LEFT:
			if (WhatIsPos().y == 0)
			{
				return 0;
			}
			else
			{
				return Map_Wall[WhatIsPos().x][WhatIsPos().y - 1];
			}
			break;
		case DOWN:
			if (WhatIsPos().x == 14)
			{
				return 0;
			}
			else
			{
				return Map_Wall[WhatIsPos().x + 1][WhatIsPos().y];
			}
			break;
		case RIGHT:
			if (WhatIsPos().y == 14)
			{
				return 0;
			}
			else
			{
				return Map_Wall[WhatIsPos().x][WhatIsPos().y + 1];
			}
			break;
		case UP:
			if (WhatIsPos().x == 0)
			{
				return 0;
			}
			else
			{
				return Map_Wall[WhatIsPos().x - 1][WhatIsPos().y];
			}
			break;
		}
		break;
	}
	return 0;
}


void CC_A_v01View::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	int i, j;
	switch (nIDEvent)
	{
	case 0:

		for (i = 0; i < 15; i++)
		{
			for (j = 0; j < 15; j++)
			{
				if (m_nSelectMap == MAP_BASE)
				{
					if (Map_Base[i][j] == FIRE)
					{
						if (WhatIsPos().x == i && WhatIsPos().y == j)
						{
							m_nDie = DIE1;
							m_nViewMode = ENDING_MODE;
							KillTimer(0);
						}
						if (WhatIsPos2().x == i && WhatIsPos2().y == j)
						{
							m_nDie = DIE2;
							m_nViewMode = ENDING_MODE;
							KillTimer(0);
						}
						Map_Base[i][j] = ROAD;
						Invalidate();
					}
				}
				else if (m_nSelectMap == MAP_WALL)
				{
					if (Map_Wall[i][j] == FIRE)
					{
						if (WhatIsPos().x == i && WhatIsPos().y == j)
						{
							m_nDie = DIE1;
							m_nViewMode = ENDING_MODE;
							KillTimer(0);
						}
						if (WhatIsPos2().x == i && WhatIsPos2().y == j)
						{
							m_nDie = DIE2;
							m_nViewMode = ENDING_MODE;
							KillTimer(0);
						}
						Map_Wall[i][j] = ROAD;
						Invalidate();
					}
				}
			}
		}


		for (i = 0; i < 15; i++)
		{
			for (j = 0; j < 15; j++)
			{
				if (m_nSelectMap == MAP_BASE)
				{
					switch (Map_Base[i][j])
					{
					case BOMB_0:
					case BOMB_1:
					case BOMB_2:
					case BOMB_3:
					case BOMB_4:
					case BOMB_5:
					case BOMB_6:
					case BOMB_7:
					case BOMB_8:
						Map_Base[i][j]++;
						break;
					case BOMB_9:
						Map_Base[i][j] = FIRE;
						if (Map_Base[i][j + 1] == ROAD && j + 1 < 15)
						{
							Map_Base[i][j + 1] = FIRE;
							if (Map_Base[i][j + 2] == ROAD && j + 2 < 15)
							{
								Map_Base[i][j + 2] = FIRE;
							}
						}
						if (Map_Base[i][j - 1] == ROAD && j - 1 >= 0)
						{
							Map_Base[i][j - 1] = FIRE;
							if (Map_Base[i][j - 2] == ROAD && j - 2 >= 0)
							{
								Map_Base[i][j - 2] = FIRE;
							}
						}
						if (Map_Base[i + 1][j] == ROAD && i + 1 < 15)
						{
							Map_Base[i + 1][j] = FIRE;
							if (Map_Base[i + 2][j] == ROAD && i + 2 < 15)
							{
								Map_Base[i + 2][j] = FIRE;
							}
						}
						if (Map_Base[i - 1][j] == ROAD && i - 1 >= 0)
						{
							Map_Base[i - 1][j] = FIRE;
							if (Map_Base[i - 2][j] == ROAD && i - 1 >= 0)
							{
								Map_Base[i - 2][j] = FIRE;
							}
						}
						Invalidate();
						break;
					}
				}
				else if (m_nSelectMap == MAP_WALL)
				{
					switch (Map_Wall[i][j])
					{
					case BOMB_0:
					case BOMB_1:
					case BOMB_2:
					case BOMB_3:
					case BOMB_4:
					case BOMB_5:
					case BOMB_6:
					case BOMB_7:
					case BOMB_8:
						Map_Wall[i][j]++;
						break;
					case BOMB_9:
						Map_Wall[i][j] = FIRE;
						if (Map_Wall[i][j + 1] == ROAD && j + 1 < 15)
						{
							Map_Wall[i][j + 1] = FIRE;
							if (Map_Wall[i][j + 2] == ROAD && j + 2 < 15)
							{
								Map_Wall[i][j + 2] = FIRE;
							}
						}
						if (Map_Wall[i][j - 1] == ROAD && j - 1 >= 0)
						{
							Map_Wall[i][j - 1] = FIRE;
							if (Map_Wall[i][j - 2] == ROAD && j - 2 >= 0)
							{
								Map_Wall[i][j - 2] = FIRE;
							}
						}
						if (Map_Wall[i + 1][j] == ROAD && i + 1 < 15)
						{
							Map_Wall[i + 1][j] = FIRE;
							if (Map_Wall[i + 2][j] == ROAD && i + 2 < 15)
							{
								Map_Wall[i + 2][j] = FIRE;
							}
						}
						if (Map_Wall[i - 1][j] == ROAD && i - 1 >= 0)
						{
							Map_Wall[i - 1][j] = FIRE;
							if (Map_Wall[i - 2][j] == ROAD && i - 2 >= 0)
							{
								Map_Wall[i - 2][j] = FIRE;
							}
						}
						Invalidate();
						break;
					}
				}
			}
		}

		break;
	}


	CView::OnTimer(nIDEvent);
}


void CC_A_v01View::DrawMap(CDC* pDC)
{
	//플레이할 맵을 그립니다.

	CRect rect;
	GetClientRect(&rect);

	CDC memDC;
	memDC.CreateCompatibleDC(pDC);

	CBitmap bitmap1, bitmap2, bitmap3, bitmap4, bitmap5, *oldbitmap;
	bitmap1.LoadBitmapW(IDB_BITMAP_ROAD);
	bitmap2.LoadBitmapW(IDB_BITMAP_WALL);
	bitmap3.LoadBitmapW(IDB_BITMAP_BOX);
	bitmap4.LoadBitmapW(IDB_BITMAP_BOMB);
	bitmap5.LoadBitmapW(IDB_BITMAP_WATER);
	oldbitmap = memDC.SelectObject(&bitmap2);

	BITMAP bmpinfo;
	bitmap1.GetBitmap(&bmpinfo);
	memDC.SelectObject(&bitmap1);

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			switch (m_nSelectMap)
			{
			case MAP_BASE:
				switch (Map_Base[i][j])
				{
				case ROAD:
					memDC.SelectObject(&bitmap1);
					pDC->StretchBlt(rect.Height()*j / 15, rect.Height()*i / 15, rect.Height() / 15, rect.Height() / 15, &memDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
					break;

				case WALL:
					memDC.SelectObject(&bitmap2);
					pDC->StretchBlt(rect.Height()*j / 15, rect.Height()*i / 15, rect.Height() / 15, rect.Height() / 15, &memDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
					break;

				case BOX:
					memDC.SelectObject(&bitmap3);
					pDC->StretchBlt(rect.Height()*j / 15, rect.Height()*i / 15, rect.Height() / 15, rect.Height() / 15, &memDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
					break;

				case BOMB_0:
				case BOMB_1:
				case BOMB_2:
				case BOMB_3:
				case BOMB_4:
				case BOMB_5:
				case BOMB_6:
				case BOMB_7:
				case BOMB_8:
				case BOMB_9:
					memDC.SelectObject(&bitmap4);
					pDC->StretchBlt(rect.Height()*j / 15, rect.Height()*i / 15, rect.Height() / 15, rect.Height() / 15, &memDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
					break;

				case FIRE:
					memDC.SelectObject(&bitmap5);
					pDC->StretchBlt(rect.Height()*j / 15, rect.Height()*i / 15, rect.Height() / 15, rect.Height() / 15, &memDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
					break;

				}
				break;

			case MAP_WALL:
				switch (Map_Wall[i][j])
				{
				case ROAD:
					memDC.SelectObject(&bitmap1);
					pDC->StretchBlt(rect.Height()*j / 15, rect.Height()*i / 15, rect.Height() / 15, rect.Height() / 15, &memDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
					break;

				case WALL:
					memDC.SelectObject(&bitmap2);
					pDC->StretchBlt(rect.Height()*j / 15, rect.Height()*i / 15, rect.Height() / 15, rect.Height() / 15, &memDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
					break;

				case BOX:
					memDC.SelectObject(&bitmap3);
					pDC->StretchBlt(rect.Height()*j / 15, rect.Height()*i / 15, rect.Height() / 15, rect.Height() / 15, &memDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
					break;

				case BOMB_0:
				case BOMB_1:
				case BOMB_2:
				case BOMB_3:
				case BOMB_4:
				case BOMB_5:
				case BOMB_6:
				case BOMB_7:
				case BOMB_8:
				case BOMB_9:
					memDC.SelectObject(&bitmap4);
					pDC->StretchBlt(rect.Height()*j / 15, rect.Height()*i / 15, rect.Height() / 15, rect.Height() / 15, &memDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
					break;

				case FIRE:
					memDC.SelectObject(&bitmap5);
					pDC->StretchBlt(rect.Height()*j / 15, rect.Height()*i / 15, rect.Height() / 15, rect.Height() / 15, &memDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
					break;

				}
				break;
			}
		}
	}


	CBitmap bitmap_gr_bl, bitmap_gr_mask, bitmap_red_bl, bitmap_red_mask;
	bitmap_gr_bl.LoadBitmapW(IDB_BITMAP_GREENBLACK);
	bitmap_gr_mask.LoadBitmapW(IDB_BITMAP_GREENMASK);
	bitmap_red_bl.LoadBitmapW(IDB_BITMAP_REDBLACK);
	bitmap_red_mask.LoadBitmapW(IDB_BITMAP_REDMASK);

	BITMAP bmp;
	bitmap_gr_bl.GetBitmap(&bmp);
	memDC.SelectObject(&bitmap_gr_mask);

	switch (m_nVector1)
	{
	case DOWN:
		pDC->StretchBlt(m_nX, m_nY, rect.Height() / 15, rect.Height() / 15, &memDC, bmp.bmWidth * 1 / 3, bmp.bmHeight * DOWN / 4, bmp.bmWidth / 3, bmp.bmHeight / 4, SRCAND);

		memDC.SelectObject(&bitmap_gr_bl);
		pDC->StretchBlt(m_nX, m_nY, rect.Height() / 15, rect.Height() / 15, &memDC, bmp.bmWidth * 1 / 3, bmp.bmHeight * DOWN / 4, bmp.bmWidth / 3, bmp.bmHeight / 4, SRCPAINT);
		break;
	case LEFT:
		pDC->StretchBlt(m_nX, m_nY, rect.Height() / 15, rect.Height() / 15, &memDC, bmp.bmWidth * 1 / 3, bmp.bmHeight * LEFT / 4, bmp.bmWidth / 3, bmp.bmHeight / 4, SRCAND);

		memDC.SelectObject(&bitmap_gr_bl);
		pDC->StretchBlt(m_nX, m_nY, rect.Height() / 15, rect.Height() / 15, &memDC, bmp.bmWidth * 1 / 3, bmp.bmHeight * LEFT / 4, bmp.bmWidth / 3, bmp.bmHeight / 4, SRCPAINT);
		break;
	case RIGHT:
		pDC->StretchBlt(m_nX, m_nY, rect.Height() / 15, rect.Height() / 15, &memDC, bmp.bmWidth * 1 / 3, bmp.bmHeight * RIGHT / 4, bmp.bmWidth / 3, bmp.bmHeight / 4, SRCAND);

		memDC.SelectObject(&bitmap_gr_bl);
		pDC->StretchBlt(m_nX, m_nY, rect.Height() / 15, rect.Height() / 15, &memDC, bmp.bmWidth * 1 / 3, bmp.bmHeight * RIGHT / 4, bmp.bmWidth / 3, bmp.bmHeight / 4, SRCPAINT);
		break;
	case UP:
		pDC->StretchBlt(m_nX, m_nY, rect.Height() / 15, rect.Height() / 15, &memDC, bmp.bmWidth * 1 / 3, bmp.bmHeight * UP / 4, bmp.bmWidth / 3, bmp.bmHeight / 4, SRCAND);

		memDC.SelectObject(&bitmap_gr_bl);
		pDC->StretchBlt(m_nX, m_nY, rect.Height() / 15, rect.Height() / 15, &memDC, bmp.bmWidth * 1 / 3, bmp.bmHeight * UP / 4, bmp.bmWidth / 3, bmp.bmHeight / 4, SRCPAINT);
		break;
	}


	memDC.SelectObject(&bitmap_red_mask);
	switch (m_nVector2)
	{
	case DOWN:
		pDC->StretchBlt(m_nX2, m_nY2, rect.Height() / 15, rect.Height() / 15, &memDC, bmp.bmWidth * 1 / 3, bmp.bmHeight * DOWN / 4, bmp.bmWidth / 3, bmp.bmHeight / 4, SRCAND);

		memDC.SelectObject(&bitmap_red_bl);
		pDC->StretchBlt(m_nX2, m_nY2, rect.Height() / 15, rect.Height() / 15, &memDC, bmp.bmWidth * 1 / 3, bmp.bmHeight * DOWN / 4, bmp.bmWidth / 3, bmp.bmHeight / 4, SRCPAINT);
		break;
	case LEFT:
		pDC->StretchBlt(m_nX2, m_nY2, rect.Height() / 15, rect.Height() / 15, &memDC, bmp.bmWidth * 1 / 3, bmp.bmHeight * LEFT / 4, bmp.bmWidth / 3, bmp.bmHeight / 4, SRCAND);

		memDC.SelectObject(&bitmap_red_bl);
		pDC->StretchBlt(m_nX2, m_nY2, rect.Height() / 15, rect.Height() / 15, &memDC, bmp.bmWidth * 1 / 3, bmp.bmHeight * LEFT / 4, bmp.bmWidth / 3, bmp.bmHeight / 4, SRCPAINT);
		break;
	case RIGHT:
		pDC->StretchBlt(m_nX2, m_nY2, rect.Height() / 15, rect.Height() / 15, &memDC, bmp.bmWidth * 1 / 3, bmp.bmHeight * RIGHT / 4, bmp.bmWidth / 3, bmp.bmHeight / 4, SRCAND);

		memDC.SelectObject(&bitmap_red_bl);
		pDC->StretchBlt(m_nX2, m_nY2, rect.Height() / 15, rect.Height() / 15, &memDC, bmp.bmWidth * 1 / 3, bmp.bmHeight * RIGHT / 4, bmp.bmWidth / 3, bmp.bmHeight / 4, SRCPAINT);
		break;
	case UP:
		pDC->StretchBlt(m_nX2, m_nY2, rect.Height() / 15, rect.Height() / 15, &memDC, bmp.bmWidth * 1 / 3, bmp.bmHeight * UP / 4, bmp.bmWidth / 3, bmp.bmHeight / 4, SRCAND);

		memDC.SelectObject(&bitmap_red_bl);
		pDC->StretchBlt(m_nX2, m_nY2, rect.Height() / 15, rect.Height() / 15, &memDC, bmp.bmWidth * 1 / 3, bmp.bmHeight * UP / 4, bmp.bmWidth / 3, bmp.bmHeight / 4, SRCPAINT);
		break;
	}

	
	memDC.SelectObject(oldbitmap);
}


void CC_A_v01View::DrawHome(CDC* pDC)
{
	//홈화면에 표시할 그림을 그립니다.
	CRect rect;
	GetClientRect(&rect);

	CDC memDC;
	memDC.CreateCompatibleDC(pDC);

	CBitmap bitmap1, bitmap2, bitmap3, bitmap4, bitmap5, bitmap6, bitmap7, *oldbitmap;
	bitmap1.LoadBitmapW(IDB_BITMAP_STARTBTN);
	bitmap2.LoadBitmapW(IDB_BITMAP_HELPBTN);
	bitmap3.LoadBitmapW(IDB_BITMAP_MODEBTN);
	bitmap4.LoadBitmapW(IDB_BITMAP_MAPWALL);
	bitmap5.LoadBitmapW(IDB_BITMAP_MAPBASE);
	bitmap6.LoadBitmapW(IDB_BITMAP_BAZZI);
	bitmap7.LoadBitmapW(IDB_BITMAP_DAO);
	oldbitmap = memDC.SelectObject(&bitmap2);

	BITMAP bmpinfo, bmpinfo2, bmpinfomap1, bmpinfomap2, bmpinfo_cham;
	bitmap1.GetBitmap(&bmpinfo);
	bitmap3.GetBitmap(&bmpinfo2);
	bitmap4.GetBitmap(&bmpinfomap1);
	bitmap5.GetBitmap(&bmpinfomap2);
	bitmap6.GetBitmap(&bmpinfo_cham);

	memDC.SelectObject(&bitmap1);

	setRect();
	//1P
	memDC.SelectObject(&bitmap6);
	pDC->StretchBlt(rect_1P.left, rect_1P.top, rect_1P.Width(), rect_1P.Height(), &memDC, 0, 0, bmpinfo_cham.bmWidth, bmpinfo_cham.bmHeight, SRCCOPY);

	//2P or AI
	memDC.SelectObject(&bitmap7);
	pDC->StretchBlt(rect_2P.left, rect_2P.top, rect_2P.Width(), rect_2P.Height(), &memDC, 0, 0, bmpinfo_cham.bmWidth, bmpinfo_cham.bmHeight, SRCCOPY);


	//MAP
	switch (m_nSelectMap)
	{
	case MAP_BASE:
		memDC.SelectObject(&bitmap5);
		pDC->StretchBlt(rect_Map.left, rect_Map.top, rect_Map.Width(), rect_Map.Height(), &memDC, 0, 0, bmpinfomap2.bmWidth, bmpinfomap2.bmHeight, SRCCOPY);
		break;
	case MAP_WALL:
		memDC.SelectObject(&bitmap4);
		pDC->StretchBlt(rect_Map.left, rect_Map.top, rect_Map.Width(), rect_Map.Height(), &memDC, 0, 0, bmpinfomap1.bmWidth, bmpinfomap1.bmHeight, SRCCOPY);
		break;
	}

	//HELP
	if (m_nClickWhat == RECT_HELP)
	{
		rect_Help.right -= 10;
		rect_Help.bottom -= 10;
		memDC.SelectObject(&bitmap2);
		pDC->StretchBlt(rect_Help.left, rect_Help.top, rect_Help.Width(), rect_Help.Height(), &memDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
	}
	else
	{
		memDC.SelectObject(&bitmap2);
		pDC->StretchBlt(rect_Help.left, rect_Help.top, rect_Help.Width(), rect_Help.Height(), &memDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
	}
	//START
	if (m_nClickWhat == RECT_START)
	{
		rect_Start.right -= 10;
		rect_Start.bottom -= 10;
		memDC.SelectObject(&bitmap1);
		pDC->StretchBlt(rect_Start.left, rect_Start.top, rect_Start.Width(), rect_Start.Height(), &memDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
	}
	else
	{
		memDC.SelectObject(&bitmap1);
		pDC->StretchBlt(rect_Start.left, rect_Start.top, rect_Start.Width(), rect_Start.Height(), &memDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
	}
	//SELECT MODE
	if (m_nClickWhat == RECT_SELECTMODE)
	{
		rect_SelectMode.right -= 10;
		rect_SelectMode.bottom -= 10;
		memDC.SelectObject(&bitmap3);
		pDC->StretchBlt(rect_SelectMode.left, rect_SelectMode.top, rect_SelectMode.Width(), rect_SelectMode.Height(), &memDC, 0, 0, bmpinfo2.bmWidth, bmpinfo2.bmHeight, SRCCOPY);
	}
	else
	{
		memDC.SelectObject(&bitmap3);
		pDC->StretchBlt(rect_SelectMode.left, rect_SelectMode.top, rect_SelectMode.Width(), rect_SelectMode.Height(), &memDC, 0, 0, bmpinfo2.bmWidth, bmpinfo2.bmHeight, SRCCOPY);
	}

	memDC.SelectObject(oldbitmap);

}


void CC_A_v01View::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CRect rect;
	GetClientRect(&rect);

	if (m_nViewMode == MAP_MODE)
	{
		switch (nChar)
		{
		case VK_LEFT:
			m_nVector1 = LEFT;
			switch (WhatIsThere(LEFT))
			{
			case ROAD:
				m_nX -= rect.Height() / 15;
				break;
			case FIRE:
				m_nDie = DIE1;
				m_nViewMode = ENDING_MODE;
				KillTimer(0);
				break;
			}
			break;
		case VK_DOWN:
			m_nVector1 = DOWN;
			switch (WhatIsThere(DOWN))
			{
			case ROAD:
				m_nY += rect.Height() / 15;
				break;
			case FIRE:
				m_nDie = DIE1;
				m_nViewMode = ENDING_MODE;
				KillTimer(0);
				break;
			}
			break;
		case VK_RIGHT:
			m_nVector1 = RIGHT;
			switch (WhatIsThere(RIGHT))
			{
			case ROAD:
				m_nX += rect.Height() / 15;
				break;
			case FIRE:
				m_nDie = DIE1;
				m_nViewMode = ENDING_MODE;
				KillTimer(0);
				break;
			}
			break;
		case VK_UP:
			m_nVector1 = UP;
			switch (WhatIsThere(UP))
			{
			case ROAD:
				m_nY -= rect.Height() / 15;
				break;
			case FIRE:
				m_nDie = DIE1;
				m_nViewMode = ENDING_MODE;
				KillTimer(0);
				break;
			}
			break;
		}

		Invalidate();
	}
	else if (m_nViewMode == HELP_MODE)
	{
		switch (nChar)
		{
		case VK_ESCAPE:
			m_nViewMode = HOME_MODE;

			Invalidate();
			break;
		}
	}

	CView::OnKeyDown(nChar, nRepCnt, nFlags);
}


void CC_A_v01View::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (m_nViewMode == HOME_MODE)
	{
		if (IsInBox(point.x, point.y, rect_1P))
		{
			m_nClickWhat = RECT_1P;
		}

		if (IsInBox(point.x, point.y, rect_2P))
		{
			m_nClickWhat = RECT_2P;
		}

		if (IsInBox(point.x, point.y, rect_Map))
		{
			m_nClickWhat = RECT_MAP;
		}

		if (IsInBox(point.x, point.y, rect_Help))
		{
			m_nClickWhat = RECT_HELP;
		}

		if (IsInBox(point.x, point.y, rect_Start))
		{
			m_nClickWhat = RECT_START;
		}

		if (IsInBox(point.x, point.y, rect_SelectMode))
		{
			m_nClickWhat = RECT_SELECTMODE;
		}

		Invalidate();
	}
	if (m_nViewMode == MAP_MODE)
	{

	}
	if (m_nViewMode == ENDING_MODE)
	{
		if (IsInBox(point.x, point.y, rect_ReStart))
		{
			m_nViewMode = HOME_MODE;
		}

		if (IsInBox(point.x, point.y, rect_Exit))
		{
			PostQuitMessage(0);
		}

		Invalidate();
	}

	CView::OnLButtonDown(nFlags, point);
}


void CC_A_v01View::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rect;
	GetClientRect(&rect);

	if (IsInBox(point.x, point.y, rect_1P))
	{
		if (m_nClickWhat == RECT_1P)
		{
			//TODO:
		}
		else
		{
			m_nClickWhat = 0;
		}
	}
	else if (IsInBox(point.x, point.y, rect_2P))
	{
		if (m_nClickWhat == RECT_2P)
		{
			//TODO:
		}
		else
		{
			m_nClickWhat = 0;
		}
	}
	else if (IsInBox(point.x, point.y, rect_Map))
	{
		if (m_nClickWhat == RECT_MAP)
		{
			//TODO:
			++m_nSelectMap %= 2;
		}
		else
		{
			m_nClickWhat = 0;
		}
	}
	else if (IsInBox(point.x, point.y, rect_Help))
	{
		if (m_nClickWhat == RECT_HELP)
		{
			//TODO:
			m_nViewMode = HELP_MODE;

			Invalidate();
		}
		else
		{
			m_nClickWhat = 0;
		}
	}
	else if (IsInBox(point.x, point.y, rect_Start))
	{
		if (m_nClickWhat == RECT_START)
		{
			//TODO:
			m_nViewMode = MAP_MODE;
			SetTimer(0, 200, NULL);

			SetPos();

			Invalidate();
		}
		else
		{
			m_nClickWhat = 0;
		}
	}
	else if (IsInBox(point.x, point.y, rect_SelectMode))
	{
		if (m_nClickWhat == RECT_SELECTMODE)
		{
			//TODO:
		}
		else
		{
			m_nClickWhat = 0;
		}
	}
	m_nClickWhat = 0;
	

	if (m_nViewMode == HOME_MODE)
	{
		Invalidate();
	}
	else if (m_nViewMode == MAP_MODE)
	{

	}
	else if (m_nViewMode == ENDING_MODE)
	{
		Invalidate();
	}

	CView::OnLButtonUp(nFlags, point);
}


void CC_A_v01View::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CRect rect;
	GetClientRect(&rect);

	if (m_nViewMode == MAP_MODE)
	{
		switch (nChar)
		{
		case 'F':
		case 'f':
			m_nVector2 = LEFT;
			switch (WhatIsThere2(LEFT))
			{
			case ROAD:
				m_nX2 -= rect.Height() / 15;
				break;
			case FIRE:
				m_nDie = DIE2;
				m_nViewMode = ENDING_MODE;
				KillTimer(0);
				break;
			}
			break;
		case 'G':
		case 'g':
			m_nVector2 = DOWN;
			switch (WhatIsThere2(DOWN))
			{
			case ROAD:
				m_nY2 += rect.Height() / 15;
				break;
			case FIRE:
				m_nDie = DIE2;
				m_nViewMode = ENDING_MODE;
				KillTimer(0);
				break;
			}
			break;
		case 'H':
		case 'h':
			m_nVector2 = RIGHT;
			switch (WhatIsThere2(RIGHT))
			{
			case ROAD:
				m_nX2 += rect.Height() / 15;
				break;
			case FIRE:
				m_nDie = DIE2;
				m_nViewMode = ENDING_MODE;
				KillTimer(0);
				break;
			}
			break;
		case 'T':
		case 't':
			m_nVector2 = UP;
			switch (WhatIsThere2(UP))
			{
			case ROAD:
				m_nY2 -= rect.Height() / 15;
				break;
			case FIRE:
				m_nDie = DIE2;
				m_nViewMode = ENDING_MODE;
				KillTimer(0);
				break;
			}
			break;
		case 'L':
		case 'l':
			switch (m_nSelectMap)
			{
			case MAP_BASE:
				Map_Base[WhatIsPos().x][WhatIsPos().y] = BOMB_0;
				break;
			case MAP_WALL:
				Map_Wall[WhatIsPos().x][WhatIsPos().y] = BOMB_0;
				break;
			}
			break;
		case 'Z':
		case 'z':
			switch (m_nSelectMap)
			{
			case MAP_BASE:
				Map_Base[WhatIsPos2().x][WhatIsPos2().y] = BOMB_0;
				break;
			case MAP_WALL:
				Map_Wall[WhatIsPos2().x][WhatIsPos2().y] = BOMB_0;
				break;
			}
			break;
		}

		Invalidate();
	}

	CView::OnChar(nChar, nRepCnt, nFlags);
}


CPoint CC_A_v01View::WhatIsPos2()
{
	CPoint Pos;
	CRect rect;
	GetClientRect(&rect);

	int i, j;

	for (i = 0; i < 15; i++)
	{
		for (j = 0; j < 15; j++)
		{
			if (rect.Height()*j / 15 <= m_nX2 && m_nX2 < rect.Height()*(j + 1) / 15)
			{
				Pos.y = j;
			}

			if (rect.Height()*i / 15 <= m_nY2 && m_nY2 < rect.Height()*(i + 1) / 15)
			{
				Pos.x = i;
			}
		}
	}

	return Pos;
}


int CC_A_v01View::WhatIsThere2(int vector)
{
	CRect rect;
	GetClientRect(&rect);

	switch (m_nSelectMap)
	{
	case MAP_BASE:
		switch (vector)
		{
		case LEFT:
			if (WhatIsPos2().y == 0)
			{
				return 0;
			}
			else
			{
				return Map_Base[WhatIsPos2().x][WhatIsPos2().y - 1];
			}
			break;
		case DOWN:
			if (WhatIsPos2().x == 14)
			{
				return 0;
			}
			else
			{
				return Map_Base[WhatIsPos2().x + 1][WhatIsPos2().y];
			}
			break;
		case RIGHT:
			if (WhatIsPos2().y == 14)
			{
				return 0;
			}
			else
			{
				return Map_Base[WhatIsPos2().x][WhatIsPos2().y + 1];
			}
			break;
		case UP:
			if (WhatIsPos2().x == 0)
			{
				return 0;
			}
			else
			{
				return Map_Base[WhatIsPos2().x - 1][WhatIsPos2().y];
			}
			break;
		}
		break;
	case MAP_WALL:
		switch (vector)
		{
		case LEFT:
			if (WhatIsPos2().y == 0)
			{
				return 0;
			}
			else
			{
				return Map_Wall[WhatIsPos2().x][WhatIsPos2().y - 1];
			}
			break;
		case DOWN:
			if (WhatIsPos2().x == 14)
			{
				return 0;
			}
			else
			{
				return Map_Wall[WhatIsPos2().x + 1][WhatIsPos2().y];
			}
			break;
		case RIGHT:
			if (WhatIsPos2().y == 14)
			{
				return 0;
			}
			else
			{
				return Map_Wall[WhatIsPos2().x][WhatIsPos2().y + 1];
			}
			break;
		case UP:
			if (WhatIsPos2().x == 0)
			{
				return 0;
			}
			else
			{
				return Map_Wall[WhatIsPos2().x - 1][WhatIsPos2().y];
			}
			break;
		}
		break;
	}
	return 0;
}




void CC_A_v01View::DrawEnding(CDC* pDC)
{
	//엔딩화면에 그릴 그림을 표시합니다.

	CRect rect;
	GetClientRect(&rect);

	CDC memDC;
	memDC.CreateCompatibleDC(pDC);

	CBitmap bitmap1, bitmap2, *oldbitmap;
	bitmap1.LoadBitmapW(IDB_BITMAP_RESTARTBTN);
	bitmap2.LoadBitmapW(IDB_BITMAP_EXITBTN);
	oldbitmap = memDC.SelectObject(&bitmap2);

	BITMAP bmpinfo;
	bitmap1.GetBitmap(&bmpinfo);
	memDC.SelectObject(&bitmap1);

	setRect();

	//RESTART
		memDC.SelectObject(&bitmap1);
		pDC->StretchBlt(rect_ReStart.left, rect_ReStart.top, rect_ReStart.Width(), rect_ReStart.Height(), &memDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);
	
	//EXIT
		memDC.SelectObject(&bitmap2);
		pDC->StretchBlt(rect_Exit.left, rect_Exit.top, rect_Exit.Width(), rect_Exit.Height(), &memDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);

		CFont font;

		//font.CreateFontW(200, 200, 0, 0, FW_HEAVY, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("굴림"));
		font.CreatePointFont(900, _T("굴림"));
		pDC->SelectObject(&font);
		if (m_nDie == DIE2)
		{
			pDC->TextOutW(rect.Width() * 1 / 4, 30, _T("1P"));
		}
		else if(m_nDie == DIE1)
		{
			pDC->TextOutW(rect.Width() * 1 / 4, 30, _T("2P"));
		}
		pDC->TextOutW(rect.Width() * 2 / 4, 30, _T("WIN"));

		font.DeleteObject();

		memDC.SelectObject(oldbitmap);
}


void CC_A_v01View::SetPos()
{
	CRect rect;
	GetClientRect(&rect);

	m_nX2 = 0;
	m_nY2 = 0;

	m_nX = rect.Height() * 14 / 15;
	m_nY = rect.Height() * 14 / 15;
}


void CC_A_v01View::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	SetPos();
}


void CC_A_v01View::DrawHelp(CDC* pDC)
{
	CRect rect;
	GetClientRect(&rect);

	CDC memDC;
	memDC.CreateCompatibleDC(pDC);

	CBitmap bitmap1, *oldbitmap;
	bitmap1.LoadBitmapW(IDB_BITMAP_HELP);
	oldbitmap = memDC.SelectObject(&bitmap1);

	BITMAP bmpinfo;
	bitmap1.GetBitmap(&bmpinfo);
	memDC.SelectObject(&bitmap1);

	memDC.SelectObject(&bitmap1);
	pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &memDC, 0, 0, bmpinfo.bmWidth, bmpinfo.bmHeight, SRCCOPY);

	memDC.SelectObject(oldbitmap);
}
