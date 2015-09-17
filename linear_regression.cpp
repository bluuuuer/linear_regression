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
	while(getline(file,data[i])){
//		cout << data[i] << endl;
		idex = data[i].find_first_of(",",0);
		if(idex == -1)
			return -1;
		y[i] = atoi(data[i].substr(0,idex).c_str());
//		cout<<data[i].substr(0,idex)<<endl;
		_idex = data[i].find_first_of(",",idex + 1);
		if(_idex == -1)
			return -1;
		x[i] = atoi(data[i].substr(idex + 1,_idex - idex - 1).c_str());
//		cout<<data[i].substr(idex+1,_idex-idex-1)<<endl;
		cout << y[i] << "\t" << x[i] <<endl;
		i ++;
	}
	file.close();

	waitKey();
	return 0;
}
