
#include <string>
#include <iostream>
#include <vector>

#include <boost/test/test_tools.hpp>
#include <boost/test/unit_test_suite.hpp>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <underwater_image_tools/ImageEnhanceViaFusion.hpp>

#define FILE_NAME "img_%02d.jpg"
#define LOCAL_PATH "/dataset/"
const std::string ABSOLUTE_PATH(__FILE__);


using namespace underwater_image_tools;

BOOST_AUTO_TEST_CASE(colorBalance_testcase) {


    std::string path_dataset = ABSOLUTE_PATH.substr(
                                            0,
                                            ABSOLUTE_PATH.find_last_of("/"));

    path_dataset += std::string(LOCAL_PATH) + std::string(FILE_NAME);
    std::cout << "DATASET PATH " << path_dataset << std::endl;

    cv::VideoCapture capture(path_dataset);

    while(capture.grab()){

        cv::Mat img;
        capture.retrieve(img);
        colorBalance(img, 0.01);
        cv::imshow("out processed" , img);
        cv::waitKey(30);
    }
}

BOOST_AUTO_TEST_CASE(colorBalanceGray_testcase) {


    std::string path_dataset = ABSOLUTE_PATH.substr(
                                            0,
                                            ABSOLUTE_PATH.find_last_of("/"));

    path_dataset += std::string(LOCAL_PATH) + std::string(FILE_NAME);
    std::cout << "DATASET PATH " << path_dataset << std::endl;

    cv::VideoCapture capture(path_dataset);

    while(capture.grab()){

        cv::Mat img;
        capture.retrieve(img);
        cvtColor(img, img, CV_BGR2GRAY);
        colorBalance(img, 0.01);
        cv::imshow("out processed" , img);
        cv::waitKey(30);
    }
}


BOOST_AUTO_TEST_CASE(colorBalanceByChannel_testcase) {

    std::string path_dataset = ABSOLUTE_PATH.substr(
                                            0,
                                            ABSOLUTE_PATH.find_last_of("/"));

    path_dataset += std::string(LOCAL_PATH) + std::string(FILE_NAME);
    std::cout << "DATASET PATH " << path_dataset << std::endl;

    cv::VideoCapture capture(path_dataset);

    while(capture.grab()){

        cv::Mat img;
        capture.retrieve(img);
        cv::imshow("out original" , img);
        colorBalance(img, cv::Scalar(0.01,0.001,0.001));

        cv::Ptr<cv::CLAHE> clahe = cv::createCLAHE(2, cv::Size(4, 4));
        std::vector<cv::Mat> channels;
        cv::cvtColor(img, img, CV_BGR2HSV);
        cv::split(img, channels);
        clahe->apply(channels[2], channels[2]);
        cv::merge(channels, img);
        cv::cvtColor(img, img, CV_HSV2BGR);

        cv::imshow("out CLAHE " , img);

        cv::waitKey(30);
    }
}

BOOST_AUTO_TEST_CASE(AdaptiveColorBalance_testcase) {

  std::string path_dataset = ABSOLUTE_PATH.substr(
                                          0,
                                          ABSOLUTE_PATH.find_last_of("/"));

  path_dataset += std::string(LOCAL_PATH) + "video_00.avi";
  std::cout << "DATASET PATH " << path_dataset << std::endl;

  cv::VideoCapture capture(path_dataset);

  AdaptiveColorBalance color_balance(cv::Scalar(40, 51, 10),
                                     cv::Scalar(190, 235, 60));
  while(capture.grab()){

      cv::Mat img;
      capture.retrieve(img);
      cv::imshow("out original" , img);
      color_balance.apply(img, 0.01, 0.1);
      cv::imshow("out colorBalance " , img);

      cv::waitKey(1);
  }
}
