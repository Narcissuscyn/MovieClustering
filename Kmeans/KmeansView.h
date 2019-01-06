
// KmeansView.h : CKmeansView ��Ľӿ�
//

#pragma once
#include "DataSet.h"
#include "Windef.h"
class CKmeansView : public CView
{
protected: // �������л�����
	CKmeansView();
	DECLARE_DYNCREATE(CKmeansView)

// ����
public:
	CKmeansDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CKmeansView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	void initData();
	DataSet *data1[10];
	DataSet *data2[15];
	DataSet *data3[20];

	CPoint points[300];
	int counts=0;
	int k = 3;
	CPoint u[3];

	CPoint points1[100];
	CPoint points2[100];
	CPoint points3[100];
	int counts1=0, counts2=0, counts3 = 0;
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	// �����������
	int analyseDistance(CPoint p1, CPoint p2, CPoint p3, CPoint p4);
	CPoint analyseCenter(CPoint* points, CPoint u,int num);
	void drawResult();
	afx_msg void OnAnalysis();
};

#ifndef _DEBUG  // KmeansView.cpp �еĵ��԰汾
inline CKmeansDoc* CKmeansView::GetDocument() const
   { return reinterpret_cast<CKmeansDoc*>(m_pDocument); }
#endif

