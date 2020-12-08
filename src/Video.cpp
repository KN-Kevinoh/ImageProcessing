#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>

#include <string>

#include "Video.h"

using namespace cv;
using namespace std;

Video::Video()
{
    //ctor
}

Video::~Video()
{
    //dtor
}

void Video::playVideoFromFile()
{
     // open the video file for reading
     VideoCapture video_capture(N_VIDEO);

     if(video_capture.isOpened() == false)
     {
        cout << "Couldn't open the videao file" << endl;
        cin.get();
        exit(EXIT_FAILURE);
     }

     //Start videao in the middle
     //video_capture.set(CAP_PROP_POS_MSEC, 300);

     //get the frame rate of the video (fréquence d'images)
     double fps = video_capture.get(CAP_PROP_FPS);
     cout << "Frames per seconds : " << fps << endl;

     //Frames number
     cout << "Nombre de frames de la video : " << video_capture.get(CAP_PROP_FRAME_COUNT) << endl;

     String n_window = "My Video";
     namedWindow(n_window, WINDOW_NORMAL);

     while(true)
     {
        Mat frame;
        bool b_success = video_capture.read(frame); // read new frame from video

        if(b_success == false)
        {
            cout << "Found the end of the video" << endl;
            break;
        }

         //show the frame in the create window
         imshow(n_window, frame);

         //wait for 10ms until any key is press
         //if 'Esc' break the loop
         //if any other continue the loop
         //if any key not pressedin 10ms, continue the loop
         if(waitKey(10) == 27)
         {
            cout << "Esc key is pressed by user. Stopping the video" << endl;
            break;
         }
     }

}


void Video::saveVideoFile(VideoWriter videoWriter, Mat frames)
{
    // Write frames to file
    videoWriter.write(frames);

    return;

}

// this fuction create and initialize the videowriter object
VideoWriter Video::initVideoWriter(VideoCapture video_file)
{
    int frame_width = video_file.get(CAP_PROP_FRAME_WIDTH);
    int frame_height = video_file.get(CAP_PROP_FRAME_HEIGHT);

    Size frame_size(frame_width, frame_height);
    int frame_per_second = 10;

    //fourcc - 4-character code of the codec which is used to compress the video.
    VideoWriter onVideoWriter("backupMedia/myVideo.avi", VideoWriter::fourcc('M','J','P','G'), frame_per_second, frame_size, true);

    // check if videoWriter successful initialize
    if(!onVideoWriter.isOpened())
    {
        exit(EXIT_FAILURE);
    }

    return onVideoWriter;
}

void Video::playVideoFromCamera()
{
    VideoCapture video_capture(0); //open the default video camera

    if(!video_capture.isOpened())
    {
        cout << " Couldn't open the video camera" << endl;
        cin.get();
        exit(EXIT_FAILURE);
    }
    // Get width and heigth of the frame
    double frame_width = video_capture.get(CAP_PROP_FRAME_WIDTH);
    double frame_height = video_capture.get(CAP_PROP_FRAME_HEIGHT);

    cout << "Resolution of the video : " << frame_width << " x " << frame_height << endl;
    cout << "Rate of images : " << video_capture.get(CAP_PROP_FPS) << endl;

    //VideoWriter onVideoWriter = initVideoWriter(video_capture);

    String n_window = "My Camera";
    namedWindow(n_window);

    while(true)
    {
        Mat frame;
        bool b_success = video_capture.read(frame);
        //break if the frame cannot be captured
        if(b_success == false)
        {
            cout << "Video camera is disconnected" << endl;
            cin.get();
            break;
        }

        //write video frame to the file
        //saveVideoFile(onVideoWriter, frame);

        // Show the frame
        imshow(n_window, frame);

        if( waitKey(10) == 27 )
        {
            cout << "Esc key is pressed. Stopping the video" << endl;
            break;
        }
    }
    //Flush and close the video file
   // onVideoWriter.release();
}


