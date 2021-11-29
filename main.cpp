#include <iostream>
//#include <opencv2/highgui.hpp>
#include <thread>
#include <stdlib.h>
#include <opencv2/opencv.hpp>
//#include <opencv2/tracking.hpp>
//#include <opencv2/video/tracking.hpp>
//#include <opencv2/tracking/tracking_legacy.hpp>
#include <unistd.h>


//using namespace  cv;
//using namespace std;

cv::Mat frame;
int finished = 0;

void show_img()
{
    cv::namedWindow("output");
    static double timer = (double)cv::getTickCount();
    while (1){

        if (finished == 1){
            float fps = cv::getTickFrequency() / ((double)cv::getTickCount() - timer);
            putText(frame, "FPS : " + std::to_string(int(fps)), cv::Point(400,50), cv::FONT_HERSHEY_SIMPLEX, 0.75, cv::Scalar(150,170,50), 2);
            imshow("Tracking", frame);
            int k = cv::waitKey(100);
            timer = (double)cv::getTickCount();
            if(k == 27)
            {
                break;
            }
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

    frame = capture.open("/home/chenyl/CLionProjects/untitled1/output_test_1122.avi");
    if(!capture.isOpened()){
        printf("can not open ...\n");
        return -1;
    }


    bool ok = capture.read(frame);

    int start = 0;
    cv::Rect bbox;
    std::thread th1(show_img);
    th1.detach();
    while (capture.read(frame)){
        finished = 0;
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
    }
    capture.release();
    return 0;
}
