#ifndef VIP_BYPASS_H
#define VIP_BYPASS_H
#include <vector>
using namespace std;
#include "configuration.h"
#include "RouterIDMap.h"
extern "C" {
#include "../host.h"
};
struct DominantFlowTableItem
{
	int src_x;
	int src_y;
	int src_z;
	int dst_x;
	int dst_y;
	int dst_z;
	int isCluster;
	int start_time;
	int end_time;
} ;
extern vector< DominantFlowTableItem  >  DominantFlowTable;
extern void ReadDominantFlows();
extern int CheckDFFlowTable(int src_x,int src_y,int src_z, int dst_x,int dst_y, int dst_z, counter_t sim_cycle, int isCluster);

#endif