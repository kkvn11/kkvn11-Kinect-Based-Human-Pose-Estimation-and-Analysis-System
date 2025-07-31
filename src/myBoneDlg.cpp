
// myBoneDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "myBone.h"
#include "myBoneDlg.h"
#include "afxdialogex.h"
#include "myKinect.h"
#include "cv.h"
#include<iostream>
#include<fstream>
#include <string>
#include <math.h>
#include <cstdlib>
#include <opencv2/opencv.hpp>	//opencv头文件
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp> 

using namespace cv;
using namespace std;			//命名空间
CBodyBasics  myKinect;
CmyBoneDlg * CmyBoneDlg::s_pDlg = nullptr;

extern double angle[8];

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmyBoneDlg 对话框



CmyBoneDlg::CmyBoneDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CmyBoneDlg::IDD, pParent)
	, m_el(0)
	, m4_el(0)
	, m7_el(0)
	, m8_el(0)
	, m1_el(0)
	, m2_el(0)
	, m5_el(0)
	, m6_el(0)
	, long_1(0)
	, long_2(0)
	, long_3(0)
	, long_4(0)
	, long_5(0)
	, long_6(0)
	, long_7(0)
	, long_8(0)
	, j_1(0)
	, j_2(0)
	, j_3(0)
	, j_4(0)
	, j_5(0)
	, j_6(0)
	, j_7(0)
	, j_8(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmyBoneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_edit);
	DDX_Text(pDX, IDC_EDIT1, m_el);
	DDX_Control(pDX, IDC_Bone, 角度);
	DDX_Text(pDX, IDC_EDIT2, m4_el);
	DDX_Text(pDX, IDC_EDIT3, m7_el);
	DDX_Text(pDX, IDC_EDIT4, m8_el);
	DDX_Text(pDX, IDC_EDIT5, m1_el);
	DDX_Text(pDX, IDC_EDIT6, m2_el);
	DDX_Text(pDX, IDC_EDIT7, m5_el);
	DDX_Text(pDX, IDC_EDIT8, m6_el);
	DDX_Control(pDX, IDC_COMBO1, choose);

	DDX_Control(pDX, IDC_EDIT9, long_f);
	DDX_Text(pDX, IDC_EDIT9, long_1);
	DDX_Text(pDX, IDC_EDIT10, long_2);
	DDX_Text(pDX, IDC_EDIT11, long_3);
	DDX_Text(pDX, IDC_EDIT12, long_4);
	DDX_Text(pDX, IDC_EDIT13, long_5);
	DDX_Text(pDX, IDC_EDIT14, long_6);
	DDX_Text(pDX, IDC_EDIT15, long_7);
	DDX_Text(pDX, IDC_EDIT16, long_8);
	DDX_Text(pDX, IDC_EDIT17, j_1);
	DDX_Text(pDX, IDC_EDIT18, j_2);
	DDX_Text(pDX, IDC_EDIT19, j_3);
	DDX_Text(pDX, IDC_EDIT20, j_4);
	DDX_Text(pDX, IDC_EDIT21, j_5);
	DDX_Text(pDX, IDC_EDIT22, j_6);
	DDX_Text(pDX, IDC_EDIT23, j_7);
	DDX_Text(pDX, IDC_EDIT24, j_8);
	DDX_Control(pDX, IDC_EDIT25, showw);
}