void Video::changeBrightnessOfVideo()
{
    VideoCapture video_file(N_VIDEO);

    if(video_file.isOpened() == false)
    {
        cout << "Couldn't open the video file" << endl;
        cin.get();
        exit(EXIT_FAILURE);
    }

    //windows names for video
    String n_window_original_image = "Original Video";
    String n_window_brightness_high_50 = "Video Brightness Increase by 50";
    String n_window_brightness_high_100 = "Video Brightness Increase by 100";
    String n_window_brightness_low_50 = "Video Brightness Decrease by 50";
    String n_window_brightness_low_100 = "Video Brightness Decrease by 100";

    // Windows created
    namedWindow(n_window_original_image, WINDOW_NORMAL);
    namedWindow(n_window_brightness_high_50, WINDOW_NORMAL);
    namedWindow(n_window_brightness_high_100, WINDOW_NORMAL);
    namedWindow(n_window_brightness_low_50, WINDOW_NORMAL);
    namedWindow(n_window_brightness_low_100, WINDOW_NORMAL);

    while(true)
    {
        Mat frame;
        bool b_success = video_file.read(frame);

        if(b_success == false)
        {
            cout << "Found the end of the video" << endl;
            break;
        }

        // Increase brightness by 50
        Mat frame_brightness_high_50;
        frame.convertTo(frame_brightness_high_50, -1, 1, 50);

        // Increase brightness by 100
        Mat frame_brightness_high_100;
        frame.convertTo(frame_brightness_high_100, -1, 1, 100);

        // Decrease brightness by 50
        Mat frame_brightness_low_50;
        frame.convertTo(frame_brightness_low_50, -1, 1, -50);

        // Decrease brightness by 100
        Mat frame_brightness_low_100;
        frame.convertTo(frame_brightness_low_100, -1, 1, -100);

        // Show videos for each windows
        imshow(n_window_original_image, frame);
        imshow(n_window_brightness_high_50, frame_brightness_high_50);
        imshow(n_window_brightness_high_100, frame_brightness_high_100);
        imshow(n_window_brightness_low_50, frame_brightness_low_50);
        imshow(n_window_brightness_low_100, frame_brightness_low_100);

        if(waitKey(10) == 27)
        {
            cout << "Esc key is pressed by user. Stopping the video" << endl;
            break;
        }
    }
}


void Video::changeContrastOfVideo()
{
     VideoCapture video_file(N_VIDEO);

    if(video_file.isOpened() == false)
    {
        cout << "Couldn't open the video file" << endl;
        cin.get();
        exit(EXIT_FAILURE);
    }

    //windows names for video
    String n_window_original_image = "Original Video";
    String n_window_contrast_high_2 = "Video Contrast Increase by 2";
    String n_window_contrast_high_4 = "Video Contrast Increase by 4";
    String n_window_contrast_low_0_5 = "Video Contrast Decrease by 0.5";
    String n_window_contrast_low_0_25 = "Video Contrast Decrease by 0.25";

    // Windows created
    namedWindow(n_window_original_image, WINDOW_NORMAL);
    namedWindow(n_window_contrast_high_2, WINDOW_NORMAL);
    namedWindow(n_window_contrast_high_4, WINDOW_NORMAL);
    namedWindow(n_window_contrast_low_0_5, WINDOW_NORMAL);
    namedWindow(n_window_contrast_low_0_25, WINDOW_NORMAL);

    while(true)
    {
        Mat frame;
        bool b_success = video_file.read(frame);

        if(b_success == false)
        {
            cout << "Found the end of the video" << endl;
            break;
        }

        // Increase contrast by 50
        Mat frame_contrast_high_2;
        frame.convertTo(frame_contrast_high_2, -1, 2, 0);

        // Increase brightness by 100
        Mat frame_contrast_high_4;
        frame.convertTo(frame_contrast_high_4, -1, 4, 0);

        // Decrease brightness by 50
        Mat frame_contrast_low_0_5;
        frame.convertTo(frame_contrast_low_0_5, -1, 0.5, 0);

        // Decrease brightness by 100
        Mat frame_contrast_low_0_25;
        frame.convertTo(frame_contrast_low_0_25, -1, 1, -100);

        // Show videos for each windows
        imshow(n_window_original_image, frame);
        imshow(n_window_contrast_high_2, frame_contrast_high_2);
        imshow(n_window_contrast_high_4, frame_contrast_high_4);
        imshow(n_window_contrast_low_0_5, frame_contrast_low_0_5);
        imshow(n_window_contrast_low_0_25, frame_contrast_low_0_25);

        if(waitKey(10) == 27)
        {
            cout << "Esc key is pressed by user. Stopping the video" << endl;
            break;
        }
    }
}

