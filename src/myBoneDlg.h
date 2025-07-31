

#pragma once
#include "myKinect.h"
#include "afxwin.h"
#include<time.h>



// CmyBoneDlg 对话框
class CmyBoneDlg : public CDialogEx
{
// 构造
public:
	CmyBoneDlg(CWnd* pParent = NULL);	// 标准构造函数
	static CmyBoneDlg  *s_pDlg;        //对象指针
// 对话框数据
	enum { IDD = IDD_MYBONE_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP();
public:
	afx_msg void OnBnClickedOpenkinect();
	afx_msg void OnBnClickedOk();
	afx_msg void  OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnEnChangeEdit1();
	CEdit m_edit;
	double m_el;
	CStatic 角度;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnEnChangeEdit2();
	double m4_el;
	afx_msg void OnEnChangeEdit3();
	double m7_el;
	afx_msg void OnEnChangeEdit4();
	double m8_el;
	afx_msg void OnEnChangeEdit5();
	double m1_el;
	afx_msg void OnEnChangeEdit6();
	double m2_el;
	afx_msg void OnEnChangeEdit7();
	double m5_el;
	afx_msg void OnEnChangeEdit8();
	double m6_el;
	afx_msg void OnCbnSelchangeCombo1();
	CComboBox choose;
	afx_msg void OnCbnSelchangeCombo3();
	CComboBox choose3;
	afx_msg void OnBnClickedButton3();
	afx_msg void OnEnChangeEdit9();
	CEdit long_f;
	double long_1;
	afx_msg void OnEnChangeEdit10();
	double long_2;
	afx_msg void OnEnChangeEdit11();
	double long_3;
	afx_msg void OnEnChangeEdit12();
	double long_4;
	afx_msg void OnEnChangeEdit13();
	double long_5;
	afx_msg void OnEnChangeEdit14();
	double long_6;
	afx_msg void OnEnChangeEdit15();
	double long_7;
	afx_msg void OnEnChangeEdit16();
	double long_8;
	afx_msg void OnBnClickedButton4();
	afx_msg void OnEnChangeEdit17();
	double j_1;
	afx_msg void OnEnChangeEdit18();
	double j_2;
	afx_msg void OnEnChangeEdit19();
	double j_3;
	afx_msg void OnEnChangeEdit20();
	double j_4;
	afx_msg void OnEnChangeEdit21();
	double j_5;
	afx_msg void OnEnChangeEdit22();
	double j_6;
	afx_msg void OnEnChangeEdit23();
	double j_7;
	afx_msg void OnEnChangeEdit24();
	double j_8;
	afx_msg void OnEnChangeEdit25();
	CEdit showw;
};
