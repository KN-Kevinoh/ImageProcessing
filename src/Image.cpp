#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui.hpp>
#include <string>


#include "Image.h"


using namespace cv;
using namespace std;

/** global variable **/



Mat src; Mat dst, src_gray;
char window_name[] = "Smoothing";
int display_caption( const char* caption );
int display_dst( int delay );

int threshold_value = 0;
int threshold_type = 3;;


int morph_elem = 0;
int morph_size = 0;
int morph_operator = 0;


char* windows_name = "Threshold";

char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
char* trackbar_value = "Value";
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);


Image::Image()
{
    Image::filename = N_IMAGE;
    my_image = imread(N_IMAGE);
}

Image::Image(string filename)
{
    Image::filename = filename;
    my_image = imread(N_IMAGE);
}

Image::~Image()
{
    //dtor
}

void Image::set_filename(string filename)
{
    Image::filename = filename;

}

void Image::set_my_image()
{
    my_image = imread(Image::filename);
}

/** check existing image file */
void Image::imageNotExist(cv::Mat file)
{
    if(file.empty())
    {
        cout << "Couldn't open or file not found" << endl;
        cin.get();
        exit(EXIT_FAILURE);
    }
}

 /** display image */
void Image::displayImage(char* n_window)
{
    imageNotExist(my_image);
    saveImageFile(my_image,"image_gray");
    showINwindow(n_window, my_image);
}

/**
 *       image color 800*600 initialize with (100,250,30)
 *       for BGR
*/

void Image::displayBlankImage(char* n_window,long height, long width)
{
   // my_image(height, width, CV_8UC3, Scalar(100, 250, 30));
    saveImageFile(my_image,"white_black");
    showINwindow(n_window, my_image);
}

/**  Save file */
void Image::saveImageFile(Mat file_image,string filename)
{
    // depth must be 8 or 16 bits and channel 1 or 3
    // if not, use Mat::convertTo and cv::cvtColor functions to convert your image.
    string dir = "backupMedia/";
    string ext = ".jpg";
    string fichier = filename + ext;
    string rep_fichier = dir + fichier;
    bool is_success = imwrite(rep_fichier,file_image);

    if(!is_success)
    {
        cout << "Failed to save the image" << endl;
        cin.get();
        exit(EXIT_FAILURE);
    }

    cout << "Image successful save" << endl;

}


/** create window and display image */
void Image::showINwindow(char* n_window, Mat file_image)
{
    namedWindow(n_window);
    imshow(n_window, file_image);
    waitKey(0);
    //de-allocate any memory
    destroyWindow(n_window);
}


