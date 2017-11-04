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
  vetor qp = subtrai(p, q);
  double dist = sqrt(pow(qp.x, 2) + pow(qp.y, 2));
  return dist;
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

/*sinal de u X v, retorna 1 se for maior que 0,
-1 se for menor que zero e 0 se u e v são paralelos*/
int sinal_produto_vetorial(vetor u, vetor v){
  double valor = u.x*v.y - v.x*u.y;

  if(valor > 0){
    return 1;
  }else if(valor == 0){
    return 0;
  }else{
    return -1;
  }
}

/*  Retorna 1 se p, q e r est~ao em sentido hor ́ario e -1 se for
anti-hor ́ario. Se os pontos forem colineares devolva 0. */
int sentido(ponto p, ponto q, ponto r){
  vetor vetorPQ = subtrai(p, q);
  vetor vetorPR = subtrai(p, r);

  return sinal_produto_vetorial(vetorPQ, vetorPR);
}


//  Retorna 1 se os segmentos se cruzam e 0 caso contr ́ario.
int cruza(segmento s, segmento t){
  double determinante;
  determinante = ((t.p2.x - t.p1.x)*(s.p2.y - s.p1.y) - (t.p2.y - t.p1.y)*(s.p2.x - s.p1.x));

  if(determinante == 0.0){
    return 0;
  }
  else{
    return 1;
  }
}

/*  Retorna 1 se o ponto p est ́a no interior do tri^angulo t.
Devolve 0 caso contr ́ario. */
int dentro(ponto p, triangulo t){
  //definir beta, pontos máximo e mínimo
  int xmax, xmin, ymax, ymin, b;
  xmax = t.p1.x;
  xmin = t.p1.x;
  ymax = t.p1.y;
  ymin = t.p1.y;

  if(t.p2.x > xmax){
      xmax = t.p2.x;
  }
  else if(t.p2.x < xmin){
    xmin = t.p2.x;
  }
  if(t.p3.x > xmax){
      xmax = t.p3.x;
  }
  else if(t.p3.x < xmin){
    xmin = t.p3.x;
  }
  if(t.p2.y > ymax){
      ymax = t.p2.y;
  }
  else if(t.p2.y < ymin){
    ymin = t.p2.y;
  }
  if(t.p3.y > ymax){
      ymax = t.p3.y;
  }
  else if(t.p3.y < ymin){
    ymin = t.p3.y;
  }

  //beta = ya*(xc-xb)+yb*(xa-xc)+yc*(xb-xa);
  b = (t.p1.y)*(t.p3.x - t.p2.x)+(t.p2.y)*(t.p1.x - t.p3.x)+(t.p3.y)*(t.p2.x - t.p1.x);

  //definir se o ponto está dentro do triângulo:
  if(p.x > xmax || p.x < xmin || p.y < ymax || p.y < ymin ){
    return 0;

  else{
    return 1;
  }


}

//  Opcional:
/*  Devolve a cordenada do ponto em que s e t se intersecta
caso eles se intersectam ou qualquer ponto caso eles n~ao
se intersectam. */
ponto cruzamento(segmanto s, segmento t){
  //encontra os parâmetros das retas; substitui os parâmetros na eq. paramétrica da reta; acha intersecção.
  ponto a;
  if(cruza(s, t) == 1){
    double determinante, parS, parT, x, y;
    determinante = ((t.p2.x - t.p1.x)*(s.p2.y - s.p1.y) - (t.p2.y - t.p1.y)*(s.p2.x - s.p1.x));

    //parâmetros de S e T
    parS = ( (t.p2.x - t.p1.x)*(t.p1.y - s.p1.y) - (t.p2.y - t.p1.y)*(t.p1.x - s.p1.x) )/determinante;
    parT = ( (s.p2.x - s.p1.x)*(t.p1.y - s.p1.y) - (s.p2.y - s.p1.y)*(t.p1.x - s.p1.x) )/determinante;

    //Substituindo S ou T e encontrando o ponto:
    a.x = (s.p1.x) + (s.p2.x - s.p1.x)*parS;
    a.y = (s.p1.y) + (s.p2.y - s.p1.y)*parS;
  }

  return a;
}


/*  Calcula o ponto que  ́e a proje ̧c~ao de p no segmento s. */
ponto projeta(ponto p, segmento s){
  //troca de coordenadas
  vetor v_s = {s.p2.x-s.p1.x, s.p2.y-s.p1.y};

  //correcao da troca de coordenadas
  p.x -= s.p1.x;
  p.y -= s.p1.y;

  //calculo da projecao
  double alpha = produto_interno(p, v_s)/produto_interno(v_s, v_s);
  //volta às coordenadas normais e corrige novamente
  ponto proj = {s.p1.x + alpha*v_s.x, s.p1.y + alpha*v_s.y};

  return proj;
}


/*  Devolve 1 se os tri^angulos a e b se intersectam
e devolve 0 caso contr ́ario. */
int intersecta(triangulo a, triangulo b){
  segmento aPQ, aPR, aQR, bPQ, bPR, bQR;
  aPQ = (a.p1.x, a.p1.y, a.p2.x, a.p2.y);
  aPR = (a.p1.x, a.p1.y, a.p3.x, a.p3.y);
  aQR = (a.p2.x, a.p2.y, a.p3.x, a.p3.y);
  bPQ = (b.p1.x, a.p1.y, a.p2.x, a.p2.y);
  bPR = (b.p1.x, b.p1.y, b.p3.x, b.p3.y);
  bQR = (b.p2.x, b.p2.y, b.p3.x, b.p3.y);

  if(cruza(aPQ, bPQ) == 1 || cruza(aPQ, bPR) == 1 || cruza(aPQ, bQR) == 1 ){
    return 1;
  }
  else if(cruza(aPR, bPQ) == 1 || cruza(aPR, bPR) == 1 || cruza(aPR, bQR) == 1){
    return 1;
  }
  else if(cruza(aQR, bPQ) == 1 || cruza(aPR, bPR) == 1 || cruza(aQR, bQR) == 1){
    return 1;
  }
  else{
    return 0;
  }
}

#endif
