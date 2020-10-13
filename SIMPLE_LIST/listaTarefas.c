#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <string.h>

typedef
    struct
    {
        char nomeTarefa     [31];
        char descricaoTarefa[51];

    }
    Tarefa;

typedef
    enum
    {
        CRIAR,
        LISTAR,
        EXCLUIR,
        SAIR
    }
    Opcao;

    unsigned int vazio (Tarefa tarefa)
{
    int   qtd   = 0, posicao;
    char* vetor = (char*)&tarefa;

    for (posicao=0; posicao<sizeof(tarefa); posicao++)
        if (vetor[posicao] != 0)
            qtd++;

    if (qtd==0)
        return 1;
    else
        return 0;
}

unsigned int filesize (FILE* mt)
{
    Tarefa tarefa;
    int posicao, retorno, posOriginal;

    posOriginal = ftell(mt);

    fseek (mt, 0, SEEK_END);
    posicao = ftell(mt)/sizeof(tarefa)-1;

    if (posicao==-1)
    {
        fseek (mt, posOriginal, SEEK_SET);
        return 0;
    }

    for (;;)
    {
        fseek (mt, posicao*sizeof(tarefa), SEEK_SET);
        fread (&tarefa, sizeof(tarefa), 1, mt);

        if (vazio(tarefa))
        {
            posicao--;
            if (posicao==-1)
            {
                fseek (mt, posOriginal, SEEK_SET);
                return 0;
            }
        }
        else
        {
            retorno = ftell(mt);
            fseek (mt, posOriginal, SEEK_SET);
            return retorno;
        }
    }

    retorno = ftell(mt);
    fseek (mt, posOriginal, SEEK_SET);
    return retorno;
}

unsigned int qtasTarefas (FILE* mt)
{
    return filesize(mt)/sizeof(Tarefa);
}

Opcao opcaoEscolhida (char** mnu, unsigned int qtdOpc)
{
    unsigned int opcAtual;
    char         opcDigitada;

    printf ("\n");

    for (opcAtual=0; opcAtual<qtdOpc; opcAtual++)
        printf ("%c) %s\n", 'a'+opcAtual, mnu[opcAtual]);

    printf ("\nSua Opcao? ");

    for(;;)
    {
        opcDigitada = getch();

        if (opcDigitada>='a' && opcDigitada<='a'+qtdOpc-1)
        {
            printf ("%c\n", opcDigitada);
            return opcDigitada-'a';
        }
        else
            if (opcDigitada>='A' && opcDigitada<='A'+qtdOpc-1)
            {
                printf ("%c\n", opcDigitada);
                return opcDigitada-'A';
            }
    }
}

void apresenteSe ()
{
    printf ("+------------------+\n");
    printf ("| LISTA DE TAREFAS |\n");
    printf ("+------------------+\n\n");
}

void criar (FILE* mt)
{
    Tarefa tarefa;

    printf ("\nNome da tarefa: ");
    gets   (tarefa.nomeTarefa);
    printf ("Descricao: ");
    gets   (tarefa.descricaoTarefa);

    fseek  (mt, 0, SEEK_END);
    fwrite (&tarefa, sizeof(Tarefa), 1, mt);
    printf("%u",qtasTarefas(mt));
}

void listar (FILE* mt)
{
    unsigned int posicao, qtd=qtasTarefas(mt);
    Tarefa tarefa;
    if (qtd == 0)
        printf ("\nLista Vazia!\n\n");
    else
        for (posicao=0; posicao<qtd; posicao++)
        {
            fseek (mt, posicao*sizeof(Tarefa), SEEK_SET);
            fread (&tarefa, sizeof(Tarefa), 1, mt);

            printf ("\nNome da Tarefa: %s", tarefa.nomeTarefa);
            printf ("\nDescricao da tarefa: %s\n\n", tarefa.descricaoTarefa);
        }
}

void excluir (FILE* mt)
{
    char nome [31];
    unsigned int posicao, qtd=qtasTarefas(mt);
    Tarefa tarefa;

    if (qtd == 0)
        printf ("\nLista Vazia!\n\n");
    else
    {
        printf ("\nNome da tarefa: ");
        gets   (nome);

        for (posicao=0; posicao<qtd; posicao++)
        {
            fseek (mt,posicao*sizeof(Tarefa),SEEK_SET);
            fread (&tarefa, sizeof(Tarefa), 1, mt);

            if (strcmp(nome,tarefa.nomeTarefa) == 0)
            {
                printf ("Descricao da tarefa\:  %s\n", tarefa.descricaoTarefa);
                break;
            }
        }

        if (posicao==qtd)
            printf ("Tarefa nao encontrada!\n\n");
        else
        {
            for (;posicao<qtd-1; posicao++)
            {
                fseek  (mt, (posicao+1)*sizeof(Tarefa), SEEK_SET);
                fread  (&tarefa, sizeof(Tarefa), 1, mt);
                fseek  (mt, posicao*sizeof(Tarefa), SEEK_SET);
                fwrite (&tarefa, sizeof(Tarefa), 1, mt);
            }

            printf ("%d\n", vazio(tarefa));
            memset (&tarefa, 0, sizeof(Tarefa));
            printf ("%d\n", vazio(tarefa));
            fwrite (&tarefa, sizeof(Tarefa), 1, mt);

            printf ("Informacoes excluidas com sucesso!\n\n");
        }
    }
}
int main(){
    static char* menu[4] = {
        "Criar tarefa",
        "Listar tarefas",
        "Excluir tarefas",
        "Sair do programa"
    };

    FILE* listaCompleta;
    Opcao opcao;
    apresenteSe();
    printf("\n", 'a');
    printf("\n", 'a' + 1);
    printf("\n", 'a' + 2);
    printf("\n", 'a' + 3);

    listaCompleta = fopen("lista.dados", "rb+");
    if(listaCompleta == NULL)
        listaCompleta == fopen("lista.dados", "wb+");

    do{
        opcao = opcaoEscolhida(menu,4);
        switch(opcao)
        {
            case CRIAR:
                criar(listaCompleta);
                break;
            case LISTAR:
                listar(listaCompleta);
                break;
            case EXCLUIR:
                excluir(listaCompleta);
        }
    }while(opcao != SAIR);
    fclose(listaCompleta);
}
