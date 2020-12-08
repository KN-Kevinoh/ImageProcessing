#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include<string>

#include "Helps.h"

using namespace std;


Helps::Helps()
{
    //ctor
}

Helps::~Helps()
{
    //dtor
}

/** check existing image file */
void imageNotExist(cv::Mat file)
{
    if(file.empty())
    {
        cout << "Couldn't open or file not found" << endl;
        cin.get();
        exit(EXIT_FAILURE);
    }
}
