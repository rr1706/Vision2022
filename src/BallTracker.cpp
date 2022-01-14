#include "frc1706/BallTracker.hpp"
#include "opencv2/videoio.hpp"

namespace frc1706 {
    BallTracker::BallTracker(const cv::VideoCapture &cap, bool broadcast) :
        _enable_broadcast(broadcast), _capture_device(cap) {}

    BallTracker::~BallTracker() {}
};