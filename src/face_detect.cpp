
#include "face_detect.h"

namespace opencv{

		opencvFaceDetect::opencvFaceDetect(int device_id , std::string path){

			this->deviceID = device_id;
			this->xml_haarcascade_path = path;
		}

		opencvFaceDetect::~opencvFaceDetect(){

		}

		int opencvFaceDetect::camOpen(){
			this->cam.open(this->deviceID);
			if(this->cam.isOpened() ==0){
				std::cout<<"cam open error"<<std::endl;
				return -1;
			}
			return 0;
		}
		
		void  opencvFaceDetect::loadXml(){
			this->face_cascade.load(this->xml_haarcascade_path);
		}
		
		void opencvFaceDetect::detectFace(){

			this->cam.read(this->img);
		 	std::vector<cv::Rect> faces;
 		 	cv::Mat frame_gray;
  		 	cv::cvtColor(this->img, frame_gray, cv::COLOR_BGR2GRAY);  // Convert to gray scale
  		 	equalizeHist(frame_gray, frame_gray);   	// Equalize histogram

  			this->face_cascade.detectMultiScale(frame_gray, faces, 1.1, 3,0|cv::CASCADE_SCALE_IMAGE, cv::Size(30, 30));

  			// Iterate over all of the faces
  				for( size_t i = 0; i < faces.size(); i++ ) {
    				cv::Point center(faces[i].x + faces[i].width/2, faces[i].y + faces[i].height/2);
    				cv::ellipse(this->img, center, cv::Size(faces[i].width/2, faces[i].height/2),0, 0, 360, cv::Scalar( 255, 0, 255 ), 4, 8, 0 );
  				}

  				cv::imshow("FaceDetect", this->img);  // Display frame
  				cv::waitKey(30);   // Pause key
		}


		void opencvFaceDetect::closeCam(){
			this->cam.release();
		}

}