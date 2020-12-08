#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H
#define N_IMAGE "car.jpg"



class ImageProcessing
{
    public:
        /** Default constructor */
        ImageProcessing();
        /** Default destructor */
        virtual ~ImageProcessing();
        void displayImage();
        void displayBlankImage();
        void saveImageFile(cv::Mat file_image);
        void changeBrightnessOfImage();
        void changeContrastOfImage();
        void equalizeHistOfImageToGrayscale();
        void equalizeHistOfColorImage();
        void gaussianBlurOfImage();
        void invertImage();
    protected:
    private:
};

#endif // IMAGEPROCESSING_H
