#include <opencv2/opencv.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <string_view>

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
    // zenoh
    Config config ;
    cv::Mat frame ;
    std::string str ;
    auto session = expect<Session>(open(std::move(config)));

    auto subscriber = expect<Subscriber>(
        session.declare_subscriber("pub_img", [&str,&frame](const Sample& sample) {
            str = std::string(sample.get_payload().as_string_view()) ;
            // std::cout << "Received: " << str << std::endl;
            frame = stringToMat(str) ; 
            cv::imshow("camera_sub", frame);
            if (cv::waitKey(1) == 27)
                return;
        })
    );

    while (true) { }
    return 0;
}
