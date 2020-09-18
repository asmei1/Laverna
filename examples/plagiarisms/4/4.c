#include <stdio.h>
#include <stdlib.h>
//Comment
int main() {
	int tab[10][10],i=0,j=0,k=0,spr=0,sw=0,sk=0,licz=0;
	printf("podaj macierz: \n");
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			spr=scanf("%d",&tab[i][j]);
			if(spr!=1){
				printf("Incorrect input");
				return 1;
			}
		}
	}
	//sprawdzenie najwiekszej warto�ci przystej w macierzy
	int max=tab[0][0];
	for(i=0;i<10;i++){
		for(j=0;j<10;j++){
			if(tab[i][j]%2==0 && tab[i][j]>=max){
				max=tab[i][j];
				licz++;
			}
		}
	}
	//sprawdzenie czy jest co pokaza�
	if(licz==0){
		printf("Nothing to show");
	}
	else{
		for(i=0;i<10;i++){
			for(j=0;j<10;j++){
				if(max==tab[i][j]){
					for(k=0;k<10;k++){
						sw+=tab[i][k];
						sk+=tab[k][j];
					}
					printf("%d %d %d\n",j,i,sw-sk);
					sw=0;
					sk=0;
				}
			}
		}
	}

	return 0;
}
