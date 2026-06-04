
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

#include "Printer.h"

#include "ControllerStatus.h"
#include "EnumConverter.h"
using namespace PrinterHub::Core;


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
	ON_BN_CLICKED(IDC_BUTTON_PRINTER_ADD_PRINTER, &CPrinterHubView::OnBnClickedButtonAdd)

	ON_BN_CLICKED(IDC_BUTTON_PRINTER_EDIT_PRINTER, &CPrinterHubView::OnBnClickedButtonPrinterEditPrinter)
	ON_BN_CLICKED(IDC_BUTTON_PRINTER_DELETE_PRINTER, &CPrinterHubView::OnBnClickedButtonPrinterDeletePrinter)
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
	DDX_Control(pDX, IDC_LIST1, m_listPrinters);
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
	CPrinterHubView::InitializeListControl();

}

void CPrinterHubView::InitializeListControl() {

	DWORD dwStyle = m_listPrinters.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP;
	m_listPrinters.SetExtendedStyle(dwStyle);

	// Thiết lập cột cho List Printers
	m_listPrinters.InsertColumn(0, _T("ID"), LVCFMT_LEFT, 100);
	m_listPrinters.InsertColumn(1, _T("MODEL"), LVCFMT_LEFT, 200);
	m_listPrinters.InsertColumn(2, _T("BRAND"), LVCFMT_LEFT, 200);
	m_listPrinters.InsertColumn(3, _T("STATUS"), LVCFMT_LEFT, 200);
	m_listPrinters.InsertColumn(4, _T("PURCHASE DATE"), LVCFMT_LEFT, 300);
	m_listPrinters.InsertColumn(5, _T("WARRANTY MONTH"), LVCFMT_LEFT, 200);

	// Dữ liệu mẫu
	int nItem = m_listPrinters.InsertItem(0, _T("Printer-01"));
	m_listPrinters.SetItemText(nItem, 1, _T("CMG"));
	m_listPrinters.SetItemText(nItem, 2, _T("HP"));
	m_listPrinters.SetItemText(nItem, 3, _T("RETIRED"));
	m_listPrinters.SetItemText(nItem, 4, _T("9/19/2009"));
	m_listPrinters.SetItemText(nItem, 5, _T("7"));

	// Firmware queue mẫu
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

void CPrinterHubView::OnBnClickedButtonAdd()
{
	CPrinterHubDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc) return;

	CAddPrinterDlg dlg;
	dlg.SetMode(CAddPrinterDlg::ModeAdd);

	if (dlg.DoModal() == IDOK) {
		std::cout << "ID value: " << CT2A(dlg.cstr_Id) << std::endl;
		std::cout << "Clicked Add and Continue\n";

		std::cout << "ID: " << CT2A(dlg.cstr_Id) << std::endl;
		std::cout << "Model: " << CT2A(dlg.cstr_Model) << std::endl;
		std::cout << "Brand: " << CT2A(dlg.cstr_Brand) << std::endl;
		std::cout << "Status: " << CT2A(dlg.cstr_Status) << std::endl;
		std::cout << "Purchase: " << CT2A(dlg.cstr_PurchaseDate) << std::endl;
		std::cout << "Warranty Month: " << dlg.int_WarrantyMonth << std::endl;

		std::string str_id = ConvertData::CStringToString(dlg.cstr_Id);
		std::string str_model = ConvertData::CStringToString(dlg.cstr_Model);

		PrinterStatus status = EnumConverter::ToPrinterStatus(dlg.cstr_Status);
		PrinterBrand brand = EnumConverter::ToPrinterBrand(dlg.cstr_Brand);


		std::string str_purchaseDate = ConvertData::CStringToString(dlg.cstr_PurchaseDate);
		int int_warrantyMonth = dlg.int_WarrantyMonth;

		Printer printer(str_id, str_model, brand, status, str_purchaseDate, int_warrantyMonth);
		pDoc->AddPrinter(printer);

	}
}


void CPrinterHubView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	 CPrinterHubDoc* pDoc = GetDocument();

	// Hàm này được gọi tự động sau khi Document chạy UpdateAllViews
	if (lHint == DocumentStatus::PRINTER_CREATE)
	{
		//PrinterHub::Core::Printer* _printer = (PrinterHub::Core::Printer*)object;

		int nIndex = (int)(INT_PTR)pHint;  // Ép từ CObject* về int

		std::cout << "CPrinterHubView::OnUpdate called with PRINTER_CREATE, nIndex = " << nIndex << std::endl;
		const auto& _printer = pDoc->GetPrinter(nIndex);

		//if (_printer.getId().empty()) {
		//	std::cout << "CPrinterHubView.cpp: Printer is NULL\n";
		//	return;
		//}

		AddPrinterToList(
			ConvertData::StringToCString(_printer.getId()),
			ConvertData::StringToCString(_printer.getModel()),
			EnumConverter::FromPrinterBrand(_printer.getBrand()),
			EnumConverter::FromPrinterStatus(_printer.getStatus()),
			ConvertData::StringToCString(_printer.getPurchaseDate()),
			_printer.getWarrantyMonth()
		);

		std::cout << "CPrinterHubView::OnUpdate called with lHint = " << lHint << std::endl;
	}
	else if (lHint == DocumentStatus::PRINTER_UPDATE)
	{
		int nIndex = (int)(INT_PTR)pHint;  // Ép từ CObject* về int
		std::cout << "CPrinterHubView::OnUpdate called with PRINTER_UPDATE, nIndex = " << nIndex << std::endl;
		const auto& _printer = pDoc->GetPrinter(nIndex);
		// Cách đơn giản: Xóa item cũ rồi thêm lại item mới
		m_listPrinters.DeleteItem(nIndex);
		AddPrinterToList(
			ConvertData::StringToCString(_printer.getId()),
			ConvertData::StringToCString(_printer.getModel()),
			EnumConverter::FromPrinterBrand(_printer.getBrand()),
			EnumConverter::FromPrinterStatus(_printer.getStatus()),
			ConvertData::StringToCString(_printer.getPurchaseDate()),
			_printer.getWarrantyMonth()
		);

		std::cout << "CPrinterHubView::OnUpdate called with lHint = " << lHint << std::endl;
		
	}
	else
	{
		// Nếu lHint = 0 hoặc các số khác, vẽ lại toàn bộ
		Invalidate();
	}
	Invalidate();
}

