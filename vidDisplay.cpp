/*
Adit Shah & Jheel Kamdar
PRCV CS5330
Date: Jan 15 2025
*/

#include "filter.h"
#include <opencv2/opencv.hpp>
#include <iostream>

int main(int argc, char *argv[]) {
    cv::VideoCapture capdev(0);

    if (!capdev.isOpened()) {
        std::cerr << "Unable to open video device" << std::endl;
        return -1;
    }

    cv::Size refS((int)capdev.get(cv::CAP_PROP_FRAME_WIDTH),
                  (int)capdev.get(cv::CAP_PROP_FRAME_HEIGHT));
    std::cout << "Expected size: " << refS.width << " x " << refS.height << std::endl;

    cv::namedWindow("Video", 1);
    cv::Mat frame, grey, processedFrame, sobelXFrame, sobelYFrame, sobelXAbs, sobelYAbs, gradientMagnitude;

    // adding variables for face detection 
    bool faceDetectionEnabled = false;
    std::vector<cv::Rect> faces;

    char lastKey = ' ';

    for (;;) {
        capdev >> frame;
        if (frame.empty()) {
            std::cerr << "Frame is empty" << std::endl;
            break;
        }

        if (faceDetectionEnabled) {
            cv::cvtColor(frame, grey, cv::COLOR_BGR2GRAY, 0); // convers the image to greyscale
            detectFaces(grey, faces);
            drawBoxes(frame, faces);
            cv::imshow("Video", frame);
        }

        switch (lastKey) {
            case 'g': // Task 3 OpenCV grayscale
                cv::cvtColor(frame, processedFrame, cv::COLOR_BGR2GRAY);
                cv::cvtColor(processedFrame, processedFrame, cv::COLOR_GRAY2BGR); 
                cv::imshow("Video", processedFrame);
                break;

            case 'h': // Task 4 Custom grayscale
                Customgreyscale(frame, processedFrame);
                cv::imshow("Video", processedFrame);
                break;

            case 's': // Task 2 Save image
                cv::imwrite("saved_image.jpg", frame);
                std::cout << "Image saved to saved_image.jpg" << std::endl;
                cv::imshow("Video", frame);
                break;

          case 'r': // Task 5 Apply sepia tone
                applySepia(frame, processedFrame, false);
                cv::imshow("Video", processedFrame);
                break;

            case 'b': // Task 6 Custom 5x5 blur
                blur5x5_2(frame, processedFrame);
                cv::imshow("Video", processedFrame);
                break;

            case 'x': // Task 7 Apply Sobel X filter
                sobelX3x3(frame, sobelXFrame); 
                cv::convertScaleAbs(sobelXFrame, sobelXAbs); 
                cv::imshow("Video", sobelXAbs);
                break;

            case 'y': // Task 7 Apply Sobel Y filter
                sobelY3x3(frame, sobelYFrame);
                cv::convertScaleAbs(sobelYFrame, sobelYAbs);
                cv::imshow("Video", sobelYAbs);
                break;

            case 'm': // Task 8 Apply Gradient Magnitude
                sobelX3x3(frame, sobelXFrame);
                sobelY3x3(frame, sobelYFrame);
                magnitude(sobelXFrame, sobelYFrame, gradientMagnitude);
                cv::imshow("Video", gradientMagnitude);
                break;

            case 'l': // Task 9 Blur and Quantize
                blurQuantize(frame, processedFrame, 10);
                cv::imshow("Video", processedFrame);
                break;

            case 'f': // Task 10 Toggle Face Detection
                faceDetectionEnabled = !faceDetectionEnabled;
                //printf("Face detection %s\n", faceDetectionEnabled ? "enabled" : "disabled");
                break;

            case 'e': // Task 12 Emboss effect
                embossEffect(frame, processedFrame);
                cv::imshow("Video", processedFrame);
                break;

            case 'c': // Task 12 Isolate color
                isolateColor(frame, processedFrame, cv::Scalar(0, 100, 100), cv::Scalar(10, 255, 255)); // Example: Isolate red
                cv::imshow("Video", processedFrame);
                break;

            case 't': // Task 12 Cartoonize the video
                cartoonize(frame, processedFrame);
                cv::imshow("Video", processedFrame);
                break;

            case 'p': // Extension - Pencil Sketch Effect
                pencilSketch(frame, processedFrame);
                cv::imshow("Video", processedFrame);
                break;

            case 'v': // Extension - Apply sepia tone with vignette
                applySepia(frame, processedFrame, true);
                cv::imshow("Video", processedFrame);
                break;

            default:
                cv::imshow("Video", frame);
                break;
        }

        char key = cv::waitKey(10);
        if (key == 'q') {
            break;
        } else if (key != -1) {
            lastKey = key;
        }
    }

    return 0;
}