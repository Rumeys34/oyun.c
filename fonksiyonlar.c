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
    yeni->hız = 1 + (rand() % 1);
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
 
void düşmanateş(düşman *düşmanlar, mermi *mermiler) {
    düşman *gecici = düşmanlar;
    while (gecici != NULL) {
        if (rand() % 250==0) { // Her 250 frame'de bir düşman ateş eder
            for (int i = 0; i < MERMİ; i++) {
                if (mermiler[i].atış == 0) {
                    mermiler[i].x = gecici->x + gecici->genislik / 2;
                    mermiler[i].y = gecici->y + gecici->yukseklik;
                    mermiler[i].atış = 1;
                    mermiler[i].hız = 1 + rand() % 2;
                    break;
                }
            }
        }

        gecici = gecici->sonraki;  
    }
}

void düşmanmermiyenile(mermi *mermiler) {
    for (int i = 0; i < MERMİ; i++) {
        if (mermiler[i].atış == 1) {
            mermiler[i].y += mermiler[i].hız;
            if (mermiler[i].y > 600) {
                mermiler[i].atış = 0;
            }
        }
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

//çarpışma
void çarpışma (mermi *mermiler,düşman **düşmanlar,mermi *düşman_mermiler, gemi *anagemi, int *oyunDevamEdiyor) {
    for (int i =0;i<MERMİ;i++){
        if (mermiler[i].atış==0) continue;
        düşman *gecici = *düşmanlar;
        düşman *önceki = NULL;
        while (gecici != NULL) {
            if (mermiler[i].x < gecici->x + gecici->genislik &&
                mermiler[i].x + mermiler[i].genislik > gecici->x &&
                mermiler[i].y < gecici->y + gecici->yukseklik &&
                mermiler[i].y + mermiler[i].yukseklik > gecici->y) {
                
                mermiler[i].atış = 0; 
               
                if (önceki == NULL) {
                    *düşmanlar = gecici->sonraki;
                } else {
                    önceki->sonraki = gecici->sonraki;
                }
                free(gecici);
                break;
            }
            önceki = gecici;
            gecici = gecici->sonraki;
        }
    }
    for(int i=0;i<MERMİ;i++){
        if (düşman_mermiler[i].atış==1){
            if (düşman_mermiler[i].x < anagemi->x + anagemi->genislik &&
                düşman_mermiler[i].x + düşman_mermiler[i].genislik > anagemi->x &&
                düşman_mermiler[i].y < anagemi->y + anagemi->yukseklik &&
                düşman_mermiler[i].y + düşman_mermiler[i].yukseklik > anagemi->y) {
                
                düşman_mermiler[i].atış = 0; 
                anagemi->can--;
                if (anagemi->can <= 0) {
                    *oyunDevamEdiyor = 0;
                }
            }
        }
    }
}