/**
 *\file partie2.c
 *\author Emilien RAZAFIMAMPIANDRA
 *\brief Ce fichier contient les fonctions de la partie de Emilien RAZAFIMAMPIANDRA
 */

#include"demineur.h"


/**
 *\author Emilien RAZAFIMAMPIANDRA
 *\brief Cette fonction met toutes les valeurs de la matrice à zéro. La mise à zéro est nécessaire avant de mettre les différentes valeurs correspondant au nombre de mines et de voisins afin de ne pas avoir des résultats faussés
 *\param plateau la matrice
 *\param parametres les parametres de la matrice
*/
void Initialise(tableau plateau,parametre_grille parametres){
  int i,j;
  for(i=0;i<parametres->nb_lignes;i++)
    for(j=0;j<parametres->nb_colonnes;j++)
      plateau->matrice[i][j]=0;
}


/**
 *\author Emilien RAZAFIMAMPIANDRA
 *\brief Cette fonction a pour but de sélectionner des cases au hasard pour y poser une mine. Les cases qui contiennent des mines auront alors la valeur -1.
 *\param plateau la matrice
 *\param parametres les parametres de la matrice
*/
void Pose_mines(tableau plateau,parametre_grille parametres){
  int i,aleatoire1,aleatoire2;
  srand(time(NULL));
  for(i=0;i<parametres->nb_mines;i++){
    aleatoire1=rand()%parametres->nb_lignes;
    aleatoire2=rand()%parametres->nb_colonnes;
    if(plateau->matrice[aleatoire1][aleatoire2]!=-1)
      plateau->matrice[aleatoire1][aleatoire2]=-1;
    else
      i--;
  }
}



/**
 *\author Emilien RAZAFIMAMPIANDRA
 *\brief Après avoir posé les mines chaque case aura une valeur qu'on lui attribue qui correspond au nombre de mines qui lui est autour.
 *\param plateau la matrice
 *\param parametres les parametres de la matrice
*/

