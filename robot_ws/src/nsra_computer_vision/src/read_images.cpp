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
bool k = true;
bool t = true;

void cam1(){
  VideoCapture cap1("rtsp://192.168.1.171");
  Mat img1, img_res1;
  while (1) {
    cap1 >> img1;
    resize(img1, img_res1, Size(im_width, im_height));
    imshow("IMG1", img1);
    int key = waitKey(50);
    if ((key != 255) && k) {
      x++;
      char filename1[200];
      sprintf(filename1, "%sleft%d.%s", imgs_directory, x, extension);
      cout << "Saving img pair " << x << endl;
      imwrite(filename1, img1);
      k = false;
    } else if (key == 255){
      k = true;
    }
  }
}

void cam2(){
  VideoCapture cap2("rtsp://192.168.1.190");
  Mat img2, img_res2;
  while (1) {
    cap2 >> img2;
    resize(img2, img_res2, Size(im_width, im_height));
    imshow("IMG1", img2);
    int key = waitKey(50);
    if ((key != 255) && t) {
      x++;
      char filename2[200];
      sprintf(filename2, "%sleft%d.%s", imgs_directory, x, extension);
      cout << "Saving img pair " << x << endl;
      imwrite(filename2, img2);
      t = false;
    } else if (key == 255){
      t = true;
    }
  }
}

int main(int argc, char const *argv[])
{
  char* imgs_directory;
  char* extension;
  int im_width, im_height;

  static struct poptOption options[] = {
    { "img_width",'w',POPT_ARG_INT,&im_width,0,"Image width","NUM" },
    { "img_height",'h',POPT_ARG_INT,&im_height,0,"Image height","NUM" },
    { "imgs_directory",'d',POPT_ARG_STRING,&imgs_directory,0,"Directory to save images in","STR" },
    { "extension",'e',POPT_ARG_STRING,&extension,0,"Image extension","STR" },
    POPT_AUTOHELP
    { NULL, 0, 0, NULL, 0, NULL, NULL }
  };

  POpt popt(NULL, argc, argv, options, 0);
  int c;
  while((c = popt.getNextOpt()) >= 0) {}
  
  std::thread thread1(cam1); 
  std::thread thread2(cam2); 
  
  return 0;
}
