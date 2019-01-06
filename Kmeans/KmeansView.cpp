
// KmeansView.cpp : CKmeansView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "Kmeans.h"
#endif

#include "KmeansDoc.h"
#include "KmeansView.h"
#include "stdlib.h"
#include<time.h>
#include "afxwin.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

bool flag = true;
int center=0;
// CKmeansView

IMPLEMENT_DYNCREATE(CKmeansView, CView)

BEGIN_MESSAGE_MAP(CKmeansView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_WM_LBUTTONDOWN()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_ANALYSIS, &CKmeansView::OnAnalysis)
END_MESSAGE_MAP()

// CKmeansView 构造/析构

CKmeansView::CKmeansView()
{
	// TODO:  在此处添加构造代码
}

CKmeansView::~CKmeansView()
{
}

BOOL CKmeansView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CKmeansView 绘制

void CKmeansView::OnDraw(CDC* pDC)
{
	CKmeansDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	//initData();
	
}


// CKmeansView 打印

BOOL CKmeansView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CKmeansView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CKmeansView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// CKmeansView 诊断

#ifdef _DEBUG
void CKmeansView::AssertValid() const
{
	CView::AssertValid();
}

void CKmeansView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CKmeansDoc* CKmeansView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CKmeansDoc)));
	return (CKmeansDoc*)m_pDocument;
}
#endif //_DEBUG


void CKmeansView::initData()
{

}

void CKmeansView::OnLButtonDown(UINT nFlags, CPoint point)
{
	CDC* cd = this->GetDC();
	if (flag)
	{
		points[counts] = point;
		CPen pen(PS_SOLID, 5, RGB(0, 0,0));
		cd->SelectObject(&pen);
		cd->MoveTo(points[counts]);
		cd->AngleArc(points[counts].x,points[counts].y, 5, 0, 360);
		counts++;
	}
		
	CView::OnLButtonDown(nFlags, point);
	cd->DeleteDC();

}


void CKmeansView::OnRButtonDown(UINT nFlags, CPoint point)
{
	CDC* cd = this->GetDC();
	flag = false;

	u[center]= point;
	CPen pen(PS_SOLID, 5, RGB(0, 0, 255));
	cd->SelectObject(&pen);
	cd->MoveTo(u[center]);
	cd->AngleArc(u[center].x, u[center].y, 5, 0, 360);
	center++;

	if (center == 3)
	{
		drawResult();
	}
	CView::OnRButtonDown(nFlags, point);
}



// 计算两点距离
int CKmeansView::analyseDistance(CPoint p1, CPoint p2,CPoint p3,CPoint p4)
{
	float distance1 = 0;
	float distance2 = 0;
	float distance3 = 0;
	distance1 = sqrt(pow(float(p1.x - p2.x), 2)+pow(float(p1.y - p2.y), 2));
	distance2 = sqrt(pow(float(p1.x - p3.x), 2) + pow(float(p1.y - p3.y), 2));
	distance3 = sqrt(pow(float(p1.x - p4.x), 2) + pow(float(p1.y - p4.y), 2));
	if(min(distance3, min(distance1, distance2))==distance1)
	{
		points1[counts1] = p1;
	//	this->GetDC()->LineTo(points1[)
		counts1++;
		return 1;
	}
	else if (min(distance3, min(distance1, distance2)) == distance2)
	{
		points2[counts2] = p1;
		counts2++;
		return 2;
	}
	else
	{
		points3[counts3] = p1;
		counts3++;
		return 3;
	}
}


CPoint CKmeansView::analyseCenter(CPoint* points, CPoint u,int num)
{
	
		int sum_x = 0,sum_y=0;
	for (int i = 0; i < num;i++)
	{
		sum_x += points[i].x;
		sum_y += points[i].y;
	}
	u.x = (int)sum_x / num;
	u.y = (int)sum_y / num;
	return u;
}


void CKmeansView::drawResult()
{

	CDC* cd = this->GetDC();
	CRect rc;
	GetClientRect(&rc);
	cd->FillSolidRect(&rc, RGB(255, 255, 255));
	for (int i = 0; i < counts; i++)
	{
		analyseDistance(points[i], u[0], u[1], u[2]);
	}
	
	CPen pen1(PS_SOLID, 5, RGB(0, 0, 0));
	cd->SelectObject(&pen1);
	for (int i = 0; i < counts1; i++)
	{
		cd->MoveTo(points1[i]);
		cd->AngleArc(points1[i].x, points1[i].y, 5, 0, 360);
	}
	CPen pen2(PS_SOLID, 5, RGB(0, 255, 0));
	cd->SelectObject(&pen2);
	for (int i = 0; i < counts2; i++)
	{

		cd->MoveTo(points2[i]);
		cd->AngleArc(points2[i].x, points2[i].y, 5, 0, 360);
	}
	CPen pen3(PS_SOLID, 5, RGB(255, 0, 0));
	cd->SelectObject(&pen3);
	for (int i = 0; i < counts3; i++)
	{

		cd->MoveTo(points3[i]);
		cd->AngleArc(points3[i].x, points3[i].y, 5, 0, 360);
	}
	CPen pen(PS_SOLID, 5, RGB(0, 0, 255));
	cd->SelectObject(&pen);
	for (int  i = 0; i < 3; i++)
	{
		cd->MoveTo(u[i]);
		cd->AngleArc(u[i].x, u[i].y, 5, 0, 360);
	}
	
	cd->DeleteDC();

}


void CKmeansView::OnAnalysis()
{
	u[0]=analyseCenter(points1, u[0], counts1);
	u[1]=analyseCenter(points2, u[1], counts2);
	u[2]=analyseCenter(points3, u[2], counts3);
	counts1 = 0;
	counts2 = 0;
	counts3 = 0;
	for (int i = 0; i < counts; i++)
	{
		analyseDistance(points[i], u[0], u[1], u[2]);
	}

	drawResult();
}