BEGIN_MESSAGE_MAP(CmyBoneDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()                     //定时器事件
	ON_BN_CLICKED(IDC_OPENKINECT, &CmyBoneDlg::OnBnClickedOpenkinect)
	ON_BN_CLICKED(IDOK, &CmyBoneDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT1, &CmyBoneDlg::OnEnChangeEdit1)
	
	ON_EN_CHANGE(IDC_EDIT2, &CmyBoneDlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CmyBoneDlg::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &CmyBoneDlg::OnEnChangeEdit4)
	ON_EN_CHANGE(IDC_EDIT5, &CmyBoneDlg::OnEnChangeEdit5)
	ON_EN_CHANGE(IDC_EDIT6, &CmyBoneDlg::OnEnChangeEdit6)
	ON_EN_CHANGE(IDC_EDIT7, &CmyBoneDlg::OnEnChangeEdit7)
	ON_EN_CHANGE(IDC_EDIT8, &CmyBoneDlg::OnEnChangeEdit8)
	ON_CBN_SELCHANGE(IDC_COMBO1, &CmyBoneDlg::OnCbnSelchangeCombo1)

	ON_BN_CLICKED(IDC_BUTTON3, &CmyBoneDlg::OnBnClickedButton3)
	ON_EN_CHANGE(IDC_EDIT9, &CmyBoneDlg::OnEnChangeEdit9)
	ON_EN_CHANGE(IDC_EDIT10, &CmyBoneDlg::OnEnChangeEdit10)
	ON_EN_CHANGE(IDC_EDIT11, &CmyBoneDlg::OnEnChangeEdit11)
	ON_EN_CHANGE(IDC_EDIT12, &CmyBoneDlg::OnEnChangeEdit12)
	ON_EN_CHANGE(IDC_EDIT13, &CmyBoneDlg::OnEnChangeEdit13)
	ON_EN_CHANGE(IDC_EDIT14, &CmyBoneDlg::OnEnChangeEdit14)
	ON_EN_CHANGE(IDC_EDIT15, &CmyBoneDlg::OnEnChangeEdit15)
	ON_EN_CHANGE(IDC_EDIT16, &CmyBoneDlg::OnEnChangeEdit16)
	ON_BN_CLICKED(IDC_BUTTON4, &CmyBoneDlg::OnBnClickedButton4)
	ON_EN_CHANGE(IDC_EDIT17, &CmyBoneDlg::OnEnChangeEdit17)
	ON_EN_CHANGE(IDC_EDIT18, &CmyBoneDlg::OnEnChangeEdit18)
	ON_EN_CHANGE(IDC_EDIT19, &CmyBoneDlg::OnEnChangeEdit19)
	ON_EN_CHANGE(IDC_EDIT20, &CmyBoneDlg::OnEnChangeEdit20)
	ON_EN_CHANGE(IDC_EDIT21, &CmyBoneDlg::OnEnChangeEdit21)
	ON_EN_CHANGE(IDC_EDIT22, &CmyBoneDlg::OnEnChangeEdit22)
	ON_EN_CHANGE(IDC_EDIT23, &CmyBoneDlg::OnEnChangeEdit23)
	ON_EN_CHANGE(IDC_EDIT24, &CmyBoneDlg::OnEnChangeEdit24)
	ON_EN_CHANGE(IDC_EDIT25, &CmyBoneDlg::OnEnChangeEdit25)
END_MESSAGE_MAP()


// CmyBoneDlg 消息处理程序

BOOL CmyBoneDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	choose.InsertString(0, _T("深蹲"));
	choose.InsertString(1, _T("W背部"));
	choose.InsertString(2, _T("Y背部"));
	choose.InsertString(3, _T("哑铃曲腿硬拉"));
	choose.InsertString(4, _T("仰卧后撑"));

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	s_pDlg = this;        //很重要的一句话 ， 对话框的指针 ， 用于与Kinect 类交互
	// TODO:  在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CmyBoneDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CmyBoneDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CmyBoneDlg::OnBnClickedOpenkinect()
{
	HRESULT hr = myKinect.InitKinect();		//初始化默认Kinect
	//m_edit.SetWindowText(TEXT("this is a test"));
	/*m_el = angle[0];
	UpdateData(FALSE);*/

	if (SUCCEEDED(hr))
	{
		myKinect.Update();								//刷新骨骼和深度数据	
		m_el = angle[2];
		m4_el = angle[3];
		m7_el = angle[6];
		m8_el = angle[7];
		m1_el = angle[0];
		m2_el = angle[1];
		m5_el = angle[4];
		m6_el = angle[5];
		UpdateData(FALSE);
	}
	SetTimer(35, 200, NULL);				//定时器
}
void CmyBoneDlg::OnTimer(UINT_PTR nIDEvent)     //定时器处理
{
	switch (nIDEvent)
	{
	case 35:
		myKinect.Update();
		m_el = angle[2];
		m4_el = angle[3];
		m7_el = angle[6];
		m8_el = angle[7];
		m1_el = angle[0];
		m2_el = angle[1];
		m5_el = angle[4];
		m6_el = angle[5];
		UpdateData(FALSE);
	default:
		break;
	}
	CDialog::OnTimer(nIDEvent);
}



void CmyBoneDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}


void CmyBoneDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}





void CmyBoneDlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CmyBoneDlg::OnEnChangeEdit3()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CmyBoneDlg::OnEnChangeEdit4()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CmyBoneDlg::OnEnChangeEdit5()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CmyBoneDlg::OnEnChangeEdit6()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CmyBoneDlg::OnEnChangeEdit7()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CmyBoneDlg::OnEnChangeEdit8()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CmyBoneDlg::OnCbnSelchangeCombo1()
{
	// TODO: 在此添加控件通知处理程序代码
	//choose.InsertString(0, _T("深蹲"));
	//choose.InsertString(1, _T("W背部"));
	//choose.InsertString(2, _T("Y背部"));
	//choose.InsertString(3, _T("哑铃曲腿硬拉"));
	//choose.InsertString(4, _T("仰卧后撑"));
}




void CmyBoneDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	string a[8];              //采用 string 类型，存100行的文本，不要用数组 
	int i = 0;
	ifstream infile;

	infile.open("f:\\whr.txt", ios::in);

	while (!infile.eof())            // 若未到文件结束一直循环 
	{
		getline(infile, a[i], '\n');//读取一行，以换行符结束，存入 a[] 中
		i++;                    //下一行
	}
	
	infile.close();
	string s = a[0];
	double n = atof(s.c_str());
	long_1 = n;

	 s = a[1];
	 n = atof(s.c_str());
	long_2 = n;

	 s = a[2];
	 n = atof(s.c_str());
	long_3 = n;

	 s = a[3];
	 n = atof(s.c_str());
	long_4 = n;

	s = a[4];
	n = atof(s.c_str());
	long_5 = n;

	s = a[5];
	n = atof(s.c_str());
	long_6 = n;

	s = a[6];
	n = atof(s.c_str());
	long_7 = n;

	s = a[7];
	n = atof(s.c_str());
	long_8 = n;
}