void Image::histogramme()
{
    Mat image = my_image;
	vector<Mat> recupRGB;
	split( image, recupRGB);
	int tailleHisto = 256;
	float intervalle[] = { 0, 256 } ;
	const float* intervalleHisto = { intervalle };
	int largeurHisto = 512; int hauteurHisto = 500;
	int pas = 2;
	Mat histImage(hauteurHisto, largeurHisto, CV_8UC3, Scalar( 255,255,255));
	Mat HistRouge,HistVert,HistBleu;

	calcHist( &recupRGB[0], 1, 0, Mat(),HistBleu , 1, &tailleHisto, &intervalleHisto, true, false);
	normalize(HistBleu,HistBleu, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	calcHist( &recupRGB[1], 1, 0, Mat(), HistVert, 1, &tailleHisto, &intervalleHisto, true, false);
	normalize(HistVert,HistVert, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	calcHist( &recupRGB[2], 1, 0, Mat(), HistRouge, 1, &tailleHisto, &intervalleHisto, true, false);
	normalize(HistRouge,HistRouge, 0, histImage.rows, NORM_MINMAX, -1, Mat());

	//Tracage de l'histogramme en rectangle
	for( int i = 0; i < tailleHisto; i++ )
	{
		rectangle(histImage, Point( pas*(i), hauteurHisto) ,Point( pas*(i+1), hauteurHisto - cvRound(HistBleu.at<float>(i)) ),Scalar( 255, 0, 0), 2, 8, 0 );

		rectangle(histImage, Point( pas*(i), hauteurHisto) ,Point( pas*(i+1), hauteurHisto - cvRound(HistVert.at<float>(i)) ),Scalar( 0, 255, 0), 2, 8, 0 );

		rectangle(histImage, Point( pas*(i), hauteurHisto) ,Point( pas*(i+1), hauteurHisto - cvRound(HistRouge.at<float>(i)) ),Scalar( 0, 0, 255), 2, 8, 0 );
	}

    imshow("Original image",image);
    saveImageFile(histImage,"image_histo");
    imshow("Histogram Image", histImage);

    waitKey(0); // Wait for any key pressed

    destroyAllWindows(); // Destroy all active windows

}

Mat tracerTrait(Mat image, int type, int numero){

	Point debut, fin;

	if (type==1){

		debut.x = 0;
		debut.y = numero;
		fin.x = image.cols;
		fin.y = numero;
	}
	else if(type==2){
		debut.x = numero;
		debut.y = 0;
		fin.x = numero;
		fin.y = image.rows;
	}

	line(image, debut, fin, Scalar(0, 0, 255), 1, 8);

	return image;
}


void Image::profilIntensiteImage()
{
    Mat image = tracerTrait(Image::my_image, 1 , 200);
    int type = 1;
    int numero = 10;
	Point premierPoint, deuxiemePoint;
    int largeur_fenetre_courbe;
    Vec3b valeurPixelDeb;
    Vec3b valeurPixelFin;
	if(type==1){
		largeur_fenetre_courbe = image.cols;
	}
	else if(type==2){
		largeur_fenetre_courbe = image.rows;
	}

		Mat courbe_profil (256,largeur_fenetre_courbe,CV_8UC3,Scalar(255,255,255));

		for(int i = 0; i < largeur_fenetre_courbe-1; i++)
		{
			if(type==1){
		    valeurPixelDeb  = image.at<Vec3b>(numero, i);
		    valeurPixelFin = image.at<Vec3b>(numero,i+1);
			}
			else if(type==2){
			valeurPixelDeb  = image.at<Vec3b>(i, numero);
			valeurPixelFin = image.at<Vec3b>(i+1,numero);
			}

			for(int j = 0; j < 3; j++)
			{
				premierPoint.x = i;
				deuxiemePoint.x = i+1;
				premierPoint.y = 255 - valeurPixelDeb.val[j];
				deuxiemePoint.y = 255 - valeurPixelFin.val[j];

				if(j==0) line(courbe_profil, premierPoint, deuxiemePoint, Scalar(255, 0, 0), 1, 8);

				if(j==1) line(courbe_profil, premierPoint, deuxiemePoint, Scalar(0, 255, 0), 1, 8);

				if(j==2) line(courbe_profil, premierPoint, deuxiemePoint, Scalar(0, 0, 255), 1, 8);
			}

		}

		imshow("Original image",image);
        saveImageFile(my_image,"image_with_line");
        imshow("Profil intensity of image",courbe_profil);
        saveImageFile(courbe_profil,"profil_intensity");
        waitKey(0); // Wait for any key pressed

        destroyAllWindows(); // Destroy all active windows
    }


void Image::correctionGamma(){
    Mat image = my_image;
    float gamma = 2;
	Mat sortie(image.rows, image.cols, CV_8UC3, Scalar( 255,255,255));

    for(int i = 0; i < image.rows; i++){

        for(int j = 0; j < image.cols; j++){

            for(int c = 0; c < 3; c++){

					int val = image.at<Vec3b>(i,j)[c];

					if(val < 0) val = 0;
    				else if(val > 255) val =255;
    				else if(0 <= val && val <= 255)
						val = pow((val/255.0),gamma)*255.0;
               sortie.at<Vec3b>(i,j)[c] = saturate_cast<uchar>(val);
            }
        }
    }
    imshow("Original image",image);
    imshow("Gamma correction of image", sortie);
    saveImageFile(sortie, "gamma");
    waitKey(0); // Wait for any key pressed

    destroyAllWindows(); // Destroy all active windows
}


/** change brigthness */
void  Image::changeBrightnessOfImage()
{
    Mat image = imread(N_IMAGE);

    if(image.empty())
    {
        cout << "Couldn't open or find image";
        cin.get();
        exit(EXIT_FAILURE);
    }

    // Increase brightness by 50
    Mat image_brightness_high_50;
    image.convertTo(image_brightness_high_50, -1, 1, 50);

    // Increase brightness by 100
    Mat image_brightness_high_100;
    image.convertTo(image_brightness_high_100, -1, 1, 100);

    // Decrease brightness by 50
    Mat image_brightness_low_50;
    image.convertTo(image_brightness_low_50, -1, 1, -50);

    // Decrease brightness by 100
    Mat image_brightness_low_100;
    image.convertTo(image_brightness_low_100, -1, 1, -100);

    //windows names for images
    String n_window_original_image = "Original Image";
    String n_window_brightness_high_50 = "Image Brightness Increase by 50";
    String n_window_brightness_high_100 = "Image Brightness Increase by 100";
    String n_window_brightness_low_50 = "Image Brightness Decrease by 50";
    String n_window_brightness_low_100 = "Image Brightness Decrease by 100";

    // Windows created
    namedWindow(n_window_original_image, WINDOW_NORMAL);
    namedWindow(n_window_brightness_high_50, WINDOW_NORMAL);
    namedWindow(n_window_brightness_high_100, WINDOW_NORMAL);
    namedWindow(n_window_brightness_low_50, WINDOW_NORMAL);
    namedWindow(n_window_brightness_low_100, WINDOW_NORMAL);

    // Show images for each windows
    imshow(n_window_original_image, image);
    imshow(n_window_brightness_high_50, image_brightness_high_50);
    imshow(n_window_brightness_high_100, image_brightness_high_100);
    imshow(n_window_brightness_low_50, image_brightness_low_50);
    imshow(n_window_brightness_low_100, image_brightness_low_100);

    waitKey(0); // Wait for any key pressed

    destroyAllWindows(); // Destroy all active windows

}

void Image::changeContrastOfImage()
{
    Mat image = imread(N_IMAGE);

    if(image.empty())
    {
        cout << "Couldn't open or find the image" << endl;
        cin.get();
        exit(EXIT_FAILURE);
    }

    // Increase contrast by 2
    Mat image_contrast_high_2;
    image.convertTo(image_contrast_high_2, -1, 2, 0);

    // Increase contrast by 4
    Mat image_contrast_high_4;
    image.convertTo(image_contrast_high_4, -1, 4, 0);

    // Decrease contrast by 0.5
    Mat image_contrast_low_0_5;
    image.convertTo(image_contrast_low_0_5, -1, 0.5, 0);

    // Decrease contrast by 0.25
    Mat image_contrast_low_0_25;
    image.convertTo(image_contrast_low_0_25, -1, 0.25, 0);

    //windows names for images
    String n_window_original_image = "Original Image";
    String n_window_contrast_high_2 = "Image Contrast Increase by 2";
    String n_window_contrast_high_4 = "Image Contrast Increase by 4";
    String n_window_contrast_low_0_5 = "Image Contrast Decrease by 0.5";
    String n_window_contrast_low_0_25 = "Image Contrast Decrease by 0.25";

    // Windows created
    namedWindow(n_window_original_image, WINDOW_NORMAL);
    namedWindow(n_window_contrast_high_2, WINDOW_NORMAL);
    namedWindow(n_window_contrast_high_4, WINDOW_NORMAL);
    namedWindow(n_window_contrast_low_0_5, WINDOW_NORMAL);
    namedWindow(n_window_contrast_low_0_25, WINDOW_NORMAL);

    // Show images for each windows
    imshow(n_window_original_image, image);
    imshow(n_window_contrast_high_2, image_contrast_high_2);
    saveImageFile(image_contrast_high_2,"contrast_2");
    imshow(n_window_contrast_high_4, image_contrast_high_4);
     saveImageFile(image_contrast_high_4,"contrast_4");
    imshow(n_window_contrast_low_0_5, image_contrast_low_0_5);
     saveImageFile(image_contrast_low_0_5,"contrast_0_5");
    imshow(n_window_contrast_low_0_25, image_contrast_low_0_25);
     saveImageFile(image_contrast_low_0_25,"contrast_0_25");

    waitKey(0); // Wait for any key pressed

    destroyAllWindows(); // Destroy all active windows

}

/** equalize image */
// Histogram EqualizationHistogram Equalization of a Grayscale image

void Image::equalizeHistOfImageToGrayscale()
{
    Mat image = imread(N_IMAGE); // read the image file

    //check for failure
    if(image.empty())
    {
        cout << "Couldn't open or find the image" << endl;
        cin.get();
        exit(EXIT_FAILURE);
    }

    // Change the color image to grayscale image
    cvtColor(image, image, COLOR_BGR2GRAY);

    // Equalize the histogram
    Mat hist_equalized_image;
    equalizeHist(image, hist_equalized_image);

    // Define names of windows
    String n_window_original_image = "Original Image";
    String n_window_histogram_equalized = "Histogram Equalized Image";

    // Create windows
    namedWindow(n_window_original_image, WINDOW_NORMAL);
    namedWindow(n_window_histogram_equalized, WINDOW_NORMAL);

    saveImageFile(hist_equalized_image,"image_eq");
    // Show images
    imshow(n_window_original_image, image);
    imshow(n_window_histogram_equalized, hist_equalized_image);

    waitKey(0); // Wait for key press to exit

    destroyAllWindows(); // destroy all open windows
}

//Histogram Equalization of a Color image with OpenCV

void Image::equalizeHistOfColorImage()
{
    Mat image = imread(N_IMAGE);

    if(image.empty())
    {
        cout << "Couldn't open or find the image" << endl;
        cin.get();
        exit(EXIT_FAILURE);
    }

    // Convert the image from BGR to YCrCb color space
    Mat hist_equalize_image;
    cvtColor(image, hist_equalize_image, COLOR_BGR2YCrCb);

    // Split the image into 3 channels: Y, Cr and Cb, and store it in std::vector data type
    vector<Mat> vec_channels;
    split(hist_equalize_image, vec_channels);

    // Equalize the histogram of only Y channel
    equalizeHist(vec_channels[0], vec_channels[0]);

    // Merge 3 channels in the vector to form the color image in YCrCb color space
    merge(vec_channels, hist_equalize_image);

    //convert the histogram equalized image from YCrCb to BGR color space again
    cvtColor(hist_equalize_image, hist_equalize_image, COLOR_YCrCb2BGR);

    // Windows names
    String n_window_original_image = "Original Image";
    String n_window_histogram_equalized_image = "Histogram Equalized_image";

    // Create Windows
    namedWindow(n_window_original_image, WINDOW_NORMAL);
    namedWindow(n_window_histogram_equalized_image, WINDOW_NORMAL);

    // Show images in windows
    imshow(n_window_original_image, image);
    imshow(n_window_histogram_equalized_image, hist_equalize_image);
    saveImageFile(hist_equalize_image,"image_eq_color");
    waitKey(0); // Exit after any key pressed

    destroyAllWindows(); // destroy all active windows

}

/**
 *Linear Filter
 */

/** homogenious blur */
void Image::homogeneousBlurOfImage()
{
    Mat image = imread(N_IMAGE);

    if(image.empty())
    {
        cout << "Couldn't open or find the image" << endl;
        cin.get();
        exit(EXIT_FAILURE);
    }

    // Blur the image with 7x7
    Mat image_blurred_with_7x7_kernel;
    blur(image, image_blurred_with_7x7_kernel, Size(7, 7));

    // Blur the image with 5x5 kernel
    Mat image_blurred_with_5x5_kernel;
    blur(image, image_blurred_with_5x5_kernel, Size(5, 5));

    // Windows names
    String n_window = "Original Image";
    String n_window_blurred_with_7x7_kernel = "Image Blurred with 7 x 7 Kernel";
    String n_window_blurred_with_5x5_kernel = "Image Blurred with 5 x 5 Kernel";

    // Create windows
    namedWindow(n_window, WINDOW_NORMAL);
    namedWindow(n_window_blurred_with_7x7_kernel, WINDOW_NORMAL);
    namedWindow(n_window_blurred_with_5x5_kernel, WINDOW_NORMAL);

    // Show our images
    imshow(n_window, image);
    imshow(n_window_blurred_with_7x7_kernel, image_blurred_with_7x7_kernel);
    saveImageFile(image_blurred_with_7x7_kernel,"moy_7");
    imshow(n_window_blurred_with_5x5_kernel, image_blurred_with_5x5_kernel);
    saveImageFile(image_blurred_with_5x5_kernel,"moy_5");

    waitKey(0);

    destroyAllWindows();
}


/** gaussian blur */
void Image::gaussianBlurOfImage()
{
    Mat image = imread(N_IMAGE);

    if(image.empty())
    {
        cout << "Couldn't open or find the image" << endl;
        cin.get();
        exit(EXIT_FAILURE);
    }

    // Blur the image with 3x3 Gaussian Kernel
    Mat image_blurred_with_3x3_kernel;
    GaussianBlur(image, image_blurred_with_3x3_kernel, Size(3, 3), 0);

    // Blur the image with 5x5 Gaussian Kernel
    Mat image_blurred_with_5x5_kernel;
    GaussianBlur(image, image_blurred_with_5x5_kernel, Size(5, 5), 0);

    // Windows names
    String n_window = "Original Image";
    String n_window_blurred_with_3x3_kernel = "Image Blurred with 3 x 3 Gaussian Kernel";
    String n_window_blurred_with_5x5_kernel = "Image Blurred with 5 x 5 Gaussian Kernel";

    // Create windows
    namedWindow(n_window, WINDOW_NORMAL);
    namedWindow(n_window_blurred_with_3x3_kernel, WINDOW_NORMAL);
    namedWindow(n_window_blurred_with_5x5_kernel, WINDOW_NORMAL);

    // Show the images
    imshow(n_window, image);
    imshow(n_window_blurred_with_3x3_kernel, image_blurred_with_3x3_kernel);
    saveImageFile(image_blurred_with_3x3_kernel, "g_3");
    imshow(n_window_blurred_with_5x5_kernel, image_blurred_with_5x5_kernel);
    saveImageFile(image_blurred_with_5x5_kernel,"g_5");

    waitKey(0); // Exit after any key pressed

    destroyAllWindows(); // Close all windows
}

/** Invert image*/
void Image::invertImage()
{
    // Load the image
    IplImage* image = cvLoadImage(N_IMAGE);
    namedWindow("Original Image", WINDOW_NORMAL);
    cvShowImage("Original Image", image);

    //Invert Image
    cvNot(image, image);
    namedWindow("Invert Image", WINDOW_NORMAL);
    cvShowImage("Invert Image", image);

    cvWaitKey(0);

    cvDestroyAllWindows();

}
/**********************************************/

/**
* Non Linear filter
*/
void Image::erodeImage()
{
    imageNotExist(my_image);

    //Erode the image with 5x5 kernel
    Mat image_eroded_with_5x5_kernel;
    erode(my_image, image_eroded_with_5x5_kernel, getStructuringElement(MORPH_RECT, Size(5, 5)));

    //Erode the image with 7x7 kernel
    Mat image_eroded_with_7x7_kernel;
    erode(my_image, image_eroded_with_7x7_kernel, getStructuringElement(MORPH_RECT, Size(7, 7)));

    //Define names of the windows
    String window_name = "Lotus";
    String window_name_eroded_with_5x5_kernel = "Image eroded with 5 x 5 kernel";
    String window_name_eroded_with_7x7_kernel = "Image eroded with 7 x 7 kernel";

    // Create windows with above names
    namedWindow(window_name);
    namedWindow(window_name_eroded_with_5x5_kernel);
    namedWindow(window_name_eroded_with_7x7_kernel);

    // Show our images inside the created windows.
    imshow(window_name, my_image);
    imshow(window_name_eroded_with_5x5_kernel, image_eroded_with_5x5_kernel);
    saveImageFile(image_eroded_with_5x5_kernel,"erode_5");
    imshow(window_name_eroded_with_7x7_kernel, image_eroded_with_7x7_kernel);
    saveImageFile(image_eroded_with_7x7_kernel,"erode_7");
    waitKey(0); // Wait for any keystroke in the window

    destroyAllWindows(); //destroy all opened windows
}

void Image::dilateImage()
{
    IplImage* img = cvLoadImage(N_IMAGE);
        cvNamedWindow("Original image");
        cvShowImage("Original image", img);

        //dilate and display the dilated image
        cvDilate(img, img, 0, 5);
        cvNamedWindow("Dilated Image");
        cvShowImage("Dilated Image", img);
        cvWaitKey(0);

        //cleaning up
        cvDestroyAllWindows();

        cvReleaseImage(&img);
}
/***************************/

void Image::brigthnessAndContrastOfImage()
{

   imageNotExist(my_image);

    // Create a window
    namedWindow("Dynamic Transformation", 1);

       //Create trackbar to change brightness
     int iSliderValue1 = 50;
     createTrackbar("Brightness", "Dynamic Transformation", &iSliderValue1, 100);

     //Create trackbar to change contrast
     int iSliderValue2 = 50;
     createTrackbar("Contrast", "Dynamic Transformation", &iSliderValue2, 100);

     while (true)
     {
          //Change the brightness and contrast of the image (For more infomation http://opencv-srf.blogspot.com/2013/07/change-contrast-of-image-or-video.html)
          Mat dst;
          int iBrightness  = iSliderValue1 - 50;
          double dContrast = iSliderValue2 / 50.0;
          my_image.convertTo(dst, -1, dContrast, iBrightness);

          //show the brightness and contrast adjusted image
          imshow("Dynamic Transformation", dst);

          // Wait until user press some key for 50ms
          int iKey = waitKey(50);

          //if user press 'ESC' key
          if (iKey == 27)
          {
               break;
          }
     }
}

void Image::MyCallbackForBrightness(int iValueForBrightness, void *userData)
{
     Mat dst;
     int iValueForContrast = *( static_cast<int*>(userData) );

     //Calculating brightness and contrast value
     int iBrightness = iValueForBrightness - 50;
     double dContrast = iValueForContrast / 50.0;

     //Calculated contrast and brightness value
     //cout << "MyCallbackForBrightness : Contrast=" << dContrast << ", Brightness=" << iBrightness << endl;

     //adjust the brightness and contrast
     my_image.convertTo(dst, -1, dContrast, iBrightness);

     //show the brightness and contrast adjusted image
     imshow("My Window", dst);
}

void Image::MyCallbackForContrast(int iValueForContrast, void *userData)
{
     Mat dst;
     int iValueForBrightness = *( static_cast<int*>(userData) );

     //Calculating brightness and contrast value
     int iBrightness = iValueForBrightness - 50;
     double dContrast = iValueForContrast / 50.0;

     //Calculated contrast and brightness value
     //cout << "MyCallbackForContrast : Contrast=" << dContrast << ", Brightness=" << iBrightness << endl;

     //adjust the brightness and contrast
     my_image.convertTo(dst, -1, dContrast, iBrightness);

     //show the brightness and contrast adjusted image
     imshow("My Window", dst);
}

void CallBackFunc(int event, int x, int y, int flags, void* userdata)
{
     if  ( event == EVENT_LBUTTONDOWN )
     {
          cout << "Left button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
     }
     else if  ( event == EVENT_RBUTTONDOWN )
     {
          cout << "Right button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
     }
     else if  ( event == EVENT_MBUTTONDOWN )
     {
          cout << "Middle button of the mouse is clicked - position (" << x << ", " << y << ")" << endl;
     }
     else if ( event == EVENT_MOUSEMOVE )
     {
          cout << "Mouse move over the window - position (" << x << ", " << y << ")" << endl;

     }
}

void Image::pixelPositionInImage()
{
     //Create a window
     namedWindow("Detect pixel position by mouse", 1);

     //set the callback function for any mouse event
     setMouseCallback("Detect pixel position by mouse", CallBackFunc, NULL);

     //show the image
     imshow("Detect pixel position by mouse", my_image);

     // Wait until user press some key
     waitKey(0);
}

void Image::rotateImage()
{

     //show the original image
     const char* pzOriginalImage = "Original Image";
     namedWindow( pzOriginalImage, CV_WINDOW_AUTOSIZE );
     imshow( pzOriginalImage, my_image);

     const char* pzRotatedImage = "Rotated Image";
     namedWindow( pzRotatedImage, CV_WINDOW_AUTOSIZE );

     int iAngle = 180;
     createTrackbar("Angle", pzRotatedImage, &iAngle, 360);

     int iImageHieght = my_image.rows / 2;
     int iImageWidth = my_image.cols / 2;

     while (true)
     {
          Mat matRotation = getRotationMatrix2D( Point(iImageWidth, iImageHieght), (iAngle - 180), 1 );

          // Rotate the image
          Mat imgRotated;
          warpAffine( my_image, imgRotated, matRotation, my_image.size() );

          imshow( pzRotatedImage, imgRotated );

          int iRet = waitKey(30);
          if ( iRet == 27 )
          {
               break;
          }
     }
}

void Image::ObjectTrackingUsingContour()
{
 IplImage* img =  cvLoadImage(N_IMAGE);

 //show the original image
 cvNamedWindow("Raw");
 cvShowImage("Raw",img);

 //converting the original image into grayscale
 IplImage* imgGrayScale = cvCreateImage(cvGetSize(img), 8, 1);
 cvCvtColor(img,imgGrayScale,CV_BGR2GRAY);

 //thresholding the grayscale image to get better results
 cvThreshold(imgGrayScale,imgGrayScale,128,255,CV_THRESH_BINARY);

 CvSeq* contours;  //hold the pointer to a contour in the memory block
 CvSeq* result;   //hold sequence of points of a contour
 CvMemStorage *storage = cvCreateMemStorage(0); //storage area for all contours

 //finding all contours in the image
 cvFindContours(imgGrayScale, storage, &contours, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));

 //iterating through each contour
 while(contours)
 {
     //obtain a sequence of points of contour, pointed by the variable 'contour'
     result = cvApproxPoly(contours, sizeof(CvContour), storage, CV_POLY_APPROX_DP, cvContourPerimeter(contours)*0.02, 0);

     //if there are 3  vertices  in the contour(It should be a triangle)
    if(result->total==3 )
     {
         //iterating through each point
         CvPoint *pt[3];
         for(int i=0;i<3;i++){
             pt[i] = (CvPoint*)cvGetSeqElem(result, i);

              }

         //drawing lines around the triangle
         cvLine(img, *pt[0], *pt[1], cvScalar(255,0,0),4);
         cvLine(img, *pt[1], *pt[2], cvScalar(255,0,0),4);
         cvLine(img, *pt[2], *pt[0], cvScalar(255,0,0),4);

     }

     //if there are 4 vertices in the contour(It should be a quadrilateral)
     else if(result->total==4 )
     {
         //iterating through each point
         CvPoint *pt[4];
         for(int i=0;i<4;i++){
             pt[i] = (CvPoint*)cvGetSeqElem(result, i);
         }

         //drawing lines around the quadrilateral
         cvLine(img, *pt[0], *pt[1], cvScalar(0,255,0),4);
         cvLine(img, *pt[1], *pt[2], cvScalar(0,255,0),4);
         cvLine(img, *pt[2], *pt[3], cvScalar(0,255,0),4);
         cvLine(img, *pt[3], *pt[0], cvScalar(0,255,0),4);
     }

  //if there are 7  vertices  in the contour(It should be a heptagon)
     else if(result->total ==7  )
     {
         //iterating through each point
         CvPoint *pt[7];
         for(int i=0;i<7;i++){
             pt[i] = (CvPoint*)cvGetSeqElem(result, i);
         }

             //drawing lines around the heptagon
         cvLine(img, *pt[0], *pt[1], cvScalar(0,0,255),4);
         cvLine(img, *pt[1], *pt[2], cvScalar(0,0,255),4);
         cvLine(img, *pt[2], *pt[3], cvScalar(0,0,255),4);
         cvLine(img, *pt[3], *pt[4], cvScalar(0,0,255),4);
         cvLine(img, *pt[4], *pt[5], cvScalar(0,0,255),4);
         cvLine(img, *pt[5], *pt[6], cvScalar(0,0,255),4);
         cvLine(img, *pt[6], *pt[0], cvScalar(0,0,255),4);
     }

     //obtain the next contour
     contours = contours->h_next;
 }

 //show the image in which identified shapes are marked
 cvNamedWindow("Tracked");
 cvShowImage("Tracked",img);

 cvWaitKey(0); //wait for a key press

 //cleaning up
 cvDestroyAllWindows();
 cvReleaseMemStorage(&storage);
 cvReleaseImage(&img);
 cvReleaseImage(&imgGrayScale);

}

void Image::ObjectTrackingUsingContourVersus2()
{
 IplImage* img =  cvLoadImage(N_IMAGE);

 //show the original image
 cvNamedWindow("Original");
 cvShowImage("Original",img);

 //smooth the original image using Gaussian kernel to remove noise
cvSmooth(img, img, CV_GAUSSIAN,3,3);

 //converting the original image into grayscale
 IplImage* imgGrayScale = cvCreateImage(cvGetSize(img), 8, 1);
 cvCvtColor(img,imgGrayScale,CV_BGR2GRAY);

 cvNamedWindow("GrayScale Image");
 cvShowImage("GrayScale Image",imgGrayScale);

 //thresholding the grayscale image to get better results
 cvThreshold(imgGrayScale,imgGrayScale,100,255,CV_THRESH_BINARY_INV);

 cvNamedWindow("Thresholded Image");
 cvShowImage("Thresholded Image",imgGrayScale);

 CvSeq* contour;  //hold the pointer to a contour
 CvSeq* result;   //hold sequence of points of a contour
 CvMemStorage *storage = cvCreateMemStorage(0); //storage area for all contours

 //finding all contours in the image
 cvFindContours(imgGrayScale, storage, &contour, sizeof(CvContour), CV_RETR_LIST, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));

  //iterating through each contour
 while(contour)
 {
  //obtain a sequence of points of the countour, pointed by the variable 'countour'
  result = cvApproxPoly(contour, sizeof(CvContour), storage, CV_POLY_APPROX_DP, cvContourPerimeter(contour)*0.02, 0);

  //if there are 3 vertices  in the contour and the area of the triangle is more than 100 pixels
  if(result->total==3 && fabs(cvContourArea(result, CV_WHOLE_SEQ))>100 )
  {
   //iterating through each point
   CvPoint *pt[3];
   for(int i=0;i<3;i++){
    pt[i] = (CvPoint*)cvGetSeqElem(result, i);
   }

   //drawing lines around the triangle
   cvLine(img, *pt[0], *pt[1], cvScalar(255,0,0),4);
   cvLine(img, *pt[1], *pt[2], cvScalar(255,0,0),4);
   cvLine(img, *pt[2], *pt[0], cvScalar(255,0,0),4);

  }

  //obtain the next contour
  contour = contour->h_next;
 }

 //show the image in which identified shapes are marked
 cvNamedWindow("Tracked");
 cvShowImage("Tracked",img);

 cvWaitKey(0); //wait for a key press


 //cleaning up
 cvDestroyAllWindows();
 cvReleaseMemStorage(&storage);
 cvReleaseImage(&img);
 cvReleaseImage(&imgGrayScale);

}

