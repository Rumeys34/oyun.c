#include <SDL2/SDL.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
     if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Hata: %s\n", SDL_GetError());
        return 1;
    }
   

    SDL_Window* ekran= SDL_CreateWindow("oyun ekranı ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* çizici = SDL_CreateRenderer(ekran, -1, SDL_RENDERER_ACCELERATED);
   
    int oyunDevamEdiyor = 1;
    SDL_Event olay;
            
    while (oyunDevamEdiyor) {
    
         while (SDL_PollEvent(&olay)) {
            if (olay.type == SDL_QUIT) {
                oyunDevamEdiyor = 0;
            }
        }
            
    SDL_SetRenderDrawColor(çizici, 100, 250, 0, 0); 
    SDL_RenderClear(çizici);
    SDL_RenderPresent(çizici);
    }
      
      
    SDL_DestroyRenderer(çizici);
    SDL_DestroyWindow(ekran);
    SDL_Quit();

    return 0;
} 

        
     
       
        
    

  