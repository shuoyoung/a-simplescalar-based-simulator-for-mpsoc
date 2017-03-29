#include "VIP_Bypass.h"
// This file contains the VIP setup algorithm
// We assume that the VIP input file has the format
// s d start_time end-time
// or C s d start_time end_time
char DFFileName[50] = "DF.txt";

vector< DominantFlowTableItem  >  DominantFlowTable;
void ReadDominantFlows()
{
	if  (Topo == ThreeD_CMESH || Topo == AFN_O ||  Topo == AFN_E )
	{
		strcpy(DFFileName,"CDF.txt");
	}         

	ifstream DFP;
	DFP.open (DFFileName);
	string spare;
	DominantFlowTableItem item;
	while (!DFP.eof())
	{
		DFP >> spare;
		if (DFP.eof())
		{
			break;
		}
		if (spare == "C")
		{
			DFP>>item.src_x;// we know that this is for cluster
			item.isCluster = 1;
		}
		else 
		{
			item.src_x = atoi(spare.c_str());
			item.isCluster = 0;
		}
		DFP>>item.src_y>>item.src_z>>item.dst_x>>item.dst_y>>item.dst_z>>item.start_time>>item.end_time;
		DominantFlowTable.push_back(item);
	}

}

int CheckDFFlowTable(int src_x,int src_y,int src_z, int dst_x,int dst_y, int dst_z, counter_t sim_cycle, int isCluster)
{
	for (int i = 0; i < DominantFlowTable.size() ; i++)
	{
		DominantFlowTableItem item = DominantFlowTable[i];
		if (item .src_x == src_x && item .src_y == src_y &&  item .src_z == src_z && item .dst_x == dst_x && item .dst_y == dst_y &&  item .dst_z == dst_z
		&& sim_cycle >= item.start_time &&sim_cycle<item.end_time )
			return 1;
	}
	return 0;
}
