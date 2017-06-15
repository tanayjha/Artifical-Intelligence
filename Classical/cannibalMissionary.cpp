#include <bits/stdc++.h>
using namespace std;
int pos;
vector <vector <int> > graph[100000];
map <vector<int>, int> id, marked;
void createId(vector<int> v, int k) {
	id[v] = pos++;
	if(k == 4)
		return;
	for(int i = 0; i < 4; i++) {
		v[k] = i;
		createId(v, k+1);
	}
}
void createGraph(vector<int> v) {
	if(marked.find(v) != marked.end())
		return;
	marked[v] = 1;
	if(v[0] > 0 && v[1] > 0 && (v[0]-1) >= (v[1]-1) && (v[2]+1) >= (v[3]+1)) {
		v[0] -= 1;
		v[1] -= 1;
		v[]

	}
}
int main()
{
	vector <int> v;
	int k = 4;
	while(k--) {
		v.push_back(0);
	}
	createId(v, 0);
	v[0] = 3;
	v[1] = 3;
	v[2] = 0;
	v[3] = 0;
	createGraph(v);
}