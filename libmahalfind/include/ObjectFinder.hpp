#ifndef _OBJECTFINDER_HPP
#define _OBJECTFINDER_HPP

class ObjectFinder{ 
public:

  std::vector<Object> objects;
  std::vector<ObjectState> object_state;

  ObjectFinder(void);
  
  ~ObjectFinder(void);
  
  void addObject(const std::string& name_, const std::string& training_image_, const double& threshold_);
  
  void getAllObjects(std::vector<Object>& objects_, const cv::Mat& src_);
  
};

#endif
