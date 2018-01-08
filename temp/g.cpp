#include <iostream>
#include <opencv2/opencv.hpp>
using namespace cv;
int main()
{
    Mat mat(100, 100, CV_8UC4);
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 100; j++)
        {
            mat.at<Vec4b>(i, j)[0] = 255;
            mat.at<Vec4b>(i, j)[1] = 0;
            mat.at<Vec4b>(i, j)[2] = 0;
            mat.at<Vec4b>(i, j)[3] = 80;            
        }
    imwrite("x.png", mat);
}