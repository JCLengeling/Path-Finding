#include "Path-finding.h"
using namespace std;


bool fieldOK(const int index, const int nMapWidth, const int nMapHeight, const unsigned char* pMap){

    if (index <0 || index >= nMapWidth * nMapHeight){
        return false;
    }
    if (pMap[index] == 0){
        return false;
    }
    if (pMap[index] == 1){
        return true;
    }
}

vector<int> iterate( int *bestPathCost,  const int index, const int targetIndex, const int nMapWidth, const int nMapHeight ,vector<int> currentPath, const unsigned char* pMap ){
    //cout <<"besPathCost: " <<*bestPathCost << endl;
    if (bestPathCost == new int(-1) | currentPath.size() <*bestPathCost ){

        int lastIndex = currentPath[currentPath.size()-1];

        currentPath.push_back(index);

        int up  = index - nMapWidth, down = index + nMapWidth, left, right;


        if (index % nMapWidth == 0){
            left = -1;
            right = index +1;
        }else if (index % nMapWidth == nMapWidth-1){
            left = index -1;
            right = -1;
        }else {
            left = index -1;
            right = index + 1;
        }


        if (up == targetIndex){
            currentPath.push_back(up);
            *bestPathCost = currentPath.size()-1;
            return currentPath;
        }else if (down == targetIndex){
            currentPath.push_back(down);
            *bestPathCost = currentPath.size()-1;
            return currentPath;
        }else if (left == targetIndex){
            currentPath.push_back(left);
            *bestPathCost = currentPath.size()-1;
            return currentPath;
        }else if (right == targetIndex){
            currentPath.push_back(right);
            *bestPathCost = currentPath.size()-1;
            return currentPath;
        }

        vector<int> ret = {} ;

      //  cout << "index in iterate " << index << endl;
      //  cout << "lastindex " << lastIndex << endl;
      //  cout << "up " << up << " down " << down << " left " << left << " right " << right <<  endl << endl;
      //  cin.get();

        if (up != lastIndex && fieldOK(up, nMapWidth, nMapHeight, pMap)){
            vector<int> upReturn =  iterate( bestPathCost, up, targetIndex, nMapWidth, nMapHeight ,currentPath, pMap );
            if (!upReturn.empty() && (ret.empty()||ret.size()> upReturn.size() )){
                vector<int>::iterator it;
                it=upReturn.begin();
                ret.assign (it, upReturn.end());
            }
        }
        if(down != lastIndex && fieldOK(down, nMapWidth, nMapHeight, pMap)){
            vector<int> downReturn =  iterate( bestPathCost, down, targetIndex, nMapWidth, nMapHeight ,currentPath, pMap );
            if (!downReturn.empty() && (ret.empty()|| ret.size()> downReturn.size())){
                vector<int>::iterator it;
                it=downReturn.begin();
                ret.assign ( it, downReturn.end());
            }
        }
        if(left != lastIndex && fieldOK(left, nMapWidth, nMapHeight, pMap)){

            vector<int> leftReturn =  iterate( bestPathCost, left, targetIndex, nMapWidth, nMapHeight ,currentPath, pMap );
            if (!leftReturn.empty() && (ret.empty()||ret.size()> leftReturn.size())){
                vector<int>::iterator it;
                it=leftReturn.begin();
                ret.assign (it, leftReturn.end());
            }
        }
        if(right != lastIndex && fieldOK(right, nMapWidth, nMapHeight, pMap)){
            vector<int> rightReturn =  iterate( bestPathCost, right, targetIndex, nMapWidth, nMapHeight ,currentPath, pMap );
            if (!rightReturn.empty() && (ret.empty()||ret.size()> rightReturn.size())){
                vector<int>::iterator it;
                it=rightReturn.begin();
                ret.assign (it, rightReturn.end());
            }
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

    const int currentIndex = nStartX + nMapWidth * nStartY, targetIndex = nTargetX +nMapWidth * nTargetY;
    int *bestPathCost = new int(-1);





   // cout << "currentIndex: " << currentIndex << endl;
   // cout << "targetIndex: " << targetIndex << endl;

    // 4 cases
    // up down left right

    int up  = currentIndex - nMapWidth, down = currentIndex + nMapWidth, left, right;


    if (currentIndex % nMapWidth == 0){
        left = -1;
        right = currentIndex +1;
    }else if (currentIndex % nMapWidth == nMapWidth){
        left = currentIndex -1;
        right = -1;
    }else {
        left = currentIndex -1;
        right = currentIndex + 1;
    }


    vector<int> ret = {} ;
    if (fieldOK(up, nMapWidth, nMapHeight, pMap)){
        //cout <<"Initial UP " << endl;
        vector<int> tmp = {currentIndex};
        vector<int> upReturn =  iterate( bestPathCost, up, targetIndex, nMapWidth, nMapHeight , tmp, pMap );
        if (!upReturn.empty() && (ret.empty()|| ret.size()> upReturn.size())){
            vector<int>::iterator it;
            it=upReturn.begin();
            ret.assign(it, upReturn.end());
        }
    }
    if(fieldOK(down, nMapWidth, nMapHeight, pMap)){
        //cout <<"Initial DOWN " << endl;
        vector<int> tmp = {currentIndex};
        vector<int> downReturn =  iterate( bestPathCost, down, targetIndex, nMapWidth, nMapHeight , tmp, pMap );
        if (!downReturn.empty() && (ret.empty()||ret.size()> downReturn.size())){
            vector<int>::iterator it;
            it=downReturn.begin();
            ret.assign (it, downReturn.end());
        }
    }
    if(fieldOK(left, nMapWidth, nMapHeight, pMap)){
        //cout <<"Initial LEFT " << endl;
        vector<int> tmp = {currentIndex};
        vector<int> leftReturn =  iterate( bestPathCost, left, targetIndex, nMapWidth, nMapHeight ,tmp, pMap );
        if (!leftReturn.empty() && (ret.empty()||ret.size()> leftReturn.size())){
            vector<int>::iterator it;
            it=leftReturn.begin();
            ret.assign (it, leftReturn.end());
        }
    }
    if(fieldOK(right, nMapWidth, nMapHeight, pMap)){
        //cout <<"Initial RIGHT " << endl;
        vector<int> tmp = {currentIndex};
        vector<int> rightReturn =  iterate( bestPathCost, right, targetIndex, nMapWidth, nMapHeight ,tmp, pMap );
        if (!rightReturn.empty() && (ret.empty()||ret.size()> rightReturn.size())){
            vector<int>::iterator it;
            it=rightReturn.begin();
            ret.assign (it, rightReturn.end());
        }
    }

    for (int i = 1; i < ret.size() ; ++i) {
        pOutBuffer[i-1] = ret[i];
    }

    //cout << endl;
    return *bestPathCost;

}

int main (){
    unsigned char pMap[] = {1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1};
    int pOutBuffer[12];
    cout << FindPath(0, 0, 1, 2, pMap, 4, 3, pOutBuffer, 12) << endl;

    unsigned char pMap2[] = {0, 0, 1, 0, 1, 1, 1, 0, 1};
    int pOutBuffer2[7];
   cout << FindPath(2, 0, 0, 2, pMap2, 3, 3, pOutBuffer2, 7) <<endl;


    // cout << "Press enter to continue ...";
   // cin.get();
}