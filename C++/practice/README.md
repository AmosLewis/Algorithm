This is my C++ algorithm practice writen in Clion.

If you want to test any function, you should first modified CMakeLists.txt.
You should choose right add_executable line,and comment out other add_executable()line.

For example,if you want to test function strStr, you should choose the following line.

add_executable(practice_1 test/strStr_test.cpp include/strStr.h src/strStr.cpp src/Solution.cpp include/Solution.h)

