#include <Windows.h>

/*
COLORES
[1]  AZUL REY
[2]  VERDE
[3]  AZUL CYAN
[4]  ROJO
[5]  VIOLETA
[6]  AMARILLO OCRE
[7]  GRIS MUY CLARO
[8]  GRIS
[9]  AZUL
[10] VERDE PASTO
[11] CELESTE
[12] ROJO CLARO
[13] MORADO
[14] CREMA
[15] BLANCO
[16]++ FONDO  
*/
gotoxy(int x,int y){
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	
	dwPos.X = x;
	dwPos.Y = y;
	
	SetConsoleCursorPosition(hcon,dwPos);
}
gotox(int x){
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	
	dwPos.X = x;
	
	SetConsoleCursorPosition(hcon,dwPos);
}

color(int color){
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	
	SetConsoleTextAttribute(hConsole, color);
}