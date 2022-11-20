//
// Created by guill on 02/11/2022.
//
#include "header.h"

void saisie_nom_ville(t_partie* game,BITMAP* page)
{
    char tempo[51]; //tableau temporaire
    int red,green,blue;
    int touche, touche1, touche2;
    int i;
    int xcoord = 512;
    int ycoord = 660;


    // declaration bitmap
    BITMAP* fond;
    BITMAP* image_com;
    BITMAP* image_cap;

    // on charge les bitmap
    fond = load_bitmap("C:\\Users\\guill\\Desktop\\info\\ing 2\\semestre1\\sim_city\\source_image_menu\\saisie_nom_ville_comu1.bmp",NULL);
    image_com = load_bitmap("C:\\Users\\guill\\Desktop\\info\\ing 2\\semestre1\\sim_city\\source_image_menu\\outils_com.bmp",NULL);
    image_cap = load_bitmap("C:\\Users\\guill\\Desktop\\info\\ing 2\\semestre1\\sim_city\\source_image_menu\\outils_cap.bmp",NULL);

    // test du chargement
    if(fond == NULL ||image_cap == NULL ||image_com == NULL)
    {
        printf("erreur lecture image saisie nom\n");

    }


    i = 0;
    for(int i = 0;i<51;i++)
    {
        tempo[i]=0;
    }
    clear_keybuf();

    while(!key[KEY_ENTER])
    {
        //    clear(page);
        blit(fond,page,0,0,0,0,SCREEN_W,SCREEN_H);

        switch (game->typejeu) {
            case 1:
            {
                red = redB;green=greenB;blue=blueB;
                break;
            }
            case 2:
            {
                red = redR;green=greenR;blue=blueR;
                break;
            }
        }
        rectfill(page,0,600,1024,768, makecol(red,green,blue));
        rectfill(page,xcoord-(8*i)-50,630,(xcoord+1)+(8*i)+50,700, makecol(255,255,0));
        show_mouse(page);
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
        ///on affiche l'entre du joueur

        textprintf(screen,font,xcoord-(8*i)-(50-(8*i)),ycoord,makecol(255,100,100),"VILLE: %s", tempo);
        touche = readkey();
        touche1 = touche & 0xFF;
        touche2 >> 8;

        if (( touche1 >31 && touche1<58) || ( touche1>64 && touche1<123))
        {
            tempo[i]=touche1;
            tempo[i+1]='_';
            i++;

        }
        if ( touche2 != key[KEY_BACKSPACE] )
        {
            printf("c bon\n");
            i--;
            if ( i<0 )i=0;
            tempo[i]= 0;
        }
        if(touche2 !=key[KEY_ENTER])
        {
            game->nom = (char*)malloc(strlen(tempo)*sizeof(char));
            for(int i=0;i< strlen(tempo);i++)
            {
                if(tempo[i]!='_')
                {
                    game->nom[i] = tempo[i];
                }
            }
        }
    }

}

void placerroute(t_partie* game,int x,int y)
{
    game->grille[x][y].value = 1;
}

void recherche_route_connecter(int* x,int* y,t_partie* game,int i)
{
    int j,sortie = 0;

    //on regarde en haut et en bas
    if(sortie==0)
    {
        for(j=game->tab_usine[i].x-1;j<game->tab_usine[i].x+1;j++)
        {
            if(game->grille[j][game->tab_usine[i].y-3].value == 1)
            {
                x = j;
                y = game->tab_usine[i].y+3;
                sortie = 1;

            }
            else if(sortie==1)
            {
                break;
            }
            else
            {
                sortie=0;
            }

            if(game->grille[j][game->tab_usine[i].y+3].value == 1)
            {
                x = j;
                y = game->tab_usine[i].y-4;
                sortie = 1;

            }
            else if(sortie==1)
            {
                break;
            }
            else
            {
                sortie=0;
            }
        }
    }
    if(sortie== 0)
    {
       for(j=game->tab_usine[i].y+3;j<game->tab_usine[i].y+2;j++)
       {
           if(game->grille[game->tab_usine[i].x-2][j].value== 1)
           {
               x = game->tab_usine[i].x-2;
               y= j;
               sortie=1;

           }
           else if(sortie==1)
           {
               break;
           }
           else
           {
               sortie=0;
           }
           if(game->grille[game->tab_usine[i].x+2][j].value== 1)
           {
               x = game->tab_usine[i].x+2;
               y= j;
               sortie=1;
           }
           else if(sortie==1)
           {
               break;
           }
           else
           {
               sortie=0;
           }
       }
    }
}


void chemin(t_partie* game)
{
    int i;
    int* x_debut,y_debut;
    x_debut = (int*)malloc(sizeof(int));
    y_debut = (int*) malloc(sizeof(int));

    for(i=0;i<game->nbrUsine;i++)
    {


    }


}


void creation_arrete(t_graph** graph,int i,int a,int b,int poid)
{
    graph[i]->taille++;
    if(graph[i]->taille == 1)
    {
        graph[i]->tabArrete = (t_arrete*)malloc(sizeof(graph[i]->taille));
    }
    else
    {
        graph[i]->tabArrete = (t_arrete*) realloc(graph[i]->tabArrete,graph[i]->taille* sizeof(t_arrete));
    }
    
    graph[i]->tabArrete[i].a = a;
    graph[i]->tabArrete[i].b = b;
    graph[i]->tabArrete[i].poid = poid;



}



