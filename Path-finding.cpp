#include "Path-finding.h"
using namespace std;

std::mutex mtx;
int *bestPathCost = new int(-1);
const unsigned char* map;

bool fieldOK(const int index, const int nMapWidth, const int nMapHeight){
    if (index <0 || index >= nMapWidth * nMapHeight){
        return false;
    }
    if (map[index] == 0){
        return false;
    }
    if (map[index] == 1){
        return true;
    }
}


vector <int> pointerToVector( vector<int>* p){
    vector<int> v = {};
    for (int i = 0; i < p->size() ; ++i) {
        v.push_back(p->at(i));
    }
    return v;
}

int readBestPath(){
    int value;
    mtx.lock();
    value = *bestPathCost;
    mtx.unlock();
    return value;
}

void writeBestPath(int value){
    mtx.lock();
    *bestPathCost = value;
    mtx.unlock();
}

void recursive(int index,  int targetIndex, int nMapWidth, int nMapHeight ,vector<int> currentPath, std::promise<vector<int>> * _result ){
    if (readBestPath() == -1 | currentPath.size() <readBestPath() ){
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
            writeBestPath(currentPath.size()-1);
            vector<int> res(currentPath);
            _result->set_value(res);
        }else if (down == targetIndex){
            currentPath.push_back(down);
            writeBestPath(currentPath.size()-1);
            vector<int> res(currentPath);
            _result->set_value(res);
        }else if (left == targetIndex){
            currentPath.push_back(left);
            writeBestPath(currentPath.size()-1);
            vector<int> res(currentPath);
            _result->set_value(res);
        }else if (right == targetIndex){
            currentPath.push_back(right);
            writeBestPath(currentPath.size()-1);
            vector<int> res(currentPath);
            _result->set_value(res);
        }
        vector<int> ret = {} ;
        vector<int> upReturn, downReturn, leftReturn, rightReturn;
        if (up != lastIndex && fieldOK(up, nMapWidth, nMapHeight)){

            promise<vector<int>> *_promise;
            future<vector<int>> _future = _promise->get_future();
            thread t (&recursive, up, targetIndex, nMapWidth, nMapHeight , currentPath, _promise);
            upReturn = _future.get();
            t.join();

            //vector<int> tmp;
           // recursive(  up, targetIndex, nMapWidth, nMapHeight ,currentPath, tmp );
           // upReturn = tmp;
        }
        if(down != lastIndex && fieldOK(down, nMapWidth, nMapHeight)){

            promise<vector<int>> *_promise;
            future<vector<int>> _future = _promise->get_future();
            thread t (&recursive, down, targetIndex, nMapWidth, nMapHeight , currentPath, _promise);
            downReturn = _future.get();
            t.join();

            //vector<int> tmp;
            //recursive ( down, targetIndex, nMapWidth, nMapHeight ,currentPath, tmp );
            //downReturn = tmp;
        }
        if(left != lastIndex && fieldOK(left, nMapWidth, nMapHeight)){

            promise<vector<int>> *_promise;
            future<vector<int>> _future = _promise->get_future();
            thread t (&recursive, left, targetIndex, nMapWidth, nMapHeight , currentPath, _promise);
            leftReturn = _future.get();
            t.join();

            //vector<int> tmp;
            //recursive(  left, targetIndex, nMapWidth, nMapHeight ,currentPath, tmp );
            //leftReturn = tmp;
        }
        if(right != lastIndex && fieldOK(right, nMapWidth, nMapHeight)){
            promise<vector<int>> *_promise;
            future<vector<int>> _future = _promise->get_future();
            thread t (&recursive, right, targetIndex, nMapWidth, nMapHeight , currentPath, _promise);
            rightReturn = _future.get();
            t.join();

            //vector<int> tmp;
            //recursive(  right, targetIndex, nMapWidth, nMapHeight ,currentPath, tmp);
            //rightReturn = tmp;
        }

        //barrier
        if (!upReturn.empty() && (ret.empty()||ret.size()> upReturn.size() )){
            ret.swap(upReturn);
        }
        if (!downReturn.empty() && (ret.empty()|| ret.size()> downReturn.size())){
            ret.swap(downReturn);
        }
        if (!leftReturn.empty() && (ret.empty()||ret.size()> leftReturn.size())){
            ret.swap ( leftReturn);
        }
        if (!rightReturn.empty() && (ret.empty()||ret.size()> rightReturn.size())){
            ret.swap (rightReturn);
        }
        _result->set_value( ret);
    }
    else {
        vector<int> tmp ={};
        _result->set_value(tmp);
    }
}


