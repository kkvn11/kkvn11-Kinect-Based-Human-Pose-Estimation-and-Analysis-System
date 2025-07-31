
// myBoneDlg.cpp : ʵ���ļ�
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
#include <opencv2/opencv.hpp>	//opencvͷ�ļ�
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp> 

using namespace cv;
using namespace std;			//�����ռ�
CBodyBasics  myKinect;
CmyBoneDlg * CmyBoneDlg::s_pDlg = nullptr;

extern double angle[8];

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmyBoneDlg �Ի���



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
	DDX_Control(pDX, IDC_Bone, �Ƕ�);
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
	ON_WM_TIMER()                     //��ʱ���¼�
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


// CmyBoneDlg ��Ϣ�������

BOOL CmyBoneDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	choose.InsertString(0, _T("���"));
	choose.InsertString(1, _T("W����"));
	choose.InsertString(2, _T("Y����"));
	choose.InsertString(3, _T("��������Ӳ��"));
	choose.InsertString(4, _T("���Ժ��"));

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	s_pDlg = this;        //����Ҫ��һ�仰 �� �Ի����ָ�� �� ������Kinect �ཻ��
	// TODO:  �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CmyBoneDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CmyBoneDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CmyBoneDlg::OnBnClickedOpenkinect()
{
	HRESULT hr = myKinect.InitKinect();		//��ʼ��Ĭ��Kinect
	//m_edit.SetWindowText(TEXT("this is a test"));
	/*m_el = angle[0];
	UpdateData(FALSE);*/

	if (SUCCEEDED(hr))
	{
		myKinect.Update();								//ˢ�¹������������	
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
	SetTimer(35, 200, NULL);				//��ʱ��
}
void CmyBoneDlg::OnTimer(UINT_PTR nIDEvent)     //��ʱ������
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnOK();
}


void CmyBoneDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}





void CmyBoneDlg::OnEnChangeEdit2()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CmyBoneDlg::OnEnChangeEdit3()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CmyBoneDlg::OnEnChangeEdit4()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CmyBoneDlg::OnEnChangeEdit5()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CmyBoneDlg::OnEnChangeEdit6()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CmyBoneDlg::OnEnChangeEdit7()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CmyBoneDlg::OnEnChangeEdit8()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CmyBoneDlg::OnCbnSelchangeCombo1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//choose.InsertString(0, _T("���"));
	//choose.InsertString(1, _T("W����"));
	//choose.InsertString(2, _T("Y����"));
	//choose.InsertString(3, _T("��������Ӳ��"));
	//choose.InsertString(4, _T("���Ժ��"));
}




void CmyBoneDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	string a[8];              //���� string ���ͣ���100�е��ı�����Ҫ������ 
	int i = 0;
	ifstream infile;

	infile.open("f:\\whr.txt", ios::in);

	while (!infile.eof())            // ��δ���ļ�����һֱѭ�� 
	{
		getline(infile, a[i], '\n');//��ȡһ�У��Ի��з����������� a[] ��
		i++;                    //��һ��
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
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CmyBoneDlg::OnEnChangeEdit10()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CmyBoneDlg::OnEnChangeEdit11()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CmyBoneDlg::OnEnChangeEdit12()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CmyBoneDlg::OnEnChangeEdit13()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CmyBoneDlg::OnEnChangeEdit14()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CmyBoneDlg::OnEnChangeEdit15()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CmyBoneDlg::OnEnChangeEdit16()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CmyBoneDlg::OnBnClickedButton4()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	
	CString itemstr;
	choose.GetWindowText(itemstr);

	if (!itemstr.Compare(_T("���")))
	{
		string a[8];              //���� string ���ͣ���100�е��ı�����Ҫ������ 
		int i = 0;
		ifstream infile;
		
		infile.open("f:\\shdun.txt", ios::in);

		while (!infile.eof())            // ��δ���ļ�����һֱѭ�� 
		{
			getline(infile, a[i], '\n');//��ȡһ�У��Ի��з����������� a[] ��
			i++;                    //��һ��
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

		string b[8];              //���� string ���ͣ���100�е��ı�����Ҫ������ 
		 i = 0;
		ifstream infile2;

		infile2.open("f:\\shdunbh.txt", ios::in);

		while (!infile2.eof())            // ��δ���ļ�����һֱѭ�� 
		{
			getline(infile2, b[i], '\n');//��ȡһ�У��Ի��з����������� a[] ��
			i++;                    //��һ��
		}
		infile2.close();
		s = b[5];
		double m= atof(s.c_str());
		m = m - j_6;
		if (m > 10)
		{
			showw.SetWindowText(TEXT("�Ȳ��˶����Ȳ�������������ֱ�����������¶�һ��"));
		}
		else
			showw.SetWindowText(TEXT("������ɵĺܺ�"));
	}
	else if (!itemstr.Compare(_T("W����")))
	{
		string a[8];              //���� string ���ͣ���100�е��ı�����Ҫ������ 
		int i = 0;
		ifstream infile;

		infile.open("f:\\W.txt", ios::in);

		while (!infile.eof())            // ��δ���ļ�����һֱѭ�� 
		{
			getline(infile, a[i], '\n');//��ȡһ�У��Ի��з����������� a[] ��
			i++;                    //��һ��
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

		string b[8];              //���� string ���ͣ���100�е��ı�����Ҫ������ 
		i = 0;
		ifstream infile2;

		infile2.open("f:\\Wbh.txt", ios::in);

		while (!infile2.eof())            // ��δ���ļ�����һֱѭ�� 
		{
			getline(infile2, b[i], '\n');//��ȡһ�У��Ի��з����������� a[] ��
			i++;                    //��һ��
		}
		infile2.close();
		s = b[1];
		double m = atof(s.c_str());
		m = m - j_2;
		if (m > 10)
		{
			showw.SetWindowText(TEXT("��֫����û�е�λ��������н��������⣬������ؽ�ʹ����������£"));
		}
		else
			showw.SetWindowText(TEXT("������ɵĺܺ�"));

	}
	else if (!itemstr.Compare(_T("��������Ӳ��")))
	{
		string a[8];              //���� string ���ͣ���100�е��ı�����Ҫ������ 
		int i = 0;
		ifstream infile;

		infile.open("f:\\yaling.txt", ios::in);

		while (!infile.eof())            // ��δ���ļ�����һֱѭ�� 
		{
			getline(infile, a[i], '\n');//��ȡһ�У��Ի��з����������� a[] ��
			i++;                    //��һ��
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

		string b[8];              //���� string ���ͣ���100�е��ı�����Ҫ������ 
		i = 0;
		ifstream infile2;

		infile2.open("f:\\yalingbh.txt", ios::in);

		while (!infile2.eof())            // ��δ���ļ�����һֱѭ�� 
		{
			getline(infile2, b[i], '\n');//��ȡһ�У��Ի��з����������� a[] ��
			i++;                    //��һ��
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
			showw.SetWindowText(TEXT("�Ȳ��˶����Ȳ�������������ֱ�����������¶�һ��"));
		}
		else if(abs(t-u)>5)
			showw.SetWindowText(TEXT("������ɵĺܺ�,�������ȷ�������"));
	}
}


void CmyBoneDlg::OnEnChangeEdit17()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CmyBoneDlg::OnEnChangeEdit18()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CmyBoneDlg::OnEnChangeEdit19()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CmyBoneDlg::OnEnChangeEdit20()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CmyBoneDlg::OnEnChangeEdit21()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CmyBoneDlg::OnEnChangeEdit22()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CmyBoneDlg::OnEnChangeEdit23()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CmyBoneDlg::OnEnChangeEdit24()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}


void CmyBoneDlg::OnEnChangeEdit25()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