void CmyBoneDlg::OnEnChangeEdit9()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CmyBoneDlg::OnEnChangeEdit10()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CmyBoneDlg::OnEnChangeEdit11()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CmyBoneDlg::OnEnChangeEdit12()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CmyBoneDlg::OnEnChangeEdit13()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CmyBoneDlg::OnEnChangeEdit14()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CmyBoneDlg::OnEnChangeEdit15()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CmyBoneDlg::OnEnChangeEdit16()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CmyBoneDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码

	
	CString itemstr;
	choose.GetWindowText(itemstr);

	if (!itemstr.Compare(_T("深蹲")))
	{
		string a[8];              //采用 string 类型，存100行的文本，不要用数组 
		int i = 0;
		ifstream infile;
		
		infile.open("f:\\shdun.txt", ios::in);

		while (!infile.eof())            // 若未到文件结束一直循环 
		{
			getline(infile, a[i], '\n');//读取一行，以换行符结束，存入 a[] 中
			i++;                    //下一行
		}

		infile.close();
		string s = a[0];
		double n = atof(s.c_str());
		j_1 = n;

		s = a[1];
		n = atof(s.c_str());
		j_2 = n;

		s = a[2];
		n = atof(s.c_str());
		j_3 = n;

		s = a[3];
		n = atof(s.c_str());
		j_4 = n;

		s = a[4];
		n = atof(s.c_str());
		j_5 = n;

		s = a[5];
		n = atof(s.c_str());
		j_6 = n;

		s = a[6];
		n = atof(s.c_str());
		j_7 = n;

		s = a[7];
		n = atof(s.c_str());
		j_8 = n;

		string b[8];              //采用 string 类型，存100行的文本，不要用数组 
		 i = 0;
		ifstream infile2;

		infile2.open("f:\\shdunbh.txt", ios::in);

		while (!infile2.eof())            // 若未到文件结束一直循环 
		{
			getline(infile2, b[i], '\n');//读取一行，以换行符结束，存入 a[] 中
			i++;                    //下一行
		}
		infile2.close();
		s = b[5];
		double m= atof(s.c_str());
		m = m - j_6;
		if (m > 10)
		{
			showw.SetWindowText(TEXT("腿部运动幅度不够，保持上身直立，请再往下蹲一点"));
		}
		else
			showw.SetWindowText(TEXT("动作完成的很好"));
	}
	else if (!itemstr.Compare(_T("W背部")))
	{
		string a[8];              //采用 string 类型，存100行的文本，不要用数组 
		int i = 0;
		ifstream infile;

		infile.open("f:\\W.txt", ios::in);

		while (!infile.eof())            // 若未到文件结束一直循环 
		{
			getline(infile, a[i], '\n');//读取一行，以换行符结束，存入 a[] 中
			i++;                    //下一行
		}

		infile.close();
		string s = a[0];
		double n = atof(s.c_str());
		j_1 = n;

		s = a[1];
		n = atof(s.c_str());
		j_2 = n;

		s = a[2];
		n = atof(s.c_str());
		j_3 = n;

		s = a[3];
		n = atof(s.c_str());
		j_4 = n;

		s = a[4];
		n = atof(s.c_str());
		j_5 = n;

		s = a[5];
		n = atof(s.c_str());
		j_6 = n;

		s = a[6];
		n = atof(s.c_str());
		j_7 = n;

		s = a[7];
		n = atof(s.c_str());
		j_8 = n;

		string b[8];              //采用 string 类型，存100行的文本，不要用数组 
		i = 0;
		ifstream infile2;

		infile2.open("f:\\Wbh.txt", ios::in);

		while (!infile2.eof())            // 若未到文件结束一直循环 
		{
			getline(infile2, b[i], '\n');//读取一行，以换行符结束，存入 a[] 中
			i++;                    //下一行
		}
		infile2.close();
		s = b[1];
		double m = atof(s.c_str());
		m = m - j_2;
		if (m > 10)
		{
			showw.SetWindowText(TEXT("上肢动作没有到位，请继续夹紧背部肌肉，想象肘关节使劲往背部靠拢"));
		}
		else
			showw.SetWindowText(TEXT("动作完成的很好"));

	}
	else if (!itemstr.Compare(_T("哑铃曲腿硬拉")))
	{
		string a[8];              //采用 string 类型，存100行的文本，不要用数组 
		int i = 0;
		ifstream infile;

		infile.open("f:\\yaling.txt", ios::in);

		while (!infile.eof())            // 若未到文件结束一直循环 
		{
			getline(infile, a[i], '\n');//读取一行，以换行符结束，存入 a[] 中
			i++;                    //下一行
		}

		infile.close();
		string s = a[0];
		double n = atof(s.c_str());
		j_1 = n;

		s = a[1];
		n = atof(s.c_str());
		j_2 = n;

		s = a[2];
		n = atof(s.c_str());
		j_3 = n;

		s = a[3];
		n = atof(s.c_str());
		j_4 = n;

		s = a[4];
		n = atof(s.c_str());
		j_5 = n;

		s = a[5];
		n = atof(s.c_str());
		j_6 = n;

		s = a[6];
		n = atof(s.c_str());
		j_7 = n;

		s = a[7];
		n = atof(s.c_str());
		j_8 = n;

		string b[8];              //采用 string 类型，存100行的文本，不要用数组 
		i = 0;
		ifstream infile2;

		infile2.open("f:\\yalingbh.txt", ios::in);

		while (!infile2.eof())            // 若未到文件结束一直循环 
		{
			getline(infile2, b[i], '\n');//读取一行，以换行符结束，存入 a[] 中
			i++;                    //下一行
		}
		infile2.close();
		s = b[4];
		string w, e;
		w = b[5];
		e = b[7];
		double m = atof(s.c_str());
		double t, u;
		t= atof(w.c_str());
		u= atof(e.c_str());
		m = m - j_5;
		if (m > 10)
		{
			showw.SetWindowText(TEXT("腿部运动幅度不够，保持上身直立，请再往下蹲一点"));
		}
		else if(abs(t-u)>5)
			showw.SetWindowText(TEXT("动作完成的很好,但左右腿发力不均"));
	}
}


void CmyBoneDlg::OnEnChangeEdit17()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CmyBoneDlg::OnEnChangeEdit18()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CmyBoneDlg::OnEnChangeEdit19()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CmyBoneDlg::OnEnChangeEdit20()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CmyBoneDlg::OnEnChangeEdit21()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CmyBoneDlg::OnEnChangeEdit22()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CmyBoneDlg::OnEnChangeEdit23()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CmyBoneDlg::OnEnChangeEdit24()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CmyBoneDlg::OnEnChangeEdit25()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}
