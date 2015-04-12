// MainFrm.cpp : CMainFrame ���ʵ��
//

#include "stdafx.h"
#include "MyPhysics.h"

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
//	ON_UPDATE_COMMAND_UI(ID_VIEW_ITEM_BAR, &CMainFrame::OnUpdateViewItemBar)
//	ON_COMMAND(ID_VIEW_ITEM_BAR, &CMainFrame::OnViewItemBar)

END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // ״̬��ָʾ��
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};


// CMainFrame ����/����

CMainFrame::CMainFrame()
{
	// TODO: �ڴ���ӳ�Ա��ʼ������
}

CMainFrame::~CMainFrame()
{
}


int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("δ�ܴ���������\n");
		return -1;      // δ�ܴ���
	}

	//if (!m_ItemBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_LEFT
	//	| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
	//	!m_ItemBar.LoadToolBar(IDR_ITEMBAR))
	//{
	//	TRACE0("δ�ܴ���ͼ�ι�����\n");
	//	return -1;      // δ�ܴ���
	//}


	for(int i = 0; i < m_wndToolBar.GetCount(); i++)
	{
		UINT id = m_wndToolBar.GetItemID(i);
		CString s;
		if(!s.LoadString(id)) continue;
		int j = s.Find(_T('\n'));
		if(j < 0) continue;
		s = s.Right(s.GetLength() - j - 1);
		m_wndToolBar.SetButtonText(i,s);
	}// Adjust sizes to include text

	//for(int i = 0; i < m_ItemBar.GetCount(); i++)
	//{
	//	UINT id = m_ItemBar.GetItemID(i);
	//	CString s;
	//	if(!s.LoadString(id)) continue;
	//	int j = s.Find(_T('\n'));
	//	if(j < 0) continue;
	//	s = s.Right(s.GetLength() - j - 1);
	//	m_ItemBar.SetButtonText(i,s);
	//}// Adjust sizes to include text

	CRect rect;
	m_wndToolBar.GetItemRect(0,&rect);
	m_wndToolBar.SetSizes(rect.Size(),CSize(16,15));
	//m_ItemBar.GetItemRect(0,&rect);
	//m_ItemBar.SetSizes(rect.Size(),CSize(40,40));

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("δ�ܴ���״̬��\n");
		return -1;      // δ�ܴ���
	}

	// TODO: �������Ҫ��������ͣ������ɾ���⼸��
	EnableDocking(CBRS_ALIGN_ANY);

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);

	//m_ItemBar.EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_ItemBar);

	m_DialogBar.Create(this,IDD_DIALOGBAR,CBRS_RIGHT|CBRS_TOOLTIPS|CBRS_FLYBY,IDD_DIALOGBAR);

	m_DialogBar.EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_DialogBar);

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ
	return TRUE;
}


// CMainFrame ���

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG


// CMainFrame ��Ϣ�������
//
//void CMainFrame::OnUpdateViewItemBar(CCmdUI *pCmdUI)
//{
//	// TODO: Add your command update UI handler code here
//	pCmdUI->SetCheck(m_ItemBar.IsWindowVisible());
//}
//
//void CMainFrame::OnViewItemBar()
//{
//	m_ItemBar.ShowWindow(m_ItemBar.IsWindowVisible() ? SW_HIDE : SW_SHOW);
//	RecalcLayout();
//}
