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

cv::Mat points4d;
Mat cam_left_pnts(1,1,CV_64FC2);
Mat cam_right_pnts(1,1,CV_64FC2);
Mat PL, PR;

ros::ServiceClient right_camera;
ros::ServiceClient left_camera;

void calcCallback(const std_msgs::StringConstPtr& str)
{
    nsra_odrive_interface::coords right_camera_coords;
    nsra_odrive_interface::coords left_camera_coords;
    right_camera_coords.request.test = 1;
    left_camera_coords.request.test = 1;
    right_camera.call(right_camera_coords);
    left_camera.call(left_camera_coords);
    cam_right_pnts.at<double>(0,0) = right_camera_coords.response.x;
    cam_right_pnts.at<double>(0,1) = right_camera_coords.response.y;
    cam_left_pnts.at<double>(0,0) = left_camera_coords.response.x;
    cam_left_pnts.at<double>(0,1) = left_camera_coords.response.y;

    triangulatePoints(PL,PR,cam_left_pnts,cam_right_pnts,points4d);

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

int main(int argc, char** argv)
{

    ros::init(argc, argv, "bottle_detection");
    ros::NodeHandle n;
    ros::Subscriber sub = n.subscribe("calc3Dcoords", 1, calcCallback);
    right_camera = n.serviceClient<nsra_odrive_interface::coords>("right_camera");
    left_camera = n.serviceClient<nsra_odrive_interface::coords>("left_camera");

    FileStorage fs(ros::package::getPath("nsra_computer_vision") + "/" + "cam_stereo.yml", FileStorage::READ);

    fs["PL"] >> PL;
    fs["PR"] >> PR;
    
    cout << PL << endl;
    cout << PR << endl;

    ros::spin();
        
    /*
    std::vector<Point3d> results;

    Point3d point = Point3d(points4d.at<double>(0, 0) / points4d.at<double>(3, 0),
                            points4d.at<double>(1, 0) / points4d.at<double>(3, 0),
                            points4d.at<double>(2, 0) / points4d.at<double>(3, 0));
    results.emplace_back(point);
    */
}