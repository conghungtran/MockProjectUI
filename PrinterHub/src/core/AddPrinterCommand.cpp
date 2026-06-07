#include "pch.h"
#include "AddPrinterCommand.h"

#include "pch.h"
#include "AddPrinterCommand.h"
#include "../ui/PrinterHubDoc.h"

using namespace PrinterHub::Core;

AddPrinterCommand::AddPrinterCommand(const Printer& printer)
    : m_printer(printer)
{
}

void AddPrinterCommand::execute()
{

    CPrinterHubDoc* pDoc = (CPrinterHubDoc*)AfxGetApp()->GetMainWnd()->GetActiveDocument();
    if (pDoc)
    {
        pDoc->AddPrinter(m_printer);
    }
}

void AddPrinterCommand::undo()
{
    if (!m_executed) return;

    CPrinterHubDoc* pDoc = GetDocument();
    if (pDoc)
    {
        // Tìm printer vừa thêm (theo ID) và xóa
        int nIndex = pDoc->FindPrinterById(m_printer.getId());
        if (nIndex != -1)
        {
            pDoc->DeletePrinter(nIndex);
            m_executed = false;
        }
    }
}