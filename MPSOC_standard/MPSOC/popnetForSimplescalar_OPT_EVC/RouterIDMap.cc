#include "RouterIDMap.h"
#include "configuration.h"
vector<MappingItem> MappingTable;
void FindNetworkID(add_type &Proc, add_type & Network)
{
	int i ;
	for ( i = 0 ; i <MappingTable.size(); i++ )
	{
		if (MappingTable[i].Proc == Proc)
		{
			break;
		}
	}
	if (i ==MappingTable.size())
	{
		printf("cannot come here");
		assert(0);
	}
	Network =  MappingTable[i].Network;
}
void FindProcID(add_type &Proc, add_type & Network)
{
	int i ;
	for ( i = 0 ; i <MappingTable.size(); i++ )
	{
		if (MappingTable[i].Network == Network)
		{
			break;
		}
	}
	if (i ==MappingTable.size())
	{
		printf("cannot come here");
		assert(0);
	}
	Proc = MappingTable[i].Proc;
}
void Generate3DMeshProcNetworkID()
{
	MappingItem m;
	int network_x, network_y;
	int new_x, new_y, new_z ;
	int NetworkID;
	int ary_size = mesh_size+3;
	int MC_index = 0;
	// print it out
	ofstream db;
	db.open("db.log");
	for	(int i = 0; i < mesh_size+2; i ++)
	{
		for (int j= 0;j <mesh_size;j++)
		{
			if (i > 0 && i < mesh_size +MEM_LOC_SHIFT)
			{
				// normal nodes, to 3D mesh
				int ProcID = (i - MEM_LOC_SHIFT)*mesh_size+j;

				new_z = ProcID / ( DIM_X*DIM_Y) +1 ; // let the bottom layer be the memory 
				new_y= (ProcID % (DIM_X*DIM_Y) )/ DIM_X;
				new_x = (ProcID % (DIM_X*DIM_Y) )% DIM_X;
				
				NetworkID = new_z* DIM_X*DIM_Y + new_y*DIM_X+new_x;
				network_y = NetworkID / ary_size;
				network_x = NetworkID % ary_size;	
	   			db<<"( " <<i<<", "<<j<<" ) "
				<<ProcID<<" Network ( "<<new_x<<", "<<new_y<<", "<<new_z<<") "<<NetworkID
				<<" ( " <<network_y<<", "<<network_x<<" )\n";		
			}		
			else 
			{
				// This is a mem controller, we map them to the bottom line
					new_z = 0; 
					//if (i == 0)
					//{
					//	new_y = 0;
					//}
					//else 
					//{
					//	new_y = DIM_Y-1;
					//}
					//int delta = mesh_size/DIM_X ;
					//new_x = j/ delta;
					NetworkID = MC_index++;
					new_y = (NetworkID %(DIM_X*DIM_Y)) /DIM_X;
					new_x = (NetworkID %(DIM_X*DIM_Y)) %DIM_X;
					//new_z* DIM_X*DIM_Y + new_y*DIM_X+new_x;
					network_y = NetworkID / ary_size;
					network_x = NetworkID % ary_size;
	   				db<<"( " <<i<<", "<<j<<" ) "
					<<-1<<" Network ( "<<new_x<<", "<<new_y<<", "<<new_z<<") "<<NetworkID
					<<" ( " <<network_y<<", "<<network_x<<" )\n";				
			}
			m.Proc.resize(2);
			m.Network.resize(2);
			m.Proc[0] = i;
			m.Proc[1] = j;
			m.Network[0] = network_y;
			m.Network[1] = network_x;
			MappingTable.push_back(m);
		}
	}
	  
	db.close();
}


