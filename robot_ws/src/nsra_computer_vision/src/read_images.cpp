#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <stdio.h>
#include <iostream>
#include "popt_pp.h"
#include <thread> 
#include <mutex>

using namespace std;
using namespace cv;

int x = 0;
bool t1 = true;
bool t2 = true;
bool t = true;
Mat img1, img_res1, img2, img_res2;
mutex m1;
mutex m2;

VideoCapture cap1("rtsp://192.168.1.171");
VideoCapture cap2("rtsp://192.168.1.190");

void cam1(char* imgs_directory, char* extension, int im_width, int im_height){
  while(1){
    m1.lock();
    cap1.read(img1);
    m1.unlock();
  }
}

void cam2(char* imgs_directory, char* extension, int im_width, int im_height){
  while(1){
    m2.lock();
    cap2.read(img2);
    m2.unlock();
  }
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
  
  cap1.set(CAP_PROP_BUFFERSIZE, 2);
  cap2.set(CAP_PROP_BUFFERSIZE, 2);

  std::thread thread1(cam1, imgs_directory_arg, extension_arg, im_width_arg, im_height_arg); 
  std::thread thread2(cam2, imgs_directory_arg, extension_arg, im_width_arg, im_height_arg);¨
  
  while(1){
    m1.lock();
    img_res1 = img1;
    m1.unlock();
    m2.lock();
    img_res2 = img2;
    m2.unlock();
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
