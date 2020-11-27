
// Implementation of Kernighan-Lin Algorithm


#include <iostream>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <cstdlib>
using namespace std;

struct Node		//Circuit elemnts as node
{
	int id;		
	int D;		
	bool flag;	
	int set;	
};

int ** graph;	//Undirected Graph 
Node * node;	//node
int nodeNum;	//number of nodes
int ed;			//number of edges
int * G1;		//Partition 1
int * G2;		//Partition 2

//Benefit D(x)=E(x)-I(x)
int getD(int x)
{
	int D = 0;
	for (int i = 0; i < nodeNum; i++)
	{
		if (graph[x][i] == 1)
		{
			if (node[x].set != node[i].set)
			{
				D++;
			}
			else
			{
				D--;
			}
		}
	}
	return D;
}
int main(int argc, char ** argv)
{

	ios_base::sync_with_stdio(false);
    cin.tie(NULL);
   
	cout<<"\nNumber of Nodes:"<<endl;
	cin>>nodeNum;
	graph = new int*[nodeNum];
	for (int i = 0; i < nodeNum; i++)
	{
		graph[i] = new int[nodeNum];
	}

	for (int i = 0; i < nodeNum; i++)
	{ 
		for (int j = 0; j < nodeNum; j++)
		{
			graph[i][j]=0;
		}
	}
	
	cout<<"Enter Number of Edges:"<<endl;
	cin>>ed;
	cout<<"Enter edges"<<endl;
	for(int i=0;i<ed;i++)
	{
		int u,v;
		cin>>u>>v;
		graph[u-1][v-1]=1;
		graph[v-1][u-1]=1;
	}

	//step 0
	node = new Node[nodeNum];
	int n = nodeNum / 2;
	for (int i = 0; i < nodeNum; i++)
	{
		node[i].id = i;
		node[i].D = 0;
		node[i].flag = false;
		node[i].set = 0;
	}

	G1 = new int[n];
	G2 = new int[n];
	for (int i = 0; i < n; i++)
	{
		G1[i] = i;
		node[i].set = 1;
		G2[i] = n + i;
		node[n + i].set = 2;
	}

	//step 1
	int* temp_G1;
	int* temp_G2;
	temp_G1 = new int[n];
	temp_G2 = new int[n];
	int temp_gain = 0;
	int final_gain = 0;

	for (int i = 0; i < n; i++)
	{
		temp_G1[i] = G1[i];
		temp_G2[i] = G2[i];
	}

	//step2
	//
	int init = n;
	while (init > 0)
	{
		for (int i = 0; i < nodeNum; i++)
		{
			node[i].D = getD(i);
		}


		int max_gain = -10000;
		int temp_a_index = -1;
		int temp_b_index = -1;
		//int tempResult0;

		for (int i = 0; i < n; i++)
		{
			if (node[G1[i]].flag == true)
			{
				continue;
			}
			for (int j = 0; j < n; j++)
			{
				if (node[G2[j]].flag == true)
				{
					continue;
				}
				
				int tempResult = getD(G1[i]) + getD(G2[j]) - 2 * graph[G1[i]][G2[j]];
				if (tempResult > max_gain)
				{
					temp_a_index = i;
					temp_b_index = j;
					max_gain = tempResult;
				}
			}
		}
		
		node[G1[temp_a_index]].flag = true;
		node[G2[temp_b_index]].flag = true;
		int temp = G1[temp_a_index];
		G1[temp_a_index] = G2[temp_b_index];
		G2[temp_b_index] = temp;
		node[G1[temp_a_index]].set = 1;
		node[G2[temp_b_index]].set = 2;

		init--;

		temp_gain += max_gain;
		if (temp_gain > final_gain)
		{
			final_gain = temp_gain;
			for (int i = 0; i < n; i++)
			{
				temp_G1[i] = G1[i];
				temp_G2[i] = G2[i];
			}
		}
	}

	cout<<"----------------------------------------------------------------------"<<endl;
	cout << "The First Partition is " << endl;
	for (int i = 0; i < n; i++)
	{
		cout << temp_G1[i] + 1 << ' ';
	}
	cout << endl;
	
        cout<<"----------------------------------------------------------------------"<<endl;
	cout << "The 2nd Partiton is " << endl;
	for (int i = 0; i < n; i++)
	{
		cout << temp_G2[i] + 1 << ' ';
	}
	cout << endl;

	

	return 0;
}
