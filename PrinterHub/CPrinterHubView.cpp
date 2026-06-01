
// CPrinterHubView.cpp : implementation of the CPrinterHubView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PrinterHub.h"
#endif

#include "PrinterHubDoc.h"
#include "CPrinterHubView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#include "CAddPrinterDlg.h"
#include <iostream>


// CPrinterHubView

IMPLEMENT_DYNCREATE(CPrinterHubView, CFormView)

BEGIN_MESSAGE_MAP(CPrinterHubView, CFormView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CFormView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CPrinterHubView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	//ON_BN_CLICKED(IDC_BUTTON8, &CPrinterHubView::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON5, &CPrinterHubView::OnBnClickedButtonOK)
	ON_BN_CLICKED(IDC_BUTTON4, &CPrinterHubView::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON1, &CPrinterHubView::OnBnClickedButtonEdit)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST3, &CPrinterHubView::OnLvnItemchangedList3)
END_MESSAGE_MAP()

// CPrinterHubView construction/destruction

CPrinterHubView::CPrinterHubView() noexcept
	: CFormView(IDD_PRINTERHUB_FORM)
{
	// TODO: add construction code here

}

CPrinterHubView::~CPrinterHubView()
{
}

void CPrinterHubView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST2, m_listFirmWare);
	DDX_Control(pDX, IDC_LIST1, m_ListPrinters);
	DDX_Control(pDX, IDC_LIST3, m_listTicket);
}

BOOL CPrinterHubView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow(cs);
}

void CPrinterHubView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// Thiết lập cột cho List Printers
	m_ListPrinters.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_ListPrinters.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 100);
	m_ListPrinters.InsertColumn(1, _T("MODEL"), LVCFMT_LEFT, 200);
	m_ListPrinters.InsertColumn(2, _T("BRAND"), LVCFMT_LEFT, 200);
	m_ListPrinters.InsertColumn(3, _T("PURCHASE DATE"), LVCFMT_LEFT, 300);
	m_ListPrinters.InsertColumn(4, _T("WARRANTY MONTH"), LVCFMT_LEFT, 200);

	//// Dữ liệu mẫu
	int nItem = m_ListPrinters.InsertItem(0, _T("Printer-01"));
	m_ListPrinters.SetItemText(nItem, 1, _T("Online"));
	m_ListPrinters.SetItemText(nItem, 2, _T("192.168.1.10"));
	m_ListPrinters.SetItemText(nItem, 3, _T("HP LaserJet"));

	//// Firmware queue mẫu
	m_listFirmWare.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listFirmWare.InsertColumn(0, _T("INDEX"), LVCFMT_LEFT, 100);
	m_listFirmWare.InsertColumn(1, _T("NAME"), LVCFMT_LEFT, 200);
	m_listFirmWare.InsertColumn(2, _T("VERSION"), LVCFMT_LEFT, 200);
	m_listFirmWare.InsertColumn(3, _T("STATUS"), LVCFMT_LEFT, 200);

	int nItemFirmWare = m_listFirmWare.InsertItem(0, _T("1"));
	m_listFirmWare.SetItemText(nItemFirmWare, 1, _T("HP LaserJet Pro"));
	m_listFirmWare.SetItemText(nItemFirmWare, 2, _T("Firmware v2.1.0"));
	m_listFirmWare.SetItemText(nItemFirmWare, 3, _T("Pending"));

	// Tickets mẫu
	// Firmware queue mẫu
	m_listTicket.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);
	m_listTicket.InsertColumn(0, _T("Priority"), LVCFMT_LEFT, 150);
	m_listTicket.InsertColumn(1, _T("DESCRIPTION"), LVCFMT_LEFT, 150);
	m_listTicket.InsertColumn(2, _T("PRINTER"), LVCFMT_LEFT, 150);
	m_listTicket.InsertColumn(3, _T("STATUS"), LVCFMT_LEFT, 150);

	int nItemTicket = m_listTicket.InsertItem(0, _T("Critical"));
	m_listTicket.SetItemText(nItemTicket, 1, _T("No Paper"));
	m_listTicket.SetItemText(nItemTicket, 2, _T("PRN-001"));
	m_listTicket.SetItemText(nItemTicket, 3, _T("Open"));



	GetParentFrame()->RecalcLayout();
	ResizeParentToFit();

}


// CPrinterHubView printing


void CPrinterHubView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CPrinterHubView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPrinterHubView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPrinterHubView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

void CPrinterHubView::OnPrint(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO: add customized printing code here
}

void CPrinterHubView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CPrinterHubView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CPrinterHubView diagnostics

#ifdef _DEBUG
void CPrinterHubView::AssertValid() const
{
	CFormView::AssertValid();
}

void CPrinterHubView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}

CPrinterHubDoc* CPrinterHubView::GetDocument() const
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPrinterHubDoc)));
	return (CPrinterHubDoc*)m_pDocument;
}
#endif //_DEBUG


// CPrinterHubView message handlers

void CPrinterHubView::OnBnClickedButton8()
{
	// TODO: Add your control notification handler code here
}

void CPrinterHubView::OnBnClickedButtonOK()
{
	CAddPrinterDlg dlg;
	if (dlg.DoModal() == IDOK) {
		std::cout << "ID value: " << CT2A(dlg.cstr_Id) << std::endl;
		std::cout << "Clicked Add and Continue\n";
	}

}

void CPrinterHubView::OnBnClickedButton4()
{
	int nSel = m_ListPrinters.GetNextItem(-1, LVNI_SELECTED);
	if (nSel >= 0)
		m_ListPrinters.DeleteItem(nSel);
	else
		AfxMessageBox(_T("Vui lòng chọn máy in cần xóa!"));
}

void CPrinterHubView::OnBnClickedButtonEdit()
{
	int nSel = m_ListPrinters.GetNextItem(-1, LVNI_SELECTED);
	// Cách 1: Lấy text từ cột 0 (cột đầu tiên)
	CString strValue = m_ListPrinters.GetItemText(nSel, 0);
	std::cout << "Column 0 value: " << CT2A(strValue) << std::endl;

	CString strValue1 = m_ListPrinters.GetItemText(nSel, 1);
	std::cout << "Column 1 value: " << CT2A(strValue1) << std::endl;

	CString strValue2 = m_ListPrinters.GetItemText(nSel, 2);
	std::cout << "Column 2 value: " << CT2A(strValue2) << std::endl;

	CString strValue3 = m_ListPrinters.GetItemText(nSel, 3);
	std::cout << "Column 3 value: " << CT2A(strValue3) << std::endl;
	CAddPrinterDlg dlg;
	if (dlg.DoModal() == IDOK) {

	}
}

void CPrinterHubView::OnLvnItemchangedList3(NMHDR* pNMHDR, LRESULT* pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}
