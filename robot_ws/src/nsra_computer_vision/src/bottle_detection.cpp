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

    double c0[] = {876.5602,474.18985};
    double c1[] = {1381.2324,483.25412};

    cam0pnts[0,0] = 876.5602;
    cam0pnts[0,1] = 474.18985;
    cam1pnts[1,0] = 1381.2324;
    cam1pnts[1,1] = 483.25412;
    
    triangulatePoints(P1,P2,cam0pnts,cam1pnts,pnts3D);

    cout << pnts3D << endl;
}