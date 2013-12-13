#ifndef PCL_MANIPULATOR_H
#define PCL_MANIPULATOR_H

#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <sys/stat.h>
#include <vector>

#include <pcl/filters/median_filter.h>
#include <pcl/filters/radius_outlier_removal.h>
#include <pcl/filters/passthrough.h>
#include <pcl/io/ply_io.h>
#include <pcl/io/pcd_io.h>
#include <pcl/compression/organized_pointcloud_conversion.h>


using namespace pcl;
using namespace std;

class pclManipulator
{
public:
  pclManipulator();
  void initialize(const string & fileName);
  void initialize(cv::Mat disparityMap);
  void filterPC();
    //RadiusOutlierRemoval
    //PassThrough
    //BilateralFilter
  void saveToFile(int fileType, const string & fileName);

  //Set Functions
  void setApplyMedian(bool in);
  void setApplyRadOutRem(bool in);
  void setApplyPassThrough(bool in);
  void setMedianWindowSize(int winSize);
  void setSearchRadius(double rad);
  void setMinNeighbors(int nM);
  void setZLimits(double min, double max);

  //Get Functions 
  bool getApplyMedian(bool in);
  bool getApplyRadOutRem(bool in);
  bool getApplyPassThrough(bool in);
  int getMedianWindowSize(int winSize);
  bool isFiltered();
  double getSearchRadius();
  int getMinNeighbors();
  //array<double,2> getZLimits();

private:
  PointCloud<PointNormal> p;
  bool applyMedian;
  bool applyRadOutRem;
  bool applyPassThrough;
  int medianWindowSize;
  bool filtered;
  double searchRadius;
  int minNeighbors;
  double minZLimit;
  double maxZLimit;
};

#endif