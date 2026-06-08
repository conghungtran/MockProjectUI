
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

#include "../core/Printer.h"

#include "../core/ControllerStatus.h"
#include "../core/EnumConverter.h"
#include "../core/ConvertData.h"
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
	ON_BN_CLICKED(IDC_BUTTON_PRINTER_ADD_PRINTER, &CPrinterHubView::OnBnClickedButtonAdd)

	ON_BN_CLICKED(IDC_BUTTON_PRINTER_EDIT_PRINTER, &CPrinterHubView::OnBnClickedButtonPrinterEditPrinter)
	ON_BN_CLICKED(IDC_BUTTON_PRINTER_DELETE_PRINTER, &CPrinterHubView::OnBnClickedButtonPrinterDeletePrinter)
	ON_BN_CLICKED(IDC_BUTTON_PRINTER_UNDO, &CPrinterHubView::OnBnClickedButtonPrinterUndo)
	ON_BN_CLICKED(IDC_BUTTON_PRINTER_REDO, &CPrinterHubView::OnBnClickedButtonPrinterRedo)
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

	//DDX_Control(pDX, IDC_BUTTON_PRINTER_ADD_PRINTER, m_btnAdd);
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
	dwStyle |= LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP | LVS_EX_CHECKBOXES;
	m_listPrinters.SetExtendedStyle(dwStyle);

	// Thiết lập cột cho List Printers
	m_listPrinters.InsertColumn(0, _T("STT"), LVCFMT_LEFT, 100);        // Cột checkbox (để trống)
	m_listPrinters.InsertColumn(2, _T("ID"), LVCFMT_LEFT, 100);
	m_listPrinters.InsertColumn(3, _T("MODEL"), LVCFMT_LEFT, 200);
	m_listPrinters.InsertColumn(4, _T("BRAND"), LVCFMT_LEFT, 200);
	m_listPrinters.InsertColumn(5, _T("STATUS"), LVCFMT_LEFT, 200);
	m_listPrinters.InsertColumn(6, _T("PURCHASE DATE"), LVCFMT_LEFT, 300);
	m_listPrinters.InsertColumn(7, _T("WARRANTY MONTH"), LVCFMT_LEFT, 200);
	
	// Dữ liệu mẫu
	//int nItem = m_listPrinters.InsertItem(0, _T("Printer-01"));
	//m_listPrinters.SetItemText(nItem, 1, _T("CMG"));
	//m_listPrinters.SetItemText(nItem, 2, _T("HP"));
	//m_listPrinters.SetItemText(nItem, 3, _T("RETIRED"));
	//m_listPrinters.SetItemText(nItem, 4, _T("9/19/2009"));
	//m_listPrinters.SetItemText(nItem, 5, _T("7"));


	//LoadFile();

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
		std::cout << "Add Dialog Pop up\n";

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
	if (!pDoc) {
		TRACE(_T("OnUpdate: No document\n"));
		return;
	}

	// Xử lý theo lHint
	switch (lHint)
	{
	case DocumentStatus::PRINTER_ADDED:
	{
		int nIndex = (int)(INT_PTR)pHint;
		TRACE(_T("PRINTER_ADDED: index = %d\n"), nIndex);

		if (nIndex >= 0 && nIndex < pDoc->GetPrinterCount()) {
			const auto& printer = pDoc->GetPrinter(nIndex);

			AddPrinterToList(
				ConvertData::StringToCString(printer.getId()),
				ConvertData::StringToCString(printer.getModel()),
				EnumConverter::FromPrinterBrand(printer.getBrand()),
				EnumConverter::FromPrinterStatus(printer.getStatus()),
				ConvertData::StringToCString(printer.getPurchaseDate()),
				printer.getWarrantyMonth()
			);

			// Scroll đến item mới và chọn nó
			int nItemIndex = m_listPrinters.GetItemCount() - 1;
			m_listPrinters.EnsureVisible(nItemIndex, FALSE);
			m_listPrinters.SetItemState(nItemIndex, LVIS_SELECTED | LVIS_FOCUSED,
				LVIS_SELECTED | LVIS_FOCUSED);
		}
		break;
	}

	case DocumentStatus::PRINTER_UPDATED:
	{
		int nIndex = (int)(INT_PTR)pHint;
		TRACE(_T("PRINTER_UPDATED: index = %d\n"), nIndex);

		if (nIndex >= 0 && nIndex < pDoc->GetPrinterCount()) {
			const auto& printer = pDoc->GetPrinter(nIndex);
			UpdatePrinterInList(nIndex, printer);

			// Highlight dòng vừa cập nhật
			m_listPrinters.SetItemState(nIndex, LVIS_SELECTED | LVIS_FOCUSED,
				LVIS_SELECTED | LVIS_FOCUSED);
			m_listPrinters.EnsureVisible(nIndex, FALSE);
		}
		break;
	}

	case DocumentStatus::PRINTER_DELETED:
	{
		int nIndex = (int)(INT_PTR)pHint;
		TRACE(_T("PRINTER_DELETED: index = %d\n"), nIndex);

		if (nIndex >= 0) {
			DeletePrinterFromList(nIndex);

			// Chọn item tiếp theo nếu còn
			int nItemCount = m_listPrinters.GetItemCount();
			if (nItemCount > 0) {
				int nNewIndex = (nIndex < nItemCount) ? nIndex : nItemCount - 1;
				m_listPrinters.SetItemState(nNewIndex, LVIS_SELECTED | LVIS_FOCUSED,
					LVIS_SELECTED | LVIS_FOCUSED);
				m_listPrinters.EnsureVisible(nNewIndex, FALSE);
			}
		}
		break;
	}

	case DocumentStatus::PRINTERS_CLEARED:
	{
		TRACE(_T("PRINTERS_CLEARED\n"));
		m_listPrinters.DeleteAllItems();
		break;
	}


	default:
	{
		// Không có hint cụ thể hoặc hint không xác định → refresh toàn bộ
		TRACE(_T("OnUpdate: Unknown hint = %ld, refreshing all\n"), lHint);
		break;
	}
	}

	// Cập nhật trạng thái Undo/Redo buttons
	//UpdateUndoRedoButtons();

	// Cập nhật status bar
	//UpdateStatusBar();
}

