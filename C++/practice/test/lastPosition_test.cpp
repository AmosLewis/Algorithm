//
// Created by chiliu on 1/16/18.
//
#include <lastPosition.h>

int main(){
    vector<int> myvector ({1, 2, 2, 4, 5, 5});
    cout<<"The vector is [ ";
    for (int i =0; i < 6; i++){
//        myvector.push_back( x[i] );
        cout<<myvector[i]<<" ";
    }
    cout<<"]";
    int i =2;
    cout<<endl<<"Find "<<i<<endl;
    cout<<"The index is "<<lastPosition(myvector , i)<<endl;
}

