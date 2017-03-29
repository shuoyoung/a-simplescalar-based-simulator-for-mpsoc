#include "sim_router.h"
#include "sim_foundation.h"
#include "mess_queue.h"
#include "mess_event.h"
#include "SRGen.h"
#include "SStd.h"

void sim_router_template::TXY_algorithm(const add_type & des_t,
		const add_type & sor_t, long s_ph, long s_vc)
{
	printf ("don't come here\n");
	assert(0);
}
//***************************************************************************//
void sim_router_template::XYZ_algorithm(const add_type & des_t,
		const add_type & sor_t, long s_ph, long s_vc)
{
	long add_z, add_y, add_x;
	long des_z, des_y, des_x;
	int local_id = address_[0]*ary_size_+address_[1];
	add_type des_network_t ;
	add_type des_t_1 = des_t;
	//FindNetworkID(des_t_1, des_network_t);
	long des_network_ID=des_t[0]*ary_size_+des_t[1];

	int des_network_z = des_network_ID / ( DIM_X*DIM_Y)  ;
	int des_network_y = (des_network_ID % (DIM_X*DIM_Y) )/ DIM_X;
	int des_network_x = (des_network_ID % (DIM_X*DIM_Y) )% DIM_X;
	
	int local_network_z = local_id / ( DIM_X*DIM_Y)  ;
	int local_network_y = (local_id % (DIM_X*DIM_Y) )/ DIM_X;
	int local_network_x = (local_id % (DIM_X*DIM_Y) )% DIM_X;


	long xoffset = des_network_x - local_network_x;
	long yoffset = des_network_y - local_network_y;
	long zoffset = des_network_z - local_network_z;
	if(zoffset < 0) {
			input_module_.add_routing(s_ph, s_vc, VC_type(5,s_vc));
	}else if(zoffset > 0) {
			input_module_.add_routing(s_ph, s_vc, VC_type(6,s_vc));
	}
	else {
	  if(yoffset < 0) {
			input_module_.add_routing(s_ph, s_vc, VC_type(3,s_vc));
	  }else if(yoffset > 0) {
			input_module_.add_routing(s_ph, s_vc, VC_type(4,s_vc));
	  }else {
	    if(xoffset < 0) {
				input_module_.add_routing(s_ph, s_vc, VC_type(1,s_vc));
	    }else if (xoffset > 0) {
				input_module_.add_routing(s_ph, s_vc, VC_type(2,s_vc));
	    }
	  } 
	}
}
//***************************************************************************//
void sim_router_template::CMESH_XYZ_algorithm(const add_type & des_t,
		const add_type & sor_t, long s_ph, long s_vc)
{
	long add_z, add_y, add_x;
	long des_z, des_y, des_x;
	int local_id = address_[0]*ary_size_+address_[1];
	int DIM = DIM_X*DIM_Y*(DIM_Z+1);
	add_type des_network_t ;
	add_type des_t_1 = des_t;
	//FindNetworkID(des_t_1, des_network_t);
	long des_network_ID = des_t[0]*ary_size_+des_t[1];
	
	int des_network_z = des_network_ID / ( DIM_X*DIM_Y) ; //des_network_ID转换为3D坐标，以便计算直接相连中间节点的ID
	int des_network_y = (des_network_ID % (DIM_X*DIM_Y) )/ (DIM_X);
	int des_network_x = (des_network_ID % (DIM_X*DIM_Y) )% (DIM_X);
	des_network_ID = DIM + (C_DIM_X*C_DIM_Y)*des_network_z + C_DIM_X*(des_network_y/2) + des_network_x/2;  //一个cluster中，由des_network_ID_id计算直接相连中间节点的ID
		
	if(local_id < DIM){ //一个cluster中,源节点的1号端口
			 input_module_.add_routing(s_ph, s_vc, VC_type(1,s_vc));
	}else if(local_id == des_network_ID){ //当前ID与目地节点在同一个cluster中，选择7、8、9、10端口中的一个
						   input_module_.add_routing(s_ph, s_vc, VC_type((7+2*(des_network_y%2)+des_network_x%2),s_vc));//一个cluster中，由des_network_ID计算输出的端口号
	}else{
		//已计算目地节点直接相连的中间节点的ID，把此中间节点ID转换为3D坐标，这样就方便利用维序路由算法
		des_network_z = (des_network_ID - DIM) / ( C_DIM_X*C_DIM_Y );
		des_network_y = ( (des_network_ID - DIM) % (C_DIM_X*C_DIM_Y ))/ C_DIM_X;
		des_network_x = ( (des_network_ID - DIM) %(C_DIM_X*C_DIM_Y) )% C_DIM_X;

		//将当前节点ID转换为3D坐标，这样就方便利用维序路由算法
		int local_network_z = (local_id - DIM) / ( C_DIM_X*C_DIM_Y );
		int local_network_y = ( (local_id - DIM) % (C_DIM_X*C_DIM_Y ))/ C_DIM_X;
		int local_network_x = ( (local_id - DIM) %(C_DIM_X*C_DIM_Y) )% C_DIM_X;

		long xoffset = des_network_x - local_network_x;
		long yoffset = des_network_y - local_network_y;
		long zoffset = des_network_z - local_network_z;

		if(zoffset < 0) {
				 input_module_.add_routing(s_ph, s_vc, VC_type(5,s_vc));
		}else if(zoffset > 0) {
					input_module_.add_routing(s_ph, s_vc, VC_type(6,s_vc));
		}else {
	  		if(yoffset < 0) {
					 input_module_.add_routing(s_ph, s_vc, VC_type(3,s_vc));
	  		}else if(yoffset > 0) {
						input_module_.add_routing(s_ph, s_vc, VC_type(4,s_vc));
	  		}else {
	    			if(xoffset < 0) {
						  input_module_.add_routing(s_ph, s_vc, VC_type(1,s_vc));
	    			}else if (xoffset > 0) {
				 			 input_module_.add_routing(s_ph, s_vc, VC_type(2,s_vc));
	    						}
	  			} 
			}
		}
}
//***************************************************************************//
void sim_router_template::AFN_E_algorithm(const add_type & des_t,
		const add_type & sor_t, long s_ph, long s_vc)
{
	long add_z, add_y, add_x;
	long des_z, des_y, des_x;
	int local_id = address_[0]*ary_size_+address_[1];
	int DIM = DIM_X*DIM_Y*(DIM_Z+1);
	add_type des_network_t ;
	add_type des_t_1 = des_t;
	//FindNetworkID(des_t_1, des_network_t);
	long des_network_ID=des_t[0]*ary_size_+des_t[1];

	int des_network_z = des_network_ID / ( DIM_X*DIM_Y) ; //des_network_ID转换为3D坐标，以便选择路由的路径
	int des_network_y = (des_network_ID % (DIM_X*DIM_Y) )/ (DIM_X);
	int des_network_x = (des_network_ID % (DIM_X*DIM_Y) )% (DIM_X);
	des_network_ID = DIM + (C_DIM_X*C_DIM_Y)*des_network_z + C_DIM_X*(des_network_y/2) + des_network_x/2;  //一个cluster中，由des_network_ID_id计算直接相连中间节点的ID

	if(local_id < DIM){ //cluster中,源节点的1号端口
			 input_module_.add_routing(s_ph, s_vc, VC_type(1,s_vc));
	}else if(local_id == des_network_ID){ //当前ID与目地节点在同一个cluster中，选择2、3、4、5端口中的一个
						   input_module_.add_routing(s_ph, s_vc, VC_type((2+2*(des_network_y%2)+des_network_x%2),s_vc));//一个cluster中，由des_network_ID计算输出的端口号
	}else if(local_id<(DIM + DIM/4) ){ //与目地节点不在同一cluster中，传至叶子节点，1号端口
						input_module_.add_routing(s_ph, s_vc, VC_type(1,s_vc));
	}else if(local_id<(DIM + DIM/4+4) ){ //叶子节点：与目地节点在同一枝时，直接向下传输；不在同一枝时需传至根节点

		//已计算目地节点直接相连的中间节点的ID，把此中间节点ID转换为3D坐标，这样就方便利用维序路由算法
		des_network_z = (des_network_ID - DIM) / ( C_DIM_X*C_DIM_Y );
		des_network_y = ( (des_network_ID - DIM) % (C_DIM_X*C_DIM_Y ))/ C_DIM_X;
		des_network_x = ( (des_network_ID - DIM) %(C_DIM_X*C_DIM_Y) )% C_DIM_X;
		
		//将四个叶子节点（ID=100-103）转换为3D坐标
		int local_network_z = (local_id - DIM) / ( C_DIM_X*C_DIM_Y );
		int local_network_y = ( (local_id - DIM) % (C_DIM_X*C_DIM_Y ))/ C_DIM_X;
		int local_network_x = ( (local_id - DIM) %(C_DIM_X*C_DIM_Y) )% C_DIM_X;

		long xoffset = des_network_x - local_network_x;
		long yoffset = des_network_y - local_network_y;
		long zoffset = des_network_z - local_network_z;

		if(xoffset!=0||yoffset!=0) //不是同一枝上，传输到根节点
		{
			input_module_.add_routing(s_ph, s_vc, VC_type(6,s_vc));
		}else 
		{
			input_module_.add_routing(s_ph, s_vc, VC_type((des_network_z+1),s_vc));
		}
	}else 
	{
		input_module_.add_routing(s_ph, s_vc, VC_type((des_network_ID%4+1),s_vc));	
	}
}
//***************************************************************************//

			
//***************************************************************************//
//only two-dimension is supported
void sim_router_template::routing_decision()
{
	time_type event_time = mess_queue::m_pointer().current_time();
	//for injection physical port 0
	for(long j = 0; j < vc_number_; j++) {
		//for the HEADER_ flit
		flit_template flit_t;
		if(input_module_.state(0,j) == ROUTING_) {
			flit_t = input_module_.get_flit(0,j);
			add_type des_t = flit_t.des_addr();
			add_type sor_t = flit_t.sor_addr();
			add_type des_network_addr;
			//FindNetworkID(des_t, des_network_addr);// by wxh
			if(address_ == des_t) {
				if(flit_t.pathsetup() == 1){
					mess_queue::wm_pointer().add_message(mess_event(event_time + 1, OPT_, sor_t, des_t, flit_t));
				}else{
					if(accept_flit(event_time, flit_t) == 0)
						continue;				
				}
				
				input_module_.remove_flit(0, j);
				input_module_.state_update(0, j, HOME_);
				counter_inc(0, j);
#if 1
				if(flit_t.flit_size() == 1) {
					if(input_module_.input(0, j).size() > 0) {
						input_module_.state_update(0, j, ROUTING_);
					}else {
						input_module_.state_update(0, j, INIT_);
					}
				}
#endif
			}else {
				input_module_.clear_routing(0,j);
				input_module_.clear_crouting(0,j);
				(this->*curr_algorithm)(des_t, sor_t, 0, j);
				input_module_.state_update(0, j, VC_AB_);
			}
		//the BODY_ or TAIL_ flits
		}else if(input_module_.state(0,j) == HOME_)  {
			if(input_module_.input(0, j).size() > 0) {
				flit_t = input_module_.get_flit(0, j);
				Sassert(flit_t.type() != HEADER_);
				if(accept_flit(event_time, flit_t) == 0)
					continue;
				input_module_.remove_flit(0, j);
				counter_inc(0, j);
				if(flit_t.type() == TAIL_) {
					if(input_module_.input(0, j).size() > 0) {
						input_module_.state_update(0, j, ROUTING_);
					}else {
						input_module_.state_update(0, j, INIT_);
					}
				}
			}
		}
	}

	//for other physical ports
	for(long i = 1; i < physic_ports_; i++) {
		for(long j = 0; j < vc_number_; j++) {
			//send back CREDIT message
			flit_template flit_t;


			//for HEADER_ flit
			if(input_module_.state(i, j) == ROUTING_) {
				flit_t = input_module_.get_flit(i, j);
				Sassert(flit_t.type() == HEADER_);
				add_type des_t = flit_t.des_addr();
				add_type sor_t = flit_t.sor_addr();
				add_type des_network_addr;
				//FindNetworkID(des_t, des_network_addr);// by wxh
				if(address_ == des_t) {
					if(flit_t.pathsetup() == 1)					
						mess_queue::wm_pointer().add_message(mess_event(event_time + 1, OPT_, sor_t, des_t, flit_t));
					else {
						if(accept_flit(event_time, flit_t) == 0)
							continue;
					}
					input_module_.remove_flit(i, j);
					input_module_.state_update(i, j, HOME_);
#if 1
					add_type cre_add_t = address_;
					long cre_pc_t = i;
					ConnectionDownStream( i,  address_, cre_add_t,  cre_pc_t, ary_size_);
					mess_queue::wm_pointer().add_message(
						mess_event(event_time + CREDIT_DELAY_, 
						CREDIT_, address_, cre_add_t, cre_pc_t, j));

					if(flit_t.flit_size() == 1) {
						if(input_module_.input(i, j).size() > 0) {
							input_module_.state_update(i, j, ROUTING_);
						}else {
							input_module_.state_update(i, j, INIT_);
						}
					}
#endif
				}else {
					input_module_.clear_routing(i, j);
					input_module_.clear_crouting(i, j);
					(this->*curr_algorithm)(des_t, sor_t, i, j);
					input_module_.state_update(i, j, VC_AB_);
				}
			//for BODY_ or TAIL_ flits
			}else if(input_module_.state(i, j) == HOME_) {
				if(input_module_.input(i, j).size() > 0) {
					flit_t = input_module_.get_flit(i, j);
					Sassert(flit_t.type() != HEADER_);
					if(accept_flit(event_time, flit_t) == 0)
						continue;
					input_module_.remove_flit(i, j);
#if 1
					add_type cre_add_t = address_;
					long cre_pc_t = i;
					ConnectionDownStream( i,  address_, cre_add_t,  cre_pc_t, ary_size_);

					mess_queue::wm_pointer().add_message(
						mess_event(event_time + CREDIT_DELAY_, 
						CREDIT_, address_, cre_add_t, cre_pc_t, j));
#endif
					if(flit_t.type() == TAIL_) {
						if(input_module_.input(i, j).size() > 0) {
							input_module_.state_update(i, j, ROUTING_);
						}else {
							input_module_.state_update(i, j, INIT_);
						}
					}
				}
			}
		}
	}
}

//***************************************************************************//
