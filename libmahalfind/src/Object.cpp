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

#include <ctime>
#include "../include/ObjectState.hpp"
#include "../include/Object.hpp"


Object::Object(const std::string& name_, const std::string& img_path_, const double& threshold_){
  
  // Allocate memory
  covar.create(3, 3, CV_64F);
  icovar.create(3, 3, CV_64F);
  mean.create(1,3, CV_64F);

  // Set properties
  name = name_;
  training_image = cv::imread(img_path_);

  getTrainingObservations();
  calcCovarMean();
  calcIcovar();

  first_cycle = true;
  num_of_samples = 0;

  int_threshold = threshold_;
}

Object::~Object(){
}

void Object::getTrainingObservations(void){
  
  cv::Vec3b b; b[0]=0; b[1]=0; b[2]=0;
  cv::Vec3b w; w[0]=255; w[1]=255; w[2]=255;

  std::vector<cv::Vec3b> output_pixels;
  
  for(int j = 0; j < training_image.rows; j++){
    for(int i = 0; i < training_image.cols; i++){
      if( (training_image.at<cv::Vec3b>(j,i) != b) &&
	  (training_image.at<cv::Vec3b>(j,i) != w) 
	  ){
	output_pixels.push_back(training_image.at<cv::Vec3b>(j,i));
      } // End of if
      else{
	training_image.at<cv::Vec3b>(j,i) = b;
      }
    }// End of for i < training_image.cols
  }// End of for j < training_image.rows
  
  

  std::cout << output_pixels.size() << " training pixels found" <<std::endl;

  cv::Mat obs = cv::Mat::zeros(output_pixels.size(),3,CV_8U);

  for(unsigned i=0; i < output_pixels.size(); i++){
    // cv::Mat has it in BGR order
    // output_pixels has it in BRG order
    obs.at<cv::Vec2b>(i,0)[0] = output_pixels[i][0]; //
    obs.at<cv::Vec2b>(i,1)[0] = output_pixels[i][2]; // 
    obs.at<cv::Vec2b>(i,2)[0] = output_pixels[i][1]; // 
  }
  
  training_observations = new cv::Mat[obs.rows];
  num_of_samples = obs.rows;

  for(int j=0; j < obs.rows; j++){
    
    training_observations[j] = cv::Mat::zeros(1, 3, CV_8UC1);

    training_observations[j].at<cv::Vec2b>(0,0) = obs.at<cv::Vec2b>(j,0);
    training_observations[j].at<cv::Vec2b>(0,1) = obs.at<cv::Vec2b>(j,1);
    training_observations[j].at<cv::Vec2b>(0,2) = obs.at<cv::Vec2b>(j,2);

    training_observations[j].convertTo(training_observations[j], CV_64FC1);
  }  
}

void Object::calcCovarMean(void){
  cv::calcCovarMatrix(training_observations, num_of_samples, covar, mean, CV_COVAR_NORMAL | CV_COVAR_SCALE, CV_64F);
}

void Object::calcIcovar(void){
  cv::invert(covar, icovar, cv::DECOMP_SVD);
}

void Object::calcCoG(void){

  cv::Vec3b b; b[0]=0; b[1]=0; b[2]=0;
  cv::Vec3b w; w[0]=255; w[1]=255; w[2]=255;

  // Do color segmentation using corresponding inverse cov. matrix, mean vector and threshold.
  std::vector<unsigned int> xs, ys;
  unsigned int cogx=0, cogy=0;

  for(int y=0; y < current_frame.rows; y++){
    for(int x=0; x < current_frame.cols; x++){
      
      cv::Mat pixel_vec = cv::Mat::zeros(1,3,CV_64F);
      pixel_vec.at<double>(0,0) = (double)current_frame.at<cv::Vec3b>(y,x)[0]; // B
      pixel_vec.at<double>(0,1) = (double)current_frame.at<cv::Vec3b>(y,x)[1]; // G
      pixel_vec.at<double>(0,2) = (double)current_frame.at<cv::Vec3b>(y,x)[2]; // R

      double temp_dist = cv::Mahalanobis(mean, pixel_vec, icovar);
      // std::cout<<name<<": "<<temp_dist<<std::endl;
      // std::cout<<"is "<<temp_dist<<" > "<<threshold<<" ?"<<std::endl;
      double_threshold = (double)int_threshold*0.1;
      if(temp_dist > double_threshold){
	current_frame.at<cv::Vec3b>(y,x) = b;
      }
      else{
	current_frame.at<cv::Vec3b>(y,x) = w;
	xs.push_back(x);
	ys.push_back(y);
      }
    }
  }

  for(unsigned i=0; i < xs.size(); i++){
    cogx = cogx + xs[i];
    cogy = cogy + ys[i];
  }
  if(xs.size() > 0 && ys.size() > 0){
    current_state.x = cogx / xs.size();
    current_state.y = cogy / ys.size();
  }
  else{
    current_state.x = -1;
    current_state.y = -1;
  }
}

void Object::calcVelocity(void){
  double tdif = difftime(current_state.time_stamp, last_vel_calc);
  if( tdif > 1.0 ){
    current_state.vx = (current_state.x - prev_state.x) / tdif; // [pixel / sec]
    current_state.vy = (current_state.y - prev_state.y) / tdif; // [pixel / sec]
    time(&last_vel_calc);
  }
}

void Object::updateState(const cv::Mat& frame_){
  if(first_cycle){
    time(&last_vel_calc);
    first_cycle = false;
  }

  prev_state = current_state;
  current_frame = frame_.clone();
  time (&current_state.time_stamp);
  calcCoG();
  calcVelocity();
}

