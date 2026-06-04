
// PrinterHubDoc.h : interface of the CPrinterHubDoc class
//


#pragma once
#include "../core/Printer.h"


class CPrinterHubDoc : public CDocument
{
protected: // create from serialization only
	CPrinterHubDoc() noexcept;
	DECLARE_DYNCREATE(CPrinterHubDoc)

// Attributes
public:
	CArray<PrinterHub::Core::Printer, PrinterHub::Core::Printer> m_arrPrinters;
// Operations
public:

	// CRUD operations
	void AddPrinter(const PrinterHub::Core::Printer& printer);
	void EditPrinter(PrinterHub::Core::Printer& printer);


	void UpdatePrinter(int nIndex, const PrinterHub::Core::Printer& printer);
	void DeletePrinter(int nIndex);
	void DeleteAllPrinters();
	
	const  PrinterHub::Core::Printer& GetPrinter(int nIndex) const;
	//PrinterHub::Core::Printer& GetPrinter(int nIndex);

	int GetPrinterCount() const { return m_arrPrinters.GetSize(); }
	
// Overrides
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);

#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// Implementation
public:
	virtual ~CPrinterHubDoc();

	//const CArray<PrinterInfo, PrinterInfo&>& GetPrinters() const { return m_arrPrinters; }

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// Helper function that sets search content for a Search Handler
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
};
