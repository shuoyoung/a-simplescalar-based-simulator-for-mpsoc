#ifndef NETWORK_MYNODE_H_
#define NETWORK_MYNODE_H_

using namespace std;

class mynode {	
	public:
		int network_ID;
		int in;
		int out;

	public:
		int in_port() {return in;}
		int out_port() {return out;}
		mynode(int a, int c, int d);
		mynode();
		mynode& operator = (const mynode& mynode1);
		//int operator==(const mynode& mynode1, const mynode& mynode2);
		int operator == (const mynode& mynode1);
};

#endif
