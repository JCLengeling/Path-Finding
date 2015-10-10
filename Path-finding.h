#include <iostream>
#include <vector>

bool fieldOK(const int index, const int nMapWidth, const int nMapHeight, const unsigned char* pMap);
std::vector<int> iterate( int *bestPathCost, const int index,
                          const int targetIndex, const int nMapWidth,
                          const int nMapHeight ,std::vector<int> currentPath, const unsigned char* pMap );
int FindPath(const int nStartX, const int nStartY,
             const int nTargetX, const int nTargetY,
             const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
             int* pOutBuffer, const int nOutBufferSize);