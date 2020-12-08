#ifndef VIDEOPROCESSING_H
#define VIDEOPROCESSING_H

#define N_VIDEO "carina_theVoice.mp4"


class VideoProcessing
{
    public:
        /** Default constructor */
        VideoProcessing();
        /** Default destructor */
        virtual ~VideoProcessing();
        void playVideoFromFile();
        void playVideoFromCamera();
        VideoWriter initVideoWriter(VideoCapture video_file);
        void saveVideoFile(VideoWriter v_Writer, Mat frames);
        void changeBrightnessOfVideo();
        void changeContrastOfVideo();
        void homogeneousBlurOfImage();
        void homogeneousBlurOfVideo();
        void gaussianBlurOfVideo();
    protected:
    private:
};

#endif // VIDEOPROCESSING_H
