#pragma once

#include <Kinect.h>
#include "cv.h"
#include <opencv2/opencv.hpp>	//opencvͷ�ļ�
#include <opencv2/core/core.hpp>  
#include <opencv2/highgui/highgui.hpp> 

using namespace cv;
using namespace std;			//�����ռ�

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
	void                    Update();//��ùǼܡ�������ֵͼ�������Ϣ
	HRESULT                InitKinect();//���ڳ�ʼ��kinect

private:
	IKinectSensor*          m_pKinectSensor;// Current Kinect
	IColorFrameReader*      m_pColorFrameReader;// Color reader
	RGBQUAD*                m_pColorRGBX;
public:
	void    DrawMat(cv::Mat & img, UINT nID);
	void    ProcessColor(RGBQUAD* pBuffer, int nWidth, int nHeight);
	void    draw(Mat & img, Joint & r_1, Joint & r_2, ICoordinateMapper * myMapper);//���߸�Բ


//-------------------------//
public:  
	IBodyFrameSource    * myBodySource; 
	IBodyFrameReader    * myBodyReader;
	int myBodyCount; 
	IBodyFrame  * myBodyFrame; 
	ICoordinateMapper   * myMapper;  
	Mat copy;
};