/** Linear Filter */

void Video::homogeneousBlurOfVideo()
{
    VideoCapture video_file(N_VIDEO);

    if(video_file.isOpened() == false)
    {
        cout << "Couldn't open or find the video";
        cin.get();
        exit(EXIT_FAILURE);
    }

    // Windows names
    String n_window = "Original Video";
    String n_window_video_blurred_with_5x5_kernel = "Video Blurred with 5 x 5 Kernel";

    // Create Windows
    namedWindow(n_window, WINDOW_NORMAL);
    namedWindow(n_window_video_blurred_with_5x5_kernel, WINDOW_NORMAL);

    while(true)
    {
        Mat frame;
        bool b_success = video_file.read(frame); // read new frame from video
        if(b_success == false)
        {
            cout << "Found the end of video" << endl;
            break;
        }

        Mat frame_blurred_with_5x5_kernel;
        blur(frame, frame_blurred_with_5x5_kernel, Size(5, 5));

        // Show Videos
        imshow(n_window, frame);
        imshow(n_window_video_blurred_with_5x5_kernel, frame_blurred_with_5x5_kernel);

        if(waitKey(10) == 27)
        {
            cout << "Esc key is pressed by used. Stopping the video" << endl;
            break;
        }

    }

}

void Video::gaussianBlurOfVideo()
{
    VideoCapture video_file(N_VIDEO);

    if(video_file.isOpened() == false)
    {
        cout << "Couldn't open or find the video" << endl;
        cin.get();
        exit(EXIT_FAILURE);
    }
    // Define & create windows
    String n_window = "Original Video";
    String n_window_blurred_with_5x5_kernel = "Video Blurred With 5 x 5 Gaussian Kernel";

    namedWindow(n_window, WINDOW_NORMAL);
    namedWindow(n_window_blurred_with_5x5_kernel, WINDOW_NORMAL);

    while(true)
    {
        Mat frame;
        bool b_success = video_file.read(frame); // Get a new frame from video
        if(b_success == false)
        {
            cout << "Found the of the video" << endl;
            break;
        }

        // Blur the frame with 5x5 Gaussian Kernel
        Mat frame_blurred_with_5x5_kernel;
        GaussianBlur(frame, frame_blurred_with_5x5_kernel, Size(5, 5), 0);

        // Show the video
        imshow(n_window, frame);
        imshow(n_window_blurred_with_5x5_kernel, frame_blurred_with_5x5_kernel);

        if(waitKey(10) == 27)
        {
            cout << "Esc key is pressed by user. Stopping the video" << endl;
            break;
        }
    }
}

/**
* Non Linear filter
*/

