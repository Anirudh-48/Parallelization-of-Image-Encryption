#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include <iostream>
#include "aes.cpp"
using namespace cv;
using namespace std;


///// CV8sc3 works okish CV_8UC3 works better always multiply channels and columns



void Encryption(Mat image);
void Decryption(Mat image);

int main()
{
	Mat image= imread("C:\\Users\\Anirudh\\Desktop\\pdc_lab\\AES_pdc\\triall.png",IMREAD_ANYCOLOR);
	//Mat image = imread("encrypted1.jpeg", IMREAD_ANYCOLOR);
	//imshow("Image", image);
	//cout << (int)image.data;
	//printf("IMG LOADED");
	Encryption(image);
	//Mat img=imread("encrypted1.jpeg",IMREAD_ANYCOLOR);
	//imshow("Image", img);
	//Decryption(image);
	imshow("Image", image);
	waitKey(0);

//	char x;
//	cin >> x;
	return 0;
}


void Encryption(Mat image)
{ 
	vector<uint8_t> res;
	AES_ctx ctx;
	uint8_t *key=new uint8_t[16];
	for (int i = 0; i < 16; i++) key[i] = 0;
	AES_init_ctx(&ctx, key);
	//vector<auto> data(image.data);
	//image.convertTo(image,CV_8SC3);
	Mat result(image.rows, image.cols, CV_8UC3);
	image.convertTo(image, CV_8UC3);
	int count = 0;
	cout <<"Rows:"<< image.rows << "Cols: " << image.cols;
	// Mat result(image.rows,image.cols,CV_8SC3);
	imshow("Image",image );
	//long long l=0;
	_InputArray* a = new _InputArray[image.rows];
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols* image.channels(); j+=16)
		{
			uint8_t* temp = new uint8_t[32];
			for(int k=j;k<j+16 && k<image.cols * image.channels() ;k++)
			{
				// cout << k << " ";
				temp[k-j]=(uint8_t)image.at<uint8_t>(i, k);
				//result.at<uint8_t>(i, k) = image.at<uint8_t>(i, k);
				//cout << temp[k - j]<<" ";
			}
			//result.at<uint8_t>(i, j) = image.at<uint8_t>(i, j);
		//	cout << '\n';
		//	cout << '\n';
			 AES_ECB_encrypt(&ctx, temp);
			for (int k = j; k < j + 16 && k<image.cols* image.channels(); k++)
			{
				result.at<uint8_t>(i, k) =temp[k-j];
			//	result.at<uint8_t>(i, k) = (uint8_t)(result.at<uint8_t>(i, k));
			//	cout << result.at<uint8_t>(i, k)<<" ";
			}
			
			//	a[l]= _InputArray(*temp);
			//	l++;
			// res.push_back(*temp);
		}
	}
	
	//cout << result;
	//imshow("Original", image);
	imshow("Enc", result);
	Decryption(result);
	//for (auto i : res) cout << (int)i << " ";
	//cout << "\nDONE!";
	

	//cout << result;
	//imwrite("encrypted1.jpeg", result);
	//cout << "\nFINISHED!:)";
/*	Mat enc=imread("encrypted1.png", IMREAD_ANYCOLOR);
	for (int i = 0; i < enc.rows; i++)
	{
		for (int j = 0; j < enc.cols; j++)
		{
			cout << enc.at<uint8_t>(i, j) << " ";
		}
	}*/
	//	cout <<endl<< count<<endl;
//	imwrite("l_resultant.png", *a);
//	uint8_t* datas = image.data;
//	cout << datas;
	// cout << image<<endl;
	
	//cout << endl<<sizeof(image) << '\n';
	//cout << sizeof(data)<<'\n';
	// cout << <<'\n';
//	_InputArray res(datas);
	//vector<int>res(*data);
	
/*	Mat* res;
	for (int i = 0; i < (*image).rows+1; i++)
	{
		for (int j = 0; j < (*image).cols + 1; j++)
		{
			Vec3b& imgpt = image->at<Vec3b>(i, j);
			
		}
	}
	printf("DONE!");
	
	
	imwrite("result.png", *image);
	printf("\nData done!!");*/
	
	//uint8_t* res;
//	if (image->isContinuous())
//	{
//		res.assign
//	}
	return;
}

void Decryption(Mat image)
{
	vector<uint8_t> res;
	AES_ctx ctx;
	uint8_t* key = new uint8_t[16];
	for (int i = 0; i < 16; i++) key[i] = 0;
	AES_init_ctx(&ctx, key);
	Mat result(image.rows, image.cols,CV_8UC3);
	//long long l=0;
	
	_InputArray* a = new _InputArray[image.rows];
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols* image.channels(); j += 16)
		{
			uint8_t* temp = new uint8_t[16];
			for (int k = j; k < j + 16 && k < image.cols* image.channels(); k++)
			{
				// cout << k << " ";
				temp[k - j] = (uint8_t)image.at<uint8_t>(i, k);
				//cout << temp[k - j]<<" ";
			}
			//	cout << '\n';
			//	cout << '\n';
			AES_ECB_decrypt(&ctx, temp);
			for (int k = j; k < j + 16 && k < image.cols * image.channels(); k++)
			{
				result.at<uint8_t>(i, k) = (uint8_t)temp[k - j];
				//	result.at<uint8_t>(i, k) = (uint8_t)(result.at<uint8_t>(i, k));
				//	cout << result.at<uint8_t>(i, k)<<" ";
			}
			//	a[l]= _InputArray(*temp);
			//	l++;
			// res.push_back(*temp);
			//cout << image.at<uint8_t>(i, j);
		}
	}
	//imshow("Original", image);
	// imshow("Dec", result);
	imwrite("decrypted.png", result);

	return;
}