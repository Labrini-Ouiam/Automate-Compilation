#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>

typedef struct transition{
    int etat_dep;
    char symb;
    int etat_arr;
}trans;

typedef struct automate{
    int nb_etats;
    int nb_alpha;
    char* alphabet;
    int etat_init;
    int nb_etats_fin;
    int* etats_fin;
    int nb_trans;
    trans* trans;
}afd;

afd lire_auto(){
    afd M;
    int i;
    printf("Donner le nombre des etats : ");
    scanf("%d",&M.nb_etats);
    printf("Donner le nombre des alphabets : ");
    scanf("%d",&M.nb_alpha);
    printf("Donner les alphabets : ");
    M.alphabet=(char*)malloc(M.nb_alpha*sizeof(char));
    scanf("%s",M.alphabet);
    printf("Donner l'etat initial : ");
    scanf("%d",&M.etat_init);
    printf("Donner le nombre des etats finaux : ");
    scanf("%d",&M.nb_etats_fin);
    M.etats_fin=(int*)malloc(M.nb_etats_fin*sizeof(int));
    for(i=0;i<M.nb_etats_fin;i++){
        printf("Donner l'etat final N°%d : ",i+1);
        scanf("%d",&M.etats_fin[i]);
    }
    printf("Donner le nombre de transitions : ");
    scanf("%d",&M.nb_trans);
    M.trans=(trans*)malloc(M.nb_trans*sizeof(trans));
    printf("Donner l'etat de depart, le symbole et l'etat d'arrive de chaque transition (Separe par des espaces) : \n");
    for(i=0;i<M.nb_trans;i++){
        printf("Transition N°%d : ",i+1);
        scanf("%d %c %d",&M.trans[i].etat_dep,&M.trans[i].symb,&M.trans[i].etat_arr);
    }
    return M;
}

int appartient(int etat, int* liste_etats, int taille){
    int i;
    for(i=0;i<taille;i++){
        if(etat==liste_etats[i])
            return 1;
    }
    return 0;
}

int* get_etats(afd M){
    int* liste_etat;
    int i;
    int j=0;
    liste_etat=(int*)malloc(M.nb_etats*sizeof(int));
    for(i=0;i<M.nb_trans;i++){
        if(appartient(M.trans[i].etat_dep,liste_etat,j)==0){
            liste_etat[j]=M.trans[i].etat_dep;
            j++;
        }
        if(appartient(M.trans[i].etat_arr,liste_etat,j)==0){
           liste_etat[j]=M.trans[i].etat_arr;
           j++;
        }
    }
    return liste_etat;
}

void afficher_auto(afd M){
    int i;
    int* liste_etat;
    printf("Voila l'automate !!! \n");
    printf("E= { ");
    liste_etat=get_etats(M);
    for(i=0;i<M.nb_etats;i++){
        printf("%d ",liste_etat[i]);
    }
    printf("} \n");
    printf("A= { ");
    i=0;
    while(M.alphabet[i]!='\0'){
        printf("%c ",M.alphabet[i]);
        i++;
    }
    printf("} \n");
    printf("I = %d \n",M.etat_init);
    printf("F= {");
    for(i=0;i<M.nb_etats_fin;i++){
        printf("%d ",M.etats_fin[i]);
    }
    printf("} \n");
    printf("Les transitions : \n");
    for(i=0;i<M.nb_trans;i++){
        printf("t(%d,%c) = %d \n",M.trans[i].etat_dep,M.trans[i].symb,M.trans[i].etat_arr);
    }
}

int accept(afd M, char* mot){
    int i, j, etat_courant;
    etat_courant=M.etat_init;
    i=0;
    while(mot[i]!='\0'){
        j=0;
        while(j<M.nb_trans){
            if(etat_courant==M.trans[j].etat_dep && mot[i]==M.trans[j].symb){
                etat_courant=M.trans[j].etat_arr;
                break;
            }
            j++;
        }
        if(j==M.nb_trans)
            return 0;
        i++;
    }
    if(appartient(etat_courant,M.etats_fin,M.nb_etats_fin)==1){
        return 1;
    }
    else
        return 0;
}
int main(){
    afd M;
    M=lire_auto();
    afficher_auto(M);
    if(accept(M,"abbc")){
        printf("accept1 \n");
    }
    else
        printf("rejet1 \n");
    if(accept(M,"ac")){
        printf("accept2 \n");
    }
    else
        printf("rejet2 \n");

return 0;
}
