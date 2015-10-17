#include "Path-finding.h"
using namespace std;

struct Option{
    int distance;
    int index;
    int lastIndex;
    Option(int distance, int index, int lastIndex){this->distance=distance, this->index=index; this->lastIndex=lastIndex;}

    bool operator <(const Option& i) const
    {
        return distance < i.distance;
    }
    bool operator >(const Option& i) const
    {
        return distance > i.distance;
    }
};

int distanceBetweenIndex(const int indexA, const int indexB, const int width){

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

int indexCalculate(const int currrentX, const int currentY, const int width){
    return currrentX + width * currentY;
}


int FindPath(const int nStartX, const int nStartY,
             const int nTargetX, const int nTargetY,
             const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
             int* pOutBuffer, const int nOutBufferSize){

    const int targetIndex = indexCalculate(nTargetX, nTargetY, nMapWidth);
    const int currentIndex = indexCalculate(nStartX,nStartY, nMapWidth) ;

    std::priority_queue<Option, std::vector<Option>, std::greater<Option> > heap;
    std::vector<Option>  processed (nMapHeight*nMapWidth, Option(-1,-2,-1));

    processed.at(currentIndex) = Option{-1,-3,currentIndex};

    if (currentIndex % nMapWidth == 0){
        if ( pMap[currentIndex - nMapWidth]==1){
            heap.push(Option(distanceBetweenIndex(currentIndex - nMapWidth, targetIndex,nMapWidth), currentIndex-nMapWidth, currentIndex));
        }
        if (  pMap[currentIndex + nMapWidth]==1){
            heap.push(Option(distanceBetweenIndex(currentIndex + nMapWidth, targetIndex,nMapWidth), currentIndex+nMapWidth, currentIndex));
        }
        if ( pMap[currentIndex +1]==1){
            heap.push(Option(distanceBetweenIndex(currentIndex +1, targetIndex,nMapWidth), currentIndex +1, currentIndex));
        }
    }else if (currentIndex % nMapWidth == nMapWidth){
        if ( pMap[currentIndex - nMapWidth]==1){
            heap.push(Option(distanceBetweenIndex(currentIndex - nMapWidth, targetIndex,nMapWidth), currentIndex-nMapWidth, currentIndex));
        }
        if (  pMap[currentIndex + nMapWidth]==1){
            heap.push(Option(distanceBetweenIndex(currentIndex + nMapWidth, targetIndex,nMapWidth), currentIndex+nMapWidth, currentIndex));
        }

        if ( pMap[currentIndex -1]==1){
            heap.push(Option(distanceBetweenIndex(currentIndex -1, targetIndex,nMapWidth), currentIndex -1, currentIndex));
        }
    }else {
        if ( pMap[currentIndex - nMapWidth]==1){
            heap.push(Option(distanceBetweenIndex(currentIndex - nMapWidth, targetIndex,nMapWidth), currentIndex-nMapWidth, currentIndex));
        }
        if (  pMap[currentIndex + nMapWidth]==1){
            heap.push(Option(distanceBetweenIndex(currentIndex + nMapWidth, targetIndex,nMapWidth), currentIndex+nMapWidth, currentIndex));
        }

        if ( pMap[currentIndex -1]==1) {
            heap.push(Option(distanceBetweenIndex(currentIndex - 1, targetIndex,nMapWidth), currentIndex - 1, currentIndex));
        }
        if ( pMap[currentIndex +1] ==1) {
            heap.push(Option(distanceBetweenIndex(currentIndex + 1, targetIndex,nMapWidth), currentIndex + 1, currentIndex));
        }
    }

    Option solution ={-1,-1,-1}, current={-1,-1,-1};


    if(heap.size()>0){
    current = heap.top();

    processed.at(current.index) = current;
    heap.pop();
    }

    while(heap.size()>=0) {
        if(current.index == targetIndex){
            solution = current;
            break;
        }
        //current.index -nMapWidth top
        //current.index + nMapWidth bot
        //current.index + 1 right
        //current.index -1 left
        if (current.index % nMapWidth == 0){
            if ( pMap[current.index - nMapWidth] == 1&&  processed.at(current.index -nMapWidth).index == -2 ){
                heap.push(Option(distanceBetweenIndex(current.index - nMapWidth, targetIndex,nMapWidth), current.index-nMapWidth, current.index));
            }
            if ( pMap[current.index +nMapWidth] ==1 &&processed.at(current.index + nMapWidth).index == -2 ){
                heap.push(Option(distanceBetweenIndex(current.index + nMapWidth, targetIndex,nMapWidth), current.index+nMapWidth, current.index));
            }
            if ( pMap[current.index+1]==1&&processed.at(current.index+1).index == -2 ){
                heap.push(Option(distanceBetweenIndex(current.index+1, targetIndex,nMapWidth), current.index+1, current.index));
            }
        }else if (current.index % nMapWidth == nMapWidth-1){
            if (pMap[current.index - nMapWidth]==1 &&processed.at(current.index -nMapWidth).index == -2  ){
                heap.push(Option(distanceBetweenIndex(current.index - nMapWidth, targetIndex,nMapWidth), current.index-nMapWidth, current.index));
            }
            if (pMap[current.index +nMapWidth]==1 &&processed.at(current.index + nMapWidth).index == -2  ){
                heap.push(Option(distanceBetweenIndex(current.index + nMapWidth, targetIndex,nMapWidth), current.index+nMapWidth, current.index));
            }
            if (pMap[current.index-1] ==1 &&processed.at(current.index-1).index == -2  ){
                heap.push(Option(distanceBetweenIndex(current.index-1, targetIndex,nMapWidth), current.index-1, current.index));
            }
        }else {
            if (pMap[current.index - nMapWidth]==1&&processed.at(current.index -nMapWidth).index == -2  ){
                heap.push(Option(distanceBetweenIndex(current.index - nMapWidth, targetIndex,nMapWidth), current.index-nMapWidth, current.index));
            }
            if (pMap[current.index +nMapWidth]==1&&processed.at(current.index + nMapWidth).index == -2  ){
                heap.push(Option(distanceBetweenIndex(current.index + nMapWidth, targetIndex,nMapWidth), current.index+nMapWidth, current.index));
            }
            if (pMap[current.index+1]==1&&processed.at(current.index+1).index == -2 ){
                heap.push(Option(distanceBetweenIndex(current.index+1, targetIndex,nMapWidth), current.index+1, current.index));
            }
            if ( pMap[current.index-1]==1&&processed.at(current.index-1).index == -2 ){
                heap.push(Option(distanceBetweenIndex(current.index-1, targetIndex,nMapWidth), current.index-1, current.index));
            }
        }

        if(heap.size()>0){
            current = heap.top();
            processed.at(current.index) = current;
            heap.pop();
        }else{
            break;
        }
    }


    vector<int> ret = {};
    if(solution.index == -1){
        return -1;
    }
    else{
        ret.push_back(solution.index);
        int lastIndex = solution.lastIndex;
        while (lastIndex!=currentIndex){
            ret.push_back(lastIndex);
            lastIndex= processed.at(lastIndex).lastIndex;
        }
    }



    if (ret.size() < nOutBufferSize){
    for (int i = 0; i < ret.size() ; i++) {
        pOutBuffer[ret.size()-i-1] = ret[i];
    }}

    return ret.size();

}


int main (){
    unsigned char pMap[] = {1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1};

    int pOutBuffer[12];
    cout << FindPath(0, 0, 1, 2, pMap, 4, 3, pOutBuffer, 12) << endl;

    unsigned char pMap2[] = {0, 0, 1, 0, 1, 1, 1, 0, 1};
    int pOutBuffer2[7];
   cout << FindPath(2, 0, 0, 2, pMap2, 3, 3, pOutBuffer2, 7) <<endl;


    unsigned char pMap3[] = {1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0,
                             1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1,
                             1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1,
                             1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1,
                             0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1,
                             1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1,
                             1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1,
                             0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1,
                             1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1,
                             1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1,
                             0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1,
                             1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1,
                             1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1,
                             0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1,
                             1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1,
                             1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0,
                             1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1,
                             1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1,
                             1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1,
                             0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1,
                             1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1,
                             1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1,
                             0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1,
                             1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1,
                             1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1,
                             0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1,
                             1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1,
                             1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1,
                             0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1,
                             1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,
                             1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0,
                             1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1,
                             1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1,
                             1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1,
                             0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1,
                             1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1,
                             1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1,
                             0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1,
                             1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1,
                             1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1,
                             0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1,
                             1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1,
                             1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1,
                             0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1,
                             1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1,
                             1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0,
                             1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1,
                             1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1,
                             1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1,
                             0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1,
                             1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1,
                             1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1,
                             0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1,
                             1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1,
                             1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1,
                             0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1,
                             1, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1,
                             1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1,
                             0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1,
                             1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1,};
    cout << sizeof(pMap3)<<endl;
    int pOutBuffer3[960*2];
    cout << FindPath(0, 0, 3, 479, pMap3, 4, 480, pOutBuffer3, 960*2) << endl;

}
