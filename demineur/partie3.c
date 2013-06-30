/**
 *\file partie3.c
 *\author Alexandre Nouri
 *\brief Ce fichier contient les fonctions de la partie d'Alexandre NOURI
 */

#include "demineur.h"

/**
 *\author Alexandre Nouri 
 *\brief  Fonction d'alloction dynamique empruntee au cours de structures de donnees.
 *\details Amelioration du malloc par l'ajout d'un message d'erreur.
 *\param size le nombre d'elements a allouer
 *\return p un pointeur alloue
 */
void *my_malloc(size_t size) {
  void *p;
  p = malloc(size);
  if(p == NULL){
    fprintf(stderr, "Erreur : impossible d'allouer la memoire\n");
    exit(-1);
  }
  return p;
}

/**
 *\author Alexandre Nouri 
 *\brief Fonction empruntee au cours de structures de donnees.
 *\details Amelioration du realloc par l'ajout d'un message d'erreur.
 *\param size le nombre d'elements a re-allouer
 *\param *p un pointeur vers une donnee a re-allouer 
 *\return p un pointeur re-alloue   
 */
void *my_realloc(void *p, size_t size) {
  p = realloc(p, size);
  if(p == NULL) {
    fprintf(stderr, "Erreur : impossible de reallouer la memoire\n");
    exit(-1);
  }
  return p;
}

/**
 *\author Alexandre Nouri 
 *\brief Creation d'une grille pour mes tests.
 *\param p parametres de la grille (passes en pointeur). 
 *\return ma_grille une grille exemple.
*/
grille new_grille_exemple(parametre_grille p) {
  int i,j;
  grille ma_grille = my_malloc(sizeof(*ma_grille));
  int nb_lignes=p->nb_lignes;
  int nb_colonnes=p->nb_colonnes;
  ma_grille->matrice = my_malloc(nb_lignes * sizeof(int*));
  for(i=0; i<nb_colonnes; i++)
    (ma_grille->matrice)[i] = my_malloc(nb_colonnes * sizeof(int));
  for(i=0; i<nb_lignes; i++)
    for(j=0; j<nb_colonnes; j++){
      if(i==0 && j<10)
	(ma_grille->matrice)[i][j]=_MINE;
      else if(i==1 && j==0)
	(ma_grille->matrice)[i][j]=_MINE;
      else if(i==1 && j==1)
	(ma_grille->matrice)[i][j]=_QUATRE;
      else if(i==1 && j<8)
	(ma_grille->matrice)[i][j]=_TROIS;
      else if(i==1 && j==8)
	(ma_grille->matrice)[i][j]=_DEUX;
      else
	(ma_grille->matrice)[i][j]=_VIDE;
    }
  return ma_grille;
}

/**
 *\author Alexandre Nouri 
 *\brief  Creation de parametres d'exemple pour grille.
 *\return p Parametres charges.
*/

parametre_grille new_param_exemple(){
  parametre_grille p = my_malloc(sizeof(*p));
  p->nb_lignes=9;
  p->nb_colonnes=9;
  p->nb_mines=10;
  return p;
}

/**
 *\author Alexandre Nouri 
 *\brief Allocation du tableau d'affichage en memoire.
 *\param p, parametres de la grille (passes en pointeur).
 *\return ma_grille Tableau contenant les donnees d'affichage.
*/
display_matrix new_display_matrix (parametre_grille p){
  int i;
  int largeur=p->nb_colonnes;
  int hauteur=p->nb_lignes;
  display_matrix ma_grille = my_malloc(sizeof(*ma_grille));
  ma_grille->tab = my_malloc(hauteur * sizeof(int*));
  for(i=0; i<hauteur; i++)
    (ma_grille->tab)[i] = my_malloc(largeur * sizeof(int));
  return ma_grille;
}

/**
 *\author Alexandre Nouri 
 *\brief Cette fonction initialise une partie: initialise le mode graphique: place tout le monde au départ.
 *\param C, Structure Context (passee en pointeur) contenant les variables graphiques du jeu, la resolution de l'ecran.
 *\return Un int soit 0 si tout s'est bien passe ou -1 sinon
 */

int Init(Context C,int x, int y){
  putenv("SDL_VIDEO_WINDOW_POS=center");//Position de la fenetre
  if (C==NULL)
    return -1;
  if (SDL_Init(SDL_INIT_VIDEO)!=0)  // initialise SDL
    return -1;
  TTF_Init();
  C->XRES = x;
  C->YRES = y;
  C->screen = SDL_SetVideoMode(C->XRES,C->YRES,32,SDL_HWSURFACE|SDL_DOUBLEBUF);    // initialise le mode vidéo
  //SDL_ShowCursor(0);  // vire le curseur souris (car ce sera une balle !!)
  if (C->screen==NULL)
    return -1;
  if (LoadAll(C)!=0)       // charge les images
    return -1;
  return 0;
}

/**
 *\author Alexandre Nouri 
 *\brief Cette fonction libere la memoire des elements chargees dans la structure Context.
 *\param C, structure Context (passee en pointeur) contenant les variables graphiques du jeu, la resolution de l'ecran.
 *\return Un int soit 0 si tout s'est bien passe ou -1 sinon
 */
