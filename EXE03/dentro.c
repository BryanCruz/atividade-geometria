int dentro (ponto p, triangulo t){
	int aux = 0;
	double v1, v2, v3, v4, v5, v6;

	v1 = produto_vetorial(t.r - t.q, p - t.p);
	v2 = produto_vetorial(t.r - t.q, t.p - t.q);
	v3 = produto_vetorial(t.r - t.p, p - t.p);
  v4 = produto_vetorial(t.r - t.p, t.q - t.p);
  v5 = produto_vetorial(t.q - t.p, p - t.p);
	v6 = produto_vetorial(t.q - t.p, t.r - p);

	if(produto_interno(v1, v2) >= 0 && produto_interno(v3, v4)>=0 && produto_interno(v5, v6)>=0){
		aux = 1;
	}

	if(aux == 1){
		return 1;
	}
    else{
		return 0;
	}


}
