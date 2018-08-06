
// FluidSimulationView.cpp : CFluidSimulationView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "FluidSimulation.h"
#endif

#include "FluidSimulationDoc.h"
#include "FluidSimulationView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CFluidSimulationView

IMPLEMENT_DYNCREATE(CFluidSimulationView, CView)

BEGIN_MESSAGE_MAP(CFluidSimulationView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CFluidSimulationView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_WM_CREATE()
END_MESSAGE_MAP()

// CFluidSimulationView ����/����

CFluidSimulationView::CFluidSimulationView()
{
	// TODO: �ڴ˴���ӹ������

}

CFluidSimulationView::~CFluidSimulationView()
{
	delete mThreadHandle;
	if (mOSG != 0)
	{
		delete mOSG;
	}
	if (sph)
	{
		delete sph;
	}
}

BOOL CFluidSimulationView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CFluidSimulationView ����

void CFluidSimulationView::OnDraw(CDC* /*pDC*/)
{
	CFluidSimulationDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���
}


// CFluidSimulationView ��ӡ


void CFluidSimulationView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CFluidSimulationView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CFluidSimulationView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CFluidSimulationView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
}

void CFluidSimulationView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CFluidSimulationView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CFluidSimulationView ���

#ifdef _DEBUG
void CFluidSimulationView::AssertValid() const
{
	CView::AssertValid();
}

void CFluidSimulationView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CFluidSimulationDoc* CFluidSimulationView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CFluidSimulationDoc)));
	return (CFluidSimulationDoc*)m_pDocument;
}
#endif //_DEBUG


// CFluidSimulationView ��Ϣ�������


int CFluidSimulationView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CView::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  �ڴ������ר�õĴ�������
	mOSG = new cOSG(m_hWnd);

	return 0;
}


void CFluidSimulationView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	mOSG->InitOSG();

	// Start the thread to do OSG Rendering
	
	mThreadHandle = new CRenderingThread(mOSG);
	mThreadHandle->start();
	Sleep(500);

	sph = new CSPH();
	sph->Init(4000);
	sph->run(mOSG);



	// TODO: �ڴ����ר�ô����/����û���
}


	//test
	/*int number = 1000;
	mOSG->SetSphereNum(number);
	Sleep(500);


	double pos[3] = {0, 0, 0};
	double color[3] = {0, 0, 0};
	int index = 0;

	for (double i=0; i<10; i++)
	{
		pos[0] += 100.0/9; 
		color[0] += 255.0/9;

		for (int j=0; j<10; j++)
		{
			pos[1] += 100.0/9;
			color[1] += 255.0/9;

			for(int k=0; k<10; k++)
			{
				pos[2] += 100.0/9;
				color[2] += 255.0/9;

				mOSG->SetSphereProperty(index, pos, color);
				index++;
			}
			pos[2] = 0;
			color[2] = 0;
		}
		pos[1] = 0;
		color[1] = 0;
	}*/