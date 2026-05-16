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
void düşmanekle(düşman **sayı, SDL_Texture* resim,int satır,int sutun) {
    int ilk_x = 80;
    int ilk_y = 50;
    int genislik = 45;
    int yukseklik = 45;
    int bosluk = 15;
    for(int i=0; i<satır; i++){
        for(int j=0;j<sutun;j++){
            düşman *yeni = (düşman*)malloc(sizeof(düşman));
            if (yeni == NULL) return;
            yeni->x = ilk_x + j * (genislik + bosluk);
            yeni->y = ilk_y + i * (yukseklik + bosluk);
            yeni->hız = 2;
            yeni->genislik = genislik;
            yeni->yukseklik = yukseklik;
            yeni->Düşmanresmi = resim;
            yeni->sonraki = *sayı;
            *sayı = yeni;
        }
    }
}

static int yön = 1; 
void düşmanhareket(düşman *sayı,int *oyunDevamEdiyor){
    düşman *gecici = sayı;
    int duvar_sayacı = 0;

    while(gecici != NULL){
        if(yön==1 && gecici->x > 800 - gecici->genislik-20){
            duvar_sayacı=1;
            break;
        }
        else if(yön==-1 && gecici->x <20){
            duvar_sayacı=1;
            break;
        }
        gecici = gecici->sonraki;
    }
    if(duvar_sayacı){
        yön*=-1;
        gecici = sayı;
        while(gecici != NULL){
            gecici->y += 10;
            if (gecici->y + gecici->yukseklik >= 530) {
                *oyunDevamEdiyor = 0; 
                break;
            }
            gecici = gecici->sonraki;
        }
    }
    else{
        gecici = sayı;
        while(gecici != NULL){
            gecici->x += yön * gecici->hız;
            gecici = gecici->sonraki;
        }
    }
}

void düşmanateş(düşman *düşmanlar, mermi *düşman_mermiler) {
    if (düşmanlar == NULL) return;
    int aktif_mermi=0;
    for (int i = 0; i < MERMİ; i++) {
        if (düşman_mermiler[i].atış == 1) {
            aktif_mermi++;
        }
    }
    if (aktif_mermi >= 10) return;
     if (rand() % 100 != 0) return; 

    int toplam_dusman = 0;
    düşman *gecici = düşmanlar;
    while (gecici != NULL) {
        toplam_dusman++;
        gecici = gecici->sonraki;
    }

    if (toplam_dusman == 0) return;
    int ateş_eden_düşmanlar= 5;
    if (toplam_dusman < ateş_eden_düşmanlar) {
        ateş_eden_düşmanlar = toplam_dusman;
    }
    for (int i = 0; i < ateş_eden_düşmanlar; i++) {
        int hedef = rand() % toplam_dusman;
        gecici = düşmanlar;
        for (int j = 0; j < hedef; j++) {
            gecici = gecici->sonraki;
        }
        for (int k = 0; k < MERMİ; k++) {
            if (düşman_mermiler[k].atış == 0) {
                düşman_mermiler[k].x = gecici->x + gecici->genislik / 2;
                düşman_mermiler[k].y = gecici->y + gecici->yukseklik;
                düşman_mermiler[k].atış = 1;
                break;
            }
        }
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
void düşmanmermiyenile(mermi *mermiler) {
    for (int i = 0; i < MERMİ; i++) {
        if (mermiler[i].atış == 1) {
            mermiler[i].y += mermiler[i].hız; 
            if (mermiler[i].y > 600) mermiler[i].atış = 0;
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

    for (int i = 0; i < MERMİ; i++) {
        if (mermiler[i].atış == 0) continue;
        for(int j=0;j<MERMİ;j++){
            if (düşman_mermiler[j].atış==0) continue;
            if (mermiler[i].x < düşman_mermiler[j].x + düşman_mermiler[j].genislik &&
                mermiler[i].x + mermiler[i].genislik > düşman_mermiler[j].x &&
                mermiler[i].y < düşman_mermiler[j].y + düşman_mermiler[j].yukseklik &&
                mermiler[i].y + mermiler[i].yukseklik > düşman_mermiler[j].y) {
                
                mermiler[i].atış = 0; 
                düşman_mermiler[j].atış = 0;
                break;
            }
        }
        
    }
}