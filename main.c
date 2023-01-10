#include "funcoes/funcoes.h"

int main(){
    int opcao, opcaoPrint, quantidade, registroAlvo;
    Tinventario pcs[MAXPCS];
    char nomeFicheiro[MAXSTR];

    do
    {
        opcao = menu();
        switch (opcao)
        {
        case 1:
            do
            {
                printf("Insira a quantidade de PCs a inserir (max: 120):\n");
                scanf("%d", &quantidade);
                
                if (quantidade <= 0 || quantidade > 120)
                    printf("Quantidade inserida invalida!\n");
            } while (quantidade <= 0 || quantidade > 120);
            
            inserePC(pcs, quantidade);
            break;
        case 2:
            opcaoPrint = 4;
            if (quantidade > 0){
                imprimePCs(pcs, quantidade, opcaoPrint);
            }
            else{
                printf("Insira ao menos um registro!\n");
            }
            
            break;

        case 3:
            if (quantidade > 0){
                for (opcaoPrint = 1; opcaoPrint < 4; opcaoPrint++)
                {
                    switch (opcaoPrint)
                    {
                        case 1: printf("\n#DESKTOPS#\n"); break;
                        case 2: printf("\n#PORTATEIS#\n"); break;
                        case 3: printf("\n#SERVIDORES#\n"); break;
                        default:break;
                    }
                    imprimePCs(pcs, quantidade, opcaoPrint);
                }
            }
            else{
                printf("Insira ao menos um registro!\n");
            }
            break;

        case 4:
            do

            {
                printf("\nInsira o numero de registro a ser deletado: ");
                scanf("%d", &registroAlvo);
                
                if (registroAlvo <= 0)
                    printf("Numero de registro invalido!\n");
            } while (registroAlvo <= 0);
            printf("\nInsira o nome do ficheiro onde esta o registro: ");
            scanf("%s", &nomeFicheiro);

            deletarPC(pcs, nomeFicheiro, registroAlvo);
            break;

        case 5:
            if(quantidade > 0){
                printf("Insira o nome do ficheiro a ser gravado: ");
                scanf("%s", &nomeFicheiro);
                gravarPC(pcs, nomeFicheiro, quantidade);
            }
            else{
                printf("Insira ao menos um registro de PC!\n");
            }

            break;

        case 6:
            printf("Insira o nome do ficheiro a ser lido: ");
            scanf("%s", &nomeFicheiro);
            quantidade = lerPCs(pcs, nomeFicheiro);

            printf("\nTotal de PCs lidos: %d\n", quantidade);
            break;
        
        default:
            printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
    printf("Fim do programa!!\n");
    printf("Ate breve!!\n");
}