int Release(Context C){  
	int i;
	for(i=0;i<C->nbsurface;i++)
	  SDL_FreeSurface(C->surface[i]);
	free(C->surface);
	for(i=0;i<C->nb_text;i++)
	  free(C->text[i]);
	free(C->text);
	for(i=0;i<C->nbimg;i++)
		SDL_FreeSurface(C->image[i]);
	free(C->image);
	for(i=0;i<C->nb_surface_text;i++)
	  SDL_FreeSurface(C->surface_text[i]);
	free(C->surface_text);
	for(i=0;i<C->nbfont;i++)

	free(C);
	TTF_Quit();
	SDL_Quit();
	return 0;
}

/**
 *\author Alexandre Nouri 
 *\brief Cette fonction sert a charger les images et surfaces utiles pour le jeu.
 *\param C, structure Context (passee en pointeur) contenant les variables graphiques du jeu, la resolution de l'ecran.
 *\return Un int soit 0 si tout s'est bien passe ou -1 sinon
 */
int LoadAll(Context C){  // charge toutes les images,les surfaces et textes
  int i;
  char* all_image[] = {"case_non_ouverte.gif","case_cliquee.gif","case_vide.gif","1.gif","2.gif","3.gif","4.gif","5.gif","6.gif","7.gif","8.gif","mine.gif","drapeau.gif","grande_mine.png","ico-clock.png","bonhomme_sourit.png","fond_ecran.jpg","pause_fond.jpg"};
  C->nbimg = sizeof(all_image)/sizeof(char*);
  C->image = malloc(C->nbimg*sizeof(SDL_Surface*)); 
  for(i=0;i<C->nbimg;i++){
    C->image[i] = LoadImageSDL(all_image[i]);  // charge de images et les passe en 32 bits
  }
  //declaration des surfaces rectangles de 76*24 pour l'arriere plan du font 
  C->nbsurface=2;
  C->surface = malloc(C->nbsurface*sizeof(SDL_Surface*));  // si vous avez ici l'erreur "cannot convert from void* ..." c'est que vous compilez en C++. Il faut compiler en C.
  for(i=0;i<C->nbsurface;i++){
    C->surface[i] = SDL_CreateRGBSurface(SDL_HWSURFACE,76, 24, 32, 0, 0, 0, 0);
  }
  //C->bouton_pause=malloc(sizeof(SDL_Surface));
  //texte: nombre de mines restantes, chrono.
  C->nb_text=2;
  C->text=malloc(C->nb_text*sizeof(char*));
  for(i=0;i<C->nb_text;i++){
    C->text[i]=malloc(20*sizeof(char));
  }
  //surface des texte lie par definition au texte
  C->nb_surface_text=4;
  C->surface_text=malloc(C->nb_surface_text*sizeof(SDL_Surface*));

  for(i=0;i<C->nb_surface_text;i++){
    C->surface_text[i]=malloc(sizeof(SDL_Surface));
  }
  //les font
  char* all_font[]={"font2.ttf"};
  C->nbfont=sizeof(all_font)/sizeof(char*);
  C->font=malloc(C->nbfont*sizeof(TTF_Font*));
  for(i=0;i<C->nbfont;i++){
    C->font[i] = Load_font(all_font[i],22);
  }
  return 0;
}

/**
 *\author Alexandre Nouri 
 *\brief Cette fonction charge la polices d'ecriture du mode jeu.
 *\param fichier un tableau de char
 *\param taille la taille de la police
 *\return font la police chargee
 */
TTF_Font* Load_font(char* fichier, int taille){
  TTF_Font* font=TTF_OpenFont(fichier,taille);
  if(!font){
    printf("Fichier introuvable : Quit.\n");
    exit (-1);
  }
  return font;
}

/**
 *\author Alexandre Nouri 
 *\brief Cette fonction charge une image extraite d'un tableau.
 *\param fichier une chaine de caracteres representant le nom de l'image a charger
 *\return f la surface image chargee
 */
SDL_Surface* LoadImageSDL(char* fichier){
  SDL_Surface* f = IMG_Load(fichier);
  if (!f){
    printf("Fichier Introuvable : Quit."); 
    exit(-1);  // termine.
  }
  return f;
}

/**
 *\author Alexandre Nouri 
 *\brief Cette fonction remplit le tableau d'affichage par des murs. 
 *\param ma_grille le tableau d'affichage de type display_matrix (passe en pointeur)
 *\param p parametres de la grille
 */
/* AUTEUR: Alexandre Nouri 
   FONCTION: Cette fonction remplit le tableau d'affichage par des murs 
   PARAMETRES E/S: E -> le tableau d'affichage (passe en pointeur), les parametre
                   S -> rien
*/
void init_jeu(display_matrix ma_grille, parametre_grille p){
  int i,j;
  int hauteur =p->nb_lignes;
  int largeur = p->nb_colonnes;
  //initialisation de notre grille de jeu
  for(i=0;i<hauteur; i++)
    for(j=0;j<largeur; j++){
      ma_grille->tab[i][j] = MUR;
    }
}

/**
 *\author Alexandre Nouri 
 *\brief Cette fonction est la fonction qui permet de jouer une partie de demineur.
 *\param C variables graphiques
 *\param grille la grille contenant les elements de calculs tels que la position des mines ou le nombre de voisins miness
 *\param parametres les parametres de la grille
 */
