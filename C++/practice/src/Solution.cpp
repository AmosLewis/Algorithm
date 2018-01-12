//
// Created by chiliu on 1/11/18.
//

#include "Solution.h"

// implementation of C++ std::strstr
// For a given source string and a target string,
// you should output the first index(from 0) in source string.
// If target does not exist in source, just return -1

int Solution::strStr(std::string source, std::string target) {
    if (source.empty() || target.empty()) {
        return -1;
    }

    auto n_source = static_cast<int>(source.length()), n_target = static_cast<int>(target.length());
    for (int i = 0; i <= n_source - n_target; i++){
        for (int j = 0; j <= n_target; j++){
//            if (source[i + j] != target[j]){
              if (source.at(i + j) != target.at(j)){
                break;
            }
            if (j == n_target-1) {
                return i;
            }
        }
    }
    return -1;
}

int Solution::strStr (const char *source, const char *target){
    if (source == nullptr || target == nullptr || source[0] == '\0' || target[0] == '\0'){
        return -1;
    }
    strStr(std::string(source),std::string(target));
}