#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tiro.h"
//private data... visible only by the functions below
struct tiro_privado
{
    char* name;
    int id_Obj;
    int n_Tiros[100];

};

//a "manual destructor"
void limpar_tiro()
{
    free(_atualTiro->tiroPrivado->name);
    free(_atualTiro->tiroPrivado);
    free(_atualTiro);

    puts("Personagem criado com sucesso !\n tchau");
}

//prints
void imprimir_tiro()
{
    printf("%s -: %d\n", _atualTiro->tiroPrivado->name,
         _atualTiro->tiroPrivado->id_Obj);
}

tiroA* novo_tiro(const char* name, int id_Obj)
{

    //Allocate the object
    tiroA* new = (tiroA*)malloc(sizeof(tiroA));
    new->tiroPrivado = (tiro_privado*)malloc(sizeof(tiro_privado));

    //Initialize the data
    new->tiroPrivado->name = (char*)malloc(strlen(name) * sizeof(char) + 1);
    strcpy(new->tiroPrivado->name, name);

    new->tiroPrivado->id_Obj = id_Obj;

    //Set the functions pointers
    new->imprimir = imprimir_tiro;
    new->limpar = limpar_tiro;

    return new;
}

//must call the objects with this function
tiroA* _(tiroA* obj)
{
    _atualTiro = obj;
    return obj;
}
