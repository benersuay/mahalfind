Color Filtering with Mahalanobis Distance
=========================================

This is a tiny library for detecting objects with different colors in captured camera frames, based on the mean, and covariance of a given training image, and a mahalanobis distance threshold. The code finds the mean and the covariance of the training image. For object detection, the code checks how similar every pixel of the captured frame to the mean of the training image if they were to come from the same distribution. If the mahalanobis distance (dissimilarity) is more than a certain threshold, then the pixel in the captured frame is filtered out, otherwise it's shown in white.

Based on the center of the white pixels, the library can give the x,y coordinates and vx, vy velocities of detected objects.

"Mahalanobis distance is used to identify and gauge similarity of an unknown sample set (i.e. captured picture / video frame)  to a known one (i.e. the training image)." For more information see http://en.wikipedia.org/wiki/Mahalanobis_distance.

Dependency
----------

Tested on Ubuntu 12.04, with OpenCV 2.4.6. 


Compile
-------

Compiling libmahalfind library (required)

    cd mahalfind/libmahalfind
    mkdir build
    cd build
    cmake ..
    make
    
Compiling mahalfind example code

    cd mahalfind
    mkdir build
    cd build
    cmake ..
    make
    
Running mahalfind example

    cd mahalfind/bin
    ./object_finder

The executable above should launch three windows (red, green, blue) and filter pixels out based on the pure_red,green,blue.png images.

Example
-------

For instance, the following image (captured in RGB) would appear as the second image shown below when ran through mahalfind

![rgbframe](http:www.wpi.edu/~benersuay/resimler/projects/mahalfind01.jpg?raw=true "RGB Frame")

![mahalfind](http:www.wpi.edu/~benersuay/resimler/projects/mahalfind02.png?raw=true "Mahal Find")