void jouer(Context C, grille ma_grille, parametre_grille parametre){//a ajouter dans parametres: , grille ma_grille, masque drapeau_tab
  Timer t=init_Timer();
  start(t);
  int temps_precedent = 0, temps_actuel = 0, intervalle=1000;
  C->game_start=VRAI; // indicateur de non-demarrage du temps: renvoie VRAI si le temps est desactive
                      // renvoie FAUX si le temps est active
  C->compteur=0;
  Input in=malloc(sizeof(*in));
  memset(in,0,sizeof(*in));

  SDL_Rect  position,position_souris;
  SDL_Surface* fenetre_principale=C->screen;

  //initialisation des parametres de grille
  int largeur = parametre->nb_colonnes;
  int hauteur = parametre->nb_lignes; 
  int taille_case=16;
  int espace_entre_les_cases=3;
  int i,j; 
  int continuer = VRAI; 
  int etre_sur_une_case;
  int abscisse,ordonnee;

  //initialisation du tableau_graphique
  display_matrix affiche_tab = new_display_matrix(parametre);

  //initialisation de notre grille de jeu
  init_jeu(affiche_tab,parametre);

  //actualisation de la surface d'ecran
  actualise_ecran(C,ma_grille,parametre,affiche_tab);

  while(!in->key[SDLK_ESCAPE] && !in->quit){
    UpdateEvents(in);
    temps_actuel=get_time(t);
    if (in->mousebuttons[SDL_BUTTON_LEFT]){
      position_souris.x = in->mousex;
      position_souris.y = in->mousey;
      in->mousebuttons[SDL_BUTTON_LEFT] = 0;

      //determiner si on est sur une case
      etre_sur_une_case=FAUX;
      continuer=VRAI;
      abscisse=0,ordonnee=0;
      if(is_paused(t)==FAUX){
	// 1: verification si on a bien clique sur une case
	for(i=0; i<hauteur && continuer == VRAI ; i++)
	  for(j=0; j<largeur && continuer==VRAI; j++){
	    position.x=(fenetre_principale->w)/2-(largeur*taille_case/2)+(taille_case+espace_entre_les_cases)*j-(espace_entre_les_cases*(largeur-1)/2);
	    position.y=(fenetre_principale->h)/2-(hauteur*taille_case/2)+(taille_case+espace_entre_les_cases)*i-(espace_entre_les_cases*(hauteur-1)/2);
	    if((position_souris.x>=position.x && position_souris.x<position.x+taille_case )
	       && (position_souris.y>=position.y && position_souris.y<position.y+taille_case) ){
	      continuer=FAUX;
	      etre_sur_une_case=VRAI;
	      abscisse=i;
	      ordonnee=j;
	    }
	  }
	// 2: verification si on  clqiue sur la case pause
	if(position_souris.x>=fenetre_principale->w-C->surface_text[PAUSE]->w-3 && position_souris.x<fenetre_principale->w-3 && position_souris.y>=3 && position_souris.y<3+C->surface_text[PAUSE]->h && C->game_start==FAUX){
	  //si on a clique sur pause et que le temps s'est declenche
	  pause(t);
	  actualise_pause(C,t);
	}else if(position_souris.x>=fenetre_principale->w-C->surface_text[PAUSE]->w-3 && position_souris.x<fenetre_principale->w-3 && position_souris.y>=3 && position_souris.y<3+C->surface_text[PAUSE]->h && C->game_start==VRAI){
	  //si on a clique sur pause et que le temps ne s'est pas encore declenche
	  C->game_start=FAUX;
	  pause(t);actualise_pause(C,t);
	  temps_precedent=get_time(t);
	  temps_actuel=get_time(t);
	}

	// 3: retour vers le menu principal
	if(position_souris.x>=fenetre_principale->w-C->surface_text[RETOUR_MENU]->w-3 && position_souris.x<fenetre_principale->w-3 && position_souris.y>=3+C->surface_text[PAUSE]->h+6 && position_souris.y<3+C->surface_text[PAUSE]->h+3+C->surface_text[RETOUR_MENU]->h){
	  Affichage_menu();
	  break;
	}
	//si on a bien clique sur une case du tableau:
	if (etre_sur_une_case){
	  //on met la couleur finale , on continue ou arrete apres analyse

	  //on analyse: avec les 2 tableaux grille et drapeau

	  //quand je clique sur une case je verifie:
	  //1: si elle n'est pas deja vide
	  //2: si il n'y a pas de drapeaux
	  //3: si elle n'a pas de mine
	  //4: si elle n'est pas voisine d'une mine
	  //et seulement la on lance le deploiement
	  if(affiche_tab->tab[abscisse][ordonnee]==MUR && ma_grille->matrice[abscisse][ordonnee]!=_MINE){
	    if(C->game_start==VRAI){
	      C->game_start=FAUX;
	      temps_precedent=get_time(t);
	      temps_actuel=get_time(t);
	    }
	    //si il n' y a aucune mine
	    //la case courante est dite vide et on libere les cases voisines non mines recursivement
	    deploiement(abscisse,ordonnee,affiche_tab,ma_grille,parametre);
	    actualise_grille(affiche_tab,ma_grille,parametre);
	    actualise_ecran(C, ma_grille, parametre, affiche_tab);
	    if(Gagne(parametre,affiche_tab)){
	      break;
	    }
	  }else if (affiche_tab->tab[abscisse][ordonnee]==MUR && ma_grille->matrice[abscisse][ordonnee]==_MINE){
	    if(C->game_start==VRAI){
	      C->game_start=FAUX;
	      temps_precedent=get_time(t);
	      temps_actuel=get_time(t);
	    }
	    // affichage du bonhomme qui pleure

	    Perdu(C,affiche_tab,ma_grille,parametre);
	    break;	  
	  }
	}
      }
    }
    if(temps_actuel-temps_precedent>=intervalle && C->game_start==FAUX){
	C->compteur++;
	temps_precedent=temps_actuel;
	actualise_ecran(C,ma_grille,parametre,affiche_tab);
    }
  }
}

