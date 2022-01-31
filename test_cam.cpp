//
// Created by chenyl on 12/15/21.
//

/*
  This is the reference example application code for XIMEA cameras.
  You can use it to simplify development of your camera application.

  Sample name:
    xiAPIplusOpenCV / Capture-50-images-and-display

  Description:
    Open camera, capture 50 images while displaying each on the screen

  Workflow:
    1: Open camera
    2: Set parameters
    3: Start acquisition
    4: For each image captured - display on screen
*/

#include <stdio.h>
#include <xiApiPlusOcv.hpp>

#include <iostream>
#include <opencv2/highgui.hpp>
#include <thread>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
#include <opencv2/tracking.hpp>
#include <opencv2/video/tracking.hpp>
#include <opencv2/tracking/tracking_legacy.hpp>
#include <unistd.h>

#include "detector.h"
#include "cxxopts.hpp"

//using namespace  cv;
//using namespace std;

cv::Mat frame;
cv::Mat yolo_frame;
cv::Mat tracker_2_frame;
cv::Mat yolo_frame_for_tracker;
cv::Mat tracker_2_frame_for_tracker;
cv::Ptr<cv::Tracker> tracker1;
cv::Ptr<cv::Tracker> tracker2;
cv::Ptr<cv::Tracker> tracker3;
cv::Ptr<cv::Tracker> tracker4;
int finished = 0;
int game_over= 0;
int yolo_is_working = 0 ;
int tracker_2_is_working = 0;
int pic_is_ready = 0;
int pic_is_ready_2 = 0;
int yolo_result_is_done = 0;
int tracker_init_is_done = 0;
int tracker_2_init_is_done = 0;
cv::Rect bbox;
cv::Rect yolo_bbox;
cv::Rect tracker2_bbox;
int start = 0;
int start_2 = 0;
int flip_flag = 0;
int flip_flag_2 = 0;

Detector detector = Detector("/home/chenyl/CLionProjects/untitled1/yolov5m.torchscript.pt", torch::kCUDA);



void show_img()
{
    cv::namedWindow("output");
    while (1){
        if (finished == 1){
            cv::rectangle(frame, bbox, cv::Scalar (0, 0, 255), 2, 1);
            cv::rectangle(frame, yolo_bbox, cv::Scalar (0, 255, 255), 2, 1);
            cv::rectangle(frame, tracker2_bbox, cv::Scalar (255, 0, 255), 2, 1);
            imshow("Tracking", frame);

            int k = cv::waitKey(1);
            if(k == 27)
            {   game_over= 1;
                break;
            }
        }
    }
}

void yolo_job()
{
    int found_num = 0;
    int total_num = 0;
    while(1){
        if (game_over == 1){
            break;
        }
        if (pic_is_ready==1){
            yolo_is_working = 1;

            auto results = detector.Run(yolo_frame, 0.3f, 0.3f);
            if (!results.empty()){
                total_num+=1;
                for (const auto& detection : results[0]){
                    int class_idx = detection.class_idx;
                    if ((class_idx == 39)||(class_idx==75)){
                        yolo_bbox = detection.bbox;
                        std::cout << "found" << std::endl;
                        found_num+=1;
                        yolo_frame_for_tracker = yolo_frame.clone();
                        yolo_result_is_done = 1;
                        break;
                    }


                }
            }

            yolo_is_working = 0;
            pic_is_ready = 0;
        }

    }
//    std::cout << found_num*100/total_num<< std::endl;
}


#define EXPECTED_IMAGES 200

using namespace cv;
using namespace std;
int main(int argc, char* argv[])
{
    // Sample for XIMEA OpenCV
    xiAPIplusCameraOcv cam;

    // Retrieving a handle to the camera device
    printf("Opening first camera...\n");
//    cam.OpenFirst();
//
//    // Set exposure
//    cam.SetExposureTime(5000); //10000 us = 10 ms
//    // Note: The default parameters of each camera might be different in different API versions
//    cam.SetImageDataFormat(XI_RGB24);
//    cam.SetDownsampling(XI_DWN_2x2);
//    cam.EnableWhiteBalanceAuto();
//    printf("Starting acquisition...\n");
//    cam.StartAcquisition();
//    frame = cam.GetNextImageOcvMat();
    cv::VideoCapture capture;
    frame = capture.open("/home/chenyl/CLionProjects/untitled1/output_test_1122.avi");
    capture.read(frame);
    std::cout << "Run once on empty image" << std::endl;
    auto temp_img = cv::Mat::ones(frame.rows, frame.cols, CV_32FC3);
    detector.Run(temp_img, 0.5f, 0.5f);
    std::cout << "Run twice on empty image" << std::endl;
    auto temp_img2 = cv::Mat::ones(frame.rows, frame.cols, CV_32FC3);
    detector.Run(temp_img, 0.5f, 0.5f);


    yolo_frame = frame.clone();


    frame = cam.GetNextImageOcvMat();

    cv::Ptr<cv::Tracker> local_tracker;

    std::thread th1(show_img);
//    std::thread th2(yolo_job);
//    std::thread th3(init_tracker);
//    std::thread th4(init_second_tracker);
//    std::thread th5(run_second_tracker);
    th1.detach();
//    th2.detach();
//    th3.detach();
//    th4.detach();
//    th5.detach();
        while(1)
        {
            frame = cam.GetNextImageOcvMat();
            finished = 0;
//            if (yolo_is_working== 0){
//                yolo_frame = frame.clone();
//                pic_is_ready = 1;
//            }
//            if (tracker_2_is_working== 0){
//                tracker_2_frame = frame.clone();
//                pic_is_ready_2 = 1;
//            }
            if (start == 1){
                if (tracker_init_is_done==1){
                    if (flip_flag==0){
                        local_tracker = tracker2;
                    }
                    else{
                        local_tracker = tracker1;
                    }
                    flip_flag = 1-flip_flag;
                    tracker_init_is_done = 0;
                }
                bool ok = local_tracker->update(frame, bbox);
//            if (!ok){
//                putText(frame, "Tracking failure detected", cv::Point(100,100), cv::FONT_HERSHEY_SIMPLEX, 0.75, cv::Scalar(0,0,255),2);
//            }
                std::cout<<"here"<<std::endl;
            }


//        printf("Read one frame ...\n");
            finished = 1;
//        writer.write(frame);
            if (game_over == 1){break;
            }
        }

        cam.StopAcquisition();
        cam.Close();
        printf("Done\n");

        cv::waitKey(500);

    return 0;
}

