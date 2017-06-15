#include <bits/stdc++.h>
using namespace std; 
int pos;
vector <vector <int> > graph[100000];
map <vector <int>, int> id;
map <vector <int>, int>:: iterator it;
bool noConflicts(vector <int> v, int k) {
	for(int i = 1; i < k; i++) {
		if((v[k] == v[i]) || (v[k]-(k-i) == v[i]) || (v[k]+(k-i) == v[i]))
			return false;
	}
	return true;
}
void createID(vector <int> v, int k) {
	if(k == 9) {
		id[v] = pos++;
		return;
	}
	id[v] = pos++;
	for(int i = 1; i <= 8; i++) {
		v[k] = i;
		if(noConflicts(v, k))	
			createID(v, k+1);
	}
}
void createSearchGraph(vector <int> v, int k) {
	if(k == 9)
		return;
	int pos = id[v];
	for(int i = 1; i <= 8; i++) {
		v[k] = i;
		graph[pos].push_back(v);
		if(noConflicts(v, k))
			createSearchGraph(v, k+1);
	}
}
int main()
{
	vector <int> v;
	int k = 9;
	while(k--)
		v.push_back(0);
	createID(v, 1);
	createSearchGraph(v, 1);
	int c = 0;
	for(it = id.begin(); it != id.end(); it++) {
		vector <int> x = it->first;
		int f = 0;
		for(int j = 1; j < x.size(); j++) {
			if(x[j] == 0) {
				f = 1;
				break;
			}
		}
		if(!f && noConflicts(x, 8))
			c++;
	}
	cout<<c<<endl;
}