#ifndef OYUN_H
#define OYUN_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#define MERMİ 100


typedef struct mermi{
    float x, y;
    int atış;
    int genislik, yukseklik;
    float hız;
    SDL_Texture* Mermiresmi;

} mermi;

typedef struct {
    float x, y;
    int genislik, yukseklik;
    float hız;
    SDL_Texture* Gemi;
    int can;

} gemi;

typedef struct düşman{
    float x,y;
    int hız;
    int genislik, yukseklik;
    struct düşman* sonraki;
    SDL_Texture* Düşmanresmi;
}düşman;





//fonksiyonlar
void mermiyenile( mermi *mermiler);
void mermiçiz( mermi *mermiler, SDL_Renderer *çizici);
void gemiçiz(gemi anagemi, SDL_Renderer *çizici);
void arkaplançiz(SDL_Texture *arkaPlan, SDL_Renderer *çizici);
void düşmanekle(düşman **sayı, SDL_Texture* resim);
void düşmançiz(düşman *sayı, SDL_Renderer *çizici);
void düşmanhareket(düşman *sayı, int *oyunDevamEdiyor);
void düşmansil(düşman **sayı);
void düşmanateş(düşman *düşmanlar, mermi *mermiler);
void düşmanmermiyenile(mermi *mermiler);
void çarpışma (mermi *mermiler,düşman **düşmanlar,mermi *düşman_mermiler, gemi *anagemi, int *oyunDevamEdiyor);


#endif 