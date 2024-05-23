//used in paper 72
// STC is equal to BSP in conception
//常宜斌 最后一个参数为0时相当于李祖嘉的STC程序 【且块数较少，而当参数为1时块数较多】
//畅彤 最后一个参数为1时相当于李祖嘉的STC程序   【且块数较少，而当参数为0时块数较多】

//  ../gray_images/brain512_1.bmp   ../gray_images/f16XXXgray.bmp    ../gray_images/f16XXXstc.bmp 10 30 225   1       //  used in paper 72


//  ../gray_images/decho512.bmp   ../gray_images/f16XXXgray.bmp    ../gray_images/f16XXXstc.bmp 10 30 225   1       //  used in paper 72


//  ../gray_images/liver512.bmp   ../gray_images/f16XXXgray.bmp    ../gray_images/f16XXXstc.bmp 10 30 225   1      //  used in paper 72



//  ../gray_images/hands512.bmp   ../gray_images/f16XXXgray.bmp    ../gray_images/f16XXXstc.bmp 10 30 225   1       //  used in paper 72





//  ../gray_images/cameraman512.bmp   ../gray_images/f16XXXgray.bmp    ../gray_images/f16XXXstc.bmp 10 30 225   1   // used in paper 67

//  ../gray_images/boatzyp512.bmp       ../gray_images/f16XXXgray.bmp     ../gray_images/f16XXXstc.bmp 10 30 225    1   // used in paper 67

//  ../gray_images/lenazyp512.bmp       ../gray_images/f16XXXgray.bmp      ../gray_images/f16XXXstc.bmp 10 30 225   1   // used in paper 67

//  ../gray_images/flightzyp512.bmp      ../gray_images/f16XXXgray.bmp      ../gray_images/f16XXXstc.bmp 10 30 225   1   // used in paper 67


// STCMethod.cpp : 定义控制台应用程序的入口点。 
#include "stdafx.h"
#include "FUNCTIONS.h"