/**
 *\author Alexandre Nouri 
 *\brief Afficher toutes les mines.
 *\param affiche_tab les tableau d'affichage
 *\param ma_grille grille de calcul
 *\param parametres parametres
 */
void devoiler_toutes_mines(display_matrix affiche_tab,grille ma_grille, parametre_grille parametre){
  int i=0,j=0;
  for(i=0; i<parametre->nb_lignes; i++){
    for(j=0; j<parametre->nb_colonnes; j++){
      if(ma_grille->matrice[i][j] == _MINE)
	affiche_tab->tab[i][j]=MINE_;
    }
  }
}

/**
 *\author Alexandre Nouri 
 *\brief Cette fonction devoile une case aux coordonnees i,j.
 *\param i,j les coordonnees de la case a devoiler
 *\param ma_grille la grille contenant les elements de calculs tels que la position des mines ou le nombre de voisins mines
 *\param affiche_tab le tableau d'affichage des elements de notre ecran graphique durant le jeu
 */
void placer_le_bon_carre(int i,int j, display_matrix affiche_tab,grille ma_grille){
  if(ma_grille->matrice[i][j]==_VIDE)
    affiche_tab->tab[i][j]=VIDE_;
  else if(ma_grille->matrice[i][j]==_UN)
    affiche_tab->tab[i][j]=UN_;
  else if(ma_grille->matrice[i][j]==_DEUX)
    affiche_tab->tab[i][j]=DEUX_;
  else if(ma_grille->matrice[i][j]==_TROIS)
    affiche_tab->tab[i][j]=TROIS_;
  else if(ma_grille->matrice[i][j]==_QUATRE)
    affiche_tab->tab[i][j]=QUATRE_;
  else if(ma_grille->matrice[i][j]==_CINQ)
    affiche_tab->tab[i][j]=CINQ_;
  else if(ma_grille->matrice[i][j]==_SIX)
    affiche_tab->tab[i][j]=SIX_;
  else if(ma_grille->matrice[i][j]==_SEPT)
    affiche_tab->tab[i][j]=SEPT_;
  else if(ma_grille->matrice[i][j]==_HUIT)
    affiche_tab->tab[i][j]=HUIT_;
  else if(ma_grille->matrice[i][j]==_MINE)
    affiche_tab->tab[i][j]=MINE_;
  
}

/**
 *\author Alexandre Nouri 
 *\brief Cette fonction devoile toutes les cases qui sont marques comme etant a devoiler. Affichage du resultat dans le tableau d'affichage.
 *\param ma_grille la grille contenant les elements de calculs tels que la position des mines ou le nombre de voisins mines
 *\param ma_grille_affiche le tableau d'affichage des elements de notre ecran graphique durant le jeu
 *\param param parametres
 */
void actualise_grille(display_matrix  ma_grille_affiche,grille ma_grille,parametre_grille param){
  int i,j;
  for(i=0;i<param->nb_lignes;i++)
    for(j=0; j<param->nb_colonnes;j++)
      if(ma_grille_affiche->tab[i][j]==DEVOILER)
	placer_le_bon_carre(i,j,ma_grille_affiche,ma_grille);
}

/**
 *\author Alexandre Nouri 
 *\brief Cette fonction relance le deploiement sur une case voisine de celle devoilee: methode recursive.
 *\param i,j les coordonnees de la case a devoiler
 *\param ma_grille la grille contenant les elements de calculs tels que la position des mines ou le nombre de voisins mines
 *\param ma_grille_affiche le tableau d'affichage des elements de notre ecran graphique durant le jeu
 *\param param parametres de la grille
 */
void sous_deploiement(int i, int j,display_matrix  ma_grille_affiche, grille ma_grille,parametre_grille param){
  int** tab2=ma_grille_affiche->tab;
  int** tab1=ma_grille->matrice;
  if(tab1[i][j]!=_MINE && tab2[i][j] != DEVOILER && tab2[i][j]!=DRAPEAU_){
    //param->nb_mines--;
    tab2[i][j]=DEVOILER;
    if(tab1[i][j]==_VIDE)
      deploiement(i,j,ma_grille_affiche,ma_grille,param);   
  }
}
  
/**
 *\author Alexandre Nouri 
 *\brief Cette fonction permet de decouvrir une portion commune de la grille
 *\param i,j les coordonnees de la case d'ou part le devoilement
 *\param ma_grille la grille contenant les elements de calculs tels que la position des mines ou le nombre de voisins mines
 *\param ma_grille_affiche le tableau d'affichage des elements de notre ecran graphique durant le jeu
 *\param p parametres de la grille
 */
