#include "oyun.h"
#include <stdio.h>
#include <stdlib.h>


//çizim
void mermiçiz(mermi *mermiler, SDL_Renderer *çizici) {
      for (int i = 0; i < MERMİ; i++) {
            if (mermiler[i].atış == 1) {
                SDL_Rect mermiögesi = { (int)mermiler[i].x, (int)mermiler[i].y, mermiler[i].genislik, mermiler[i].yukseklik };
                if (mermiler[i].Mermiresmi != NULL) {
                    SDL_RenderCopy(çizici, mermiler[i].Mermiresmi, NULL, &mermiögesi);
                } 
                else {
                    SDL_SetRenderDrawColor(çizici, 255, 255, 255, 255);
                    SDL_RenderFillRect(çizici, &mermiögesi);
                }
            }
        }
}

void gemiçiz(gemi anagemi, SDL_Renderer *çizici) {
    SDL_Rect gemiögesi = { (int)anagemi.x, (int)anagemi.y, anagemi.genislik, anagemi.yukseklik };
        if (anagemi.Gemi != NULL) {
        SDL_RenderCopy(çizici, anagemi.Gemi, NULL, &gemiögesi);
        } 
        else {
        SDL_SetRenderDrawColor(çizici, 255, 255, 255, 255);
        SDL_RenderFillRect(çizici, &gemiögesi);
        }

}

void arkaplançiz(SDL_Texture *arkaPlan, SDL_Renderer *çizici) {
    if(arkaPlan) {
        SDL_RenderCopy(çizici, arkaPlan, NULL, NULL);
    } 
    else {
        SDL_SetRenderDrawColor(çizici, 0, 0, 0, 255);
        SDL_RenderClear(çizici);
    }
}

void düşmançiz(düşman *sayı, SDL_Renderer *çizici) {
    düşman *gecici = sayı;
    while (gecici != NULL) {
        if (gecici->Düşmanresmi != NULL) {
            SDL_Rect r = { (int)gecici->x, (int)gecici->y, gecici->genislik, gecici->yukseklik };
            SDL_RenderCopy(çizici, gecici->Düşmanresmi, NULL, &r);
        }
        gecici = gecici->sonraki;
    }
        
}



//düşman 
void düşmanekle(düşman **sayı, SDL_Texture* resim) {
    düşman *yeni = (düşman*)malloc(sizeof(düşman));
    if (yeni == NULL) return ;
    
    yeni->x = rand() % 750; 
    yeni->y = -50;
    yeni->hız = 1 + (rand() % 3);
    yeni->genislik = 50;
    yeni->yukseklik = 50;
    yeni->Düşmanresmi = resim;
    yeni->sonraki = *sayı;
    *sayı = yeni;
    
}

void düşmanhareket(düşman *sayı,int *oyunDevamEdiyor){
    düşman *gecici = sayı;
    while(gecici != NULL){
        gecici->y += gecici->hız;
        
        if(gecici->y>550){
            *oyunDevamEdiyor=0;
        }
        gecici=gecici->sonraki;
    }
}

void düşmansil(düşman **sayı) {
    while (*sayı != NULL) {
        düşman *gecici = *sayı;
        *sayı = (*sayı)->sonraki;
        free(gecici);
    }
}
 


//mermi
void mermiyenile(mermi *mermiler) {
     for (int i = 0; i < MERMİ; i++) {
            if (mermiler[i].atış == 1) {
                mermiler[i].y -= mermiler[i].hız;
                if (mermiler[i].y < 0) {
                    mermiler[i].atış = 0;
                }
            }
        }
}