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