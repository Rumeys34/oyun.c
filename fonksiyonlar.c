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


void cançiz(SDL_Renderer *çizici,SDL_Texture *can_resmi,int kalan_can) {
    if (can_resmi==NULL ||  kalan_can <= 0) return;
    int can_x = 750;
    int can_y = 20;
    int can_genislik = 25;
    int can_yukseklik = 25;
    int bosluk = 28;
    for (int i = 0; i < kalan_can; i++) {
        SDL_Rect can_ögesi = { can_x - (i * bosluk), can_y, can_genislik, can_yukseklik };
        SDL_RenderCopy(çizici, can_resmi, NULL, &can_ögesi);
    }
    
    
    
    
}

void seviyeçiz(SDL_Renderer *çizici,SDL_Texture *seviyekutusu, TTF_Font *font,int seviye) {
    if (seviyekutusu == NULL || font == NULL) return;

    SDL_Rect kutukonum={170,170,460,260};
    SDL_RenderCopy(çizici, seviyekutusu, NULL, &kutukonum);

    char seviye_metni[10];
    sprintf(seviye_metni, "%d", seviye);

    SDL_Color yazı_rengi = {0,240,255,255};
    SDL_Surface *yazı = TTF_RenderText_Solid(font, seviye_metni, yazı_rengi);
    if (yazı == NULL) return;

    SDL_Texture *yazı_kutusu = SDL_CreateTextureFromSurface(çizici, yazı);
    if (yazı_kutusu == NULL) {
        SDL_FreeSurface(yazı);
        return;
    }
    int yazı_genislik = 40;
    int yazı_yukseklik = 45;
    SDL_QueryTexture(yazı_kutusu, NULL, NULL, &yazı_genislik, &yazı_yukseklik);
     

    SDL_Rect yazı_konum;
    yazı_konum.x = kutukonum.x + (kutukonum.w - yazı_genislik) / 2;
    yazı_konum.y = kutukonum.y + 115;
    yazı_konum.w = yazı_genislik;
    yazı_konum.h = yazı_yukseklik;
    
    SDL_RenderCopy(çizici, yazı_kutusu, NULL, &yazı_konum);
   
    SDL_FreeSurface(yazı);
    SDL_DestroyTexture(yazı_kutusu);
}

void bariyerçizme(bariyer *bariyerler,int sayı, SDL_Renderer *çizici, SDL_Texture *b1,SDL_Texture *b2,SDL_Texture *b3) {
    for (int i = 0; i < sayı; i++) {
        if (bariyerler[i].yokolma == 1) {
            SDL_Rect r = { (int)bariyerler[i].x, (int)bariyerler[i].y, bariyerler[i].genislik, bariyerler[i].yukseklik };

            if (bariyerler[i].çeşit == 1) {
                SDL_RenderCopy(çizici, b1, NULL, &r);
            } 
            else if (bariyerler[i].çeşit == 2) {
                SDL_RenderCopy(çizici, b2, NULL, &r);
            } 
            else if (bariyerler[i].çeşit == 3) {
                SDL_RenderCopy(çizici, b3, NULL, &r);
            }
        }
        
    }
}


//düşman 
void düşmanekle(düşman **sayı, SDL_Texture* resim,int seviye) {
    int ilk_x = 50;
    int ilk_y = 40;
    int genislik = 45;
    int yukseklik = 40;
    int bosluk = 7;

    int satır =seviye;
    int sutun =6;
    float hız=3 + (seviye*0.5);
    for (int i = 0; i < satır; i++) {
        for (int j = 0; j < sutun; j++) {
            düşman *d = (düşman*)malloc(sizeof(düşman));
            if (d == NULL) return;
            d->x = ilk_x + j * (genislik + bosluk);

            if (i<3){
                d->y = ilk_y + i * (yukseklik + bosluk);
            }
            else{
                d->y = ilk_y - ((i-2) * (yukseklik + bosluk));
            }
            d->genislik = genislik;
            d->yukseklik = yukseklik;
            d->hız = hız;
            d->Düşmanresmi = resim;
            d->sonraki = *sayı;
            *sayı = d;
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
    if (aktif_mermi >= 8) return;
    if (rand() % 160 != 0) return; 

    int toplam_dusman = 0;
    düşman *gecici = düşmanlar;
    while (gecici != NULL) {
        toplam_dusman++;
        gecici = gecici->sonraki;
    }

    if (toplam_dusman == 0) return;
    int ateş_eden_düşmanlar= 3;
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
void çarpışma (mermi *mermiler,düşman **düşmanlar,mermi *düşman_mermiler, gemi *anagemi, int *oyunDevamEdiyor, bariyer *bariyerler, int bariyersayısı) {
  // gemi mermileri ile düşman çarpışması
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
    //düşman mermileri ile gemi çarpışması
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
// gemi mermileri ile düşman mermileri çarpışması
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
    // bariyer çarpışmaları
    for (int i = 0; i < bariyersayısı; i++) {
        if (bariyerler[i].yokolma == 0) continue;
        // gemi mermileri ile bariyer çarpışması
        for (int j = 0; j < MERMİ; j++) {
            //bizim mermiler çarptı mı 
            if(mermiler[j].atış ==1){
                if (mermiler[j].x < bariyerler[i].x + bariyerler[i].genislik &&
                    mermiler[j].x + mermiler[j].genislik > bariyerler[i].x &&
                    mermiler[j].y < bariyerler[i].y + bariyerler[i].yukseklik &&
                    mermiler[j].y + mermiler[j].yukseklik > bariyerler[i].y) {
                    
                    mermiler[j].atış = 0; 
                    bariyerler[i].can--;
                    if (bariyerler[i].can <= 0) {
                        bariyerler[i].yokolma = 0;
                    }
                }
            }
            //düşman mermileri çarptı mı
            if(düşman_mermiler[j].atış ==1){
                if (düşman_mermiler[j].x < bariyerler[i].x + bariyerler[i].genislik &&
                    düşman_mermiler[j].x + düşman_mermiler[j].genislik > bariyerler[i].x &&
                    düşman_mermiler[j].y < bariyerler[i].y + bariyerler[i].yukseklik &&
                    düşman_mermiler[j].y + düşman_mermiler[j].yukseklik > bariyerler[i].y) {
                    
                    düşman_mermiler[j].atış = 0; 
                    bariyerler[i].can--;
                    if (bariyerler[i].can <= 0) {
                        bariyerler[i].yokolma = 0;
                    }
                }
            }
           
            
        }
    }
}






// bariyer
void bariyeryapma(bariyer *bariyerler, int sayı ){
    int ilk_x = 90;
    int boşluk =190;

    for (int i = 0; i < sayı; i++) {
        bariyerler[i].x = ilk_x + (i * boşluk);
        bariyerler[i].y = 440;
        bariyerler[i].genislik = 40;
        bariyerler[i].yukseklik = 20;
        bariyerler[i].yokolma = 1;

        int rastgele = rand() % 3+1;
        bariyerler[i].çeşit = rastgele;
        bariyerler[i].can =rastgele;

    }
}



