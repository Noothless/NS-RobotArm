#include <opencv2/core/core.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <iostream>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
#include "nsra_odrive_interface/coords.h"
#include <ros/package.h>

using namespace std;
using namespace cv;

Mat pnts3D(1,1,CV_64FC4);
Mat cam0pnts(1,1,CV_64FC2);
Mat cam1pnts(1,1,CV_64FC2);
Mat P1, P2;

int main(int argc, char** argv)
{

    ros::init(argc, argv, "bottle_detection");
    ros::NodeHandle n;

    FileStorage fs(ros::package::getPath("nsra_computer_vision") + "/" + "cam_stereo.yml", FileStorage::READ);

    fs["P1"] >> P1;
    fs["P2"] >> P2;
    
    cout << P1 << endl;
    cout << P2 << endl;

    vector<vector<double>> vec{ {763.9179 , 146.99612, 1136.4603, 189.02242},
                                {1410.4741, 178.00208, 1789.9531, 202.65692},
                                {662.7758 , 640.4207 , 1161.9884, 684.38464},
                                {1211.7473, 679.71954, 1729.7555, 708.58624} };



    for(int i = 0; i < 4; i++) {
        cam0pnts.at<double>(0,0) = vec[i][0];
        cam0pnts.at<double>(0,1) = vec[i][1];
        cam1pnts.at<double>(0,0) = vec[i][2];
        cam1pnts.at<double>(0,1) = vec[i][3];
    
        triangulatePoints(P1,P2,cam1pnts,cam0pnts,pnts3D);

        //cout << pnts3D << endl;

        cv::Mat1f Thomogeneous(4, 1); 
        Thomogeneous(0) = pnts3D.at<double>(0,0);
        Thomogeneous(1) = pnts3D.at<double>(0,1);
        Thomogeneous(2) = pnts3D.at<double>(0,2);
        Thomogeneous(3) = pnts3D.at<double>(0,3);

        Mat Th = Thomogeneous.reshape(4);

        cv::Mat T;
        cv::convertPointsFromHomogeneous(Th, T);

        cout << T << endl;
    }
}