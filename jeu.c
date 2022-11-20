//
// Created by guill on 13/11/2022.
//
#include "header.h"

void debut_parti(t_partie* game)
{

    game->nbrBatiment = 0;
    game->nbrUsine = 0;
    game->argent=5000000;
    game->grille = (t_grille_flux**) malloc(20* sizeof(t_grille_flux*));
    for(int i=0;i<20;i++)
    {
        game->grille[i] = (t_grille_flux*) malloc(20* sizeof(t_grille_flux));
    }
    for(int i=0;i<20;i++)
    {
        for(int j=0;j<20;j++)
        {
            game->grille[i][j].value = 0;
        }
    }
    game->nb_graph=0;



}
void nouvelle_usine(t_partie* game,int type,int x,int y)
{
    game->nbrUsine++;
    game->nb_graph++;
    if(game->nbrUsine == 1)
    {
        game->tab_usine = (t_usine*)malloc(sizeof(t_usine));
    }
    else
    {
        game->tab_usine = (t_usine*) realloc(game->tab_usine,game->nbrUsine* sizeof(t_usine));
    }
    int i = game->nbrUsine-1;
    game->tab_usine[i].type = type;
    game->tab_usine[i].capacite_totale = 5000;
    game->tab_usine[i].capacite_utilise = 0;
    game->tab_usine[i].x = x;
    game->tab_usine[i].y = y;

    // on remplie la partie therorie des graph de la structure
    if(game->nb_graph==1)
    {
        game->mon_graph = (t_graph**) malloc(sizeof(t_graph*));
        game->mon_graph[i] =(t_graph*) malloc(sizeof(t_graph));
        game->mon_graph[i]->taille=0;
        game->mon_graph[i]->ordre=0;
    }
    else
    {
        game->mon_graph = (t_graph**) realloc(game->mon_graph,game->nb_graph* sizeof(t_graph*));
        game->mon_graph[i] =(t_graph*) malloc(sizeof(t_graph));
        game->mon_graph[i]->taille=0;
        game->mon_graph[i]->ordre=0;
    }



    //on remplie le tableau des different endroit de connection possible
    for(int j=x-1;j<x+1;x++)
    {
        for(int k=y-1;k<k+1;k++)
        {
            if(type ==2)game->grille[x][y].value = 2;
            if(type ==3)game->grille[x][y].value = 3;
        }
    }



}

void nouveau_batiment(t_partie* game,int temps,int x,int y)
{
    game->nbrBatiment++;

    if(game->nbrBatiment == 1)
    {
        game->tab_batiment = (t_batiment*) malloc(game->nbrBatiment* sizeof(t_batiment));

    }
    else
    {
        game->tab_batiment = (t_batiment*) realloc(game->tab_batiment,game->nbrBatiment* sizeof(t_batiment));
    }
    int i = game->nbrBatiment-1;
    game->tab_batiment[i].niveau =0;
    game->tab_batiment[i].elec =0;
    game->tab_batiment[i].eau =0;
    game->tab_batiment[i].date_creation =temps;
    game->tab_batiment[i].x = x;
    game->tab_batiment[i].y = y;
    //on enregistre les infos du graph
    niveau_batiment(i,game->tab_batiment);

    // on remplie la partie therorie des graph de la structure


    //on remplie le tableau des different endroit de connection possible
    for(int j=x-1;j<x+1;x++)
    {
        for(int k=y-1;k<k+1;k++)
        {
            game->grille[x][y].value = 2;
        }
    }


}

void niveau_batiment(int i,t_batiment bat[i])
{
    FILE* fichier;
    fichier = fopen("C:\\Users\\guill\\Desktop\\info\\ing 2\\semestre1\\sim_city\\info_base.txt","r");

    if(fichier==NULL)
    {
        printf("erreur ouverture fichier\n");
    }
    else
    {

        int tempNum, tempHab;
        char tempNom[30];
        for (int j = 0; j < 30; j++) {
            tempNom[j] = 0;
        }

        for (int j = 0; i < 4; j++) {
            fscanf(fichier, "%d%s%d", &tempNum, &tempNom, &tempHab);

            if (tempNum == bat[i].niveau) {
                bat[i].nombre_habitant = tempHab;

                bat[i].nom = (char *) malloc((strlen(tempNom) + 1) * sizeof(char));
                strcpy(bat[i].nom, tempNom);

                break;
            }
        }

        fclose(fichier);
    }


}


int impot(t_partie* game)
{
    int somme = 0;
    if(game->nbrBatiment != 0) {

        for (int i = 0; i < game->nbrBatiment; i++) {
            somme = somme + (game->tab_batiment[i].nombre_habitant*10);
        }
    }
    printf("somme %d\n",somme);
    return somme;
}

void evolution(t_partie* game,int temps)
{
    int i;
    for(i=0;i<game->nbrBatiment;i++)
    {
        //mode capitalisme
        if(game->typejeu == 1)
        {
            // on augmente que avec le temps
            if((temps -game->tab_batiment[i].date_creation)%15 == 0)
            {
                game->tab_batiment[i].date_creation = 0;
                if(game->tab_batiment[i].niveau < 4)
                {
                    game->tab_batiment[i].niveau++;
                    niveau_batiment(i,game->tab_batiment);
                }
            }
        }
        //mode communiste
        if(game->typejeu == 2)
        {
            // on rajoute les condition pour valider les amelioration ici
            if((temps -game->tab_batiment[i].date_creation)%15 == 0 && game->tab_batiment[i].elec == game->tab_batiment[i].nombre_habitant && game->tab_batiment[i].eau ==  game->tab_batiment[i].nombre_habitant)
            {
                game->tab_batiment[i].date_creation = 0;
                if(game->tab_batiment[i].niveau < 4)
                {
                    game->tab_batiment[i].niveau = game->tab_batiment[i].niveau + 1;
                    niveau_batiment(i,game->tab_batiment);
                }
            }
        }


    }

}

void jeu(t_partie* game)
{
    int timeRef,timeB,init;
    int exit;

    init = time(NULL);
    timeRef = time(NULL)-init;
    int clk = 0;

    do
    {
        exit = 0;
        timeB = timeRef;
        timeRef = time(NULL)-init;
        // le temps en seconde
        if(timeB < timeRef)
        {
            clk++;
            //si il y a au moins 1 batiment on regarde si il peut evoluer
            if(game->nbrBatiment != 0)
            {
                evolution(game,clk);
            }
            //si on a passer 1 mois dans je jeu on recolte les impot
            if(clk%15 == 0)
            {
                printf("\n\n\nrecolte    \n\n\n");
                game->argent = game->argent + impot(game);
                printf("argent ville:: %d\n",game->argent);
            }
        }


        if(key[KEY_S])
        {
            while(key[KEY_S])rest(10);
            nouveau_batiment(game,clk,0,0);

        }

        if(key[KEY_D])
        {
            while(key[KEY_D])rest(10);
            for(int i=0;i<game->nbrBatiment;i++)
            {
                printf("%d nombre habitant\n",game->tab_batiment[i].nombre_habitant);
                printf("%s nom\n",game->tab_batiment[i].nom);
                printf("%d niveau\n",game->tab_batiment[i].niveau);
                printf("%d en eau \n",game->tab_batiment[i].eau);
                printf("%d elec \n",game->tab_batiment[i].elec);
                printf("\n\n\n");
            }
        }


        if(key[KEY_SPACE])
        {
            exit = 1;
        }

    } while (exit == 0);


}