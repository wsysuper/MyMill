// MyPhysicsDoc.cpp : CMyPhysicsDoc ���ʵ��
//

#include "stdafx.h"
#include "MyPhysics.h"

#include "MyPhysicsDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMyPhysicsDoc

IMPLEMENT_DYNCREATE(CMyPhysicsDoc, CDocument)

BEGIN_MESSAGE_MAP(CMyPhysicsDoc, CDocument)
END_MESSAGE_MAP()


// CMyPhysicsDoc ����/����

CMyPhysicsDoc::CMyPhysicsDoc()
{
	// TODO: �ڴ����һ���Թ������

}

CMyPhysicsDoc::~CMyPhysicsDoc()
{
}

BOOL CMyPhysicsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: �ڴ�������³�ʼ������
	// (SDI �ĵ������ø��ĵ�)

	return TRUE;
}




// CMyPhysicsDoc ���л�

void CMyPhysicsDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: �ڴ���Ӵ洢����
	}
	else
	{
		// TODO: �ڴ���Ӽ��ش���
	}
}


// CMyPhysicsDoc ���

#ifdef _DEBUG
void CMyPhysicsDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMyPhysicsDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMyPhysicsDoc ����
