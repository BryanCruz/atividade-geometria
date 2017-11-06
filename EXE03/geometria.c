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

/*valor numérico de (u x v)*/
double produto_vetorial(vetor u, vetor v){
  return u.x*v.y - v.x*u.y;
}

/*  Retorna 1 se p, q e r est~ao em sentido hor ́ario e -1 se for
anti-hor ́ario. Se os pontos forem colineares devolva 0. */
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


//  Retorna 1 se os segmentos se cruzam e 0 caso contr ́ario.
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

/*  Retorna 1 se o ponto p est ́a no interior do tri^angulo t.
Devolve 0 caso contr ́ario. */
int dentro(ponto p, triangulo t){
  return (sentido(p, t.p, t.q) == sentido(p, t.q, t.r)) && (sentido(p, t.q, t.r) == sentido(p, t.r, t.p));
}

//  Opcional:
/*  Devolve a cordenada do ponto em que s e t se intersecta
caso eles se intersectam ou qualquer ponto caso eles nao
se intersectam. */

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



/* Devolve 1 se o interior dos tri^angulos a e b se
intersectam e devolve 0 caso contr´ario. */

int intersecta(triangulo a, triangulo b){
	segmento segA[] = {{a.p, a.q}, {a.q, a.r}, {a.r, a.p}};
	segmento segB[] = {{b.p, a.q}, {b.q, a.r}, {b.r, b.p}};
	
	int inside = 1;
	int i, j;
	for(i = 0; i < 3 && inside; i++){
		for(j = 0; j < 3 && inside; j++){
			inside = !cruza(segA[i], segB[j]);
		}
	}
	
	return inside? 1 : 0;
	
}