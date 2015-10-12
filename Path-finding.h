#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <future>



bool fieldOK(const int index, const int nMapWidth, const int nMapHeight);

int readBestPath(int *bestPathCost);

void writeBestPath(int value, int *bestPathCost);

void recursive( const int index,
                          const int targetIndex, const int nMapWidth,
                          const int nMapHeight ,std::vector<int> currentPath,  std::promise<std::vector<int>> * _result  );


int FindPath(const int nStartX, const int nStartY,
             const int nTargetX, const int nTargetY,
             const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
             int* pOutBuffer, const int nOutBufferSize);