#include <iostream>
using namespace std;
#include "colores.cpp"

int main(){
    cout<<"Arbol de decisiones"<<endl;

    char opcion1;
    char opcion2;
    char opcion3;
    color(1);
    cout<<"ESTAS EN TU CASA, vas a ir a la escuela o al ejercito?"<<endl;
    color(9);
    cout<<"[1] escuela [2] ejercito"<<endl; color(15);
    cin>>opcion1;		

    switch(opcion1){
        case '1':
            color(4);
            cout<<"FUISTE A LA ESCUELA"<<endl;
            color(1);
            cout<<"entraste a la clase de Claudia o te fuiste con las de QFB"<<endl;
            color(9);
            cout<<"[1] Claudia [2] QFB"<<endl; color(15);
            cin >>opcion2;
            switch (opcion2){
                case '1':
                    color(4);
                    cout<<"TE METISTE CON CLAUDIA"<<endl;

                    color(1);
                    cout<<"TE PUSISTE A ESTUDIAR O A JUGAR"<<endl;
                    color(9);
                    cout<<"[1] Estudiar [2] Jugar"<<endl;
                    cin>>opcion3;
                    switch(opcion3){
                        case '1':
                            color(4);
                            cout<<"TE PUSISTE A ESTUDIAR"<<endl;
                            color(6);
                            cout<<"Te regaño Claudia"<<endl;
                            cout<<"FINAL NEUTRO :! FIN"<<endl;
                            break;
                        case '2':
                            color(4);
                            cout<<"TE PUSISTE A JUGAR"<<endl;
                            cout<<"TE MORISTE, FINAL MALO :("<<endl;
                            break;
                        default:
                            cout<<"hazlo de nuevo por wey"<<endl;
                            main();
                            break;
                    }
                    break;

                case '2':
                    color(4);
                    cout<<"TE FUISTE CON LAS DE QFB"<<endl;

                    color(1);
                    cout<<"TE PUSISTE A COQUETEAR O A ESTUDIAR"<<endl;
                    color(9);
                    cout<<"[1] Coqueteaste [2] Estudiar"<<endl;
                    cin>>opcion3;
                    switch(opcion3){
                        case '1':
                            color(4);
                            cout<<"TE PUSISTE A COQUETEAR"<<endl;
                            color(10);
                            cout<<"Conseguiste novia"<<endl;
                            cout<<"FINAL BUENO FIN :)"<<endl;
                            break;
                        case '2':
                            color(4);
                            cout<<"TE PUSISTE A ESTUDIAR"<<endl;
                            color(8);
                            cout<<"TE SACO EL PROFE"<<endl;
                            cout<<"FINAL NEUTRO FIN :!"<<endl;
                            break;
                        default:
                            cout<<"hazlo de nuevo por wey"<<endl;
                            main();
                            break;
                    }
                    break;	

                default:
                    cout<<"hazlo de nuevo por wey"<<endl;
                    main();
                    break;
            }
            break;

        case '2':
            color(4);
            cout<<"FUISTE AL EJERCITO"<<endl;
            color(1);
            cout<<"Marchaste o te robaste un helicoptero?"<<endl;
            color(9);
            cout<<"[1] Marchar [2] Robar helicoptero"<<endl; color(15);
            cin>>opcion2;
            switch(opcion2){
                case '1':
                    color(4);
                    cout<<"MARCHASTE"<<endl;
                    color(1);
                    cout<<"LE ECHASTE GANAS?"<<endl;
                    color(9);
                    cout<<"[1] Si [2] No"<<endl;
                    cin>>opcion3;
                    switch(opcion3){
                        case '1':
                            color(4);
                            cout<<"MARCHASTE BIEN"<<endl;
                            color(4);
                            cout<<"Te mandaron a Irak"<<endl;
                            cout<<"FINAL MALO :( FIN"<<endl;
                            break;
                        case '2':
                            color(4);
                            cout<<"MARCHASTE MAL"<<endl;
                            cout<<"TE MORISTE, TE FUSILARON, FINAL MALO :("<<endl;
                            break;
                        default:
                            cout<<"hazlo de nuevo por wey"<<endl;
                            main();
                            break;
                    }
                    break;	

                case '2':
                    color(4);
                    cout<<"ROBASTE HELICOPTERO"<<endl;
                    color(1);
                    cout<<"A DONDE TE DIRIGISTE?"<<endl;
                    color(9);
                    cout<<"[1] Tu casa [2] La casa de Claudia"<<endl;
                    cin>>opcion3;
                    switch(opcion3){
                        case '1':
                            color(4);
                            cout<<"TE FUISTE A TU CASA"<<endl;
                            color(6);
                            cout<<"Te quitaron el helicoptero"<<endl;
                            cout<<"FINAL NEUTRO :! FIN"<<endl;
                            break;
                        case '2':
                            color(4);
                            cout<<"TE FUISTE A LA CASA DE CLAUDIA"<<endl;
                            color(6);
                            cout<<"Atropellaste a Claudia, FINAL NEUTRO :!"<<endl;
                            break;
                        default:
                            cout<<"hazlo de nuevo por wey"<<endl;
                            main();
                            break;
                    }
                    break;

                default:
                    cout<<"hazlo de nuevo por wey"<<endl;
                    main();
                    break;					
            }
            break;

        default:
            cout<<"hazlo de nuevo por wey"<<endl;
            main();
            break;
    }
}

