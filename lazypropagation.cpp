#include<iostream>
using namespace std;
void construct(int arr[],int segmenttree[],int low,int high,int pos)
{	
	if(low>high){return;}
	if(low==high)
	{
		segmenttree[pos]=arr[low];
		return;
	}
	int mid=(low+high)/2;
	construct(arr,segmenttree,low,mid,2*pos+1);
	construct(arr,segmenttree,mid+1,high,2*pos+2);
	segmenttree[pos]=min(segmenttree[2*pos+1],segmenttree[2*pos+2]);
	
}

void update(int segmenttree[],int lazytree[],int qlow,int qhigh,int k,int low,int high,int pos) //k is the number by which we want to increment in range qlow to qhigh
{
	if(low>high){return;}
	
	if(lazytree[pos]!=0)
	{
		segmenttree[pos]+=lazytree[pos];
		if(low!=high)
		{
			lazytree[2*pos+1]+=lazytree[pos];
			lazytree[2*pos+2]+=lazytree[pos];
		}
		lazytree[pos]=0;
	}
	
	if(qlow>high || qhigh<low)			//if there is no overlapping, dont make any changes
	{
		return;
	}
	if(qlow<=low && qhigh>=high)		//if there is complete overlapping, make changes to root of segment tree, and make changes to children in lazy tree
	{
		segmenttree[pos]=segmenttree[pos]+k;
		if(low!=high)
		{
			lazytree[2*pos+1]=lazytree[2*pos+1]+k;
			lazytree[2*pos+2]=lazytree[2*pos+2]+k;
		}
		return;
	}
	int mid=(low + high)/2;											//if there is partial overlap
	update(segmenttree,lazytree,qlow,qhigh,k,low,mid,2*pos+1);
	update(segmenttree,lazytree,qlow,qhigh,k,mid+1,high,2*pos+2);
	segmenttree[pos]=min(segmenttree[2*pos+1],segmenttree[2*pos+2]);
}

int rangeminquery(int segmenttree[],int lazytree[],int qlow,int qhigh,int low,int high,int pos)
{
	if(low>high){return 1000;}
	
	if(lazytree[pos]!=0)
	{
		segmenttree[pos]+=lazytree[pos];
		if(low!=high)
		{
			lazytree[2*pos+1]+=lazytree[pos];
			lazytree[2*pos+2]+=lazytree[pos];
		}
		lazytree[pos]=0;
	}
	if(qlow > high || qhigh < low)		//no overlapping
	{
		return 1000;
	}
	if(qlow<=low && qhigh>=high)		//complete overlapping
	{
		return segmenttree[pos];
	}
	
	int mid=(low+high)/2;
	int left=rangeminquery(segmenttree,lazytree,qlow,qhigh,low,mid,2*pos+1);
	int right=rangeminquery(segmenttree,lazytree,qlow,qhigh,mid+1,high,2*pos+2);
	return min(left,right);
}

int main()
{
	int arr[8]={-1,2,4,1,7,1,3,2};
	int segmenttree[15];			//if the size of main array is n,then size of segment tree is always 2n-1
	int i;
	for(i=0;i<15;i++)
	{
		segmenttree[i]=1000;
	}
	int lazytree[15]={0};
	construct(arr,segmenttree,0,7,0);
	for(i=0;i<15;i++)
	{
		cout << segmenttree[i] << " ";
	}
	
	update(segmenttree,lazytree,0,3,3,0,7,0);
	cout << endl << "Segment Tree after update" << endl;
	for(i=0;i<15;i++)
	{
		cout << segmenttree[i] << " ";
	}
	
	cout << endl <<  "Lazy tree" << endl;
	for(i=0;i<15;i++)
	{
		cout << lazytree[i] << " ";
	}
	cout << endl << rangeminquery(segmenttree,lazytree,0,3,0,7,0) << endl;
}
