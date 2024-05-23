#include "highgui.h"
#include "cxcore.h"
#include "vector"
#include "cv.h"
#include "ctime"
#include "iostream"
#include "math.h"
#include <iomanip>
#include <fstream>
using namespace cv;
using namespace std;
extern int reg_num;
extern int bitnum ;
extern int cur_block ;
extern double thresU ;
extern double thresVar ;
struct colorListStandard//��׼������ɫ��
{
	uchar g1,g2,g3,g4;
};

struct doubleCoordinate{
	int x1;
	int y1;
	int x2;
	int y2;
};//���ϽǼ����½�����


struct treeNode {
	uchar confirm;   //��ʶ0��1
	treeNode* parent;
	treeNode* nwchild;
	treeNode* nechild;
};//�������Ľ��ṹ



bool JudgeSameBlock ( double epsilon , IplImage *&img1 , int x1 , int y1 ,int x2 , int y2 );//�жϾ����Ƿ�Ϊͬ���

void BuildTreeT (   IplImage* &img1 , treeNode* &root , vector<colorListStandard> &P, vector<doubleCoordinate> &C, int &num , double epsilon , int x1 , int y1 ,int x2 , int y2 );//�ָ�ԭͼ.����������T.��ɫ��P


double PSNR ( IplImage *&img1 , IplImage *&imggest );  //����PSNR
double BPP ( vector<colorListStandard> &P  ,int M , int N , vector<char> &Q );  //����BPP

void InitialNode (treeNode* &a);//��ʼ�������
void InsertNode (treeNode* &root);//���뺢�ӽ��
void LevelOrder(vector<char> &Q , treeNode* root );//��α���


inline double Gst(int g2,int g1,int w)
{
    return (g2-g1)/(w-1.0);
}

inline double Gsb(int g4,int g3,int w)
{
    return (g4-g3)/(w-1.0);
}

inline double Gsl(int g3,int g1,int h)
{
    return (g3-g1)/(h-1.0);
}

inline double Gsr(int g4,int g2,int h)
{
    return (g4-g2)/(h-1.0);
}

inline double C1(int w)
{
    return (2*w-1)/(6*(w-1.0));
}

inline double C2(int h)
{
    return (2*h-1)/(6*(h-1.0));
}

inline double D1(int g1,int g2,int g3,int g4,int w,int h)
{
    return (g4-g3-g2+g1)/((w-1.0)*(h-1));
}

inline double Ubi(colorListStandard color , doubleCoordinate coor)
{
  if (coor.x1<coor.x2 && coor.y1<coor.y2)
    return (color.g1+color.g2+color.g3+color.g4)/4.0;
  else if (coor.x1 == coor.x2 && coor.y1 == coor.y2)
    return color.g1;
  else if (coor.y1 == coor.y2)
    return (color.g1+color.g2)/2.0;
  else if (coor.x1 == coor.x2)
    return (color.g1+color.g3)/2.0;
}

inline double Squaresumbi(colorListStandard color , doubleCoordinate coor)
{

  int w = coor.x2-coor.x1+1;
  int h = coor.y2-coor.y1+1;
  double c1 = C1(w);
  double c2 = C2(h);

  if (coor.x1<coor.x2 && coor.y1<coor.y2)
    return w*h*((0.5-c1-c2)*(color.g1*color.g4+color.g2*color.g3)+c1*(color.g2*color.g4+color.g1*color.g3)+c2*(color.g3*color.g4+color.g1*color.g2)+c1*c2*(color.g4-color.g3-color.g2+color.g1)*(color.g4-color.g3-color.g2+color.g1));
  else if (coor.x1 == coor.x2 && coor.y1 == coor.y2)
    return w*h*color.g1*color.g1;
  else if (coor.y1 == coor.y2)
    return w*h*(color.g1*color.g2+c1*(color.g2-color.g1)*(color.g2-color.g1));
  else if (coor.x1 == coor.x2)
    return w*h*(color.g1*color.g3+c2*(color.g3-color.g1)*(color.g3-color.g1));
}


inline double Varbi(colorListStandard color , doubleCoordinate coor)
{

  int w = coor.x2-coor.x1+1;
  int h = coor.y2-coor.y1+1;
  double c1 = C1(w);
  double c2 = C2(h);

  if (coor.x1<coor.x2 && coor.y1<coor.y2)
  {
    double ubi = Ubi(color,coor);
    return ((0.5-c1-c2)*(color.g1*color.g4+color.g2*color.g3)+c1*(color.g2*color.g4+color.g1*color.g3)+c2*(color.g3*color.g4+color.g1*color.g2)+c1*c2*(color.g4-color.g3-color.g2+color.g1)*(color.g4-color.g3-color.g2+color.g1)-ubi*ubi);
  }
  else if (coor.x1 == coor.x2 && coor.y1 == coor.y2)
    return 0;
  else if (coor.y1 == coor.y2)
    return (c1-0.25)*(color.g2-color.g1)*(color.g2-color.g1);
  else if (coor.x1 == coor.x2)
    return (c2-0.25)*(color.g3-color.g1)*(color.g3-color.g1);
}

inline double Uc(int na , int nb , double ua , double ub)
{
  return (na*ua+nb*ub)/(na+nb);

}

inline double Varc(int na , int nb , double vara , double varb,double ua,double ub)
{
  return (na*vara+nb*varb)/(na+nb) + (na*nb*(ua-ub)*(ua-ub))/((na+nb)*(na+nb));

}

struct Corner_Vertex
{
	int x;
	int y;
	Corner_Vertex* Next;
};
struct Edge;
struct Region
{
  double Mean;
  double Var;
  int Size;//�߳�
  Region* Father;
  int Count;//������������
  int SegmentCount;//number of edges shared by the waveform
  Edge* EdgeLink;
};
struct Edge
{
	Edge* PreLink;
	Edge* SucLink;
	Region* Reg;
	Corner_Vertex* First;
	Corner_Vertex* Last;
};

struct Segment
{
	Segment* PreLink;
	Segment* SucLink;
	int Length;
    Edge* ActiveELink;
};


void Region_Segm(Segment* UpperLeft , Segment* &UpperRight , Segment* &PreLowerLeft , int Xleft , int Yupper , int Length , int Width, Region** all_region , vector<colorListStandard> &P , vector<doubleCoordinate> &C  , vector<char> Q,int &num);
inline char Get_bit( vector<char> &Q)
{
	return Q[bitnum++];
}

void SPLIT(Segment* UpperLeft  , int Size,int direction);

void Leaf_Operation(Segment* UpperLeft , Segment* &UpperRight , Segment* &PreLowerLeft , int Xleft , int Yupper , int Length , int Width , vector<colorListStandard> &P , vector<doubleCoordinate> &C ,  Region** all_region);
Region* FindParent(Region *p);
void MakeImggest ( IplImage* &imggest ,  vector<colorListStandard> &P , vector<doubleCoordinate> C , Region** all_region );//����gestͼ��

