#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <fstream>

using namespace std;

int obtenerMatriz(const char* path, int (&distancias)[21][21]) {
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



int obtenerSolucionCorrida(const char* path, string(&solActual)[3][15]) {
    ifstream solParseada;
    solParseada.open(path, ios::in);

    if (!solParseada) {
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

        (solActual[fila - 1][columna - 1]) = empleado;


    }
    return 0;
}

void inicializarMatrizEnCeros(int (&matriz)[21][21]) {
    for (int i = 0; i < 21; i++) {

        for (int j = 0; j < 21; j++) {
            matriz[i][j] = 0;

        }
    }
}



//A partir del vector de recorrido de la combi ej: v = (A,B,C) obtengo la matriz de adyacencias

bool obtenerMatrizSolucion(string domicilios[15], int (&matriz)[21][21]) {

    char inicio, destino;

    inicializarMatrizEnCeros(matriz);

    for (int i = 0; i < 14; i++) {

        if (!domicilios[i].empty() && !domicilios[i + 1].empty()) {

            inicio = int(domicilios[i].at(0)) - 65;
            destino = int(domicilios[i + 1].at(0)) - 65;
            matriz[destino][inicio] = 1;

        }
        else {

            if (!domicilios[i].empty() && domicilios[i + 1].empty()) {
                inicio = int(domicilios[i].at(0)) - 65;
                matriz[20][inicio] = 1;
            }

            if (!domicilios[i + 1].empty() && domicilios[i + 2].empty()) {
                inicio = int(domicilios[i + 1].at(0)) - 65;
                matriz[20][inicio] = 1;
            }

        }

    }



}

bool multiplicarMatrices(int a[21][21], int b[21][21], int (&c)[21]) {

    for (int i = 0; i < 21; i++) {

        for (int j = 0; j < 21; j++) {

            c[i] += a[i][j] * b[j][i];

        }
    }



}

void imprimirMatriz(int matriz[21][21]) {
    for (int i = 0; i < 21; i++) {

        for (int j = 0; j < 21; j++) {
            cout << matriz[i][j] << " ";

        }
        cout << endl;
    }
}

void imprimirSolActual(string solActual[3][15]) {
    
    for (int i = 0; i < 3; i++) {
        cout << "Recorrido de la combi "<< i+1 << ": ";
        for (int j = 0; j < 15; j++) {
            cout << solActual[i][j] << " ";

        }
        cout << endl;
    }
}

int obtenerParametro(string A, string B, int matrix[21][21]) {

    int inicio = int(A.at(0)) - 65;
    int destino = int(B.at(0)) - 65;

    return matrix[inicio][destino];

}

void obtenerDistanciaYTiempoSolucion(int distancias[21][21], int tiempos[21][21], int sol[21][21], int &time, int &d) {

    // Calculo la distancia y los tiempos

    int dist[21] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int t[21] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    //cout << dist[0]<< endl;

    multiplicarMatrices(distancias, sol, dist);
    multiplicarMatrices(tiempos, sol, t);





    d = 0;

    for (int i = 0; i < 21; i++) {
        d += dist[i];
    }

    time = 0;

    for (int i = 0; i < 21; i++) {
        time += t[i];
    }


}





void intercambiosCruzados(string solActual[3][15], string solNueva[3][15], int distancias[21][21], int tiempos[21][21]) {
    cout<< "-Iniciando el proceso de intercambios entre combis "<<endl<<endl<<
            "Recorrido inicial:"<<endl<<endl;
    
    imprimirSolActual(solActual);
    
    cout<<endl<<endl;
    
    
    
    string aux;
    int time, dist, t0, d0;
    int matrizSolNueva[21][21], matrizSolActual[21][21];



    //Hago una copia de la solucion para trabajar sobre ella.
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 21; j++) {
            solNueva[i][j] = solActual[i][j];
        }
    }



    int distPart0, tiempoPart0, tiempoPart1, distPart1, distPart01,distPart10,tiempoPart01,tiempoPart10;



    for (int i = 0; i < 2; i++) {

        //Aplico para cada combi
        inicializarMatrizEnCeros(matrizSolActual);
        obtenerMatrizSolucion(solActual[i], matrizSolActual);
        obtenerDistanciaYTiempoSolucion(distancias, tiempos, matrizSolActual, t0, d0);




        for (int k = 0; k < 15; k++) {

            if (!solNueva[i][k].empty() && !solNueva[i][k + 1].empty()) {
                distPart0 = obtenerParametro(solNueva[i][k], solNueva[i][k + 1], distancias);
                tiempoPart0 = obtenerParametro(solNueva[i][k], solNueva[i][k + 1], tiempos);
                
                for (int j = i + 1; j < 3; j++) {
                    
                    for(int l = 0; l<15;l ++ ){
                        
                    
                        if (!solNueva[j][l].empty() && !solNueva[j][l + 1].empty()) {
                            
                            distPart1 = obtenerParametro(solNueva[j][l], solNueva[j][l + 1], distancias);
                            tiempoPart1 = obtenerParametro(solNueva[j][l], solNueva[j][l + 1], tiempos);
                            
                           //calculo la distancia entre el domicilio jl al ik
                            distPart10 = obtenerParametro(solNueva[j][l], solNueva[i][k + 1], distancias);
                            tiempoPart10 = obtenerParametro(solNueva[j][l], solNueva[i][k + 1], tiempos);
                            
                            //calculo la distancia de el domicilio ik al jl
                            distPart01 = obtenerParametro(solNueva[i][k], solNueva[j][l + 1], distancias);
                            tiempoPart01 = obtenerParametro(solNueva[i][k], solNueva[j][l + 1], tiempos);
                        
                            
                            if( tiempoPart01 <= tiempoPart0 && tiempoPart10 <= tiempoPart1 && distPart01 <= distPart0 && distPart10 <= distPart1){
                                swap(solNueva[i][k],solNueva[j][l]);
                                obtenerMatrizSolucion(solNueva[i], matrizSolNueva);
                                obtenerDistanciaYTiempoSolucion(distancias, tiempos, matrizSolNueva, time, dist);
                                if(time > t0 && dist > d0){
                                    swap(solNueva[i][k],solNueva[j][l]);
                                }
                                
                                
                            }
                            
                            
                        }
                        
                    }

                }


            }




        }


}
    cout<< "Recorridos resultantes: "<<endl<<endl;
    
    imprimirSolActual(solNueva);
    
    
    cout<<endl<<endl;
    
    
}




void swap(string &A,string &B){
    string aux = A;
    A = B;
    B= aux;
}








void kIntercambios(string solActual[3][15], string solNueva[3][15], int distancias[21][21], int tiempos[21][21]) {

    
    cout<< "-Iniciando el proceso de Intercambios por fuerza bruta"<<endl;
    cout<<endl<< "Recorrido original:"<<endl<<endl;
    imprimirSolActual(solActual);
    cout<< endl;

    
    
    
    
    string aux;
    int time, dist, t0, d0;
    int matrizSolNueva[21][21], matrizSolActual[21][21];



    //Hago una copia de la solucion para trabajar sobre ella.
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 21; j++) {
            solNueva[i][j] = solActual[i][j];
        }
    }



    for (int i = 0; i < 3; i++) {

        //Aplico para cada combi
        inicializarMatrizEnCeros(matrizSolActual);
        obtenerMatrizSolucion(solActual[i], matrizSolActual);
        obtenerDistanciaYTiempoSolucion(distancias, tiempos, matrizSolActual, t0, d0);


        cout << "inicial " << "combi " << i+1 << " tiempo " << t0 << " distancia " << d0 << endl;

        for (int j = 0; j < 14; j++) {

            for (int k = j + 1; k < 15; k++) {

                if (!solNueva[i][j].empty() && !solNueva[i][k].empty()) {
       
                    swap(solNueva[i][j],solNueva[i][k]);

                    inicializarMatrizEnCeros(matrizSolNueva);
                    obtenerMatrizSolucion(solNueva[i], matrizSolNueva);

                    obtenerDistanciaYTiempoSolucion(distancias, tiempos, matrizSolNueva, time, dist);

                    
                    if (time > t0 && dist > d0) {
                        swap(solNueva[i][j],solNueva[i][k]);
                      

                    } else {
                        t0 = time;
                        d0 = dist;
                    }

                }
            }

        }

        cout << "final " << "combi " << i+1 << "tiempo" << t0 << "distancia " << d0 << endl;
        cout<<endl;
    }
    
    cout<< "Recorrido final:"<<endl<<endl;
    
    imprimirSolActual(solNueva);
    cout<< endl;



};

bool agregarDomicilioAlRecorrido(string recorrido[15], string domicilio, int pos) {
    bool ingreso = false;
    
    if(pos > 15){
        return false;
    }

    if (recorrido[pos - 1].empty() && recorrido[pos - 2].empty()) {
        return false;
    }
    if (!recorrido[pos - 1].empty() || (!recorrido[pos - 2].empty() && recorrido[pos - 1].empty())) {
        for (int i = pos - 1; i < 14; i++) {
            if (!recorrido[i].empty() && recorrido[i + 1].empty() && !ingreso) {
                recorrido[i + 1] = domicilio;
                ingreso = true;
                swap(recorrido[i+1],recorrido[pos-1]);
            }
        }
    }

    return ingreso;

}



