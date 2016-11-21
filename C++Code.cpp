#include <string>
#include <iostream>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

int main(int argc, char** argv)
{
    if (argc < 2) {
        std::cout << "Requires path to image" << std::endl;
        return 1;
    }

    std::string name = argv[1];
    cv::Mat image = cv::imread(name);
    if (!image.data) {
        std::cout << "Invalid path" << std::endl;
        return 1;
    }

    cv::namedWindow(name, cv::WINDOW_AUTOSIZE);
    cv::imshow(name, image);
    cv::waitKey();
   

    cv::Mat bgr[3];   //destination array
    split(image,bgr);//split source  

    //Note: OpenCV uses BGR color order
    imwrite("blue.png",bgr[0]); //blue channel
    imwrite("green.png",bgr[1]); //green channel
    imwrite("red.png",bgr[2]); //red channel

    return 0;

    

    
}


