#ifndef IMAGE_H
#define IMAGE_H
#define N_IMAGE "images/car.jpg"
#define DELAY_CAPTION  1500
#define DELAY_BLUR 100
#define MAX_KERNEL_LENGTH  31
#define max_value  255
#define max_type  4
#define max_BINARY_value  255
#define max_operator 4
#define max_elem 2
#define max_kernel_size 21

#include<string>


class Image
{
    public:
        /** Default constructor */
        Image();
        Image(std::string filename);

        /** Default destructor */
        virtual ~Image();

        void displayImage(char* n_window);

        void displayBlankImage(char* n_window,long height, long width);

        void histogramme();

        void profilIntensiteImage();

        void correctionGamma();

        void showINwindow(char* n_window, cv::Mat file_image);

        void imageNotExist(cv::Mat file);

        void saveImageFile(cv::Mat file_image,std::string filename);

        void changeBrightnessOfImage();

        void changeContrastOfImage();

        void equalizeHistOfImageToGrayscale();

        void equalizeHistOfColorImage();

        void homogeneousBlurOfImage();

        void gaussianBlurOfImage();

        void invertImage();

        void erodeImage();

        void dilateImage();

        void brigthnessAndContrastOfImage();

        void MyCallbackForBrightness(int iValueForBrightness, void *userData);

        void MyCallbackForContrast(int iValueForContrast, void *userData);

        void pixelPositionInImage();

        void rotateImage();

        void CallbackForTrackBar(int, void*);

        void ObjectTrackingUsingContour();

        void ObjectTrackingUsingContourVersus2();

        void DFTOnImage();

        void freqFilter();

        int smothing();

        void threshold();

        void cannyContour();

        void binaryImage();

        void opening_closing_image();

        void set_filename(std::string filename);

        void set_my_image();

    private:
            cv::Mat my_image;
            std::string filename;

};

#endif // IMAGE_H
