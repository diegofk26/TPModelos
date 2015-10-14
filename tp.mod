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
var E{i in COMBIS, j in DOMICILIOS} >= 0, binary;

# Nij entera. Ni si Yijk = 1, 0 sino.
var M{i in COMBIS, j in DOMICILIOS, k in DOMICILIOS} >= 0, integer;

# Tiempo que tarda la combi i en realizar el recorrido (minutos)
var T{i in COMBIS} >= 0;

/*Funcional*/

# Falta completarlo con los $KM y $COMBIS
minimize z: sum{i in COMBIS, j in DOMICILIOS, k in DOMICILIOS : j<>k} DISTANCIA[j,k]*Y[i,j,k];

/*Restricciones*/

# Cantidad de combis
s.t. cantidadCombis: C <= 3;

# Salgo de todos los domicilios una sola vez. Excluyo el origen.
s.t. salen{j in DOMICILIOS : j<>'Z'}: sum{i in COMBIS, k in DOMICILIOS: j<>k} Y[i,j,k] = 1;

# Llego a todos los domicilios una sola vez. Excluyo el origen.
s.t. llegan{k in DOMICILIOS : k<>'Z'}: sum{i in COMBIS, j in DOMICILIOS : j<>k } Y[i,j,k] = 1;

# Del origen salgo a C domicilios
s.t. aDomicilios: sum{i in COMBIS, k in DOMICILIOS : k<>'Z'} Y[i,'Z',k] = C;

# Con cada combi salgo del origen hasta una vez
s.t. salenOrigen{i in COMBIS}: sum{k in DOMICILIOS : k<>'Z'} Y[i,'Z',k] <= 1;

# Al origen llego C veces
s.t. desdeDomicilios: sum{i in COMBIS, j in DOMICILIOS : j<>'Z'} Y[i,j,'Z'] = C;

# Con cada combi llego al origen hasta una vez
s.t. lleganOrigen{i in COMBIS}: sum{j in DOMICILIOS : j<>'Z'} Y[i,j,'Z'] <= 1;

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
s.t. calculoTiempo{i in COMBIS}: sum{j in DOMICILIOS, k in DOMICILIOS : j<>k} TIEMPO[j,k]*Y[i,j,k] = T[i];

# El tiempo no puede exceder las dos horas
s.t. tiempo{i in COMBIS}: T[i] <= 120;

solve;

/*Data segment*/

data;

set DOMICILIOS := A B C D E F G H I J K L M N O P Q R S T Z;
set COMBIS := 1 2 3;

param DISTANCIA : 
	A	B	C	D	E	F	G	H	I	J	K	L	M	N	O	P	Q	R	S	T	Z :=
A	.	3	3	5	6	7	8	5	5	7	7	9	11	8	13	10	8	9	11	11	11
B	3	.	2	4	5	6	7	2	4	4	6	8	10	7	12	7	7	8	10	10	10
C	3	2	.	2	3	4	5	4	2	6	4	6	8	5	10	9	7	6	8	8	8
D	5	4	2	.	1	2	3	6	4	8	4	4	6	7	8	11	9	8	6	8	8
E	6	5	3	1	.	1	2	7	5	9	5	3	5	8	7	12	10	9	7	9	9
F	7	6	4	2	1	.	1	6	4	8	4	2	4	7	6	11	9	8	6	8	8
G	8	7	5	3	2	1	.	7	5	9	5	3	3	8	5	12	10	9	7	9	9
H	5	2	4	6	7	6	7	.	2	2	4	6	8	5	10	5	5	6	8	8	8
I	5	4	2	4	5	4	5	2	.	4	2	4	6	3	8	7	5	4	6	6	6
J	7	4	6	8	9	8	9	2	4	.	4	6	8	5	10	3	5	6	8	8	8
K	7	6	4	4	5	4	5	4	2	4	.	2	4	3	6	7	5	4	4	4	4
L	9	8	6	4	3	2	3	6	4	6	2	.	2	5	4	9	7	6	4	6	6
M	11	10	8	6	5	4	3	8	6	8	4	2	.	5	2	9	7	6	4	6	6
N	8	7	5	7	8	7	8	5	3	5	3	5	5	.	5	4	2	1	3	3	3
O	13	12	10	8	7	6	5	10	8	10	6	4	2	5	.	9	7	6	4	6	6
P	10	7	9	11	12	11	12	5	7	3	7	9	9	4	9	.	2	3	5	5	5
Q	8	7	7	9	10	9	10	5	5	5	5	7	7	2	7	2	.	1	3	3	3
R	9	8	6	8	9	8	9	6	4	6	4	6	6	1	6	3	1	.	2	2	2
S	11	10	8	6	7	6	7	8	6	8	4	4	4	3	4	5	3	2	.	2	2
T	11	10	8	8	9	8	9	8	6	8	4	6	6	3	6	5	3	2	2	.	0
Z	11	10	8	8	9	8	9	8	6	8	4	6	6	3	6	5	3	2	2	0	. ;

param TIEMPO :
	A	B	C	D	E	F	G	H	I	J	K	L	M	N	O	P	Q	R	S	T	Z :=
A	.	18	18	30	36	42	48	30	30	42	42	54	66	48	78	60	48	54	66	66	66
B	18	.	12	24	30	36	42	12	24	24	36	48	60	42	72	42	42	48	60	60	60
C	18	12	.	12	18	24	30	24	12	36	24	36	48	30	60	54	42	36	48	48	48
D	30	24	12	.	6	12	18	36	24	48	24	24	36	42	48	66	54	48	36	48	48
E	36	30	18	6	.	6	12	42	30	54	30	18	30	48	42	72	60	54	42	54	54
F	42	36	24	12	6	.	6	36	24	48	24	12	24	42	36	66	54	48	36	48	48
G	48	42	30	18	12	6	.	42	30	54	30	18	18	48	30	72	60	54	42	54	54
H	30	12	24	36	42	36	42	.	12	12	24	36	48	30	60	30	30	36	48	48	48
I	30	24	12	24	30	24	30	12	.	24	12	24	36	18	48	42	30	24	36	36	36
J	42	24	36	48	54	48	54	12	24	.	24	36	48	30	60	18	30	36	48	48	48
K	42	36	24	24	30	24	30	24	12	24	.	12	24	18	36	42	30	24	24	24	24
L	54	48	36	24	18	12	18	36	24	36	12	.	12	30	24	54	42	36	24	36	36
M	66	60	48	36	30	24	18	48	36	48	24	12	.	30	12	54	42	36	24	36	36
N	48	42	30	42	48	42	48	30	18	30	18	30	30	.	30	24	12	6	18	18	18
O	78	72	60	48	42	36	30	60	48	60	36	24	12	30	.	54	42	36	24	36	36
P	60	42	54	66	72	66	72	30	42	18	42	54	54	24	54	.	12	18	30	30	30
Q	48	42	42	54	60	54	60	30	30	30	30	42	42	12	42	12	.	6	18	18	18
R	54	48	36	48	54	48	54	36	24	36	24	36	36	6	36	18	6	.	12	12	12
S	66	60	48	36	42	36	42	48	36	48	24	24	24	18	24	30	18	12	.	12	12
T	66	60	48	48	54	48	54	48	36	48	24	36	36	18	36	30	18	12	12	.	0
Z	66	60	48	48	54	48	54	48	36	48	24	36	36	18	36	30	18	12	12	0	. ;

end;
