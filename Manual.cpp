#include <iostream>
#include "colores.cpp"
using namespace std;

/*
ANGEL EDUARDO MUÑOZ PEREZ

*/


void MenuPrincipal(){
	system("cls");
	//Margenes
	color(3);
	gotoxy(1,2); cout<<"===========================================================";
	gotoxy(1,12);cout<<"===========================================================";
	for(int altura =3; altura <12; altura++){
		gotoxy(0, altura); cout<<"|";
		gotoxy(60,altura); cout<<"|";
	}
	
	const int colormenu = 10;
	const int colormenuescogido = 4;
	const int colormenunormal = 10;
	//Menu de opciones
	color (2);gotoxy(15,3);cout<<"Que deseas consultar?";
	color(colormenu);gotoxy(2,5); cout<<"[1]  Tipos de datos";
	color(colormenu);gotoxy(2,6); cout<<"[2]  Entradas y salidas";
	color(colormenu);gotoxy(2,7); cout<<"[3]  Condicionale";
	color(colormenu);gotoxy(2,8); cout<<"[4]  Ciclos";
}// #### FIN DE FUNCION MenuPrincipal ####


int main(){
	color(9); gotoxy(1,2); cout<<"               BIENVENIDO A MI PROGRAMA"<<endl;
	color(9); gotoxy(1,3); cout<<"=========================================================="<<endl;
	color(7); gotoxy(1,5); cout<<"C++ es un lenguaje de programación de propósito general"<<endl; 
			  gotoxy(1,6); cout<<"   de paradigma estructurado y orientado a objetos"<<endl;
			  gotoxy(1,7); cout<<"es de alto rendimiento y es usado en programas de alto"<<endl;
			  gotoxy(1,8); cout<<"  rendimiento, viedojuegos, SO y sistemas embebidos"<<endl;
								
	color(15);gotoxy(1,10);cout<<"PRESIONE CUALQUIER TECLA PARA CONTINUAR"<<endl;
	char opcion;
	if (cin>>opcion){
		MenuPrincipal();
	}							
}//FIN DEL MAIN