void Video::erodeVideo()
{
      VideoCapture cap(N_VIDEO);

    // if not success, exit program
    if (cap.isOpened() == false)
    {
        cout << "Cannot open the video file" << endl;
        cin.get(); //wait for any key press
        return exit(EXIT_FAILURE);
    }



    //Define names of the window
    String window_name_of_original_video = "Original Video";
    String window_name_of_video_eroded_with_5x5_kernel = "Video eroded with 5 x 5 kernel";

    // Create a window with above names
    namedWindow(window_name_of_original_video, WINDOW_NORMAL);
    namedWindow(window_name_of_video_eroded_with_5x5_kernel, WINDOW_NORMAL);

    while (true)
    {
        Mat frame;
        bool bSuccess = cap.read(frame); // read a new frame from video
        if (bSuccess == false)
        {
            cout << "Found the end of the video" << endl;
            break;
        }

        //erode the frame with 5x5 kernel
        Mat frame_eroded_with_5x5_kernel;
        erode(frame, frame_eroded_with_5x5_kernel, getStructuringElement(MORPH_RECT, Size(5, 5)));

        //show the frames in the created windows
        imshow(window_name_of_original_video, frame);
        imshow(window_name_of_video_eroded_with_5x5_kernel, frame_eroded_with_5x5_kernel);

        //wait for for 10 ms until any key is pressed.

        if (waitKey(10) == 27)
        {
            cout << "Esc key is pressed by user. Stoppig the video" << endl;
            break;
        }
    }
}

/********** Object tracking **/
void Video::ObjectTrackingFromWebcam()
{
      VideoCapture cap(0); //capture the video from webcam

    if ( !cap.isOpened() )  // if not success, exit program
    {
         cout << "Cannot open the web cam" << endl;
         return exit(EXIT_FAILURE);
    }

 namedWindow("Control", CV_WINDOW_AUTOSIZE); //create a window called "Control"

 int iLowH = 170;
 int iHighH = 179;

 int iLowS = 150;
 int iHighS = 255;

 int iLowV = 60;
 int iHighV = 255;

 //Create trackbars in "Control" window
 createTrackbar("LowH", "Control", &iLowH, 179); //Hue cad teinte en francais (0 - 179)
 createTrackbar("HighH", "Control", &iHighH, 179);

 createTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
 createTrackbar("HighS", "Control", &iHighS, 255);

 createTrackbar("LowV", "Control", &iLowV, 255);//Value (0 - 255)
 createTrackbar("HighV", "Control", &iHighV, 255);

 int iLastX = -1;
 int iLastY = -1;

 //Capture a temporary image from the camera
 Mat imgTmp;
 cap.read(imgTmp);

 //Create a black image with the size as the camera output
 Mat imgLines = Mat::zeros( imgTmp.size(), CV_8UC3 );


    while (true)
    {
        Mat imgOriginal;

        bool bSuccess = cap.read(imgOriginal); // read a new frame from video



         if (!bSuccess) //if not success, break loop
        {
             cout << "Cannot read a frame from video stream" << endl;
             break;
        }

      Mat imgHSV;

      cvtColor(imgOriginal, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

      Mat imgThresholded;

      inRange(imgHSV, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), imgThresholded); //Threshold the image

      //morphological opening (removes small objects from the foreground)
      erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
      dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

      //morphological closing (removes small holes from the foreground)
      dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );
      erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(5, 5)) );

      //Calculate the moments of the thresholded image
      Moments oMoments = moments(imgThresholded);

      double dM01 = oMoments.m01;
      double dM10 = oMoments.m10;
      double dArea = oMoments.m00;

      // if the area <= 10000, I consider that the there are no object in the image and it's because of the noise, the area is not zero
      if (dArea > 10000)
      {
       //calculate the position of the ball
       int posX = dM10 / dArea;
       int posY = dM01 / dArea;

       if (iLastX >= 0 && iLastY >= 0 && posX >= 0 && posY >= 0)
       {
        //Draw a red line from the previous point to the current point
        line(imgLines, Point(posX, posY), Point(iLastX, iLastY), Scalar(0,0,255), 2);
       }

       iLastX = posX;
       iLastY = posY;
      }


      imgOriginal = imgOriginal + imgLines;
      imshow("Original", imgOriginal); //show the original image

            if (waitKey(30) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
           {
                cout << "esc key is pressed by user" << endl;
                break;
           }
        }
}

