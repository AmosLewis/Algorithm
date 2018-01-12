//
// Created by chiliu on 1/11/18.
//
#include "strStr.h"
using namespace std;


// For a given source string and a target string,
// you should output the first index(from 0) in source string.
// If target does not exist in source, just return -1

// implementation1 of C++ std::strstr
int strStr (const char *source, const char *target){
    if (source == nullptr || target ==nullptr || source[0] == '\0' || target[0] == '\0'){
        return -1;
    }

    for (int i = 0; i <= strlen(source) - strlen(target)+1; i++){
        int j = 0;
        for (j = 0;j < strlen(target); j++){
            if (source[i+j] != target[j]){
                break;
            }
        }
        if (j == strlen(target) ){
            return i;
        }
    }
    return -1;
}

// implementation2 of C++ std::strstr

//int strStr (const string& source, const string& target){
//    int n_source = source.length(), n_target = target.length();
//
//    if (source.empty() || target.empty()) {
////    if (n_target == 0 || n_source == 0) { //same function with up line
//        return -1;
//    }
//
//    if (source == nullptr || target == nullptr) {
////    if (n_target == 0 || n_source == 0) { //same function with up line
//        return -1;
//    }
//
//    for (int i = 0; i <= n_source - n_target; i++){
//        for (int j = 0; j <= n_target; j++){
//            if (source[i + j] != target[j]){
//                break;
//            }
//            if (j == n_target-1) {
//                return i;
//            }
//        }
//    }
//
//    return -1;
//}



