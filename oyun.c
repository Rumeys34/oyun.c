
#include "oyun.h"
#include <stdio.h>
#define MERMİ 100

ekranlar ekran = girişekranı;

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
    
  
    
    SDL_Window* oyunkutusu = SDL_CreateWindow("oyun ekranı ", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* çizici = SDL_CreateRenderer(oyunkutusu, -1, SDL_RENDERER_ACCELERATED);
    SDL_Texture* arkaPlan = IMG_LoadTexture(çizici, "arkplan.jpg");
    SDL_Texture* düşmanResmi = IMG_LoadTexture(çizici, "düşman.png");
    SDL_Texture* can_resmi = IMG_LoadTexture(çizici, "can2.png");
    SDL_Texture* seviyekutusu = IMG_LoadTexture(çizici, "seviyekutusu3.png");
    SDL_Texture* b1_resmi = IMG_LoadTexture(çizici, "bariyer1.png");
    SDL_Texture* b2_resmi = IMG_LoadTexture(çizici, "bariyer2.png");
    SDL_Texture* b3_resmi = IMG_LoadTexture(çizici, "bariyer3.png");
    SDL_Texture* girişresmi= IMG_LoadTexture(çizici, "girişekranı.png");
    SDL_Texture* çıkışresmi= IMG_LoadTexture(çizici, "çıkışekranı.png");
    SDL_Texture* howtoplayresim = IMG_LoadTexture(çizici, "howtoplay.png");
    TTF_Font* font = TTF_OpenFont("retro.ttf", 32);

    SDL_Rect startbutonu = {.x=271, .y = 308, .w = 271, .h = 79};
    SDL_Rect howtoplay = {.x=281, .y = 415, .w = 247, .h = 60};
    SDL_Rect exitbutonu = {.x=279, .y = 468, .w = 247, .h = 78};
    SDL_Rect restartbutonu = {.x=260, .y = 272, .w = 273, .h = 58};
    SDL_Rect çıkışexitbutonu = {.x=258, .y = 188, .w = 279, .h = 62};
    SDL_Rect backbuton = {.x=250, .y = 520, .w = 300, .h = 60};
   
    bariyer bariyerler[4];
    bariyeryapma(bariyerler, 4);
   
   int seviye = 1;  
   int skor=0;           
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
       if (günceldurum == oyundurumu && ekran==oyunekranı){
        düşmanateş(düşmanlar, düşman_mermiler);
        }
        while (SDL_PollEvent(&olay)) {
            if (olay.type == SDL_QUIT) {
                oyunDevamEdiyor = 0;
            }

            if (olay.type == SDL_MOUSEBUTTONDOWN){
                if (olay.button.button == SDL_BUTTON_LEFT){
                    int farex=olay.button.x;
                    int farey=olay.button.y;

                    printf ("koordinatlar x=%d y = %d ",farex,farey);

                    if(ekran ==girişekranı){
                        if (farex >= startbutonu.x && farex<= startbutonu.x + startbutonu.w &&
                            farey >= startbutonu.y && farey<= startbutonu.y + startbutonu.h) {
                            ekran = oyunekranı;
                        }  
                        else if (farex >= howtoplay.x && farex <= howtoplay.x + howtoplay.w &&
                                 farey >= howtoplay.y && farey <= howtoplay.y + howtoplay.h) {
                            ekran = nasıloynanırekranı ; 
                        }  
                        else if (farex >= exitbutonu.x && farex <= exitbutonu.x + exitbutonu.w &&
                                farey>= exitbutonu.y && farey <= exitbutonu.y + exitbutonu.h) {
                            oyunDevamEdiyor = 0;
                        }
                    }
                    else if (ekran == nasıloynanırekranı) {
                        if (farex >= backbuton.x && farex <= backbuton.x + backbuton.w &&
                            farey >= backbuton.y && farey <= backbuton.y + backbuton.h) {     
                            ekran = girişekranı; 
                        }
                    }           
                    
                       
                    else if (ekran == çıkışekranı) {
                        // YENİDEN BAŞLA butonuna basıldı mı
                        if (farex >= restartbutonu.x && farex <= restartbutonu.x + restartbutonu.w &&
                            farey >= restartbutonu.y && farey <= restartbutonu.y + restartbutonu.h) {
                            skor = 0;
                            seviye = 1;
                            anagemi.can = 5;
                            anagemi.x = 400;
                            düşmansil(&düşmanlar);
                            düşmanekle(&düşmanlar, düşmanResmi, seviye);
                            for (int i = 0; i < MERMİ; i++) {
                                mermiler[i].atış = 0;
                                düşman_mermiler[i].atış = 0;
                            }
                            bariyeryapma(bariyerler, 4);
                            ekran = oyunekranı;
                        }
                        // ÇIKIŞ butonuna basıldı mı?
                        else if (farex >= çıkışexitbutonu.x && farex <= çıkışexitbutonu.x + çıkışexitbutonu.w && 
                                farey >= çıkışexitbutonu.y && farey <= çıkışexitbutonu.y + çıkışexitbutonu.h) {
                            oyunDevamEdiyor = 0;
                        }
                    }
                }
            }
           
            if (olay.type == SDL_KEYDOWN && ekran == oyunekranı) {
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
        if (ekran == oyunekranı) {
            if (günceldurum==oyundurumu){
            düşmanhareket(düşmanlar);
            mermiyenile(mermiler);
            düşmanmermiyenile(düşman_mermiler);
            çarpışma(mermiler, &düşmanlar, düşman_mermiler, &anagemi, bariyerler, 4,&skor);
            
            if (anagemi.can <= 0) {
                ekran = çıkışekranı;
            }      
        } 
        //seviye
        if (düşmanlar == NULL && günceldurum == oyundurumu) {
            seviye++;        
            if (seviye %5 == 0){
                anagemi.can++;
            }

            for (int i = 0; i < MERMİ; i++) {
                mermiler[i].atış = 0;
                düşman_mermiler[i].atış = 0;
            }
            bariyeryapma(bariyerler, 4);
            günceldurum = oyun_seviye_atlama;
            başlangıç_zamanı = SDL_GetTicks();
        } 
        if (günceldurum == oyun_seviye_atlama) {
            if (SDL_GetTicks() - başlangıç_zamanı > 1000) {
                düşmanekle(&düşmanlar, düşmanResmi, seviye);
                günceldurum = oyundurumu;
            }  
        } 
    } 
      //çizimler
      SDL_RenderClear(çizici);

      if (ekran == girişekranı) {
        girişçiz(çizici, girişresmi);
      }
      else if (ekran == nasıloynanırekranı){
        howtoplayçiz(çizici,howtoplayresim);
      }
      else if (ekran == çıkışekranı) {
        çıkışçiz(çizici, çıkışresmi);
        çıkışskor(çizici, font, skor);
      }
      
    else if (ekran == oyunekranı) {  
        arkaplançiz(arkaPlan,çizici);
        if (günceldurum == oyundurumu) {
            mermiçiz(mermiler,çizici);
            mermiçiz(düşman_mermiler, çizici);
            gemiçiz(anagemi,çizici);
            düşmançiz(düşmanlar,çizici);
            bariyerçizme(bariyerler, 4, çizici, b1_resmi, b2_resmi, b3_resmi);
            cançiz(çizici, can_resmi, anagemi.can);
            skorçiz(çizici,font,skor);
        }
      
      else if (günceldurum == oyun_seviye_atlama) {
        SDL_SetRenderDrawBlendMode(çizici, SDL_BLENDMODE_BLEND);
        SDL_SetRenderDrawColor(çizici, 0, 0, 0, 150); 
        SDL_Rect kaplama = {0, 0, 800, 600};
        SDL_RenderFillRect(çizici, &kaplama);
        SDL_SetRenderDrawBlendMode(çizici, SDL_BLENDMODE_NONE);
        seviyeçiz(çizici, seviyekutusu, font, seviye);
        
      }
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
    SDL_DestroyTexture(howtoplayresim);
    SDL_DestroyTexture(b2_resmi);
    SDL_DestroyTexture(b3_resmi);
    TTF_CloseFont(font);
    SDL_DestroyTexture(girişresmi);
    SDL_DestroyTexture(çıkışresmi);
    for (int i = 0; i < MERMİ; i++) {
        SDL_DestroyTexture(mermiler[i].Mermiresmi);
        SDL_DestroyTexture(düşman_mermiler[i].Mermiresmi);
    }
    
    
    
       

    
    SDL_DestroyRenderer(çizici);
    SDL_DestroyWindow(oyunkutusu);
    TTF_Quit();
    IMG_Quit();
    SDL_Quit();


return 0;
} 

        
     
       
        
    

  