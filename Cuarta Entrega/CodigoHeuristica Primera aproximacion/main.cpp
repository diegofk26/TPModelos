#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace std;


int obtenerMatriz(const char* path, int (&distancias)[21][21]){
    ifstream file;
    file.open(path, ios::in);

    
    //primero leo los nombres de los domicilios
    string casaDos[21];

    for (int i = 0; i <= 20; i++) {
        file >> casaDos[i];

    }

    string casaUno;
    int dato;
    string dist;


    for (int i = 0; i < 21; i++) {

        //leo el domicilio de salida
        file >> casaUno;

        for (int j = 0; j < 21; j++) {

            // AGREGAR LA DISTANCIA COMO UNA ARISTA
            file >> dist;

            dato = atoi(dist.c_str());

            (distancias[i][j]) = dato;
        }

    }
    
}



int obtenerSolucionCorrida(const char* path,string (&solActual)[3][15],int cantidades[3]){
    ifstream solParseada;
    solParseada.open(path, ios::in);
    
    if(!solParseada){
        cout << "error no se pudo abrir el archivo que contiene la solucion anterior";
        return 1;
    }
    string sol;

    string a, empleado;
    int fila, columna;

    int cantEmpleados = 20;

    for (int i = 0; i < cantEmpleados; i++) {

        solParseada >> sol;
       
                
        solParseada >> sol;
 
                
        a = sol.substr(2, 1);
        fila = atoi(a.c_str());

        empleado = sol.substr(4, 1);

        solParseada >> sol;
        
        
        solParseada >> sol;
        
        columna = atoi(sol.c_str());
        solParseada >> sol;
      
        (solActual[fila-1][columna-1])= empleado;
     
        
    }
    return 0;
}



void inicializarMatrizEnCeros(int (&matriz)[21][21]){
    for(int i = 0; i < 21 ; i++){
        
        for(int j = 0 ; j< 21; j++){
            matriz[i][j] = 0;
            
        }
    }
}



//A partir del vector de recorrido de la combi ej: v = (A,B,C) obtengo la matriz de adyacencias
bool obtenerMatrizSolucion(string domicilios[15],int (&matriz)[21][21]){
    
    char inicio, destino;
    
    inicializarMatrizEnCeros(matriz);
    
    for ( int i = 0; i < 14; i++){
        
        if(! domicilios[i].empty() && !domicilios[i+1].empty()){
            
            inicio = int(domicilios[i].at(0)) - 65;
            destino = int(domicilios[i+1].at(0)) - 65;
            matriz[destino][inicio] = 1;
            
        }
        
        else{
            
            if(! domicilios[i].empty() && domicilios[i+1].empty()){
                inicio = int(domicilios[i].at(0)) - 65;
                matriz[20][inicio] = 1;
            }
            
            if(! domicilios[i+1].empty() && domicilios[i+2].empty()){
                inicio = int(domicilios[i+1].at(0)) - 65;
                matriz[20][inicio] = 1;
            }
            
        }
        
    }
    
    
    
}



bool multiplicarMatrices(int a[21][21],int b[21][21],int (&c)[21]){
    
    for( int i = 0; i < 21 ; i++){
        
        for(int j = 0 ; j < 21 ; j++){
            
            c[i] += a[i][j] * b[j][i];
            
        }
    }
    
    
    
}



void imprimirMatriz(int matriz[21][21]){
    for(int i = 0; i < 21 ; i++){
        
        for(int j = 0 ; j< 21; j++){
            cout << matriz[i][j]<< " ";
            
        }
        cout << endl;
    }
}



void imprimirSolActual(string solActual[3][15]){
        for(int i = 0; i < 3 ; i++){
        
        for(int j = 0 ; j< 15; j++){
            cout << solActual[i][j]<< " ";
            
        }
        cout << endl;
    }
}



