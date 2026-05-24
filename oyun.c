
#include "oyun.h"
#include <stdio.h>
#define MERMİ 100



int main(void) {
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
     if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Hata: %s\n", SDL_GetError());
        return 1;
    }
    if (TTF_Init() == -1) {
        printf("TTF_Init Hatası: %s\n", TTF_GetError());
        SDL_Quit();
        return 1;
    }
    
  
    
    SDL_Window* ekran= SDL_CreateWindow("oyun ekranı ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* çizici = SDL_CreateRenderer(ekran, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture* arkaPlan = IMG_LoadTexture(çizici, "arkplan.jpg");
    SDL_Texture* düşmanResmi = IMG_LoadTexture(çizici, "düşman.png");
    SDL_Texture* can_resmi = IMG_LoadTexture(çizici, "can2.png");
    SDL_Texture* seviyekutusu = IMG_LoadTexture(çizici, "seviyekutusu3.png");
    SDL_Texture* b1_resmi = IMG_LoadTexture(çizici, "bariyer1.png");
    SDL_Texture* b2_resmi = IMG_LoadTexture(çizici, "bariyer2.png");
    SDL_Texture* b3_resmi = IMG_LoadTexture(çizici, "bariyer3.png");
    TTF_Font* font = TTF_OpenFont("retro.ttf", 32);
   
    bariyer bariyerler[3];
    bariyeryapma(bariyerler, 3);
   
   int seviye = 1;             
   düşman* düşmanlar = NULL; 
   OyunDurumu günceldurum = oyundurumu;
   Uint32 başlangıç_zamanı = 0;
   
    // Gemi özelliklerini ayarlama
    gemi anagemi;
    anagemi.x = 400;
    anagemi.y = 520;
    anagemi.genislik = 140;
    anagemi.yukseklik = 100;
    anagemi.hız =20;
    anagemi.can = 5;
    anagemi.Gemi = IMG_LoadTexture(çizici, "anagemi.png");
    
   
    

    mermi mermiler[MERMİ];
    for (int i = 0; i < MERMİ; i++) {
        mermiler[i].atış = 0;
        mermiler[i].hız = 5;
        mermiler[i].genislik = 12;
        mermiler[i].yukseklik = 15;
        mermiler[i].Mermiresmi = IMG_LoadTexture(çizici, "mermi2.png");
    }
   
   mermi düşman_mermiler[MERMİ];
    for (int i = 0; i < MERMİ; i++) {
        düşman_mermiler[i].atış = 0;
        düşman_mermiler[i].hız = 2;
        düşman_mermiler[i].genislik = 12;
        düşman_mermiler[i].yukseklik = 15;
        düşman_mermiler[i].Mermiresmi = IMG_LoadTexture(çizici, "düşmanmermi.png");
    }
   
    
    
    

// Oyun döngüsü
    düşmanekle(&düşmanlar, düşmanResmi, seviye);
    int oyunDevamEdiyor = 1;
    SDL_Event olay;
            
    while (oyunDevamEdiyor) {
       if (günceldurum == oyundurumu ){
        düşmanateş(düşmanlar, düşman_mermiler);
        }
        while (SDL_PollEvent(&olay)) {
            if (olay.type == SDL_QUIT) {
                oyunDevamEdiyor = 0;
            }
           
            if (olay.type == SDL_KEYDOWN) {
                switch (olay.key.keysym.sym) {
                    case SDLK_LEFT:
                        if (günceldurum==oyundurumu){
                            anagemi.x -= anagemi.hız;
                            if (anagemi.x < 0) {
                                anagemi.x = 0; 
                            }
                        }
                    break;
                    case SDLK_RIGHT:
                        if (günceldurum==oyundurumu){
                            anagemi.x += anagemi.hız;
                            if (anagemi.x > 730) {
                                anagemi.x = 730; 
                            }
                        }
                    break;
                    case SDLK_SPACE:
                        if (günceldurum==oyundurumu){
                            for (int i = 0; i < MERMİ; i++) {
                                if (mermiler[i].atış == 0) {
                                    mermiler[i].x = anagemi.x + anagemi.genislik / 2 ;
                                    mermiler[i].y = anagemi.y;
                                    mermiler[i].atış = 1;
                                break;
                                }
                            }
                        }
                    break;
                }
            }
        }

        if (günceldurum==oyundurumu){
            düşmanhareket(düşmanlar, &oyunDevamEdiyor);
            mermiyenile(mermiler);
            düşmanmermiyenile(düşman_mermiler);
            çarpışma(mermiler, &düşmanlar, düşman_mermiler, &anagemi, &oyunDevamEdiyor, bariyerler, 3);
        } 
        //seviye
        if (düşmanlar == NULL) {
            seviye++;
            düşmanekle(&düşmanlar, düşmanResmi, seviye);

            if (seviye %5 == 0){
                anagemi.can++;
            }

            for (int i = 0; i < MERMİ; i++) {
                mermiler[i].atış = 0;
                düşman_mermiler[i].atış = 0;
            }
            bariyeryapma(bariyerler, 3);
            günceldurum = oyun_seviye_atlama;
            başlangıç_zamanı = SDL_GetTicks();
        } 
        if (günceldurum == oyun_seviye_atlama) {
            if (SDL_GetTicks() - başlangıç_zamanı > 1000) {
                günceldurum = oyundurumu;
            }  
        } 
       
      //çizimler
      SDL_RenderClear(çizici);
      arkaplançiz(arkaPlan,çizici);
      if (günceldurum == oyundurumu) {
        mermiçiz(mermiler,çizici);
        mermiçiz(düşman_mermiler, çizici);
        gemiçiz(anagemi,çizici);
        düşmançiz(düşmanlar,çizici);
        bariyerçizme(bariyerler, 3, çizici, b1_resmi, b2_resmi, b3_resmi);
        cançiz(çizici, can_resmi, anagemi.can);
      }
      else if (günceldurum == oyun_seviye_atlama) {
        SDL_SetRenderDrawBlendMode(çizici, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(çizici, 0, 0, 0, 150); 
        SDL_Rect kaplama = {0, 0, 800, 600};
        SDL_RenderFillRect(çizici, &kaplama);
        SDL_SetRenderDrawBlendMode(çizici, SDL_BLENDMODE_NONE);
        seviyeçiz(çizici, seviyekutusu, font, seviye);
        
      }
        SDL_RenderPresent(çizici);
        SDL_Delay(16); // Yaklaşık 60 FPS için 16 ms gecikme
    
    } 

    düşmansil(&düşmanlar);
    SDL_DestroyTexture(arkaPlan);
    SDL_DestroyTexture(düşmanResmi);
    SDL_DestroyTexture(anagemi.Gemi);
    SDL_DestroyTexture(can_resmi);
    SDL_DestroyTexture(seviyekutusu);
     SDL_DestroyTexture(b1_resmi);
    SDL_DestroyTexture(b2_resmi);
    SDL_DestroyTexture(b3_resmi);
    TTF_CloseFont(font);
    for (int i = 0; i < MERMİ; i++) {
        SDL_DestroyTexture(mermiler[i].Mermiresmi);
    }
    for (int i = 0; i < MERMİ; i++) {
        SDL_DestroyTexture(düşman_mermiler[i].Mermiresmi);
    }    

    
    SDL_DestroyRenderer(çizici);
    SDL_DestroyWindow(ekran);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();


return 0;
} 

        
     
       
        
    

  