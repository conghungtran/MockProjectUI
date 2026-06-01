// CAddPrinterDlg.cpp : implementation file
//

#include "pch.h"
#include "PrinterHub.h"
#include "afxdialogex.h"
#include "CAddPrinterDlg.h"


// CAddPrinterDlg dialog

IMPLEMENT_DYNAMIC(CAddPrinterDlg, CDialogEx)

CAddPrinterDlg::CAddPrinterDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
{

}

// MyDialog.cpp
BOOL CAddPrinterDlg::OnInitDialog()
{
    CDialog::OnInitDialog();

    // Load cities
    m_cboBrand.AddString(_T("DELL"));
    m_cboBrand.AddString(_T("LG"));
    m_cboBrand.AddString(_T("SAMSUNG"));
    m_cboBrand.AddString(_T("TOSHIBA"));
    m_cboBrand.SetCurSel(0);

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
	DDX_Control(pDX, IDC_COMBO1, m_cboBrand);
}


BEGIN_MESSAGE_MAP(CAddPrinterDlg, CDialogEx)
END_MESSAGE_MAP()


// CAddPrinterDlg message handlers
