// MyPhysicsDoc.h : CMyPhysicsDoc ��Ľӿ�
//


#pragma once


class CMyPhysicsDoc : public CDocument
{
protected: // �������л�����
	CMyPhysicsDoc();
	DECLARE_DYNCREATE(CMyPhysicsDoc)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

// ʵ��
public:
	virtual ~CMyPhysicsDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};


