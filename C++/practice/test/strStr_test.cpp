//
// Created by chiliu on 1/11/18.
//
#include <iostream>
#include "strStr.h"
#include "Solution.h"
using namespace std;

int main() {

//test of strStr
    string source("abcdsv");
    string target("dsv");
    int position = strStr(source.c_str(), target.c_str());
    cout << "Position_fun_string is : " << position << endl;
    Solution solution;
    int position0 = solution.strStr(source, target);
    cout << "Position_class_fun_string is : " << position0 << endl;

    //test of ["","dsv"]
    const char *source1 = "";
    const char *target1 = "dsv";
    int position2 = strStr(source1, target1);
    cout << "Position_fun_\"\" is : " << position2 << endl;
    int position3 = solution.strStr(source1, target1);
    cout << "Position_class_fun_\"\" is : " << position3 << endl;

    //test of [NULL,"dsv"]
    const char *source2 = nullptr;
    const char *target2 = "dsv";
    int position4 = strStr(source2, target2);
    cout << "Position_fun_NULL is : " << position4 << endl;
    int position5 = solution.strStr(source2, target2);
    cout << "Position_class_fun_NULL is : " << position5 << endl;
//test of strStr

    return 0;
}