#ifndef GEOMETRIA
#define GEOMETRIA

struct s_ponto {
  double x, y;
};

typedef struct s_ponto ponto;
typedef struct s_ponto vetor;

struct s_segmento {
  ponto p, q;
};

typedef struct s_segmento segmento;

struct s_triangulo {
  ponto p, q, r;
};

typedef struct s_triangulo triangulo;

//  Calcula o produto interno <u,v>
double produto_interno(vetor u, vetor v);

//  Calcula o vetor u - v
vetor subtrai(vetor u, vetor v);

/*  Calcula o vetor resultante da rotação do vetor v
    de um ângulo de 90 graus no sentido anti-horário. */
vetor roda90(vetor v);

//  Calcula a distância entre os pontos p e q.
double distancia(ponto p, ponto q);

/*  Retorna 1 se o coseno do ângulo entre os vetores u e v é 
    positivo e retorna -1 se for negativo e 0 se for nulo. 
    Se u ou v for o vetor nulo, devolve 0. */
int sinal_do_coseno(vetor u, vetor v);

/*  Retorna 1 se p, q e r estão em sentido horário e -1 se for
    anti-horário. Se os pontos forem colineares devolva 0. 
    Se dois desses pontos são iguais, devolve 0. */
int sentido(ponto p, ponto q, ponto r);

/*  Retorna 1 se os interiores dos segmentos se intersectam em
    um único ponto e retorna 0 caso contrário. */
int cruza(segmento s, segmento t);

/*  Retorna 1 se o ponto p está no interior do triângulo t
    e retorna 0 caso contrário. */
int dentro(ponto p, triangulo t);

// Opcional:

/* Devolve o ponto em que s e t se intersectam caso cruza(s, t) 
   devolva 1 (ou seja, caso s e t se intersectem em um 
   único ponto no interior dos dois segmentos) e devolve 
   o ponto {0, 0} caso contrário. */
ponto cruzamento(segmento s, segmento t);

/* Calcula o ponto que é a projeção de p na reta que 
   contém o segmento s. */
ponto projeta(ponto p, segmento s);

/*  Devolve 1 se o interior dos triângulos a e b se 
    intersectam e devolve 0 caso contrário. */
int intersecta(triangulo a, triangulo b);

#endif
