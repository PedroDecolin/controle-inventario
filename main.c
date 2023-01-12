#include "funcoes/funcoes.h"

int main(){
    int opcaoPrint, quantidade, registroAlvo, crescente;
    Tinventario pcs[MAXPCS];
    char nomeFicheiro[MAXSTR], opcao;

    do
    {
        opcao = menu();
        switch (opcao)
        {
        case '1':
        //Inserir informações de PCs da organização
            do
            {
                printf("Insira a quantidade de PCs a inserir (max: 120):\n");
                scanf("%d", &quantidade);
                
                if (quantidade <= 0 || quantidade > 120)
                    printf("Quantidade inserida invalida!\n");
            } while (quantidade <= 0 || quantidade > 120);
            
            inserePC(pcs, quantidade);
            break;
            
        case '2':
        //Listar todos os registros de PCs inseridos
            if (quantidade > 0){
                for (int i = 0; i < quantidade; i++)
                {
                    printf("\nINFORMACOES PC %d", (i + 1));
                    mostrarPC(pcs[i]);
                }
            }
            else{
                printf("Insira ao menos um registro!\n");
            }
            
            break;

        case '3':
        //Listar PCs por categoria
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
                    for (int i = 0; i < quantidade; i++)
                    {
                        if (pcs[i].tipoPc == opcaoPrint)
                            mostrarPC(pcs[i]);
                    }   
                }
            }
            else{
                printf("Insira ao menos um registro!\n");
            }
            break;

        case '4':
        //Remover PC por Número de Registro
            do
            {
                printf("\nInsira o numero de registro a ser deletado: ");
                scanf("%d", &registroAlvo);
                
                if (registroAlvo <= 0)
                    printf("Numero de registro invalido!\n");
            } while (registroAlvo <= 0);
            printf("\nInsira o nome do ficheiro onde esta o registro (.bin): ");
            scanf("%s", &nomeFicheiro);

            deletarPC(pcs, nomeFicheiro, registroAlvo);
            break;

        case '5':
        //Gravar registros de PCs no ficheiro
            if(quantidade > 0){
                printf("Insira o nome do ficheiro a ser gravado (.bin): ");
                scanf("%s", &nomeFicheiro);
                gravarPCs(pcs, nomeFicheiro, quantidade);
            }
            else{
                printf("Insira ao menos um registro de PC!\n");
            }

            break;

        case '6':
        //Ler registros do ficheiro e mostrar
            printf("Insira o nome do ficheiro a ser lido (.bin): ");
            scanf("%s", &nomeFicheiro);
            quantidade = lerPCs(pcs, nomeFicheiro);

            printf("\nTotal de PCs lidos: %d\n", quantidade);
            for (int i = 0; i < quantidade; i++)
            {
                printf("\nINFORMACOES PC %d", (i + 1));
                mostrarPC(pcs[i]);
            }
            break;

        case '7':
        //Ler do ficheiro, ordenar, gravar e mostrar
            printf("Insira o nome do ficheiro a ser lido (.bin): ");
            scanf("%s", &nomeFicheiro);

            do
            {
                printf("Insira a organizacao: [1] Crescente, [0] Decrescente: ");
                scanf("%d", &crescente);

                if(crescente < 0 || crescente > 1)
                    printf("Insira uma opcao valida!\n");
            } while (crescente < 0 || crescente > 1);
            

            // 1: lista em ordem crescente, 0: lista em ordem decrescente
            if (!(listarPCs(pcs, nomeFicheiro, crescente) == -1))
                reescreverPCs(pcs, nomeFicheiro, quantidade);

            break;

        case '8':
        //Calcular valor estimado total de todos os PCs registrados
            printf("Insira o nome do ficheiro a ser lido (.bin): ");
            scanf("%s", &nomeFicheiro);

            printf("O valor total dos PCs da organizacao é de: $%.2f", calcularValorPCs(pcs, nomeFicheiro));
            break;
        
        default:
        //Entrada inválida do usuário
            printf("Opcao invalida!\n");
            break;
        }
    } while (opcao != '0');
    printf("Fim do programa!!\n");
    printf("Ate breve!!\n");
}