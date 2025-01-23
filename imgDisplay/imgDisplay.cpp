/*
Adit Shah and Jheel Kamdar
Jan 13th 2025
OpenCV Image Display
*/

#include <cstdio> // gives me printf
#include <cstring> // gives me strncpy
#include <opencv2/opencv.hpp> // openCV
 
int main(int argc, char *argv[]) {
    cv::Mat src;
    cv::Mat dst;
    char filename[256];
 
    // check for a command line argument
    if(argc < 2) {
        printf("usage: %s <image filename>\n", argv[0]); // argv[0] is the program name
        exit(-1);
    }
    strncpy(filename, argv[1], 255); // safe strcpy
    
    src = cv::imread(filename); // by default, returns image as 8-bit BGR image (if it's color), use IMREAD_UNCHANGED to keep the original data format
    
    if(src.data == NULL) { // no data, no image
        printf("error: unable to read image %s\n", filename);
        exit(-1);
    }
    
    cv::imshow(filename, src); // display the image
 
    // Modify the image
    src.copyTo(dst); // copy the image to another image
 
    // Use the at<> method to modify pixel values
    for(int i = 0; i < dst.rows; i++) {
        for(int j = 0; j < dst.cols; j++) {
            // Swap the red and blue values
            unsigned char tmp = dst.at<cv::Vec3b>(i, j)[0];
            dst.at<cv::Vec3b>(i, j)[0] = dst.at<cv::Vec3b>(i, j)[2];
            dst.at<cv::Vec3b>(i, j)[2] = tmp;
        }
    }
 
    // Use the ptr<> method to modify pixel values
    for(int i = 0; i < dst.rows; i++) {
        cv::Vec3b *ptr = dst.ptr<cv::Vec3b>(i);
        for(int j = 0; j < dst.cols; j++) {
            // Swap the red and blue values
            unsigned char tmp = ptr[j][0];
            ptr[j][0] = ptr[j][2];
            ptr[j][2] = tmp;
        }
    }
 
    cv::imshow("Modified Image", dst); // display the modified image
 
    cv::waitKey(0); // blocking call with an argument of 0
 
    printf("Terminating\n");
 
    return 0;
}
