#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <string>


#include "Image.h"
#include "Video.h"

using namespace cv;
using namespace std;

/*** Training from
*www.opencv-srf.com/
*****/

int main(int argc, char ** argv)
{
    string filename_image = argc >=2 ? argv[1] : N_IMAGE;
    const char* filename_video = argc >=2 ? argv[1] : N_VIDEO;
    int choix, answer;
    Image img(filename_image);

    Video video;
    /** menu */
    cout << "-------IMAGE PROCESSING--------\n" << endl;
    cout << "1- Display an image."<< endl;
    cout << "2- Play a video."<< endl;
    cout << "3- Play video from caméra."<< endl;
    cout << "4- Modify image brigthness."<< endl;
    cout << "5- Modify video brigthness."<< endl;
    cout << "6- Modify image contrast."<< endl;
    cout << "7- Modify video contrast."<< endl;
    cout << "8- Equalize grayscale image."<< endl;
    cout << "9- Equalize color image."<< endl;
    cout << "10- Homogenious blur of image."<< endl;
    cout << "11- Homogenious blur of video ."<< endl;
    cout << "12- Gaussian blur of image."<< endl;
    cout << "13- Gaussian blur of video ."<< endl;
    cout << "14- Invert image."<< endl;
    cout << "15- Erode image."<< endl;
    cout << "16- Erode video."<< endl;
    cout << "17- Dilate image."<< endl;
    cout << "18- Image brigthness and contrast change."<< endl;
    cout << "19- Rotate Image."<< endl;
    cout << "20- Track Object from webcam."<< endl;
    cout << "21- Detected contour in Image (versus1)."<< endl;
    cout << "22- Detected contour in Image (versus2)."<< endl;
    cout << "23- Apply DFT In Image. ."<< endl;
    cout << "25- Apply different threshold in Image."<< endl;
    cout << "26- Blur image by different filter."<< endl;
    cout << "27- Contour vesus canny."<< endl;
    cout << "28- Histogram image."<< endl;
    cout << "29- Profil intensity of image."<< endl;
    cout << "30- Gama correction of image."<< endl;
    cout << "31- Binarization of image."<< endl;
    cout << "32- Others binarization operations of image."<< endl;

  /** input complet image path**/
    printf("Voulez vous redefinir une image? (entrer 0 pour non et 1 pour oui): ");
    scanf("%d",&answer);
    // check answer
     if(answer!=0){
        cout << "Entrez le chemin complet: " << endl;
        cin >> filename_image;
        img.set_filename(filename_image);
        img.set_my_image();

    }

     while(1){

        do{
             cout << "Entrez votre choix: " << endl;
             cin >> choix;
        }while(choix <= 0 || choix > 50);
        // Initialization of max depending the choice
        switch(choix){
            case 1 : img.displayImage((char*)"My Image"); break;
            case 2 : video.playVideoFromFile(); break;
            case 3 : video.playVideoFromCamera(); break;
            case 4 : img.changeBrightnessOfImage(); break;
            case 5 : video.changeBrightnessOfVideo(); break;
            case 6 : img.changeContrastOfImage(); break;
            case 7 : video.changeContrastOfVideo(); break;
            case 8 : img.equalizeHistOfImageToGrayscale(); break;
            case 9 : img.equalizeHistOfColorImage(); break;
            case 10 : img.homogeneousBlurOfImage(); break;
            case 11 : video.homogeneousBlurOfVideo(); break;
            case 12 : img.gaussianBlurOfImage(); break;
            case 13 : video.gaussianBlurOfVideo(); break;
            case 14 : img.invertImage(); break;
            case 15 : img.erodeImage(); break;
            case 16 : video.erodeVideo(); break;
            case 17 : img.dilateImage(); break;
            case 18 : img.brigthnessAndContrastOfImage(); break;
            case 19 : img.rotateImage(); break;
            case 20 : video.ObjectTrackingFromWebcam(); break;
            case 21 : img.ObjectTrackingUsingContour(); break;
            case 22 : img.ObjectTrackingUsingContourVersus2(); break;
            case 23 : img.DFTOnImage(); break;
            case 25 : img.threshold(); break;
            case 26 : img.smothing(); break;
            case 27 : img.cannyContour(); break;
            case 28 : img.histogramme(); break;
            case 29 : img.profilIntensiteImage(); break;
            case 30 : img.correctionGamma(); break;
            case 31 : img.binaryImage(); break;
            case 32 : img.opening_closing_image(); break;
            default : cout << "Choix invalide" << endl;
        }

        printf("Voulez vous continuer? (entrer 0 pour non et 1 pour oui): ");
        scanf("%d",&answer);
        // check answer
         if(answer==0){
            break;
        }else{
            continue;
        }

    }
    return 0;
}