void Calcule_voisins(tableau plateau,parametre_grille parametres){
  int i,j;


  /*Numerotation d'une case dans le cas général, c'est-a-dire les cases possédant huit voisins */
  for(i=1;i<(parametres->nb_lignes)-1;i++)
    for(j=1;j<(parametres->nb_colonnes)-1;j++)
      if(plateau->matrice[i][j]==-1);
      else {
	if(plateau->matrice[i-1][j-1]==-1)
	  plateau->matrice[i][j]++;
	if(plateau->matrice[i-1][j]==-1)
	  plateau->matrice[i][j]++;
	if(plateau->matrice[i-1][j+1]==-1)
	  plateau->matrice[i][j]++;
	if(plateau->matrice[i][j-1]==-1)
	  plateau->matrice[i][j]++;
	if(plateau->matrice[i][j+1]==-1)
	  plateau->matrice[i][j]++;
	if(plateau->matrice[i+1][j-1]==-1)
	  plateau->matrice[i][j]++;
	if(plateau->matrice[i+1][j]==-1)
	  plateau->matrice[i][j]++;
	if(plateau->matrice[i+1][j+1]==-1)
	  plateau->matrice[i][j]++;
      }


  /*Numerotation de la première ligne excepté les extrémités*/
  for(j=1,i=0;j<(parametres->nb_colonnes)-1;j++)
    if(plateau->matrice[i][j]==-1);
    else {
	if(plateau->matrice[i][j-1]==-1)
	  plateau->matrice[i][j]++;
	if(plateau->matrice[i][j+1]==-1)
	  plateau->matrice[i][j]++;
	if(plateau->matrice[i+1][j-1]==-1)
	  plateau->matrice[i][j]++;
	if(plateau->matrice[i+1][j]==-1)
	  plateau->matrice[i][j]++;
	if(plateau->matrice[i+1][j+1]==-1)
	  plateau->matrice[i][j]++;
    }


  /*Numerotation de la dernière ligne excepté les extrémités*/
  for(j=1,i=(parametres->nb_lignes)-1;j<(parametres->nb_colonnes)-1;j++)
    if(plateau->matrice[i][j]==-1);
    else {
	if(plateau->matrice[i-1][j-1]==-1)
	  plateau->matrice[i][j]++;
	if(plateau->matrice[i-1][j]==-1)
	  plateau->matrice[i][j]++;
	if(plateau->matrice[i-1][j+1]==-1)
	  plateau->matrice[i][j]++;
	if(plateau->matrice[i][j-1]==-1)
	  plateau->matrice[i][j]++;
	if(plateau->matrice[i][j+1]==-1)
	  plateau->matrice[i][j]++;
    }


  /*Numerotation de la première colonne excepté les extrémités*/
  for(i=1,j=0;i<(parametres->nb_lignes)-1;i++)
    if(plateau->matrice[i][j]==-1);
    else {
	if(plateau->matrice[i-1][j]==-1)
	  plateau->matrice[i][j]++;
	if(plateau->matrice[i-1][j+1]==-1)
	  plateau->matrice[i][j]++;
	if(plateau->matrice[i][j+1]==-1)
	  plateau->matrice[i][j]++;
	if(plateau->matrice[i+1][j]==-1)
	  plateau->matrice[i][j]++;
	if(plateau->matrice[i+1][j+1]==-1)
	  plateau->matrice[i][j]++;
    }

  
  /*Numerotation de la dernière colonne excepté les extrémités*/
  for(i=1,j=(parametres->nb_colonnes)-1;i<(parametres->nb_lignes)-1;i++)
    if(plateau->matrice[i][j]==-1);
    else {
	if(plateau->matrice[i-1][j]==-1)
	  plateau->matrice[i][j]++;
	if(plateau->matrice[i-1][j-1]==-1)
	  plateau->matrice[i][j]++;
	if(plateau->matrice[i][j-1]==-1)
	  plateau->matrice[i][j]++;
	if(plateau->matrice[i+1][j-1]==-1)
	  plateau->matrice[i][j]++;
	if(plateau->matrice[i+1][j]==-1)
	  plateau->matrice[i][j]++;
    }


  /*Numerotation de la case sur l'extremité en haut à gauche*/
  i=0,j=0;
  if(plateau->matrice[i][j]==-1);
  else {
    if(plateau->matrice[i][j+1]==-1)
      plateau->matrice[i][j]++;
    if(plateau->matrice[i+1][j]==-1)
      plateau->matrice[i][j]++;
    if(plateau->matrice[i+1][j+1]==-1)
      plateau->matrice[i][j]++;
  }


  /*Numerotation de la case sur l'extremité en haut à droite */
  i=0,j=(parametres->nb_colonnes)-1;
  if(plateau->matrice[i][j]==-1);
  else {
    if(plateau->matrice[i][j-1]==-1)
      plateau->matrice[i][j]++;
    if(plateau->matrice[i+1][j-1]==-1)
      plateau->matrice[i][j]++;
    if(plateau->matrice[i+1][j]==-1)
      plateau->matrice[i][j]++;
  }


  /*Numerotation de la case sur l'etremité en bas à gauche */
  i=(parametres->nb_lignes)-1,j=0;
  if(plateau->matrice[i][j]==-1);
  else {
    if(plateau->matrice[i-1][j]==-1)
      plateau->matrice[i][j]++;
    if(plateau->matrice[i-1][j+1]==-1)
      plateau->matrice[i][j]++;
    if(plateau->matrice[i][j+1]==-1)
      plateau->matrice[i][j]++;
  }


  /*Numerotation de la case sur l'extremité en bas à droite*/
  i=(parametres->nb_lignes)-1,j=(parametres->nb_colonnes)-1;
  if(plateau->matrice[i][j]==-1);
  else {
    if(plateau->matrice[i-1][j]==-1)
      plateau->matrice[i][j]++;
    if(plateau->matrice[i-1][j-1]==-1)
      plateau->matrice[i][j]++;
    if(plateau->matrice[i][j-1]==-1)
      plateau->matrice[i][j]++; 
  }

}


