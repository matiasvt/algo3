
#include <iostream>
#include <vector>
#include <assert.h>
#include <cstdio>
using namespace std;

int main() {

  freopen("input.in", "r", stdin);
  freopen("output.out", "w", stdout);
  
  int n, actual, temp, c, cantPasos;
  vector<int> puente, res;
  
  while(cin >> n >> c) {
	  
	  c = c + 1;
	  puente.resize(n + 1); 
	  res.resize(n); fill(res.begin(), res.end(), 0);
	  
	  for(int i=1; i<=n; i++) { cin >> puente[i]; }
	  
	  actual = 0; cantPasos = 0;

	  while(actual <= n) {
		
		temp = 0; actual += c;
		
		while(temp < c && puente[actual] == 1) {
			
			actual--;
			temp++;
		}
		if(temp == c) {cout << "no" << endl; break; }
		
	    res[cantPasos] = actual; cantPasos++;
	  }
	  if(temp==c) { continue; }
	  cout << cantPasos << " ";
	  for(int i=0; i<cantPasos; i++) {cout << res[i] << " ";}
	  cout << endl;
  }
  
  return 0;
}
