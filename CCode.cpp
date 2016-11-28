#include <string>
#include <iostream>
#include <vector>

#include <ctime>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
//#include <raspicam/raspicam_cv.h>

int main(int argc, char** argv)
{
    if (argc < 2) {  // Checking for input
        std::cout << "Requires path to image" << std::endl; //Missing input indication
        return 1;                                           //Error code
    }

    std::clock_t start;
    double duration;
    start = std::clock();

 //  raspicam::RaspiCam_Cv Camera;


//Obtain the name of the Input-Image
   std::string name = argv[1];  
//Read the image into a matrix
   std::clock_t A;
   A = std::clock();
   cv::Mat image = cv::imread(name);
//Check if the input image is valid
 if (!image.data) { //Check if the matrix is empty
        std::cout << "Invalid path" << std::endl; // if it is empty print this message
        return 1;  //error return value
    }   

   duration = (std::clock()-A)/(double)CLOCKS_PER_SEC;
   std::cout<<"Reading Image :"<<duration<<"\n";  

    cv::Mat EqualImage;
    cv::Mat BlurImage;
    cv::Mat ThreshImage;
//Variables for computing threshold
	double thresh = 30;
	double MaxValue = 175;
//Variables for counting black pixels
	int i;
	int j;
	int count=0; 

   // cv::namedWindow(name, cv::WINDOW_AUTOSIZE);
   // cv::imshow(name, image);
  //  cv::waitKey();

    cv::Mat bgr[3];   //destination array 
    split(image,bgr);//split source (RED COLOUR AT THIS STAGE)

     //Note: OpenCV uses BGR color order in this case only dealing with RED
    //imwrite("blue.png",bgr[0]); //blue channel
    // imwrite("green.png",bgr[1]); //green channel
    // imwrite("red.png",bgr[2]); //red channel

    cv::Mat RedImage = bgr[2];
    imwrite("RedImage.png",RedImage);



    cv::namedWindow("Display Window",cv::WINDOW_AUTOSIZE);
    cv::imshow("Display Window", RedImage);
	std::cout<<"Display Window"<<std::endl;

    ///Convert to grayscale
   // cv::cvtColor(Image, Image, CV_BGR2GRAY);


         //Apply histogram Equalization
          cv::equalizeHist(RedImage, EqualImage);
          cv::imwrite("EqualImage.png", EqualImage);
      
         //apply median smoothing      
          medianBlur (EqualImage, BlurImage,13); 
          cv::imwrite("BlurImage.png", BlurImage);
        
         //Apply Threshold
        cv::threshold(BlurImage,ThreshImage, thresh, MaxValue,cv::THRESH_BINARY);  
         cv::imwrite("ThreshImage.png", ThreshImage);      
            
         
        std::cout<<"Image Size ="<<ThreshImage.cols<<"x"<<ThreshImage.rows<<"\n";	
	
     for (i = 0; i<ThreshImage.cols;i++){
	for(j = 0;j<ThreshImage.rows;j++){
		int k=ThreshImage.at<uchar>(j,i);
                if(k==0){ count++;}      
		}
	}  
     
        std::cout<<"Number of BlackPixels ="<<count<<"\n";  

	 duration = (std::clock() - start)/(double)CLOCKS_PER_SEC;
         std::cout<< "Process Time: " << duration <<"\n";
       //	std::cout<<"Process Time: "<<((std::clock()-start)/(double)CLOCKS_PER_SEC)<<'\n';
   	 std::cout << "Images have been processed" << std::endl; //success message


    return 0;


}
