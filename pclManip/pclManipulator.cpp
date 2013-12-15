/*
 * pclManipulator.cpp
 * Point Cloud manipulation utility
 * Authors: Jakob Hoellerbauer, Cody Hyman, Scott Meldrum
 * December, 2013
 */

#include "pclManipulator.hpp"

pclManipulator::pclManipulator()
{
  PointCloud<PointXYZINormal>::Ptr temp (new PointCloud<PointXYZINormal>);
  pptr = temp;
  applyMedian = true;
  applyRadOutRem = true;
  applyPassThrough = true;
  medianWindowSize = 5;
  filtered = false;
  searchRadius = 0.2;
  minNeighbors = 10;
  minZLimit = -1000;
  maxZLimit = 1000;
  
}

void pclManipulator::initialize(const string & fileName)
{
struct stat buf;
if(stat(fileName.c_str(),&buf)!=-1)
{
  cerr << "Warning: ply file given to pclManipulator does not exist" << endl;
  cerr << "No data will be loaded" << endl;
}
else
  io::loadPLYFile(fileName,*pptr);
}

void pclManipulator::initialize(cv::Mat disparityMap)
{
    vector<float> v;
    vector<float> row;
    cv::Size s = disparityMap.size();

    for(int i=0;i<s.height;i++)
    {
      float* pointer = disparityMap.ptr<float>(i);
      row = vector<float>(pointer,pointer+disparityMap.cols);
      v.insert(v.end(),row.begin(),row.end());
    }
    io::OrganizedConversion<PointXYZINormal,false> OC;   
    std::vector<uint8_t> temp;
    OC.convert(v,temp,false,s.width,s.height,1,*pptr);
}
    
void pclManipulator::filterPC()
{
  //Apply Median Filter
  if(applyMedian)
  {
    PointCloud<PointXYZINormal>::Ptr tempPtr(new PointCloud<PointXYZINormal>(*pptr));
    MedianFilter<PointXYZINormal> m;
    m.setInputCloud(tempPtr);
    m.setWindowSize(medianWindowSize);
    m.filter(*pptr);
    m.~MedianFilter<PointXYZINormal>();
    filtered = true;
  }
  if(applyRadOutRem)
  {
    PointCloud<PointXYZINormal>::Ptr tempPtr(new PointCloud<PointXYZINormal>(*pptr));
    cout << "Warning: applying radius outlier removal filter on point cloud" << endl;
    cout << "This will cause the point cloud to become unordered!" << endl;
    RadiusOutlierRemoval<PointXYZINormal> r(true);
    StatisticalOutlierRemoval<PointXYZINormal> sor(true);
    r.setInputCloud(tempPtr);
    r.setRadiusSearch(searchRadius);
    r.setMinNeighborsInRadius(minNeighbors);
    r.filter(*pptr);
    sor.setInputCloud(pptr);
    sor.setMeanK(50);
    sor.setStddevMulThresh(1.0);
    sor.filter(*pptr);
    r.~RadiusOutlierRemoval<PointXYZINormal>();
    sor.~StatisticalOutlierRemoval<PointXYZINormal>();
    filtered = true;
  }
  if(applyPassThrough)
  {
    PointCloud<PointXYZINormal>::Ptr tempPtr(new PointCloud<PointXYZINormal>(*pptr));
    cout << "Warning: applying passThrough filter on point cloud" << endl;
    cout << "This will cause the point cloud to become unordered!" << endl;   
    PassThrough<PointXYZINormal> pt(true);
    pt.setFilterFieldName("z");
    pt.setFilterLimits(minZLimit,maxZLimit);
    pt.filter(*pptr);
    pt.~PassThrough<PointXYZINormal>();
    filtered = true;
  }  
}

 void pclManipulator::saveToFile(int fileType, const string & fileName)
{
  if(fileType==1)
    io::savePLYFile(fileName,*pptr);
  else if(fileType==2)
    io::savePCDFile(fileName,*pptr);
  else
    cerr << "ERROR: fileType not recognized "     \
         << endl << "Use 1 to save as PLY file "  \
         << endl << "Use 2 to save as PCD file " << endl;
}

void pclManipulator::setApplyMedian(bool in)
{
  applyMedian = in;
}

void pclManipulator::setApplyRadOutRem(bool in)
{
  applyRadOutRem = in;
}

void pclManipulator::setApplyPassThrough(bool in)
{
  applyPassThrough = in;
}

void pclManipulator::setMedianWindowSize(int winSize)
{
  medianWindowSize = winSize;
}

void pclManipulator::setSearchRadius(double rad)
{
  searchRadius = rad;
}

void pclManipulator::setMinNeighbors(int mN)
{
  minNeighbors = mN;
}


void pclManipulator::setZLimits(double min, double max)
{
  minZLimit = min;
  maxZLimit = max;
}

bool pclManipulator::getApplyMedian(bool in)
{
  return applyMedian;
}

bool pclManipulator::getApplyRadOutRem(bool in)
{
  return applyRadOutRem;
}

bool pclManipulator::getApplyPassThrough(bool in)
{
  return applyPassThrough;
}
int pclManipulator::getMedianWindowSize(int winSize)
{
  return medianWindowSize;
}

double pclManipulator::getSearchRadius()
{
  return searchRadius;
}

int pclManipulator::getMinNeighbors()
{
  return minNeighbors;
}
/*
array<double,2> pclManipulator::getZLimits()
{
  double ret[2] = {minZLimit, maxZLimit};
  return ret;
*/




