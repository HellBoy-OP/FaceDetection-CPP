/*
*   Project Name: Face Detection App
*   Description:
*       A C++ program that detects faces using default webcam.
*       Based on OpenCV library for C++.
*       Detect and draw rectangle around the face and give face count.
*       Random rectangle & text color on every startup.
*/


// opencv header files
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/dnn/dnn.hpp>

// required header files
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>


using namespace std;
using namespace cv;

// function to generate random rgb numbers and store in given array
// range is 0 - 255
void random_RGB_number(int rand_array[]) {
    srand(time(0));
    for (int i = 0; i < 3; i++) {
        rand_array[i] = rand() % 255;
    }
}

// main function
int main() {
    int rand_array[3];  // array to store rgb numbers
    Mat video_stream;   // matrix hold frame for video
    VideoCapture real_time(0);  // to capture video from default webcam

    namedWindow("Face Detection");  // a window that displays the output video

    // load the xml classifier
    // using opencv default haarcascade frontalface alt
    string cascade_path = "C:/opencv/sources/data/haarcascades/haarcascade_frontalface_alt.xml";
    CascadeClassifier faceDetector;
    faceDetector.load(cascade_path);

    vector<Rect> faces;  // rectangular vector

    random_RGB_number(rand_array);  // calling random rgb function

    // start to detect face and draw rectangle until 'q' / 'Q' is pressed
    while (true) {
        // start to detect the faces in frame
        faceDetector.detectMultiScale(video_stream, faces, 1.1, 4, CASCADE_SCALE_IMAGE, Size(30, 30));
        real_time.read(video_stream);

        // add text on the output video showing number of faces.
        putText(
            video_stream,   // matrix data of webcam video
            "Face Detected: " + to_string(faces.size()),    // text to display
            Point(10, 30),  // position of text in video
            FONT_HERSHEY_COMPLEX,    // default font from opencv
            1,  // font scale value
            CV_RGB(rand_array[0], rand_array[1], rand_array[2]),    // font color
            2   // text thikness
        );
        putText(
            video_stream,
            "~ Anand",
            Point(500, 475),
            FONT_HERSHEY_SCRIPT_SIMPLEX,
            1,
            CV_RGB(rand_array[0], rand_array[1], rand_array[2]),
            2
        );

        // draw rectangle around the detected face
        for (int i = 0; i < faces.size(); i++) {
            Mat faceROI = video_stream(faces[i]);   // another matrix declaration to store the face
            int x = faces[i].x; // initial row value of rectangle's starting point
            int y = faces[i].y; // initial column value of rectangle's starting point
            int h = y + faces[i].height;    // calculate rectangle height
            int w = x + faces[i].width;     // calculate rectangle width

            // draw the rectangle using above creds
            rectangle(video_stream, Point(x, y), Point(w, h), CV_RGB(rand_array[0], rand_array[1], rand_array[2]), 2, 8, 0);
        }

        // show the output video
        imshow("Face Detection", video_stream);

        // wait till 'q' or 'Q' is pressed and terminate the window
        char c = (char)waitKey(1);
        if (c == 27 || c == 'q' || c == 'Q') {
            break;
        }
    }   // end of loop. terminate process

    return 0;
}