int obtenerParametro(string A,string B,int matrix[21][21]){
    
    int inicio = int(A.at(0)) - 65;
    int destino = int(B.at(0)) - 65;
    
    return matrix[inicio][destino];
    
}


void obtenerDistanciaYTiempoSolucion(int distancias[21][21], int tiempos[21][21],int sol[21][21],int &time,int &d){
    
    // Calculo la distancia y los tiempos
    
    int dist[21]= {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int t[21] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    //cout << dist[0]<< endl;
    
    multiplicarMatrices(distancias,sol,dist);
    multiplicarMatrices(tiempos,sol,t);
    
    
    
    
    
    d=0;
    
    for(int i=0 ; i<21 ; i++){
        d += dist[i];
    }
    
    time=0;
    
    for(int i=0 ; i<21 ; i++){
        time += t[i];
    }
    

}



void kIntercambios(string solActual[3][15],string solNueva[3][15],int distancias[21][21],int tiempos[21][21]){
    
    string aux;
    int time,dist,t0,d0;
    int matrizSolNueva[21][21],matrizSolActual[21][21];
    
    
    
    //Hago una copia de la solucion para trabajar sobre ella.
    for (int i = 0; i< 3 ; i++){
        for (int j = 0; j<21 ; j++){
            solNueva[i][j] = solActual[i][j];
        }
    }
            
    
    
    for(int i = 0; i< 3 ; i++ ){
        
        //Aplico para cada combi
        inicializarMatrizEnCeros(matrizSolActual);
        obtenerMatrizSolucion(solActual[i],matrizSolActual);
        obtenerDistanciaYTiempoSolucion(distancias,tiempos,matrizSolActual,t0,d0);
        
        if(i==0){
           // imprimirMatriz(matrizSolActual);
        }
        
        cout << "inicial " << "combi "<< i << "tiempo" << t0 <<"distancia "<< d0<< endl;
        
        for(int j = 0; j <14; j++){
            
            for( int k = j + 1 ; k < 15; k++ ){
                
                if (!solNueva[i][j].empty() && !solNueva[i][k].empty()){
                    aux = solNueva[i][j];
                    solNueva[i][j]=solNueva[i][k];
                    solNueva[i][k]= aux;
                   
                    
                    inicializarMatrizEnCeros(matrizSolNueva);
                    obtenerMatrizSolucion(solNueva[i],matrizSolNueva);
                    
                    obtenerDistanciaYTiempoSolucion(distancias,tiempos,matrizSolNueva,time,dist);
                    
                    //cout<< "combi numero "<< i<< endl;
                    //cout << "cambiando los siguientes ordenes: "<< aux <<  solNueva[i][j] << 
                    //      "se obtienen tiempo: "<< time << " distancia "<< dist <<endl;
                    if (time > t0 && dist > d0){
                        
                        solNueva[i][k]= solNueva[i][j];
                        solNueva[i][j] = aux;
                        
                    }
                    else{
                        t0 = time;
                        d0 = dist;
                        cout << "tiempo"<< t0 << "distancia"<<d0<<endl;
                    }
                    
                }
            }
            
        }
        
        cout << "final " << "combi "<< i << "tiempo" << t0 <<"distancia "<< d0<<endl;
    }
    imprimirSolActual(solNueva);
    
    
    
};






/*
 * 
 */
int main(int argc, char** argv) {

    
    //Subida de datos.
    
    int distancias[21][21];
    int tiempos[21][21];
    
    obtenerMatriz("data/distancias.csv",distancias);
    obtenerMatriz("data/tiempos.csv",tiempos);
    
    
    string solActual[3][15];
    int cantidades[3];
    
    // De la forma solActual = {A,H,B,C}
    obtenerSolucionCorrida("data/solucion/solparseada.txt",solActual,cantidades);
       
    
    
    //K intercambios
    
    string solNueva[3][15];
    kIntercambios(solActual,solNueva,distancias, tiempos );
    
    
    


return 0;
}

