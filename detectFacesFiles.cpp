#include "opencv2/objdetect/objdetect.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

#include <iostream>
#include <unistd.h>

using namespace std;
using namespace cv;

void findFaces( Mat, char* );

/** Global variables */
String face_cascade_name = "/usr/local/share/OpenCV/haarcascades/haarcascade_frontalface_alt.xml";
CascadeClassifier face_cascade;
int face_counter = 1;

int main( int argc, char** argv )
{
    if( argc != 2)
    {
        cout <<" Usage: display_image ImageToLoadAndDisplay" << endl;
        return -1;
    }
    
    if( !face_cascade.load( face_cascade_name ) ){ printf("--(!)Error loading face cascade\n"); return -1; };

    Mat image;
    image = imread(argv[1], CV_LOAD_IMAGE_COLOR);   // Read the file

    if(! image.data )                              // Check for invalid input
    {
        cout <<  "Could not open or find the image" << std::endl ;
        return -1;
    }
    
    findFaces(image, argv[1]);                                    // Wait for a keystroke in the window
    return 0;
}

void findFaces( Mat frame, char* filename)
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
        string nombre = "submitted-face-pics/" + string(filename) + "-face-" + to_string(face_counter) + ".png";
        cout << nombre << endl;
        imwrite(nombre, faceColor);
        face_counter++;
    }
}
