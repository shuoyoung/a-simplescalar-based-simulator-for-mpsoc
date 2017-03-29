#include "mynode.h"

mynode& mynode::operator = (const mynode& mynode1)	
{
	x = mynode1.x;
	y = mynode1.y;
	in = mynode1.in;
	out = mynode1.out;
	return *this;
}
/*
int mynode::operator==(const mynode& mynode1, const mynode& mynode2)
{
	if((mynode1.x==mynode2.x)&&(mynode1.y==mynode2.y)&&(mynode1.in==mynode2.in)&&(mynode1.out==mynode2.out))
		return 1;
	else 
		return 0;
}*/
int mynode::operator == (const mynode& mynode1)
{
	if((network_ID==mynode1.network_ID)&&(in==mynode1.in)&&(out==mynode1.out))
		return 1;
	else 
		return 0;
}

mynode::mynode(int a int c, int d)
{
	network_ID=a;
	in=c;
	out=d;
}

mynode::mynode()
{
	network_ID = 0;
	in = 0;
	out = 0;
}