void CPrinterHubView::OnDraw(CDC* pDC)
{
	CPrinterHubDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc) return;

	//// Tiến hành vẽ danh sách sinh viên mới nhất từ Document lên màn hình
	//for (int i = 0; i < pDoc->m_arrPrinters.GetSize(); i++)
	//{
	//	//pDC->TextOut(10, y, pDoc->m_arrPrinters.GetAt(i));
	//	std::cout << CT2A(pDoc->m_arrPrinters.GetAt(0)) << std::endl;
	//	//y += 20; // Xuống dòng cho sinh viên tiếp theo
	//}
}



// Hàm thêm dữ liệu vào List Control
void CPrinterHubView::AddPrinterToList(
	const CString& strId,
	const CString& strModel,
	const CString& strBrand,
	const CString& strStatus,
	const CString& strPurchaseDate,
	const int& intWarrantyMonth)
{
	// Thêm item mới
	int nIndex = m_listPrinters.GetItemCount();

	// Cột 0: ID máy in
	m_listPrinters.InsertItem(nIndex, strId);

	m_listPrinters.SetItemText(nIndex, 1, strModel);
	m_listPrinters.SetItemText(nIndex, 2, strBrand);
	m_listPrinters.SetItemText(nIndex, 3, strStatus);
	m_listPrinters.SetItemText(nIndex, 4, strPurchaseDate);

	CString strWarrantyMonth;
	strWarrantyMonth.Format(_T("%d"), intWarrantyMonth);
	m_listPrinters.SetItemText(nIndex, 5, strWarrantyMonth);



	//// Optional: Lưu thêm data pointer (nếu cần)
	//PrinterInfo* pInfo = new PrinterInfo();
	//pInfo->strName = strName;
	//pInfo->strIP = strIP;
	//pInfo->nPort = nPort;
	//m_listPrinters.SetItemData(nIndex, (DWORD_PTR)pInfo);

	//// Scroll đến item vừa thêm
	//m_listPrinters.EnsureVisible(nIndex, FALSE);

	//// Chọn item vừa thêm
	//m_listPrinters.SetItemState(nIndex, LVIS_SELECTED, LVIS_SELECTED);
}

void CPrinterHubView::OnBnClickedButtonPrinterEditPrinter()
{
	int nSel = m_listPrinters.GetNextItem(-1, LVNI_SELECTED);
	std::cout << "Selected item index: " << nSel << std::endl;

	// Cách 1: Lấy text từ cột 0 (cột đầu tiên)
	CString str_id = m_listPrinters.GetItemText(nSel, 0);
	CString str_model = m_listPrinters.GetItemText(nSel, 1);
	CString str_brand = m_listPrinters.GetItemText(nSel, 2);
	CString str_status = m_listPrinters.GetItemText(nSel, 3);
	CString str_purchaseDate = m_listPrinters.GetItemText(nSel, 4);
	CString str_warrantyMonth = m_listPrinters.GetItemText(nSel, 5);

	std::cout << "Selected Printer Info:\n";
	std::cout << "ID: " << CT2A(str_id) << std::endl;
	std::cout << "Model: " << CT2A(str_model) << std::endl;
	std::cout << "Brand: " << CT2A(str_brand) << std::endl;
	std::cout << "Status: " << CT2A(str_status) << std::endl;
	std::cout << "Purchase Date: " << CT2A(str_purchaseDate) << std::endl;
	std::cout << "Warranty Month: " << CT2A(str_warrantyMonth) << std::endl;

	
	if (nSel == -1) {
		AfxMessageBox(_T("Please choose Printer !"));
		return;
	}

	CAddPrinterDlg dlg;
	dlg.SetMode(CAddPrinterDlg::ModeEdit);
	dlg.SetEditData(str_id, str_model, str_brand, str_status, str_purchaseDate, 
		ConvertData::CStringToInt(str_warrantyMonth));

	if (dlg.DoModal() == IDOK) {
		PrinterHub::Core::Printer printer;
		dlg.GetPrinter(printer);

		CPrinterHubDoc* pDoc = GetDocument();
		pDoc->EditPrinter(printer);




		std::cout << "Edited \n";

		
	}
}

void CPrinterHubView::OnBnClickedButtonPrinterDeletePrinter()
{
	int nSel = m_listPrinters.GetNextItem(-1, LVNI_SELECTED);
	if (nSel >= 0)
		m_listPrinters.DeleteItem(nSel);
	else
		AfxMessageBox(_T("Vui lòng chọn máy in cần xóa!"));

}
