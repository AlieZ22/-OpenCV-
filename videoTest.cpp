#include"myHead.h"
/*
	һ֡һ֡������Ƶ��rukou.mp4��
	���к󣬰�ESC����ͣ�����л������ڼ��
	�ڻ������ڼ��Ĺ����У���⵽һ��ʱ������ESC���˳�����������������Ƶ�����������������������ڼ��
	һ֡�Ĵ��ڼ�����Զ��˳�������������Ƶ
*/
extern vector<int> aHashValue(Mat& src);
extern void LBP(const cv::Mat& image, cv::Mat& lbp_image);

int main()
{
	VideoCapture cap;
	Mat frame;
	Mat img;
	int key;
	int num = 100;

	cap.open("tech.flv");
	if (!cap.isOpened()) {
		cout << "cap load failed!" << endl;
		return -1;
	}

	// ������ѵ����svmģ��
	CvSVM svm;
	svm.clear();
	string modelPath = "hash_svm.xml";
	FileStorage svm_fs(modelPath, FileStorage::READ);
	if (svm_fs.isOpened()) {
		svm.load(modelPath.c_str());
	}

	// ���м��
	while (true) 
	{
		cap >> frame;
		imshow("video", frame);
		if (frame.empty()) {
			cout << "����" << endl;
			break;
		}
		key = waitKey(30);
		if (key != 27) {
			continue;
		}
		// �������ڼ����һ֡
		int response;
		img = frame.clone();
		Mat clone;
		cvtColor(img, clone, CV_BGR2GRAY);
		// �������ڴ�С
		int winSize1 = 180;    // ��
		int winSize2 = 220;    // ��
		if (img.cols > winSize1 && img.rows > winSize2)
		{
			int step = 25;    // ������x,y�������
			for (int y = 0; y < img.rows - winSize2; y += step) {
				for (int x = 0; x < img.cols - winSize1; x += step) {
					imshow("detect_frame", img);
					waitKey(5);
					Mat myROI = clone(Rect(x, y, winSize1, winSize2));
					Mat lbp_roi;
					LBP(myROI, lbp_roi);
					imshow("roi", lbp_roi);
					vector<int> hash = aHashValue(myROI);
					Mat dst = Mat(hash);
					dst = dst.reshape(1, 1);
					dst.convertTo(dst, CV_32FC1);
					response = (int)svm.predict(dst);
					// �ô��ڼ�⵽����
					if (response == 1) {
						cout << "�������" << endl;
						rectangle(img, cvPoint(x, y), cvPoint((x + winSize1), (y + winSize2)), cvScalar(0, 0, 255), 3, 4, 0);
						int c = waitKey(0);
						// ��⵽һ��ʱ������ESC���˳�����������������Ƶ
						if (c == 27) {
							//string hardPath = "d:\\program\\c++\\proj\\phash_svm\\hardneg\\hard";
							//hardPath = hardPath.append(to_string(num));
							//hardPath = hardPath.append(".jpg");
							//imwrite(hardPath, myROI);
							//num++; 
							goto Label;
						}
					}
					else {
						//cout << "δ�������" << endl;
					}
				}
			}
		}
		Label:
			destroyWindow("detect_frame");
			destroyWindow("roi");
	}

}