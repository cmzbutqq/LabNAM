#include "stdafx.h"
#include "FUNCTIONS.h"

//bool JudgeSameBlock ( uchar epsilon , IplImage *&img1 , int x1 , int y1 ,int x2 , int y2 )//判断矩形是否为同类块lzj
bool JudgeSameBlock ( double epsilon , IplImage *&img1 , int x1 , int y1 ,int x2 , int y2 )//判断矩形是否为同类块zyp
{

	uchar* ptrtemp = (uchar*) (img1->imageData+y1*img1->widthStep);
	uchar g1 = ptrtemp[x1],g2 = ptrtemp[x2];
	ptrtemp = (uchar*) (img1->imageData+y2*img1->widthStep);
	uchar g3 = ptrtemp[x1],g4 = ptrtemp[x2];

	 for(int y = y1;y<=y2;y++)
	{
		uchar* ptr = (uchar*) (img1->imageData+y*img1->widthStep);

			for (int x = x1;x<=x2;x++)
			{
			uchar g = ptr[x];
			double i1 = (double)(y-y1)/(y2-y1);
			double i2 = (double)(x-x1)/(x2-x1);
			double g5 = g1+(g2-g1)*i2;//zyp
			double g6 = g3+(g4-g3)*i2;//zyp
			double gest = g5+(g6-g5)*i1;//zyp
            //printf("g=%f  g5=%f g6=%f  gest=%f  \n",g, g5,g6,gest);
			//printf("g-gest=%f \n",g-gest);
				if (g-gest>=-epsilon&&g-gest<=epsilon)

				{continue;}
				else {return false;}

			}
	 }



return true;


}