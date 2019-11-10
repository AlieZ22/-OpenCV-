#include"myHead.h"
#include<io.h>
/*
	main.cpp����ѵ��svmģ�ͣ���Ҫ����Ч�����򽫴�ע��
	��test.cpp��videoTest.cpp���в���
*/

#define PosSample 500
#define NegSample 1000
string posPath = "D:\\Program\\C++\\proj\\phash_svm\\pos2";
string negPath = "D:\\Program\\C++\\proj\\phash_svm\\neg";

extern vector<int> pHashValue(Mat& src);
extern vector<int> aHashValue(Mat& src);
extern void LBP(const cv::Mat& image, cv::Mat& lbp_image);
void getFiles(string path, vector<string>& files);
void get_pos(Mat& trainingImages, vector<int>& trainingLabels);
void get_neg(Mat& trainingImages, vector<int>& trainingLabels);

/*int main()
{
	// ��ȡѵ����
	Mat classes;                  // ����ѵ����ǩ
	Mat trainingData;             // ����ѵ������
	Mat trainingImages;           
	vector<int> trainingLabels;
	get_pos(trainingImages, trainingLabels);
	get_neg(trainingImages, trainingLabels);
	classes = Mat(trainingLabels).clone();
	trainingData = Mat(trainingImages).clone();
	trainingData.convertTo(trainingData, CV_32FC1);
	cout << trainingData.size() << endl;
	// ����SVM����
	CvSVMParams SVM_params;
	SVM_params.svm_type = CvSVM::C_SVC;
	SVM_params.kernel_type = CvSVM::LINEAR;
	SVM_params.degree = 0;
	SVM_params.gamma = 1;
	SVM_params.coef0 = 0;
	SVM_params.C = 1;
	SVM_params.nu = 0;
	SVM_params.p = 0;
	SVM_params.term_crit = cvTermCriteria(CV_TERMCRIT_ITER, 10000, 0.01);
	// ѵ��
	CvSVM svm;
	svm.train(trainingData, classes, Mat(), Mat(), SVM_params);
	// ����ģ��
	svm.save("hash_svm.xml");

	return 0;
}*/

void getFiles(string path, vector<string>& files)
{
	intptr_t handle = 0;
	struct _finddata_t fileinfo;
	string p;
	if ((handle = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib & _A_SUBDIR))
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
					getFiles(p.assign(path).append("\\").append(fileinfo.name), files);
			}
			else
			{
				files.push_back(p.assign(path).append("\\").append(fileinfo.name));
			}
		} while (_findnext(handle, &fileinfo) == 0);

		_findclose(handle);
	}
}

void get_pos(Mat& trainingImages, vector<int>& trainingLabels)
{
	vector<string> files;
	getFiles(posPath, files);
	int number = files.size();
	for (int i = 0; i < number; i++) 
	{
		Mat src = imread(files[i].c_str(),0);
		//Mat kernel = (Mat_<float>(3, 3) << 1, 1, 1, 1, -8, 1, 1, 1, 1);
		//filter2D(src, src, -1, kernel);
		// ��LBP����
		//Mat lbp_img;
		//LBP(src, lbp_img);
		//imshow("lbp", lbp_img);
		//waitKey(15);
		//destroyAllWindows();
		// ת����hash�ַ���,�ַ���ת����vector<int>
		vector<int> hash = aHashValue(src);
		Mat dst = Mat(hash);
		dst = dst.reshape(1, 1);
		//cout << dst << endl;
		trainingImages.push_back(dst);
		trainingLabels.push_back(1);  // ��ʾ������
	}
}

void get_neg(Mat& trainingImages, vector<int>& trainingLabels)
{
	vector<string> files;
	getFiles(negPath, files);
	int number = files.size();
	for (int i = 0; i < number; i++) 
	{
		Mat src = imread(files[i].c_str(),0);
		//Mat kernel = (Mat_<float>(3, 3) << 1, 1, 1, 1, -8, 1, 1, 1, 1);
		//filter2D(src, src, -1, kernel);
		// ��LBP����
		//Mat lbp_img;
		//LBP(src, lbp_img);
		//imshow("test", lbp_img);
		//waitKey(30);
		// ת����hash�ַ���,�ַ���ת����vector<int>
		vector<int> hash = aHashValue(src);
		Mat dst = Mat(hash);
		dst = dst.reshape(1, 1);
		trainingImages.push_back(dst);
		trainingLabels.push_back(-1);  // ��ʾ��������
	}
}