#include "pclManipulator.hpp"


int main(int argc, char ** argv)
{
  pclManipulator *pclMan = new pclManipulator();
  pclMan->initialize("boxwall.ply");
  pclMan->filterPC();
  pclMan->saveToFile(1,"boxwall_filtered.ply");
  return 0;
}
