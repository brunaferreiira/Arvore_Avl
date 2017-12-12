
void inicializar (DicAVL &D) {
	D->raiz=nullptr;
}

Noh* inserir (DicAVL &D, TC c, TV v) {
	Noh *novo_noh =  new (std::nothrow) Noh;
	Noh *ant_noh = nullptr;
	Noh *prox_noh = nullptr;

	if (D->raiz==nullptr) {
		D->raiz = novo_noh;			
		novo_noh->dir = nullptr;
		novo_noh->esq = nullptr;
		novo_noh->valor = v;
		novo_noh->chave = c;
	}
	else {
		prox_noh = D->raiz;

		while (prox_noh != nullptr) {
			ant_noh = prox_noh;

			if (prox_noh->chave == c)
			{
				return;
			}
			else if (prox_noh->chave < c) {
				prox_noh = prox_noh->dir;
			}
			else {
				prox_noh = prox_noh->esq;
			}
		}

		novo_noh->pai = ant_noh;

		if (ant_noh->chave < c) {
			ant_noh->dir = novo_noh;
			novo_noh->dir = nullptr;
			novo_noh->esq = nullptr;
			novo_noh->valor = v;
			novo_noh->chave = c;
		}
		else {
			ant_noh->dir = novo_noh;
			novo_noh->dir = nullptr;
			novo_noh->esq = nullptr;
			novo_noh->valor = v;
			novo_noh->chave = c;
		}
	}
	balancear_arvore(D);
}

void balancear_arvore (DicAVL&D) {
	Noh* nova_raiz = nullptr;
	nova_raiz = balancear_noh(D->raiz);
	if (nova_raiz =! D->raiz) {
		D->raiz = nova_raiz;
	}
}

Noh* balancear_noh (Noh* noh) {
	Noh* noh_balanceado = nullptr;

	if (noh->esq) {
		noh->esq = balancear_noh(noh->esq);
	}
	if (noh->dir) {
		noh->dir = balancear_noh(noh->dir);
	}

	int fator = fator_balanceamento (noh);

	if (fator >=2) {

		if (fator_balanceamento(noh->esq) <= -1) {
			noh_balanceado = rot_esq_dir(noh);
		}
		else {
			noh_balanceado = rot_dir_dir(noh);
		} 
	}
	else if(fator <=-2) {
		if (fator_balanceamento(noh->dir) >= 1) {
			noh_balanceado = rot_dir_esq(noh);
		}
		else {
			noh_balanceado = rot_dir_dir(noh);
		} 
	}

	else {
		noh_balanceado = noh;
	}
}

int fator_balanceamento (Noh* noh) {
	int fator =0;
	if (noh->esq) {
		fator += altura(noh->esq);
	}
	if (noh->dir) {
		fator -= altura(noh->dir);
	}
	return fator;
}
		
Noh* rot_dir_dir (Noh* noh) {
	Noh* noh_aux = noh;
	Noh* noh_dir = noh_aux->dir;
	noh_aux->dir = noh_dir->esq;
	noh_dir->esq = noh_aux;
	return noh_dir;
}

Noh* rot_esq_esq (Noh* noh) {
	Noh* noh_aux = noh;
	Noh* noh_esq = noh_aux->esq;
	noh_aux->esq = noh_esq->dir;
	noh_esq->dir = noh_aux;
	return noh_esq;

}

Noh rot_dir_esq (Noh* noh) {
	Noh* noh_aux = noh;
	Noh*
}

Noh* procurar (DicAVL &D, TC c);   // Retorna um ponteiro para o n ́o da
// chave procurada, ou nulo se a chave
// n~ao estiver em D.

void remover (DicAVL &D, Noh *n);  // ’n’ aponta para o n ́o a ser removido

void terminar (DicAVL &D);         // Desaloca os n ́os da  ́arvore.