
// PrinterHubDoc.cpp : implementation of the CPrinterHubDoc class
//

#include "pch.h"
#include "framework.h"
#include "ControllerStatus.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "PrinterHub.h"
#endif

#include "PrinterHubDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CPrinterHubDoc

IMPLEMENT_DYNCREATE(CPrinterHubDoc, CDocument)

BEGIN_MESSAGE_MAP(CPrinterHubDoc, CDocument)
END_MESSAGE_MAP()


// CPrinterHubDoc construction/destruction

CPrinterHubDoc::CPrinterHubDoc() noexcept
{
	// TODO: add one-time construction code here

}
//
void CPrinterHubDoc::AddPrinter(const PrinterHub::Core::Printer& printer) {
	if (printer.getId().empty()) {
		std::cout << "CPrinterHubDoc::AddPrinter: printer ID is empty\n";
		return;
	}

	// 1. Xử lý logic / Thêm dữ liệu vào bộ nhớ tạm của Document
	int nIndex = m_arrPrinters.GetSize();
	std::cout << "CPrinterHubDoc:Index: " << nIndex << std::endl;
	m_arrPrinters.Add(printer);
	SetModifiedFlag(TRUE);

	// 2. (Tùy chọn) Lưu dữ liệu vào Database tại đây nếu cần
	// OpenDatabaseConnection();
	// ExecuteSQL("INSERT INTO Students ..."); 

	// 3. GỌI UPDATEALLVIEWS ĐỂ BÁO CHO VIEW BIẾT DATA ĐÃ THAY ĐỔI
	// NULL nghĩa là báo cho TẤT CẢ các View đang gắn với Document này
	UpdateAllViews(NULL, DocumentStatus::PRINTER_CREATE, (CObject*)(INT_PTR)nIndex);
}

void CPrinterHubDoc::EditPrinter(PrinterHub::Core::Printer& printer) {

	if (printer.getId().empty()) {
		std::cout << "CPrinterHubDoc::AddPrinter: printer ID is empty\n";
		return;
	}

	// 1. Xử lý logic / Thêm dữ liệu vào bộ nhớ tạm của Document
	int nIndex = m_arrPrinters.GetSize();
	for (int i = 0; i < nIndex; i++)
	{
		if (m_arrPrinters[i] == printer) {
			//m_arrPrinters[i].setA(
			//	printer.getModel(),
			//	printer.getBrand(),
			//	printer.getStatus(),
			//	printer.getPurchaseDate(),
			//	printer.getWarrantyMonth()
			//);

			m_arrPrinters[i] = printer;
			break;
		}
	}



	std::cout << "CPrinterHubDoc:Index: " << nIndex << std::endl;
	SetModifiedFlag(TRUE);

	// 2. (Tùy chọn) Lưu dữ liệu vào Database tại đây nếu cần
	// OpenDatabaseConnection();
	// ExecuteSQL("INSERT INTO Students ..."); 

	// 3. GỌI UPDATEALLVIEWS ĐỂ BÁO CHO VIEW BIẾT DATA ĐÃ THAY ĐỔI
	// NULL nghĩa là báo cho TẤT CẢ các View đang gắn với Document này
	UpdateAllViews(NULL, DocumentStatus::PRINTER_UPDATE, (CObject*)(INT_PTR)nIndex);
}


// CPrinterHubDoc.cpp
//PrinterHub::Core::Printer& CPrinterHubDoc::GetPrinter(int nIndex)
//{
//	ASSERT(nIndex >= 0 && nIndex < m_arrPrinters.GetSize());
//	return m_arrPrinters[nIndex];  // ← Trả về non-const reference
//}

const PrinterHub::Core::Printer& CPrinterHubDoc::GetPrinter(int nIndex) const
{
	ASSERT(nIndex >= 0 && nIndex < m_arrPrinters.GetSize());
	return m_arrPrinters[nIndex];  // ← Trả về const reference
}

void CPrinterHubDoc::UpdatePrinter(int nIndex, const PrinterHub::Core::Printer& printer) {
	UpdateAllViews(NULL, DocumentStatus::PRINTER_UPDATE, NULL);
}

void CPrinterHubDoc::DeletePrinter(int nIndex) {
	UpdateAllViews(NULL, DocumentStatus::PRINTER_DELETE, NULL);
}

void CPrinterHubDoc::DeleteAllPrinters() {
	UpdateAllViews(NULL, DocumentStatus::PRINTER_DELETE_ALL, NULL);
}

CPrinterHubDoc::~CPrinterHubDoc()
{
}

BOOL CPrinterHubDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}




// CPrinterHubDoc serialization

void CPrinterHubDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

#ifdef SHARED_HANDLERS

// Support for thumbnails
void CPrinterHubDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// Modify this code to draw the document's data
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// Support for Search Handlers
void CPrinterHubDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// Set search contents from document's data.
	// The content parts should be separated by ";"

	// For example:  strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CPrinterHubDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CPrinterHubDoc diagnostics

#ifdef _DEBUG
void CPrinterHubDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPrinterHubDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CPrinterHubDoc commands
