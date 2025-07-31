#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

bool ColorImg::fixStart(cv::Mat imgIn) {
    bool hascenter = false;
    if (imgIn.data == NULL) return -1;

    resize(imgIn, imgResize, Size(160, 120), 0, 0, INTER_LINEAR);
    cvtColor(imgResize, imgGray, CV_BGR2GRAY);
    cvtColor(imgResize, imgHSV, CV_BGR2HSV);
    imgBin = imgGray < 100;
    cv::split(imgHSV, channels);
    imgH = channels.at(0);
    imgS = channels.at(1);
    imgV = channels.at(2);

    imgS = imgS < 120;
    imgH = ~((imgH > 90) & (imgH < 120));
    imgBin = imgBin & imgS & imgH;

    erode_ele = getStructuringElement(0, Size(3, 3));
    erode(imgBin, imgSErode, erode_ele);

    vector<vector<Point>> contours;
    vector<Vec4i> hierarchy;
    double area = 0;
    uint number = 0;
    Mat img2contours;
    imgSErode.copyTo(img2contours);
    findContours(img2contours, contours, hierarchy, RETR_CCOMP, CHAIN_APPROX_SIMPLE);

    for (uint i = 0; i < contours.size(); i++) {
        double nowarea = contourArea(contours[i]);
        if ((nowarea > area) && (nowarea > 400)) {
            area = nowarea;
            number = i;
        }
    }

    if (area != 0) {
        Scalar color(0, 0, 255);
        drawContours(imgResize, contours, number, color, 1, 8, vector<Vec4i>(), 0, Point());

        RotatedRect box = minAreaRect(Mat(contours[number]));
        Point2f vertex[4];
        box.points(vertex);
        // (Omitted: Variance & rotation check and result assignment)
        hascenter = true;
    }

    imshow("findSquare", imgResize);
    m_deal_writer << imgResize;
    return hascenter;
}
