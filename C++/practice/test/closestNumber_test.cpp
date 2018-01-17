//
// Created by chiliu on 1/16/18.
//
#include "closestNumber.h"

using namespace std;

int main() {
    vector<int> myvector;
    cout<<"The vector is [ ";
    for (int i =1; i < 5; i++){
        myvector.push_back( i );
        cout<<i<<" ";
    }
    cout<<"]";
    int i =2;
    cout<<endl<<"Find "<<i<<endl;
    cout<<"The index is "<<closestNumber(myvector , 2)<<endl;
}