/*************************************************
author: Bowen Yang
date:2019/04/19
describe: compute DC based on color average of each region.
**************************************************/
#include "NAM.h"

void ComputeDC(const vector<Region> &region, const vector<Vec2i> &adjacent, vector<float> &DC)
{
    for (auto &x : adjacent)
    {
        int row = x[0];
        int col = x[1];
        float D = sqrt(pow(region[row].lab[0] - region[col].lab[0], 2) +
                       pow(region[row].lab[1] - region[col].lab[1], 2) + pow(region[row].lab[2] - region[col].lab[2], 2));
        DC.push_back(D);
    }
}

void ComputeDC(const vector<Region> &region,const list<Vec2i> &adjacent,list<float> &DC)
{
    for (auto &x:adjacent)
    {
        int row = x[0];
        int col = x[1];
        float D = sqrt(pow(region[row].lab[0] - region[col].lab[0], 2) +
                       pow(region[row].lab[1] - region[col].lab[1], 2) + pow(region[row].lab[2] - region[col].lab[2], 2));
        DC.push_back(D);
    }
}
