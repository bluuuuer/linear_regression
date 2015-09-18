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
	putText(image,"10O",t_50_0,1,1,255);
	putText(image,"20O",t_100_0,1,1,255);
	putText(image,"30O",t_150_0,1,1,255);
	putText(image,"40O",t_200_0,1,1,255);
	putText(image,"50O",t_250_0,1,1,255);
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
	putText(image,"200",t_0_50,1,1,255);
	putText(image,"40O",t_0_100,1,1,255);
	putText(image,"60O",t_0_150,1,1,255);
	putText(image,"80O",t_0_200,1,1,255);
	putText(image,"100O",t_0_250,1,1,255);
	line(image,Point(50,450),Point(60,450),255,1,LINE_AA);
	line(image,Point(50,350),Point(60,350),255,1,LINE_AA);
	line(image,Point(50,250),Point(60,250),255,1,LINE_AA);
	line(image,Point(50,150),Point(60,150),255,1,LINE_AA);
	line(image,Point(50,50),Point(60,50),255,1,LINE_AA);
}

void DrawPoint(Mat& image,float x,float y){
	Point center;
	center.x = x + 50;
	center.y = 550 - y / 2;
	circle(image,center,1,255,1,LINE_AA);

}

float h_theta_x(float* theta,float (*x)[50],int i){
    return theta[0]+theta[1]*x[0][i]+theta[2]*x[1][i]+theta[3]*x[2][i]+theta[4]*x[3][i];
}

float J_theta(float* theta,float (*x)[50],float* y,int num){
    float sum = 0.0;
    for(int i = 0;i < num;i ++)
        sum += (h_theta_x(theta,x,i) - y[i]) * (h_theta_x(theta,x,i) - y[i]);
    return sum / 2;
}

void DrawLine(Mat& image,float* theta){
    Point A,B;
    A.x = 50;
    A.y = 550;
    B.x = 550;
    B.y = 550 - (theta[0] + theta[1] * 250) / 2;
    line(image,A,B,255,1,LINE_AA);
    imshow("Coordinate",image);
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
	float y[50],x[4][50];
	int idex = 0;
	int _idex = 0;
	int num = 0;
	float temp_x[4] = {0.0,0.0,0.0,0.0};
	float temp_y = 0.0;
    int k = 0;
	while(getline(file,data[i])){
		cout << data[i] << endl;
		idex = data[i].find_first_of(",",0);
		if(idex == -1)
			return -1;
		temp_y = atof(data[i].substr(0,idex).c_str());
//		cout<<data[i].substr(0,idex)<<endl;

		_idex = data[i].find_first_of(",",idex + 1);
		if(_idex == -1)
			return -1;
		temp_x[0] = atof(data[i].substr(idex + 1,_idex - idex - 1).c_str());
//		cout<<data[i].substr(idex+1,_idex-idex-1)<<endl;

		idex = data[i].find_first_of(",",_idex + 1);
		if(idex == -1)
			return -1;
		temp_x[1] = atof(data[i].substr(_idex + 1,idex - _idex - 1).c_str());
//		cout<<data[i].substr(_idex+1,idex-_idex-1)<<endl;

		_idex = data[i].find_first_of(",",idex + 1);
		if(_idex == -1)
			return -1;
		temp_x[2] = atof(data[i].substr(idex + 1,_idex - idex - 1).c_str());
 //       cout<<data[i].substr(idex+1,_idex-idex-1)<<endl;

		temp_x[3] = atof(data[i].substr(_idex + 1).c_str());
//		cout<<data[i].substr(_idex+1)<<endl;

//		for(k = 0;k < num;k ++)
//			if(temp_y == y[k]&&temp_x[0]==x[0][k]&&temp_x[1]==x[1][k]&&temp_x[2]==x[2][k]&&temp_x[3]==x[3][k])
//				break;
//		if(k == num){
			y[num] = temp_y / 100;
            for(int j = 0;j < 4;j ++){
			    x[j][num] = temp_x[j] / 100;
           }
//		}
        cout<<y[num]<<"\t"<<x[0][num]<<"\t"<<x[1][num]<<"\t"<<x[2][num]<<"\t"<<x[3][num]<<endl;
	    num ++;
        i ++;
    }
	file.close();
//	cout << num <<endl;

	namedWindow("Coordinate");
	Mat coord = Mat::zeros(600,600,CV_8UC1);
	plot(coord);
/*	for(int j = 0;j < num;j ++){
	cout << y[j] << "\t" << x[j] <<endl;
		point(coord,x[j] * 100,y[j] * 100);
	}*/

//	cout << "num = " << num <<endl;
    float theta[5] = {0.0,0.0,0.0,0.0,0.0};
    float alpha = atof(argv[1]);
    float temp[5] = {0.0,0.0,0.0,0.0,0.0};
    i = 0;k = 0;
//    float* p = &(x[0][0]);
    float tempJ = 0.0;
    while((J_theta(theta,x,y,num) - tempJ) > atof(argv[2]) || (tempJ - J_theta(theta,x,y,num) > atof(argv[2]))){
        tempJ = J_theta(theta,x,y,num);
        cout << "J=" << tempJ << endl;
        for(int j = 0;j < 3;j ++){
            if(i+j >= num)
                i -= num;
            temp[0] += alpha * (h_theta_x(theta,x,i+j)- y[i+j]);
            temp[1] += alpha * (h_theta_x(theta,x,i+j)- y[i+j]) * x[0][i+j];
            temp[2] += alpha * (h_theta_x(theta,x,i+j)- y[i+j]) * x[1][i+j];
            temp[3] += alpha * (h_theta_x(theta,x,i+j)- y[i+j]) * x[2][i+j];
            temp[4] += alpha * (h_theta_x(theta,x,i+j)- y[i+j]) * x[3][i+j];
        }
        for(int j = 0;j < 5;j ++){
            theta[j] -= temp[j] / 3;
            temp[j] = 0.0;
            cout << theta[j] << "    ";
        }
        cout<<endl;
        i += 3;
        if(i >= num)
            i -=  num;
        //DrawLine(coord,theta);
        DrawPoint(coord,k,tempJ);
        k ++;
    }
    cout << k<< endl;

   // DrawLine(coord,theta);
    imshow("Coordinate",coord);
	waitKey();
	return 0;
}
