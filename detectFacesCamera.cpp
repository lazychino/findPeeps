#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <unistd.h>

using namespace std;
using namespace cv;

/** Function Headers */
void detectAndDisplay( Mat frame );

/** Global variables */
String face_cascade_name = "/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml";
//~ String face_cascade_name = "/usr/local/share/OpenCV/lbpcascades/lbpcascade_frontalface.xml";
String fullBody = "/usr/local/share/OpenCV/haarcascades/haarcascade_fullbody.xml";
CascadeClassifier face_cascade;
CascadeClassifier body_cascade;
String window_name = "Capture peaple detection";
int face_counter = 1;
int body_counter = 1;

/** @function main */
int main( void )
{
    VideoCapture capture;
    Mat frame;

    //-- 1. Load the cascades
    if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading face cascade\n"); return -1; };
    if( !body_cascade.load( fullBody ) ){ printf("--(!)Error loading body cascade\n"); return -1; };

    //-- 2. Read the video stream
    capture.open( 1 );
    if ( ! capture.isOpened() ) { printf("--(!)Error opening video capture\n"); return -1; }

    while ( capture.read(frame) )
    {
        if( frame.empty() ) 
        {
            printf(" --(!) No captured frame -- Break!");
            break;
        }

        //-- 3. Apply the classifier to the frame
        detectAndDisplay( frame );
        int c = waitKey(10);
        if( (char)c == 27 ) { break; } // escape
    }
    return 0;
}

/** @function detectAndDisplay */
void detectAndDisplay( Mat frame )
{
    std::vector<Rect> faces;
    Mat frame_gray;

    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );

    //-- Detect faces
    face_cascade.detectMultiScale( frame_gray, faces, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(30, 30) );

    for ( size_t i = 0; i < faces.size(); i++ )
    {
        cout << i << ": x=" << faces[i].x << " y=" << faces[i].y << " width=" << faces[i].width << " height=" << faces[i].height << endl;
        Mat faceColor = frame( faces[i] );
        imwrite("face-pics/capture-" + to_string(face_counter) + ".png", faceColor);
        face_counter++;
    }

    std::vector<Rect> bodies;
    //-- Detect bodies
    body_cascade.detectMultiScale( frame_gray, bodies, 1.1, 2, 0|CASCADE_SCALE_IMAGE, Size(100, 100) );

    for ( size_t i = 0; i < bodies.size(); i++ )
    {        
        Mat faceColor = frame( bodies[i] );
        
        imwrite("body-pics/capture-" + to_string(body_counter) + ".png", faceColor);
        body_counter++;       
        
    }
    
}
