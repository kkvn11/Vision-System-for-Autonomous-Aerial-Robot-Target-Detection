#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

bool ColorImg::findCircle(Mat img) {
    bool hascenter = false;
    resize(img, imgResize, Size(160, 120), 0, 0, INTER_LINEAR);
    cvtColor(imgResize, imgHSV, CV_BGR2HSV);
    cv::split(imgHSV, channels);
    imgS = channels.at(1);
    imgS = imgS < 100;

    erode_ele = getStructuringElement(0, Size(4, 4));
    erode(imgS, imgSErode, erode_ele);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    Mat img2contours;
    imgSErode.copyTo(img2contours);
    findContours(img2contours, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

    unsigned int x_sum = 0, y_sum = 0, cnt = 0;
    for (uint i = 0; i < contours.size(); i++) {
        double nowarea = contourArea(contours[i]);
        if (nowarea > 250) {
            int length = arcLength(contours[i], true);
            if (nowarea / length > 10) {
                RotatedRect ellipsein = fitEllipse(Mat(contours[i]));
                ellipse(imgResize, ellipsein, Scalar(0, 0, 255), 1);
                x_sum += ellipsein.center.x;
                y_sum += ellipsein.center.y;
                cnt++;
                hascenter = true;
            }
        }
    }

    if (hascenter) {
        center_point.x = x_sum / cnt;
        center_point.y = y_sum / cnt;
    }

    imshow("findCircle", imgResize);
    m_deal_writer << imgResize;
    return hascenter;
}
