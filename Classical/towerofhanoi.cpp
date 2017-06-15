#include <bits/stdc++.h>
using namespace std; 
void solveTowerOfHanoi(char source, char destination, char aux, int noOfDiscs) {
  if(noOfDiscs == 0)
    return;
  solveTowerOfHanoi(source, aux, destination, noOfDiscs-1);
  cout<<"Move from peg "<<source<<" to peg "<<destination<<endl;
  solveTowerOfHanoi(aux, destination, source, noOfDiscs-1);
}
int main() 
{
  int n;
  cout<<"Enter the number of discs: ";
  cin>>n;
  solveTowerOfHanoi('A', 'C', 'B', n);
}