#pragma once

#include <Kinect.h>
#include "cv.h"
#include <opencv2/opencv.hpp>	//opencv头文件
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp> 

using namespace cv;
using namespace std;			//命名空间

template<class Interface>
inline void SafeRelease(Interface *& pInterfaceToRelease)
{
	if (pInterfaceToRelease != NULL)
	{
		pInterfaceToRelease->Release();
		pInterfaceToRelease = NULL;
	}
}

class  CBodyBasics
{

public:
	static const int        cColorWidth = 1920;
	static const int        cColorHeight = 1080;
	CBodyBasics();
	~CBodyBasics();
	void                    Update();//获得骨架、背景二值图和深度信息
	HRESULT                InitKinect();//用于初始化kinect

private:
	IKinectSensor*          m_pKinectSensor;// Current Kinect
	IColorFrameReader*      m_pColorFrameReader;// Color reader
	RGBQUAD*                m_pColorRGBX;
public:
	void    DrawMat(cv::Mat & img, UINT nID);
	void    ProcessColor(RGBQUAD* pBuffer, int nWidth, int nHeight);
	void    draw(Mat & img, Joint & r_1, Joint & r_2, ICoordinateMapper * myMapper);//画线跟圆


//-------------------------//
public:  
	IBodyFrameSource    * myBodySource; 
	IBodyFrameReader    * myBodyReader;
	int myBodyCount; 
	IBodyFrame  * myBodyFrame; 
	ICoordinateMapper   * myMapper;  
	Mat copy;
};