#include <bits/stdc++.h>  
using namespace std;  
struct status{ 
  int chair,stick,onchair,gotbanana;  
};
int main()
{
  status s;
  cout<<"the solution  for monkey  banana  problem :\n\n";
  s.chair = 0;
  s.stick = 0;
  s.onchair = 0;
  s.gotbanana = 0;
  if(s.chair == 0)
    cout<<"Put the chair under the banana\n";
  s.chair = 1;
  if(s.stick == 0)
    cout<<"Grab the stick\n";
  s.stick = 1;
  if(s.onchair == 0)
    cout<<"Stand on the chair\n";
  s.onchair = 1;
  if(s.gotbanana == 0)
    cout<<"Get banana with stick\n";
  cout<<endl; 
}