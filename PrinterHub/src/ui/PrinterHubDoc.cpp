
// PrinterHubDoc.cpp : implementation of the CPrinterHubDoc class
//

#include "pch.h"
#include "framework.h"
#include "../core/ControllerStatus.h"
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
#include "io/CsvReader.h"
#include "io/CsvWriter.h"
#include "core/ConvertData.h"
#include "core/Enumconverter.h"

using namespace PrinterHub::Core;

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
void CPrinterHubDoc::AddPrinter(const PrinterHub::Core::Printer& printer, int mode = 0) {
	if (printer.getId().empty()) {
		std::cout << "CPrinterHubDoc::AddPrinter: printer ID is empty\n";
		return;
	}

	// 1. Xử lý logic / Thêm dữ liệu vào bộ nhớ tạm của Document
	int nIndex = m_arrPrinters.GetSize();
	std::cout << "CPrinterHubDoc:Index: " << nIndex << std::endl;
	m_arrPrinters.Add(printer);
	SetModifiedFlag(TRUE);

	// 2. Save Data
    if (mode == 1) {
        std::cout << "Adding printer to CSV: \n";
        AppendPrinterToCSV(printer, _T("printers.csv"));
    }
   

	

	// 3. GỌI UPDATEALLVIEWS ĐỂ BÁO CHO VIEW BIẾT DATA ĐÃ THAY ĐỔI
	// NULL nghĩa là báo cho TẤT CẢ các View đang gắn với Document này
	UpdateAllViews(NULL, DocumentStatus::PRINTER_CREATE, (CObject*)(INT_PTR)nIndex);
}

void CPrinterHubDoc::EditPrinter(int index, PrinterHub::Core::Printer& printer) {

	std::cout << printer.getId() << std::endl;
	std::cout << printer.getModel() << std::endl;

	m_arrPrinters[index] = printer;


	std::cout << "CPrinterHubDoc:Index: " << index << std::endl;
	SetModifiedFlag(TRUE);

	// 2. (Tùy chọn) Lưu dữ liệu vào Database tại đây nếu cần
	
    UpdatePrinterInCSV(_T("printers.csv"), index, printer);

	// 3. GỌI UPDATEALLVIEWS ĐỂ BÁO CHO VIEW BIẾT DATA ĐÃ THAY ĐỔI
	// NULL nghĩa là báo cho TẤT CẢ các View đang gắn với Document này
	UpdateAllViews(NULL, DocumentStatus::PRINTER_UPDATE, (CObject*)(INT_PTR)index);
}

// Đọc danh sách Printer từ CSV
bool CPrinterHubDoc::LoadPrintersFromCSV(const CString& strFilePath, CPrinterHubDoc* pDoc)
{
    using namespace PrinterHub::Core;

    CsvReader reader;
    reader.SetDelimiter(_T(','));
    reader.SetHasHeader(true);  // Dòng đầu là header

    std::vector<std::vector<CString>> data;
    if (!reader.ReadAll(strFilePath, data))
    {
        AfxMessageBox(_T("Cannot load printers from CSV"));
        return false;
    }

    for (const auto& row : data)
    {
        if (row.size() >= 6)
        {
            Printer printer(
                ConvertData::CStringToString(row[0]),  // ID
                ConvertData::CStringToString(row[1]),  // Model
                EnumConverter::ToPrinterBrand(row[2]), // Brand
                EnumConverter::ToPrinterStatus(row[3]),// Status
                ConvertData::CStringToString(row[4]),  // Purchase Date
                _ttoi(row[5])                          // Warranty Month
            );
            pDoc->AddPrinter(printer);
        }
    }

    return true;
}

// Trong CPrinterHubDoc.cpp
bool CPrinterHubDoc::AppendPrinterToCSV(const Printer& printer, const CString& strFilePath)
{
    CStdioFile file;

    // Mở file ở chế độ append (ghi tiếp vào cuối)
    if (!file.Open(strFilePath, CFile::modeWrite | CFile::modeCreate | CFile::modeNoTruncate))
    {
        TRACE(_T("Cannot open file for append: %s\n"), strFilePath);
        return false;
    }

    // Di chuyển con trỏ đến cuối file
    file.SeekToEnd();

    // Format dòng dữ liệu mới
    CString strLine;
    strLine.Format(_T("%s,%s,%s,%s,%s,%d\n"),
        CString(printer.getId().c_str()),
        CString(printer.getModel().c_str()),
        EnumConverter::FromPrinterBrand(printer.getBrand()),
        EnumConverter::FromPrinterStatus(printer.getStatus()),
        CString(printer.getPurchaseDate().c_str()),
        printer.getWarrantyMonth());

    // Ghi xuống file
    file.WriteString(strLine);
    file.Close();

    TRACE(_T("Appended printer to CSV: %s\n"), printer.getId().c_str());
    return true;
}

// Ghi danh sách Printer xuống CSV
bool CPrinterHubDoc::SavePrintersToCSV(const CString& strFilePath, CPrinterHubDoc* pDoc)
{
    using namespace PrinterHub::Core;

    CsvWriter writer;
    writer.SetDelimiter(_T(','));
    writer.SetQuoteStrings(true);  // Tự động thêm quotes khi cần

    // Ghi header
    std::vector<CString> header = { _T("ID"), _T("Model"), _T("Brand"),
                                   _T("Status"), _T("PurchaseDate"), _T("WarrantyMonth") };
    if (!writer.WriteHeader(strFilePath, header, true))
    {
        return false;
    }

    // Ghi dữ liệu
    for (int i = 0; i < pDoc->GetPrinterCount(); i++)
    {
        const auto& printer = pDoc->GetPrinter(i);

        std::vector<CString> row;
        row.push_back(CString(printer.getId().c_str()));
        row.push_back(CString(printer.getModel().c_str()));
        row.push_back(EnumConverter::FromPrinterBrand(printer.getBrand()));
        row.push_back(EnumConverter::FromPrinterStatus(printer.getStatus()));
        row.push_back(CString(printer.getPurchaseDate().c_str()));

        CString strWarranty;
        strWarranty.Format(_T("%d"), printer.getWarrantyMonth());
        row.push_back(strWarranty);

        if (!writer.AppendRow(strFilePath, row))
        {
            return false;
        }
    }

    return true;
}

// Cập nhật một dòng cụ thể
bool CPrinterHubDoc::UpdatePrinterInCSV(const CString& strFilePath, int nRowIndex, const Printer& printer)
{
    using namespace PrinterHub::Core;

    CsvWriter writer;
    writer.SetDelimiter(_T(','));

    std::vector<CString> row;
    row.push_back(CString(printer.getId().c_str()));
    row.push_back(CString(printer.getModel().c_str()));
    row.push_back(EnumConverter::FromPrinterBrand(printer.getBrand()));
    row.push_back(EnumConverter::FromPrinterStatus(printer.getStatus()));
    row.push_back(CString(printer.getPurchaseDate().c_str()));

    CString strWarranty;
    strWarranty.Format(_T("%d"), printer.getWarrantyMonth());
    row.push_back(strWarranty);

    // Cập nhật dòng thứ nRowIndex (bỏ qua header)
    return writer.UpdateRow(strFilePath, nRowIndex, row, true);
}

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
