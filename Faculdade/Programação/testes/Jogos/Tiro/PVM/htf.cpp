#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define BORDA_SUP 5
#define BORDA_INF 25
#define VEL_TIRO 20 //milissegundos

void gotoxy(int x, int y){
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),(COORD){x,y});
}   

void atualizarPontos(int hits, int fail){
	gotoxy(3, 3);
	printf("Acertos: %d ", hits);
	
	gotoxy(20, 3);
	printf("Erros: %d ", fail);
}

void subir(int *x, int *y){
	if(*y>BORDA_SUP+1){
		gotoxy(*x, *y);
		printf(" ");
		*y-=1;
		gotoxy(*x, *y);
		printf ("%c", 220);
	}
}

void descer(int *x, int *y){
	if(*y<BORDA_INF-1){
		gotoxy(*x, *y);
		printf(" ");
		*y+=1;
		gotoxy(*x, *y);
		printf ("%c", 220);
	}
}

void desenharCenario(){
	for(int i=0; i<80;i++){
		gotoxy(i, BORDA_SUP);
		printf ("%c", 177);
	}
	
	for(int i=0; i<80;i++){
		gotoxy(i, BORDA_INF);
		printf ("%c", 177);
	}		
}

void mudaAlvo(int *ax, int *ay){
	gotoxy(*ax, *ay);
	printf(" ");
	int teste = 0;
	*ax = 6 + rand() % 74;
	*ay = 6 + rand() % (BORDA_INF-7);
	
    gotoxy(*ax, *ay);
	printf ("%c", 1);
}

int main (){
	
	int x = 5, 	
		y = 19, 
		auxT = 0, 
		ax, ay, 
		hits = 0,
		fail = 0,
		auxY = 0, 
		trocarPos = 0,
		vel = 10,
		acertou = 0;
	
	char tecla;
	
	srand(time(NULL));
	
	desenharCenario();
	
    gotoxy(5, 19);
	printf ("%c", 220);
	atualizarPontos(hits, fail);
	
	ax = 50; //desenha atirador
	ay = 10;
	gotoxy(ax, ay);
	printf ("%c", 1);
	
	while(1){
		while(kbhit()){
			tecla = getch();
			if(tecla == 72 || tecla == 119){ //subir
				subir(&x, &y);
			}
			if(tecla == 80 || tecla == 115){ //descer
				descer(&x, &y);
			}		
			if(tecla == 32){ //se atirar
				auxY=y;
				for(int i=7;i<81;i++){ //tiro
					Sleep(vel); 
					gotoxy(i, auxY);   
					printf ("%c", 175);
				    gotoxy(i-1, auxY);
					printf (" ");
							
					if(kbhit()){
						tecla = getch();
						if(tecla == 72 || tecla == 119){ //subir
							subir(&x, &y);
						}
						if(tecla == 80 || tecla == 115){ //descer
							descer(&x, &y);
						}		
						if(tecla == 68 || tecla == 97){
							vel+=3;
						}
						if(tecla == 65 || tecla == 100){
							if(vel>3)
								vel-=3;
						}
					
					}
					
					if(ax==i &&ay==auxY){ //se acertou alvo
						mudaAlvo(&ax, &ay);
						hits++;
						atualizarPontos(hits, fail);
						acertou = 1;
					}
					
					if(!acertou){
						if(i==80){
							fail++;
							atualizarPontos(hits, fail);
						}
					}
				}
				vel = 20;
				auxY=y; //recupera posição atual do eixo y
				acertou = 0;
			}		
		}			
	}	
}