void Image::DFTOnImage()
{

    Mat I = imread(filename, IMREAD_GRAYSCALE);
    if( I.empty()){
        cout << "Error opening image" << endl;
        return exit(EXIT_FAILURE);
    }
    Mat padded;                            //expand input image to optimal size
    int m = getOptimalDFTSize( I.rows );
    int n = getOptimalDFTSize( I.cols ); // on the border add zero values
    copyMakeBorder(I, padded, 0, m - I.rows, 0, n - I.cols, BORDER_CONSTANT, Scalar::all(0));
    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    Mat complexI;
    merge(planes, 2, complexI);         // Add to the expanded another plane with zeros
    dft(complexI, complexI);            // this way the result may fit in the source matrix
    // compute the magnitude and switch to logarithmic scale
    // => log(1 + sqrt(Re(DFT(I))^2 + Im(DFT(I))^2))
    split(complexI, planes);                   // planes[0] = Re(DFT(I), planes[1] = Im(DFT(I))
    magnitude(planes[0], planes[1], planes[0]);// planes[0] = magnitude
    Mat magI = planes[0];
    magI += Scalar::all(1);                    // switch to logarithmic scale
    log(magI, magI);
    // crop the spectrum, if it has an odd number of rows or columns
    magI = magI(Rect(0, 0, magI.cols & -2, magI.rows & -2));
    // rearrange the quadrants of Fourier image  so that the origin is at the image center
    int cx = magI.cols/2;
    int cy = magI.rows/2;
    Mat q0(magI, Rect(0, 0, cx, cy));   // Top-Left - Create a ROI per quadrant
    Mat q1(magI, Rect(cx, 0, cx, cy));  // Top-Right
    Mat q2(magI, Rect(0, cy, cx, cy));  // Bottom-Left
    Mat q3(magI, Rect(cx, cy, cx, cy)); // Bottom-Right
    Mat tmp;                           // swap quadrants (Top-Left with Bottom-Right)
    q0.copyTo(tmp);
    q3.copyTo(q0);
    tmp.copyTo(q3);
    q1.copyTo(tmp);                    // swap quadrant (Top-Right with Bottom-Left)
    q2.copyTo(q1);
    tmp.copyTo(q2);
    normalize(magI, magI, 0, 1, NORM_MINMAX); // Transform the matrix with float values into a
                                            // viewable image form (float between values 0 and 1).
    imshow("Input Image", I);    // Show the result
    saveImageFile(I,"result");
    imshow("spectrum magnitude", magI);
    saveImageFile(magI,"spec");
    cvWaitKey(0); //wait for a key press
    destroyAllWindows();
}



