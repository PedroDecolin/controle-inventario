#include "funcoes.c"

//Definicao de funcoes

//Verificacao de datas

int bissexto(int ano);

int ultimo(int mes, int ano);

int valida(int data[]);

//Funcionalidades do sistema

char menu();

int getNumRegistro();

void setNumRegistro(int quantidadePCs);

void inserePC(Tinventario *pcs, int quantidade);

void gravarPCs(Tinventario pcs[], char nomeFicheiro[], int quantidade);

void reescreverPCs(Tinventario pcs[], char nomeFicheiro[], int quantidade);

int lerPCs(Tinventario *pcs, char nomeFicheiro[]);

void mostrarPC(Tinventario pcs);

void deletarPC(Tinventario *pcs, char nomeFicheiro[], int registroAlvo);

void ordenarPCs(Tinventario pcs[], int quantidade, int crescente);

int listarPCs(Tinventario *pcs, char nomeFicheiro[], int crescente);

float calcularValorPCs(Tinventario *pcs, char nomeFicheiro[]);