void deploiement(int i, int j,display_matrix  ma_grille_affiche, grille ma_grille, parametre_grille p){
  int nb_lignes=p->nb_lignes;
  int nb_colonnes=p->nb_colonnes;
  if(ma_grille->matrice[i][j]==_VIDE){
    if(i==0 && j==0){
      sous_deploiement(i,j+1,ma_grille_affiche,ma_grille,p);
      sous_deploiement(i+1,j,ma_grille_affiche,ma_grille,p);
      sous_deploiement(i+1,j+1,ma_grille_affiche,ma_grille,p);
    }else if(i==0 && j==nb_colonnes-1){
      sous_deploiement(i,j-1,ma_grille_affiche,ma_grille,p);
      sous_deploiement(i+1,j,ma_grille_affiche,ma_grille,p);
      sous_deploiement(i+1,j-1,ma_grille_affiche,ma_grille,p);
      // 3eme cas, de la 2eme a l'avt derniere ligne, a gauche 
    }else if(i>0 && i<nb_lignes-1 && j==0){
      sous_deploiement(i-1,j,ma_grille_affiche,ma_grille,p);
      sous_deploiement(i+1,j,ma_grille_affiche,ma_grille,p);
      sous_deploiement(i,j+1,ma_grille_affiche,ma_grille,p);
      sous_deploiement(i+1,j+1,ma_grille_affiche,ma_grille,p);
      sous_deploiement(i-1,j+1,ma_grille_affiche,ma_grille,p);
      // 4eme cas, derniere ligne, a gauche
    }else if(i==nb_lignes-1 && j==0){
      sous_deploiement(i-1,j,ma_grille_affiche,ma_grille,p);
      sous_deploiement(i,j+1,ma_grille_affiche,ma_grille,p);
      sous_deploiement(i-1,j+1,ma_grille_affiche,ma_grille,p);
      // 5eme cas, derniere ligne, a droite
    }else if(i==nb_lignes-1 && j==nb_colonnes-1){
      sous_deploiement(i,j-1,ma_grille_affiche,ma_grille,p);
      sous_deploiement(i-1,j,ma_grille_affiche,ma_grille,p);
      sous_deploiement(i-1,j-1,ma_grille_affiche,ma_grille,p);
      // 6eme cas, derniere ligne, sans les extremites
    }else if(j>0 && j<nb_colonnes-1 && i==nb_lignes - 1){
      sous_deploiement(i,j-1,ma_grille_affiche,ma_grille,p);
      sous_deploiement(i-1,j,ma_grille_affiche,ma_grille,p);
      sous_deploiement(i-1,j-1,ma_grille_affiche,ma_grille,p);
      sous_deploiement(i-1,j+1,ma_grille_affiche,ma_grille,p);
      sous_deploiement(i,j+1,ma_grille_affiche,ma_grille,p);
      // 7eme cas, derniere colonne, sans les extremites
    }else if(i>0 && i<nb_lignes-1 && j==nb_colonnes - 1){
      sous_deploiement(i-1,j,ma_grille_affiche,ma_grille,p);
      sous_deploiement(i,j-1,ma_grille_affiche,ma_grille,p);
      sous_deploiement(i+1,j,ma_grille_affiche,ma_grille,p);
      sous_deploiement(i+1,j-1,ma_grille_affiche,ma_grille,p);
      sous_deploiement(i-1,j-1,ma_grille_affiche,ma_grille,p);
      // 8eme cas, 1ere ligne, sans les extremites
    }else if(j>0 && j<nb_colonnes-1 && i == 0){
      sous_deploiement(i,j-1,ma_grille_affiche,ma_grille,p);
      sous_deploiement(i+1,j,ma_grille_affiche,ma_grille,p);
      sous_deploiement(i,j+1,ma_grille_affiche,ma_grille,p);
      sous_deploiement(i+1,j+1,ma_grille_affiche,ma_grille,p);
      sous_deploiement(i+1,j-1,ma_grille_affiche,ma_grille,p);
      // cas general
    }else{
      sous_deploiement(i,j-1,ma_grille_affiche,ma_grille,p);
      sous_deploiement(i+1,j,ma_grille_affiche,ma_grille,p);
      sous_deploiement(i,j+1,ma_grille_affiche,ma_grille,p);
      sous_deploiement(i-1,j,ma_grille_affiche,ma_grille,p);
      sous_deploiement(i+1,j+1,ma_grille_affiche,ma_grille,p);
      sous_deploiement(i+1,j-1,ma_grille_affiche,ma_grille,p);
      sous_deploiement(i-1,j+1,ma_grille_affiche,ma_grille,p);
      sous_deploiement(i-1,j-1,ma_grille_affiche,ma_grille,p);
    }
  }else if(ma_grille->matrice[i][j]!=_MINE)
    sous_deploiement(i, j, ma_grille_affiche, ma_grille, p);
}
  
/**
 *\author Alexandre Nouri 
 *\brief Cette fonction permet d'actualiser l'ecran
 *\param C la structure Context contenant les images chargees et les surfaces.
 *\param ma_grille la grille contenant les elements de calculs tels que la position des mines ou le nombre de voisins mines
 *\param affiche_tab le tableau d'affichage des elements de notre ecran graphique durant le jeu
 *\param parametre parametres de la grille
 */

