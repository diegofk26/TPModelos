/*Problema del viajante*/

/*Conjuntos*/

# ¿Z es nuestra empresa, el origen?

set DOMICILIOS;
set COMBIS;

/*Parametros*/

# Distancia de j a k, con j distinto de k
param DISTANCIA{j in DOMICILIOS, k in DOMICILIOS : j<>k};

# Tiempo de j a k, con j distinto de k
param TIEMPO{j in DOMICILIOS, k in DOMICILIOS : j<>k};

/*Variables*/

# Cantidad de combis a utilizar (combis)
var C >= 0, integer;

# Yijk binaria. 1 si combi i va desde j hasta k, con j distinto de k
var Y{i in COMBIS, j in DOMICILIOS, k in DOMICILIOS: j<>k} >= 0, binary;

# Orden en que es recogido el empleado w por la combi i. Excluyo el origen. 
var U{i in COMBIS, w in DOMICILIOS: w<>'Z'} >=0, integer;

# Cantidad de pasajeros que viajan en la combi i
var N{i in COMBIS} >= 0, integer;

# Eij binaria. 1 si el empleado j toma la combi i
var E{i in COMBIS, j in DOMICILIOS: j<> 'Z'} >= 0, binary;

# Nij entera. Ni si Yijk = 1, 0 sino.
var M{i in COMBIS, j in DOMICILIOS, k in DOMICILIOS} >= 0, integer;

# Tiempo que tarda la combi i en realizar el recorrido (minutos)
var T{i in COMBIS} >= 0;


#Binaria que dice si uso una combi o no
var COMB{i in COMBIS} >= 0, binary;






/*Funcional*/


minimize z: 100 * C + sum{i in COMBIS, j in DOMICILIOS, k in DOMICILIOS : j<>k} DISTANCIA[j,k]*Y[i,j,k] ;






/*Restricciones*/


/*Nuevas*/


#total de combis
s.t. totalCombis: C = sum{i in COMBIS} COMB[i];


#COMB vale 1 si se usa la combi o 0 si no 
s.t. seUsaLaCombi{i in COMBIS}: COMB[i] <= sum{j in DOMICILIOS: j <>'Z'} E[i,j];
s.t. seUsaLaCombii{i in COMBIS}: sum{j in DOMICILIOS: j <>'Z'} E[i,j] <= 15 * COMB[i];



s.t. unPasajeroVaEnUnaSolaCombi{j in DOMICILIOS: j <>'Z'}: sum{i in COMBIS} E[i,j] = 1;


s.t. restriccionDeSalidaDeLasCombis{i in COMBIS}: sum{k in DOMICILIOS: k <>'Z'} Y[i,'Z',k] <= COMB[i];

s.t. restriccionDeLlegadaDeLasCombis{i in COMBIS}: sum{j in DOMICILIOS: j <>'Z'} Y[i,j,'Z'] <= COMB[i];



#Relacion entre Eij y las Yijk
s.t. viajaEnEsaCombi1{i in COMBIS, j in DOMICILIOS: j <>'Z'}: E[i,j] = sum{k in DOMICILIOS: k<>j} Y[i,j,k];














# Cantidad de combis
s.t. cantidadCombis: C <= 3;

# Salgo de todos los domicilios una sola vez. Excluyo el origen.
s.t. salen{j in DOMICILIOS : j<>'Z'}: sum{i in COMBIS, k in DOMICILIOS: j<>k } Y[i,j,k] = 1;



# Llego a todos los domicilios una sola vez. Excluyo el origen.
s.t. llegan{k in DOMICILIOS : k<>'Z'}: sum{i in COMBIS, j in DOMICILIOS : j<>k } Y[i,j,k] = 1;







# Del origen salgo a C domicilios
s.t. aDomicilios: sum{i in COMBIS, k in DOMICILIOS : k<>'Z'} Y[i,'Z',k] = C;

# Con cada combi salgo del origen hasta una vez
s.t. salenOrigen{i in COMBIS}: sum{k in DOMICILIOS : k<>'Z'} Y[i,'Z',k] <= 1; #COMB[i];

# Al origen llego C veces
s.t. desdeDomicilios: sum{i in COMBIS, j in DOMICILIOS : j<>'Z'} Y[i,j,'Z'] = C;

# Con cada combi llego al origen hasta una vez
s.t. lleganOrigen{i in COMBIS}: sum{j in DOMICILIOS : j<>'Z'} Y[i,j,'Z'] <= 1; #COMB[i];









# Relación entre la cantidad de pasajeros y la bivalente E
s.t. relacionPasajeros{i in COMBIS}: sum{j in DOMICILIOS : j<>'Z'} E[i,j] = N[i];



# Cantidad máxima de pasajeros por combi i
s.t. pasajeros{i in COMBIS}: N[i] <= 15;




# Definición de Nijk
# Si Yijk = 0 entonces Nijk = 0 
s.t. defNijk1{i in COMBIS, j in DOMICILIOS, k in DOMICILIOS: j<>k}: M[i,j,k] <= 15 * Y[i,j,k];


# Yijk = 1 entonces Nijk = Ni 
s.t. defNijk2{i in COMBIS, j in DOMICILIOS, k in DOMICILIOS: j<>k}: N[i] - 15*(1-Y[i,j,k]) <= M[i,j,k];
s.t. defNijk3{i in COMBIS, j in DOMICILIOS, k in DOMICILIOS: j<>k}: M[i,j,k] <= N[i];



# Elimino subtours
s.t. eliminoSubTours{i in COMBIS, j in DOMICILIOS, k in DOMICILIOS: j<>k and j<>'Z' and k<>'Z'}: U[i,j] - U[i,k] +M[i,j,k] <= N[i] - 1 + 15 * (1-E[i,j]) + 15 * (1-E[i,k]);


# Rango de Uij. Si pertenece va de 1 a Ni si no es 0
s.t. rango1{i in COMBIS, j in DOMICILIOS: j<>'Z'}: 1 - (1-E[i,j]) <= U[i,j];
s.t. rango2{i in COMBIS, j in DOMICILIOS: j<>'Z'}: U[i,j] <= N[i];
s.t. rango3{i in COMBIS, j in DOMICILIOS: j<>'Z'}: U[i,j] <= 15 * E[i,j];


# Si j y k no pertenecen a la combi Yijk es igual a 0
s.t. jykNoPertenecenAlaMismaCombi{i in COMBIS, j in DOMICILIOS, k in DOMICILIOS: j<>k and j<>'Z' and k <>'Z'}: Y[i,j,k] <= ( E[i,j] + E[i,k] ) / 2;


# Cálculo del tiempo
s.t. calculoTiempo{i in COMBIS}: sum{j in DOMICILIOS, k in DOMICILIOS : j<>k and j<>'Z'} TIEMPO[j,k]*Y[i,j,k] = T[i];


# El tiempo no puede exceder las dos horas
s.t. tiempo{i in COMBIS}: T[i] <= 120;






solve;





/*Data segment*/

data;

set DOMICILIOS := A B C D E Z;
set COMBIS := 1 2 3;

param DISTANCIA : 
	A	B	C	D	E	Z :=
A	.	3	3	5	6	11
B	3	.	2	4	5	10
C	3	2	.	2	3	8
D	5	4	2	.	1	8
E	6	5	3	1	.	9
Z	11	10	8	8	9	. ;

param TIEMPO :
	A	B	C	D	E	Z :=
A	.	18	18	30	36	66
B	18	.	12	24	30	60
C	18	12	.	12	18	48
D	30	24	12	.	6	48
E	36	30	18	6	.	54
Z	66	60	48	48	54	. ;

end;