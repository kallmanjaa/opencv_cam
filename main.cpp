#include "face_detect.h"
#include <signal.h>
#include <unistd.h>

volatile sig_atomic_t flag = 0;

void sig_handler(int sig){ // can be called asynchronously
  flag = 1; // set flag
}

void * myfunc(void * arg){

	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL); 

	while(1) {
		((opencv::opencvFaceDetect *) arg)->detectFace();
	}
	return NULL;
}

int main(){

	signal(SIGINT, sig_handler); 
	int deviceId=0;
	std::string path = "/home/bentur/project/opencv_camera/haarcascade_frontalcatface_alt.xml";
	pthread_t thread;


	opencv::opencvFaceDetect * camera = new opencv::opencvFaceDetect(deviceId,path);

	if(camera->camOpen() == -1){
		return -1;
	}

	camera->loadXml();

	pthread_create(&thread,NULL, myfunc, camera);

	struct timespec sleep_time = {1, 40000000000L};

	while(1){

		if(flag){
			std::cout<<"key CTRL-C pressed -- terminating"<<std::endl;
			 pthread_cancel(thread);
			 pthread_join(thread, NULL);
			break;
		}
 		nanosleep(&sleep_time, NULL);	
 	}

 	camera->closeCam();

	delete camera;

}