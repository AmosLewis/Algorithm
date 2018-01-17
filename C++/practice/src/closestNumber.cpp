//
// Created by chiliu on 1/16/18.
//

#include "closestNumber.h"

//Given a target number and an integer array A sorted in ascending order,
//find the index i in A such that A[i] is closest to the given target.
//Return -1 if there is no element in the array.

//Given [1, 2, 3] and target = 2, return 1.
//Given [1, 4, 6] and target = 3, return 1.
//Given [1, 4, 6] and target = 5, return 1 or 2.
//Given [1, 3, 3, 4] and target = 2, return 0 or 1 or 2.

/*
 * @param A: an integer array sorted in ascending order
 * @param target: An integer
 * @return: an integer
 */

int closestNumber (vector<int> &A, int target) {
    // 0 bounds checking;
    if (A.size() == 0){
        return -1;
    }
    // 1 start
    int start = 0, end = A.size()-1;
    // 2 iterative every word in vector
    while (start +1 < end) {
        int mid = start + (end - start) / 2;
        if (A[mid] == target) {
            return mid;
        }
        else if (A[mid] > target) {
            end = mid;
        } else {
            start = mid;
        }
    }
    // 3 compare and return
    if (A[end] - target > target - A[start]){
        return start;
    } else {
        return end;
    }
}
