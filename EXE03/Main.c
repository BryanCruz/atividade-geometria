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
  determinante = ((t.q.x - t.p.x)*(s.q.y - s.p.y) - (t.q.y - t.p.y)*(s.q.x - s.p.x));

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
  xmax = t.p.x;
  xmin = t.p.x;
  ymax = t.p.y;
  ymin = t.p.y;

  if(t.q.x > xmax){
      xmax = t.q.x;
  }
  else if(t.q.x < xmin){
    xmin = t.q.x;
  }
  if(t.r.x > xmax){
      xmax = t.r.x;
  }
  else if(t.r.x < xmin){
    xmin = t.r.x;
  }
  if(t.q.y > ymax){
      ymax = t.q.y;
  }
  else if(t.q.y < ymin){
    ymin = t.q.y;
  }
  if(t.r.y > ymax){
      ymax = t.r.y;
  }
  else if(t.r.y < ymin){
    ymin = t.r.y;
  }

  //beta = ya*(xc-xb)+yb*(xa-xc)+yc*(xb-xa);
  b = (t.p.y)*(t.r.x - t.q.x)+(t.q.y)*(t.p.x - t.r.x)+(t.r.y)*(t.q.x - t.p.x);

  //definir se o ponto está dentro do triângulo:
  if(p.x > xmax || p.x < xmin || p.y < ymax || p.y < ymin ){
    return 0;

  }else{
    return 1;
  }


}

//  Opcional:
/*  Devolve a cordenada do ponto em que s e t se intersecta
caso eles se intersectam ou qualquer ponto caso eles n~ao
se intersectam. */
ponto cruzamento(segmento s, segmento t){
  //encontra os parâmetros das retas; substitui os parâmetros na eq. paramétrica da reta; acha intersecção.
  ponto a;
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
}


/*  Calcula o ponto que  ́e a proje ̧c~ao de p no segmento s. */
ponto projeta(ponto p, segmento s){
  //troca de coordenadas
  vetor v_s = {s.q.x-s.p.x, s.q.y-s.p.y};

  //correcao da troca de coordenadas
  p.x -= s.p.x;
  p.y -= s.p.y;

  //calculo da projecao
  double alpha = produto_interno(p, v_s)/produto_interno(v_s, v_s);
  //volta às coordenadas normais e corrige novamente
  ponto proj = {s.p.x + alpha*v_s.x, s.p.y + alpha*v_s.y};

  return proj;
}


/*  Devolve 1 se os tri^angulos a e b se intersectam
e devolve 0 caso contr ́ario. */
int intersecta(triangulo a, triangulo b){
  segmento aPQ = {a.p.x, a.p.y, a.q.x, a.q.y};
  segmento aPR = {a.p.x, a.p.y, a.r.x, a.r.y};
  segmento aQR = {a.q.x, a.q.y, a.r.x, a.r.y};
  segmento bPQ = {b.p.x, a.p.y, a.q.x, a.q.y};
  segmento bPR = {b.p.x, b.p.y, b.r.x, b.r.y};
  segmento bQR = {b.q.x, b.q.y, b.r.x, b.r.y};

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

//#endif
