#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "tiro.h"

#define WIDTH 640
#define HEIGHT 480
#define velocidadeNave 4
#define max_Tiro 10

SDL_Window * window;
SDL_Renderer * render;
TTF_Font * text_font;
SDL_Event evento;
tiroA* person3[];
int contador_Nave = 0;
int i = 0;

typedef struct {
      SDL_Rect rect;
      int velX;
      int velY;
      int ativo;
} Sprite;


typedef struct {
int hp;
SDL_Rect rect1;
int velX1;
int velY1;
int ativoTiro[max_Tiro];
int ativo;
SDL_Texture * imagem;
SDL_Texture * image;
Sprite tiroNave [10];
} Objeto;

//Sprite tiroInimigo = {1,{-100,-100,64,64},0,+2,NULL,0,0};
//Sprite tiro = {0,{-100,-100,64,64},0,-5,NULL,0,0};
Objeto obj[];
//Sprite inimigo = {2,{240,100,64,64},1,0,NULL,1,50};
//Sprite nave = {3,{240,400,64,64},0,0,NULL,1,50};

//cria a janela
int iniciarVideo(){
   if(SDL_Init(SDL_INIT_EVERYTHING) >= 0){
   if(TTF_Init() >= 0){
    text_font = TTF_OpenFont("arial.ttf",32);
    if(text_font == NULL){
        printf("Erro ao carregar a font \n");
    }
    window = SDL_CreateWindow("N A V E",
                              100,100,WIDTH,HEIGHT,
                              SDL_WINDOW_SHOWN);
    if(window != NULL){
       render = SDL_CreateRenderer(window,-1,0);
       if(render != NULL){
        return 0;
       }
    }
   } else{
     printf("Erro ao iniciar a font \n");
   }
}
   return -1;
}

void criarOb(char imagem[],SDL_Rect * nv,int ati1,int vel_x1,int vel_y1,char image[],SDL_Rect * rt,int ati,int vel_x,int vel_y){



    SDL_Surface * surImage = IMG_Load(imagem);
    obj[contador_Nave].imagem = SDL_CreateTextureFromSurface(render, surImage);
    obj[contador_Nave].ativo = ati1;
    obj[contador_Nave].velX1=vel_x1;
    obj[contador_Nave].velY1=vel_y1;
    obj[contador_Nave].rect1 = *nv;
    SDL_Surface * suImage = IMG_Load(image);

    for(i = 0; i < max_Tiro ;i++){

    obj[contador_Nave].tiroNave[i].ativo = 0;
    obj[contador_Nave].tiroNave[i].rect = *rt;
    obj[contador_Nave].tiroNave[i].velX = 0;
    obj[contador_Nave].tiroNave[i].velY = -5;
    obj[contador_Nave].image = SDL_CreateTextureFromSurface(render, suImage);
    obj[contador_Nave].hp = 0;

    }
    SDL_FreeSurface(suImage);
}

iniciarImagens(){
 if(IMG_Init(IMG_INIT_JPG) == IMG_INIT_JPG){
    SDL_Rect nav = {240,400,64,64};
    SDL_Rect ret = {240,400,64,64};
    char nomeImagem[]= "imagens/nave.png";
    char nomeImage[]= "imagens/fire.png";
    criarOb(nomeImagem,&nav,1,0,0,nomeImage,&ret,0,0,-2);
    contador_Nave++;

    char nome[]= "teste";
    printf("%s",nome);


 }
 else{
    printf("Nao foi possivel iniciar a imagem");
 }
}

int moverSprite(Objeto * o,int testX,int testY){
    if(o->ativo){
    o->rect1.x += o->velX1;
    o->rect1.y += o->velY1;

    if(testX &&((o->rect1.x + o->rect1.w) > WIDTH || o->rect1.x < 0)){
        o->velX1 *= -1;
      }

      if(testY && ((o->rect1.y + o->rect1.h) > HEIGHT || o->rect1.y < 0)){
        o->velY1 *= -1;
      }

    }

}


int moverSpriteTiro(Objeto * o,int testX,int testY){
 for(i = 0; i < max_Tiro;i++){
    if(o->tiroNave[i].ativo){
    o->tiroNave[i].rect.x += o->tiroNave[i].velX;
    o->tiroNave[i].rect.y += o->tiroNave[i].velY;

    if(testX &&((o->tiroNave[i].rect.x + o->tiroNave[i].rect.w) > WIDTH || o->tiroNave[i].rect.x < 0)){
        o->tiroNave[i].velX *= -1;
      }

      if(testY && ((o->tiroNave[i].rect.y + o->tiroNave[i].rect.h) > HEIGHT || o->tiroNave[i].rect.y < 0)){
        o->tiroNave[i].velY *= -1;
      }

    }
 }
}


int pintarSpriteTiro(Objeto *o){

     if(o->ativo){
     int w1,h1;
     SDL_QueryTexture(o->imagem,NULL,NULL,&w1,&h1);
     SDL_Rect rOrig = {0,0,w1,h1};
     SDL_RenderCopy(render,o->imagem,&rOrig,&o->rect1);
     }

    for(i = 0; i < max_Tiro;i++){
     if(o->tiroNave[i].ativo){
     int w,h;
     SDL_QueryTexture(o->imagem,NULL,NULL,&w,&h);
     SDL_Rect rOrig1 = {0,0,w,h};
     SDL_RenderCopy(render,o->image,&rOrig1,&o->tiroNave[i].rect);
     }
    }

}

