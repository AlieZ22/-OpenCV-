#include"myHead.h"
/*
	����ͼƬ��ahashֵ
*/

vector<int> aHashValue(Mat& src)
{
	Mat img;
	vector<int> rst(64);
	double dldex[64];
	double mean = 0.0;
	int k = 0;

	if (src.channels() == 3)
	{
		cvtColor(src, src, CV_BGR2GRAY);
	}
	img = Mat_<double>(src);
	// ���ųߴ�
	resize(img, img, Size(8, 8));
	// ����ƽ������
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			dldex[k] = img.at<double>(i, j);
			mean += img.at<double>(i, j) / 64;
			k++;
		}
	}
	// �����ϣֵ
	for (int i = 0; i < 64; i++) {
		if (dldex[i] >= mean) {
			rst[i] = 1;
		}
		else {
			rst[i] = 0;
		}
	}
	return rst;
}