void actualise_ecran(Context C, grille ma_grille,parametre_grille parametre,display_matrix affiche_tab){
  TTF_Font* font_comic=C->font[FONTCOMIC];
  //initialisation de la variable position
  SDL_Rect  position;
  SDL_Surface* fenetre_principale=C->screen;
  //initialisation des parametres de grille
  int largeur = parametre->nb_colonnes;
  int hauteur = parametre->nb_lignes;
  int i,j; 
  int taille_case = 16;
  int nb_mines_restantes=parametre->nb_mines;
  //initialisation des couleurs
  Uint32 white,bleu;
  white=SDL_MapRGB(fenetre_principale->format,255,255,255);
  bleu=SDL_MapRGB(fenetre_principale->format,0,0,255);
  SDL_Color _white={255,255,255};
  int compteur = C->compteur;
  //lancement de la fenetre principale
  SDL_FillRect(fenetre_principale,NULL,white);
  
  //On suppose le choix suivant:
  //  -Grille de 9*9 selectionne
  //temps_precedent=SDL_GetTicks();
  //affichage initial des surfaces de la grille
  
  position.x=0;
  position.y=0;
  SDL_BlitSurface(C->image[FOND_ECRAN],NULL,fenetre_principale,&position);

  // 1: les cases actualisees
  for(i=0; i<hauteur; i++)
    for(j=0; j<largeur; j++){
      position.x=(fenetre_principale->w)/2-(largeur*taille_case/2)+(taille_case+3)*j-(3*(largeur-1)/2);
      position.y=(fenetre_principale->h)/2-(hauteur*taille_case/2)+(taille_case+3)*i-(3*(hauteur-1)/2);
      affiche_case(i,j,C,affiche_tab,&position);
    }

  // 2: affichage de la grande mine
  position.x=3;
  position.y=(fenetre_principale->h)-(C->image[GRANDE_MINE]->h)-3;
  SDL_BlitSurface(C->image[GRANDE_MINE],NULL,fenetre_principale,&position);

  // 3: affichage du rectangle a l'interieur duquel on met le nombre de mines restantes
  SDL_FillRect(C->surface[RECTANGLE_DRAPEAU], NULL, bleu);
  position.x=3+C->image[GRANDE_MINE]->w+3;
  position.y=position.y+4;
  SDL_BlitSurface(C->surface[RECTANGLE_DRAPEAU],NULL,fenetre_principale,&position);

  // 4: affichage du texte du nombre de mines restantes
  sprintf(C->text[DRAPEAU_RESTANT_TEXT],"%d",nb_mines_restantes);
  C->surface_text[DRAPEAU_RESTANT]=TTF_RenderText_Blended(font_comic,C->text[DRAPEAU_RESTANT_TEXT],_white);
  position.x=position.x+C->surface[RECTANGLE_DRAPEAU]->w/2-C->surface_text[DRAPEAU_RESTANT]->w/2;
  position.y=position.y-1.5;
  SDL_BlitSurface(C->surface_text[DRAPEAU_RESTANT],NULL,fenetre_principale,&position);

  //5: affichage du rectangle contenant le chrono
  SDL_FillRect(C->surface[RECTANGLE_CHRONO], NULL, bleu);
  position.x=fenetre_principale->w-C->surface[RECTANGLE_CHRONO]->w-3;
  position.y=fenetre_principale->h-C->surface[RECTANGLE_CHRONO]->h-6;
  SDL_BlitSurface(C->surface[RECTANGLE_CHRONO],NULL,fenetre_principale,&position);

  //6: affichage de l'image de l'horloge
  position.x=position.x-3-C->image[CLOCK]->w;
  position.y=fenetre_principale->h-3-C->image[CLOCK]->h;
  SDL_BlitSurface(C->image[CLOCK],NULL,fenetre_principale,&position);
  
  //7: affichage du texte indiquant le temps ecoule
  sprintf(C->text[TIME_TEXT],"%d",compteur);
  C->surface_text[TIME]=TTF_RenderText_Blended(font_comic,C->text[TIME_TEXT],_white);
  position.x=fenetre_principale->w-3-C->surface[RECTANGLE_CHRONO]->w/2-C->surface_text[TIME]->w/2;
  position.y=fenetre_principale->h-3-C->surface_text[TIME]->h-3;
  SDL_BlitSurface(C->surface_text[TIME],NULL,fenetre_principale,&position);

  //8: affichage du bouton pause
  C->surface_text[PAUSE]=TTF_RenderText_Blended(font_comic,"Pause",_white);
  position.x=fenetre_principale->w-C->surface_text[PAUSE]->w-3;
  position.y=3;
  SDL_BlitSurface(C->surface_text[PAUSE],NULL,fenetre_principale,&position);

  //8.2: affichage du bouton retour vers le menu

  C->surface_text[RETOUR_MENU]=TTF_RenderText_Blended(font_comic,"Retour vers le menu",_white);
  position.x=fenetre_principale->w-C->surface_text[RETOUR_MENU]->w-3;
  position.y=3+C->surface_text[PAUSE]->h+3;
  SDL_BlitSurface(C->surface_text[RETOUR_MENU],NULL,fenetre_principale,&position);


  //9: affichage du bonhomme 
  position.x=fenetre_principale->w/2-C->image[BONHOMME_SOURIT]->w/2;
  position.y=3;
  SDL_BlitSurface(C->image[BONHOMME_SOURIT],NULL,fenetre_principale,&position);
  //FIN DE l'actualisation des surfaces
  SDL_Flip(fenetre_principale);
}

