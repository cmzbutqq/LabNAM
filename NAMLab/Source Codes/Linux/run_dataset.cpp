/*************************************************
author: Bowen Yang
date:2021/01/10
describe: datasets
**************************************************/
#include <iomanip>
#include <sys/stat.h>
#include "NAM.h"
#include "convertToMat.h"
#include "getImageList.h"

// ./run_dataset inputDirectory outputDirectory mode saveHir

// ./run_dataset ../BSDS500/images ../BSDS500/precomputedResults 0 60

int main(int argc, char * argv[])
{
	if (argc < 5)	return 0;
	string inDir = argv[1];
	inDir = inDir + '/';

	string outDir = argv[2];
	outDir = outDir + '/';

	mkdir(outDir.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

	unordered_map<string, double> param;

	/* Output */
	param["mode"] = atof(argv[3]);		// 0: Only label 1: Output images and label
	param["saveHir"] = atof(argv[4]);	// Number of saved images (in our paper it is 60)

	/* Rgb2lab */
	param["lab"] = 0;					// Light source 0:D50 1:D65

	/* Representation */
	param["homogeneous"] = 0;			// Dissimilarity between two pixels. 0:Euclidean Eq.(10) 1:Gouraud Eq. (11)
	param["k"] = 2.0;					// Threshold in Eq. (10) or Eq. (11)
	param["shape"] = 0;					// Shape of homogeneous blocks 0:Square 1:Diagonal 2:Vertical 3:Diagonal
	param["ratio"] = 1.0;				// Maximum ratio of height to width of homogeneous blocks

	/* Mergence */
	param["u"] = 1.9;					// Mean
	param["var"] = 3.0;					// Variance

	/* Scanning */
	param["alpha"] = 1.0;				//
	param["beta"] = 1.97;				//
	param["gamma"] = 1.97;				//
	param["percent"] = 6.7;				// Scanning
	param["si"] = 67.0;					//
	param["size"] = 4700.0;				//
	param["change"] = 197;				//

	/* Display in terminal */
	param["seg"] = 0;					// Number of segments after removing remnant regions
	param["remnant"] = 0;
	param["scanning"] = 0;				// Cost time
	param["representation"] = 0;
	param["mergence"] = 0;

    double avgPhase1Time, avgPhase2Time, avgCostTime, avgSeg;
    avgPhase1Time = avgPhase2Time = avgCostTime = avgSeg = 0;
    int count = 1;

    vector<string> imageList;
    getImageList(inDir.c_str(), imageList);

	for (auto &x : imageList) {
		param["seg"] = 0;
		param["representation"] = 0;
		param["mergence"] = 0;
		param["remnant"] = 0;
		param["scanning"] = 0;

		vector<Mat> map;
		vector<Mat> result;

		NAM(param, inDir + x, map, result);

		if (param["mode"] == 0)
		{
			convertToMat(map, outDir + x.substr(0, x.size() - 4) + ".mat");
			for (auto &x : map)
				x.release();
		}
		else if (param["mode"] == 1)
		{
			Mat img = imread(inDir + x);
			if (!img.data || img.channels() != 3)
				return -1;
			const int &M = img.rows;
			const int &N = img.cols;

			for (int i = 0; i < result.size(); i++)
			{
				Mat mark = Mat::zeros(M, N, CV_8UC1);
				Mat mask = img.clone();
				Mat &mean = result[result.size() - 1 - i];

				imwrite(outDir + x.substr(0, x.size() - 4) + string("_Hier_") + to_string(i + 1) + string("_MeanNoBoundaryLine") + ".png", mean);
				for (int m = 0; m < M; m++)
					for (int n = 0; n < N; n++)
						if (!mark.at<uchar>(m, n) && m >= 1 && m < M - 1 && map[map.size() - 1 - i].at<float>(m - 1, n) != map[map.size() - 1 - i].at<float>(m + 1, n) && !mark.at<uchar>(m - 1, n) && !mark.at<uchar>(m + 1, n)
							|| n >= 1 && n < N - 1 && map[map.size() - 1 - i].at<float>(m, n - 1) != map[map.size() - 1 - i].at<float>(m, n + 1) && !mark.at<uchar>(m, n - 1) && !mark.at<uchar>(m, n + 1))
						{
							mark.at<uchar>(m, n) = 1;
							mask.at<Vec3b>(m, n) = Vec3b(0, 0, 255);
							mean.at<Vec3b>(m, n) = Vec3b(0, 0, 255);
						}

				imwrite(outDir + x.substr(0, x.size() - 4) + string("_Hier_") + to_string(i + 1) + string("_Mask") + ".png", mask);
				imwrite(outDir + x.substr(0, x.size() - 4) + string("_Hier_") + to_string(i + 1) + string("_Mean") + ".png", mean);

				mean.release();
				mask.release();
				mark.release();
			}

			convertToMat(map, outDir + x.substr(0, x.size() - 4) + ".mat");
			for (auto &x : map)
				x.release();
		}

		avgSeg += param["seg"];

		double p1, p2, cost;
		p1 = param["representation"] + param["mergence"] + param["remnant"];
		p2 = param["scanning"];
		cost = p1 + p2;

		std::cout << setw(4) << count++ << " ";
		std::cout << setw(10) << x.substr(0, x.size() - 4) << "\t";
		std::cout << setw(4) << cost << " s" << endl;

		avgPhase1Time += p1;
		avgPhase2Time += p2;
		avgCostTime += cost;
	}

    count--;
    cout << "Average numSeg :" << avgSeg / (1.0 * count) << endl;
    cout << "Average phase1Time: " << avgPhase1Time / (1.0 * count) << " s" << endl;
    cout << "Average phase2Time: " << avgPhase2Time / (1.0 * count) << " s" << endl;
    cout << "Average costTime: " << avgCostTime / (1.0 * count) << " s" << endl;

	return 0;
}