int display_caption( const char* caption )
{
    dst = Mat::zeros( src.size(), src.type() );
    putText( dst, caption,
             Point( src.cols/4, src.rows/2),
             FONT_HERSHEY_COMPLEX, 1, Scalar(255, 255, 255) );
    return display_dst(DELAY_CAPTION);
}
int display_dst( int delay )
{
    imshow( window_name, dst );
    int c = waitKey ( delay );
    if( c >= 0 ) { return -1; }
    return 0;
}

int Image::smothing()
{
    namedWindow( window_name, WINDOW_AUTOSIZE );
    src = imread(filename, IMREAD_COLOR);
    if (src.empty())
    {
        printf(" Error opening image\n");
        return EXIT_FAILURE;
    }
    if( display_caption( "Original Image" ) != 0 )
    {
        return 0;
    }
    dst = src.clone();
    if( display_dst( DELAY_CAPTION ) != 0 )
    {
        return 0;
    }
    if( display_caption( "Homogeneous Blur" ) != 0 )
    {
        return 0;
    }
    for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
    {
        blur( src, dst, Size( i, i ), Point(-1,-1) );
        if( display_dst( DELAY_BLUR ) != 0 )
        {
            return 0;
        }
    }
    if( display_caption( "Gaussian Blur" ) != 0 )
    {
        return 0;
    }
    for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
    {
        GaussianBlur( src, dst, Size( i, i ), 0, 0 );
        if( display_dst( DELAY_BLUR ) != 0 )
        {
            return 0;
        }
    }
    if( display_caption( "Median Blur" ) != 0 )
    {
        return 0;
    }
    for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
    {
        medianBlur ( src, dst, i );
        if( display_dst( DELAY_BLUR ) != 0 )
        {
            return 0;
        }
    }
    if( display_caption( "Bilateral Blur" ) != 0 )
    {
        return 0;
    }
    for ( int i = 1; i < MAX_KERNEL_LENGTH; i = i + 2 )
    {
        bilateralFilter ( src, dst, i, i*2, i/2 );
        if( display_dst( DELAY_BLUR ) != 0 )
        {
            return 0;
        }
    }
    display_caption( "Done!" );
    return 0;
}

