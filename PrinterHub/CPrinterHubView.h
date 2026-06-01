
// CPrinterHubView.h : interface of the CPrinterHubView class
//

#pragma once


class CPrinterHubView : public CFormView
{
protected: // create from serialization only
	CPrinterHubView() noexcept;
	DECLARE_DYNCREATE(CPrinterHubView)

public:
#ifdef AFX_DESIGN_TIME
	enum{ IDD = IDD_PRINTERHUB_FORM };
#endif

// Attributes
public:
	CPrinterHubDoc* GetDocument() const;

// Operations
public:

// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CPrinterHubView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	CListCtrl IDC_LIST_TICKETS;
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton5();
};

#ifndef _DEBUG  // debug version in CPrinterHubView.cpp
inline CPrinterHubDoc* CPrinterHubView::GetDocument() const
   { return reinterpret_cast<CPrinterHubDoc*>(m_pDocument); }
#endif

