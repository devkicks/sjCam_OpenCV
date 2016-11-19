// Code for accessing live streams in OpenCV
// This code was written for SJCAM 4000 Wifi camera
// The idea is to using grab/retrieve functions to grab only current frames

// One thing to note is that the OpenCV needs to be recompiled with ffmpeg
// This will generate an opencv_ffmpegXXX.dll which is required by the program at runtime
// Copy this dll in the debug or release folder containing *.exe files


#include "opencv\cv.h"
#include "opencv\highgui.h"
#include <iostream>

int main()
{

	cv::VideoCapture sjCam;
	sjCam.open("rtsp://192.168.1.254/sjcam.mov"); 
	// URL for SJCAM - it may be different for other wifi cameras

	if(!sjCam.isOpened())
	{
		// the camera failed to open
		std::cout << "The camera failed to open" << std::endl;
		exit(EXIT_FAILURE);
	}

	cv::Mat inImage; // container for storing our incoming stream of images

	// character to get input from waitkey function
	char ch = ' ';

	while(ch != 'q')
	{
		// grab the current frame and retrieve it using mat container
		if(sjCam.grab())
			sjCam.retrieve(inImage);

		// check if the image was successfully downloaded
		if(!inImage.empty())
		{
			// Write your processing application here


			cv::imshow("SJCAM Stream", inImage);

			ch = cv::waitKey(1);
		}
	}

	return 1;
}