// CAddPrinterDlg.cpp : implementation file
//

#include "pch.h"
#include "PrinterHub.h"
#include "afxdialogex.h"
#include "CAddPrinterDlg.h"
#include <iostream>


// CAddPrinterDlg dialog

IMPLEMENT_DYNAMIC(CAddPrinterDlg, CDialogEx)

CAddPrinterDlg::CAddPrinterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_ADD_PRINTER, pParent)
{

}

// MyDialog.cpp
BOOL CAddPrinterDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // Load Brands
    m_cboBrand.AddString(_T("DELL"));
    m_cboBrand.AddString(_T("LG"));
    m_cboBrand.AddString(_T("SAMSUNG"));
    m_cboBrand.AddString(_T("TOSHIBA"));
    m_cboBrand.SetCurSel(0);

    // Load Brands
    m_cboStatus.AddString(_T("ACTIVE"));
    m_cboStatus.AddString(_T("RETIRED"));
    m_cboStatus.AddString(_T("IN PROCESS"));
    m_cboStatus.SetCurSel(0);

    // Load districts for default city (Hà Nội)
    //LoadDistricts(0);

    return TRUE;
}


CAddPrinterDlg::~CAddPrinterDlg()
{
}

void CAddPrinterDlg::DoDataExchange(CDataExchange* pDX)
{
    CDialogEx::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT_ADD_PRINTER_BRAND, m_cboBrand);
    DDX_Control(pDX, IDC_EDIT_ADD_PRINTER_ID, m_editId);
    DDX_Control(pDX, IDC_EDIT_ADD_PRINTER_MODEL, m_editModel);
    DDX_Control(pDX, IDC_EDIT_ADD_PRINTER_DATE, m_dtpPurchaseDate);
    DDX_Control(pDX, IDC_EDIT_ADD_PRINTER_WARRANTY, m_editWarrantyMonth);
    DDX_Control(pDX, IDC_EDIT_ADD_PRINTER_STATUS, m_cboStatus);

    // Automatically map
    DDX_Text(pDX,IDC_EDIT_ADD_PRINTER_ID, cstr_Id); 



    
}


BEGIN_MESSAGE_MAP(CAddPrinterDlg, CDialogEx)
    ON_BN_CLICKED(IDC_BUTTON_ADD_CONTINUE, &CAddPrinterDlg::OnBnClickedButtonAddContinue)
END_MESSAGE_MAP()


// CAddPrinterDlg message handlers

void CAddPrinterDlg::OnBnClickedButtonAddContinue()
{
    UpdateData(TRUE);
    if (cstr_Id.IsEmpty())
    {
        AfxMessageBox(_T("ID cannot be empty"));
        return;
    }

    if (cstr_Model.IsEmpty())
    {
        AfxMessageBox(_T("Model cannot be empty"));
        return;
    }

    if (cstr_Brand.IsEmpty())
    {
        AfxMessageBox(_T("Brand cannot be empty"));
        return;
    }

    if (cstr_PurchaseDate.IsEmpty())
    {
        AfxMessageBox(_T("Purchase cannot be empty"));
        return;
    }

    if (cstr_WarrantyMonth.IsEmpty())
    {
        AfxMessageBox(_T("Warranty cannot be empty"));
        return;
    }

    std::cout << "Added \n";
	CDialogEx::OnOK();
}
