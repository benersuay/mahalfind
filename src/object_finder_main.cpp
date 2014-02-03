#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <string>
#include <cmath>
#include <vector>

#include <libmahalfind/include/ObjectState.hpp>
#include <libmahalfind/include/Object.hpp>
#include <libmahalfind/include/ObjectFinder.hpp>

int main(int argc, char* argv[]){
  
  ObjectFinder my_objectfinder;

  my_objectfinder.addObject("red","../src/pure_red.png",40.0);
  my_objectfinder.addObject("green","../src/pure_green.png",60.0);
  my_objectfinder.addObject("blue","../src/pure_blue.png",120.0);

  for(unsigned i=0; i<my_objectfinder.objects.size(); i++){
    std::cout << my_objectfinder.objects[i].name << std::endl;
    cv::namedWindow(my_objectfinder.objects[i].name, cv::WINDOW_AUTOSIZE);
  }
  
  cv::VideoCapture cap(0); // open the default camera
  if(!cap.isOpened()){  // check if we succeeded
    std::cout << "Video capture failed." <<std::endl;
  }
  else{
    std::cout << "Video capture succeeded." <<std::endl;
    cap.set(CV_CAP_PROP_FRAME_WIDTH, 320.0);
    cap.set(CV_CAP_PROP_FRAME_HEIGHT, 240.0);
    cv::Mat frame;
    frame.create(240,320,CV_8UC3);
    
    while(true){ 
      
      cap >> frame;

      std::vector<Object> visible_objects;

      my_objectfinder.getAllObjects(visible_objects, frame);

      std::cout<<"---"<<std::endl;
      for(unsigned i=0; i<visible_objects.size(); i++){
	cv::imshow(visible_objects[i].name, visible_objects[i].current_frame);
	std::cout<<visible_objects[i].name<<std::endl<<"x: "<<visible_objects[i].current_state.x<<" - y: "<<visible_objects[i].current_state.y<<std::endl<<"vx: "<<visible_objects[i].current_state.vx<<" - vy: "<<visible_objects[i].current_state.vy<<std::endl<<std::endl;
      }

      if(cv::waitKey(10) >= 0) break;  
      
    } 
  }
  return 0;
}
