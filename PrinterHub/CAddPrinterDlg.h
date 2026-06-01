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
	enum { IDD = IDD_DIALOG_ADD_PRINTER };
#endif

public:
	CString cstr_Id;
	CString cstr_Model;
	CString cstr_Brand;
	CString cstr_Status;
	CString cstr_PurchaseDate;
	CString cstr_WarrantyMonth;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cboBrand;
	CEdit m_editId;
	CEdit m_editModel;
	CDateTimeCtrl m_dtpPurchaseDate;
	CEdit m_editWarrantyMonth;
	CComboBox m_cboStatus;
	afx_msg void OnBnClickedButtonAddContinue();
};
