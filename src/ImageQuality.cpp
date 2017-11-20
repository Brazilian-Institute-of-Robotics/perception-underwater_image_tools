#include "ColorBalance.hpp"

#include <vector>
#include <iostream>

#include <opencv2/imgproc/imgproc.hpp>

namespace underwater_image_tools {

float computeEdgeDensity( cv::Mat image,
                          int canny_threshold,
                          cv::Size image_size ){

    if( image.size().area() > image_size.area() )
        cv::resize(image, image, image_size );

    cv::Canny(image, image, canny_threshold, 255, 3);
    cv::Scalar out_scalar = cv::sum(image);

    float density = out_scalar[0] / image.size().area();

    return density;
}


}
