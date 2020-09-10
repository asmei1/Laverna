#include <stdio.h>

int main(void) {
	int tab[1000];
	int i;
	int suma = 0;
	int suma_max = 0;
	int suma_min = 0;
	float srednia = 0.0;
	int zlicz = 0;

	printf("Podaj liczby: ");

	for (i = 0; i < 1000; i++) {
		int test = scanf("%i", &tab[i]);
		if (!test) {
			printf("Incorrect input\n");
			return 1;
		}
		if (tab[i] == 0) {
			break;
		}
		suma += tab[i];
		zlicz++;
	}

	srednia = (float)suma / (float)i;

	if(zlicz == 0){
		printf("Brak danych\n");
		return 0;
	}

	for (i = 0; i < zlicz; i++) {
		if (tab[i] > srednia) {
			suma_max += tab[i];
		}
		if (tab[i] < srednia) {
			suma_min += tab[i];
		}
	}

	printf("%.2f\n", srednia);
	printf("%i\n", suma_max);
	printf("%i", suma_min);

	return 0;
}

