#include "funcoes.c"

//Definicao de funcoes

//Verificacao de datas

int bissexto(int ano);

int ultimo(int mes, int ano);

int valida(int data[]);

//Funcionalidades do sistema

int menu();

int getNumRegistro();

void setNumRegistro(int quantidadePCs);

void inserePC(Tinventario *pcs, int quantidade);

void gravarPC(Tinventario pcs[], char nomeFicheiro[], int quantidade);

int lerPCs(Tinventario *pcs, char nomeFicheiro[]);

void imprimePCs(Tinventario *pcs, int quantidade, int opcao);

void deletarPC(Tinventario *pcs, char nomeFicheiro[], int registroAlvo);