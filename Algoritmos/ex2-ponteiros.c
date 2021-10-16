#include <stdio.h>

int busca(int v[], int n, int x){
	int i, ans;
	for(i = ans = 0; i < n; i++)
		if(v[i] == x)
			ans++;
	return ans;
}

int main(void){
	int n, x, ans, i;

	scanf("%d %d", &n, &x);
	int vet[n];
	for(i = 0; i < n; i++)
		scanf("%d", &vet[i]);
	ans = busca(vet, n, x);
	printf("%d\n", ans);

	return 0;
}