#include "stdafx.h"
#include "FUNCTIONS.h"

using namespace std;
double BPP ( vector<colorListStandard> &P ,int M , int N , vector<char> &Q )  //º∆À„BPP

{

	double b = (Q.size()+32.0*P.size())/(M*N);
	//double b = 8*(Q.size()+32.0*P.size())/(M*N*8);

	//cout << fixed << setprecision(4) << "Length of the linear tree table: " << Q.size() << " bits." << endl;
	//cout << fixed << setprecision(4) << "Length of the color table      : " << 32.0*P.size() << " bits." << endl;
	return b;
}
