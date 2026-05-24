#ifndef OYUN_H
#define OYUN_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>

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
    float hız;
    int genislik, yukseklik;
    struct düşman* sonraki;
    SDL_Texture* Düşmanresmi;
}düşman;

typedef enum {
    oyundurumu,
    oyun_seviye_atlama
} OyunDurumu;

//fonksiyonlar
void mermiyenile( mermi *mermiler);
void mermiçiz( mermi *mermiler, SDL_Renderer *çizici);
void gemiçiz(gemi anagemi, SDL_Renderer *çizici);
void arkaplançiz(SDL_Texture *arkaPlan, SDL_Renderer *çizici);
void düşmançiz(düşman *sayı, SDL_Renderer *çizici);
void düşmanekle (düşman **sayı, SDL_Texture* resim,int seviye);
void düşmanhareket(düşman *sayı, int *oyunDevamEdiyor);
void düşmansil(düşman **sayı);
void düşmanateş(düşman *düşmanlar, mermi *düşman_mermiler);
void düşmanmermiyenile(mermi *mermiler);
void çarpışma (mermi *mermiler,düşman **düşmanlar,mermi *düşman_mermiler, gemi *anagemi, int *oyunDevamEdiyor);
void cançiz(SDL_Renderer *çizici,SDL_Texture *can_resmi,int kalan_can);
void seviyeçiz(SDL_Renderer *çizici,SDL_Texture *seviyekutusu, TTF_Font *font,int seviye);

#endif 