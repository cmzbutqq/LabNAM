#include "Header.h"
double BPP (map<unsigned int,ColorNode> &color_list ,int xn , int yn , vector<char> &Q )
{ 
	int a1=0,a2=0,a3=0;
	for (int i=0;i<color_list.size();i++){ 
		if(color_list[i].g1!=-1&&color_list[i].g4!=-1 ) a1++;
		else if(color_list[i].g2==-1&&color_list[i].g3==-1) a3++;
		else  a2++;
	}
	double BPPValue = (Q.size()+16*a1+8*a2+4.0*a3)/(xn*yn);
	return BPPValue;
}