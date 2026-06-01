#pragma once
#include "afxdialogex.h"


// CAddPrinterDlg dialog

class CAddPrinterDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddPrinterDlg)

public:
	CAddPrinterDlg(CWnd* pParent = nullptr);   // standard constructor
	virtual ~CAddPrinterDlg();
	BOOL OnInitDialog();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG1 };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cboBrand;
};
