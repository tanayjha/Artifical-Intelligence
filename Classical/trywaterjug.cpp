#include <bits/stdc++.h>
using namespace std;
int pos;
vector <pair<int, int> > graph[100000];
map <pair<int, int>, int> id, marked;
map <int, pair<int, int> > reverseid;
map <int, pair<int, int> >:: iterator it;
map <int, int> parent;
vector <int> ans;
void createID(int a, int b, int x, int y) {
	if(a > x || b > y)
		return;
	id[make_pair(a, b)] = pos++;
	reverseid[pos-1] = make_pair(a, b);
	createID(a+1, b, x, y);
	createID(a, b+1, x, y);
}
void createGraph(int a, int b, int x, int y) {
	if(marked.find(make_pair(a, b)) != marked.end())
		return;
	marked[make_pair(a, b)] = 1;
	int position = id[make_pair(a, b)];
	if(a != 0)
		graph[position].push_back(make_pair(0, b));
	createGraph(0, b, x, y);
	if(b != 0)
		graph[position].push_back(make_pair(a, 0));
	createGraph(a, 0, x, y);
	if(a != x)
		graph[position].push_back(make_pair(x, b));
	createGraph(x, b, x, y);
	if(b != y)
		graph[position].push_back(make_pair(a, y));
	createGraph(a, y, x, y);
	if(a+b <= x) {
		if(a != a+b && b != 0)
			graph[position].push_back(make_pair(a+b, 0));
		createGraph(a+b, 0, x, y);
	} else {
		if(a != x && b != (b-(x-a)))
			graph[position].push_back(make_pair(x, b-(x-a)));
		createGraph(x, b-(x-a), x, y);
	}
	if(b+a <= y) {
		if(a != 0 && b != b+a)
			graph[position].push_back(make_pair(0, b+a));
		createGraph(0, b+a, x, y);
	} else {
		if(a != (a-(y-b)), b != y)
			graph[position].push_back(make_pair(a-(y-b), y));
		createGraph(a-(y-b), y, x, y);
	}
}
void printSolution(int node) {
	while(node != 0) {
		ans.push_back(node);
		node = parent[node];
	}
	it = reverseid.find(0);
	cout<<"The starting state is "<<(it->second).first<<","<<(it->second).second<<"\n";
	for(int i = ans.size()-1; i >= 0; i--) {
		cout<<"The next state is "<<(reverseid.find(ans[i])->second).first<<","<<(reverseid.find(ans[i])->second).second<<endl;
	}
}
void searchSolution(int x, int y, int k) {
	if(marked.find(make_pair(x, y)) != marked.end())
		return;
	marked[make_pair(x, y)] = 1;
	int position = id[make_pair(x, y)];
	for(int i = 0; i < graph[position].size(); i++) {
		if(parent.find(id[make_pair(graph[position][i].first, graph[position][i].second)]) == parent.end())
			parent[id[make_pair(graph[position][i].first, graph[position][i].second)]] = position;
		if(graph[position][i].first == k && graph[position][i].second == 0) {
			cout<<"Solution found\n";
			printSolution(id[make_pair(graph[position][i].first, graph[position][i].second)]);
			exit(0);
		}
		searchSolution(graph[position][i].first, graph[position][i].second, k);
	}
}
int main()
{
	int x, y, k;
	cout<<"Enter the size of the jugs ";
	cin>>x>>y;
	if(x < y)
		swap(x, y);
	cout<<"Enter the amount you want to measure ";
	cin>>k;
	createID(0, 0, x, y);
	createGraph(x, y, x, y);
	marked.clear();
	searchSolution(x, y, k);
}