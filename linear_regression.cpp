/*************************************************************************
 > File Name: linear_regression.cpp
 > Author: bluuuuer

*************************************************************************/
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <string>

using namespace std;
using namespace cv;

void plot(Mat & image){
	Point o_point,x_point,y_point;
	o_point.x = 50;
	o_point.y = 550;
	x_point.x = 550;
	x_point.y = 550;
	y_point.x = 50;
	y_point.y = 50;

	line(image,o_point,x_point,255,1,LINE_AA);
	line(image,o_point,y_point,255,1,LINE_AA);
	
	Point t_0_0;
	t_0_0.x = 30;
	t_0_0.y = 570;

	putText(image,"O",t_0_0,1,1,255);

	Point t_50_0,t_100_0,t_150_0,t_200_0,t_250_0;
	t_50_0.x = 150;
	t_50_0.y = t_100_0.y = t_150_0.y = t_200_0.y = t_250_0.y = 570;
	t_100_0.x = 250;
	t_150_0.x = 350;
	t_200_0.x = 450;
	t_250_0.x = 550;
	putText(image,"5O",t_50_0,1,1,255);
	putText(image,"10O",t_100_0,1,1,255);
	putText(image,"15O",t_150_0,1,1,255);
	putText(image,"20O",t_200_0,1,1,255);
	putText(image,"25O",t_250_0,1,1,255);
	line(image,Point(150,550),Point(150,545),255,1,LINE_AA);
	line(image,Point(250,550),Point(250,545),255,1,LINE_AA);
	line(image,Point(350,550),Point(350,545),255,1,LINE_AA);
	line(image,Point(450,550),Point(450,545),255,1,LINE_AA);
	line(image,Point(550,550),Point(550,545),255,1,LINE_AA);

	Point t_0_50,t_0_100,t_0_150,t_0_200,t_0_250;
	t_0_50.y = 450;
	t_0_50.x = t_0_100.x = t_0_150.x = t_0_200.x = t_0_250.x = 20;
	t_0_100.y = 350;
	t_0_150.y = 250;
	t_0_200.y = 150;
	t_0_250.y = 50;
	putText(image,"100",t_0_50,1,1,255);
	putText(image,"20O",t_0_100,1,1,255);
	putText(image,"30O",t_0_150,1,1,255);
	putText(image,"40O",t_0_200,1,1,255);
	putText(image,"50O",t_0_250,1,1,255);
	line(image,Point(50,450),Point(60,450),255,1,LINE_AA);
	line(image,Point(50,350),Point(60,350),255,1,LINE_AA);
	line(image,Point(50,250),Point(60,250),255,1,LINE_AA);
	line(image,Point(50,150),Point(60,150),255,1,LINE_AA);
	line(image,Point(50,50),Point(60,50),255,1,LINE_AA);
}

void point(Mat& image,int x,int y){
	Point center;
	center.x = (x + 50) * 2;
	center.y = 600 - y;
	circle(image,center,1,255,1,LINE_AA);

}

int main(int argc,char ** argv){
	fstream file;
	file.open("data.txt");
	if(!file){
		cout<<"无法打开指定文件"<<endl;
		return -1;
	}

	string data[51];
	int i = 0;
	int y[50],x[50];
	int idex = 0;
	int _idex = 0;
	int num = 0;
	int temp_x = 0;
	int temp_y = 0;
	int k;
	while(getline(file,data[i])){
//		cout << data[i] << endl;
		idex = data[i].find_first_of(",",0);
		if(idex == -1)
			return -1;
		temp_y = atoi(data[i].substr(0,idex).c_str());
//		cout<<data[i].substr(0,idex)<<endl;
		_idex = data[i].find_first_of(",",idex + 1);
		if(_idex == -1)
			return -1;
		temp_x = atoi(data[i].substr(idex + 1,_idex - idex - 1).c_str());
//		cout<<data[i].substr(idex+1,_idex-idex-1)<<endl;
//		cout << y[i] << "\t" << x[i] <<endl;
		for(k = 0;k < num;k ++)
			if(temp_y == y[k] && temp_x == x[k])
				break;
		if(k == num){
			y[num] = temp_y;
			x[num++] = temp_x;
		}
		i ++;
	}
	file.close();
//	cout << num <<endl;

	namedWindow("Coordinate");
	Mat coord = Mat::zeros(600,600,CV_8UC1);
	plot(coord);
	for(int j = 0;j < num;j ++){
//		cout << y[j] << "\t" << x[j] <<endl;
		point(coord,x[j],y[j]);
	}

	imshow("Coordinate",coord);
	waitKey();
	return 0;
}
