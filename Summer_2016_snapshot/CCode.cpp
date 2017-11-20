#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
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
   std::cout<<"Reading Image :"<<std::setprecision(2)<<duration<<"\n";  
   std::cout<<"Image Size ="<<image.cols<<"x"<<image.rows<<"\n";
   
    cv::Mat EqualImage;
    cv::Mat BlurImage;
    cv::Mat ThreshImage;
    cv::Mat ThreshImage2;
//Variables for computing threshold
	double thresh = 5;
	double thresh2 = 10;
	double MaxValue = 255;
//Variables for counting black pixels
	int i;
	int j;
	int count=0; 


start = std::clock();
    cv::Mat bgr[3];   //destination array 
    split(image,bgr);//split source (RED COLOUR AT THIS STAGE)

    //Obtain Red Channel
    cv::Mat RedImage = bgr[2];
    //Apply Equalize
    cv::equalizeHist(RedImage, EqualImage);
    //Apply medianBlur
    cv::medianBlur (EqualImage, BlurImage,11);
    //Apply Threshold
    cv::threshold(BlurImage,ThreshImage, thresh, MaxValue,cv::THRESH_BINARY);  
    cv::threshold(ThreshImage,ThreshImage2, thresh2, MaxValue,cv::THRESH_BINARY);                 	
	
	//counting black pixels
	std::clock_t B;
	B = clock();
     for (i = 0; i<ThreshImage.cols;i++){
	for(j = 0;j<ThreshImage.rows;j++){
		int k=ThreshImage.at<uchar>(j,i);
                if(k==0){ count++;}      
		}
	}  
    std::cout<<"for loop : "<<(clock()-B)/(double)CLOCKS_PER_SEC<<std::endl;
    
    duration = (std::clock() - start)/(double)CLOCKS_PER_SEC;
    std::cout<<"Number of BlackPixels = "<<count<<"\n";  

    std::cout<< "Process Time: "<<std::setprecision(2)<< duration <<"\n";
	std::cout << "Images have been processed" << std::endl; //success message

	cv::namedWindow("Red Image",cv::WINDOW_NORMAL);
    cv::imshow("Red Image", RedImage);
    	
	cv::namedWindow("EqualImage", cv::WINDOW_NORMAL);
    cv::imshow("EqualImage",EqualImage);
	
	cv::namedWindow("BlurImage", cv::WINDOW_NORMAL);
	cv::imshow("BlurImage", BlurImage);

	cv::namedWindow("ThreshImage",cv::WINDOW_NORMAL);
	cv::imshow("ThreshImage", ThreshImage);
	
	cv::namedWindow("ThreshImage2",cv::WINDOW_NORMAL);
	cv::imshow("ThreshImage2", ThreshImage2);
	
         cv::waitKey();

    return 0;


}
