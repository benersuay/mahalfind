#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <string>
#include <vector>
#include <ctime>

#include "../include/ObjectState.hpp"

ObjectState::ObjectState() : x(0), y(0), vx(0), vy(0){
}

ObjectState::~ObjectState(){}

void ObjectState::reset(){
  x = 0; y = 0; vx = 0; vy = 0;
}
  
