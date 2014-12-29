#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <cv.h>
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <random>
# define M_PI           3.14159265358979323846  /* pi */
using namespace std;
using namespace cv;
Mat src,img, gray_image;

int mask33(int x,int y,int i);
int checks(int x,int y,int i);
/** @function main */
int main(int argc, char** argv)
{
	String ins="len_std_gray2";
	/// Read the image 
	src = imread(ins+".jpg", 1 );
	cvtColor( src, src, CV_RGB2GRAY );
	const int nrolls=10000;  // number of experiments
	const int nstars=800;    // maximum number of stars to distribute

	std::default_random_engine generator(time(0));
	std::normal_distribution<double> distribution(127.0,50.0);

	int p[65536]={};
	int count=0;
	for (int i=0; i<256; ++i) {
		for(int j=0;j<256;j++){
			double number = distribution(generator);
			if ((number>=0.0)&&(number<255.0)){
				++p[int(number)];
				uchar color=number;
				//src.at<uchar>(Point(i,j))= color;
				if(rand()%2==1){
					src.at<uchar>(Point(i,j))= color;
				}
			}
			else{
				count++;
			}

			
		}
	}
	
	std::cout << "normal_distribution (5.0,2.0):" << std::endl;

	for (int i=0; i<256; ++i) {
	std::cout << i << "-" << (i+1) << ": ";
	std::cout << std::string(p[i]*nstars/nrolls,'*') << std::endl;
	}
	cout << "count:"<<count<< endl;
	namedWindow( "gray", CV_WINDOW_AUTOSIZE );
	imshow( "gray", src );
	imwrite( ins+"_result.jpg", src );
	waitKey(0);
	return 0;
}
//


int mask33(int x,int y,int i){
	int arr33[3][3]={{ 0,-1, 0},
					 {-1, 4,-1},
					 { 0,-1, 0}};
	int lu=checks(x-1,y-1,i);
	int u=checks(x,y-1,i);
	int ru=checks(x+1,y-1,i);
	int l=checks(x-1,y,i);
	int m=checks(x,y,i);
	int r=checks(x+1,y,i);
	int ld=checks(x-1,y+1,i);
	int d=checks(x,y+1,i);
	int rd=checks(x+1,y+1,i);

	float color_v=(arr33[0][0]*lu+arr33[0][1]*u+arr33[0][2]*ru+
				 arr33[1][0]*l+arr33[1][1]*m+arr33[1][2]*r+
				 arr33[2][0]*ld+arr33[2][1]*d+arr33[2][2]*rd
	)/9;
	
	return color_v;
}

int checks(int x,int y,int i){
	if(x>=0&&x<src.cols&&y>=0&&y<src.rows){
		uchar c=gray_image.at<uchar>(y,x);
		return 	c;
	}
	else
		return 0;
}