void Threshold_Demo( int, void* )
{
  /* 0: Binary
     1: Binary Inverted
     2: Threshold Truncated
     3: Threshold to Zero
     4: Threshold to Zero Inverted
   */

  threshold( src_gray, dst, threshold_value, max_BINARY_value,threshold_type );

  imshow( window_name, dst );
}

void Image::threshold()
{
    src = imread(filename, 1 );

  /// Convert the image to Gray
  cvtColor( src, src_gray, CV_BGR2GRAY );

  /// Create a window to display results
  namedWindow( window_name, CV_WINDOW_AUTOSIZE );

  /// Create Trackbar to choose type of Threshold
  createTrackbar( trackbar_type,
                  window_name, &threshold_type,
                  max_type, Threshold_Demo );

  createTrackbar( trackbar_value,
                  window_name, &threshold_value,
                  max_value, Threshold_Demo );

  /// Call the function to initialize
  Threshold_Demo( 0, 0 );

  /// Wait until user finishes program
  while(true)
  {
    int c;
    c = waitKey( 20 );
    if( (char)c == 27 )
      { break; }
   }
}

/** @function thresh_callback */
void thresh_callback(int, void* )
{
  Mat canny_output;
  vector<vector<Point> > contours;
  vector<Vec4i> hierarchy;

  /// Detect edges using canny
  Canny( src_gray, canny_output, thresh, thresh*2, 3 );
  /// Find contours
  findContours( canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

  /// Draw contours
  Mat drawing = Mat::zeros( canny_output.size(), CV_8UC3 );
  for( int i = 0; i< contours.size(); i++ )
     {
       Scalar color = Scalar( rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255) );
       drawContours( drawing, contours, i, color, 2, 8, hierarchy, 0, Point() );
     }

  /// Show in a window
  namedWindow( "Contours", CV_WINDOW_AUTOSIZE );

  imshow( "Contours", drawing );


}



