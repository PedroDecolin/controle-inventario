#include <stdio.h>
#include <string.h>
#define MAXSTR 50
#define MAXPCS 120

//Definicao de estruturas
typedef enum{
    Desktop = 1, Portatil = 2, Servidor = 3
} TipoPc;

typedef struct {
    int numeroRegistro;
    char numeroSerie[MAXSTR], marca[MAXSTR], processador[MAXSTR];
    float quantidadeMemoria;
    float espacoDisco;
    float precoCusto;
    int data[3];
    TipoPc tipoPc;
} Tinventario;

//Definicao de funcoes

//Funcoes de verificacao de data

int bissexto(int ano)
{
    // funcao retorna 1 se o ano for bissexto e 0 senao for
    if (ano % 4 == 0)
    {
        if (ano % 100 == 0)
        {
            if (ano % 400 == 0)
                return 1;
            else
                return 0;
        }
        else
            return 1;
    }
    return 0;
}

int ultimo(int mes, int ano)
{
    // funcao retorna o ultimo dia do 'mes' com base no 'ano'
    if (mes >= 1 && mes <= 12)
    {
        if (mes == 2)
        {
            if (bissexto(ano))
                return 29;
            else
                return 28;
        }
        else
        {
            if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12)
                return 31;
            else
                return 30;
        }
    }
    else
    {
        printf("\nMes invalido!\n");
        return 0;
    }
}

int valida(int data[])
{
    // funcao retorna 1 se a data passada for valida, e 0 se nao for
    if (data[2] > 0)
    {
        if (data[1] >= 1 && data[1] <= 12)
        {
            if (data[0] > 0 && data[0] <= ultimo(data[1], data[2]))
                return 1;
            else
            {
                return 0;
                printf("Data invalida");
            }
        }
        else
        {
            return 0;
            printf("Data invalida");
        }
    }
    else
    {
        return 0;
        printf("Data invalida");
    }
}


//Funcionalidades do sistema

int menu(){
    int opcao;
    do
    {
        printf("\n=====================MENU=====================\n");
        printf("[1] Inserir informacao dos PCs da organizacao\n");
        printf("[2] Listar todos os registros de PCs inseridos\n");
        printf("[3] Listar PCs por categoria\n");
        printf("[4] Remover PCs por Numero de Registro\n");
        printf("[5] Gravar registros de PCs no ficheiro\n");
        printf("[6] Ler registros nos ficheiros\n");
        printf("[0] Sair\n");
        scanf("%d", &opcao);
    } while (opcao < 0 || opcao > 6);
    return (int) opcao;
}

int getNumRegistro(){
    FILE *fp;
    int quantidadePCs;

    if((fp = fopen("quantidadePCs.bin", "rb")) == NULL){
        return 0;
    }
    else{
        fread(&quantidadePCs, sizeof(int), 1, fp);
    }
    fclose(fp);
    return quantidadePCs;
}

void setNumRegistro(int quantidadePCs){
    FILE *fp;

    if((fp = fopen("quantidadePCs.bin", "wb")) == NULL){
        printf("Erro ao abrir o arquivo");
        return;
    }
    fwrite(&quantidadePCs, sizeof(int), 1, fp);
    fclose(fp);
}