/**
 *\author Alexandre Nouri 
 *\brief Cette fonction permet d'afficher une case dans l'ecran
 *\details on modifie les valeurs du tableau affiche_tab, le tableau d'affichage
 *\param C la structure Context contenant les images chargees et les surfaces.
 *\param affiche_tab le tableau d'affichage des elements de notre ecran graphique durant le jeu
 *\param pos la position en pixels 
 *\param i,j les coordonnes de la case a affficher
 */

void affiche_case(int i, int j, Context C, display_matrix affiche_tab,SDL_Rect* pos){
  SDL_Surface* fenetre_principale=C->screen;
  if(affiche_tab->tab[i][j]==MUR)
    SDL_BlitSurface(C->image[CARRE_CLAIR],NULL,fenetre_principale,pos);
  else if(affiche_tab->tab[i][j]==VIDE_)
    SDL_BlitSurface(C->image[VIDE],NULL,fenetre_principale,pos);
  else if(affiche_tab->tab[i][j]==DRAPEAU_)
    SDL_BlitSurface(C->image[DRAPEAU],NULL,fenetre_principale,pos);
  else if(affiche_tab->tab[i][j]==UN_)
    SDL_BlitSurface(C->image[UN],NULL,fenetre_principale,pos);
  else if(affiche_tab->tab[i][j]==DEUX_)
    SDL_BlitSurface(C->image[DEUX],NULL,fenetre_principale,pos);
  else if(affiche_tab->tab[i][j]==TROIS_)
    SDL_BlitSurface(C->image[TROIS],NULL,fenetre_principale,pos);
  else if(affiche_tab->tab[i][j]==QUATRE_)
    SDL_BlitSurface(C->image[QUATRE],NULL,fenetre_principale,pos);
  else if(affiche_tab->tab[i][j]==CINQ_)
    SDL_BlitSurface(C->image[QUATRE],NULL,fenetre_principale,pos);
  else if(affiche_tab->tab[i][j]==SIX_)
    SDL_BlitSurface(C->image[CINQ],NULL,fenetre_principale,pos);
  else if(affiche_tab->tab[i][j]==SEPT_)
    SDL_BlitSurface(C->image[SIX],NULL,fenetre_principale,pos);
  else if(affiche_tab->tab[i][j]==HUIT_)
    SDL_BlitSurface(C->image[HUIT],NULL,fenetre_principale,pos);
  else if(affiche_tab->tab[i][j]==MINE_)
    SDL_BlitSurface(C->image[MINE],NULL,fenetre_principale,pos);
}


/**
 *\author Alexandre Nouri 
 *\brief Fonction de simplification de la gestion des Switch en SDL.
 *\details inspire du site du zero
 *\param In la structure Input qui contient un tableau de toutes les evenements (traduits en variables)
 */
void UpdateEvents(Input in)
{
	SDL_Event event;
	while(SDL_PollEvent(&event))
	{
		switch (event.type)
		{ 
		case SDL_KEYDOWN:
			in->key[event.key.keysym.sym]=0;
			break;
		case SDL_KEYUP:
			in->key[event.key.keysym.sym]=1;
			break;
		case SDL_MOUSEMOTION:
			in->mousex=event.motion.x;
			in->mousey=event.motion.y;
			break;
		case SDL_MOUSEBUTTONDOWN:
			in->mousebuttons[event.button.button]=0;
			break;
		case SDL_MOUSEBUTTONUP:
			in->mousebuttons[event.button.button]=1;
			break;
		case SDL_QUIT:
			in->quit = 1;
			break;
		default:
			break;
		}
	}
}

/**
 *\author Alexandre Nouri 
 *\brief Cette fonction permet d'initialiser un chronometre.
 *\return t, de type Timer(passe en pointeur), la structure qui contient les informations necessaires a un chronometre
 */
Timer init_Timer(){
  Timer t=malloc(sizeof(*t));
  t->started=FAUX;
  t->paused=FAUX;
  t->startTicks=0;
  t->pausedTicks=0;
  return t;
}

/**
 *\author Alexandre Nouri 
 *\brief Cette fonction permet de lancer un chronometre.
 *\details modification des champs: temps de depart, t->started et t->paused
 *\param t la structure Timer (passe en pointeur)
 */
void start(Timer t){

    //On demarre le timer
    t->started = VRAI;

    //On enlève la pause du timer
    t->paused = FAUX;

    //On récupére le temps courant
    t->startTicks = SDL_GetTicks();

}

/**
 *\author Alexandre Nouri 
 *\brief Cette fonction permet d'arreter un chronometre.
 *\details modification des champs: t->started et t->paused
 *\param t la structure Timer (passe en pointeur)
 */
void stop(Timer t){
  
  //On demarre le timer
  t->started = FAUX;
  
  //On enlève la pause du timer
  t->paused = FAUX;
}

