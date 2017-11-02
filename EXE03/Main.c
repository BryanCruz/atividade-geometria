//Bryan Bialokur da Cruz, RA: 11052316
//Melissa Gabriela Pereira da Soledade Perrone, RA: 11072216

#include "geometria.h"
#include <stdio.h>
#include <math.h>

#ifndef GEOMETRIA
#define GEOMETRIA

struct s_ponto{
  double x;
  double y;
};
typedef struct s_ponto ponto;
typedef struct s_ponto vetor;

struct s_segmento{
   ponto p1, p2;
 };
typedef struct s_segmento segmento;

struct s_triangulo{
   ponto p1, p2, p3;
};
typedef struct s_triangulo triangulo;

//  Calcula o produto interno <u,v>
double produto_interno(vetor p, vetor q) {
	return p.x*q.x + p.y*q.y;
}

//  Calcula o vetor p - q
vetor subtrai(vetor p, vetor q){
	vetor temp;
	temp.x = p.x - q.x;
	temp.y = p.y - q.y;

	return temp;
}

/*  Calcula o vetor resultante da rotacao do vetor v
de um angulo de 90 graus (no sentido anti-horario). */
vetor roda90(vetor p){
	double aux = p.y;
	p.y = p.x;
	p.x = -p.y;

	return p;
}

// Calcula distancia
 double distancia (ponto p, ponto q){
  int dist = sqrt(pot((q.y - p.y), 2)+pot((q.x - p.x), 2));
  return dist;
}

// Calcula o módulo do vetor
double modulo(vetor u){
  vetor nulo = {0, 0};
	return distancia(u, nulo);
}

/*  Retorna 1 se o coseno do ^angulo entre os vetores u e v  ́e positivo
retorna -1 se for negativo e 0 se for nulo. */
int sinal_do_coseno(vetor u, vetor v){
	int pi = produto_interno(u, v);
	if(pi > 0){
		return 1;
	}else if(pi == 0){
		return 0;
	}else{
		return -1;
	}
}

/*  Retorna 1 se p, q e r est~ao em sentido hor ́ario e -1 se for
anti-hor ́ario. Se os pontos forem colineares devolva 0. */
int sentido(ponto p, ponto q, ponto r){

}


//  Retorna 1 se os segmentos se cruzam e 0 caso contr ́ario.
int cruza(segmento s, segmento t){

}






/*  Retorna 1 se o ponto p est ́a no interior do tri^angulo t.
Devolve 0 caso contr ́ario. */
int dentro(ponto p, triangulo t){

}




//  Opcional:
/*  Devolve a cordenada do ponto em que s e t se intersecta
caso eles se intersectam ou qualquer ponto caso eles n~ao
se intersectam. */
ponto cruzamento(segmanto s, segmento t);


/*  Calcula o ponto que  ́e a proje ̧c~ao de p no segmento s. */
ponto projeta(ponto p, segmento s);


/*  Devolve 1 se os tri^angulos a e b se intersectam
e devolve 0 caso contr ́ario. */
int intersecta(triangulo a, triangulo b);

#endif