/**
 *\author Emilien RAZAFIMAMPIANDRA
 *\brief Paramètre la grille de jeu à 9*9 cases contenant 10 mines.
 *\param parametres les parametres de la matrice
 */
void Facile(parametre_grille parametres){
  parametres->nb_lignes=9;
  parametres->nb_colonnes=9;
  parametres->nb_mines=10;
}


/**
 *\author Emilien RAZAFIMAMPIANDRA
 *\brief Paramètre la grille de jeu à 16*16 cases contenant 40 mines
 *\param parametres les parametres de la matrice
 */
void Moyen(parametre_grille parametres){
  parametres->nb_lignes=16;
  parametres->nb_colonnes=16;
  parametres->nb_mines=40;
}


/**
 *\author Emilien RAZAFIMAMPIANDRA
 *\brief Paramètre la grille de jeu à 16*30 cases contenant 99 mines
 *\param parametres les parametres de la matrice
 */
void Difficile(parametre_grille parametres){
  parametres->nb_lignes=16;
  parametres->nb_colonnes=30;
  parametres->nb_mines=99;
}


/**
 *\author Emilien RAZAFIMAMPIANDRA
 *\brief Créer une fenêtre de taille normalisée par le groupe pour afficher lesparamètres, c'est-à-dire les différents niveau disponibles.
 *\param parametres les parametres de la matrice 
*/

