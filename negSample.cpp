#include"myHead.h"
/*
	�Ӳ�������(����)����Ƭ�ü�64x128�ĸ�����
	���ڣ�ע�ͺ��ǣ���������ڵĽ�ͼ�ó�2000�Ÿ�����
*/
extern void getFiles(string path, vector<string>& files);

/*int main()
{
	int counter = 0;
	string path = "D://Program//C++//proj//phash_svm//pic2.png";
	vector<string> files;
	char saveName[256];
	//getFiles(path, files);
	//cout << files.size() << endl;
	//for (int i = 0; i < files.size(); i++)
	//{
		//Mat src = imread(files[i].c_str());
		Mat src = imread(path);
		imshow("test", src);
		waitKey(0);
		// ͼƬӦ����64x128
		if (src.cols > 100 && src.rows > 120) {
			srand(time(NULL));   // �����������
			// ��ÿ��ͼƬ�м���10��64x128��С�ĸ�����
			for (int i = 0; i < 1000; i++)
			{
				// �������������Ͻ�����
				int x = (rand() % (src.cols - 100));
				int y = (rand() % (src.rows - 120));
				Mat imgROI = src(Rect(x, y, 100, 120));
				sprintf_s(saveName, "neg2//example2_%d.jpg", ++counter);
				imwrite(saveName, imgROI);   // ע��imwrite�������ļ����Ƿ���ڣ���������д
			}
		}
	//}
	cout << "�õ���������" << counter << endl;
	return 0;
}*/