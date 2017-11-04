#include<stdio.h>
#include<math.h>

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

typedef s_triangulo triangulo;


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





int main(){

	return 0;
}
