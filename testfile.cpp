//
// Created by chenyl on 12/2/21.
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



class myTracker: protected cv::Ptr<cv::Tracker>{
public:
    bool check_is_init(){
        return isInit;
    }
};


int main(){
    myTracker tracker = cv::legacy::upgradeTrackingAPI(cv::legacy::TrackerMOSSE::create());
    std::cout << tracker.isInit << std::endl;


    return 0;
}