void Affichage_parametres(parametre_grille parametres){
  putenv("SDL_VIDEO_WINDOW_POS=center"); //Mise en place de la fenêtrre principale au centre de l'ecran
 
  SDL_Surface *ecran=NULL,*fond=NULL,*facile=NULL,*moyen=NULL,*difficile=NULL,*personalise=NULL,*menu=NULL,*texte_facile=NULL,*texte_moyen=NULL,*texte_difficile=NULL,*texte_personalise=NULL,*texte_menu=NULL;
  SDL_Rect pos_fond,pos_facile, pos_moyen, pos_difficile, pos_personalise,pos_menu,pos_texte_facile,pos_texte_moyen,pos_texte_difficile,pos_texte_personalise,pos_texte_menu;
  SDL_Event event;
  TTF_Font *police=NULL;
  SDL_Color texte_couleur={38,55,100};
  int continuer=1;

  /*Position de l'image de fond*/
  pos_fond.x=0;
  pos_fond.y=0;

  SDL_Init(SDL_INIT_VIDEO);// Chargement du système d'affichage
  TTF_Init();//Initialisation de la SDL_ttf

  ecran=SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);
  facile=SDL_CreateRGBSurface(SDL_HWSURFACE, LARGEUR, HAUTEUR,32,0,0,0,0);
  moyen=SDL_CreateRGBSurface(SDL_HWSURFACE, LARGEUR, HAUTEUR,32,0,0,0,0);
  difficile=SDL_CreateRGBSurface(SDL_HWSURFACE, 200, HAUTEUR,32,0,0,0,0);
  personalise=SDL_CreateRGBSurface(SDL_HWSURFACE, 300, HAUTEUR,32,0,0,0,0);
  menu=SDL_CreateRGBSurface(SDL_HWSURFACE, 350, HAUTEUR,32,0,0,0,0);

  SDL_WM_SetCaption("Paramètres", NULL);

  fond=IMG_Load("parametres.jpg");// Chargement de l'image de fond
  SDL_BlitSurface(fond, NULL, ecran, &pos_fond);


  //Coordonnées du bouton "Facile"
  pos_facile.x=(ecran->w)-(facile->w/0.20);
  pos_facile.y=(ecran->h/3.2)-(facile->h/5);
  SDL_FillRect(facile, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));
  SDL_SetColorKey(facile, SDL_SRCCOLORKEY, SDL_MapRGB(facile->format,255,255,255));// Mise en transparance du bouton
  SDL_BlitSurface(facile, NULL, ecran, &pos_facile);


  //Coordonnées du bouton "Moyen"
  pos_moyen.x=(ecran->w)-(moyen->w/0.20);
  pos_moyen.y=(ecran->h/2.3)-(moyen->h/5);
  SDL_FillRect(moyen, NULL, SDL_MapRGB(ecran->format, 255, 0, 255));
  SDL_SetColorKey(moyen, SDL_SRCCOLORKEY, SDL_MapRGB(moyen->format, 255, 0, 255));
  SDL_BlitSurface(moyen, NULL, ecran, &pos_moyen);


  //Coordonnées du bouton "Difficile"
  pos_difficile.x=(ecran->w)-(difficile->w/0.26);
  pos_difficile.y=(ecran->h/1.8)-(difficile->h/5);
  SDL_FillRect(difficile, NULL, SDL_MapRGB(ecran->format, 255, 255, 0));
  SDL_SetColorKey(difficile, SDL_SRCCOLORKEY, SDL_MapRGB(difficile->format, 255, 255, 0));
  SDL_BlitSurface(difficile, NULL, ecran, &pos_difficile);


  //Coordonnées du bouton "Personnalisé"
  pos_personalise.x=(ecran->w)-(personalise->w/0.39);
  pos_personalise.y=(ecran->h/1.5)-(personalise->h/5);
  SDL_FillRect(personalise, NULL, SDL_MapRGB(ecran->format, 0, 255, 255));
  SDL_SetColorKey(personalise, SDL_SRCCOLORKEY, SDL_MapRGB(personalise->format, 0, 255, 255));
  SDL_BlitSurface(personalise, NULL, ecran, &pos_personalise);


  //Coordonnées du bouton "Menu"
  pos_menu.x=(ecran->w)-(menu->w/0.455);
  pos_menu.y=(ecran->h/1.28)-(menu->h/5);
  SDL_FillRect(menu, NULL, SDL_MapRGB(ecran->format, 0, 0, 255));
  SDL_SetColorKey(menu, SDL_SRCCOLORKEY, SDL_MapRGB(menu->format, 0, 0, 255));
  SDL_BlitSurface(menu, NULL, ecran, &pos_menu);


  police=TTF_OpenFont("BlackAsylumDEMO-KCFonts.ttf", 50);
  TTF_SetFontStyle(police, TTF_STYLE_BOLD);
  texte_facile=TTF_RenderText_Solid(police, "Facile", texte_couleur);
  texte_moyen=TTF_RenderText_Solid(police, "Moyen", texte_couleur);
  texte_difficile=TTF_RenderText_Solid(police, "Difficile", texte_couleur);
  texte_personalise=TTF_RenderText_Solid(police, "Personalise", texte_couleur);
  texte_menu=TTF_RenderText_Solid(police, "Menu principal", texte_couleur);
  
  
  pos_texte_facile.x=(ecran->w)-(facile->w/0.20);
  pos_texte_facile.y=(ecran->h/3.2)-(facile->h/5);
  pos_texte_facile.w=texte_facile->w;
  pos_texte_facile.h=texte_facile->h;
  
  SDL_BlitSurface(texte_facile, NULL, ecran, &pos_texte_facile);
  
 

  pos_texte_moyen.x=(ecran->w)-(moyen->w/0.20);
  pos_texte_moyen.y=(ecran->h/2.3)-(moyen->h/5);
  pos_texte_moyen.w=texte_moyen->w;
  pos_texte_moyen.h=texte_moyen->h;
  
  SDL_BlitSurface(texte_moyen, NULL, ecran, &pos_texte_moyen);
 
 
  pos_texte_difficile.x=(ecran->w)-(difficile->w/0.26);
  pos_texte_difficile.y=(ecran->h/1.8)-(difficile->h/5);
  pos_texte_difficile.w=texte_difficile->w;
  pos_texte_difficile.h=texte_difficile->h;
  
  SDL_BlitSurface(texte_difficile, NULL, ecran, &pos_texte_difficile);
  

  pos_texte_personalise.x=(ecran->w)-(personalise->w/0.39);
  pos_texte_personalise.y=(ecran->h/1.5)-(personalise->h/5);
  pos_texte_personalise.w=texte_personalise->w;
  pos_texte_personalise.h=texte_personalise->h;
  
  SDL_BlitSurface(texte_personalise, NULL, ecran, &pos_texte_personalise);
  

  pos_texte_menu.x=(ecran->w)-(menu->w/0.455);
  pos_texte_menu.y=(ecran->h/1.28)-(menu->h/5);
  pos_texte_menu.w=texte_menu->w;
  pos_texte_menu.h=texte_menu->h;
  
  SDL_BlitSurface(texte_menu, NULL, ecran, &pos_texte_menu);
  
  

  SDL_FreeSurface(texte_facile);
  SDL_FreeSurface(texte_moyen);
  SDL_FreeSurface(texte_difficile);
  SDL_FreeSurface(texte_personalise);
  SDL_FreeSurface(texte_menu);
  TTF_CloseFont(police);
  
  SDL_Flip(ecran);


  //Gestion d'événement de la souris
  while(continuer){
    SDL_WaitEvent(&event);
    switch(event.type){
    case SDL_QUIT:
      continuer=0;
      break;

    case SDL_MOUSEBUTTONUP:
      parametres=malloc(sizeof(*parametres));
      if(event.button.x>(ecran->w)-(facile->w/0.20) && event.button.x<=(ecran->w)-(facile->w/0.20)+LARGEUR && event.button.y>(ecran->h/3.2)-(facile->h/5) && event.button.y<=(ecran->h/3.2)-(facile->h/5)+HAUTEUR){
	continuer=0;
	Facile(parametres);
	joue_apres_parametrage(parametres);
      }else
	if(event.button.x>(ecran->w)-(moyen->w/0.20) && event.button.x<=(ecran->w)-(moyen->w/0.20)+LARGEUR && event.button.y>(ecran->h/2.3)-(moyen->h/5) && event.button.y<=(ecran->h/2.3)-(moyen->h/5)+HAUTEUR){
	  continuer=0;
	  Moyen(parametres);
	  joue_apres_parametrage(parametres);
	}else
	  if(event.button.x>(ecran->w)-(difficile->w/0.26) && event.button.x<=(ecran->w)-(difficile->w/0.26)+200 && event.button.y>(ecran->h/1.8)-(difficile->h/5) && event.button.y<=(ecran->h/1.8)-(difficile->h/5)+HAUTEUR){
	    continuer=0;
	    Difficile(parametres);
	    joue_apres_parametrage(parametres);
	  }else
	    if(event.button.x>(ecran->w)-(menu->w/0.39) && event.button.x<=(ecran->w)-(menu->w/0.39)+355 && event.button.y>(ecran->h/1.5)-(menu->h/5) && event.button.y<=(ecran->h/1.5)-(menu->h/5)+HAUTEUR){
	      continuer=0;
	      personnalise(parametres);
	    }else
	      if(event.button.x>(ecran->w)-(menu->w/0.455) && event.button.x<=(ecran->w)-(menu->w/0.455)+355 && event.button.y>(ecran->h/1.28)-(menu->h/5) && event.button.y<=(ecran->h/1.28)-(menu->h/5)+HAUTEUR){
		continuer=0;
		Affichage_menu();
	      }else
		continuer=1;
      break;
    }
  }
}


