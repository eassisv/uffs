#include <stdio.h>

void calculaHora(int x, int *hr, int *min){
	*hr = *min = 0;
	while(x >= 60){
		*hr += 1;
		x -= 60;
	}
	*min = x;
}

int main(void){
	int minutos, hr, min;

	scanf("%d", &minutos);
	calculaHora(minutos, &hr, &min);
	printf("%d:", hr);
	if(min < 10) printf("0");
	printf("%d\n", min);

	return 0;
}