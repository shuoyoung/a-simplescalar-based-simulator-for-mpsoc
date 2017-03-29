#include "EVC.h"
vector <mytableItem >mytable;

int CheckMyTableConflict(int msgNo, int cur_node, int next_node)
{
    if (mytable.size () == 0)
    {
        return 0;
    }
    for (int i = 0 ; i <mytable.size();i++ )
    {
        for (int j = 0; j <mytable[i].path.size()-1; j++ )
        {
            if (cur_node == mytable[i].path[j] && next_node == mytable[i].path[j+1] )
            {
                return 1;
            }
        }
    }
    return 0;
}


void RemoveItem(int msgNo)
{
    for (int i = 0 ; i <mytable.size();i++ )
    {
        if (mytable[i].msgNo == msgNo)
		{
			mytableItem.erase(i+mytable.begin());
			return;
		}
    }

}
void AddMytablePath(int msgNo, int cur_node, int next_node)
{
    int flag = 0;
    int i = 0;
    for ( i = 0 ; i < mytable.size(); i ++)
    {
        if (mytable[i].msgNo ==msgNo )
        {
            flag = 1;
            break;
        }
    }
    if (flag == 0)
    {
        //新加一项
        mytableItem item;
        item.msgNo = msgNo;
        mytable.push_back(item);
        i = mytable.size()-1;
    }
    //加入新的node到path里
    mytable[i].path.push_back(cur_node);
}
