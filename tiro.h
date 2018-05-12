#ifndef TIRO_H_INCLUDED
#define TIRO_H_INCLUDED

//#ifndef PERSON_H__
//#define PERSON_H__

//Incomplete type declaration
typedef struct tiro_privado tiro_privado;

typedef struct tiroArray {
    //"privado" tiroPrivado.
    tiro_privado* tiroPrivado;

    //"class" functions
    void (*limpar)();
    void (*imprimir)();
} tiroA;

//instatiate a new person
tiroA* novo_tiro(const char*, int);

//pointer to the actual person in the context
tiroA* _atualTiro;

//sets the actual person
tiroA* _(tiroA* obj);

#endif
