#include "opencv2/core/mat.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/videoio.hpp"
#include <iostream>

int main() {

    cv::VideoCapture BallCamera;
    //cv::VideoCapture TapeCamera;

    BallCamera.open(0);

    cv::Mat base;
    while(BallCamera.isOpened()) {
        BallCamera >> base;

        char esc = cv::waitKey(33);
        if(esc == 27) {
            BallCamera.release();
            break;
        }
    }
    return 0; 
}