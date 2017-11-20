#ifndef PERCEPTION_UNDERWATER_IMAGE_TOOLS_IMAGEQUALITY_HPP_
#define PERCEPTION_UNDERWATER_IMAGE_TOOLS_IMAGEQUALITY_HPP_

#include <opencv2/core/core.hpp>

namespace underwater_image_tools {

float computeEdgeDensity( cv::Mat& image,
                          int canny_threshold = 3,
                          cv::Size image_size = cv::Size(250,250));

} // end namespace dehaze_undewater_image

#endif /* PERCEPTION_UNDERWATER_IMAGE_TOOLS_IMAGEQUALITY_HPP_ */
