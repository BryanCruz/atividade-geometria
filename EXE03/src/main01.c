#include <stdio.h>
#include "geometria.h"

//  Calcula o produto interno <u,v>
//  double produto_interno(vetor u, vetor v);
int main() {
  vetor u, v;

  while(scanf("%lf %lf %lf %lf", &u.x, &u.y, &v.x, &v.y) == 4) 
    printf("%.6lf\n", produto_interno(u, v));

  return 0;
}
