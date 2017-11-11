//Bryan Bialokur da Cruz, RA: 11052316
//Melissa Gabriela Pereira da Soledade Perrone, RA: 11072216

#include "geometria.h"
#include <stdio.h>
#include <math.h>

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

//1  Calcula o produto interno <u,v>
double produto_interno(vetor u, vetor v) {
	return u.x*v.x + u.y*v.y;
}

//2  Calcula o vetor u - v
vetor subtrai(vetor u, vetor v){
	vetor temp;
	temp.x = u.x - v.x;
	temp.y = u.y - v.y;

	return temp;
}

/*3  Calcula o vetor resultante da rotacao do vetor v
de um angulo de 90 graus no sentido anti-horario. */
vetor roda90(vetor v){
	double aux = v.y;
	v.y = v.x;
	v.x = -aux;

	return p;
}

//4 Calcula a distância entre os pontos p e q.
 double distancia (ponto p, ponto q){
  vetor qp = subtrai(p, q);
  double dist = sqrt(pow(qp.x, 2) + pow(qp.y, 2));
  return dist;
}

/*5  Retorna 1 se o coseno do ^angulo entre os vetores u e v  ́
		 e positivo e retorna -1 se for negativo e 0 se for nulo.
		 Se u ou v for o vetor nulo, devolve 0.*/
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

/*valor numérico de (u x v)*/
double produto_vetorial(vetor u, vetor v){
  return u.x*v.y - v.x*u.y;
}

/* 6 Retorna 1 se p, q e r estão em sentido horário e -1 se for
    anti-horário. Se os pontos forem colineares devolva 0.
    Se dois desses pontos são iguais, devolve 0. */
int sentido(ponto p, ponto q, ponto r){
  vetor vetorPQ = subtrai(q, p);
  vetor vetorPR = subtrai(r, p);

  double pv = produto_vetorial(vetorPQ, vetorPR);
	if(pv > 0){
		return -1;
	}else if(pv < 0){
		return 1;
	}else{
		return 0;
	}
}


/* 7 Retorna 1 se os interiores dos segmentos se intersectam em
    um único ponto e retorna 0 caso contrário. */
int cruza(segmento s, segmento t){

	int sent1 = sentido(s.p, t.p, t.q);
	int sent2 = sentido(s.q, t.p, t.q);

	int sent3 = sentido(t.p, s.p, s.q);
	int sent4 = sentido(t.q, s.p, s.q);

	int cr = 0;
	if(sent1*sent2 == -1 && sent3*sent4 == -1){
		//se intersectam
		cr = 1;
	}else{
		if((sent1*sent2 == -1 && sent3*sent4 == 0) || (sent1*sent2 == 0 && sent3*sent4 == -1)){
			//um dos pontos de um segmento faz parte do outro segmento
			cr = 1;
		}else{
			if((s.p.x == t.p.x && s.p.y == t.p.y) || (s.p.x == t.q.x && s.p.y == t.q.y)
			|| (s.q.x == t.p.x && s.q.y == t.p.y) || (s.q.x == t.q.x && s.q.y == t.q.y)){
				//os pontos do segmento coincidem
				cr = 1;
			}
		}
	}

	return cr;
}

/*8 Retorna 1 se o ponto p está no interior do triângulo t
    e retorna 0 caso contrário. */
int dentro(ponto p, triangulo t){
  return (sentido(p, t.p, t.q) == sentido(p, t.q, t.r)) && (sentido(p, t.q, t.r) == sentido(p, t.r, t.p));
}

//  Opcional:
/*9 Devolve o ponto em que s e t se intersectam caso cruza(s, t)
   devolva 1 (ou seja, caso s e t se intersectem em um
   único ponto no interior dos dois segmentos) e devolve
   o ponto {0, 0} caso contrário. */

ponto cruzamento(segmento s, segmento t){
	ponto p = {0, 0};

	if(cruza(s, t)){
		//encontra os parâmetros das retas; substitui os parâmetros na eq. paramétrica da reta; acha intersecção.
		//r_s = s.p + (s.q - s.p)*n1 = a + b*n1
		//r_t = t.p + (t.q - t.p)*n1 = c + d*n2

	  ponto a = s.p;
	  vetor b = subtrai(s.q, s.p);

	  ponto c = t.p;
	  vetor d = subtrai(t.q, t.p);

		if(produto_vetorial(d, b) != 0){
			//parametro da reta s
			double n1 = produto_vetorial(d, subtrai(c, a)) / produto_vetorial(d, b);

			//substituindo n1 para encontrar o ponto:
			p.x = a.x + n1*b.x;
			p.y = a.y + n1*b.y;
		}else{
			if((s.p.x == t.p.x && s.p.y == t.p.y) || (s.p.x == t.q.x && s.p.y == t.q.y)){
				p.x = s.p.x;
				p.y = s.p.y;
			}else if((s.q.x == t.p.x && s.q.y == t.p.y) || (s.q.x == t.q.x && s.q.y == t.q.y)){
				p.x = s.q.x;
				p.y = s.q.y;
			}
		}

	}

  return p;
}


/*10 Calcula o ponto que é a projeção de p na reta que
   contém o segmento s. */
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



/*  Devolve 1 se o interior dos triângulos a e b se
    intersectam e devolve 0 caso contrário. */
int intersecta(triangulo a, triangulo b){
	segmento aPQ = {a.p, a.q};
	segmento aPR = {a.q, a.r};
	segmento aQR = {a.r, a.p};

	segmento bPQ = {b.p, b.q};
	segmento bPR = {b.q, b.r};
	segmento bQR = {b.r, b.p};

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
