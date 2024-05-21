#include "Header.h"
//../gray_images/barbarazyp512.bmp ../gray_images/barbarazyp512XXXgray.bmp ../gray_images/barbarazyp512XXXrnamc.bmp 20
int main(int argc,char **argv)
{
	IplImage *img = NULL;

	if(argc == 5 && (img = cvLoadImage(argv[1],0)) != 0)
	{

		cvNamedWindow("ԭͼ�Ҷ�ͼ��",1);
		cvShowImage("ԭͼ�Ҷ�ͼ��",img);
		/*һ���ָ�ͬ��鼰����*/
		int height = img->height;
		int width = img->width;

		CvMat *markMatrix = cvCreateMat(height,width,CV_8UC1);
		cvSetZero(markMatrix);
		CvMat *R = cvCreateMat(height,width,CV_8UC1);
		cvSetZero(R);

		int num = 0;
		map<unsigned int,ColorNode> color_list;
		map<unsigned int,Location> block_list;
		double margin = atof(argv[4]);
		time_t begin,end;
		begin = clock();
		/*�ֿ�*/
		StartNamCut(img,markMatrix,R,color_list,block_list,height,width,margin,num);

		/*�������*/
		vector<char> Q;
		EnCode(R,height,width,Q);
		end = clock();

		cout<<"����ѹ������:"<<end-begin<<"ms"<<endl;

		/*for(int i =0;i<height;i++)
		{
			for(int j=0;j<width;j++)
			{
				cout<<(int)(R->data.ptr+i*R->step)[j]<<" ";
			}
			cout<<endl;
		}

		
		cout<<"���빲��"<<Q.size()<<"λ"<<endl;
		for (vector<char>::iterator it = Q.begin();it != Q.end();it++)
		{
			cout<<*it;
		}*/

		/*for (vector<ColorNode>::iterator it = colorList.begin();it != colorList.end();it++)
		{
			cout<<(*it).g1<<" "<<(*it).g2<<" "<<(*it).g3<<" "<<(*it).g4<<endl;
		}*/

		/*������ԭͼ�����ͼ��*/
		CvMat *T = cvCreateMat(height,width,CV_8UC1);
		cvSetZero(T);
		begin = clock();
        Decode(T,height,width,Q);
	

		/*cout<<endl;
		for(int i =0;i<height;i++)
		{
			for(int j=0;j<width;j++)
			{
				cout<<(int)(T->data.ptr+i*T->step)[j]<<" ";
			}
			cout<<endl;
		}*/

		
		IplImage *newImg = cvCreateImage(cvSize(width,height), 8, 1);
		RestoreImage(newImg,markMatrix,T,color_list,height,width);
		end = clock();

		
		cout<<"��ԭͼ���ʱ:"<<end-begin<<"ms"<<endl;

		
		cout<<"����:"<<num<<endl;
	    cout<<"PSNRֵ:"<<PSNR(img,newImg)<<endl;
		double BPPValue=BPP(color_list,width,height,Q);
	    cout<<"BPPֵ:"<<BPPValue<<endl;
	    cout<<"CRֵ:"<<8.0/BPPValue<<endl;

		cvNamedWindow("ѹ��ͼ�Ҷ�ͼ��",1);
		cvShowImage("ѹ��ͼ�Ҷ�ͼ��",newImg);
		cvSaveImage(argv[2],img,0);
	    cvSaveImage(argv[3],newImg,0);

		//���ָ�ͼ
		IplImage* sketch;
	    int xr,yr;
	    int sketchXn,sketchYn;
	    if (height>=256||width>=256) 
		{
			xr=1,yr=1,sketchXn=height,sketchYn=width;
		    sketch = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U,1);
	    }
		else
		{
		xr=511/(height-1);
		yr=511/(width-1);
		sketchXn=512,sketchYn=512;
		sketch = cvCreateImage(cvSize(512,512), IPL_DEPTH_8U,1);
	    }

	    for(int i = 0;i<sketchYn;i++)
		{
		   uchar* ptrsketch = (uchar*) (sketch->imageData+i*sketch->widthStep);
		   for (int j = 0;j<sketchXn;j++)
		   {
			   ptrsketch[j]=255;
		   }
	     }
	     for (int i=0 ; i<block_list.size();i++)
	     {
			   if (block_list[i].x1==0&&block_list[i].y1==0)
			   cvRectangle(sketch,cvPoint(block_list[i].x1,block_list[i].y1),cvPoint(block_list[i].x2,block_list[i].y2),cvScalar(0x00,0x00,0x00));
			   else   if (block_list[i].x1==0&&block_list[i].y1!=0)
			   cvRectangle(sketch,cvPoint(block_list[i].x1,block_list[i].y1-1),cvPoint(block_list[i].x2,block_list[i].y2),cvScalar(0x00,0x00,0x00));
			   else   if (block_list[i].x1!=0&&block_list[i].y1==0)
			   cvRectangle(sketch,cvPoint(block_list[i].x1-1,block_list[i].y1),cvPoint(block_list[i].x2,block_list[i].y2),cvScalar(0x00,0x00,0x00));
			   else   if (block_list[i].x1!=0&&block_list[i].y1!=0)
			   cvRectangle(sketch,cvPoint(block_list[i].x1-1,block_list[i].y1-1),cvPoint(block_list[i].x2,block_list[i].y2),cvScalar(0x00,0x00,0x00));
	     }
	    cvShowImage("�ָ�ʾ��ͼ",sketch);

		cvWaitKey();
		cvDestroyAllWindows();
	}

	return 0;
}