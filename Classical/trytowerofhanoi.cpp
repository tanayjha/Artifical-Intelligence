#include <bits/stdc++.h>
using namespace std;
int pos, node;
vector <int> ans; 
vector <vector<int> > graph[1000000];
map <vector<int>, int> id, marked;
map <int, vector <int> > reverseid;
map <int, int> parent;
void createID(vector <int> v, int k, int n) {
	id[v] = pos++;
	reverseid[pos-1] = v;
	if(k == n) 
		return;
	v[k] = 1;
	createID(v, k+1, n);
	v[k] = 2;
	createID(v, k+1, n);
	v[k] = 3;
	createID(v, k+1, n);	
}
void createGraph(vector <int> v, int n) {
	int topOf1 = INT_MIN, topOf2 = INT_MIN, topOf3 = INT_MIN;
	if(marked.find(v) != marked.end())
		return;
	marked[v] = 1;
	int position = id[v];
	for(int i = 0; i < n; i++) {
		if(v[i] == 1)
			topOf1 = i;
		if(v[i] == 2)
			topOf2 = i;
		if(v[i] == 3)
			topOf3 = i;
	}
	if(topOf2 != INT_MIN && topOf1 < topOf2) {
		v[topOf2] = 1;
		graph[position].push_back(v);
		createGraph(v, n);
		v[topOf2] = 2;
	}
	if(topOf1 != INT_MIN && topOf1 > topOf2) {
		v[topOf1] = 2;
		graph[position].push_back(v);
		createGraph(v, n);
		v[topOf1] = 1;
	}

	if(topOf3 != INT_MIN && topOf1 < topOf3) {
		v[topOf3] = 1;
		graph[position].push_back(v);
		createGraph(v, n);
		v[topOf3] = 3;
	}
	if(topOf1 != INT_MIN && topOf1 > topOf3) {
		v[topOf1] = 3;
		graph[position].push_back(v);
		createGraph(v, n);
		v[topOf1] = 1;
	}

	if(topOf3 != INT_MIN && topOf2 < topOf3) {
		v[topOf3] = 2;
		graph[position].push_back(v);
		createGraph(v, n);
		v[topOf3] = 3;
	}
	if(topOf2 != INT_MIN && topOf2 > topOf3) {
		v[topOf2] = 3;
		graph[position].push_back(v);
		createGraph(v, n);
		v[topOf2] = 2;
	} 
}
void printSolution(int val, int n) {
	vector <int> v;
	for(int i = 1; i <= n; i++)
		v.push_back(3);
	int position = id[v];
	while(position != val) {
		ans.push_back(position);
		position = parent[position];
	}
	cout<<"The starting configuration is ";
	for(int i = 0; i < n; i++)
		cout<<1;
	cout<<endl;
	for(int i = ans.size()-1; i >= 0; i--) {
		cout<<"The next state is ";
		v = reverseid[ans[i]];	
		for(int j = 0; j < v.size(); j++)
			cout<<v[j];
		cout<<endl;
	}
}
void searchSolution(vector <int> v, int n) {
	if(marked.find(v) != marked.end())
		return;
	marked[v] = 1;
	int position = id[v];
	for(int i = 0; i < graph[position].size(); i++) {
		if(parent.find(id[graph[position][i]]) == parent.end())
			parent[id[graph[position][i]]] = position;
		int f = 0;
		for(int j = 0; j < graph[position][i].size(); j++) {
			if(graph[position][i][j] != 3) {
				f = 1;
				break;
			}
		}
		if(!f) {
			cout<<"Solution found\n";
			printSolution(node, n);
			exit(0);
		}
		searchSolution(graph[position][i], n);
	}
}
int main()
{
	vector <int> v;
	int n;
	cout<<"Enter the number of dics ";
	cin>>n;
	for(int i = 1; i <= n; i++)
		v.push_back(1);
	createID(v, 0, n);
	createGraph(v, n);
	for(int i = 0; i < n; i++)
		v[i] = 1;
	node = id[v];
	marked.clear();
	searchSolution(v, n);
}