/**
 *\author Emilien RAZAFIMAMPIANDRA
 *\brief Cette fonction crée une nouvelle grille en l'initialisant en posant les mines et en calculant le nombre de voisins; c'est la fonction qui permet de changer de plateau de jeu a chaque partie
 *\param plateau la matrice
 *\param parametres les parametres de la matrice
*/
void Nouvelle_grille(parametre_grille parametres,tableau plateau){
  Initialise(plateau,parametres);
  Pose_mines(plateau,parametres);
  Calcule_voisins(plateau,parametres);
}


/**
 *\author Emilien RAZAFIMAMPIANDRA
 *\brief Lors de l'unification des parties effectuées par chaque membre du groupe, il a été remarqué que certaines parties ne collaient pas ensemble, et  cette fonction permet alors de convertir un plateau donné sous une autre forme afin de créer une certaine compatibilité à chaque partie des membres du groupe
 *\param plateau la matrice
 *\param parametres les parametres de la matrice
*/
grille Conversion(parametre_grille parametres, tableau plateau){
  grille ma_grille;
  int valeurs[]={_MINE,_VIDE,_UN,_DEUX,_TROIS,_QUATRE,_CINQ,_SIX,_SEPT,_HUIT};
  int i,j;
  Nouvelle_grille(parametres,plateau);
  ma_grille = my_malloc(sizeof(*ma_grille));
  int nb_lignes=parametres->nb_lignes;
  int nb_colonnes=parametres->nb_colonnes;
  ma_grille->matrice = my_malloc(nb_lignes * sizeof(int*));
  for(i=0; i<nb_colonnes; i++)
  (ma_grille->matrice)[i] = my_malloc(nb_colonnes * sizeof(int));
  for(i=0;i<parametres->nb_lignes;i++)
    for(j=0;j<parametres->nb_colonnes;j++){
      if(plateau->matrice[i][j]==-1)
	ma_grille->matrice[i][j]=_MINE;
      else 
	if(plateau->matrice[i][j]==0)
	  ma_grille->matrice[i][j]=_VIDE;
	else
	  ma_grille->matrice[i][j]=valeurs[(plateau->matrice[i][j])+1];
    }
  return ma_grille;
}


