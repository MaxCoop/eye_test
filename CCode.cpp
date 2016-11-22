#include <string>
#include <iostream>

#include <ctime>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

int main(int argc, char** argv)
{
    if (argc < 2) {  // Checking for input
        std::cout << "Requires path to image" << std::endl; //Missing input indication
        return 1;                                           //Error code
    }

    std::clock_t start;
    double duration;
        start = std::clock();

    std::string name = argv[1];    //Get the name of the image
    cv::Mat image = cv::imread(name);  // Read the image into a matrix
    cv::Mat EqualImage; 

    if (!image.data) { //Check if the matrix is empty
        std::cout << "Invalid path" << std::endl; // if it is empty print this message
        return 1;  //error return value
    }

  //  cv::namedWindow(name, cv::WINDOW_AUTOSIZE);
  //  cv::imshow(name, image);
  //  cv::waitKey();


    cv::Mat bgr[3];   //destination array 
    split(image,bgr);//split source (RED COLOUR AT THIS STAGE)

     //Note: OpenCV uses BGR color order in this case only dealing with RED
    //imwrite("blue.png",bgr[0]); //blue channel
    // imwrite("green.png",bgr[1]); //green channel
    // imwrite("red.png",bgr[2]); //red channel

    cv::Mat RedImage = bgr[2];
    imwrite("RedImage.png",RedImage);

    ///Convert to grayscale
   // cv::cvtColor(Image, Image, CV_BGR2GRAY);


      ///Apply histogram Equalization
       cv::equalizeHist(RedImage, EqualImage);

    cv::imwrite("EqualImage.png", EqualImage);
     
	 duration = (std::clock() - start)/(double)CLOCKS_PER_SEC;
         std::cout<< "printf: " << duration <<'\n';
   	 std::cout << "Red decoded images have been processed" << std::endl; //success message


    return 0;




}
