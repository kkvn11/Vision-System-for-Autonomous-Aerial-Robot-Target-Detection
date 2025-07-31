#include <opencv2/opencv.hpp>
using namespace cv;
using namespace std;

bool ColorImg::findSudoku(Mat imgIn) {
    if (imgIn.data == NULL) exit(0);

    resize(imgIn, imgResize, Size(320, 240), 0, 0, INTER_LINEAR);
    cvtColor(imgResize, imgHSV, CV_BGR2HSV);
    cv::split(imgHSV, channels);
    imgH = channels.at(0);
    imgS = channels.at(1);
    imgV = channels.at(2);

    threshold(imgV, imgVthreshold, 50, 255, THRESH_BINARY);
    imgH.copyTo(imgHMasked, imgVthreshold);

    imgYellow = ((imgHMasked > 10) & (imgHMasked < 165));
    imgRed = (((imgHMasked > 165) & (imgHMasked < 190)) | ((imgHMasked > 0) & (imgHMasked < 10)));

    erode_ele = getStructuringElement(1, Size(3, 3));
    dilate(imgRed, imgRed, erode_ele);
    dilate(imgYellow, imgYellow, erode_ele);

    vector<Vec4i> lines;
    HoughLinesP(imgRed, lines, 1, CV_PI / 90, 50, 10, 0);
    Mat imgLines = Mat::zeros(imgResize.size(), CV_8UC3);
    for (size_t i = 0; i < lines.size(); i++) {
        Vec4i l = lines[i];
        line(imgLines, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(50, 200, 0), 5, CV_AA);
    }

    // (Omitted: contour extraction, rectangle fitting, and centroid calculation)
    imshow("findSudoku", imgResize);
    return true;
}
