#include <bits/stdc++.h>
using namespace std;
vector <pair<int, int> > graph[10000];
int vis[100000];
void solveTSPNearestNeighbour() {
	int present = 1, ans = 0;
	while(1) {
		vis[present] = 1; 
		int val = INT_MAX, newnode = -1;
		for(int i = 0; i < graph[present].size(); i++) {
			if(!vis[graph[present][i].first] && graph[present][i].second < val) {
				val = graph[present][i].second;
				newnode = graph[present][i].first;
			}
		}
		if(newnode == -1) {
			for(int i = 0; i < graph[present].size(); i++) {
				if(graph[present][i].first == 1) {	
					ans += graph[present][i].second;
					break;
				}
			}
			cout<<"THE MINIMUM DISTANCE USING NEAREST NEIGHBOUR HEURISTIC IS "<<ans<<endl;
			break;
		}
		present = newnode;
		ans += val;
	}
}
int main()
{
	graph[1].push_back(make_pair(2, 5));
	graph[1].push_back(make_pair(3, 3));
	graph[1].push_back(make_pair(4, 4));
	graph[2].push_back(make_pair(1, 5));
	graph[2].push_back(make_pair(4, 2));
	graph[2].push_back(make_pair(3, 1));
	graph[3].push_back(make_pair(2, 1));
	graph[3].push_back(make_pair(1, 3));
	graph[3].push_back(make_pair(4, 7));
	graph[4].push_back(make_pair(1, 4));
	graph[4].push_back(make_pair(2, 2));
	graph[4].push_back(make_pair(3, 7));
	solveTSPNearestNeighbour();
}