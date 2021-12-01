#include <iostream>
//#include <opencv2/highgui.hpp>
#include <thread>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
//#include <opencv2/tracking.hpp>
//#include <opencv2/video/tracking.hpp>
//#include <opencv2/tracking/tracking_legacy.hpp>
#include <unistd.h>

#include "detector.h"
#include "cxxopts.hpp"

//using namespace  cv;
//using namespace std;

cv::Mat frame;
cv::Mat yolo_frame;
int finished = 0;
int game_over= 0;
int yolo_is_working = 0 ;
Detector detector = Detector("/home/chenyl/CLionProjects/untitled1/yolov5m.torchscript.pt", torch::kCUDA);

void show_img()
{
    cv::namedWindow("output");
    while (1){
        if (finished == 1){
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
    while(1){
        yolo_is_working = 1;
        auto results = detector.Run(yolo_frame, 0.5f, 0.5f);
        yolo_is_working = 0;
        if (game_over == 1){
            break;
        }

    }


}






int main() {
//    string trackerTypes[7] = {"BOOSTING", "MIL", "KCF", "TLD","MEDIANFLOW", "GOTURN", "MOSSE"};
//    string trackerType = trackerTypes[2];
//    Ptr<Tracker> tracker;

//    tracker = TrackerKCF::create();
//    tracker = legacy::upgradeTrackingAPI(legacy::TrackerMOSSE::create());


    cv::VideoCapture capture;
    torch::DeviceType device_type;



    frame = capture.open("/home/chenyl/CLionProjects/untitled1/output_test_1122.avi");
    if(!capture.isOpened()){
        printf("can not open ...\n");
        return -1;
    }
    capture.read(frame);
    std::cout << "Run once on empty image" << std::endl;
    auto temp_img = cv::Mat::ones(frame.rows, frame.cols, CV_32FC3);
    detector.Run(temp_img, 0.5f, 0.5f);
    std::cout << "Run once twice empty image" << std::endl;
    auto temp_img2 = cv::Mat::ones(frame.rows, frame.cols, CV_32FC3);
    detector.Run(temp_img, 0.5f, 0.5f);


    yolo_frame = frame.clone();


    bool ok = capture.read(frame);

    int start = 0;
    cv::Rect bbox;
    std::thread th1(show_img);
    std::thread th2(yolo_job);
    th1.detach();
    th2.detach();
    while (capture.read(frame)){
        finished = 0;
        if (yolo_is_working== 0){
            yolo_frame = frame.clone();
        }
        double timer = (double)cv::getTickCount();
        usleep(5000);
//        if (start == 1){
//            bool ok = tracker->update(frame, bbox);
//            if (ok)
//            {
//                rectangle(frame, bbox, Scalar(255, 0, 0), 2, 1);
//            }
//            else
//            {
//                putText(frame, "Tracking failure detected", Point(100,80), FONT_HERSHEY_SIMPLEX, 0.75, Scalar(0,0,255),2);
//            }
//        }
//
//
//        int k = waitKey(1);
//        if(k == 27)
//        {
//            break;
//        }
//        if(k == 97)
//        {
//            Rect bbox = selectROI(frame, false);
//            tracker->init(frame, bbox);
//            start = 1;
//        }


//        printf("Read one frame ...\n");
        float fps = cv::getTickFrequency() / ((double)cv::getTickCount() - timer);
        putText(frame, "FPS : " + std::to_string(int(fps)), cv::Point(100,50), cv::FONT_HERSHEY_SIMPLEX, 0.75, cv::Scalar(50,170,50), 2);
        finished = 1;
        if (game_over == 1){break;
        }
    }
    capture.release();
    return 0;
}
