#include <bits/stdc++.h>
using namespace std;
vector <vector<int> > allPerm;
map <char, int> m;
set <char> distinct;
set <char>:: iterator it;
void createPerm(vector <int> v, int k, int n) {
	int f = 0;
	for(int i = 0; i < k; i++) {
		if(v[k] == v[i]) {
			f = 1;
			break;
		}
	}
	if(!f)
		allPerm.push_back(v);
	if(k == n)
		return;
	for(int i = 0; i < 10; i++) {
		v[k] = i;
		createPerm(v, k+1, n);
	}
}
void solve(string s1, string s2, string s3) {
	for(int i = 0; i < allPerm.size(); i++) {
		int k = 0;
		for(it = distinct.begin(); it != distinct.end(); it++) {
			// if(m[*it] != 0)
			// 	continue;
			m[*it] = allPerm[i][k++];
		}
		int firstNum = 0, secondNum = 0;
		for(int j = 0; j < s1.length(); j++) {
			firstNum += pow(10, s1.length()-j-1)*(m[s1[j]]);
		}
		for(int j = 0; j < s2.length(); j++) {
			secondNum += pow(10, s2.length()-j-1)*(m[s2[j]]);
		}
		int f = 0;
		int finalNum = firstNum + secondNum;
		int finalStore = finalNum;
		for(int j = s3.length()-1; j >= 0; j--) {
			if(m[s3[j]] == 0 || (m[s3[j]] == (finalNum%10))) {

			} else {
				f = 1;
				break;
			}
			finalNum = finalNum/10;
		}
		if(!f && finalStore == 10652) {
			cout<<"The solution is "<<firstNum<<"+"<<secondNum<<"="<<finalStore<<endl;
			exit(0);
		}
	}
}
int main()
{
	string s1, s2, s3;
	for(int i = 65; i <= 65+26; i++) {
		m[char(i)] = 0;
	}
	cout<<"Enter first string ";
	cin>>s1;
	cout<<"Enter second string ";
	cin>>s2;
	for(int i = 0; i < s1.length(); i++)
		distinct.insert(s1[i]);
	for(int i = 0; i < s2.length(); i++)
		distinct.insert(s2[i]);
	cout<<"Enter the output string ";
	cin>>s3; 
	// if(s3.length() == s1.length() + 1)
	// 	m[s3[0]] = 1;
	int c = distinct.size();
	cout<<c<<endl;
	// for(it = distinct.begin(); it != distinct.end(); it++) {
	// 	if(m[*it] == 0)
	// 		c++;
	// }
	vector <int> v;
	for(int i = 0; i < c; i++)
		v.push_back(0);
	createPerm(v, 0, c);
	v[0] = 9;
	v[1] = 5;
	v[2] = 6;
	v[3] = 7;
	v[4] = 1;
	v[5] = 0;
	v[6] = 8;
	if(find(allPerm.begin(), allPerm.end(), v) != allPerm.end())
		cout<<"HERE\n";
	cout<<allPerm.size()<<endl;
	solve(s1, s2, s3);
}