
#include "oyun.h"
#include <stdio.h>
#define MERMİ 100


int main(void) {
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
     if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Hata: %s\n", SDL_GetError());
        return 1;
    }
    
   
    SDL_Texture* arkaPlan;
    SDL_Window* ekran= SDL_CreateWindow("oyun ekranı ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* çizici = SDL_CreateRenderer(ekran, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture* düşmanResmi = IMG_LoadTexture(çizici, "anagemi.png");

    
   düşman *düşmanlar = NULL; 
   
    // Gemi özelliklerini ayarlama
    gemi anagemi;
    anagemi.x = 400;
    anagemi.y = 520;
    anagemi.genislik = 140;
    anagemi.yukseklik = 100;
    anagemi.hız =20;
    anagemi.can = 5;
    
    //görselleri yükleme
    arkaPlan = IMG_LoadTexture(çizici, "arkplan2.jpg");
    anagemi.Gemi = IMG_LoadTexture(çizici, "anagemi1.png");
    SDL_Texture* can_resmi = IMG_LoadTexture(çizici, "can2.png");
    
    

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
    düşmanekle(&düşmanlar, düşmanResmi, 5, 10); // 5 satır, 10 sütun düşman ekle
    int oyunDevamEdiyor = 1;
    SDL_Event olay;
            
    while (oyunDevamEdiyor) {
        düşmanateş(düşmanlar, düşman_mermiler);

        while (SDL_PollEvent(&olay)) {
            if (olay.type == SDL_QUIT) {
                oyunDevamEdiyor = 0;
            }
           
            if (olay.type == SDL_KEYDOWN) {
                    switch (olay.key.keysym.sym) {
                       case SDLK_LEFT:
                            anagemi.x -= anagemi.hız;
                            if (anagemi.x < 0) {
                                anagemi.x = 0; 
                            }
                            break;
                        case SDLK_RIGHT:
                            anagemi.x += anagemi.hız;
                            if (anagemi.x > 730) {
                                anagemi.x = 730; 
                            }
                            break;
                        case SDLK_SPACE:
                            for (int i = 0; i < MERMİ; i++) {
                                if (mermiler[i].atış == 0) {
                                    mermiler[i].x = anagemi.x + anagemi.genislik / 2 ;
                                    mermiler[i].y = anagemi.y;
                                    mermiler[i].atış = 1;
                                    break;
                                }
                            }
                    }
                }
        }
        düşmanhareket(düşmanlar, &oyunDevamEdiyor);
        mermiyenile(mermiler);
        düşmanmermiyenile(düşman_mermiler);
        çarpışma(mermiler, &düşmanlar, düşman_mermiler, &anagemi, &oyunDevamEdiyor);
      
      
      //çizimler
        SDL_RenderClear(çizici);
        arkaplançiz(arkaPlan,çizici);
        mermiçiz(mermiler,çizici);
        mermiçiz(düşman_mermiler, çizici);
        gemiçiz(anagemi,çizici);
        düşmançiz(düşmanlar,çizici);
        cançiz(çizici, can_resmi, anagemi.can);

        SDL_RenderPresent(çizici);
        SDL_Delay(16); // Yaklaşık 60 FPS için 16 ms gecikme
    
    } 

    düşmansil(&düşmanlar);
    SDL_DestroyTexture(arkaPlan);
    SDL_DestroyTexture(düşmanResmi);
    SDL_DestroyTexture(anagemi.Gemi);
    SDL_DestroyTexture(can_resmi);
    for (int i = 0; i < MERMİ; i++) {
        SDL_DestroyTexture(mermiler[i].Mermiresmi);
    }
    for (int i = 0; i < MERMİ; i++) {
        SDL_DestroyTexture(düşman_mermiler[i].Mermiresmi);
    }    

    
    SDL_DestroyRenderer(çizici);
    SDL_DestroyWindow(ekran);
    IMG_Quit();
    SDL_Quit();


return 0;
} 

        
     
       
        
    

  