void CPrinterHubView::UpdatePrinterInList(int nIndex, const Printer& printer)
{
	std::cout << "CPrinterHubView::UpdatePrinterInList called with nIndex = " << nIndex << std::endl;
	// ✅ Chỉ cập nhật item tại index, KHÔNG xóa toàn bộ
	m_listPrinters.SetItemText(nIndex, 0, CString(printer.getId().c_str()));
	m_listPrinters.SetItemText(nIndex, 1, CString(printer.getModel().c_str()));
	m_listPrinters.SetItemText(nIndex, 2, EnumConverter::FromPrinterBrand(printer.getBrand()));
	m_listPrinters.SetItemText(nIndex, 3, EnumConverter::FromPrinterStatus(printer.getStatus()));
	m_listPrinters.SetItemText(nIndex, 4, CString(printer.getPurchaseDate().c_str()));

	CString strWarranty;
	strWarranty.Format(_T("%d"), printer.getWarrantyMonth());
	m_listPrinters.SetItemText(nIndex, 5, strWarranty);
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
	CString strValue;
	strValue.Format(_T("%d"), nIndex);

	m_listPrinters.InsertItem(nIndex, strValue);
	m_listPrinters.SetItemText(nIndex,1, strId);
	m_listPrinters.SetItemText(nIndex, 2, strModel);
	m_listPrinters.SetItemText(nIndex, 3, strBrand);
	m_listPrinters.SetItemText(nIndex, 4, strStatus);
	m_listPrinters.SetItemText(nIndex, 5, strPurchaseDate);

	CString strWarrantyMonth;
	strWarrantyMonth.Format(_T("%d"), intWarrantyMonth);
	m_listPrinters.SetItemText(nIndex, 6, strWarrantyMonth);

}


