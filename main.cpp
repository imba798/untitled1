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
int use_yolo_or_tracker = 1; //1 is yolo and 0 is tracker
int yolo_lost_num = 0;
int tracker2_lost_num= 0;
int tracker2_track_num=0;
float yolo_confidence;
int yolo_loop = 0;





Detector detector = Detector("/home/chenyl/CLionProjects/untitled1/yolov5m.torchscript.pt", torch::kCUDA);



void show_img()
{
    cv::namedWindow("output");
    while (1){
        if (finished == 1){
//            cv::rectangle(frame, bbox, cv::Scalar (0, 0, 255), 2, 1);
//            cv::rectangle(frame, yolo_bbox, cv::Scalar (0, 255, 255), 2, 1);
//            cv::rectangle(frame, tracker2_bbox, cv::Scalar (255, 0, 255), 2, 1);
            if ((bbox.width!=0)&&(tracker2_bbox.width!=0)){
                result_bbox = cv::Rect(cv::Point((bbox.x+tracker2_bbox.x)/2, (bbox.y+tracker2_bbox.y)/2), cv::Point((bbox.x+bbox.width+tracker2_bbox.x+tracker2_bbox.width)/2, (bbox.y+tracker2_bbox.y+bbox.height+tracker2_bbox.height)/2));
            }
            else{
                if (bbox.width==0){
                    result_bbox = tracker2_bbox;
                }
                else if (tracker2_bbox.width==0){
                    result_bbox = bbox;

                }
            }

            cv::rectangle(frame, result_bbox, cv::Scalar (100, 100, 100), 2, 1);
            imshow("output", frame);

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
        if (game_over == 1){
            break;
        }
        if (pic_is_ready==1){
            yolo_is_working = 1;

            auto results = detector.Run(yolo_frame, 0.3f, 0.3f);

            if (!results.empty()){
                for (const auto& detection : results[0]){
                    int class_idx = detection.class_idx;
//                    if ((class_idx == 39)||(class_idx==75)){
                    if (class_idx == 47){
                        yolo_bbox = detection.bbox;
                        std::cout << "found" << std::endl;
                        yolo_frame_for_tracker = yolo_frame.clone();
                        yolo_result_is_done = 1;
                        yolo_lost_num = 0;
                        break;
                    }


                }
                if (yolo_result_is_done==0){
                    yolo_lost_num+=1;
                }
            }
            else{
                yolo_lost_num+=1;
            }

            yolo_is_working = 0;
            pic_is_ready = 0;
        }

    }
}

void init_tracker(){
    while(1){
        if (game_over == 1){
            break;
        }
        if (tracker2_track_num>3){
            use_yolo_or_tracker=0;
        }
        else{
            use_yolo_or_tracker=1;
        }
        std::cout<<use_yolo_or_tracker<<std::endl;
        if (((yolo_result_is_done==1)||(use_yolo_or_tracker==0))&&(yolo_is_working==0)){
            if (flip==0){
                if (use_yolo_or_tracker==1){
                    tracker2 = cv::legacy::upgradeTrackingAPI(cv::legacy::TrackerMOSSE::create());
                    tracker2->init(yolo_frame_for_tracker, yolo_bbox);
                }
                else{
                    tracker2 = cv::legacy::upgradeTrackingAPI(cv::legacy::TrackerMOSSE::create());
                    tracker2->init(tracker_2_frame_for_tracker, tracker2_bbox);
                }

            }
            else{
                if (use_yolo_or_tracker==1){
                    tracker1 = cv::legacy::upgradeTrackingAPI(cv::legacy::TrackerMOSSE::create());
                    tracker1->init(yolo_frame_for_tracker, yolo_bbox);
                }
                else{
                    tracker1 = cv::legacy::upgradeTrackingAPI(cv::legacy::TrackerMOSSE::create());
                    tracker1->init(tracker_2_frame_for_tracker, tracker2_bbox);
                }
            }

            yolo_result_is_done = 0;
            start = 1;
            tracker_init_is_done = 1;

        }

    }

}

void init_second_tracker(){
    while(1){
        if (game_over == 1){
            break;
        }
        if ((yolo_result_is_done==1)&&(tracker_2_init_is_done==0)){
            if (flip_2==0){
                tracker4 = cv::TrackerKCF::create();
                tracker4->init(yolo_frame_for_tracker, yolo_bbox);
            }
            else{
                tracker3 = cv::TrackerKCF::create();
                tracker3->init(yolo_frame_for_tracker, yolo_bbox);
            }

            start_2 = 1;
            tracker_2_init_is_done = 1;



        }
    }
}

void run_second_tracker(){
    cv::Ptr<cv::Tracker> local_tracker;
    while (1){
        if (game_over == 1){
            break;
        }
        if ((start_2 == 1)){
            tracker_2_is_working = 1;
            if (tracker_2_init_is_done == 1) {
                if (flip_2 == 0) {
                    local_tracker = tracker4;
                } else {
                    local_tracker = tracker3;
                }
                flip_2 = 1 - flip_2;
                tracker_2_init_is_done = 0;
            }
            if (pic_is_ready_2==1){
                bool ok = local_tracker->update(tracker_2_frame, tracker2_bbox);
                if (ok){
                    tracker_2_frame_for_tracker = tracker_2_frame.clone();
                    tracker2_track_num+=1;
                    tracker2_lost_num=0;
                }
                else{
                    tracker2_track_num=0;
                    tracker2_lost_num+=1;
                }

                pic_is_ready_2 = 0;
            }

            tracker_2_is_working = 0;


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
//    int codec = cv::VideoWriter::fourcc('M', 'J', 'P', 'G');
//    cv::VideoWriter writer("/home/chenyl/CLionProjects/untitled1/ex3.mp4", codec, 190, cv::Size (640, 512), true);

//    frame = capture.open("/home/chenyl/CLionProjects/untitled1/output_test_1122.avi");
    frame = capture.open("/home/chenyl/CLionProjects/untitled1/20220131-test1.avi");
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


    bool ok = capture.read(frame);

    cv::Ptr<cv::Tracker> local_tracker;

    std::thread th1(show_img);
    std::thread th2(yolo_job);
    std::thread th3(init_tracker);
    std::thread th4(init_second_tracker);
    std::thread th5(run_second_tracker);
    th1.detach();
    th2.detach();
    th3.detach();
    th4.detach();
    th5.detach();
    while (capture.read(frame)){
        finished = 0;
        if (yolo_is_working== 0){
            yolo_frame = frame.clone();
            pic_is_ready = 1;
        }
        if (tracker_2_is_working== 0){
            tracker_2_frame = frame.clone();
            pic_is_ready_2 = 1;
        }
        double timer = (double)cv::getTickCount();
        usleep(4900);
        if (start == 1){
            if (tracker_init_is_done==1){
                if (flip==0){
                    local_tracker = tracker2;
                }
                else{
                    local_tracker = tracker1;
                }
                flip = 1-flip;
                tracker_init_is_done = 0;
            }
            bool ok = local_tracker->update(frame, bbox);
//            if (!ok){
//                putText(frame, "Tracking failure detected", cv::Point(100,100), cv::FONT_HERSHEY_SIMPLEX, 0.75, cv::Scalar(0,0,255),2);
//            }
//            std::cout<<"here"<<std::endl;
        }


//        printf("Read one frame ...\n");
        float fps = cv::getTickFrequency() / ((double)cv::getTickCount() - timer);
//        putText(frame, "FPS : " + std::to_string(int(fps)), cv::Point(100,50), cv::FONT_HERSHEY_SIMPLEX, 0.75, cv::Scalar(50,170,50), 2);
//        putText(frame, "Flip : " + std::to_string(flip), cv::Point(300,50), cv::FONT_HERSHEY_SIMPLEX, 0.75, cv::Scalar(50,170,50), 2);
        finished = 1;
//        writer.write(frame);
        if (game_over == 1){break;
        }
    }
    capture.release();
//    writer.release();
    return 0;
}
