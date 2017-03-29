#ifndef EVC_H
#define EVC_H
#include <vector>
using namespace std;
#include "configuration.h"
#include "RouterIDMap.h"
extern "C" {
#include "../host.h"
};
struct mynode
{
	int network_ID;
	int input_port;
	int output_port;
}
struct mytableItem
{
    int msgNo;
    vector <mynode >path;
};
extern vector <mytableItem >mytable;
extern void AddMytablePath(int,int, int);
extern int CheckMyTableConflict(int, int , int);
extern void RemoveItem(int);

#endif