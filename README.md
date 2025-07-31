# Vehicle Vision Tracking System

This project implements a computer vision pipeline for autonomous aerial vehicles to detect:
- Pick-up Zones (black box with white edges)
- Circular Disks with Yellow Targets
- 3x3 Sudoku Light Grid (with red/yellow lamps)

Algorithms are based on OpenCV and written in C++.

## Features

- HSV-based color filtering and morphology operations
- Contour analysis for shape recognition
- Ellipse fitting and Hough Line Transform
- Designed for fixed lighting environments

## Structure

- `src/`: Source code for different detection modules
- `docs/`: English version of the technical report
- `images/`: Example output visuals

## Dependencies

- OpenCV (3.x or 4.x)
- C++11 or above

## License

This project is licensed under the MIT License.