int FindPath(const int nStartX, const int nStartY,
             const int nTargetX, const int nTargetY,
             const unsigned char* pMap, const int nMapWidth, const int nMapHeight,
             int* pOutBuffer, const int nOutBufferSize){

    const int currentIndex = nStartX + nMapWidth * nStartY, targetIndex = nTargetX +nMapWidth * nTargetY;
    writeBestPath(-1);
    map = pMap;
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
    if (fieldOK(up, nMapWidth, nMapHeight)){
        vector<int> tmp = {currentIndex};



        promise<vector<int>> *_promise;
        future<vector<int>> _future = _promise->get_future();
        thread t (&recursive, up, targetIndex, nMapWidth, nMapHeight , tmp, _promise);
        vector<int> upReturn = _future.get();
        t.join();

        if (!upReturn.empty() && (ret.empty()|| ret.size()> upReturn.size())){
                 vector<int>::iterator it;
                 it=upReturn.begin();
                 ret.assign(it, upReturn.end());
            }




       // vector<int>  tmp2;
       // recursive( up, targetIndex, nMapWidth, nMapHeight , tmp, tmp2 );
       // vector<int> upReturn (tmp2);
       // if (!upReturn.empty() && (ret.empty()|| ret.size()> upReturn.size())){
       //     vector<int>::iterator it;
       //     it=upReturn.begin();
       //     ret.assign(it, upReturn.end());
       // }
    }
    if(fieldOK(down, nMapWidth, nMapHeight)){
        vector<int> tmp = {currentIndex};


        promise<vector<int>> *_promise;
        future<vector<int>> _future = _promise->get_future();
        thread t (&recursive, down, targetIndex, nMapWidth, nMapHeight , tmp, _promise);
        vector<int> downReturn = _future.get();
        t.join();

        if (!downReturn.empty() && (ret.empty()|| ret.size()> downReturn.size())){
            vector<int>::iterator it;
            it=downReturn.begin();
            ret.assign(it, downReturn.end());
        }



        /*vector<int> tmp2;
        recursive(  down, targetIndex, nMapWidth, nMapHeight , tmp, tmp2 );
        vector<int> downReturn (tmp2);
        if (!downReturn.empty() && (ret.empty()||ret.size()> downReturn.size())){
            vector<int>::iterator it;
            it=downReturn.begin();
            ret.assign (it, downReturn.end());
        }
         */
    }
    if(fieldOK(left, nMapWidth, nMapHeight)){
        vector<int> tmp = {currentIndex};


        promise<vector<int>> *_promise;
        future<vector<int>> _future = _promise->get_future();
        thread t (&recursive, left, targetIndex, nMapWidth, nMapHeight , tmp, _promise);
        vector<int> leftReturn = _future.get();
        t.join();




        //vector<int> tmp2;
        //recursive(  left, targetIndex, nMapWidth, nMapHeight ,tmp, tmp2 );
        //vector<int> leftReturn (tmp2);


        if (!leftReturn.empty() && (ret.empty()||ret.size()> leftReturn.size())){
            vector<int>::iterator it;
            it=leftReturn.begin();
            ret.assign (it, leftReturn.end());
        }


    }
    if(fieldOK(right, nMapWidth, nMapHeight)){
        vector<int> tmp = {currentIndex};

        promise<vector<int>> *_promise;
        future<vector<int>> _future = _promise->get_future();
        thread t (&recursive, right, targetIndex, nMapWidth, nMapHeight , tmp, _promise);
        vector<int> rightReturn = _future.get();
        t.join();

        //vector<int> tmp2;
        //recursive(  right, targetIndex, nMapWidth, nMapHeight ,tmp, tmp2 );
        //vector<int> rightReturn (tmp2);



        if (!rightReturn.empty() && (ret.empty()||ret.size()> rightReturn.size())){
            vector<int>::iterator it;
            it=rightReturn.begin();
            ret.assign (it, rightReturn.end());
        }
    }
    if (nOutBufferSize <= ret.size()){
    for (int i = 1; i < ret.size() ; ++i) {
        pOutBuffer[i-1] = ret[i];
    }}
    return readBestPath();
}

int main (){
    unsigned char pMap[] = {1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 1};
    int pOutBuffer[12];
    cout << FindPath(0, 0, 1, 2, pMap, 4, 3, pOutBuffer, 12) << endl;

    unsigned char pMap2[] = {0, 0, 1, 0, 1, 1, 1, 0, 1};
    int pOutBuffer2[7];
   cout << FindPath(2, 0, 0, 2, pMap2, 3, 3, pOutBuffer2, 7) <<endl;
}