void Image::cannyContour()
{
    /// Load source image and convert it to gray
  src = imread( filename, 1 );

  /// Convert image to gray and blur it
  cvtColor( src, src_gray, CV_BGR2GRAY );
  blur( src_gray, src_gray, Size(3,3) );

  /// Create Window
  char* source_window = "Source";
  namedWindow( source_window, CV_WINDOW_AUTOSIZE );

  imshow( source_window, src );

  createTrackbar( " Canny thresh:", "Source", &thresh, max_thresh, thresh_callback );
  thresh_callback( 0, 0 );

  waitKey(0);

  destroyAllWindows();
}

void Image::binaryImage()
{
    Mat imageMat = my_image;
     //Grayscale matrix
    Mat grayscaleMat (imageMat.size(), CV_8U);

    //Convert BGR to Gray
    cvtColor( imageMat, grayscaleMat, CV_BGR2GRAY );

    //Binary image
    Mat binaryMat(grayscaleMat.size(), grayscaleMat.type());

    //Apply thresholding
    cv::threshold(grayscaleMat, binaryMat, 100, 255, cv::THRESH_BINARY);

    //Show the results
    namedWindow("Original image", cv::WINDOW_AUTOSIZE);
    imshow("Original image", my_image);

    namedWindow("Binary image", cv::WINDOW_AUTOSIZE);
    saveImageFile(binaryMat,"binary");
    imshow("Binary image", binaryMat);

    waitKey(0);

    destroyAllWindows();

}

