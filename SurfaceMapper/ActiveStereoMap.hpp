#ifndef ACTIVE_STEREO_MAP
#define ACTIVE_STEREO_MAP

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <opencv2/opencv.hpp>
#include "ProcGen.hpp"

#define PROJECTOR_W 848
#define PROJECTOR_H 480 

using namespace cv;
class ActiveStereoMap
{
public:
  ActiveStereoMap(VideoCapture c, Size projSize);
  void runMapping(int levels);
  Mat computeDisparity(Mat dCam, Mat dProj, Mat R, Mat T);
  Mat getGraymap(void);
  Mat getGrayComposite(void);
  Mat grayFilter(Mat src, int graylvl);
private:
  VideoCapture cap;
  Size patternSize;
  Size streamSize;
  Mat grayImg;
  Mat grayPattern;
  
  int intPow(int base, unsigned int power);
  void processRawImage(Mat rawImg, Mat destImg, int thresh, int factor);
  void capturePattern(Mat tempPattern, Mat tempMat, int levels, int level);
};

#endif