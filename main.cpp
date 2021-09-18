#include <opencv2/imgcodecs.hpp>
   #include <opencv2/highgui.hpp>
   #include <opencv2/imgproc.hpp>
   #include <iostream>

   using namespace cv;
   using namespace std;

void getcountours(Mat imgDil,Mat img){
    
    vector<vector<Point>>contours;
    vector<Vec4i>hierarchy;
    findContours(imgDil, contours,hierarchy, RETR_EXTERNAL, CHAIN_APPROX_SIMPLE);
    //drawContours(img, contours, -1, Scalar(255,0,255),2);
    
    for (int i=0; i <contours.size() ; i++ ) {
        int area = contourArea(contours[i]);
        cout<<area<<endl;
        vector<vector<Point>>conPoly(contours.size());
        vector<Rect>boundrect(contours.size());
        string objectType ;
        
        if (area>1000){
            float peri = arcLength(contours[i], true);
            approxPolyDP(contours[i], conPoly[i], 0.02*peri, true);
            drawContours(img, conPoly, i, Scalar(255,0,255),2);
            cout<<  conPoly[i].size()<<endl;
            boundingRect(conPoly[i]);
            boundrect[i]=boundingRect(conPoly[i]);
            rectangle(img, boundrect[i].tl(), boundrect[i].br(), Scalar(0,255,0,5));
            
            int objcor = (int)conPoly[i].size();
            
            if (objcor==3){
                
                objectType ="Triangle";
                
            }
                else if (objcor==4) {
                    
                    float aspRatio = (float)boundrect[i].width/(float)boundrect[i].height;
                    cout<<aspRatio<<endl ;
                    
                    if ( aspRatio> 0.95 && aspRatio<1.05 ) {
                        
                        objectType="Square";
                        
                    }
    
                    
                else { objectType="Rectangle";
            }
                }
                else if  ( objcor > 5 ) {
                    objectType = "Circle";
                }
                
        
            drawContours(img, conPoly, i, Scalar(255,0,255),2);
            rectangle(img, boundrect[i].tl(), boundrect[i].br(), Scalar(0,255,0,5));
            putText(img, objectType, {boundrect[i].x, boundrect[i].y-5}, FONT_HERSHEY_PLAIN,1,Scalar(0,69,255),2);
        }
    }

}

   /////////////////  Images  //////////////////////


int main () {
   
    string path ="/usr/local/Cellar/opencv/4.5.3_2/lib/Opencvcourse/Opencvcourse/Resources 4/shapes.png";
    Mat img = imread(path);
    Mat imgGray,imgBlur,imgCanny,imgDil ;
    
    cvtColor(img, imgGray, COLOR_BGR2GRAY);
    GaussianBlur(imgGray, imgBlur, Size(3,3), 3,0);
    Canny(imgBlur, imgCanny, 25, 75);
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3,3));
    dilate(imgCanny, imgDil, kernel);
    
    getcountours(imgDil,img);
    
    
    
    
    
    imshow("Image1", img);
   /* imshow("Image gray", imgGray);
    imshow("Image blur", imgBlur);
    imshow("Image canny", imgCanny);
    imshow("Image dilation", imgDil); */
    
    waitKey(0);
    }
    