int calcularRegras(){

    int j;
//    moverSprite(&nave,velocidadeNave,velocidadeNave);
  //  moverSprite(&inimigo,1,1);
   // moverSprite(&tiro,0,0);
    //moverSprite(&tiroInimigo,0,0);
    moverSprite(&obj[0],0,0);
    for(j = 0; j < contador_Nave;j++){
      for(i = 0; i < max_Tiro;i++){
      moverSpriteTiro(&obj[j],0,0);
      }
    }
/*
    int meioX = inimigo.rect.x;
    if(!tiroInimigo.ativo && (meioX > nave.rect.x && meioX < nave.rect.x + 5)){
       tiroInimigo.ativo = 1;
       tiroInimigo.rect.x = meioX ;
       tiroInimigo.rect.y = inimigo.rect.y;
    }

    if(tiro.ativo && (tiro.rect.y + tiro.rect.h/2 < 0)){
        tiro.ativo = 0;
    }



    if(tiro.ativo && inimigo.ativo &&
        (SDL_HasIntersection(&tiro.rect,&inimigo.rect))){
         tiro.ativo = 0;
         inimigo.hp -= 5;
         //inimigo.ativo = 0;
            printf("HP: %d \n",inimigo.hp);
    }

    if(tiroInimigo.ativo && (tiroInimigo.rect.y > HEIGHT)){
        tiroInimigo.ativo = 0;
    }
*/



    for(j = 0; j < contador_Nave;j++){
      for(i = 0; i < max_Tiro;i++){
    if(obj[j].tiroNave[i].ativo && (obj[j].tiroNave[i].rect.y + obj[j].tiroNave[i].rect.h/2 < 0)){
        obj[j].tiroNave[i].ativo = 0;
     }


     int m;
     for(m = 0;m < contador_Nave;m++){
     if(obj[j].tiroNave[i].ativo && obj[m].ativo && (m!=j) &&
         (SDL_HasIntersection(&obj[j].tiroNave[i].rect,&obj[m].rect1))){
         obj[j].tiroNave[i].ativo = 0;
         obj[m].hp -= 5;
         //inimigo.ativo = 0;
            printf("HP: %d \n",obj[m].hp);
      }
     }
    }
}





}

void pintar(){
     SDL_SetRenderDrawColor(render,0,0,0,255);
     SDL_RenderClear(render);

     //pintar a nave
     //pintarSprite(&nave);
     //pintarSprite(&inimigo);


     if(contador_Nave != 0){

     int j;
      for(j = 0; j < contador_Nave;j++){
      for(i = 0; i < max_Tiro;i++){
       pintarSpriteTiro(&obj[j]);
        }
       }

     }

     //pintarSprite(&tiro);
     //pintarSprite(&tiroInimigo);
     SDL_RenderPresent(render);
}

void capturarEventos(){
     int haEventos = SDL_PollEvent(&evento);

     if(evento.type == SDL_QUIT){
            exit(0);
     }else if(evento.type == SDL_KEYDOWN){
      if(evento.key.keysym.sym == SDLK_LEFT){
       obj[0].velX1 = -velocidadeNave;
       }
       if(evento.key.keysym.sym == SDLK_RIGHT){
       obj[0].velX1 = velocidadeNave;
       }
       if(evento.key.keysym.sym == SDLK_UP){
       obj[0].velY1 = -velocidadeNave;
       }
       if(evento.key.keysym.sym == SDLK_DOWN){
       obj[0].velY1 = velocidadeNave;
       }


       if(evento.key.keysym.sym == SDLK_SPACE){


       for(i = 0; i < max_Tiro;i++){
            printf("tiro.");
            if(obj[0].tiroNave[i].ativo != 1){
       obj[0].tiroNave[i].ativo = 1;
       obj[0].tiroNave[i].rect.x = obj[0].rect1.x;
       obj[0].tiroNave[i].rect.y = obj[0].rect1.y - obj[0].rect1.h/2;
        break;
        }

       }

       }



     }
     else if(evento.type == SDL_KEYUP){
      if(evento.key.keysym.sym == SDLK_LEFT){
       obj[0].velX1 = 0;
       }
       if(evento.key.keysym.sym == SDLK_RIGHT){
       obj[0].velX1 = 0;
       }
       if(evento.key.keysym.sym == SDLK_UP){
       obj[0].velY1 = 0;
       }
       if(evento.key.keysym.sym == SDLK_DOWN){
       obj[0].velY1 = 0;
       }
     }
}

int main(int argc, char** args)
{
    iniciarVideo();
    iniciarImagens();



    tiroA* person1 = novo_tiro("Murilo", 21);
    tiroA* person2 = novo_tiro("Rovane", 47);
    person3[10] =  novo_tiro("Name", 22);
    //print
    _(person1)->imprimir();
    _(person2)->imprimir();
    _(person3[10])->imprimir();

    //free
    _(person1)->limpar();
    _(person2)->limpar();
    _(person3[10])->limpar();


    while(1){
        calcularRegras();
        pintar();
        capturarEventos();
        SDL_Delay(10);
    }

    getch();
    return 0;
}
