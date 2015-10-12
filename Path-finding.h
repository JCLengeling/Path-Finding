#include <iostream>
#include <vector>
#include <queue>
#include <functional>


std::vector<int> iterate(  const int index, std::vector<int> currentPath);
int FindPath(const int nStartX, const int nStartY,
             const int nTargetX, const int nTargetY,
             const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
             int* pOutBuffer, const int nOutBufferSize);