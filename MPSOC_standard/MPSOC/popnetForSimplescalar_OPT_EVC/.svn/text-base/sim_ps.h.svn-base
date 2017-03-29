#ifndef SIM_PS_
#define SIM_PS_

#include "flit.h"
#include "index.h"
#include "mytable.h"
#include "SStd.h"
#include "SRGen.h"
#include "configuration.h"
#include <vector>
#include <utility>
#include <map>
#include <functional>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
#include <set>

#include <algorithm>

// *************************************************************************
// data structure to model the structure and behavior of photonic switches
// *************************************************************************

class sim_ps_template {
	friend ostream& operator<<(ostream& os, const sim_ps_template & sr);

	private:
		add_type address_;
		long ary_size_;
		long packet_counter_;

		long total_switch_power_;
		long total_modulator_power_;
		long total_demodulator_power_;
		long total_laser_power_;
		long total_detector_power_;


	public:	
		vector<long> & address() {return address_;}
		const vector<long> & address() const {return address_;}

		long total_switch_power() const {return total_switch_power_;}
		long total_switch_power() {return total_switch_power_;}

		long total_modulator_power() const {return total_modulator_power_;}
		long total_modulator_power() {return total_modulator_power_;}

		long total_demodulator_power() const {return total_demodulator_power_;}
		long total_demodulator_power() {return total_demodulator_power_;}

		long total_laser_power() const {return total_laser_power_;}
		long total_laser_power() {return total_laser_power_;}

		long total_detector_power() const {return total_detector_power_;}
		long total_detector_power() {return total_detector_power_;}
		
		double power_switch_update();
		double power_modulator_update(long data_size);
		double power_demodulator_update(long data_size);
		double power_laser_update(long data_size);
		double power_detector_update(long data_size);
		double power_report(FILE *fd, add_type address_);

		void photonic_message_transmission(){};

		sim_ps_template();
		sim_ps_template(const add_type & e, long f);
		
};

#endif
