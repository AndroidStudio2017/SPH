
// FluidSimulationView.h : CFluidSimulationView ��Ľӿ�
//

#pragma once
#include "MFC_OSG.h"
#include "SPH.h"


class CFluidSimulationView : public CView
{
protected: // �������л�����
	CFluidSimulationView();
	DECLARE_DYNCREATE(CFluidSimulationView)

// ����
public:
	CFluidSimulationDoc* GetDocument() const;

	cOSG *mOSG;
	CRenderingThread* mThreadHandle;

	CSPH *sph;



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
	virtual ~CFluidSimulationView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnInitialUpdate();
};

#ifndef _DEBUG  // FluidSimulationView.cpp �еĵ��԰汾
inline CFluidSimulationDoc* CFluidSimulationView::GetDocument() const
   { return reinterpret_cast<CFluidSimulationDoc*>(m_pDocument); }
#endif

