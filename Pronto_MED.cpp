//Inclus�o de bibliotecas.
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <locale.h>
#include <cstring>
#include <windows.h>

using namespace std;

//Struct respons�vel por armazenar os dados do paciente.
struct Pac
{
	char nomepac[100];
	int registropac;
};

//Struct da lista.
struct elemento
{
	Pac pac;
	struct elemento* prox;
};
typedef struct elemento Elemento;

//Struct respons�vel por armazenar os dados do m�dico.
struct Med
{
	char nomemed[100];
	int registromed;
};

//Struct da pilha.
struct Pilha
{
	int topo;
	int capacidade;
	Med *pElem;
} pi;

//Struct para armazenar o registro dos atendimentos.
struct Reg
{
	char nomepac[100];
	char nomemed[100];
	int numeroatendimento;
};

//Struct da �rvore.
struct noh
{
	Reg reg;
	struct noh* esq;
	struct noh* dir;
	int altura;
};
typedef struct noh arvore;

//Declara��o das fun��es.
Elemento* lst_cria(void);
Elemento* lst_insere(Elemento* lst);
Elemento* lst_busca(Elemento* lst, int num);
void lst_imprime(Elemento* lst);
int lst_vazia(Elemento* lst);
Elemento* lst_retira(Elemento* lst);
void criarPilha(struct Pilha *p, int c);
int estaVazia(struct Pilha *p);
int estaCheia(struct Pilha *p);
void push(struct Pilha *p, Med *m);
Med pop(struct Pilha *p);
Med retornaTopo(struct Pilha *p);
arvore* arv_criavazia();
arvore* insere(arvore* a, Reg *r);
arvore* novoNo(Reg *r);
int max(int a, int b);
arvore* min(arvore* a);
int altura(arvore* a);
int pegaBalanceamento(arvore* a);
arvore* rotacaoEsquerda(arvore* x);
arvore* rotacaoDireita(arvore* y);
void arv_busca(arvore* a, int pesquisa);
int arv_vazia(arvore* a);

//Declara��o de uma vari�vel global para armazenar o nome a ser enviado para a �rvore.
char nomepaciente[100];