int ConnectionDownStream(int i, add_type & address_, add_type & next_add_t, long & next_pc_t, int ary_size_) // Credit
{
	long next_add_z, next_add_y, next_add_x;
	long local_id=address_[0]*ary_size_+address_[1];
	int DIM = DIM_X*DIM_Y*(DIM_Z+1);
	int upstream_ID;	

	switch (Topo)
	{
		case ThreeD_MESH:
		next_add_z = local_id / ( DIM_X*DIM_Y)  ;
		next_add_y = (local_id % (DIM_X*DIM_Y) )/ DIM_X;
		next_add_x = (local_id % (DIM_X*DIM_Y) )% DIM_X;
		if((i%2)==0)
		{
				next_pc_t=i-1;
				switch(i) 
				{
					case 2 : next_add_x++; break;
					case 4 : next_add_y++; break;
					case 6 : next_add_z++; break;
					default: break;
				}
			}
			else 
			{
				next_pc_t=i+1;
				switch(i) 
				{
					case 1 : next_add_x--; break;
					case 3 : next_add_y--; break;
					case 5 : next_add_z--; break;
					default: break;
				}
			}

		upstream_ID = next_add_z* DIM_X*DIM_Y + next_add_y*DIM_X+next_add_x;
		break;
//***************************************************************************//
		case ThreeD_CMESH:
		if(local_id<DIM)	
		{
			next_add_z = local_id / ( DIM_X*DIM_Y); //将local_id转换成3D坐标，以便计算每一个cluster内，其他节点与中间节点ID和端口的连接关系
			next_add_y = (local_id % (DIM_X*DIM_Y) )/ (DIM_X);
			next_add_x = (local_id % (DIM_X*DIM_Y) )% (DIM_X);

			upstream_ID=DIM+(C_DIM_X* C_DIM_Y)*next_add_z+C_DIM_X*(next_add_y/2)+next_add_x/2;  //一个cluster中，由local_id计算直接相连中间节点的ID
			next_pc_t=7+2*(next_add_y%2)+next_add_x%2;     //一个cluster中，4个节点分别与中间节点的7、8、9、10号端口相连
		}
		else
		{	
			 //把20个cluster中间节点的ID转换为3D坐标
			next_add_z = (local_id-DIM) / ( C_DIM_X*C_DIM_Y)  ;
			next_add_y = ((local_id-DIM) % ( C_DIM_X*C_DIM_Y) )/ C_DIM_X;
			next_add_x = ((local_id-DIM) % ( C_DIM_X*C_DIM_Y) )% C_DIM_X;

			if((i%2)==0&&i<7) 
			{
				next_pc_t=i-1;
				switch(i) 
				{
					case 2 : next_add_x++; break;
					case 4 : next_add_y++; break;
					case 6 : next_add_z++; break;
					default: break;
				}
				upstream_ID = next_add_z* ( C_DIM_X*C_DIM_Y)  + next_add_y*C_DIM_X+next_add_x+DIM; //根据改变后的3D坐标计算出改变后的ID
			}
			else if(i<7)
			{
				next_pc_t=i+1;
				switch(i) 
				{
					case 1 : next_add_x--; break;
					case 3 : next_add_y--; break;
					case 5 : next_add_z--; break;
					default: break;
				}
				upstream_ID = next_add_z* ( C_DIM_X*C_DIM_Y) + next_add_y*C_DIM_X+next_add_x+DIM;  //根据改变后的3D坐标计算出改变后的ID
			}
			else 
			{
				next_pc_t=1;//一个cluster内，与中间节点相连的其他节点的端口号为1
				upstream_ID = (DIM_X*DIM_Y)*next_add_z + DIM_X*2*next_add_y + 2*next_add_x+ DIM_X*(i/9) + (i-7)%2; //一个cluster内，由中间节点ID和i计算直接相连的节点的ID			
			}	
		}
		break;
//***************************************************************************//
		case AFN_E:
		if(local_id < DIM)	//原始节点0-79
		{
			//将80个原始节点ID转换成3D坐标，以便计算每一个cluster内，其他节点与中间节点ID和端口的连接关系
			next_add_z = local_id / ( DIM_X*DIM_Y); 
			next_add_y = (local_id % (DIM_X*DIM_Y) ) / (DIM_X);
			next_add_x = (local_id % (DIM_X*DIM_Y) ) % (DIM_X);

			//upstream_ID = DIM + 4*next_add_z + 2*(next_add_y/2) + next_add_x/2;  
			upstream_ID=DIM+(C_DIM_X* C_DIM_Y)*next_add_z+C_DIM_X*(next_add_y/2)+next_add_x/2;  //一个cluster中，由原始节点id计算其直接相连中间节点的ID
			next_pc_t = 2 + 2*(next_add_y%2) + next_add_x%2;     //一个cluster中，4个节点分别与中间节点的2、3、4、5号端口相连
		}
		else if(local_id < (DIM+DIM/4) ) //新增的20个中间节点：80-99	
		{	
			//把20个cluster中间节点的ID转换为3D坐标
			next_add_z = (local_id-DIM) / ( C_DIM_X*C_DIM_Y)  ;
			next_add_y = ((local_id-DIM) % ( C_DIM_X*C_DIM_Y) )/ C_DIM_X;
			next_add_x = ((local_id-DIM) % ( C_DIM_X*C_DIM_Y) )% C_DIM_X;

			if(i==1) //cluster的1号端口连接到叶子节点
 			{
				next_pc_t = next_add_z+1; //每个叶子连接5个cluster,端口号为1、2、3、4、5
				next_add_z = DIM_Z+1; //用于得到叶子节点的3D坐标
				upstream_ID = next_add_z* ( C_DIM_X*C_DIM_Y)  + next_add_y*C_DIM_X+next_add_x+DIM; //根据改变后的3D坐标计算出叶子节点的ID
			}else
			{
				next_pc_t = 1; //一个cluster内，与中间节点相连的其他节点的端口号为1
				upstream_ID = (DIM_X*DIM_Y)*next_add_z + DIM_X*2*next_add_y + 2*next_add_x+ DIM_X*(i/4) + (i-2)%2; //一个cluster内，由中间节点ID和i计算直接相连的节点的ID
			}	
		}
		else if(local_id<(DIM + DIM/4 + 4) ) //tree的四个叶子节点：100-103; 1-5号端口连接cluster,6号端口接根节点
		{
			if(i==6)
			{
				next_pc_t = local_id - (DIM + DIM/4-1); //根节点ID=104的1、2、3、4端口连接四个叶子（ID分别为100-103）
				upstream_ID = DIM + DIM/4 + 4;
			}else if(i<6)
			{
				next_pc_t = 1; //cluster的1号端口连接到叶子节点
				next_add_z = i - 1;
				upstream_ID = DIM + next_add_z* ( C_DIM_X*C_DIM_Y)  + local_id%4; //Z向偏移量+xy向总偏移量
			}
		}
		else //根节点ID=104
		{
			next_pc_t = 6; //叶子节点的6号端口接根节点
			upstream_ID = i + (DIM + DIM/4-1); //根节点连接四个叶子（ID分别为100-103）的端口分别为1、2、3、4	
		}
		break;
	}

	next_add_t[0]=upstream_ID/ary_size_;
	next_add_t[1]=upstream_ID%ary_size_;
}
