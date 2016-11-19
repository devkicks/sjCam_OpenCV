// Code for accessing live streams in OpenCV
// This code was written for SJCAM 4000 Wifi camera
// The idea is to using grab/retrieve functions to grab only current frames

// One thing to note is that the OpenCV needs to be recompiled with ffmpeg
// This will generate an opencv_ffmpegXXX.dll which is required by the program at runtime
// Copy this dll in the debug or release folder containing *.exe files


#include "opencv\cv.h"
#include "opencv\highgui.h"
#include <iostream>
#include <windows.h>

cv::VideoCapture sjCam;
cv::vector<cv::Mat> imageVec;
cv::Mat bufferM; 
char ch = ' ';


// thread to keep on reading images into memory to prevent decoding error
// write to shared vector only when we need the images
DWORD WINAPI readImage(LPVOID lpParameter)
{
	while(ch != 'q')
	{
		if(sjCam.grab())
		{
				sjCam.retrieve(bufferM);
		}

		if(!imageVec.size())
		{
			
				imageVec.push_back(bufferM);
		//	}
		}
	}
	return 0;
}


int main()
{

	//cv::VideoCapture sjCam;
	sjCam.open("rtsp://192.168.1.254/sjcam.mov"); 
	//sjCam.open(0); 
	// URL for SJCAM - it may be different for other wifi cameras

	if(!sjCam.isOpened())
	{
		// the camera failed to open
		std::cout << "The camera failed to open" << std::endl;
		exit(EXIT_FAILURE);
	}

	//cv::Mat inImage; // container for storing our incoming stream of images
	DWORD myThreadID;
	HANDLE myHandle = CreateThread(0, 0, readImage, 0, 0, &myThreadID);


	// character to get input from waitkey function
	//char ch = ' ';
	cv::Mat inImage;

	while(ch != 'q')
	{
		// grab the current frame and retrieve it using mat container
		//if(sjCam.grab())
		//sjCam.retrieve(inImage);
		if(imageVec.size() == 1)
		{
			inImage = imageVec[0];
			imageVec.pop_back();
		}

		// check if the image was successfully downloaded
		if(!inImage.empty())
		{
			// Write your processing application here


			cv::imshow("SJCAM Stream", inImage);

			ch = cv::waitKey(100);
		}
	}

	WaitForSingleObject(myHandle, INFINITE);
	CloseHandle(myHandle);
	return 1;
}