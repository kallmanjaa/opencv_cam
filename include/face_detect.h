#ifndef FACE_DETECT_H
#define FACE_DETECT_H

#include <opencv2/core/core.hpp>
#include "opencv2/highgui.hpp"
#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <vector>


namespace opencv{
	class opencvFaceDetect{
		public :
			opencvFaceDetect(int device_id , std::string path);
			~opencvFaceDetect();
			int camOpen();
			void loadXml();
			void detectFace();
			void closeCam();
		private:
			cv::VideoCapture cam;
			int deviceID;
			std::string xml_haarcascade_path;
			cv::Mat img;
			cv::CascadeClassifier face_cascade;
	};

}


#endif