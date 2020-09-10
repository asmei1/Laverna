#include <stdio.h>

int main(void) {
	int t[1000];
	int i;
	int suma = 0;
	int suma_maxi = 0;
	int suma_mini = 0;
	float srednia = 0.0;
	int z = 0;

	printf("Podaj liczby: ");

	for (i = 0; i < 1000; i++) {
		int test = scanf("%i", &t[i]);
		if (!test) {
			printf("Incorrect input\n");
			return 1;
		}
		if (t[i] == 0) {
			break;
		}
		suma += t[i];
		z++;
	}

	srednia = (float)suma / (float)i;

	if(z == 0){
		printf("Brak danych\n");
		return 0;
	}

	for (i = 0; i < z; i++) {
		if (t[i] > srednia) {
			suma_maxi += t[i];
		}
		if (t[i] < srednia) {
			suma_mini += t[i];
		}
	}

	printf("%.2f\n", srednia);
	printf("%i\n", suma_maxi);
	printf("%i", suma_mini);

	return 0;
}

