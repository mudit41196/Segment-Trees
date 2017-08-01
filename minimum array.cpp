#include<iostream>
using namespace std;

void constructmin(int arr[],int segment[],int low,int high,int pos)
{
	if(low==high)
	{
		segment[pos]=arr[low];
		return;
	}
	int mid=(low+high)/2;
	constructmin(arr,segment,low,mid,2*pos+1);  //create left subtree with root at 2*pos +1 of segment tree
	constructmin(arr,segment,mid+1,high,2*pos+2); //create right subtree with root at 2*pos +2 of segment tree
	segment[pos]=min(segment[2*pos+1],segment[2*pos+2]); //root data will be minimum of root of leftsubtree and root of right subtree
}
int rangemin(int segment[],int qlow,int qhigh,int low,int high,int pos)
{
	if(qlow<=low && qhigh>=high)
	{
		return segment[pos];		//total overlap
	}
	if(qlow>high || qhigh<low)    //no overlap
	{
		return 1000;				//a very big value
	}
	//otherwise do this
	int mid=(low+high)/2;
	int left=rangemin(segment,qlow,qhigh,low,mid,2*pos+1);
	int right=rangemin(segment,qlow,qhigh,mid+1,high,2*pos+2);
	return min(left,right);
}
void constructsum(int arr2[],int segmenttree2[],int low,int high,int pos)
{
	if(low==high)
	{
		segmenttree2[pos]=arr2[low];
		return;
	}
	int mid=(low+high)/2;
	constructsum(arr2,segmenttree2,low,mid,2*pos+1);
	constructsum(arr2,segmenttree2,mid+1,high,2*pos+2);
	segmenttree2[pos]=segmenttree2[2*pos+1]+ segmenttree2[2*pos+2];
}
int rangesum(int segmenttree2[],int qlow,int qhigh,int low,int high,int pos)
{
	if(qlow <= low && qhigh>=high)
	{
		return segmenttree2[pos];
	}
	if(qlow>high || qhigh < low)
	{
		return 0;
	}
	int mid=(low+high)/2;
	int left=rangesum(segmenttree2,qlow,qhigh,low,mid,2*pos+1);
	int right=rangesum(segmenttree2,qlow,qhigh,mid+1,high,2*pos+2);
	return left+right;
}
int main()
{
	int arr[4]={-1,2,4,0};
	int segmenttree[7];
	int i;
	for(i=0;i<7;i++)
	{
		segmenttree[i]=1000;
	}
	constructmin(arr,segmenttree,0,3,0);
	cout << rangemin(segmenttree,0,3,0,3,0)<< endl;
	
	
	int arr2[6]={1,3,5,7,9,11};
	int segmenttree2[11]={0};
	constructsum(arr2,segmenttree2,0,5,0);
	cout << rangesum(segmenttree2,2,5,0,5,0) << endl;
	
}
