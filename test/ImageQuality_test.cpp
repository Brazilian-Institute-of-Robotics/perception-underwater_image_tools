#include <string>
#include <iostream>
#include <vector>
#include <ctime>

#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test_suite.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <underwater_image_tools/ImageQuality.hpp>
#include <underwater_image_tools/ColorBalance.hpp>

#define FILE_NAME "img_%02d.jpg"
#define LOCAL_PATH "/dataset/"
const std::string ABSOLUTE_PATH(__FILE__);

using namespace underwater_image_tools;

BOOST_AUTO_TEST_CASE(computeEdgeDensity_test) {

    std::string path_dataset = ABSOLUTE_PATH.substr(
                                            0,
                                            ABSOLUTE_PATH.find_last_of("/"));

    path_dataset += std::string(LOCAL_PATH) + std::string(FILE_NAME);
    std::cout << "DATASET PATH " << path_dataset << std::endl;

    cv::VideoCapture capture(path_dataset);
    int i = 0;
    while(capture.grab()){

        cv::Mat img;
        capture.retrieve(img);
        float density = computeEdgeDensity(img);
        std::cout  << "Image | Density -> " << i++
                   << " | " << density << std::endl;
        cv::imshow("IMAGE" , img);
        cv::waitKey();
    }
}


BOOST_AUTO_TEST_CASE(computeEdgeDensity_fps_test) {

    std::string path_dataset = ABSOLUTE_PATH.substr(
                                            0,
                                            ABSOLUTE_PATH.find_last_of("/"));

    path_dataset += std::string(LOCAL_PATH) + "video_00.avi";
    std::cout << "DATASET PATH " << path_dataset << std::endl;

    cv::VideoCapture capture(path_dataset);
    int i = 0;
    while(capture.grab()){

        cv::Mat img;
        capture.retrieve(img);

        std::clock_t begin_time = std::clock();
        float density = computeEdgeDensity(img);
        std::clock_t end_time = std::clock();
        double fps = double(end_time - begin_time) / CLOCKS_PER_SEC;

        std::cout  << "Image | Density | FPS -> " << i++
                   << " | " << density
                   << " | " << fps  << std::endl;

        cv::imshow("IMAGE" , img);
        cv::waitKey(1);
    }
}


BOOST_AUTO_TEST_CASE(computeEdgeDensityWithColorBalance_test) {

    std::string path_dataset = ABSOLUTE_PATH.substr(
                                            0,
                                            ABSOLUTE_PATH.find_last_of("/"));

    path_dataset += std::string(LOCAL_PATH) + std::string(FILE_NAME);
    std::cout << "DATASET PATH " << path_dataset << std::endl;

    cv::VideoCapture capture(path_dataset);
    int i = 0;
    while(capture.grab()){

        cv::Mat img;
        capture.retrieve(img);
        cv::Mat temp = img.clone();
        float density_before = computeEdgeDensity(temp);

        colorBalance(img, 0.01);
        cv::imshow("COLOR BALANCE" , img);
        float density_after = computeEdgeDensity(img);

        std::cout  << "Image | Density NO COLOR BALANCE | With COLOR BALANCE -> "
                   << i++ << " | " << density_before << " | "
                   << density_after << std::endl;

        cv::imshow("EDGE" , temp);
        cv::imshow("EDGE COLOR BALANCE" , img);
        cv::waitKey();
    }
}

BOOST_AUTO_TEST_CASE(computeEdgeDensityWithColorBalance_video_test) {

  std::string path_dataset = ABSOLUTE_PATH.substr(
                                          0,
                                          ABSOLUTE_PATH.find_last_of("/"));

  path_dataset += std::string(LOCAL_PATH) + "video_00.avi";
  std::cout << "DATASET PATH " << path_dataset << std::endl;

  cv::VideoCapture capture(path_dataset);

  AdaptiveColorBalance color_balance(cv::Scalar(40, 51, 10),
                                     cv::Scalar(190, 235, 60));
  AdaptiveColorBalance color_balance_cl(cv::Scalar(40, 51, 10),
                                        cv::Scalar(190, 235, 60));

  cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE(2, cv::Size(4, 4));
  std::vector<cv::Mat> channels;

  int i = 0;
  while(capture.grab()){

      cv::Mat img;
      capture.retrieve(img);
      cv::imshow("out original" , img);
      cv::Mat original = img.clone();
      float density_before = computeEdgeDensity(original, 30);

      cv::Mat im_balance = img.clone();
      color_balance.apply(im_balance, 0.01, 0.1);
      cv::imshow("out colorBalance " , im_balance);
      float density_after = computeEdgeDensity(im_balance, 30);

      color_balance_cl.apply(img, 0.01, 0.1);
      cv::cvtColor(img, img, CV_BGR2HSV);
      cv::split(img, channels);
      clahe->apply(channels[2], channels[2]);
      cv::merge(channels, img);
      cv::cvtColor(img, img, CV_HSV2BGR);
      cv::imshow("out clahe " , img);
      float density_cl = computeEdgeDensity(img, 30);

      cv::hconcat(img, im_balance, img);
      cv::hconcat(img, original, img);
      cv::imshow("EDGE", img);

      std::cout  << "Image | d | d_CB | CB + CLAHE -> " << i++
                 << " | " << density_before
                 << " | " << density_after
                 << " | " << density_cl
                 << std::endl;

      cv::waitKey();
  }
}