void CPrinterHubView::DeletePrinterFromList(int nIndex)
{
	if (nIndex < 0 || nIndex >= m_listPrinters.GetItemCount()) {
		TRACE(_T("DeletePrinterFromList: Invalid index %d\n"), nIndex);
		return;
	}

	m_listPrinters.DeleteItem(nIndex);
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
		std::cout << "92929  " << ConvertData::CStringToString(dlg.cstr_Id) << std::endl;
		PrinterHub::Core::Printer printer;
		dlg.GetPrinter(printer);
		printer.setId(ConvertData::CStringToString(dlg.cstr_Id));  // Giữ nguyên ID cũ
		std::cout << "Updated Printer Info:\n";
		std::cout << "ID: " << printer.getId() << std::endl;
		std::cout << "Model: " << printer.getModel() << std::endl;
		std::cout << "Warranty Month: " << printer.getWarrantyMonth() << std::endl;
		CPrinterHubDoc* pDoc = GetDocument();
		//pDoc->EditPrinter(nSel, printer);


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

	CPrinterHubDoc* pDoc = GetDocument();
	pDoc->DeletePrinter(nSel);
}

// CPrinterHubView.cpp

void CPrinterHubView::OnBnClickedButtonPrinterUndo()
{
	// Lấy Document
	CPrinterHubDoc* pDoc = GetDocument();
	if (!pDoc) {
		TRACE(_T("OnBnClickedButtonPrinterUndo: No document\n"));
		return;
	}

	// Kiểm tra xem có thể Undo không
	if (!pDoc->CanUndo()) {
		TRACE(_T("OnBnClickedButtonPrinterUndo: Cannot undo\n"));

		// Optional: Hiển thị tooltip hoặc message
		// AfxMessageBox(_T("Nothing to undo"), MB_ICONINFORMATION);
		return;
	}

	// Thực hiện Undo
	pDoc->Undo();


	// Cập nhật trạng thái nút Undo/Redo (optional)
	//UpdateUndoRedoButtons();

	// Log
	TRACE(_T("Undo performed\n"));
}

void CPrinterHubView::OnBnClickedButtonPrinterRedo()
{
	// Lấy Document
	CPrinterHubDoc* pDoc = GetDocument();
	if (!pDoc) {
		TRACE(_T("OnBnClickedButtonPrinterRedo: No document\n"));
		return;
	}

	// Kiểm tra xem có thể Redo không
	if (!pDoc->CanRedo()) {
		TRACE(_T("OnBnClickedButtonPrinterRedo: Cannot redo\n"));

		// Optional: Hiển thị tooltip
		// AfxMessageBox(_T("Nothing to redo"), MB_ICONINFORMATION);
		return;
	}

	// Thực hiện Redo
	pDoc->Redo();

	// Refresh hiển thị

	// Cập nhật trạng thái nút Undo/Redo (optional)
	//UpdateUndoRedoButtons();

	// Log
	TRACE(_T("Redo performed\n"));
}



//
//// Optional: Cập nhật trạng thái nút Undo/Redo (enable/disable)
//void CPrinterHubView::UpdateUndoRedoButtons()
//{
//	CPrinterHubDoc* pDoc = GetDocument();
//	if (!pDoc) return;
//
//	// Lấy button từ toolbar hoặc dialog
//	// Cách 1: Nếu dùng toolbar button
//	// CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
//	// CToolBar& toolbar = pMainFrame->GetToolBar();
//	// toolbar.EnableButton(ID_BUTTON_UNDO, pDoc->CanUndo());
//	// toolbar.EnableButton(ID_BUTTON_REDO, pDoc->CanRedo());
//
//	// Cách 2: Nếu dùng button trên dialog
//	// GetDlgItem(IDC_BUTTON_UNDO)->EnableWindow(pDoc->CanUndo());
//	// GetDlgItem(IDC_BUTTON_REDO)->EnableWindow(pDoc->CanRedo());
//
//	// Cách 3: Cập nhật text trên status bar
//	// CStatusBar* pStatusBar = ...;
//	// CString strUndo;
//	// strUndo.Format(_T("Undo: %s"), pDoc->CanUndo() ? _T("Available") : _T("Not available"));
//	// pStatusBar->SetPaneText(0, strUndo);
//}