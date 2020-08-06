#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <iostream>
#include "popt_pp.h"
#include <thread> 

using namespace std;
using namespace cv;

int x = 0;
bool t1 = true;
bool t2 = true;
bool t = true;
Mat img1, img_res1,img2, img_res2;

VideoCapture cap1("rtsp://192.168.1.171", 3);
VideoCapture cap2("rtsp://192.168.1.190", 3);

void cam1(int im_width, int im_height){
  cap1 >> img1;
  resize(img1, img_res1, Size(im_width, im_height));
}

void cam2(int im_width, int im_height){
  cap2 >> img2;
  resize(img2, img_res2, Size(im_width, im_height));
}



int main(int argc, char const *argv[])
{
  char* imgs_directory_arg;
  char* extension_arg;
  int im_width_arg, im_height_arg;

  static struct poptOption options[] = {
    { "img_width",'w',POPT_ARG_INT,&im_width_arg,0,"Image width","NUM" },
    { "img_height",'h',POPT_ARG_INT,&im_height_arg,0,"Image height","NUM" },
    { "imgs_directory",'d',POPT_ARG_STRING,&imgs_directory_arg,0,"Directory to save images in","STR" },
    { "extension",'e',POPT_ARG_STRING,&extension_arg,0,"Image extension","STR" },
    POPT_AUTOHELP
    { NULL, 0, 0, NULL, 0, NULL, NULL }
  };

  POpt popt(NULL, argc, argv, options, 0);
  int c;
  while((c = popt.getNextOpt()) >= 0) {}
  
  

  while(1){
    std::thread thread1(cam1, im_width_arg, im_height_arg); 
    std::thread thread2(cam2, im_width_arg, im_height_arg);
    thread1.join();
    thread2.join();
    imshow("IMG1", img_res1);
    imshow("IMG2", img_res2);
    int key = waitKey(50);
    if ((key != 255)) {
      x++;
      char filename1[200], filename2[200];
      sprintf(filename1, "%sright%d.%s", imgs_directory_arg, x, extension_arg);
      sprintf(filename2, "%sleft%d.%s", imgs_directory_arg, x, extension_arg);
      cout << "Saving img pair" << x << endl;
      imwrite(filename1, img_res1);
      imwrite(filename2, img_res2);
      t = true;
    } else if (key == 255){
      t = false;
    }
  }
  return 0;
}
