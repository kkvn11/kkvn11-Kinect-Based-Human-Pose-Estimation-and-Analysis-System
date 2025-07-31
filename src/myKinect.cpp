#include "stdafx.h"
#include"myBone.h"
#include"myBoneDlg.h"
#include<cmath>
#include<math.h>
#include<iostream>
#include<fstream>

//#include"stdio.h"
#include "myKinect.h"

using namespace std;
//using namespace cv;
double angle[8];

CBodyBasics::CBodyBasics() //构造函数
{
	
	IKinectSensor*  m_pKinectSensor = NULL;
	IColorFrameReader*  m_pColorFrameReader = NULL;

	m_pColorRGBX = new RGBQUAD[cColorWidth * cColorHeight];// create heap storage for color pixel data in RGBX format

//-----------------初始化骨骼------//
	myBodySource = nullptr; 
	myBodyReader = nullptr;
	myBodyCount = 0;  
	myBodyFrame = nullptr; 
	myMapper = nullptr;  

}
CBodyBasics::~CBodyBasics()

{
	if (m_pColorRGBX)
	{
		delete[] m_pColorRGBX;
		m_pColorRGBX = NULL;
	}

	SafeRelease(m_pColorFrameReader);// done with color frame reader

	if (m_pKinectSensor)
	{
		m_pKinectSensor->Close();// close the Kinect Sensor
	}
	SafeRelease(m_pKinectSensor);
}
HRESULT	CBodyBasics::InitKinect()
{
	HRESULT hr;

	hr = GetDefaultKinectSensor(&m_pKinectSensor);
	if (FAILED(hr))
	{
		return hr;
	}

	if (m_pKinectSensor)
	{
		// Initialize the Kinect and get the color reader
		IColorFrameSource* pColorFrameSource = NULL;

		hr = m_pKinectSensor->Open();//open kinect

		if (SUCCEEDED(hr))
		{
			hr = m_pKinectSensor->get_ColorFrameSource(&pColorFrameSource);
			//方法get_ColorFrameSource打开彩色帧的源
		}

		if (SUCCEEDED(hr))
		{
			hr = pColorFrameSource->OpenReader(&m_pColorFrameReader);
			//方法openreader打开彩色帧读取器
		}

		SafeRelease(pColorFrameSource);
	}

	//--------------------------//
	if (m_pKinectSensor)
	{
		m_pKinectSensor->get_BodyFrameSource(&myBodySource);
		myBodySource->OpenReader(&myBodyReader);
	
		m_pKinectSensor->get_CoordinateMapper(&myMapper);
	}
	//--------------------------//


	if (!m_pKinectSensor || FAILED(hr))
	{
		printf("No ready Kinect found! \n");
		return E_FAIL;
	}

	return hr;
}
void CBodyBasics::Update()
{
	double x1, y1, z1, x2, y2, z2, a, b, c;
	
	if (!m_pColorFrameReader)
	{
		return;
	}
//--------------------------//
	Mat  original(cColorHeight, cColorWidth, CV_8UC4);
	
//--------------------------//


	IColorFrame* pColorFrame = NULL;

	HRESULT hr = m_pColorFrameReader->AcquireLatestFrame(&pColorFrame);
	//更新彩色帧

	if (SUCCEEDED(hr))
	{
		IFrameDescription* pFrameDescription = NULL;
		int nWidth = 0;
		int nHeight = 0;
		ColorImageFormat imageFormat = ColorImageFormat_None;
		UINT nBufferSize = 0;
		RGBQUAD *pBuffer = NULL;

		if (SUCCEEDED(hr))
		{
			hr = pColorFrame->get_FrameDescription(&pFrameDescription);
			//一共六种数据源,彩色图像
		}

		if (SUCCEEDED(hr))
		{
			hr = pFrameDescription->get_Width(&nWidth);
		}

		if (SUCCEEDED(hr))
		{
			hr = pFrameDescription->get_Height(&nHeight);
		}

		if (SUCCEEDED(hr))
		{
			hr = pColorFrame->get_RawColorImageFormat(&imageFormat);
		}

		if (SUCCEEDED(hr))
		{
			if (imageFormat == ColorImageFormat_Bgra)
			{
				hr = pColorFrame->AccessRawUnderlyingBuffer(&nBufferSize, reinterpret_cast<BYTE**>(&pBuffer));
			}
			else if (m_pColorRGBX)
			{
				pBuffer = m_pColorRGBX;
				nBufferSize = cColorWidth * cColorHeight * sizeof(RGBQUAD);
				hr = pColorFrame->CopyConvertedFrameDataToArray(nBufferSize, reinterpret_cast<BYTE*>(pBuffer), ColorImageFormat_Bgra);

				pColorFrame->CopyConvertedFrameDataToArray(nBufferSize, original.data , ColorImageFormat_Bgra);
				copy = original.clone();
			}
			else
			{
				hr = E_FAIL;
			}
		}

		if (SUCCEEDED(hr))
		{
		ProcessColor(pBuffer, nWidth, nHeight);
		}

		SafeRelease(pFrameDescription);
	}

SafeRelease(pColorFrame);


	//---------------------------------//
//  while (myBodyReader->AcquireLatestFrame(&myBodyFrame) != S_OK); //读取身体图像
	 hr = myBodyReader->AcquireLatestFrame(&myBodyFrame); //读取身体图像
	if SUCCEEDED(hr)
	{
		myBodySource->get_BodyCount(&myBodyCount); 

		IBody   **  myBodyArr = new IBody *[myBodyCount];       //为存身体数据的数组做准备
		for (int i = 0; i < myBodyCount; i++)
			myBodyArr[i] = nullptr;
	
		if (myBodyFrame->GetAndRefreshBodyData(myBodyCount, myBodyArr) == S_OK)     //把身体数据输入数组
			for (int i = 0; i < myBodyCount; i++)
			{
			BOOLEAN     result = false;
			if (myBodyArr[i]->get_IsTracked(&result) == S_OK && result) //先判断是否侦测到
			{
				Joint   myJointArr[JointType_Count];
				if (myBodyArr[i]->GetJoints(JointType_Count, myJointArr) == S_OK)   //如果侦测到就把关节数据输入到数组并画图
				{
					draw(copy, myJointArr[JointType_Head], myJointArr[JointType_Neck], myMapper);
					draw(copy, myJointArr[JointType_Neck], myJointArr[JointType_SpineShoulder], myMapper);

					draw(copy, myJointArr[JointType_SpineShoulder], myJointArr[JointType_ShoulderLeft], myMapper);
					draw(copy, myJointArr[JointType_SpineShoulder], myJointArr[JointType_SpineMid], myMapper);
					draw(copy, myJointArr[JointType_SpineShoulder], myJointArr[JointType_ShoulderRight], myMapper);

					draw(copy, myJointArr[JointType_ShoulderLeft], myJointArr[JointType_ElbowLeft], myMapper);
					draw(copy, myJointArr[JointType_SpineMid], myJointArr[JointType_SpineBase], myMapper);
					draw(copy, myJointArr[JointType_ShoulderRight], myJointArr[JointType_ElbowRight], myMapper);

					draw(copy, myJointArr[JointType_ElbowLeft], myJointArr[JointType_WristLeft], myMapper);
					draw(copy, myJointArr[JointType_SpineBase], myJointArr[JointType_HipLeft], myMapper);
					draw(copy, myJointArr[JointType_SpineBase], myJointArr[JointType_HipRight], myMapper);
					draw(copy, myJointArr[JointType_ElbowRight], myJointArr[JointType_WristRight], myMapper);

					draw(copy, myJointArr[JointType_WristLeft], myJointArr[JointType_ThumbLeft], myMapper);
					draw(copy, myJointArr[JointType_WristLeft], myJointArr[JointType_HandLeft], myMapper);
					draw(copy, myJointArr[JointType_HipLeft], myJointArr[JointType_KneeLeft], myMapper);
					draw(copy, myJointArr[JointType_HipRight], myJointArr[JointType_KneeRight], myMapper);
					draw(copy, myJointArr[JointType_WristRight], myJointArr[JointType_ThumbRight], myMapper);
					draw(copy, myJointArr[JointType_WristRight], myJointArr[JointType_HandRight], myMapper);

					draw(copy, myJointArr[JointType_HandLeft], myJointArr[JointType_HandTipLeft], myMapper);
					draw(copy, myJointArr[JointType_KneeLeft], myJointArr[JointType_FootLeft], myMapper);
					draw(copy, myJointArr[JointType_KneeRight], myJointArr[JointType_FootRight], myMapper);
					draw(copy, myJointArr[JointType_HandRight], myJointArr[JointType_HandTipRight], myMapper);
					
					x1 = myJointArr[JointType_ShoulderRight].Position.X - myJointArr[JointType_ElbowRight].Position.X;
					y1 = myJointArr[JointType_ShoulderRight].Position.Y - myJointArr[JointType_ElbowRight].Position.Y;
					z1 = myJointArr[JointType_ShoulderRight].Position.Z - myJointArr[JointType_ElbowRight].Position.Z;
					x2 = myJointArr[JointType_ShoulderRight].Position.X - myJointArr[JointType_SpineShoulder].Position.X;
					y2 = myJointArr[JointType_ShoulderRight].Position.Y - myJointArr[JointType_SpineShoulder].Position.Y;
					z2 = myJointArr[JointType_ShoulderRight].Position.Z - myJointArr[JointType_SpineShoulder].Position.Z;
					a = x1 * x2 + y1 * y2 + z1 * z2;
					b = sqrt(x1*x1 + y1 * y1 + z1 * z1)*sqrt(x2*x2 + y2 * y2 + z2 * z2);
					c = acos(a / b);
					angle[0] = c * 180 / 3.1415;

					x1 = myJointArr[JointType_ElbowRight].Position.X - myJointArr[JointType_ShoulderRight].Position.X;
					y1 = myJointArr[JointType_ElbowRight].Position.Y - myJointArr[JointType_ShoulderRight].Position.Y;
					z1 = myJointArr[JointType_ElbowRight].Position.Z - myJointArr[JointType_ShoulderRight].Position.Z;
					x2 = myJointArr[JointType_ElbowRight].Position.X - myJointArr[JointType_WristRight].Position.X;
					y2 = myJointArr[JointType_ElbowRight].Position.Y - myJointArr[JointType_WristRight].Position.Y;
					z2 = myJointArr[JointType_ElbowRight].Position.Z - myJointArr[JointType_WristRight].Position.Z;
					a = x1 * x2 + y1 * y2 + z1 * z2;
					b = sqrt(x1*x1 + y1 * y1 + z1 * z1)*sqrt(x2*x2 + y2 * y2 + z2 * z2);
					c = acos(a / b);
					angle[1] = c * 180 / 3.1415;

					x1 = myJointArr[JointType_ShoulderLeft].Position.X - myJointArr[JointType_SpineShoulder].Position.X;
					y1 = myJointArr[JointType_ShoulderLeft].Position.Y - myJointArr[JointType_SpineShoulder].Position.Y;
					z1 = myJointArr[JointType_ShoulderLeft].Position.Z - myJointArr[JointType_SpineShoulder].Position.Z;
					x2 = myJointArr[JointType_ShoulderLeft].Position.X - myJointArr[JointType_ElbowLeft].Position.X;
					y2 = myJointArr[JointType_ShoulderLeft].Position.Y - myJointArr[JointType_ElbowLeft].Position.Y;
					z2 = myJointArr[JointType_ShoulderLeft].Position.Z - myJointArr[JointType_ElbowLeft].Position.Z;
					a = x1 * x2 + y1 * y2 + z1 * z2;
					b = sqrt(x1*x1 + y1 * y1 + z1 * z1)*sqrt(x2*x2 + y2 * y2 + z2 * z2);
					c = acos(a / b);
					angle[2] = c * 180 / 3.1415;

					x1 = myJointArr[JointType_ElbowLeft].Position.X - myJointArr[JointType_ShoulderLeft].Position.X;
					y1 = myJointArr[JointType_ElbowLeft].Position.Y - myJointArr[JointType_ShoulderLeft].Position.Y;
					z1 = myJointArr[JointType_ElbowLeft].Position.Z - myJointArr[JointType_ShoulderLeft].Position.Z;
					x2 = myJointArr[JointType_ElbowLeft].Position.X - myJointArr[JointType_WristLeft].Position.X;
					y2 = myJointArr[JointType_ElbowLeft].Position.Y - myJointArr[JointType_WristLeft].Position.Y;
					z2 = myJointArr[JointType_ElbowLeft].Position.Z - myJointArr[JointType_WristLeft].Position.Z;
					a = x1 * x2 + y1 * y2 + z1 * z2;
					b = sqrt(x1*x1 + y1 * y1 + z1 * z1)*sqrt(x2*x2 + y2 * y2 + z2 * z2);
					c = acos(a / b);
					angle[3] = c * 180 / 3.1415;

					x1 = myJointArr[JointType_HipRight].Position.X - myJointArr[JointType_SpineBase].Position.X;
					y1 = myJointArr[JointType_HipRight].Position.Y - myJointArr[JointType_SpineBase].Position.Y;
					z1 = myJointArr[JointType_HipRight].Position.Z - myJointArr[JointType_SpineBase].Position.Z;
					x2 = myJointArr[JointType_HipRight].Position.X - myJointArr[JointType_KneeRight].Position.X;
					y2 = myJointArr[JointType_HipRight].Position.Y - myJointArr[JointType_KneeRight].Position.Y;
					z2 = myJointArr[JointType_HipRight].Position.Z - myJointArr[JointType_KneeRight].Position.Z;
					a = x1 * x2 + y1 * y2 + z1 * z2;
					b = sqrt(x1*x1 + y1 * y1 + z1 * z1)*sqrt(x2*x2 + y2 * y2 + z2 * z2);
					c = acos(a / b);
					angle[4] = c * 180 / 3.1415;

					x1 = myJointArr[JointType_KneeRight].Position.X - myJointArr[JointType_HipRight].Position.X;
					y1 = myJointArr[JointType_KneeRight].Position.Y - myJointArr[JointType_HipRight].Position.Y;
					z1 = myJointArr[JointType_KneeRight].Position.Z - myJointArr[JointType_HipRight].Position.Z;
					x2 = myJointArr[JointType_KneeRight].Position.X - myJointArr[JointType_FootRight].Position.X;
					y2 = myJointArr[JointType_KneeRight].Position.Y - myJointArr[JointType_FootRight].Position.Y;
					z2 = myJointArr[JointType_KneeRight].Position.Z - myJointArr[JointType_FootRight].Position.Z;
					a = x1 * x2 + y1 * y2 + z1 * z2;
					b = sqrt(x1*x1 + y1 * y1 + z1 * z1)*sqrt(x2*x2 + y2 * y2 + z2 * z2);
					c = acos(a / b);
					angle[5] = c * 180 / 3.1415;

					x1 = myJointArr[JointType_HipLeft].Position.X - myJointArr[JointType_SpineBase].Position.X;
					y1 = myJointArr[JointType_HipLeft].Position.Y - myJointArr[JointType_SpineBase].Position.Y;
					z1 = myJointArr[JointType_HipLeft].Position.Z - myJointArr[JointType_SpineBase].Position.Z;
					x2 = myJointArr[JointType_HipLeft].Position.X - myJointArr[JointType_KneeLeft].Position.X;
					y2 = myJointArr[JointType_HipLeft].Position.Y - myJointArr[JointType_KneeLeft].Position.Y;
					z2 = myJointArr[JointType_HipLeft].Position.Z - myJointArr[JointType_KneeLeft].Position.Z;
					a = x1 * x2 + y1 * y2 + z1 * z2;
					b = sqrt(x1*x1 + y1 * y1 + z1 * z1)*sqrt(x2*x2 + y2 * y2 + z2 * z2);
					c = acos(a / b);
					angle[6] = c * 180 / 3.1415;

					x1 = myJointArr[JointType_KneeLeft].Position.X - myJointArr[JointType_HipLeft].Position.X;
					y1 = myJointArr[JointType_KneeLeft].Position.Y - myJointArr[JointType_HipLeft].Position.Y;
					z1 = myJointArr[JointType_KneeLeft].Position.Z - myJointArr[JointType_HipLeft].Position.Z;
					x2 = myJointArr[JointType_KneeLeft].Position.X - myJointArr[JointType_FootLeft].Position.X;
					y2 = myJointArr[JointType_KneeLeft].Position.Y - myJointArr[JointType_FootLeft].Position.Y;
					z2 = myJointArr[JointType_KneeLeft].Position.Z - myJointArr[JointType_FootLeft].Position.Z;
					a = x1 * x2 + y1 * y2 + z1 * z2;
					b = sqrt(x1*x1 + y1 * y1 + z1 * z1)*sqrt(x2*x2 + y2 * y2 + z2 * z2);
					c = acos(a / b);
					angle[7] = c * 180 / 3.1415;


				}
			}
			}
		DrawMat(copy, IDC_Bone);
		//angle[0] = 2.2;
		delete[]myBodyArr; 
		SafeRelease(myBodyFrame);
		//myColorFrame->Release();
	
	
	}
}
void CBodyBasics::ProcessColor(RGBQUAD* pBuffer, int nWidth, int nHeight)
{
	// Make sure we've received valid data
	if (pBuffer && (nWidth == cColorWidth) && (nHeight == cColorHeight))

	{
		// Draw the data with OpenCV
		Mat ColorImage(nHeight, nWidth, CV_8UC4, pBuffer);
		Mat showImage;
		resize(ColorImage, showImage, Size(nWidth / 2, nHeight / 2));
		//cvtColor(showImage, showImage, CV_RGB2GRAY);
		//Canny(showImage, showImage, 3);
		//imshow("ColorImage", showImage);////imshow("ColorImage", ColorImage);
		DrawMat(ColorImage, IDC_Image);
	}
}
void    CBodyBasics::DrawMat(cv::Mat & img, UINT nID)
{
	cv::Mat imgTmp;
	CRect rect;
	CmyBoneDlg::s_pDlg->GetDlgItem(nID)->GetClientRect(&rect);  // 获取控件大小
	cv::resize(img, imgTmp, cv::Size(rect.Width(), rect.Height()));// 缩小或放大Mat并备份

	// 转一下格式 ,这段可以放外面,
	switch (imgTmp.channels())
	{
	case 1:
		cv::cvtColor(imgTmp, imgTmp, CV_GRAY2BGRA); // GRAY单通道
		break;
	case 3:
		cv::cvtColor(imgTmp, imgTmp, CV_BGR2BGRA);  // BGR三通道
		break;
	default:
		break;
	}

	int pixelBytes = imgTmp.channels()*(imgTmp.depth() + 1); // 计算一个像素多少个字节
	// 制作bitmapinfo(数据头)
	BITMAPINFO bitInfo;
	bitInfo.bmiHeader.biBitCount = 8 * pixelBytes;
	bitInfo.bmiHeader.biWidth = imgTmp.cols;
	bitInfo.bmiHeader.biHeight = -imgTmp.rows;
	bitInfo.bmiHeader.biPlanes = 1;
	bitInfo.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bitInfo.bmiHeader.biCompression = BI_RGB;
	bitInfo.bmiHeader.biClrImportant = 0;
	bitInfo.bmiHeader.biClrUsed = 0;
	bitInfo.bmiHeader.biSizeImage = 0;
	bitInfo.bmiHeader.biXPelsPerMeter = 0;
	bitInfo.bmiHeader.biYPelsPerMeter = 0;
	// Mat.data + bitmap数据头 -> MFC
	CDC *pDC = CmyBoneDlg::s_pDlg->GetDlgItem(nID)->GetDC();
	::StretchDIBits(
		pDC->GetSafeHdc(),
		0, 0, rect.Width(), rect.Height(),
		0, 0, rect.Width(), rect.Height(),
		imgTmp.data,
		&bitInfo,
		DIB_RGB_COLORS,
		SRCCOPY
		);
	CmyBoneDlg::s_pDlg->ReleaseDC(pDC);
}



void   CBodyBasics::draw(Mat & img, Joint & r_1, Joint & r_2, ICoordinateMapper * myMapper)
{
	//用两个关节点来做线段的两端，并且进行状态过滤
	if (r_1.TrackingState == TrackingState_Tracked && r_2.TrackingState == TrackingState_Tracked)
	{
		ColorSpacePoint t_point;    //要把关节点用的摄像机坐标下的点转换成彩色空间的点
		Point   p_1, p_2;
		myMapper->MapCameraPointToColorSpace(r_1.Position, &t_point);
		p_1.x = t_point.X;
		p_1.y = t_point.Y;
		myMapper->MapCameraPointToColorSpace(r_2.Position, &t_point);
		p_2.x = t_point.X;
		p_2.y = t_point.Y;

		/*	line(img, p_1, p_2, Vec3b(0, 255, 0), 5);
		circle(img, p_1, 10, Vec3b(255, 0, 0), -1);
		circle(img, p_2, 10, Vec3b(255, 0, 0), -1);*/
		line(img, p_1, p_2, Scalar(0, 255, 0), 5);
		circle(img, p_1, 10, Scalar(255, 0, 0), -1);
		circle(img, p_2, 10, Scalar(255, 0, 0), -1);
	}
}