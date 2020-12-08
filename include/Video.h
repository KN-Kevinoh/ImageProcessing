#ifndef VIDEO_H
#define VIDEO_H

#define N_VIDEO "videos/carina_theVoice.mp4"


class Video
{
    public:
        /** Default constructor */
        Video();
        /** Default destructor */
        virtual ~Video();

        void playVideoFromFile();

        void playVideoFromCamera();

        void saveVideoFile(cv::VideoWriter videoWriter, cv::Mat frames);

        cv::VideoWriter initVideoWriter(cv::VideoCapture video_file);

        void changeBrightnessOfVideo();

        void changeContrastOfVideo();

        void homogeneousBlurOfVideo();

        void gaussianBlurOfVideo();

        void erodeVideo();

        void ObjectTrackingFromWebcam();

    protected:

    private:
};

#endif // VIDEO_H
