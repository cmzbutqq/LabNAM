//used in paper 72
// STC is equal to BSP in conception
//���˱� ���һ������Ϊ0ʱ�൱������ε�STC���� ���ҿ������٣���������Ϊ1ʱ�����϶ࡿ
//��ͮ ���һ������Ϊ1ʱ�൱������ε�STC����   ���ҿ������٣���������Ϊ0ʱ�����϶ࡿ

//  ../gray_images/brain512_1.bmp   ../gray_images/f16XXXgray.bmp    ../gray_images/f16XXXstc.bmp 10 30 225   1       //  used in paper 72


//  ../gray_images/decho512.bmp   ../gray_images/f16XXXgray.bmp    ../gray_images/f16XXXstc.bmp 10 30 225   1       //  used in paper 72


//  ../gray_images/liver512.bmp   ../gray_images/f16XXXgray.bmp    ../gray_images/f16XXXstc.bmp 10 30 225   1      //  used in paper 72



//  ../gray_images/hands512.bmp   ../gray_images/f16XXXgray.bmp    ../gray_images/f16XXXstc.bmp 10 30 225   1       //  used in paper 72





//  ../gray_images/cameraman512.bmp   ../gray_images/f16XXXgray.bmp    ../gray_images/f16XXXstc.bmp 10 30 225   1   // used in paper 67

//  ../gray_images/boatzyp512.bmp       ../gray_images/f16XXXgray.bmp     ../gray_images/f16XXXstc.bmp 10 30 225    1   // used in paper 67

//  ../gray_images/lenazyp512.bmp       ../gray_images/f16XXXgray.bmp      ../gray_images/f16XXXstc.bmp 10 30 225   1   // used in paper 67

//  ../gray_images/flightzyp512.bmp      ../gray_images/f16XXXgray.bmp      ../gray_images/f16XXXstc.bmp 10 30 225   1   // used in paper 67


// STCMethod.cpp : �������̨Ӧ�ó������ڵ㡣 
#include "stdafx.h"
#include "FUNCTIONS.h"

