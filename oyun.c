
#include "oyun.h"
#include <stdio.h>
#define MERMİ 100








SDL_Texture* arkaPlan=NULL;


int main(int argc, char* argv[]) {
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
     if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Hata: %s\n", SDL_GetError());
        return 1;
    }

   
  
    SDL_Window* ekran= SDL_CreateWindow("oyun ekranı ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* çizici = SDL_CreateRenderer(ekran, -1, SDL_RENDERER_ACCELERATED);
   

   // Gemi özelliklerini ayarlama
    gemi anagemi;
    anagemi.x = 400;
    anagemi.y = 530;
    anagemi.genislik = 70;
    anagemi.yukseklik = 70;
    anagemi.hız =20;
    
    //görselleri yükleme
    arkaPlan = IMG_LoadTexture(çizici, "arkplan2.jpg");
    anagemi.Gemi = IMG_LoadTexture(çizici, "anagemi.png");


    mermi mermiler[MERMİ];
    for (int i = 0; i < MERMİ; i++) {
        mermiler[i].atış = 0;
        mermiler[i].hız = 2;
        mermiler[i].genislik = 20;
        mermiler[i].yukseklik = 20;
        mermiler[i].Mermiresmi = IMG_LoadTexture(çizici, "mermi2.png");
    }
   
   
    
    
    

// Oyun döngüsü

    int oyunDevamEdiyor = 1;
    SDL_Event olay;
            
    while (oyunDevamEdiyor) {
    
        while (SDL_PollEvent(&olay)) {
            if (olay.type == SDL_QUIT) {
                oyunDevamEdiyor = 0;
            }

        

               if (olay.type == SDL_KEYDOWN) {
                    switch (olay.key.keysym.sym) {
                       case SDLK_LEFT:
                            anagemi.x -= anagemi.hız;
                            break;
                        case SDLK_RIGHT:
                            anagemi.x += anagemi.hız;
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

        mermiyenile(mermiler);
      
      
      //çizimler
        arkaplançiz(arkaPlan,çizici);
        mermiçiz(mermiler,çizici);
        gemiçiz(anagemi,çizici);
        






        
         
      

        
   
    
       

        SDL_RenderPresent(çizici);
    
    } 
      
    SDL_DestroyRenderer(çizici);
    SDL_DestroyWindow(ekran);
    IMG_Quit();
    SDL_DestroyTexture(arkaPlan); 
    SDL_Quit();


    return 0;
} 

        
     
       
        
    

  