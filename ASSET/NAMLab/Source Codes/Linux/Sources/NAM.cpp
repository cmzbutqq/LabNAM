/*************************************************
author: Bowen Yang
date:2019/04/19
describe: NAM based hierarchical image segmentation algorithm.
**************************************************/
#include "NAM.h"
#include "rgb2lab.h"

void NAM(unordered_map<string, double> &param, const string &imgPath, vector<Mat> &map, vector<Mat> &result)
{
	Mat img = imread(imgPath);
	if (!img.data || img.channels() != 3)
		return;
	const int &M = img.rows;
	const int &N = img.cols;

	Mat lab = Mat::zeros(M, N, CV_32FC3);
	vector<Coordinate> P; //coordinate queue
    vector<ColorVariance> R; //color queue
    int NumSeg = 0;
    vector<vector<int>> blockMap(M);    //index queue
    for (auto &x : blockMap) x.resize(N);
    vector<Region> region;
    vector<Vec2i> adjacent;
    list<Vec2i> adjacentList;

	switch ((int)param["lab"])
	{
	case 0://D50
		lab.convertTo(lab, CV_32FC3);
		for (int i = 0; i < M; i++)
		{
			for (int j = 0; j < N; j++)
			{
				Vec3b &c = img.at<Vec3b>(i, j);
				Vec3f &l = lab.at<Vec3f>(i, j);
				float L, A, B;
				RGBToLabD50(c[2], c[1], c[0], L, A, B);
				l[0] = L;
				l[1] = A;
				l[2] = B;
			}
		}
		break;
	case 1://D65
		img.convertTo(img, CV_32FC3, 1.0 / 255, 0);
		cvtColor(img, lab, COLOR_BGR2Lab);
		img.convertTo(img, CV_8UC3, 255.0, 0);
		break;
	}

	representation(param,lab,P,R,blockMap);

	mergence(param,P,R,NumSeg,blockMap);

	removeRemnant(param,lab,NumSeg,blockMap,region,map,result,adjacent,adjacentList);

	scanning(param,region,blockMap,adjacentList,lab,img,map,result);
}