void inserePC(Tinventario *pcs, int quantidade){
    int numRegistro = getNumRegistro();
    int auxTipoPc, auxData[3];

    for (int i = 0; i < quantidade; i++)
    {
        pcs[i].numeroRegistro = ++numRegistro;
        strcpy(pcs[i].numeroSerie, "Desconhecido");
        printf("INFORMACOES PC %d\n", (i + 1));
        printf("\nMarca: ");
        scanf("%s", &pcs[i].marca);
        printf("\nProcessador: ");
        scanf("%s", &pcs[i].processador);
        do
        {
            printf("\nQuantidade de Memoria (em GB): ");
            scanf("%f", &pcs[i].quantidadeMemoria);
            
            if(pcs[i].quantidadeMemoria <= 0)
                printf("Insira uma quantidade valida!\n");
        } while (pcs[i].quantidadeMemoria <= 0);
        do
        {
            printf("\nEspaco em disco (em GB): ");
            scanf("%f", &pcs[i].espacoDisco);
            
            if(pcs[i].espacoDisco <= 0)
                printf("Insira uma quantidade valida!\n");
        } while (pcs[i].espacoDisco <= 0);
        do
        {
            printf("\nPreco de custo: ");
            scanf("%f", &pcs[i].precoCusto);
            
            if(pcs[i].precoCusto <= 0)
                printf("Insira uma quantidade valida!\n");
        } while (pcs[i].precoCusto < 0);
        do
        {
            printf("\nData de compra (dd/mes/ano): ");
            scanf("%d/%d/%d", &auxData[0], &auxData[1], &auxData[2]);
            
            if(valida(auxData)){
                pcs[i].data[0] = auxData[0];
                pcs[i].data[1] = auxData[1];
                pcs[i].data[2] = auxData[2];
            }
            else
                printf("Insira uma data valida!");
        } while (!valida(auxData));
        do
        {
            printf("\nTipo PC (Desktop [1], Portatil [2], Servidor [3]): ");
            scanf("%d", &auxTipoPc);

            if (auxTipoPc < 1 || auxTipoPc > 3)
                printf("Insira um Tipo de PC valido!");
            else
                pcs[i].tipoPc = auxTipoPc;
            
        } while (auxTipoPc < 1 || auxTipoPc > 3);
    }

    setNumRegistro(numRegistro);
}

void gravarPC(Tinventario pcs[], char nomeFicheiro[], int quantidade){
    FILE *fp;
    strcat(nomeFicheiro, ".bin");

    if((fp = fopen(nomeFicheiro, "ab")) == NULL){
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    fwrite(pcs, sizeof(Tinventario), quantidade, fp);
    fclose(fp);
}

int lerPCs(Tinventario *pcs, char nomeFicheiro[]){
    FILE *fp;
    int i;
    strcat(nomeFicheiro, ".bin");

    if((fp = fopen(nomeFicheiro, "rb")) == NULL){
        printf("Erro ao abrir o arquivo!\n");
        return;
    }

    for (i = 0; i < MAXPCS; i++)
    {
        fread(&pcs[i], sizeof(Tinventario), 1, fp);
        if (pcs[i].numeroRegistro == 0){
            break;
        }
    }
    fclose(fp);
    return i;
}

void imprimePCs(Tinventario *pcs, int quantidade, int opcao){
    for (int i = 0; i < quantidade; i++)
    {
        if (pcs[i].tipoPc == opcao || opcao == 4){
            printf("\nINFORMACOES PC %d", (i + 1));
            printf("\nNumero de Registro: %d", pcs[i].numeroRegistro);
            printf("\nNumero de Serie: %s", pcs[i].numeroSerie);
            printf("\nMarca: %s", pcs[i].marca);
            printf("\nProcessador: %s", pcs[i].processador);
            printf("\nQuantidade memoria RAM: %.1f", pcs[i].quantidadeMemoria);
            printf("\nEspaco em disco: %.1f", pcs[i].espacoDisco);
            printf("\nPreco de Custo: %.2f", pcs[i].precoCusto);
            printf("\nData de compra: [%d/%d/%d]", pcs[i].data[0], pcs[i].data[1], pcs[i].data[2]);
            printf("\nTipo PC: ");
            switch (pcs[i].tipoPc)
            {
                case Desktop: printf("Desktop\n"); break;
                case Portatil: printf("Portatil\n"); break;
                case Servidor: printf("Servidor\n"); break;
                default: break;
            }
        }
    }
}

void deletarPC(Tinventario *pcs, char nomeFicheiro[], int registroAlvo){
    Tinventario auxiliar[MAXPCS];
    int quantidade = lerPCs(pcs, nomeFicheiro), verifica = 0;

    for (int i = 0; i < quantidade; i++)
    {
        if (pcs[i].numeroRegistro == registroAlvo){
            pcs[i].numeroRegistro = 0;
            verifica = 1;
            break;
        }
    }

    if(!verifica){
        printf("Registro %d nao encontrado\n", registroAlvo);
        return;
    }

    int j = 0;
    for (int i = 0; i < quantidade; i++)
    {
        if (pcs[i].numeroRegistro != 0){
            auxiliar[j] = pcs[i];
            j++;
        }
    }
    
    FILE *fp;

    if((fp = fopen(nomeFicheiro, "wb")) == NULL){
        printf("Erro ao abrir o arquivo!");
        return;
    }

    fwrite(auxiliar, sizeof(Tinventario), quantidade, fp);
    fclose(fp); 
}