//Fun��o principal.
int main()
{
	//Declara��o das vari�veis.
	int opcao1;
	int valor;
	int vazia;
	Elemento* lst;
	int opcao2;
	int opcao3;
	int cheia;
	arvore* arv;
	int atendimento = 0;
	Med med;
	int buscaatendimento;

	//Fun��o que aceita os caracteres da Lingua Portuguesa.
	setlocale(LC_ALL, "Portuguese");

	//Criar lista vazia.
	lst = lst_cria();

	//Criar pilha vazia.
	criarPilha(&pi, 5);

	//Criar �rvore vazia.
	arv = arv_criavazia();

	//Menu geral.
	cout << "Digite: " << endl;
	cout << "1 - Para paciente." << endl;
	cout << "2 - Para m�dico." << endl;
	cout << "3 - Para atendimento." << endl;
	cout << "4 - Para acessar o registro de atendimentos." << endl;
	cout << "5 - Para mais informa��es." << endl;
	cout << "6 - Sair do programa." << endl;
	cin >> opcao3;
	cout << endl;

	while(opcao3 != 6)
	{
		switch(opcao3)
		{
		case 1:
			//Menu de op��es do paciente.
			system("cls");
			cout << "O que deseja fazer? Digite o n�mero da op��o desejada." << endl;
			cout << "1 - Cadastrar um paciente." << endl;
			cout << "2 - Buscar paciente." << endl;
			cout << "3 - Ver pacientes ainda n�o atendidos." << endl;
			cout << "4 - Voltar ao menu principal." << endl;
			cin >> opcao1;
			cout << endl;

			while(opcao1 != 4)
			{
				switch(opcao1)
				{
				case 1:
					system("cls");
					lst = lst_insere(lst);
					cout << "O paciente foi cadastrado com sucesso." << endl;
					cout << endl;
					system("pause");
					break;

				case 2:
					system("cls");
					cout << "Digite o registro do paciente desejado." << endl;
					cin >> valor;
					lst_busca(lst, valor);
					if(lst_busca(lst, valor) == NULL)
					{
						cout << "Paciente j� atendido." << endl;
						cout << endl;
					}
					else
					{
						cout << "Paciente n�o atendido." << endl;
						cout << endl;
					}
					system("pause");
					cout << endl;
					break;

				case 3:
					system("cls");
					vazia = lst_vazia(lst);
					if(vazia == 1)
					{
						cout << "Todos os pacientes j� foram atendidos." << endl;
						cout << endl;
					}
					else
					{
						cout << "Pacientes ainda n�o atendidos: " << endl;
						lst_imprime(lst);
						cout << endl;
					}
					system("pause");
					cout << endl;
					break;

				default:
					system("cls");
					cout << "Op��o inv�lida." << endl;
					cout << endl;
					system("pause");
				}

				system("cls");
				cout << "O que deseja fazer? Digite o n�mero da op��o desejada." << endl;
				cout << "1 - Cadastrar um paciente." << endl;
				cout << "2 - Buscar paciente." << endl;
				cout << "3 - Ver pacientes ainda n�o atendidos." << endl;
				cout << "4 - Voltar ao menu principal." << endl;
				cin >> opcao1;
				cout << endl;
			}
			break;

		case 2:
			//Menu de op��es de m�dico.
			system("cls");
			cout << "O que deseja fazer? Digite o n�mero da op��o desejada." << endl;
			cout << "1 - Cadastrar um m�dico." << endl;
			cout << "2 - Mostrar o pr�ximo m�dico dispon�vel." << endl;
			cout << "3 - Voltar ao menu principal." << endl;
			cin >> opcao2;

			while(opcao2 != 3)
			{
				switch(opcao2)
				{
				case 1:
					cheia = estaCheia(&pi);
					if(cheia == 1)
					{
						system("cls");
						cout << "Ainda h� m�dicos dispon�veis para o atendimento." << endl;
						cout << endl;
						system("pause");
					}
					else
					{
						system("cls");
						Med *novomed = (Med*) malloc(sizeof(Med));
						cout << "Qual nome do m�dico?" << endl;
						cin.ignore();
						cin.getline(novomed->nomemed, 100);
						do
						{
							cout << "Qual o registro do m�dico?" << endl;
							cin >> novomed->registromed;
						}
						while(novomed->registromed <= 0);
						push(&pi, novomed);
						cout << "Pronto. O m�dico foi cadastrado com sucesso." << endl;
						cout << endl;
						system("pause");
					}
					break;

				case 2:
					vazia = estaVazia(&pi);
					if(vazia == 1)
					{
						system("cls");
						cout << "N�o h� nenhum m�dico dispon�vel para atendimento." << endl;
						cout << endl;
						system("pause");
					}
					else
					{
						system("cls");
						med = retornaTopo(&pi);
						cout << "O pr�ximo m�dico dispon�vel � " << med.nomemed << "." << endl;
						cout << endl;
						system("pause");
					}
					break;

				default:
					system("cls");
					cout << "Op��o inv�lida." << endl;
					cout << endl;
					system("pause");
					break;
				}

				system("cls");
				cout << "O que deseja fazer? Digite o n�mero da op��o desejada." << endl;
				cout << "1 - Cadastrar um m�dico." << endl;
				cout << "2 - Mostrar o pr�ximo m�dico dispon�vel." << endl;
				cout << "3 - Voltar ao menu principal." << endl;
				cin >> opcao2;
			}
			break;

		case 3:
			system("cls");
			//Verificar se ainda h� pacientes para serem atendidos ou n�o.
			if(lst_vazia(lst) == 1)
			{
				cout << "Todos os pacientes j� foram atendidos." << endl;
				cout << endl;
			}

			//Verificar se h� m�dicos dispon�veis para atendimento ou n�o.
			if(estaVazia(&pi) == 1)
			{
				cout << "N�o h� m�dicos dispon�veis para atendimento." << endl;
				cout << endl;
			}

			//Se houverem m�dicos e pacientes, � feito um atendimento.
			if(lst_vazia(lst) == 0 && estaVazia(&pi) == 0)
			{
				Reg* reg = (Reg*) malloc(sizeof(Reg));
				atendimento++;
				lst = lst_retira(lst);
				med = pop(&pi);
				strcpy(reg->nomemed, med.nomemed);
				strcpy(reg->nomepac, nomepaciente);
				reg->numeroatendimento = atendimento;
				arv = insere(arv, reg);
				cout << "Paciente atendido." << endl;
				cout << endl;
			}
			system("pause");
			break;

		case 4:
			if(arv_vazia(arv) == 1)
			{
				system("cls");
				cout << "N�o h� nenhum atendimento registrado." << endl;
				cout << endl;
				system("pause");
			}
			else
			{
				system("cls");
				do
				{
					cout << "Qual o n�mero do atendimento que deseja visitar?" << endl;
					cin >> buscaatendimento;
				}
				while(buscaatendimento <= 0);
				system("cls");
				arv_busca(arv, buscaatendimento);
				system("pause");
			}
			break;

		case 5:
			//Fun��o respons�vel por abrir um site no Internet Explorer.
			system("cls");
			cout << "Carregando site..." << endl;
			system("start iexplore.exe http://www.hamc.org.br/");
			system("pause");
			break;

		default:
			system("cls");
			cout << "Op��o inv�lida." << endl;
			cout << endl;
			system("pause");
			break;
		}

		system("cls");
		cout << "Digite: " << endl;
		cout << "1 - Para paciente." << endl;
		cout << "2 - Para m�dico." << endl;
		cout << "3 - Para atendimento." << endl;
		cout << "4 - Para acessar o registro de atendimentos." << endl;
		cout << "5 - Para mais informa��es." << endl;
		cout << "6 - Sair do programa." << endl;
		cin >> opcao3;
		cout << endl;
	}
}

