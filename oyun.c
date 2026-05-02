
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <stdlib.h>
#include <stdio.h>






typedef struct {
    float x, y;
    int genislik, yukseklik;
    float hız;
    SDL_Texture* Gemi;

} gemi;
SDL_Texture* arkaPlan=NULL;


int main(int argc, char* argv[]) {
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
     if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Hata: %s\n", SDL_GetError());
        return 1;
    }

   

    SDL_Window* ekran= SDL_CreateWindow("oyun ekranı ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* çizici = SDL_CreateRenderer(ekran, -1, SDL_RENDERER_ACCELERATED);
    
   

   
    gemi anagemi;
    anagemi.x = 400;
    anagemi.y = 530;
    anagemi.genislik = 70;
    anagemi.yukseklik = 70;
    anagemi.hız =10;
    anagemi.Gemi = IMG_LoadTexture(çizici, "anagemi.png");
    arkaPlan = IMG_LoadTexture(çizici, "arkplan2.jpg");
    
    



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
                        default:
                            break;
                    }
                }
        }








        
         
        SDL_SetRenderDrawColor(çizici, 0, 0, 0, 255);
        SDL_RenderClear(çizici);

        if(arkaPlan) {
            SDL_RenderCopy(çizici, arkaPlan, NULL, NULL);
        } 
    

    
   
    
        SDL_Rect gemiögesi = { (int)anagemi.x, (int)anagemi.y, anagemi.genislik, anagemi.yukseklik };
        if (anagemi.Gemi != NULL) {
        SDL_RenderCopy(çizici, anagemi.Gemi, NULL, &gemiögesi);
        } 
        else {
        SDL_SetRenderDrawColor(çizici, 255, 255, 255, 255);
        SDL_RenderFillRect(çizici, &gemiögesi);
        }

        SDL_RenderPresent(çizici);
    
    } 
      
    SDL_DestroyRenderer(çizici);
    SDL_DestroyWindow(ekran);
    IMG_Quit();
    SDL_DestroyTexture(arkaPlan); 
    SDL_Quit();


    return 0;
} 

        
     
       
        
    

  