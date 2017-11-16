#ifndef PERCEPTION_UNDERWATER_IMAGE_TOOLS_IMAGEENHANCEVIAFUSION_HPP_
#define PERCEPTION_UNDERWATER_IMAGE_TOOLS_IMAGEENHANCEVIAFUSION_HPP_

#include <opencv2/core/core.hpp>

namespace underwater_image_tools {

void colorBalance(cv::Mat& image, float percent = 0.05);
void colorBalance(cv::Mat& image, const cv::Scalar& percent_channel);

class AdaptiveColorBalance {

public:
    AdaptiveColorBalance();
    AdaptiveColorBalance(cv::Scalar intial_low_value,
                         cv::Scalar intial_top_value);

    void apply(cv::Mat& image,
                  float clip_value = 0.01,
                  float learn_rate = 0.5);

private:
    cv::Scalar low_values_;
    cv::Scalar top_values_;
};

} // end namespace dehaze_undewater_image

#endif /* PERCEPTION_UNDERWATER_IMAGE_TOOLS_IMAGEENHANCEVIAFUSION_HPP_ */
