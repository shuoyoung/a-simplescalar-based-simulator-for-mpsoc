#include <math.h>
#include <iomanip>
#include <sstream>
#include <cstdio>
#include "sim_ps.h"
#include "sim_foundation.h"
#include "mess_queue.h"
#include "mess_event.h"
#include "SRGen.h"
#include "SStd.h"
#include "mainPopnet.h"

#define ROWX	16
#define ROWY	16
#define COLX	16
#define COLY	16
#define TIMEINFOSIZE	16

extern long destInfoPass[4];
extern long srcInfoPass[4];
extern long sizeInfoPass;
extern time_type eventTimePass;
extern long long int msgNoPass;
extern long vc_suggest;
extern long long int addr; 
extern int link_width;

extern map<long, vector<mynode> > mytable;


// ***********************************************************************
// data structure to model the structure and behavior of photonic switch.
// ***********************************************************************

sim_ps_template::sim_ps_template():
	address_(),
	ary_size_(),
	packet_counter_()
{
}

//***************************************************************************//
//e: address  f: ary_size_
sim_ps_template::sim_ps_template(const add_type & e, long f):
	address_(e),
	ary_size_(f),
	packet_counter_(0),
	total_switch_power_(0),
	total_modulator_power_(0),
	total_demodulator_power_(0),
	total_laser_power_(0),
	total_detector_power_(0)
{
}

double sim_ps_template::power_report(FILE *fd, add_type address_)
{
	double total_power = 0;
	double indv_power = 0;
	int id = 10 * address_[0] + address_[1];
	
	indv_power = total_switch_power();
	fprintf(fd,"  %d switch power: %g\n", id, indv_power);
	total_power += indv_power;

	indv_power = total_modulator_power();
	fprintf(fd,"  %d modulator power: %g\n", id, indv_power);
	total_power += indv_power;

    	indv_power = total_demodulator_power();
    	fprintf(fd,"  %d demodulator power: %g\n", id, indv_power);
    	total_power += indv_power;

    	indv_power = total_laser_power();
    	fprintf(fd,"  %d laser power: %g\n", id, indv_power);
    	total_power += indv_power;
    	
    	indv_power = total_detector_power();
	fprintf(fd,"  %d detector power: %g\n", id, indv_power);
    	total_power += indv_power;
	
	fprintf(fd,"%d total photonic switch power: %g\n", id, total_power);
    	return total_power;
}

double sim_ps_template::power_switch_update()
{	
	total_switch_power_ += 1;
}

double sim_ps_template::power_modulator_update(long data_size)
{	
	total_modulator_power_ += data_size/5;
}

double sim_ps_template::power_demodulator_update(long data_size)
{	
	total_demodulator_power_ += data_size/5;
}

double sim_ps_template::power_laser_update(long data_size)
{	
	total_laser_power_ += data_size/5;
}

double sim_ps_template::power_detector_update(long data_size)
{	
	total_detector_power_ += data_size/5;
}

