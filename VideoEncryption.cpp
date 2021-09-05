#include<iostream>

#include "opencv2/highgui.hpp"
#include<opencv2/imgcodecs.hpp>
#include<opencv2/imgproc.hpp>
#include "opencv2/core.hpp"
#include<opencv2/videoio.hpp>
#include<omp.h>
#include "aes.cpp"
#include<chrono>


using namespace std;
using namespace cv;
using namespace chrono;

Mat Encryption(Mat image);
Mat Decryption(Mat image);

int main()
{

	//VideoCapture v(0,CAP_DSHOW);
	//VideoCapture v(0, CAP_DSHOW);
	//int frame_w = v.get(CAP_PROP_FRAME_WIDTH);
	//int frame_h = v.get(CAP_PROP_FRAME_HEIGHT);
	string file;
	cin >> file;
	VideoCapture vid(file);

	/*VideoWriter video("output.avi", VideoWriter::fourcc('M', 'J', 'P', 'G'), 20, Size(250, 300));*/
	VideoWriter video;
	int codec = VideoWriter::fourcc('M', 'P', '4', 'V');
	//int codec = VideoWriter::fourcc('M', 'J', 'P', 'G');
	double fps = vid.get(CAP_PROP_FPS);
	// video.open("Enc12.mp4", codec, fps, Size(vid.get(CAP_PROP_FRAME_WIDTH),vid.get(CAP_PROP_FRAME_HEIGHT)));
	video.open("EDec12.mp4", codec, fps, Size(vid.get(CAP_PROP_FRAME_WIDTH), vid.get(CAP_PROP_FRAME_HEIGHT)));
	//imshow("video", v);
	//Mat frame;
	//waitKey(0);
	//v.open(0, CAP_DSHOW);
	if (!video.isOpened()) {
		cerr << "Could not open the output video file for write\n";
		return -1;

	}
	else
	{
		cout << "\nSuccess!";
	}
	auto start = high_resolution_clock::now();
	while (1)
	{
		Mat frame;
		vid >> frame;
		// imshow("Frame", frame);
		if (!frame.empty())
			//video.write(Encryption(frame));
		{
			//video.write(frame);
			Mat fr = (Decryption(Encryption(frame)));
			//imshow("E-Decryption", fr);
			video.write(fr);
			//imshow("DATA", Decryption(frame));
			//imshow("DATA", Decryption(Encryption(frame)));
			// video.write(Decryption(frame));
			//waitKey(20);
		}
			//imshow("DATA", frame);
		else
		{
			cout << "BREAKING!\n";
			break;
		}
		//waitKey(10);
		char temp = (char)waitKey(1);
		if (temp==27) break;
		/*waitKey(5);*/
	}
	auto end = high_resolution_clock::now();

	cout << (end - start).count();
	//VideoCapture nvid("live.mp4");
	//if(nvid.isOpened())	cout << "\n Opened!";
	//else
	//{
	//	cerr << "ERROR!\n";
	//	return -1;
	//}
	//while (1)
	//{
	//	Mat frame;
	//	nvid >> frame;
	//	cout << "WORKING!";
	//	if (!frame.empty())
	//	{
	//		imshow("Encrypted", frame);
	//		waitKey(20);
	//	}
	//	else
	//	{
	//		cout << "BREAKINGF!";
	//		break;
	//	}
	//	waitKey(20);
	//}

	//v.release();
	video.release();
	//nvid.release();
	//cout << v.isOpened();
	//destroyAllWindows();
	return 0;
}

