//
// Created by chenyl on 12/18/21.
//

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
cv::Rect result_bbox;
int start = 0;
int start_2 = 0;
int flip = 0;
int flip_2 = 0;


Detector detector = Detector("/home/chenyl/CLionProjects/untitled1/yolov5x.torchscript.pt", torch::kCUDA);

void writeCvRectToFile(cv::Rect2d rect, const char* filename) {
    cv::FileStorage fs(filename, cv::FileStorage::WRITE);
    fs<<"x"<<rect.x;
    fs<<"y"<<rect.y;
    fs<<"width"<<rect.width;
    fs<<"height"<<rect.height;
    fs.release();
}

int main(){
    int start_eval = 0;
    int total_num = 0;
    int yolo_num = 0;
    int found_num = 0;
    cv::VideoCapture capture;
//    int codec = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');
//    cv::VideoWriter writer("/home/chenyl/CLionProjects/untitled1/ex3.mp4", codec, 190, cv::Size (640, 512), true);

    frame = capture.open("/home/chenyl/CLionProjects/untitled1/output_test_1122.avi");
    if(!capture.isOpened()){
        printf("can not open ...\n");
        return -1;
    }
    capture.read(frame);
    std::cout << "Run once on empty image" << std::endl;
    auto temp_img = cv::Mat::ones(frame.rows, frame.cols, CV_32FC3);
    detector.Run(temp_img, 0.5f, 0.5f);
    std::cout << "Run twice on empty image" << std::endl;
    auto temp_img2 = cv::Mat::ones(frame.rows, frame.cols, CV_32FC3);
    detector.Run(temp_img, 0.5f, 0.5f);


    yolo_frame = frame.clone();
    cv::namedWindow("output");

    bool ok = capture.read(frame);

    while (capture.read(frame)){
        total_num+=1;
        if (total_num==3451){
            start_eval = 1;
        }
        if (start_eval == 0){
            usleep(5000);
            cv::imshow("output",frame);
            int k = cv::waitKey(1);
            if(k == 27)
            {   game_over= 1;
                break;
            }
            if (k==115)   //push s to start eval
            {
                start_eval = 1;
            }
        }


        else{
            yolo_num+=1;
            std::cout<<total_num<<std::endl;
            auto results = detector.Run(frame, 0.3f, 0.3f);
            if (!results.empty()){
                for (const auto& detection : results[0]){
                    int class_idx = detection.class_idx;
                    if ((class_idx == 39)||(class_idx==75)){
                        yolo_bbox = detection.bbox;
                        found_num+=1;
                        break;
                    }
                }
            }
            cv::Mat show_frame = frame.clone();
            cv::rectangle(show_frame, yolo_bbox, cv::Scalar (0, 255, 255), 2, 1);
            cv::imshow("output",show_frame);
            int k = cv::waitKey(0);
            if (k==115)   //push s to save bbox
            {
                writeCvRectToFile(yolo_bbox, ("/home/chenyl/CLionProjects/untitled1/images/"+std::to_string(total_num)+".yaml").data());
                cv::imwrite(("/home/chenyl/CLionProjects/untitled1/images/"+std::to_string(total_num)+".jpg").data(), frame);
            }
            if (k==100)  //push d to draw bbox
            {
                cv::Rect2d r = cv::selectROI(frame);
                writeCvRectToFile(r, ("/home/chenyl/CLionProjects/untitled1/images/"+std::to_string(total_num)+".yaml").data());
                cv::imwrite(("/home/chenyl/CLionProjects/untitled1/images/"+std::to_string(total_num)+".jpg").data(), frame);
            }
            if(k == 27)
            {   game_over= 1;
                break;
            }






            if (k==101)   //push e to end eval
            {
                start_eval = 0;
            }

        }

    }
    std::cout << found_num*100/yolo_num<< std::endl;




    return 0;
}