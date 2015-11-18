/* Resolucion 6.2 */

/* Declaracion de variables */
var Y1 >= 0;
var Y2 >= 0;
var Y3 >= 0;

/* Definicion del funcional */

/* B1 = 8*/

minimize z: 30 * Y1 - 2 * Y2 + 20 * Y3 ;

/* Restricciones */

s.t. a: Y1 + 4 * Y3 >= 4;
s.t. b: 2 * Y1 - Y2 + 2 * Y3 >= 3;
s.t. c: Y1 + 2 * Y3 >= 2;

end;