void Morphology_Operations( int, void* )
{
  // Since MORPH_X : 2,3,4,5 and 6
  int operation = morph_operator + 2;
  Mat element = getStructuringElement( morph_elem, Size( 2*morph_size + 1, 2*morph_size+1 ), Point( morph_size, morph_size ) );
  morphologyEx( src, dst, operation, element );
  imshow( window_name, dst );
}

void Image::opening_closing_image()
{
      src = my_image;
      if (src.empty())
      {
        std::cout << "Could not open or find the image!\n" << std::endl;
        return exit(EXIT_FAILURE);
      }
      namedWindow( window_name, WINDOW_AUTOSIZE ); // Create window
      createTrackbar("Operator:\n 0: Opening - 1: Closing  \n 2: Gradient - 3: Top Hat \n 4: Black Hat", window_name, &morph_operator, max_operator, Morphology_Operations );
      createTrackbar( "Element:\n 0: Rect - 1: Cross - 2: Ellipse", window_name,
                      &morph_elem, max_elem,
                      Morphology_Operations );
      createTrackbar( "Kernel size:\n 2n +1", window_name,
                      &morph_size, max_kernel_size,
                      Morphology_Operations );
      Morphology_Operations( 0, 0 );
      waitKey(0);
      destroyAllWindows();
}

