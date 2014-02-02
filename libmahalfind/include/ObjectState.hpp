#ifndef _OBJECTSTATE_HPP
#define _OBJECTSTATE_HPP

class ObjectState{
public:
  int x, y;
  double vx, vy;
  time_t time_stamp;

  // Constructor
  ObjectState();

  // Destructor
  ~ObjectState();

  // assigns zero to all values
  void reset();
};

#endif
