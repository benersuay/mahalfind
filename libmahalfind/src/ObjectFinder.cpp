/* Bener Suay
 * 
 * benersuay@wpi.edu
 *
 * Feb 2014
 */

#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <string>
#include <vector>

#include "../include/ObjectState.hpp"
#include "../include/Object.hpp"
#include "../include/ObjectFinder.hpp"

ObjectFinder::ObjectFinder(){
  objects.reserve(10);
  object_state.reserve(10);
}

ObjectFinder::~ObjectFinder(){
}

void ObjectFinder::addObject(const std::string& name_, const std::string& training_image_, const double& threshold_){
  Object new_object(name_, training_image_, threshold_);
  objects.push_back(new_object);  
}

void ObjectFinder::getAllObjects(std::vector<Object>& objects_, const cv::Mat& src_){

  objects_.clear();
  
  for(unsigned i=0; i < objects.size(); i++){
    objects[i].updateState(src_);
    objects_.push_back(objects[i]);
  }
}
