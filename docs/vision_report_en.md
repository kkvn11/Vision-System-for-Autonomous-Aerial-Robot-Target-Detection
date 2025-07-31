# Technical Report: Vehicle Vision Tracking System

## 1. Task Overview

The summer camp task was to design an autonomous flying robot capable of:
- Navigating in an 8x8 meter field
- Detecting and picking up balls autonomously

To achieve this, the system needs to:
- Identify pickup zones
- Detect circular disks with yellow sandbags
- Recognize a 3x3 light grid (Sudoku pattern)

We developed the solution using a downward-facing camera and OpenCV.

---

## 2. Design Overview

### 2.1 Pickup Zone Detection

The pickup zone is a black foam box with a white border. The detection process includes:
- Convert to HSV and use:
  - S channel to remove high-saturation interference
  - V channel for thresholding
  - H channel to filter deep blue areas
- Apply morphological operations (erosion)
- Extract contours and approximate to a rectangle
- Filter based on edge variance

```cpp
imgS = imgS < 120;
imgH = ~((imgH > 90) & (imgH < 120));
imgBin = imgBin & imgS & imgH;
```

### 2.2 Disk Detection

Yellow sandbags are used as markers. The detection includes:
- HSV filtering on S channel
- Contour extraction
- Filter based on area and perimeter
- Ellipse fitting on suitable contours

```cpp
if (nowarea / arcLength > 10) {
    RotatedRect ellipse = fitEllipse(contours[i]);
    ellipse(imgResize, ellipse, Scalar(0, 0, 255), 1);
}
```

### 2.3 Sudoku Light Grid Detection

#### Method A: Normal Exposure
- V channel to detect brightness
- H channel to identify red/yellow colors
- Issue: Overexposure and color merging

#### Method B: Reduced Exposure
- Use Hough Transform to detect tube lines
- Draw thick lines to close gaps
- Apply erosion and dilation
- Extract internal contours and fit rectangles
- Calculate centers of red/yellow lights

```cpp
HoughLinesP(imgRed, lines, 1, CV_PI/90, 50, 10, 0);
line(imgLines, Point(l[0], l[1]), Point(l[2], l[3]), Scalar(50,200,0), 5, CV_AA);
```

---

## 3. Conclusion and Limitations

The algorithm works reliably under fixed lighting and camera settings. However, under dynamic lighting conditions, such as changes in white balance or exposure, the performance degrades. Future improvements may include histogram equalization and adaptive preprocessing for better robustness.
