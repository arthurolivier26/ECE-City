#include "header.h"




void initialisationAllegro()
{

    allegro_init();
    install_keyboard();
    install_mouse();
    set_color_depth(desktop_color_depth());
    if((set_gfx_mode(GFX_AUTODETECT_WINDOWED,W,H,0,0))!=0)
    {
        allegro_message("Pb de mode graphique") ;
        allegro_exit();
        exit(EXIT_FAILURE);
    }
}

int main() {
    initialisationAllegro();

    menu();



    return 0;
}END_OF_MAIN();



void menu()
{
    int choix = 0;
    BITMAP* page;
    BITMAP* fond;
    BITMAP* capitaliste;
    BITMAP* communiste;
    BITMAP* jouer_cap;
    BITMAP* jouer_com;
    BITMAP* charger_cap;
    BITMAP* charger_com;
    BITMAP* regle_cap;
    BITMAP* regle_com;

    t_partie* game;
    game = (t_partie*) malloc(sizeof(t_partie));

    //chargement des bitmap
    page = create_bitmap(SCREEN_W,SCREEN_H);
    fond = load_bitmap("C:\\Users\\guill\\Desktop\\info\\ing 2\\semestre1\\sim_city\\source_image_menu\\menu_fond.bmp",NULL);
    capitaliste = load_bitmap("C:\\Users\\guill\\Desktop\\info\\ing 2\\semestre1\\sim_city\\source_image_menu\\mode_cap.bmp",NULL);
    communiste = load_bitmap("C:\\Users\\guill\\Desktop\\info\\ing 2\\semestre1\\sim_city\\source_image_menu\\mode_com.bmp",NULL);
    jouer_cap = load_bitmap("C:\\Users\\guill\\Desktop\\info\\ing 2\\semestre1\\sim_city\\source_image_menu\\bouton_menu\\jouer_cap.bmp",NULL);
    charger_cap = load_bitmap("C:\\Users\\guill\\Desktop\\info\\ing 2\\semestre1\\sim_city\\source_image_menu\\bouton_menu\\charger_cap.bmp",NULL);
    regle_cap = load_bitmap("C:\\Users\\guill\\Desktop\\info\\ing 2\\semestre1\\sim_city\\source_image_menu\\bouton_menu\\regles_cap.bmp",NULL);
    jouer_com = load_bitmap("C:\\Users\\guill\\Desktop\\info\\ing 2\\semestre1\\sim_city\\source_image_menu\\bouton_menu\\jouer_com.bmp",NULL);
    charger_com = load_bitmap("C:\\Users\\guill\\Desktop\\info\\ing 2\\semestre1\\sim_city\\source_image_menu\\bouton_menu\\charger_com.bmp",NULL);
    regle_com = load_bitmap("C:\\Users\\guill\\Desktop\\info\\ing 2\\semestre1\\sim_city\\source_image_menu\\bouton_menu\\regles_com.bmp",NULL);


    if(fond==NULL)
    {
        printf("erreur lecture image\n");
    }


    while(!key[KEY_ESC])
    {
        choix = 0;
        clear(page);

        //printf("x::%d et y::%d\n",mouse_x,mouse_y);


        //premier rectangle


        /// affichage du fond du menu

        blit(fond,page,0,0,200,0,SCREEN_W,SCREEN_H);
        rectfill(page,0,0,200,768, makecol(redB,greenB,blueB));
        rectfill(page,824,0,1024,768, makecol(redR,greenR,blueR));
        blit(communiste,page,0,0,824,0,SCREEN_W,SCREEN_H);
        blit(capitaliste,page,0,0,0,0,SCREEN_W,SCREEN_H);
        ///affichage des bouton

        for(int i=0;i<3;i++)
        {
            /// mode capitaliste

            rect(page,20+i,275+i,180+i,325+i,makecol(255,0,0));
            rect(page,20+i,375+i,180+i,425+i,makecol(255,0,0));
            rect(page,20+i,475+i,180+i,525+i,makecol(255,0,0));
            /// mode communiste

            rect(page,844+i,275+i,999+i,325+i,makecol(0,0,255));
            rect(page,844+i,375+i,999+i,425+i,makecol(0,0,255));
            rect(page,844+i,475+i,999+i,525+i,makecol(0,0,255));
        }
        /// mode capitaliste

        masked_blit(jouer_cap,page,0,0,25,278,SCREEN_W,SCREEN_H);
        masked_blit(charger_cap,page,0,0,25,378,SCREEN_W,SCREEN_H);
        masked_blit(regle_cap,page,0,0,25,478,SCREEN_W,SCREEN_H);
        /// mode communiste

        masked_blit(jouer_com,page,0,0,849,278,SCREEN_W,SCREEN_H);
        masked_blit(charger_com,page,0,0,849,378,SCREEN_W,SCREEN_H);
        masked_blit(regle_com,page,0,0,849,478,SCREEN_W,SCREEN_H);

        ///selction du bouton

        
        /// mode cap
        if(mouse_x > 20 && mouse_x < 183)
        {
            if(mouse_y > 275 && mouse_y < 325)
            {
                for(int i=0;i<3;i++)
                {
                    rect(page,20+i,275+i,180+i,325+i,makecol(255,255,0));
                    choix = 1;
                }
            }
            if(mouse_y > 375 && mouse_y < 425)
            {
                for(int i=0;i<3;i++)
                {
                    rect(page,20+i,375+i,180+i,425+i,makecol(255,255,0));
                    choix = 2;
                }
            }

            if(mouse_y > 475 && mouse_y < 525)
            {
                for(int i=0;i<3;i++)
                {
                    rect(page,20+i,475+i,180+i,525+i,makecol(255,255,0));
                    choix = 3;
                }
            }
        }
        /// mode comm
        if(mouse_x > 844 && mouse_x < 1003)
        {
            if(mouse_y > 275 && mouse_y < 325)
            {
                for(int i=0;i<3;i++)
                {
                    rect(page,844+i,275+i,999+i,325+i,makecol(255,255,0));
                    choix = 4;
                }
            }
            if(mouse_y > 375 && mouse_y < 425)
            {
                for(int i=0;i<3;i++)
                {
                    rect(page,844+i,375+i,999+i,425+i,makecol(255,255,0));
                    choix = 5;
                }
            }

            if(mouse_y > 475 && mouse_y < 525)
            {
                for(int i=0;i<3;i++)
                {
                    rect(page,844+i,475+i,999+i,525+i,makecol(255,255,0));
                    choix = 6;
                }
            }
        }

        ///lorsque on clique
        if((choix ==1|| choix==4) && mouse_b & 1)
        {
            while(mouse_b & 1)
            {
                rest(10);
            }
            debut_parti(game);
            if(choix == 1)game->typejeu = 1;
            if(choix == 4)game->typejeu = 2;
            ///on nomme sa ville
            saisie_nom_ville(game,page);
            printf("nom de la ville:: %s\n",game->nom);
            /// on lance le jeu
            jeu(game);

        }
        if(choix == 2 && mouse_b & 1)
        {
            while (mouse_b & 1)
            {
                rest(10);
            }
        }



        show_mouse(page);
        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    }
}

