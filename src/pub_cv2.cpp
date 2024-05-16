#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include "zenoh.hxx"

#include <nlohmann/json.hpp>
// sudo apt install nlohmann-json3-dev

using namespace zenoh;
using json = nlohmann::json;

std::string matToString(const cv::Mat& image) {
    std::vector<uchar> buffer;
    cv::imencode(".png", image, buffer);
    return std::string(buffer.begin(), buffer.end());
}

cv::Mat stringToMat(const std::string& imageString) {
    std::vector<uchar> buffer(imageString.begin(), imageString.end());
    return cv::imdecode(buffer, cv::IMREAD_COLOR);
}

int main() {
    cv::VideoCapture cap(0);
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 640); 
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 480); 
    cap.set(cv::CAP_PROP_FPS, 30);

    if (!cap.isOpened()) {
        std::cerr << "Error: Unable to open the camera." << std::endl;
        return -1;
    }
    
    // zenoh
    Config config;

    cv::Mat frame;
    auto session = expect<Session>(open(std::move(config)));
    auto publisher = expect<Publisher>(session.declare_publisher("pub_img"));

    while (true) {
        cap >> frame;
        // frame = stringToMat(str) ;
        if (frame.empty()) {
            std::cerr << "Error: Unable to read frame from the camera." << std::endl;
            break;
        }
        std::string str = matToString(frame) ; 
        publisher.put(str) ;
        cv::imshow("camera_pub", frame);
        if (cv::waitKey(1) == 27)
            break;
    }
    cap.release();
    cv::destroyAllWindows();
    return 0;
}
