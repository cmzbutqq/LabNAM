/*************************************************
author: Bowen Yang
date:2019/04/19
describe: compute DAB and DW, and then use them to compute DT.
**************************************************/
#include "NAM.h"

void ComputeDAB(const vector<Region> &region, const list<Vec2i> &adjacent, list<float> &DAB)
{
    for (auto &x:adjacent)
    {
        int row = x[0];
        int col = x[1];
        float D = sqrt(pow(region[row].lab[1] - region[col].lab[1], 2) + pow(region[row].lab[2] - region[col].lab[2], 2));
        DAB.push_back(D);
    }
}

void ComputeDW(const vector<Region> &region, const list<Vec2i> &adjacent, list<float> &DW)
{
    const int TD = region[0].WLD[0].size();

    for (auto &x : adjacent)
    {
        int row = x[0];
        int col = x[1];
        float D = 0;
        for (int j = 0; j < TD; j++)
        {
            D += pow(region[row].WLD[0][j] - region[col].WLD[0][j], 2);
            D += pow(region[row].WLD[1][j] - region[col].WLD[1][j], 2);
            D += pow(region[row].WLD[2][j] - region[col].WLD[2][j], 2);
        }
        D = sqrt(D);
        DW.push_back(D);
    }
}

void ComputeDT(const list<float> &DAB, const list<float> &DW, list<float> &DT)
{
    list<float>::const_iterator itr1 = DAB.begin(), itr2 = DW.begin();
    for (; itr1 != DAB.end(); itr1++, itr2++)
    {
        float DistT = (*itr1) * (*itr2);
        DT.push_back(DistT);
    }
}
