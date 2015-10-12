#include "Path-finding.h"
using namespace std;


int *bestcost;
const unsigned char* map;
int width;
int height;
int targetIndex;


struct Option{
    int distance;
    int index;
    Option(int distance, int index){this->distance=distance, this->index=index;}

    bool operator <(const Option& i) const
    {
        return distance < i.distance;
    }
    bool operator >(const Option& i) const
    {
        return distance > i.distance;
    }
};

int distanceBetweenIndex(const int indexA, const int indexB){

    int aX = indexA % width;
    int bX = indexB % width;

    int aY = 0;
    int bY = 0;

    if(indexA > width || indexA <0){
        aY = indexA/width;
    }
    if(indexB > width || indexB <0){
        bY = indexB/width;
    }

    int deltaX = abs(aX-bX);
    int deltaY = abs(aY-bY);
    return deltaX + deltaY;
}

int indexCalculate(const int currrentX, const int currentY){
    return currrentX + width * currentY;
}


vector<int> iterate(   const int index ,vector<int> currentPath){

    if (bestcost == new int(-1) | currentPath.size() <*bestcost ){

        currentPath.push_back(index);

        std::priority_queue<Option, std::vector<Option>, std::greater<Option> > heap;

        if (index % width == 0){
            if (index - width == targetIndex){
                currentPath.push_back(index - width);
                *bestcost = currentPath.size()-1;
                return currentPath;
            }else if (index + width == targetIndex){
                currentPath.push_back(index + width);
                *bestcost = currentPath.size()-1;
                return currentPath;
            }else if (index+1 == targetIndex){
                currentPath.push_back(index+1);
                *bestcost = currentPath.size()-1;
                return currentPath;
            }

            if (index -width != currentPath[currentPath.size()-2] && map[index - width] == 1){
                heap.push(Option(distanceBetweenIndex(index - width, targetIndex), index-width));
            }
            if (index + width != currentPath[currentPath.size()-2] && map[index +width] ==1){
                heap.push(Option(distanceBetweenIndex(index + width, targetIndex), index+width));
            }
            if (index+1 != currentPath[currentPath.size()-2] && map[index+1]==1){
                heap.push(Option(distanceBetweenIndex(index+1, targetIndex), index+1));
            }


        }else if (index % width == width-1){
            if (index - width == targetIndex){
                currentPath.push_back(index - width);
                *bestcost = currentPath.size()-1;
                return currentPath;
            }else if (index + width == targetIndex){
                currentPath.push_back(index + width);
                *bestcost = currentPath.size()-1;
                return currentPath;
            }else if (index-1 == targetIndex){
                currentPath.push_back(index-1);
                *bestcost = currentPath.size()-1;
                return currentPath;
            }

            if (index -width != currentPath[currentPath.size()-2] && map[index - width]==1){
                heap.push(Option(distanceBetweenIndex(index - width, targetIndex), index-width));
            }
            if (index + width != currentPath[currentPath.size()-2] && map[index +width]==1){
                heap.push(Option(distanceBetweenIndex(index + width, targetIndex), index+width));
            }

            if (index-1 != currentPath[currentPath.size()-2] && map[index-1] ==1){
                heap.push(Option(distanceBetweenIndex(index-1, targetIndex), index-1));
            }

        }else {
            if (index - width == targetIndex){
                currentPath.push_back(index - width);
                *bestcost = currentPath.size()-1;
                return currentPath;
            }else if (index + width == targetIndex){
                currentPath.push_back(index + width);
                *bestcost = currentPath.size()-1;
                return currentPath;
            }else if (index-1 == targetIndex){
                currentPath.push_back(index-1);
                *bestcost = currentPath.size()-1;
                return currentPath;
            }else if (index+1 == targetIndex){
                currentPath.push_back(index+1);
                *bestcost = currentPath.size()-1;
                return currentPath;
            }

            if (index -width != currentPath[currentPath.size()-2] && map[index - width]==1){
                heap.push(Option(distanceBetweenIndex(index - width, targetIndex), index-width));
            }
            if (index + width != currentPath[currentPath.size()-2] && map[index +width]==1){
                heap.push(Option(distanceBetweenIndex(index + width, targetIndex), index+width));
            }
            if (index+1 != currentPath[currentPath.size()-2] && map[index+1]==1){
                heap.push(Option(distanceBetweenIndex(index+1, targetIndex), index+1));
            }
            if (index-1 != currentPath[currentPath.size()-2] && map[index-1]==1){
                heap.push(Option(distanceBetweenIndex(index-1, targetIndex), index-1));
            }
        }
        vector<int> ret = {} ;
        while(heap.size()>0) {
            vector<int> tmp =  iterate( heap.top().index ,currentPath );
            if (!tmp.empty() && (ret.empty()||ret.size()> tmp.size() )){
                ret.swap(tmp);
            }
           heap.pop();
        }
        return ret;
    }
    else {
        return  vector<int> ();
    }
}


