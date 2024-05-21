#include "Header.h"

void SetMarkMatrix(CvMat *markMatrix,int x1,int y1,int x2,int y2,int value)
{
	for(int y = y1;y<=y2;y++)
	{
		for(int x = x1;x<=x2;x++)
		{
			(markMatrix->data.ptr + markMatrix->step*y)[x] = value;
		}
	}
}

bool IsSameBlock(const IplImage *img,int x1,int y1,int x2,int y2,int margin)
{
	uchar *gy1 = (uchar*)img->imageData + y1*img->widthStep;
	uchar *g1 = gy1 + x1;
	uchar *g2 = gy1 + x2;
	uchar *gy2 = (uchar*)img->imageData + y2*img->widthStep;
	uchar *g3 = gy2 + x1;
	uchar *g4 = gy2 + x2;
	bool returnValue = true;

	if(x1 == x2  && y1 == y2)
	{
		returnValue = true;
	}
	else if(y1 == y2)
	{
		for(int x = x1+1;x<x2;x++)
		{
			double i2 = (double)(x - x1) / (double)(x2 - x1);
			double g = *g1 + (*g4 - *g1)*i2;
			uchar *gValue = gy1 + x;
			if(abs(*gValue - g) > margin)
			{
				returnValue = false;
				break;
			}

		}
	}
	else if(x1 == x2)
	{
		for(int y=y1+1;y<y2;y++)
		{
			double i1 = (double)(y-y1) / (double)(y2 - y1);
			double g = *g1 + (*g4 - *g1)*i1;
			uchar *gy = (uchar*)img->imageData + y*img->widthStep;
			uchar *gValue = gy + x1;
			if(abs(*gValue - g) >margin)
			{
				returnValue = false;
				break;
			}
		}
	}
	else
	{
		for(int x = x1; x<=x2;x++)
		{
			for(int y = y1;y<=y2;y++)
			{
				double i1 = (double)(y - y1)/(double)(y2 - y1);
				double i2 = (double)(x - x1)/(double)(x2 - x1);
				double g5 = *g1 + (*g2 - *g1)*i2;
				double g6 = *g3 + (*g4 - *g3)*i2;
				double g = g5 + (g6 - g5) *i1;
				uchar *gy = (uchar*)img->imageData + y*img->widthStep;
			    uchar *gValue = gy + x;
				if(abs(*gValue - g) >margin)
				{
					returnValue = false;
					break;
				}
			}
		}
	}

	return returnValue;
}



