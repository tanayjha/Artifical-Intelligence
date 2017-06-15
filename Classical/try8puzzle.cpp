#include <bits/stdc++.h>
using namespace std; 
int pos, countv;
vector <vector <int> > graph[450000];
map <vector <int>, int> id, marked;
map <vector <int>, int>:: iterator it;
void createID(vector <int> v) {
	vector <int> x;
	for(int i = 0; i <= 8; i++)
		x.push_back(i);
	id[v] = pos++;
	next_permutation(v.begin(), v.end());
	while(v != x) {
		id[v] = pos++;
		next_permutation(v.begin(), v.end());
	}
}
void createSearchGraph(vector <int> v) {
	if(marked.find(v) != marked.end()) {
		return;
	}
	marked[v] = 1;
	int pos = id[v];
	int position;
	for(int i = 0; i < 9; i++) {
		if(v[i] == 0) {
			position = i;
			break;
		}
	}	
	if((position == 1) || (position == 2) || (position == 4) ||(position == 5) || (position == 7) || (position == 8)) {
		swap(v[position], v[position-1]);
		countv++;
		graph[pos].push_back(v);
		createSearchGraph(v);
		swap(v[position], v[position-1]);
	}
	if((position == 0) || (position == 1) || (position == 3) ||(position == 4) || (position == 6) || (position == 7)) {
		swap(v[position], v[position+1]);
		countv++;
		graph[pos].push_back(v);
		createSearchGraph(v);
		swap(v[position], v[position+1]);	
	}
	// if((position == 3) || (position == 4) || (position == 5) ||(position == 6) || (position == 7) || (position == 8)) {
	// 	swap(v[position], v[position-3]);
	// 	countv++;
	// 	graph[pos].push_back(v);
	// 	createSearchGraph(v);
	// 	swap(v[position], v[position-3]);	
	// }
	if((position == 0) || (position == 1) || (position == 2) ||(position == 3) || (position == 4) || (position == 5)) {
		swap(v[position], v[position+3]);
		// cout<<position<<endl;
		countv++;
		graph[pos].push_back(v);
		createSearchGraph(v);
		swap(v[position], v[position+3]);	
	}
	cout<<countv<<endl;
}
int main()
{
	vector <int> v;
	for(int i = 0; i <= 8; i++)
		v.push_back(i);
	createID(v);
	cout<<id.size()<<endl;
	createSearchGraph(v);
	cout<<graph[0].size()<<endl;
	cout<<countv<<" HERE\n";
}