int FindPath(const int nStartX, const int nStartY,
             const int nTargetX, const int nTargetY,
             const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
             int* pOutBuffer, const int nOutBufferSize){


    map = pMap;
    width = nMapWidth;
    height= nMapHeight;
    bestcost = new int(-1);
    targetIndex = indexCalculate(nTargetX, nTargetY);
    const int currentIndex = indexCalculate(nStartX,nStartY) ;

    std::priority_queue<Option, std::vector<Option>, std::greater<Option> > heap;


    if (currentIndex % nMapWidth == 0){
        if ( map[currentIndex - nMapWidth]==1){
            heap.push(Option(distanceBetweenIndex(currentIndex - nMapWidth, targetIndex), currentIndex-nMapWidth));
        }
        if (  map[currentIndex + nMapWidth]==1){
            heap.push(Option(distanceBetweenIndex(currentIndex + nMapWidth, targetIndex), currentIndex+nMapWidth));
        }
        if ( map[currentIndex +1]==1){
            heap.push(Option(distanceBetweenIndex(currentIndex +1, targetIndex), currentIndex +1));
        }
    }else if (currentIndex % nMapWidth == nMapWidth){
        if ( map[currentIndex - nMapWidth]==1){
            heap.push(Option(distanceBetweenIndex(currentIndex - nMapWidth, targetIndex), currentIndex-nMapWidth));
        }
        if (  map[currentIndex + nMapWidth]==1){
            heap.push(Option(distanceBetweenIndex(currentIndex + nMapWidth, targetIndex), currentIndex+nMapWidth));
        }

        if ( map[currentIndex -1]==1){
            heap.push(Option(distanceBetweenIndex(currentIndex -1, targetIndex), currentIndex -1));
        }
    }else {
        if ( map[currentIndex - nMapWidth]==1){
            heap.push(Option(distanceBetweenIndex(currentIndex - nMapWidth, targetIndex), currentIndex-nMapWidth));
        }
        if (  map[currentIndex + nMapWidth]==1){
            heap.push(Option(distanceBetweenIndex(currentIndex + nMapWidth, targetIndex), currentIndex+nMapWidth));
        }

        if ( map[currentIndex -1]==1) {
            heap.push(Option(distanceBetweenIndex(currentIndex - 1, targetIndex), currentIndex - 1));
        }
        if ( map[currentIndex +1] ==1) {
            heap.push(Option(distanceBetweenIndex(currentIndex + 1, targetIndex), currentIndex + 1));
        }
    }

    vector<int> ret = {} ;
    while(heap.size()>0) {
        vector<int> tmp =  iterate( heap.top().index  ,vector<int> {currentIndex} );
        if (!tmp.empty() && (ret.empty()||ret.size()> tmp.size() )){
            ret.swap(tmp);
        }
        heap.pop();
    }

    if (ret.size() < nOutBufferSize){
    for (int i = 1; i < ret.size() ; ++i) {
        pOutBuffer[i-1] = ret[i];
    }}

    return *bestcost;

}

/*
int main (){
    unsigned char pMap[] = {1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1};
    int pOutBuffer[12];
    cout << FindPath(0, 0, 1, 2, pMap, 4, 3, pOutBuffer, 12) << endl;

    unsigned char pMap2[] = {0, 0, 1, 0, 1, 1, 1, 0, 1};
    int pOutBuffer2[7];
   cout << FindPath(2, 0, 0, 2, pMap2, 3, 3, pOutBuffer2, 7) <<endl;

}
 */