//Criando lista vazia.
Elemento* lst_cria(void)
{
	return NULL;
}

//Cadastro do paciente, salvando seu nome e n�mero de registro.
Elemento* lst_insere(Elemento* lst)
{
	cin.ignore();
	Elemento* novo = (Elemento*)malloc(sizeof(Elemento));
	cout << "Qual o nome do paciente?" << endl;
	cin.ignore(0, '\n');
	cin.getline(novo->pac.nomepac, 100);
	do
	{
		cout << "Entre com o registro do paciente: " << endl;
		cin >> novo->pac.registropac;
	}
	while(novo->pac.registropac <= 0);
	novo->prox = lst;
	return novo;
}

//Buscando paciente para ver se foi atendido ou n�o, atrav�s do registro.
Elemento* lst_busca(Elemento* lst, int v)
{
	Elemento* p;
	for(p = lst; p != NULL; p = p->prox)
	{
		if(p->pac.registropac == v)
		{
			return p;
		}
	}
	return NULL;
}

//Imprimir os pacientes que n�o foram atendidos.
void lst_imprime(Elemento* lst)
{
	Elemento* p;
	for(p = lst; p != NULL; p = p->prox)
	{
		cout << "Paciente " << p->pac.nomepac << "." << endl;
	}
}

//Verificar se a lista est� vazia ou n�o.
int lst_vazia(Elemento* lst)
{
	return(lst == NULL);
}

//Remover pacientes da lista, atrav�s do registro dele.
Elemento* lst_retira(Elemento* lst)
{
	Elemento* a = NULL;
	Elemento* p = lst;
	while(p->prox != NULL)
	{
		a = p;
		p = p->prox;
	}
	strcpy(nomepaciente, p->pac.nomepac);
	if(p == NULL)
	{
		return lst;
	}
	if(a == NULL)
	{
		lst = p->prox;
	}
	else
	{
		a->prox = p->prox;
	}
	free(p);
	return lst;
}

//Criar Pilha.
void criarPilha(struct Pilha *p, int c)
{
	p->topo = -1;
	p->capacidade = c;
	p->pElem = (Med*) malloc(c * sizeof(Med));
}

