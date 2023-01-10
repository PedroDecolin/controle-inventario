CONTROLE DE INVENTARIO DE PCS

Este programa foi feito para a avaliação da disciplina de programação da minha graduação. 

O conceito básico é gerenciar os PCs de uma organização qualquer, por meio de algumas operações 
básicas (inserir, listar e excluir). As operações são feitas diretamente no terminal. Os dados são gravados e recuperados em um arquivo binário. Para 
o PC, foi definida uma estrutura Tinventario com determinados atributos, incluindo um numero de 
registro que é único e gerado sequencialmente.

O programa conta com 7 funções:

    1) Inserir informações dos PCs: pergunta ao utilizador quantos PCs quer inserir e coleta os 
    atributos de cada PC, guardando-os em um vetor de estruturas;

    2) Listar todos os PCs: lista todos os atributos dos PCs recentemente inseridos (item 1) ou 
    recuperados do arquivo binário;

    3) Lista PCs por categoria: realiza a mesma função do item 2, porém filtrando os PCs conforme sua 
    categoria (Desktop, Portatil ou Servidor);

    4) Remover PC por numero de registro: coleta do usuário um numero de registro e o exclui do 
    ficheiro indicado;

    5) Gravar registros de PCs no arquivo: pergunta ao utilizador o nome do ficheiro a ser gravado, e 
    grava todos os registros coletados no item 1. Se o arquivo não existir, ele o cria. Se existir, 
    ele o edita;

    6) Ler registros de ficheiro: copia as informações de PCs contidas no arquivo indicado para um 
    vetor de estruturas;

    0) Sair

Quaisquer indicações de melhoria, fico à disposição! :)