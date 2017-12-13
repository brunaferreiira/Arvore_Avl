#include <new>
#include <stdio.h>
#include "funcoes.hpp"
#include <iostream>
using namespace std;


void inicializar (DicAVL &D) {
	D.raiz = nullptr;
}

Noh* inserir (DicAVL &D, TC c, TV v) {
	Noh *novoNoh =  new (std::nothrow) Noh;
	Noh *antNoh = nullptr;
	Noh *proxNoh = nullptr;

	novoNoh->dir = nullptr;
	novoNoh->esq = nullptr;
	novoNoh->valor = v;
	novoNoh->chave = c;

	if (D.raiz == nullptr) {
		novoNoh->pai = nullptr;
		D.raiz = novoNoh;	
	}
	else {
		proxNoh = D.raiz;

		while (proxNoh != nullptr) {
			antNoh = proxNoh;

			if (proxNoh->chave == c) {
				return nullptr;
			}
			else if (proxNoh->chave < c) {
				proxNoh = proxNoh->dir;
			}
			else if (proxNoh->chave > c) {
				proxNoh = proxNoh->esq;
			}
		}

		if (antNoh->chave < c) {
			antNoh->dir = novoNoh;
			novoNoh->pai = antNoh;
		}
		if (antNoh->chave > c){
			antNoh->esq = novoNoh;
			novoNoh->pai = antNoh;
		}
	}
	
	balancear_arvore(D);
}

void balancear_arvore (DicAVL &D) {
	Noh* novaRaiz = nullptr;
	novaRaiz = balancear_noh(*D.raiz);
	if (novaRaiz != D.raiz) {
		D.raiz = novaRaiz;
	}
}

Noh* balancear_noh (Noh &noh) {
	Noh* nohBalanceado = nullptr;

	if (noh.esq) {
		noh.esq = balancear_noh(*noh.esq);
	}
	if (noh.dir) {
		noh.dir = balancear_noh(*noh.dir);
	}

	int fator = fator_balanceamento(noh);

	if (fator >=2) {

		if (fator_balanceamento(*noh.esq) <= -1) {
			nohBalanceado = rot_esq_dir(noh);
		}
		else {
			nohBalanceado = rot_esq_esq(noh);
		} 
	}
	else if(fator <=-2) {
		if (fator_balanceamento(*noh.dir) >= 1) {
			nohBalanceado = rot_dir_esq(noh);
		}
		else {
			nohBalanceado = rot_dir_dir(noh);
		} 
	}

	else {
		nohBalanceado = &noh;
	}

	return nohBalanceado;
}

int fator_balanceamento (Noh &noh) {
	int fator = 0;
	if (noh.esq) {
		fator += altura(*noh.esq);
	}
	if (noh.dir) {
		fator -= altura(*noh.dir);
	}
	return fator;
}

int altura (Noh &noh) {
	int alturaDir = 0;
	int alturaEsq = 0;

	if (noh.dir) {
		alturaDir = altura(*noh.dir);
	}
	
	if (noh.esq) {
		alturaEsq = altura(*noh.esq);
	}

	if (alturaDir>alturaEsq) {
		return alturaDir + 1;
	}
	else {
		return alturaEsq + 1;
	}
	
}
		
Noh* rot_dir_dir (Noh &noh) {
	Noh* nohAux = &noh;
	Noh* nohDir = nohAux->dir;
	nohDir->pai = nohAux->pai;
	nohAux->pai = nohDir;
	nohDir->esq->pai = nohAux;

	nohAux->dir = nohDir->esq;
	nohDir->esq = nohAux;
	return nohDir;
}

Noh* rot_esq_esq (Noh &noh) {
	Noh* nohAux = &noh;
	Noh* nohEsq = nohAux->esq;
	nohEsq->pai = nohAux->pai;
	nohAux->pai = nohEsq;
	nohEsq->dir->pai = nohAux;

	nohAux->esq = nohEsq->dir;
	nohEsq->dir = nohAux;
	return nohEsq;
}