int reg_num = 0;
int bitnum = 0;
double thresU = 0;
double thresVar = 0;
int cur_block = -1;
int main( int argc, char** argv )//分别输入1.程序地址2.原彩图3.转坏灰度图文件名4.转换RNAMC文件名5.同类快阀值6.均值阀值7.方差阀值8.切法 1 水平 0垂直
{
	int nmb = 0;
	IplImage* img1;
  //cout << "start" << endl;
	if( argc == 8 && (img1 = cvLoadImage( argv[1], 0)) != 0 )   //将源彩色图像img转化成目标灰色图像读入
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




		time_t start,end,time,converge_start, converge_end, converge_time; //计时变量
    	

	   IplImage* imggest = cvCreateImage(cvGetSize(img1), img1->depth, img1->nChannels); //创建同类型图像gest
	   cvSetZero(imggest);

       int num = atoi(argv[7]);
	   int M = img1->height;  //行(after)
	   int N = img1->width;   //列(before)
	   double epsilon = atof(argv[4]);
	
	  
	   vector<doubleCoordinate> C;//建立坐标表
	   vector<colorListStandard>P;//建立颜色表
	   vector<char> Q;//建立线性树表
	   treeNode *root=new treeNode; //建立根结点
	   InitialNode (root);
		  thresU = atof(argv[5]);
		 thresVar = atof(argv[6]);
	    //创建素描图像
	   IplImage* sketch = cvCreateImage(cvGetSize(img1), IPL_DEPTH_8U,1); 
	  /* for(int y = 0;y<M;y++)             
		{
			uchar* ptrsketch = (uchar*) (sketch->imageData+y*sketch->widthStep);

				for (int x = 0;x<N;x++)
				{
				 ptrsketch[x]=255;
				}
		 }*/
	  //素描图像初始化完成

	   start=clock();
	   cout << "building tree" << endl;
	   BuildTreeT (  img1 , root , P , C , num , epsilon , 0 , 0 , M-1 ,N-1);
		cout << "making  Q" << endl;
	   LevelOrder(Q , root );//寻找同类块，构造线性树表，颜色表,坐标表

	   end=clock();
	   time=end-start;
	   cout  << "编码所用时间:" << time << "ms" << endl;

	

	   start=clock();
	  
	   end=clock();

	   time=end-start;

       ofstream fout("Results.txt");
	   cout  << "解码所用时间:  " << time << "  ms" << endl<<endl;	

       cout << "epsilon =  " << epsilon << endl << endl;
       fout << "epsilon =  " << epsilon << endl << endl;

	   cout << "================================================"  << endl<<endl;	

      //ofstream fout("Results.txt",ios::app);
	 

	   cout << "块数:  " << P.size() << endl<<endl;	

       fout << "块数:  " << P.size() << endl<<endl;	

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

      cvShowImage("区域合并示意图1",seg);
      cvShowImage("区域合并示意图2",seg_line);

	  MakeImggest ( imggest , P , C ,all_region);

	   cout << "PSNR of recontructured:  " << PSNR( img1 , imggest ) <<endl<<endl;
       //cout << "PSNR of segmentation:" << PSNR( img1 ,seg ) << endl<<endl;	
	   fout << "PSNR of recontructured:  " << PSNR( img1 , imggest ) <<endl<<endl;

       cvNamedWindow("灰度化图像", CV_WINDOW_AUTOSIZE); 
	   cvShowImage("灰度化图像", img1); //显示原始灰度图像
	   cvNamedWindow("QSC区域分割后的图像",CV_WINDOW_AUTOSIZE);     //区域分割后的图像
	   cvShowImage("QSC区域分割后的图像",imggest);//载入转化后的灰度图像   //区域分割后的图像

	   cvSaveImage(argv[2], img1, 0);//把图像写入文件
	  cvSaveImage(argv[3], imggest, 0);//把图像写入文件
	   //画示意图
	   cvNamedWindow("分割示意图",CV_WINDOW_AUTOSIZE);
	        if (N>=256||M>=256)
	   {
	   //创建素描图像
	   IplImage* sketch = cvCreateImage(cvGetSize(img1), IPL_DEPTH_8U,1); 
	   for(int y = 0;y<M;y++)             
		{
			uchar* ptrsketch = (uchar*) (sketch->imageData+y*sketch->widthStep);

				for (int x = 0;x<N;x++)
				{
				 ptrsketch[x]=255;
				}
		 }
	  //素描图像初始化完成
     
	   // 向原始图像中加矩形时，只需将cvRectangle和cvShowImage("分割示意图",sketch512或sketch);中的sketch或sketch512换为img1即可，共有两处修改！


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




	   cvShowImage("分割示意图",img1);//载入转化后的灰度图像 
     
	//画示意图结束
	   }
	   else //放大图像
	   {
	     //创建素描图像
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
	  //素描图像初始化完成
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
	   cvShowImage("分割示意图",img1);//载入转化后的灰度图像 
	//画示意图结束
	   }

       cvSaveImage("二元树分割示意图.bmp", img1, 0);//把图像写入文件 , added by zyp
       cvSaveImage("二元树区域分割后的图像.bmp", imggest, 0);//把图像写入文件 , added by zyp 重建后的图像

       cvSaveImage("二元树区域合并示意图1.bmp", seg, 0);//把图像写入文件 , added by zyp  区域合并后用均值填充后的图像
       cvSaveImage("二元树区域合并示意图2.bmp", seg_line, 0);//把图像写入文件 , added by zyp


	 //// added by zyp begin
 	//cout << "Display the data matrix of the 二元树分割示意图.bmp:" << endl;
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
 	//cout << "Display the data matrix of the 二元树区域分割后的图像.bmp:" << endl;
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
 	//cout << "Display the data matrix of the 二元树区域合并示意图1.bmp:" << endl;
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
 	//cout << "Display the data matrix of the 二元树区域合并示意图2.bmp:" << endl;
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

	 //cout << "2*2块数量："<< nmb << endl;
	 cout << "区域数量：  "<< reg_num << endl<< endl;

	 fout << "区域数量：  "<< reg_num << endl<< endl;
     fout.close();


       cvWaitKey(0); //等待按键


	   cvReleaseImage(&img1);
	   cvReleaseImage(&imggest);
	   cvDestroyAllWindows( );//关闭

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


	
     

	







	
 

