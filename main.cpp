#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "std_msgs/String.h"
#include<vector>
#include<iostream>
#include <opencv2/opencv.hpp>

//////////////////////////////////////////////////////////////////////////////////
/// \brief cxg_bgr
/// \param array_bayer
///this is convert of raw bayerrg8 to rgb format(1280*1024)
/////////////////////////////////////////////////////////////////////////////////
void cxg_bgr(unsigned char *array_bayer)
{
    cv::Mat opencv_Bayer(cv::Size(1280,1024),CV_8UC1);  // bayer data in opencv (value is equl to raw ros bayer data)
    cv::Mat opencv_Bgr(cv::Size(1280,1024),CV_8UC3);    //final bgr data in opencv
    int framesize = 1280 * 1024;
    unsigned char * bayerdata=( unsigned char *) malloc (sizeof( unsigned char * ) * framesize);
    bayerdata=array_bayer;    //bayerdata is a temp variable
    opencv_Bayer.data=bayerdata;
    printf("opencv bayer: %d\n",opencv_Bayer.data[10000]);
    cv::cvtColor(opencv_Bayer, opencv_Bgr, cv::COLOR_BayerGR2RGB);
    printf("opencv bgr channel1:%d channel2:%d  channel3:%d\n",opencv_Bgr.at<cv::Vec3b>(1000,1000)[0],opencv_Bgr.at<cv::Vec3b>(1000,1000)[1],opencv_Bgr.at<cv::Vec3b>(0,0)[2]);
    imshow("view",opencv_Bgr);
    cv::waitKey(30);
}

void convertCallback(const sensor_msgs::ImageConstPtr& msg)
{

   // unsigned char *data;
    try
    {

         //ROS_INFO("%d",msg->step);
         //  std::vector<unsigned char> dataccc;
         const unsigned char * tmp = &(msg->data[0]);
         unsigned char array[1310720];
         unsigned char *array_bayer = (unsigned char *)tmp;
         unsigned char *array_bgr;
         cxg_bgr(array_bayer);

    }
    catch (cv_bridge::Exception& e)
    {
      ROS_ERROR("Could not convert from '%s' to 'bgr8'.", msg->encoding.c_str());
    }

}


int main(int argc, char** argv)
{

  ros::init(argc, argv, "cxg_camera");

  ros::NodeHandle cxg;
  cv::namedWindow("view");
  cv::startWindowThread();
  image_transport::ImageTransport it(cxg);
  image_transport::Subscriber sub = it.subscribe("/camera/image_raw", 1000, convertCallback);
  ros::spin();
  return 0;
}