//Conferir se pilha est� vazia.
int estaVazia(struct Pilha *p)
{
	if(p->topo == -1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//Conferir se pilha est� cheia.
int estaCheia(struct Pilha *p)
{
	if(p->topo == p->capacidade - 1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

//Acrescentar um elemento � pilha.
void push(struct Pilha *p, Med *m)
{
	p->topo++;
	p->pElem[p->topo] = *m;
}

//Retirar elemento do topo da pilha.
Med pop(struct Pilha *p)
{
	Med aux = p->pElem[p->topo];
	p->topo--;
	return aux;
}

//Retornar o nome do m�dico no topo da pilha.
Med retornaTopo(struct Pilha *p)
{
	return p->pElem[p->topo];
}

//Criar uma �rvore vazia.
arvore* arv_criavazia()
{
	return NULL;
}

//Inserir novos registros de atendimento na �rvore.
arvore* insere(arvore* a, Reg *r)
{
	if(a == NULL)
	{
		return(novoNo(r));
	}

	if(r->numeroatendimento < a->reg.numeroatendimento)
	{
		a->esq = insere(a->esq, r);
	}
	else if(r->numeroatendimento > a->reg.numeroatendimento)
	{
		a->dir = insere(a->dir, r);
	}
	else
	{
		return a;
	}

	a->altura = 1 + max(altura(a->esq), altura(a->dir));

	int fb = pegaBalanceamento(a);

	if(fb > 1 && r->numeroatendimento < a->esq->reg.numeroatendimento)
	{
		return rotacaoDireita(a);
	}

	if(fb < -1 && r->numeroatendimento > a->dir->reg.numeroatendimento)
	{
		return rotacaoEsquerda(a);
	}

	if(fb > 1 && r->numeroatendimento > a->esq->reg.numeroatendimento)
	{
		a->esq = rotacaoEsquerda(a->esq);
		return rotacaoDireita(a);
	}

	if(fb < -1 && r->numeroatendimento < a->dir->reg.numeroatendimento)
	{
		a->dir = rotacaoDireita(a->dir);
		return rotacaoEsquerda(a);
	}

	return a;
}

//Criar �rvore com um novo n�, com o registro a ser armazenado.
arvore* novoNo(Reg *r)
{
	arvore* p = (arvore*)malloc(sizeof(arvore));
	p->reg = *r;
	p->esq = NULL;
	p->dir = NULL;
	p->altura = 1;
	return p;
}

//Pegar o m�ximo valor entre dois inteiros, para definir a altura de uma �rvore ou sub�rvore.
int max(int a, int b)
{
	return (a > b) ? a : b;
}

//Encontrar o valor m�nimo na �rvore.
arvore* min(arvore* a)
{
	arvore* atual = a;
	while(atual->esq != NULL)
	{
		atual = atual->esq;
	}
	return atual;
}

//Encontrar a altura da �rvore.
int altura(arvore* a)
{
	if(a == NULL)
	{
		return 0;
	}
	return a->altura;
}

//Encontrar o fator de balanceamento do n�, para verificar se � necess�ria ou n�o uma rota��o.
int pegaBalanceamento(arvore* a)
{
	if(a == NULL)
	{
		return 0;
	}
	return altura(a->esq) - altura(a->dir);
}

//Fun��o respons�vel por rotacionar a �rvore/sub�rvore para a esquerda.
arvore* rotacaoEsquerda(arvore* x)
{
	arvore* y = x->dir;
	arvore* T2 = y->esq;

	y->esq = x;
	x->dir = T2;

	x->altura = max(altura(x->esq), altura(x->dir)) + 1;
	y->altura = max(altura(y->esq), altura(y->dir)) + 1;

	return y;
}

//Fun��o respons�vel por rotacionar a �rvore/sub�rvore para a direita.
arvore* rotacaoDireita(arvore* y)
{
	arvore* x = y->esq;
	arvore* T2 = x->dir;

	x->dir = y;
	y->esq = T2;

	y->altura = max(altura(y->esq), altura(y->dir)) + 1;
	x->altura = max(altura(x->esq), altura(x->dir)) + 1;

	return x;
}

//Pesquisar o atendimento na �rvore e imprimi-lo.
void arv_busca(arvore* a, int pesquisa)
{
	if(!arv_vazia(a))
	{
		if(pesquisa == a->reg.numeroatendimento)
		{
			cout << "Atendimento: " << a->reg.numeroatendimento << endl;
			cout << "Paciente: " << a->reg.nomepac << endl;
			cout << "M�dico: " << a->reg.nomemed << endl;
		}
		arv_busca(a->esq, pesquisa);
		arv_busca(a->dir, pesquisa);
	}
}

//Verificar se a �rvore est� vazia.
int arv_vazia(arvore* a)
{
	return a == NULL;
}