/**
 *\author Alexandre Nouri 
 *\brief Cette fonction permet de recuperer le temps ecoule depuis le lancement du chronometre.
 *\param t la structure Timer (passe en pointeur)
 *\return retourne le temps ecoule 
 */
int get_time(Timer t){
  //Si le timer est en marche
  if( t->started == VRAI ){
    //Si le timer est en pause
    if( t->paused == VRAI ){
      //On retourne le nombre de ticks quand le timer a été mis en pause
      return t->pausedTicks;
    }else{
      //On retourne le temps courant moins le temps quand il a démarré
      return SDL_GetTicks() - t->startTicks;
    }
  }
  //Si le timer n'est pas en marche
  return 0;
}

/**
 *\author Alexandre Nouri 
 *\brief Cette fonction permet de mettre en pause le chronometre.
 *\param t la structure Timer (passe en pointeur)
 */
void pause(Timer t){
  //Si le timer est en marche et pas encore en pause
  if( ( t->started == VRAI ) && ( t->paused == FAUX ) ){
    //On met en pause le timer
    t->paused = VRAI;
    //On calcul le pausedTicks
    t->pausedTicks = SDL_GetTicks() - t->startTicks;
  }
}

/**
 *\author Alexandre Nouri 
 *\brief Cette fonction permet d'afficher un ecran de pause avec bouton pour revenir au jeu et relancer le chronometre.
 *\param t la structure Timer (passe en pointeur)
 *\param C la structure Context
 */
void actualise_pause(Context C,Timer t){
  TTF_Font* font_comic=C->font[FONTCOMIC];
  TTF_Font* font2=Load_font("BlackAsylumDEMO-KCFonts.ttf",90);

  Input in=malloc(sizeof(*in));
  memset(in,0,sizeof(*in));
  SDL_Surface* surface_texte_pause=malloc(sizeof(*surface_texte_pause));
  SDL_Surface* pause=malloc(sizeof(*pause));
  SDL_Rect position_souris;
  SDL_Rect position;
  SDL_Color rouge={255,255,51};
  surface_texte_pause=TTF_RenderText_Blended(font_comic,"Cliquer ici pour revenir au jeu",rouge);
  pause=TTF_RenderText_Blended(font2,"Pause",rouge);
  position.x=0;
  position.y=0;
  SDL_BlitSurface(C->image[PAUSE_FOND_ECRAN],NULL,C->screen,&position);
  position.x=C->screen->w/2-pause->w/2;
  position.y=C->screen->h/2-pause->h/2;
  SDL_BlitSurface(pause,NULL,C->screen,&position);

  position.x=C->screen->w/2-surface_texte_pause->w/2;
  position.y=C->screen->h/4-surface_texte_pause->h/2;
  SDL_BlitSurface(surface_texte_pause,NULL,C->screen,&position);
  //FIN DE l'actualisation des surfaces
  SDL_Flip(C->screen);
  int continuer=VRAI;
  while(!in->key[SDLK_ESCAPE] && !in->quit && continuer==VRAI){
    UpdateEvents(in); 
    if (in->mousebuttons[SDL_BUTTON_LEFT]){
      position_souris.x = in->mousex;
      position_souris.y = in->mousey;
      in->mousebuttons[SDL_BUTTON_LEFT] = 0;
      if(position_souris.x>=position.x && position_souris.x<position.x+surface_texte_pause->w && position_souris.y>=position.y && position_souris.y<position.y+surface_texte_pause->h){
	continuer=FAUX;
	unpause(t); 
      }
    }
  }
}

/**
 *\author Alexandre Nouri 
 *\brief Cette fonction permet de relancer le chronometre qui est suppose est en mode pause.
 *\param t la structure Timer
 */
void unpause(Timer t){
  //Si le timer est en pause
  if( t->paused == VRAI ){
    //on enlève la pause du timer
    t->paused = FAUX;
    //On remet le startTicks a la valeur avnant la pause
    t->startTicks = SDL_GetTicks() - t->pausedTicks;
    
    //Remise à zero du pausedTicks
    t->pausedTicks = 0;
  }
}

/**
 *\author Alexandre Nouri 
 *\brief Cette fonction verifie si le chronometre est en mode pause.
 *\param t la structure Timer
 *\return Soit vrai, soit faux
 */
int is_paused(Timer t){
  return t->paused;
}


/**
 *\author Alexandre Nouri 
 *\brief Cette fonction verifie si le chronometre est lance.
 *\param t la structure Timer
 *\return soit VRAI soit FAUX
 */
int is_started(Timer t){
  return t->started;
}



/**
 *\author Alexandre Nouri 
 *\brief Cette fonction regroupe un exemple d'execution d'une partie basique
 *\details ie sans placer au hasard les mines et sans les parametres
 */
int nouvelle_partie(){
  Context C=malloc(sizeof(*C));
  tableau plateau=malloc(sizeof(*plateau));
  parametre_grille parametre=malloc(sizeof(*parametre));
  Facile(parametre);
  grille ma_grille=Conversion(parametre,plateau);
  if (Init(C,800,600)!=0)   // init en 800*600 avec 10 sprites
    return -1;

  jouer(C,ma_grille,parametre);
  Release(C);
  return 0; 
}