Noh* rot_dir_esq (Noh &noh) {
	Noh* nohAux = &noh;
	Noh* nohDir = nohAux->dir;
	Noh* nohEsq = nohDir->esq;
	nohEsq->pai = nohAux->pai;
	nohAux->pai = nohEsq;
	nohDir->pai = nohEsq;
	nohEsq->esq->pai = nohAux;
	nohEsq->dir->pai = nohDir;

	nohAux->dir = nohEsq->esq;
	nohDir->esq = nohEsq->dir;
	nohEsq->dir = nohDir;
	nohEsq->esq = nohAux;
	return nohEsq;
}
Noh* rot_esq_dir (Noh &noh) {
	Noh* nohAux = &noh;
	Noh* nohEsq = nohAux->esq;
	Noh* nohDir = nohEsq->dir;
	nohDir->pai = nohAux->pai;
	nohAux->pai = nohDir;
	nohEsq->pai = nohDir;
	nohDir->dir->pai = nohAux;
	nohDir->esq->pai = nohEsq;

	nohAux->esq = nohDir->dir;
	nohEsq->dir = nohDir->esq;
	nohDir->esq = nohEsq;
	nohDir->dir = nohAux;
	return nohDir;

}

Noh* procurar (DicAVL &D, TC c) {
	Noh *nohAux = D.raiz;
	while (nohAux && nohAux->chave != c) {
		if (c > nohAux->chave) {
			nohAux = nohAux->dir;}
		else {
			nohAux = nohAux->esq;}	
	}
	return nohAux;
}

void remover (DicAVL &D, Noh *n) {
		
	if (n->esq==nullptr && n->dir==nullptr) {
		delete n; 
	}
	else if (n->esq && !n->dir) {

		if(n->pai->esq->chave == n->chave) {
			n->pai->esq = n->esq;
		}
		else {
			n->pai->dir = n->esq;
		}	
		delete n;
	}
	else if (!n->esq && n->dir) {

		if(n->pai->esq->chave == n->chave) {
			n->pai->esq = n->dir;
		}
		else {
			n->pai->dir = n->dir;
		}
		
		delete n;
	}
	else if (n->esq && n->dir) {
		Noh* nohAux = n->dir;
		while (nohAux->esq) {
			nohAux = nohAux->esq;
		}

		nohAux->esq = n->esq;

		if(n->pai == nullptr) {
			D.raiz = n->dir;
		}
		else{ 
			if(n->pai->esq->chave == n->chave) {
				n->pai->esq = n->dir;
			}
			else {
				n->pai->dir = n->dir;
			}			
		}
		delete n;
	}
	
	balancear_arvore(D);
}

void terminar (DicAVL &D) {
	matar(D.raiz);
	inicializar(D);
}

void matar(Noh *noh) {
	if(noh==nullptr)
		return;

	matar(noh->esq);
	matar(noh->dir);

	delete noh;
	return;
}

void listar (Noh *noh) {
	if(noh != nullptr) {
		listar(noh->esq);
		cout << "chave: " << noh->chave << " valor:" << noh->valor << " altura: "<< altura(*noh);
		listar(noh->dir);
	}
	else
		return;
}

int main(){
	DicAVL arvore;
	inicializar(arvore);
	int op;
	TC chave;
	TV valor;

	for (;;) {
		cout << "\n 0-Sair; \n 1-Inserir;\n 2-Listar;\n 3-Remover;\n 4-Procurar;\n 5-Terminar\nOpcao: ";
		cin >> op;
		if (op==0) {
			break;
		}
		else if (op==1) {
			cout << "Insira o valor";
			cin >> valor;
			cout << "Insira a chave";
			cin >> chave;
			inserir(arvore,chave,valor);
				
		}
		else if (op==2) {
			if (arvore.raiz==nullptr) {
				cout << "Árvore vazia!";
			}
			else {
				cout << endl;
				listar(arvore.raiz);
				cout << endl;
			}
		}
		else if (op==3) {
			cout << "Insira a chave que deseja remover";
			cin >> chave;
			remover(arvore, procurar(arvore,chave));
		}
		else if (op==4) {
			cout << "Insira a chave do elemento que deseja procurar";
			cin >> chave;
			Noh* nohBusca = procurar(arvore,chave);
			cout << "chave: " << nohBusca->chave << " valor:" << nohBusca->valor << " altura: "<< altura(*nohBusca);
		}
		else if (op==5) {
			terminar(arvore);

		}
	}
	return 0;
	}