/**
 *\author Emilien RAZAFIMAMPIANDRA
 *\brief Cette fonction permet d'ouvrir une grille de jeu apres avoir choisi le niveau de jeu souhaité
 *\param parametres les parametres de la matrice
 */
int joue_apres_parametrage(parametre_grille parametre){
  Context C=malloc(sizeof(*C));
  tableau plateau=malloc(sizeof(*plateau));
  grille ma_grille=Conversion(parametre,plateau);
  if (Init(C,800,600)!=0)   // init en 800*600 avec 10 sprites
    return -1;

  jouer(C,ma_grille,parametre);
  Release(C);
  return EXIT_SUCCESS; 
}


/**
 *\author Emilien RAZAFIMAMPIANDRA
 *\brief Etant donné l'inexistance de fonctions de saisie tel que scanf sur une fenêtre sdl, on récupère donc les données saisies par l'utilisateur sur le terminal, d'où l'utilité de cette fonction
 *\param parametres les parametres de la matrice   
 */

void personnalise(parametre_grille parametres){
  int nb_max_mines;
  while(parametres->nb_lignes<9 || parametres->nb_lignes>24){
    printf("\nVeuillez entrer le nombre de ligne désirée: ");
    scanf("%d",&parametres->nb_lignes);
    clean_stdin();
  }
  while(parametres->nb_colonnes<9 || parametres->nb_colonnes>30){
    printf("\nVeuillez entrer le nombre de colonne désirée: ");
    scanf("%d",&parametres->nb_colonnes);
    clean_stdin();
  }
  nb_max_mines=((parametres->nb_lignes * parametres->nb_colonnes)-(parametres->nb_lignes+parametres->nb_colonnes));//Correspond au nombre maximal de mines tout en tenant compte de la longueur et la largeur de la grille
  while(parametres->nb_mines<10 || parametres->nb_mines> nb_max_mines){
	printf("\nVeuillez entrer le nombre de mines, entre 10 et %d: ",nb_max_mines);
	scanf("%d",&parametres->nb_mines);
	clean_stdin();
  }
  joue_apres_parametrage(parametres);
}



/**
 *\author Emilien RAZAFIMAMPIANDRA
 *\brief Permet de vider le buffer pour l'entrée clavier et eviter le rebouclage infini.
 */
void clean_stdin(void){
  int c;
  do {
    c = getchar();
  }
  while (c != '\n' && c != EOF);
}