int reg_num = 0;
int bitnum = 0;
double thresU = 0;
double thresVar = 0;
int cur_block = -1;
int main( int argc, char** argv )//�ֱ�����1.�����ַ2.ԭ��ͼ3.ת���Ҷ�ͼ�ļ���4.ת��RNAMC�ļ���5.ͬ��췧ֵ6.��ֵ��ֵ7.���ֵ8.�з� 1 ˮƽ 0��ֱ
{
	int nmb = 0;
	IplImage* img1;
  //cout << "start" << endl;
	if( argc == 8 && (img1 = cvLoadImage( argv[1], 0)) != 0 )   //��Դ��ɫͼ��imgת����Ŀ���ɫͼ�����
//	if(( img1 = cvLoadImage("cameraman.tif", 0)) != 0)
    {    
	//	 cout << "img readed" << endl;
	  /*int sum=0;
      for (int row=0;row<img1->height;row++)
      {
	  uchar* p=(uchar*) (img1->imageData+row*img1->widthStep);
	  for (int col=0;col<img1->width;col++)
	  {   
		  
		  sum+=*p;
		  printf("%3d ", *p++);
		  
	    }
	    printf("\n\n");
       }
		printf("\n%d\n",sum);*/

	 //// added by zyp begin
 	//cout << "Display the data matrix of the source image:" << endl;
	 //for(int y = 0;y<img1->height;y++)
  //  {
		//	uchar* ptr = (uchar*) (img1->imageData+y*img1->widthStep);

		//	for (int x = 0;x<img1->width;x++)
		//	{
		//		printf ("%5d",*ptr++);
		//	}
  //          printf("\n\n");
  //  }
	 //// added by zyp end




		time_t start,end,time,converge_start, converge_end, converge_time; //��ʱ����
    	

	   IplImage* imggest = cvCreateImage(cvGetSize(img1), img1->depth, img1->nChannels); //����ͬ����ͼ��gest
	   cvSetZero(imggest);

       int num = atoi(argv[7]);
	   int M = img1->height;  //��(after)
	   int N = img1->width;   //��(before)
	   double epsilon = atof(argv[4]);
	
	  
	   vector<doubleCoordinate> C;//���������
	   vector<colorListStandard>P;//������ɫ��
	   vector<char> Q;//������������
	   treeNode *root=new treeNode; //���������
	   InitialNode (root);
		  thresU = atof(argv[5]);
		 thresVar = atof(argv[6]);
	    //��������ͼ��
	   IplImage* sketch = cvCreateImage(cvGetSize(img1), IPL_DEPTH_8U,1); 
	  /* for(int y = 0;y<M;y++)             
		{
			uchar* ptrsketch = (uchar*) (sketch->imageData+y*sketch->widthStep);

				for (int x = 0;x<N;x++)
				{
				 ptrsketch[x]=255;
				}
		 }*/
	  //����ͼ���ʼ�����

	   start=clock();
	   cout << "building tree" << endl;
	   BuildTreeT (  img1 , root , P , C , num , epsilon , 0 , 0 , M-1 ,N-1);
		cout << "making  Q" << endl;
	   LevelOrder(Q , root );//Ѱ��ͬ��飬��������������ɫ��,�����

	   end=clock();
	   time=end-start;
	   cout  << "��������ʱ��:" << time << "ms" << endl;

	

	   start=clock();
	  
	   end=clock();

	   time=end-start;

       ofstream fout("Results.txt");
	   cout  << "��������ʱ��:  " << time << "  ms" << endl<<endl;	

       cout << "epsilon =  " << epsilon << endl << endl;
       fout << "epsilon =  " << epsilon << endl << endl;

	   cout << "================================================"  << endl<<endl;	

      //ofstream fout("Results.txt",ios::app);
	 

	   cout << "����:  " << P.size() << endl<<endl;	

       fout << "����:  " << P.size() << endl<<endl;	

	   cout << fixed << setprecision(4)  << "BPP:" << BPP ( P , M , N , Q ) << endl<<endl;
       fout << fixed << setprecision(4)  << "BPP:  " << BPP ( P , M , N , Q ) << endl<<endl;

       //cout << fixed << setprecision(4)  << "CR:  " << 8.0/BPP ( P , M , N , Q ) << endl<<endl;	
	   //fout << fixed << setprecision(4)  << "CR:  " << 8.0/BPP ( P , M , N , Q ) << endl<<endl;	

       


       
	  

       converge_start=clock(); 
	   Region** all_region = new Region*[P.size()];


		Segment* UpperLeft = new Segment;

		Segment* Upper = new Segment;

		UpperLeft->Length = M;
		UpperLeft->ActiveELink = NULL;
		UpperLeft->PreLink = NULL;
		UpperLeft->SucLink = Upper;

		Upper->Length = M;
		Upper->ActiveELink = NULL;
		Upper->PreLink = UpperLeft;
		Upper->SucLink = NULL;

		Segment* UpperRight = NULL;
		Segment* PreLowerLeft = NULL;

		num = atoi(argv[7]);
	    Region_Segm(UpperLeft , UpperRight , PreLowerLeft , 0 , 0 , M ,N,   all_region ,P , C  ,Q ,num);


	    converge_end=clock(); 
        converge_time=converge_end - converge_start;
        cout << "converge_time of QSC:  " << converge_time<< "  ms"<< endl<<endl;	

        fout << "converge_time of QSC:  " << converge_time<< "  ms"<< endl<<endl;

	     Region** pixel_region = new Region*[M*N];
	

	    IplImage* seg = cvCreateImage(cvGetSize(img1), IPL_DEPTH_8U,1); 
			for (unsigned int i=0;i<P.size();i++)
		{
		   int x1=C[i].x1,x2=C[i].x2;
		   int y1=C[i].y1,y2=C[i].y2;

	 for(int y = y1;y<=y2;y++)
	{
		  uchar* ptrsketch = (uchar*) (seg->imageData+y*seg->widthStep);

			for (int x = x1;x<=x2;x++)
			{
				ptrsketch[x] = FindParent(all_region[i])->Mean;
				pixel_region[y*N+x] = FindParent(all_region[i]);
			}
		 }
	}


   IplImage* seg_line = cvCreateImage(cvGetSize(img1), IPL_DEPTH_8U,1); 
   for(int y = 0;y<M;y++)    
    {
      uchar* ptrsketch = (uchar*) (seg_line->imageData+y*seg_line->widthStep);

        for (int x = 0;x<N;x++)
        {
			if (x == N-1 || y == M-1)
			{
				ptrsketch[x] = 0;
				break;
			}
			ptrsketch[x]=(pixel_region[y*N+x] != pixel_region[y*N+x+1] || pixel_region[y*N+x] != pixel_region[(y+1)*N+x])? 0 : 255;
			

        }
     }


   // added by zyp add box begin!
   for(int y = 0;y<M;y++)    
    {
      uchar* ptrsketch = (uchar*) (seg_line->imageData+y*seg_line->widthStep);
      
        for (int x = 0;x<N;x++)
        {
			if ((y==0)||(y==M-1))
				ptrsketch[x] = 0;
			else if ((x==0))
				ptrsketch[x]=0;
	     }
     }
   // added by zyp add box end!

      cvShowImage("����ϲ�ʾ��ͼ1",seg);
      cvShowImage("����ϲ�ʾ��ͼ2",seg_line);

	  MakeImggest ( imggest , P , C ,all_region);

	   cout << "PSNR of recontructured:  " << PSNR( img1 , imggest ) <<endl<<endl;
       //cout << "PSNR of segmentation:" << PSNR( img1 ,seg ) << endl<<endl;	
	   fout << "PSNR of recontructured:  " << PSNR( img1 , imggest ) <<endl<<endl;

       cvNamedWindow("�ҶȻ�ͼ��", CV_WINDOW_AUTOSIZE); 
	   cvShowImage("�ҶȻ�ͼ��", img1); //��ʾԭʼ�Ҷ�ͼ��
	   cvNamedWindow("QSC����ָ���ͼ��",CV_WINDOW_AUTOSIZE);     //����ָ���ͼ��
	   cvShowImage("QSC����ָ���ͼ��",imggest);//����ת����ĻҶ�ͼ��   //����ָ���ͼ��

	   cvSaveImage(argv[2], img1, 0);//��ͼ��д���ļ�
	  cvSaveImage(argv[3], imggest, 0);//��ͼ��д���ļ�
	   //��ʾ��ͼ
	   cvNamedWindow("�ָ�ʾ��ͼ",CV_WINDOW_AUTOSIZE);
	        if (N>=256||M>=256)
	   {
	   //��������ͼ��
	   IplImage* sketch = cvCreateImage(cvGetSize(img1), IPL_DEPTH_8U,1); 
	   for(int y = 0;y<M;y++)             
		{
			uchar* ptrsketch = (uchar*) (sketch->imageData+y*sketch->widthStep);

				for (int x = 0;x<N;x++)
				{
				 ptrsketch[x]=255;
				}
		 }
	  //����ͼ���ʼ�����
     
	   // ��ԭʼͼ���мӾ���ʱ��ֻ�轫cvRectangle��cvShowImage("�ָ�ʾ��ͼ",sketch512��sketch);�е�sketch��sketch512��Ϊimg1���ɣ����������޸ģ�


	   for (int i=0 ; i<C.size();i++)
	   {
		   if (C[i].x1==0&&C[i].y1==0)
		   cvRectangle(img1,cvPoint(C[i].x1,C[i].y1),cvPoint(C[i].x2,C[i].y2),cvScalar(0x00,0x00,0x00));
		   else   if (C[i].x1==0&&C[i].y1!=0)
		   cvRectangle(img1,cvPoint(C[i].x1,C[i].y1-1),cvPoint(C[i].x2,C[i].y2),cvScalar(0x00,0x00,0x00));
		   else   if (C[i].x1!=0&&C[i].y1==0)
		   cvRectangle(img1,cvPoint(C[i].x1-1,C[i].y1),cvPoint(C[i].x2,C[i].y2),cvScalar(0x00,0x00,0x00));
		   else   if (C[i].x1!=0&&C[i].y1!=0)
		   cvRectangle(img1,cvPoint(C[i].x1-1,C[i].y1-1),cvPoint(C[i].x2,C[i].y2),cvScalar(0x00,0x00,0x00));

	   }




	   cvShowImage("�ָ�ʾ��ͼ",img1);//����ת����ĻҶ�ͼ�� 
     
	//��ʾ��ͼ����
	   }
	   else //�Ŵ�ͼ��
	   {
	     //��������ͼ��
	   IplImage* sketch512 = cvCreateImage(cvSize(512,512), IPL_DEPTH_8U,1); 
	   int xr = 511/(N-1);
	   int yr = 511/(M-1);
	   for(int y = 0;y<512;y++)             
		{
			uchar* ptrsketch = (uchar*) (sketch512->imageData+y*sketch512->widthStep);

				for (int x = 0;x<512;x++)
				{
				 ptrsketch[x]=255;
				}
		 }
	  //����ͼ���ʼ�����
	   for (int i=0 ; i<C.size();i++)
	   {
		   if (C[i].x1==0&&C[i].y1==0)
		   cvRectangle(img1,cvPoint(C[i].x1*xr,C[i].y1*yr),cvPoint(C[i].x2*xr,C[i].y2*yr),cvScalar(0x00,0x00,0x00));
		   else   if (C[i].x1==0&&C[i].y1!=0)
		   cvRectangle(img1,cvPoint(C[i].x1*xr,(C[i].y1-1)*yr),cvPoint(C[i].x2*xr,C[i].y2*yr),cvScalar(0x00,0x00,0x00));
		   else   if (C[i].x1!=0&&C[i].y1==0)
		   cvRectangle(img1,cvPoint((C[i].x1-1)*xr,C[i].y1*yr),cvPoint(C[i].x2*xr,C[i].y2*yr),cvScalar(0x00,0x00,0x00));
		   else   if (C[i].x1!=0&&C[i].y1!=0)
		   cvRectangle(img1,cvPoint((C[i].x1-1)*xr,(C[i].y1-1)*yr),cvPoint(C[i].x2*xr,C[i].y2*yr),cvScalar(0x00,0x00,0x00));

	   }
	   cvShowImage("�ָ�ʾ��ͼ",img1);//����ת����ĻҶ�ͼ�� 
	//��ʾ��ͼ����
	   }

       cvSaveImage("��Ԫ���ָ�ʾ��ͼ.bmp", img1, 0);//��ͼ��д���ļ� , added by zyp
       cvSaveImage("��Ԫ������ָ���ͼ��.bmp", imggest, 0);//��ͼ��д���ļ� , added by zyp �ؽ����ͼ��

       cvSaveImage("��Ԫ������ϲ�ʾ��ͼ1.bmp", seg, 0);//��ͼ��д���ļ� , added by zyp  ����ϲ����þ�ֵ�����ͼ��
       cvSaveImage("��Ԫ������ϲ�ʾ��ͼ2.bmp", seg_line, 0);//��ͼ��д���ļ� , added by zyp


	 //// added by zyp begin
 	//cout << "Display the data matrix of the ��Ԫ���ָ�ʾ��ͼ.bmp:" << endl;
	 //for(int y = 0;y<img1->height;y++)
  //  {
		//	uchar* ptr = (uchar*) (img1->imageData+y*img1->widthStep);

		//	for (int x = 0;x<img1->width;x++)
		//	{
		//		printf ("%5d",*ptr++);
		//	}
  //          printf("\n\n");
  //  }
	 //// added by zyp end


	 //// added by zyp begin
 	//cout << "Display the data matrix of the ��Ԫ������ָ���ͼ��.bmp:" << endl;
	 //for(int y = 0;y<imggest->height;y++)
  //  {
		//	uchar* ptr = (uchar*) (imggest->imageData+y*imggest->widthStep);

		//	for (int x = 0;x<imggest->width;x++)
		//	{
		//		printf ("%5d",*ptr++);
		//	}
  //          printf("\n\n");
  //  }
	 //// added by zyp end


	 //// added by zyp begin
 	//cout << "Display the data matrix of the ��Ԫ������ϲ�ʾ��ͼ1.bmp:" << endl;
	 //for(int y = 0;y<seg->height;y++)
  //  {
		//	uchar* ptr = (uchar*) (seg->imageData+y*seg->widthStep);

		//	for (int x = 0;x<seg->width;x++)
		//	{
		//		printf ("%5d",*ptr++);
		//	}
  //          printf("\n\n");
  //  }
	 //// added by zyp end


	 //// added by zyp begin
 	//cout << "Display the data matrix of the ��Ԫ������ϲ�ʾ��ͼ2.bmp:" << endl;
	 //for(int y = 0;y<seg_line->height;y++)
  //  {
		//	uchar* ptr = (uchar*) (seg_line->imageData+y*seg_line->widthStep);

		//	for (int x = 0;x<seg_line->width;x++)
		//	{
		//		printf ("%5d",*ptr++);
		//	}
  //          printf("\n\n");
  //  }
	 //// added by zyp end


	 for (int i=0 ; i<C.size();i++)
	   {
		   if (C[i].x2-C[i].x1==1)
		   nmb++;

	   }

	 //cout << "2*2��������"<< nmb << endl;
	 cout << "����������  "<< reg_num << endl<< endl;

	 fout << "����������  "<< reg_num << endl<< endl;
     fout.close();


       cvWaitKey(0); //�ȴ�����


	   cvReleaseImage(&img1);
	   cvReleaseImage(&imggest);
	   cvDestroyAllWindows( );//�ر�

      char zyp;
	  cin >> zyp; 
  

      return 0;

    }

	else

     return -1;

}


int ackerman(int n , int m)
{
	if ( n >= 2 && m == 0)
		return n+2;
	else if (n == 1 && m == 0)
		return 2;
	else if (n == 0)
		return 1;
	else return ackerman(ackerman(n-1,m) , m-1);

}


	
     

	







	
 