Mat Encryption(Mat image)
{
	vector<uint8_t> res;
	AES_ctx ctx;
	uint8_t* key = new uint8_t[16];
	for (int i = 0; i < 16; i++) key[i] = 0;
	AES_init_ctx(&ctx, key);
	//vector<auto> data(image.data);
	//image.convertTo(image,CV_8SC3);
	Mat result(image.rows, image.cols, CV_8UC3);
	image.convertTo(image, CV_8UC3);
	int count = 0;
	//cout << "Rows:" << image.rows << "Cols: " << image.cols;
	// Mat result(image.rows,image.cols,CV_8SC3);
	//imshow("Image",image );
	//long long l=0;
	_InputArray* a = new _InputArray[image.rows];

	int i, j, k;
#pragma omp parallel for num_threads(24) private(i,j,k)
	for (i = 0; i < image.rows; i++)
	{
		//int j;
//#pragma omp parallel for
		{
			for (j = 0; j < image.cols * image.channels(); j += 16)
			{
				//int k = j;
				//thread_num = omp_get_thread_num();
				//cout << thread_num << " ";
				uint8_t* temp = new uint8_t[32];
				//#pragma omp parallel for
				{
					for (k = j; k < j + 16 && k < image.cols * image.channels(); k++)
					{
						// cout << omp_get_thread_num() << " ";
						temp[k - j] = image.at<uint8_t>(i, k);
						//result.at<uint8_t>(i, k) = image.at<uint8_t>(i, k);
						//cout << temp[k - j]<<" ";
					}
				}
				//result.at<uint8_t>(i, j) = image.at<uint8_t>(i, j);
			//	cout << '\n';
			//	cout << '\n';
				AES_ECB_encrypt(&ctx, temp);
				//#pragma omp parallel for
				{
					for (k = j; k < j + 16 && k < image.cols * image.channels(); k++)
					{
						result.at<uint8_t>(i, k) = temp[k - j];
						//	result.at<uint8_t>(i, k) = (uint8_t)(result.at<uint8_t>(i, k));
						//	cout << result.at<uint8_t>(i, k)<<" ";
					}
				}

				//	a[l]= _InputArray(*temp);
				//	l++;
				// res.push_back(*temp);
			}
		}

	}

	//cout << result;
	//imshow("Original", image);
	//imshow("Enc", result);
	//cout << "Encrypted Image\n:\n"<<result.rowRange(0, 1) << '\n';
	//result.resize(image.size);
	//imwrite("encrypted2.png", result);
	//Mat ress = imread("encrypted2.png", IMREAD_ANYCOLOR);
	//imshow("Encrypted image",ress);
	//Decryption(ress);
	//cout << ress.rowRange(0, 1) << '\n';

	//for (int i = 0; i < ress.rows; i++)
	//{
	//	for (int j = 0; j < ress.cols; j++)
	//	{
	//		if (ress.at<uint8_t>(i, j) != result.at<uint8_t>(i, j))
	//		{
	//			cout << "Not working! " << i << " " << j;
	//			break;
	//			exit(1);
	//		}
	//	}
	//}

	//Decryption(ress);
	//Decryption(result);
	//Decryption(result);
	//for (auto i : res) cout << (int)i << " ";
	//cout << "\nDONE!";


	//cout << result;
	//imwrite("encrypted1.jpeg", result);
	//cout << "\nFINISHED!:)";
	//Mat enc=imread("encrypted1.png", IMREAD_ANYCOLOR);
	//for (int i = 0; i < enc.rows; i++)
	//{
	//	for (int j = 0; j < enc.cols; j++)
	//	{
	//		cout << enc.at<uint8_t>(i, j) << " ";
	//	}
	//}
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

	/*Mat* res;
	for (int i = 0; i < (*image).rows+1; i++)
	{
		for (int j = 0; j < (*image).cols + 1; j++)
		{
			Vec3b& imgpt = image->at<Vec3b>(i, j);

		}
	}
	*/
	//printf("DONE!");


	//imwrite("result.png", *image);
	//printf("\nData done!!");

	//uint8_t* res;
//	if (image->isContinuous())
//	{
//		res.assign
//	}
	return result;
}


Mat Decryption(Mat image)
{

	vector<uint8_t> res;
	AES_ctx ctx;
	uint8_t* key = new uint8_t[16];
	for (int i = 0; i < 16; i++) key[i] = 0;
	AES_init_ctx(&ctx, key);
	Mat result(image.rows, image.cols, CV_8UC3);
	//long long l=0;
	//image.convertTo(image, CV_8UC3);
	_InputArray* a = new _InputArray[image.rows];
	int i, j, k;
#pragma omp parallel for num_threads(25) private(i,j,k)
	for (i = 0; i < image.rows; i++)
	{

		//#pragma omp parallel for
		{
			for (j = 0; j < image.cols * image.channels(); j += 16)
			{
				//int k;
				uint8_t* temp = new uint8_t[32];
				//#pragma omp parallel for
				{
					for (k = j; k < j + 16 && k < image.cols * image.channels(); k++)
					{
						// cout << k << " ";
						temp[k - j] = (uint8_t)image.at<uint8_t>(i, k);
						//result.at<uint8_t>(i, k) = image.at<uint8_t>(i, k);
						//cout << temp[k - j]<<" ";
					}
				}
				//	cout << '\n';
				//	cout << '\n';
				AES_ECB_decrypt(&ctx, temp);
				//#pragma omp parallel for
				{
					for (k = j; k < j + 16 && k < image.cols * image.channels(); k++)
					{
						result.at<uint8_t>(i, k) = temp[k - j];
						//	result.at<uint8_t>(i, k) = (uint8_t)(result.at<uint8_t>(i, k));
						//	cout << result.at<uint8_t>(i, k)<<" ";
					}
					//	a[l]= _InputArray(*temp);
					//	l++;
					// res.push_back(*temp);
					//cout << image.at<uint8_t>(i, j);
				}
			}
		}
	}
	//imshow("Original", image);
//	imshow("Dec", result);
//	imwrite("decrypted.png", result);
	//Mat result(image);
	//cout << "Decrypted1\n"<<result.rowRange(0, 1);
	return result;
}
