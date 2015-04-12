// MyPhysicsDoc.cpp : CMyPhysicsDoc 类的实现
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


// CMyPhysicsDoc 构造/析构

CMyPhysicsDoc::CMyPhysicsDoc()
{
	// TODO: 在此添加一次性构造代码

}

CMyPhysicsDoc::~CMyPhysicsDoc()
{
}

BOOL CMyPhysicsDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}




// CMyPhysicsDoc 序列化

void CMyPhysicsDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}


// CMyPhysicsDoc 诊断

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


// CMyPhysicsDoc 命令
