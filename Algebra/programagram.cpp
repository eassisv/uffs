#include <stdio.h>
#include <vector>
#include <queue>
using namespace std;

#define pb push_back

double determinante(vector <double> a[]){
	double factor = 0, temp = 0;
	int i, j, k, count = 0, m = 5;
  for(i = 0; i < m - 1; i++){
    if(a[i][i] == 0){
      for(k = i; k < m; k++){
				if(a[k][i] != 0){
	  			for(j = 0; j < m; j++){
	    			temp = a[i][j];
	    			a[i][j] = a[k][j];
	    			a[k][j] = temp;
	  			}
	  		k = m;
				}
      }
      count++;
    }
    if(a[i][i] != 0){
      for(k = i + 1; k < m; k++){
				factor = -1.0 * a[k][i] /  a[i][i];
					for(j = i; j < m; j++){
	  				a[k][j] = a[k][j] + (factor * a[i][j]);
					}
      }
    }
  }
  temp = 1.0;
  for(i = 0; i < m; i++)
    temp *= a[i][i];
  if(count % 2 == 0)
    return temp;
  else
    return -1.0 * temp;
}

double escalar(vector <double> v, vector <double> w){
	double esc;
	for(int i = esc = 0; i < 5; i++) esc += v[i] * w[i];
	return esc;
}

void formula(vector <double> v, vector <double> w[], int i){
	double x;
	int j = i-1;
	x = escalar(v, w[j]) / escalar(w[j], w[j]);
	for(int k = 0; k < 5; k++)
		w[i].pb(v[k] - w[j][k] * x);
	j--;
	while(j >= 0){
		x = escalar(v, w[j]) / escalar(w[j], w[j]);
		for(int k = 0; k < 5; k++)
			w[i][k] -= (w[j][k] * x);
		j--;
	}

}


void gram_schmidt(vector <double> v[], vector <double> w[]){
	w[0] = v[0];
	int i;
	for(i = 1; i < 5; i++){
		formula(v[i], w, i);
	}	
}

int main(void){
  vector < double > v[5], m[5], w[5];
  FILE *f;
  f = fopen("vetores.txt", "r+");
	int j, i = 0;
	char c;

	while(fscanf(f, "%c", &c) != EOF){
		if(v[i].size() > 4) i++;
		if(c >= '0' && c <= '9') v[i].pb(c - '0');
	}

	for(i = 0; i < 5; i++)
		for(j = 0; j < 5; j++)
			m[i].pb(v[j][i]);

	if(!determinante(m)){
		fprintf(f, "O conjunto nao e uma base\n");
		fclose(f);
		return 0;
	}
	gram_schmidt(v, w);
	for(i = 0; i < 5; i++){
		fprintf(f, "w%d = (", i+1);
		for(j = 0; j < 4; j++)
			fprintf(f, "%s%lf, ", (w[i][j] + 0.0000001 < 0) ? "" : " ", w[i][j] + 0.0000001);
		fprintf(f, "%s%lf )\n", (w[i][j] + 0.0000001 < 0) ? "" : " ", w[i][j] + 0.0000001);
	}

  fclose(f);

	return 0;
}
