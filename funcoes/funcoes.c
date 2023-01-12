#include <stdio.h>
#include <string.h>
#define MAXSTR 50
#define MAXPCS 120

//Definição de estruturas
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

//Definição de funções

//Funções de verificação de data

int bissexto(int ano){
    // Recebe como parâmetro um ano. A função retorna 1 se o ano for bissexto e 0 senão for
    if (ano % 4 == 0){
        if (ano % 100 == 0){
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

int ultimo(int mes, int ano){
    // Recebe como parâmetro um mês e um ano. A função retorna o último dia do mês com base no ano
    if (mes >= 1 && mes <= 12){
        if (mes == 2){
            if (bissexto(ano))
                return 29;
            else
                return 28;
        }
        else{
            if (mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 10 || mes == 12)
                return 31;
            else
                return 30;
        }
    }
    else{
        printf("\nMes invalido!\n");
        return 0;
    }
}

int valida(int data[]){
    // Recebe como parâmetro um vetor de data. A função retorna 1 se for válida e 0 senão for
    if (data[2] > 0){
        if (data[1] >= 1 && data[1] <= 12){
            if (data[0] > 0 && data[0] <= ultimo(data[1], data[2]))
                return 1;
            else{
                return 0;
                printf("Data invalida");
            }
        }
        else{
            return 0;
            printf("Data invalida");
        }
    }
    else{
        return 0;
        printf("Data invalida");
    }
}


//Funcionalidades do sistema

char menu(){
    /*Imprime o menu e devolve uma opção inserida pelo usuário*/
    char opcao;
    printf("\n=====================MENU=====================\n");
    printf("[1] Inserir informacao dos PCs da organizacao\n");
    printf("[2] Listar todos os registros de PCs inseridos\n");
    printf("[3] Listar PCs por categoria\n");
    printf("[4] Remover PC por Numero de Registro\n");
    printf("[5] Gravar registros de PCs no ficheiro\n");
    printf("[6] Ler registros do Ficheiro e Mostrar\n");
    printf("[7] Ler do Ficheiro, Ordenar, Gravar e Mostrar\n");
    printf("[8] Calcular o Valor Estimado Total de todos os PCs registrados\n");
    printf("[0] Sair\n");
    scanf(" %c", &opcao);
    return opcao;
}

int getNumRegistro(){
    /*Recupera do arquivo "numRegistro.bin" o último número de registro inserido e retorna. Caso o 
    arquivo não exista, significa que não há nenhum registro. Portanto, neste caso retorna 0*/
    FILE *fp;
    int quantidadePCs;

    if((fp = fopen("numRegistro.bin", "rb")) == NULL){
        return 0;
    }
    else{
        fread(&quantidadePCs, sizeof(int), 1, fp);
    }
    fclose(fp);
    return quantidadePCs;
}

void setNumRegistro(int quantidadePCs){
    /*Recebe uma quantidade de PCs como parâmetro e grava no ficheiro "numRegistro.bin"*/
    FILE *fp;

    if((fp = fopen("numRegistro.bin", "wb")) == NULL){
        printf("Erro ao abrir o arquivo");
        return;
    }
    fwrite(&quantidadePCs, sizeof(int), 1, fp);
    fclose(fp);
}

void inserePC(Tinventario *pcs, int quantidade){
    /*Recebe como parâmetro um vetor de PCs e a quantidade de PCs. A função coleta as informações 
    individuais de cada PC, perguntando os valores dos atributos ao usuário, armazenando no vetor*/
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

void gravarPCs(Tinventario pcs[], char nomeFicheiro[], int quantidade){
    /*Recebe como parâmetro um vetor de PCs, o nome do ficheiro e a quantidade de PCS. A função grava 
    as informações do vetor no ficheiro indicado em modo de 'adição'. Caso ele não exista, é então 
    criado*/
    FILE *fp;

    if((fp = fopen(nomeFicheiro, "ab")) == NULL){
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    fwrite(pcs, sizeof(Tinventario), quantidade, fp);
    fclose(fp);
}

void reescreverPCs(Tinventario pcs[], char nomeFicheiro[], int quantidade){
    /*Recebe como parâmetro um vetor de PCs, o nome do ficheiro e a quantidade de PCS. A função grava 
    as informações do vetor no ficheiro indicado em modo de 'reescrita'. Caso ele não exista, é então 
    criado*/
    FILE *fp;

    if((fp = fopen(nomeFicheiro, "wb")) == NULL){
        printf("Erro ao abrir o arquivo\n");
        return;
    }

    fwrite(pcs, sizeof(Tinventario), quantidade, fp);
    fclose(fp);
}

int lerPCs(Tinventario *pcs, char nomeFicheiro[]){
    /*Recebe como parâmetro um vetor de PCs e o nome do ficheiro. A função copia as informações do
    ficheiro para o vetor, e retorna a quantidade de registros lidos*/
    FILE *fp;
    int i;

    if((fp = fopen(nomeFicheiro, "rb")) == NULL){
        printf("Erro ao abrir o arquivo!\n");
        return 0;
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

void mostrarPC(Tinventario pcs){
    /*Recebe como parâmetro uma estrutura de PC. Então, a imprime no terminal*/
    printf("\nNumero de Registro: %d", pcs.numeroRegistro);
    printf("\nNumero de Serie: %s", pcs.numeroSerie);
    printf("\nMarca: %s", pcs.marca);
    printf("\nProcessador: %s", pcs.processador);
    printf("\nQuantidade memoria RAM: %.1f", pcs.quantidadeMemoria);
    printf("\nEspaco em disco: %.1f", pcs.espacoDisco);
    printf("\nPreco de Custo: %.2f", pcs.precoCusto);
    printf("\nData de compra: [%d/%d/%d]", pcs.data[0], pcs.data[1], pcs.data[2]);
    printf("\nTipo PC: ");
    switch (pcs.tipoPc)
    {
        case Desktop: printf("Desktop\n"); break;
        case Portatil: printf("Portatil\n"); break;
        case Servidor: printf("Servidor\n"); break;
        default: break;
    }
}

void deletarPC(Tinventario *pcs, char nomeFicheiro[], int registroAlvo){
    /*Recebe como parâmetro um vetor de PCs, o nome do ficheiro e um registro alvo. A função lê o 
    ficheiro indicado e procura pelo registro alvo. Caso não encontre, sai da função. Caso encontre,
    define o registro para '0', e copia para um vetor auxiliar todos os registro exceto '0'. Este
    vetor auxiliar é então reescrito no ficheiro*/
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
    reescreverPCs(auxiliar, nomeFicheiro, quantidade);
    printf("\nRegistro %d deletado com sucesso!\n", registroAlvo);
}

void ordenarPCs(Tinventario pcs[], int quantidade, int crescente){
    /*Recebe como parâmetro um vetor de PCs, a quantidade de PCs e a opção 'crescente'. A função 
    ordena o vetor conforme o ano de compra do PC de forma crescente. Se a opção 'crescente' for 1, 
    a função deixa o vetor como está. Caso seja 0, ela inverte o vetor crescente, deixando-o na ordem 
    decrescente*/
    int i,j,min;
    Tinventario temp, reverso[quantidade];
    
    for(i = 0; i <= quantidade - 2; i++){
        min = i;
        
        for(j = i + 1; j <= quantidade - 1; j++)
            if(pcs[j].data[2] < pcs[min].data[2]) min=j;
        
        if(min != i){
            temp = pcs[min];
            pcs[min] = pcs[i];
            pcs[i] = temp;
        }
    }

    if(!crescente){
        j = quantidade -1;
        for (i = 0; i < quantidade; i++)
        {
            reverso[j] = pcs[i];
            j--;
        }
        for (i = 0; i < quantidade; i++) pcs[i] = reverso[i];
    }
}

int listarPCs(Tinventario *pcs, char nomeFicheiro[], int crescente){
    /*Recebe como parâmetro um vetor de PCs, o nome do ficheiro e a opção 'crescente'. A função lê
    o ficheiro indicado e se não houver registros, retorna '-1'. Caso haja registros, ordena na 
    ordem escolhida (1: crescente, 0: decrescente), depois imprime no terminal os PCs ordenados
    e retorna 1, indicano execução bem sucedida*/
    int quantidade = lerPCs(pcs, nomeFicheiro);
    if (quantidade == 0)
        return -1;
    ordenarPCs(pcs, quantidade, crescente);

    for (int i = 0; i < quantidade; i++)
    {
        printf("\nINFORMACOES PC %d", (i + 1));
        mostrarPC(pcs[i]);
    }
    return 1;
}

float calcularValorPCs(Tinventario *pcs, char nomeFicheiro[]){
    /*Recebe como parâmetro um vetor de PCs e o nome do ficheiro. A função lê o ficheiro e calcula
    o valor estimado de todos os PCs lidos, fazendo uma soma simples dos preços de custo. Essa soma
    é então retornada*/
    int quantidade = lerPCs(pcs, nomeFicheiro);

    float valorPCs = 0;
    for (int i = 0; i < quantidade; i++)
    {
        valorPCs += pcs[i].precoCusto;
    }
    return valorPCs;
}