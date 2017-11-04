//Bryan Bialokur da Cruz, RA: 11052316
//Melissa Gabriela Pereira da Soledade Perrone, RA: 11072216

#include "geometria.h"
#include <stdio.h>
#include <math.h>

//#ifndef GEOMETRIA
//#define GEOMETRIA

/*struct s_ponto{
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
*/
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
	p.x = -aux;

	return p;
}

// Calcula distancia
 double distancia (ponto p, ponto q){
  vetor qp = subtrai(p, q);
  double dist = sqrt(pow(qp.x, 2) + pow(qp.y, 2));
  return dist;
}

/*  Retorna 1 se o coseno do ^angulo entre os vetores u e v  ́e positivo
retorna -1 se for negativo e 0 se for nulo. */
int sinal_do_coseno(vetor u, vetor v){
  double pi = produto_interno(u, v);
  if(pi > 0){
    return 1;
  }else if(pi < 0){
    return -1;
  }else{
    return 0;
  }
}

/*sinal de u X v, retorna 1 se for maior que 0,
-1 se for menor que zero e 0 se u e v são paralelos*/
int sinal_produto_vetorial(vetor u, vetor v){
  double valor = u.x*v.y - v.x*u.y;

  if(valor > 0){
    return -1;
  }else if(valor == 0){
    return 0;
  }else{
    return 1;
  }
}

/*  Retorna 1 se p, q e r est~ao em sentido hor ́ario e -1 se for
anti-hor ́ario. Se os pontos forem colineares devolva 0. */
int sentido(ponto p, ponto q, ponto r){
  vetor vetorPQ = subtrai(q, p);
  vetor vetorPR = subtrai(r, p);

  return sinal_produto_vetorial(vetorPQ, vetorPR);
}


//  Retorna 1 se os segmentos se cruzam e 0 caso contr ́ario.
int cruza(segmento s, segmento t){

	int sent1 = sentido(s.p, t.p, t.q);
 int sent2 = sentido(s.q, t.p, t.q);

 int sent3 = sentido(t.p, s.p, s.q);
 int sent4 = sentido(t.q, s.p, s.q);

 int cr = 0;
 if(sent1 != 0 && sent2 != 0){
	 if(sent1 != sent2 && sent3 != sent4){
		 cr = 1;
	 }
 }else{
	 double xminT, xmaxT;
	 if(t.p.x < t.q.x){
		 xminT = t.p.x;
		 xmaxT = t.q.x;
	 }else{
		 xminT = t.q.x;
		 xmaxT = t.p.x;
	 }

	 double yminT, ymaxT;
	 if(t.p.y < t.q.y){
		 yminT = t.p.y;
		 ymaxT = t.q.y;
	 }else{
		 yminT = t.q.y;
		 ymaxT = t.p.y;
	 }

	 if(sent1 == sent2){ // as 2 retas são colineares
		 if((xminT <= s.p.x && s.p.x <= xmaxT) || (xminT <= s.q.x && s.q.x <= xmaxT)){
			 cr = 1;
		 }
	 }else{
		 ponto col; //ponto colinear de s no segmento t

		 if(sent1 == 0){
			 col = s.p;
		 }else{
			 col = s.q;
		 }

		 if(xminT <= col.x && col.x <= xmaxT && yminT <= col.y && col.y <= ymaxT){
			 cr = 1;
		 }
	 }
 }



 return cr;

}

/*  Retorna 1 se o ponto p est ́a no interior do tri^angulo t.
Devolve 0 caso contr ́ario. */
int dentro(ponto p, triangulo t){
  int sent = 0;
  if(sentido(p, t.p, t.q) == sentido(p, t.q, t.r)){
    if(sentido(p, t.q, t.r) == sentido(p, t.r, t.p)){
      sent = 1;
    }
  }

  return sent;
}

//  Opcional:
/*  Devolve a cordenada do ponto em que s e t se intersecta
caso eles se intersectam ou qualquer ponto caso eles n~ao
se intersectam. */

ponto cruzamento(segmento s, segmento t){
  ponto p;
  //r_s = s.p + (s.q - s.p) * n = a + b*n
  //r_t = t.p + (t.q - t.p) * n = c + d*n

	if(cruza){
	  ponto a = s.p;
	  vetor b = subtrai(s.q, s.p);

	  ponto c = t.p;
	  vetor d = subtrai(t.q, t.p);

	  double n = 0;
	  if(b.x != d.x){
	    n = (c.x - a.x) / (b.x - d.x);
	  }else if(b.y != d.y){
			n = (c.y - a.y) / (b.y - d.y);
		}

	  p.x = a.x + b.x*n;
	  p.y = a.y + b.y*n;
	}
  return p;

  //encontra os parâmetros das retas; substitui os parâmetros na eq. paramétrica da reta; acha intersecção.
  /*ponto a = {0, 0};
  if(cruza(s, t) == 1){
    double determinante, parS, parT, x, y;
    determinante = ((t.q.x - t.p.x)*(s.q.y - s.p.y) - (t.q.y - t.p.y)*(s.q.x - s.p.x));

    //parâmetros de S e T
    parS = ( (t.q.x - t.p.x)*(t.p.y - s.p.y) - (t.q.y - t.p.y)*(t.p.x - s.p.x) )/determinante;
    parT = ( (s.q.x - s.p.x)*(t.p.y - s.p.y) - (s.q.y - s.p.y)*(t.p.x - s.p.x) )/determinante;

    //Substituindo S ou T e encontrando o ponto:
    a.x = (s.p.x) + (s.q.x - s.p.x)*parS;
    a.y = (s.p.y) + (s.q.y - s.p.y)*parS;
  }

  return a;
  */
}


/*  Calcula o ponto que  ́e a proje ̧c~ao de p no segmento s. */
ponto projeta(ponto p, segmento s){
  //troca de coordenadas
  vetor v_s = subtrai(s.q, s.p);

  //correcao da troca de coordenadas
  p.x = p.x - s.p.x;
  p.y = p.y - s.p.y;

  double alpha = 0;
  //calculo da projecao (proj = alpha*v_s)
  if(produto_interno(v_s, v_s) != 0){
    alpha = produto_interno(p, v_s)/produto_interno(v_s, v_s);
  }
  //corrige novamente para voltar às coordenadas originais
  ponto proj = {s.p.x + alpha*(v_s.x), s.p.y + alpha*(v_s.y)};
  return proj;
}



/*  Devolve 1 se os tri^angulos a e b se intersectam
e devolve 0 caso contr ́ario. */
int intersecta(triangulo a, triangulo b){
	segmento aPQ = {a.p, a.q};
	segmento aPR = {a.p, a.r};
	segmento aQR = {a.q, a.r};

	segmento bPQ = {b.p, b.q};
	segmento bPR = {b.p, b.r};
	segmento bQR = {b.q, b.r};

	segmento segA[3] = {aPQ, aPR, aQR};
	segmento segB[3] = {bPQ, bPR, bQR};

  int intersec = 0;
	int i, j;
	for(i = 0; i < 3 && !intersec; i++){
		for(j = 0; j < 3 && !intersec; j++){
			intersec = cruza(segA[i], segB[j]);
		}
	}

	return intersec;
}
/*
int main(){
	ponto p1 = {0, 1};
	ponto p2 = {1, 1.5};

	ponto q1 = {0, 2};
	ponto q2 = {-1, 0};

	segmento s1 = {p1, p2};
	segmento s2 = {q1, q2};

	printf("%d\n", cruza(s1, s2));
	return 0;
}*/

//#endif