void StartNamCut(const IplImage *img,CvMat *markMatrix,CvMat *R,map<unsigned int,ColorNode> &color_list,map<unsigned int,Location> &block_list,int height,int width,double margin,int &num)
{

	unsigned int *block = new unsigned int[height*width];
	for(int i=0;i<height*width;i++)
	{
		block[i] = 0;
	}

	for(int y = 0;y < height;y++)
	{
		int x = 0;
		uchar *p_y = (uchar *)(img->imageData + y*img->widthStep);

		while(x < width)
		{
			int start_pos = x;
			while(x < width)
			{
				x++;
				if(!IsSameBlock(img,start_pos,y,x,y,margin))
				{
					break;
				}
			}

			x--;
			if(0 == y)
			{
				Location loc;
				ColorNode color;

				if(start_pos == x)
				{
					(R->data.ptr + R->step*y)[x] = 3;
					block[y*width + x] = ++num;
					loc.x1 = loc.x2 = x;
					loc.y1 = loc.y2 = y;

					color.kind = 3;
					color.g1 = p_y[x];
					color.g2 = color.g3 = color.g4 = -1;
				}
				else
				{
					(R->data.ptr + R->step*y)[start_pos] = 1;
					(R->data.ptr + R->step*y)[x] = 2;
					++num;

					for(int j = start_pos;j<=x;j++)
					{
						block[y*width + j] = num;
					}

					loc.x1 = start_pos;
					loc.x2 = x;
					loc.y1 = loc.y2 = y;

					color.kind = 1;
					color.g1 = p_y[start_pos];
					color.g2 = p_y[x];;
					color.g3 = color.g4 = -1;
				}

				block_list.insert(make_pair(num,loc));
				color_list.insert(make_pair(num,color));
			}
			else
			{
				int key;
				map<unsigned int,Location>::iterator it;
				map<unsigned int,ColorNode>::iterator c_it;
				key = block[(y-1)*width + start_pos];
				it = block_list.find(key);
				c_it = color_list.find(key);

				if(it->second.x1 == start_pos && it->second.x2 == x && IsSameBlock(img,start_pos,it->second.y1,x,y,margin) )
				{
					it->second.x2 = x;
					it->second.y2 = y;
					

					if(3 == (R->data.ptr + R->step*(y-1))[x])
					{
						(R->data.ptr+R->step*(y-1))[x] = 1;
						c_it->second.g3 = ((uchar *)(img->imageData + y*img->widthStep))[start_pos];
						c_it->second.kind = 2;
					}
					else
					{
						(R->data.ptr+R->step*(y-1))[x] = 0;
						c_it->second.g3 = ((uchar *)(img->imageData + y*img->widthStep))[start_pos];
						c_it->second.g4 = ((uchar *)(img->imageData + y*img->widthStep))[x];
						c_it->second.kind = 0;
					}

					(R->data.ptr+R->step*y)[x] = 2;
				}
				else
				{
					Location loc;
					ColorNode color;

					if(start_pos == x)
					{
						(R->data.ptr + R->step*y)[x] = 3;
						loc.x1 = loc.x2 = x;
						loc.y1 = loc.y2 = y;

					    color.kind = 3;
					    color.g1 = p_y[x];
					    color.g2 = color.g3 = color.g4 = -1;
					}
					else
					{
						(R->data.ptr + R->step*y)[start_pos] = 1;
						(R->data.ptr + R->step*y)[x] = 2;

						loc.x1 = start_pos;
						loc.x2 = x;
						loc.y1 = loc.y2 = y;

						color.kind = 1;
					    color.g1 = p_y[start_pos];
					    color.g2 = p_y[x];;
					    color.g3 = color.g4 = -1;
					}
					key = ++num;
					block_list.insert(make_pair(num,loc));
					color_list.insert(make_pair(num,color));
				}

				for(int j = start_pos;j<=x;j++)
				{
					block[y*width + j] = key;
				}
			}

			x++;
		}

	}

	delete[] block;

	//for(int row = 0;row < height;row++)
	//{
	//	for(int col = 0;col < width;col++)
	//	{
	//		if((markMatrix->data.ptr+row*markMatrix->step)[col] == 0)
	//		{
	//			num++;
	//			Location loc = FindSameBlock(img,markMatrix,R,col,row,margin,ratio);
	//			LocList.push_back(loc);
	//			//Mark
	//			SetMarkMatrix(markMatrix,loc.x1,loc.y1,loc.x2,loc.y2,1);
	//			//R
	//			if(loc.x1 == loc.x2 && loc.y1 == loc.y2)
	//			{
	//				uchar * g = R->data.ptr + R->step*loc.y1;
	//				g[loc.x1] = 3;
	//				ColorNode node(3,((uchar*)img->imageData + img->widthStep*loc.y1)[loc.x1]);
	//				ColorList.push_back(node);
	//			}
	//			else if(loc.x1 == loc.x2)
	//			{
	//				for(int j=loc.y1;j<=loc.y2;j++)
	//				{
	//					uchar *g = R->data.ptr + R->step*j;
	//					g[loc.x1] = 0;
	//				}
	//				(R->data.ptr + R->step*loc.y1)[loc.x1] = 1;
	//				(R->data.ptr + R->step*loc.y2)[loc.x1] = 2;
	//				ColorNode node(2,((uchar*)img->imageData + img->widthStep*loc.y1)[loc.x1],((uchar*)img->imageData + img->widthStep*loc.y2)[loc.x1]);
	//				ColorList.push_back(node);
	//				
	//			}
	//			else
	//			{
	//				for(int i=loc.y1;i<=loc.y2;i++)
	//				{
	//					for(int j = loc.x1;j<=loc.x2;j++)
	//					{
	//						(R->data.ptr + R->step*i)[j] = 0;
	//					}
	//				}

	//				if(loc.y1 == loc.y2)
	//				{
	//					ColorNode node(1,((uchar*)img->imageData + img->widthStep*loc.y1)[loc.x1],((uchar*)img->imageData + img->widthStep*loc.y1)[loc.x2]);
	//					ColorList.push_back(node);
	//				}
	//				else
	//				{
	//					ColorNode node(0,((uchar*)img->imageData + img->widthStep*loc.y1)[loc.x1],((uchar*)img->imageData + img->widthStep*loc.y1)[loc.x2],
	//						((uchar*)img->imageData + img->widthStep*loc.y2)[loc.x1],((uchar*)img->imageData + img->widthStep*loc.y2)[loc.x2]);
	//					ColorList.push_back(node);
	//				}


	//				(R->data.ptr + R->step*loc.y1)[loc.x1] = 1;
	//				(R->data.ptr + R->step*loc.y2)[loc.x2] = 2;
	//			}
	//		}
	//	}
	//}
}