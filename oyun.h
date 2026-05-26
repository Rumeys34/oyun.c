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

typedef enum {
    girişekranı,
    oyunekranı,
    nasıloynanırekranı,
    çıkışekranı
} ekranlar;
extern ekranlar ekran;




typedef struct {
   float x ,y ;
   int genislik, yukseklik;
   int çeşit;
   int yokolma;
   int can;
} bariyer ;

//fonksiyonlar
void mermiyenile( mermi *mermiler);
void mermiçiz( mermi *mermiler, SDL_Renderer *çizici);
void gemiçiz(gemi anagemi, SDL_Renderer *çizici);
void arkaplançiz(SDL_Texture *arkaPlan, SDL_Renderer *çizici);
void düşmançiz(düşman *sayı, SDL_Renderer *çizici);
void düşmanekle (düşman **sayı, SDL_Texture* resim,int seviye);
void düşmanhareket(düşman *sayı);
void düşmansil(düşman **sayı);
void düşmanateş(düşman *düşmanlar, mermi *düşman_mermiler);
void düşmanmermiyenile(mermi *mermiler);
void çarpışma (mermi *mermiler,düşman **düşmanlar,mermi *düşman_mermiler, gemi *anagemi, bariyer *bariyerler, int bariyersayısı,int *skor);
void cançiz(SDL_Renderer *çizici,SDL_Texture *can_resmi,int kalan_can);
void seviyeçiz(SDL_Renderer *çizici,SDL_Texture *seviyekutusu, TTF_Font *font,int seviye);
void bariyeryapma(bariyer *bariyerler, int sayı );
void bariyerçizme(bariyer *bariyerler,int sayı, SDL_Renderer *çizici, SDL_Texture *bariyer1,SDL_Texture *bariyer2,SDL_Texture *bariyer3);
void skorçiz(SDL_Renderer *çizici,TTF_Font *font,int skor);
void girişçiz(SDL_Renderer *çizici,SDL_Texture *girişresmi);
void çıkışçiz(SDL_Renderer *çizici,SDL_Texture *çıkışresmi );
void çıkışskor (SDL_Renderer *çizici,TTF_Font *font,int skor);
void howtoplayçiz(SDL_Renderer *çizici,SDL_Texture *howtoplayresim);
#endif 