int obtenerCantidadDePasajeros(string combi[15]){
    int cont = 0;
    for(int i = 0; i<15 ; i++){
        if(!combi[i].empty()){
            cont++;
        }
    }
    return cont;
}




//en principio comprueba muy por arriba si puedo agregar un domicilio mas
bool puedoAgregarUnoMas(string A[15],int tiempos[21][21],int distancias [21][21]){
    
    int t,d ,matriz[21][21];
    
    if(obtenerCantidadDePasajeros(A) >= 15){
        return false;
    }
    
    obtenerMatrizSolucion(A,matriz);
    
    obtenerDistanciaYTiempoSolucion(distancias,tiempos,matriz,t,d);
    
    if(t < 120){
        return true;
    }
    
    return false;
    
}






int main(int argc, char** argv) {


    //Subida de datos.

    int distancias[21][21];
    int tiempos[21][21];

    obtenerMatriz("data/distancias.csv", distancias);
    obtenerMatriz("data/tiempos.csv", tiempos);


    string solActual[3][15];

    // De la forma solActual = {A,H,B,C}
    obtenerSolucionCorrida("data/solucion/solparseada.txt", solActual);



    //K intercambios

    string solNueva[3][15];
    
    
    kIntercambios(solActual, solNueva, distancias, tiempos);

    intercambiosCruzados(solNueva, solNueva, distancias, tiempos);

    string solDosCombis[3][15];
    
    
    
    int matrizSolNueva[21][21];
    inicializarMatrizEnCeros(matrizSolNueva);
    
    
    
    
    cout<< "-Iniciando proceso de reduccion de combis." << endl<<endl;
    
    //TRATO DE ELIMINAR UNA COMBI
    
    int min, cantidades[3];
    int nomin1,nomin2;
    
    for(int i= 0; i<3; i++){
        cantidades[i] = obtenerCantidadDePasajeros(solNueva[i]);
    }
    
    if(cantidades[0] <= cantidades[1] && cantidades[0] <= cantidades[2]){
        min = 0;
        nomin1=1;
        nomin2=2;
    }
    else{
        if(cantidades[1] <= cantidades[0] && cantidades[1] <= cantidades[2]){
            min = 1;
            nomin1=0;
            nomin2=2;
        }
        else{
            min=2;
            nomin1=1;
            nomin2=0;
        }
    }
    
    
    
    
    //Hago una copia de la solucion para trabajar sobre ella.
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 15; j++) {
            if(i != min ){
                solDosCombis[i][j] = solNueva[i][j];
            }
            else{
                solDosCombis[i][j]= "";
            }
        }
    }
    

    bool pudePasarEmpleados = true;
    
    
    
   
    
    for(int i = 0; i<15; i++){
        if(! solActual[1][i].empty()){
            if(puedoAgregarUnoMas(solDosCombis[nomin1],distancias,tiempos)){
                agregarDomicilioAlRecorrido(solDosCombis[nomin1],solActual[1][i],1);
                
                int t,d ,matriz[21][21];
  
                obtenerMatrizSolucion(solDosCombis[nomin1],matriz);
    
                obtenerDistanciaYTiempoSolucion(distancias,tiempos,matriz,t,d);
                
                if(t > 120){
                    if(pudePasarEmpleados){
                        cout << "No es posible utilizar menos de 3 combis."<<endl;
                        pudePasarEmpleados =false;
                    }
                }
                
            }
            else{
                if(puedoAgregarUnoMas(solDosCombis[nomin2],distancias,tiempos)){
                    
                    agregarDomicilioAlRecorrido(solDosCombis[nomin2],solActual[1][i],1);
            
                     int t,d ,matriz[21][21];
  
                    obtenerMatrizSolucion(solDosCombis[nomin1],matriz);
    
                    obtenerDistanciaYTiempoSolucion(distancias,tiempos,matriz,t,d);
                    
                    if(t > 120){
                    if(pudePasarEmpleados){
                        cout << "No es posible utilizar menos de 3 combis."<<endl;
                        pudePasarEmpleados =false;
                    }
                }
                    
                    
                }
                else{
                    if(pudePasarEmpleados){
                        cout << "No es posible utilizar menos de 3 combis."<<endl;
                        pudePasarEmpleados =false;
                    }
                }
            }
            
        }
    }
    
    if(pudePasarEmpleados){
        kIntercambios(solDosCombis, solDosCombis, distancias, tiempos);
        cout<<endl<<"----------------------------------------"<<endl<<endl;
    
        cout << "Solucion definitiva: "<< endl<<endl;  
   
        imprimirSolActual(solDosCombis);
    }
    else{
        cout<<endl<<"----------------------------------------"<<endl<<endl;
    
        cout << "Solucion definitiva: "<< endl<<endl;  
   
        imprimirSolActual(solNueva);
    }

    return 0;
}

