#include "ImageQuality.hpp"

#include <vector>
#include <iostream>

#include <opencv2/imgproc/imgproc.hpp>

namespace underwater_image_tools {

float computeEdgeDensity( cv::Mat& image,
                          int canny_threshold,
                          cv::Size compute_size ){

    if( image.size().area() > compute_size.area() )
        cv::resize(image, image, compute_size );

    cv::Canny(image, image, canny_threshold, 255, 3);
    cv::Scalar out_scalar = cv::sum(image);
    
    float density = out_scalar[0] / image.size().area();

    return density;
}


}
