#ifndef _OBJECT_HPP
#define _OBJECT_HPP

class Object{
private:
  
  void getTrainingObservations(void);
  
  void calcCovarMean(void);

  void calcIcovar(void);

  void calcCoG(void);
  
  void calcVelocity(void);  

  int num_of_samples;

public:
  cv::Mat training_image;
  cv::Mat covar;
  cv::Mat icovar;
  cv::Mat mean;
  cv::Mat* training_observations;
  cv::Mat current_frame;
  std::string name;
  int int_threshold;
  double double_threshold;
  ObjectState prev_state;
  ObjectState current_state;
  int obs_num;
  time_t last_vel_calc;
  bool first_cycle;

  void updateState(const cv::Mat& frame_);
  
  Object(const std::string& name_, const std::string& img_path_, const double& threshold_);
  
  ~Object();
};

#endif
