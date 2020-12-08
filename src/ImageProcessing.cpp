#include<opencv2/opencv.hpp>
#include<iostream>
#include<string>
#include "ImageProcessing.h"




ImageProcessing::ImageProcessing()
{
    //ctor
}

ImageProcessing::~ImageProcessing()
{
    //dtor
}

//display image
void ImageProcessing::displayImage()
{
    Mat file_image = imread(N_IMAGE);

    if(file_image.empty())
    {
        cout << "Couldn't open or file not found" << endl;
        cin.get();
        exit(-1);
    }
    //create window and display image
    String n_window = "My Profil";
    namedWindow(n_window);
    imshow(n_window, file_image);
    waitKey(0);
    //de-allocate any memory
    destroyWindow(n_window);
}

// Create a blank image  & display

void ImageProcessing::displayBlankImage()
{
    /*
        image color 800*600 initialize with (100,250,30)
        for BGR
    */

    Mat image(600, 800, CV_8UC3, Scalar(100, 250, 30));
    saveImageFile(image);
    String n_window = "Blank Image";
    namedWindow(n_window);
    imshow(n_window, image);
    waitKey(0);
    destroyWindow(n_window);

}


void ImageProcessing::saveImageFile(Mat file_image)
{
    // depth must be 8 or 16 bits and channel 1 or 3
    // if not, use Mat::convertTo and cv::cvtColor functions to convert your image.

    bool is_success = imwrite("backupMedia/imgSave.jpg",file_image);

    if(!is_success)
    {
        cout << "Failed to save the image" << endl;
        cin.get();
        exit(EXIT_FAILURE);
    }

    cout << "Image successful save" << endl;

}

// Change Brightness of the images & videos
void  ImageProcessing::changeBrightnessOfImage()
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


// Change contrast of the images & videos

void ImageProcessing::changeContrastOfImage()
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
    imshow(n_window_contrast_high_4, image_contrast_high_4);
    imshow(n_window_contrast_low_0_5, image_contrast_low_0_5);
    imshow(n_window_contrast_low_0_25, image_contrast_low_0_25);

    waitKey(0); // Wait for any key pressed

    destroyAllWindows(); // Destroy all active windows

}

// Histogram EqualizationHistogram Equalization of a Grayscale image

void ImageProcessing::equalizeHistOfImageToGrayscale()
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

    // Show images
    imshow(n_window_original_image, image);
    imshow(n_window_histogram_equalized, hist_equalized_image);

    waitKey(0); // Wait for key press to exit

    destroyAllWindows(); // destroy all open windows
}


//Histogram Equalization of a Color image with OpenCV

void ImageProcessing::equalizeHistOfColorImage()
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

    waitKey(0); // Exit after any key pressed

    destroyAllWindows(); // destroy all active windows

}


// Flouter ou lisser une image ou une vidéo (flou homogène)

void ImageProcessing::homogeneousBlurOfImage()
{
    Mat image = imread(N_IMAGE);

    if(image.empty())
    {
        cout << "Couldn't open or find the image" << endl;
        cin.get();
        exit(EXIT_FAILURE);
    }

    // Blur the image with 3x3
    Mat image_blurred_with_3x3_kernel;
    blur(image, image_blurred_with_3x3_kernel, Size(3, 3));

    // Blur the image with 5x5 kernel
    Mat image_blurred_with_5x5_kernel;
    blur(image, image_blurred_with_5x5_kernel, Size(5, 5));

    // Windows names
    String n_window = "Original Image";
    String n_window_blurred_with_3x3_kernel = "Image Blurred with 3 x 3 Kernel";
    String n_window_blurred_with_5x5_kernel = "Image Blurred with 5 x 5 Kernel";

    // Create windows
    namedWindow(n_window, WINDOW_NORMAL);
    namedWindow(n_window_blurred_with_3x3_kernel, WINDOW_NORMAL);
    namedWindow(n_window_blurred_with_5x5_kernel, WINDOW_NORMAL);

    // Show our images
    imshow(n_window, image);
    imshow(n_window_blurred_with_3x3_kernel, image_blurred_with_3x3_kernel);
    imshow(n_window_blurred_with_5x5_kernel, image_blurred_with_5x5_kernel);

    waitKey(0);

    destroyAllWindows();
}


// Flouter ou lisser une image ou une vidéo (flou gaussien)

void ImageProcessing::gaussianBlurOfImage()
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
    imshow(n_window_blurred_with_5x5_kernel, image_blurred_with_5x5_kernel);

    waitKey(0); // Exit after any key pressed

    destroyAllWindows(); // Close all windows
}


// Invert images and Videos

void ImageProcessing::invertImage()
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

