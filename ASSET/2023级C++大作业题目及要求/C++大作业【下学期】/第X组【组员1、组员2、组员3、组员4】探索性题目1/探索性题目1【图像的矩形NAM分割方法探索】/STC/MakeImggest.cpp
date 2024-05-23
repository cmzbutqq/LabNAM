#include "stdafx.h"
#include "FUNCTIONS.h"

void MakeImggest ( IplImage* &imggest , vector<colorListStandard> &P , vector<doubleCoordinate> C , Region** all_region )//½¨Á¢gestÍ¼Ïñ
{
	uchar g1=0,g2=0,g3=0,g4=0;
	for (unsigned int i=0;i<P.size();i++)
	{
		 g1 = P[i].g1;g2 = P[i].g2;
		 g3 = P[i].g3;g4 = P[i].g4;
		 int x1=C[i].x1,x2=C[i].x2;
		 int y1=C[i].y1,y2=C[i].y2;

		if(x1 == x2 && y1 == y2)
		{
			uchar* ptr = (uchar*) (imggest->imageData+y1*imggest->widthStep);
			ptr[x1] = g1;
		}
		else if(x1 == x2)
		{
			for(int y=y1;y<=y2;y++)
		    {
				double i1 = (double)(y-y1) / (double)(y2 - y1);
				(imggest->imageData + imggest->widthStep*y)[x1] = (int)(g1 + (g2 - g1)*i1);
				
		    }
		}
		else if(y1 == y2)
		{
			for(int x = x1;x<=x2;x++)
		   {
				double i2 = (double)(x - x1) / (double)(x2 - x1);
				(imggest->imageData+y1*imggest->widthStep)[x] =(int)(g1 + (g2 - g1)*i2);
		   }
		}
		else
		{
			 for(int y = y1;y<=y2;y++)
			{
				   uchar* ptr = (uchar*) (imggest->imageData+y*imggest->widthStep);

					for (int x = x1;x<=x2;x++)
					{
							double i1 = (double)(y-C[i].y1)/(C[i].y2-C[i].y1);
							double i2 = (double)(x-C[i].x1)/(C[i].x2-C[i].x1);
							double g5 = g1+(g2-g1)*i2;
							double g6 = g3+(g4-g3)*i2;
							ptr[x] = g5+(g6-g5)*i1;
					}
			 }
		}
	
	}
}
