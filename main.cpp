// #include <opencv2/opencv.hpp>
// #include <iostream>
// #include <vector>

// struct threshold_params {
//     int h_up;
//     int s_up;
//     int v_up;
//     int h_down;
//     int s_down;
//     int v_down;
// };

// class Detector {
// private:
//     threshold_params thres;

// public:
//     Detector(const threshold_params &params)
//         : thres(params) {}

//     cv::Mat preprocessingImage(const cv::Mat &rgb_image){
//         cv::Mat blurred;
//         cv::GaussianBlur(rgb_image, blurred, cv::Size(11, 11), 0);
        
//         cv::Mat hsv_image;
//         cv::cvtColor(blurred, hsv_image, cv::COLOR_BGR2HSV);

//         cv::Mat mask;
//         cv::inRange(hsv_image, cv::Scalar(thres.h_up, thres.s_up, thres.v_up),
//                     cv::Scalar(thres.h_down, thres.s_down, thres.v_down), mask);

//         cv::dilate(mask, mask, cv::Mat(), cv::Point(-1, -1), 5);
//         cv::erode(mask, mask, cv::Mat(), cv::Point(-1, -1), 5);

//         return mask;
//     }

//     cv::Mat b_r_max(const cv::Mat &frame){
//         cv::Mat bgr_planes[3];
//         cv::split(frame, bgr_planes);
//         cv::Mat max_blue = cv::max(cv::max(bgr_planes[0], bgr_planes[1]), bgr_planes[2]);

//         cv::Mat blue_mask = (bgr_planes[0] == max_blue) & (bgr_planes[1] == max_blue) & (bgr_planes[2] == max_blue);
//         blue_mask.convertTo(blue_mask, CV_8U, 255);

//         cv::Mat masked_image;
//         cv::bitwise_and(frame, frame, masked_image, blue_mask);

//         return masked_image;
//     }

//     std::vector<std::vector<cv::Point>> find_ball(const cv::Mat &frame){
//         std::vector<std::vector<cv::Point>> contours;
//         cv::findContours(frame.clone(), contours, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
//         return contours;
//     }

//     void draw_circle(cv::Mat &frame, const std::vector<std::vector<cv::Point>> &cnts){
//         if (!cnts.empty()) {
//             size_t largestContourIndex = 0;
//             double maxArea = cv::contourArea(cnts[0]);

//             for (size_t i = 1; i < cnts.size(); ++i) {
//                 double area = cv::contourArea(cnts[i]);
//                 if (area > maxArea) {
//                     maxArea = area;
//                     largestContourIndex = i;
//                 }
//             }

//             cv::Point2f center; 
//             float radius;
//             cv::minEnclosingCircle(cnts[largestContourIndex], center, radius);
//             cv::Moments M = cv::moments(cnts[largestContourIndex]);
//             if (M.m00 != 0) {
//                 center = cv::Point2f(M.m10 / M.m00, M.m01 / M.m00);
//                 float radius = maxArea > 10 ? std::sqrt(maxArea / CV_PI) : 0;
//                 if (radius > 10) {
//                     cv::circle(frame, cv::Point(center.x, center.y), static_cast<int>(radius), cv::Scalar(0, 255, 255), 2);
//                     cv::circle(frame, cv::Point(center.x, center.y), 5, cv::Scalar(0, 0, 255), -1);
//                     std::cout << center << std::endl;
//                 }
//             }
//         }
//     }
// };

// void processVideo() {
//     // Open the default video camera
//     cv::VideoCapture cap(0);
//     if (!cap.isOpened()) {
//         std::cerr << "Error: Unable to open video capture device." << std::endl;
//         return;
//     }

//     // Parameters for thresholding
//     threshold_params params = {30, 39, 96, 59, 70, 100};
//     Detector detector(params);

//     cv::Mat frame;
//     while (true) {
//         // Read a new frame from the camera
//         cap >> frame;

//         if (frame.empty()) {
//             std::cerr << "Error: Unable to read frame from video capture device." << std::endl;
//             break;
//         }

//         // Preprocess the image
//         cv::Mat processed_image = detector.preprocessingImage(frame);

//         // Find contours
//         std::vector<std::vector<cv::Point>> cnts = detector.find_ball(processed_image);

//         // Draw circles
//         detector.draw_circle(frame, cnts);

//         // Display the frame
//         cv::imshow("Frame", frame);

//         // Press 'q' to exit
//         if (cv::waitKey( 1 & 0xFF) == 'q') {
//             break;
//         }
//     }

//     // Release the video capture device
//     cap.release();

//     // Close all windows
//     cv::destroyAllWindows();
// }

// int main() {
//     processVideo();
//     return 0;
// }


// #include "opencv2/opencv.hpp"
// #include <iostream>
 
// using namespace cv;
// using namespace std;
 
// #include <opencv2/opencv.hpp>
// #include <iostream>
// #include <string>

// int main()
// {

//     // rtsp地址变量
//     // 一般main 主码流，sub 子码流
//     std::string rtsp1 = "rtsp://admin:SEGJKL@192.168.3.75:554/h264/ch1/sub/av_stream";

//     // std::string rtsp1 = "rtsp://localhost:8554/live1.sdp";


//     // CAP_FFMPEG：使用ffmpeg解码
//     cv::VideoCapture stream1 = cv::VideoCapture("/dev/video0", cv::CAP_V4L2);
//     stream1.set(3, 640);
//     stream1.set(4, 480);


//     if (!stream1.isOpened())
//     {
//         std::cout << "有视频流未打开" << std::endl;
//         return -1;
//     }

//     cv::Mat frame1;


//     // // 使用namedWindow创建窗口，WINDOW_AUTOSIZE：自动调整窗口大小
//     // cv::namedWindow("rtsp_demo", cv::WINDOW_AUTOSIZE);

//     while (true)
//     {
//         if (!stream1.read(frame1))
//         {
//             std::cout << "有视频流未读取" << std::endl;
//             continue;
//         }


//         cv::imshow("rtsp_demo", frame1);

//         if (cv::waitKey(1) == 27)
//         {
//             break;
//         }
//     }

//     return 0;
// }

#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;

int width = 640;
int heigth = 480;
cv::VideoCapture cap;
int main()
{
	cap.open(0);
	cap.set(cv::CAP_PROP_FRAME_WIDTH, width);    //设置宽度
	cap.set(cv::CAP_PROP_FRAME_HEIGHT, heigth);  //设置长度
	cap.set(cv::CAP_PROP_FOURCC, cv::VideoWriter::fourcc('M', 'J', 'P', 'G'));//视频流格式
	cap.set(cv::CAP_PROP_FPS, 30);//帧率 帧/秒

	if (!cap.isOpened())
	{
		cout << "打开失败" << endl;
		return 0;
	}
	cv::Mat frame;
	cv::namedWindow("frame");//创建显示窗口


	while (1)
	{
		cap >> frame;//bool judge=cap.read(frame);
		if (frame.empty()) break;
        cout << "打成功" << endl;
		cv::imshow("frame", frame);
		if (27 == cv::waitKey(33))//"ESC"
			break;
	}
	cv::destroyWindow("frame");
	cap.release();
	return 0;
}