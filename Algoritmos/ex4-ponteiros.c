#include <stdio.h>
#include <string.h>


void mostraMedia(double m[][4], int n){
	int i;
	for(i = 0; i < n; i++)
		printf("Aluno %d media: %.2lf\n", i+1, m[i][3]);
}

double mediaGeral(double m[][4], int n){
	int i, j;
	double mediaGeral = 0;
	for(i = 0; i < n; i++){
		for(j = 0; j < 3; j++){
			m[i][3] += m[i][j];
			mediaGeral += m[i][j];
		}
		m[i][3] /= 3.0;
	}
	return mediaGeral / (3 * n);
}

void lerNotas(double m[][4], int n){
	int i, j;
	for(i = 0; i < n; i++)
		for(j = 0; j < 3; j++)
			scanf("%lf", &m[i][j]);
}

int main(void){
	int n;

	scanf("%d", &n);
	double m[n][4], ans;
	memset(m, 0, sizeof(m));
	lerNotas(m, n);
	ans = mediaGeral(m, n);
	mostraMedia(m, n);
	printf("Media Geral = %.2lf\n", ans);

	return 0;
}