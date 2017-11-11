#include <stdio.h>
#include "geometria.h"

/*  Devolve a cordenada do ponto em que s e t se intersecta
    caso eles se intersectem ou qualquer ponto caso contrário. */
//  ponto cruzamento(segmento s, segmento t);
int main() {
  segmento s, t;

  while(scanf("%lf %lf %lf %lf %lf %lf %lf %lf", &s.p.x, &s.p.y,
	      &s.q.x, &s.q.y, &t.p.x, &t.p.y, &t.q.x, &t.q.y) == 8) {
    ponto p = cruzamento(s, t);
    printf("%.6lf %.6lf\n", p.x, p.y);
  }

  return 0;
}


