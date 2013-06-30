/**
 *\file partie1.c
 *\author Massinissa MOHANDI
 *\brief Ce fichier contient les fonctions de la partie de Massinissa MOHANDI
 */

#include"demineur.h"

/**
 *\author Massinissa MOHANDI 
 *\brief Fonction d'affichage du menu principal du jeu. 
*/

void Affichage_menu(){
  putenv("SDL_VIDEO_WINDOW_POS=center");//Position de la fenetre
  SDL_Surface *ecran=NULL, *fond=NULL, *jouer=NULL, *regles=NULL,*parametres=NULL,*scores=NULL,*quitter=NULL, *texte_jouer=NULL,*texte_regles=NULL,*texte_parametres=NULL,*texte_scores=NULL,*texte_quitter=NULL;
  SDL_Rect pos_fond, pos_jouer, pos_texte_jouer, pos_regles, pos_texte_regles, pos_parametres, pos_texte_parametres, pos_scores, pos_texte_scores, pos_quitter, pos_texte_quitter; 
  SDL_Event event;
  TTF_Font *police=NULL;
  SDL_Color texte_couleur={140,55,38};
  int continuer=1;
  parametre_grille param;
  
  //Position de l'image de fond
  pos_fond.x=0; 
  pos_fond.y=0;

  SDL_Init(SDL_INIT_VIDEO);//Charge le système d'affichage
  TTF_Init();//démarre SDL_ttf

  ecran=SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);//Taille et Type de fenetre
  jouer=SDL_CreateRGBSurface(SDL_HWSURFACE, LARGEUR, HAUTEUR, 32, 0, 0, 0, 0);//Taille et couleur du bouton
  regles=SDL_CreateRGBSurface(SDL_HWSURFACE, LARGEUR, HAUTEUR, 32, 0, 0, 0, 0);
  parametres=SDL_CreateRGBSurface(SDL_HWSURFACE, 300, HAUTEUR, 32, 0, 0, 0, 0);
  scores=SDL_CreateRGBSurface(SDL_HWSURFACE, LARGEUR, HAUTEUR, 32, 0, 0, 0, 0);
  quitter=SDL_CreateRGBSurface(SDL_HWSURFACE, LARGEUR, HAUTEUR, 32, 0, 0, 0, 0);  
  
  SDL_WM_SetCaption("Demineur", NULL);//Nom de la fenetre

  fond=IMG_Load("Demin.png");//Chargement de l'image de fond
  SDL_BlitSurface(fond, NULL, ecran, &pos_fond);//Blitter l'image de fond sur l'ecran
  
  //Position du bouton jouer
  pos_jouer.x=(ecran->w)-(jouer->w/0.54);
  pos_jouer.y=(ecran->h/3.2)-(jouer->h/5);
  SDL_FillRect(jouer, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));//Cette fonction effectue un remplissage rapide du bouton jouer
  SDL_SetColorKey(jouer, SDL_SRCCOLORKEY, SDL_MapRGB(jouer->format, 255, 255, 255));//Rendre la couleur du bouton transparente
  SDL_BlitSurface(jouer, NULL, ecran, &pos_jouer);
  
  //Position du bouton regles
  pos_regles.x=(ecran->w)-(regles->w/0.55);
  pos_regles.y=(ecran->h/2.3)-(regles->h/5);
  SDL_FillRect(regles, NULL, SDL_MapRGB(ecran->format, 255, 0, 255));//Cette fonction effectue un remplissage rapide du bouton regles
  SDL_SetColorKey(regles, SDL_SRCCOLORKEY, SDL_MapRGB(regles->format, 255, 0, 255));//Rendre la couleur du bouton transparente
  SDL_BlitSurface(regles, NULL, ecran, &pos_regles);

  //Position du bouton parametres
  pos_parametres.x=(ecran->w)-(parametres->w/1.05);
  pos_parametres.y=(ecran->h/1.8)-(parametres->h/5);
  SDL_FillRect(parametres, NULL, SDL_MapRGB(ecran->format, 255, 255, 0));//Cette fonction effectue un remplissage rapide du bouton scores
  SDL_SetColorKey(parametres, SDL_SRCCOLORKEY, SDL_MapRGB(parametres->format, 255, 255, 0));//Rendre la couleur du bouton transparente
  SDL_BlitSurface(parametres, NULL, ecran, &pos_parametres);

  //Position du bouton scores
  pos_scores.x=(ecran->w)-(scores->w/0.56);
  pos_scores.y=(ecran->h/1.5)-(scores->h/5);
  SDL_FillRect(scores, NULL, SDL_MapRGB(ecran->format, 0, 255, 255));//Cette fonction effectue un remplissage rapide du bouton scores
  SDL_SetColorKey(scores, SDL_SRCCOLORKEY, SDL_MapRGB(scores->format, 0, 255, 255));//Rendre la couleur du bouton transparente
  SDL_BlitSurface(scores, NULL, ecran, &pos_scores);

  //Position du bouton quitter
  pos_quitter.x=(ecran->w)-(quitter->w/0.57);
  pos_quitter.y=(ecran->h/1.28)-(quitter->h/5);
  SDL_FillRect(quitter, NULL, SDL_MapRGB(ecran->format, 0, 0, 255));//Cette fonction effectue un remplissage rapide du bouton quitter
  SDL_SetColorKey(quitter, SDL_SRCCOLORKEY, SDL_MapRGB(quitter->format, 0, 0, 255));//Rendre la couleur du bouton transparente
  SDL_BlitSurface(quitter, NULL, ecran, &pos_quitter);

  //Police du texte des boutons 
  police=TTF_OpenFont("BlackAsylumDEMO-KCFonts.ttf", 50);
  TTF_SetFontStyle(police, TTF_STYLE_BOLD);//mettre le texte en gras
  texte_jouer=TTF_RenderText_Solid(police, "Jouer", texte_couleur);
  texte_regles=TTF_RenderText_Solid(police, "Regles", texte_couleur);
  texte_parametres=TTF_RenderText_Solid(police, "Parametres", texte_couleur);
  texte_scores=TTF_RenderText_Solid(police, "Scores", texte_couleur);
  texte_quitter=TTF_RenderText_Solid(police, "Quitter", texte_couleur);
 
  //position du texte jouer
  pos_texte_jouer.x=(ecran->w)-(jouer->w/0.55);
  pos_texte_jouer.y=(ecran->h/3.2)-(jouer->h/5);
  pos_texte_jouer.w=texte_jouer->w;
  pos_texte_jouer.h=texte_jouer->h;
  
  SDL_BlitSurface(texte_jouer, NULL, ecran, &pos_texte_jouer);

  //position du texte regles
  pos_texte_regles.x=(ecran->w)-(regles->w/0.55);
  pos_texte_regles.y=(ecran->h/2.3)-(regles->h/5);
  pos_texte_regles.w=texte_regles->w;
  pos_texte_regles.h=texte_regles->h;

  SDL_BlitSurface(texte_regles, NULL, ecran, &pos_texte_regles);
 
  //position du texte parametres
  pos_texte_parametres.x=(ecran->w)-(parametres->w/1.07);
  pos_texte_parametres.y=(ecran->h/1.8)-(parametres->h/5);
  pos_texte_parametres.w=texte_parametres->w;
  pos_texte_parametres.h=texte_parametres->h;
  
  SDL_BlitSurface(texte_parametres, NULL, ecran, &pos_texte_parametres);
  
  //position du texte scores
  pos_texte_scores.x=(ecran->w)-(scores->w/0.55);
  pos_texte_scores.y=(ecran->h/1.5)-(scores->h/5);
  pos_texte_scores.w=texte_scores->w;
  pos_texte_scores.h=texte_scores->h;
  
  SDL_BlitSurface(texte_scores, NULL, ecran, &pos_texte_scores);
  
  //position du texte quitter
  pos_texte_quitter.x=(ecran->w)-(quitter->w/0.55);
  pos_texte_quitter.y=(ecran->h/1.28)-(quitter->h/5);
  pos_texte_quitter.w=texte_quitter->w;
  pos_texte_quitter.h=texte_quitter->h;
  
  SDL_BlitSurface(texte_quitter, NULL, ecran, &pos_texte_quitter);
  

  //Libération des surfaces de texte
  SDL_FreeSurface(texte_jouer);
  SDL_FreeSurface(texte_regles);
  SDL_FreeSurface(texte_parametres);
  SDL_FreeSurface(texte_scores);
  SDL_FreeSurface(texte_quitter);
  TTF_CloseFont(police);

  SDL_Flip(ecran);//Mise à jour de l'écran

  //Gestion d'evenement de la souris
  while(continuer){
    SDL_WaitEvent(&event);
    switch(event.type){
    case SDL_QUIT:
      continuer=0;
      break;
    case SDL_MOUSEBUTTONUP:
      if(event.button.x>(ecran->w)-(jouer->w/0.54) && event.button.x<=(ecran->w)-(jouer->w/0.54)+LARGEUR && event.button.y>(ecran->h/3.2)-(jouer->h/5) && event.button.y<=(ecran->h/3.2)-(jouer->h/5)+HAUTEUR){
	continuer=0;       
	nouvelle_partie();//Appel de la fonction nouvelle_partie pour jouer
      }
      else if(event.button.x>(ecran->w)-(regles->w/0.55) && event.button.x<=(ecran->w)-(regles->w/0.55)+LARGEUR && event.button.y>(ecran->h/2.3)-(regles->h/5) && event.button.y<=(ecran->h/2.3)-(regles->h/5)+HAUTEUR){
	continuer=0;       
	Regles();//Appel de la fonction Regles pour les regles du jeu 
      }
      else if(event.button.x>(ecran->w)-(parametres->w/1.05) && event.button.x<=(ecran->w)-(parametres->w/1.05)+300 && event.button.y>(ecran->h/1.8)-(parametres->h/5) && event.button.y<=(ecran->h/1.8)-(parametres->h/5)+HAUTEUR){
	continuer=0;       
	Affichage_parametres(param);//Appel de la fonction Affichage_parametres pour changer les parametres du jeu      
      }
      else if(event.button.x>(ecran->w)-(quitter->w/0.57) && event.button.x<=(ecran->w)-(quitter->w/0.57)+LARGEUR && event.button.y>(ecran->h/1.28)-(quitter->h/5) && event.button.y<=(ecran->h/1.28)-(quitter->h/5)+HAUTEUR)
	continuer=0;
      else 
	continuer=1;
      break;
    }
  }
  
  SDL_FreeSurface(fond);//Libération de la surface fond
  SDL_FreeSurface(jouer);//Liberation de la surface jouer
  TTF_Quit();//Arrête SDL_ttf
  SDL_Quit();//Libère la SDL de la mémoire
}

/**
 *\author Massinissa MOHANDI 
 *\brief Cette fonction verifie si on a perdu la partie.
 *\param c la structure Context contenant les images chargees et les surfaces.
 *\param ma_grille le tableau d'affichage des elements de notre ecran graphique durant le jeu
 *\param grille la grille contenant les elements de calculs tels que la position des mines ou le nombre de voisins mines
 *\param parametre parametres de la grille
 */

void Perdu(Context c, display_matrix ma_grille, grille grille, parametre_grille parametre){
  devoiler_toutes_mines(ma_grille,grille,parametre);//Devoiler toutes les mines de la grille
  actualise_ecran(c, grille, parametre, ma_grille);
  SDL_Surface *img;
  SDL_Rect pos_img;
  img=IMG_Load("bonhomme_pleure.png");
  pos_img.x=(c->screen->w/2)-(img->w/2);
  pos_img.y=3;
  SDL_BlitSurface(img, NULL, c->screen, &pos_img);
  SDL_Flip(c->screen);
  SDL_Delay(3500);//Attendre 3.5 secondes pour afficher la fenetre Perdu
  Perdre_partie(parametre);//Appel a la fonction Perdre_partie 
}

/**
 *\author Massinissa MOHANDI 
 *\brief Cette fonction affiche la fenetre Perdu.
 *\param param parametres de la grille
 */

void Perdre_partie(parametre_grille param){
  putenv("SDL_VIDEO_WINDOW_POS=center");//Position de la fenetre
  SDL_Surface *ecran=NULL, *fond=NULL, *rejouer=NULL, *scores=NULL, *menu=NULL, *texte_rejouer=NULL, *texte_scores=NULL, *texte_menu=NULL;
  SDL_Rect pos_fond, pos_rejouer, pos_texte_rejouer, pos_scores, pos_texte_scores, pos_menu, pos_texte_menu; 
  SDL_Event event;
  TTF_Font *police=NULL;
  SDL_Color noir={1, 9, 10};
  int continuer=1;
  
  //Position de l'image de fond
  pos_fond.x=0; 
  pos_fond.y=0;

  SDL_Init(SDL_INIT_VIDEO);//Charge le système d'affichage
  TTF_Init();//démarre SDL_ttf
  
  ecran=SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);//Taille et Type de fenetre
  rejouer=SDL_CreateRGBSurface(SDL_HWSURFACE, LARGEUR, HAUTEUR, 32, 0, 0, 0, 0);//Taille et couleur du bouton
  scores=SDL_CreateRGBSurface(SDL_HWSURFACE, LARGEUR, HAUTEUR, 32, 0, 0, 0, 0);
  menu=SDL_CreateRGBSurface(SDL_HWSURFACE, 350, HAUTEUR, 32, 0, 0, 0, 0);
  
  SDL_WM_SetCaption("Perdu", NULL);// Nom de la fenetre
  
  fond=IMG_Load("Perdu.png");//Chargement de l'image de fond
  SDL_BlitSurface(fond, NULL, ecran, &pos_fond);

  //Position du bouton rejouer
  pos_rejouer.x=(ecran->w/2)-(rejouer->w/1.8);
  pos_rejouer.y=(ecran->h/1.4)-(rejouer->h/5);
  SDL_FillRect(rejouer, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));//Cette fonction effectue un remplissage rapide du bouton rejouer
  SDL_SetColorKey(rejouer, SDL_SRCCOLORKEY, SDL_MapRGB(rejouer->format, 255, 255, 255));//Rendre la couleur du bouton transparente
  SDL_BlitSurface(rejouer, NULL, ecran, &pos_rejouer);
  
  //Position du bouton scores
  pos_scores.x=(ecran->w/2)-(scores->w/2);
  pos_scores.y=(ecran->h/1.215)-(scores->h/5);
  SDL_FillRect(scores, NULL, SDL_MapRGB(ecran->format, 255, 0, 255));//Cette fonction effectue un remplissage rapide du bouton scores
  SDL_SetColorKey(scores, SDL_SRCCOLORKEY, SDL_MapRGB(scores->format, 255, 0, 255));//Rendre la couleur du bouton transparente
  SDL_BlitSurface(scores, NULL, ecran, &pos_scores);
  
  //Position du bouton retour au menu principal
  pos_menu.x=(ecran->w/2)-(menu->w/2);
  pos_menu.y=(ecran->h/1.07)-(menu->h/5);
  SDL_FillRect(menu, NULL, SDL_MapRGB(ecran->format, 255, 255, 0));//Cette fonction effectue un remplissage rapide du bouton menu
  SDL_SetColorKey(menu, SDL_SRCCOLORKEY, SDL_MapRGB(menu->format, 255, 255, 0));//Rendre la couleur du bouton transparente
  SDL_BlitSurface(menu, NULL, ecran, &pos_menu);
  
  
  //Police du texte des boutons 
  police=TTF_OpenFont("BlackAsylumDEMO-KCFonts.ttf", 50);
  TTF_SetFontStyle(police, TTF_STYLE_BOLD);
  texte_rejouer=TTF_RenderText_Solid(police, "Rejouer", noir);
  texte_scores=TTF_RenderText_Solid(police, "Scores", noir);
  texte_menu=TTF_RenderText_Solid(police, "Menu Principal", noir);
  
  //position du texte rejouer
  pos_texte_rejouer.x=(ecran->w/2)-(rejouer->w/1.8);
  pos_texte_rejouer.y=(ecran->h/1.4)-(rejouer->h/5);
  pos_texte_rejouer.w=texte_rejouer->w;
  pos_texte_rejouer.h=texte_rejouer->h;
  
  SDL_BlitSurface(texte_rejouer, NULL, ecran, &pos_texte_rejouer);
  
  //position du texte scores
  pos_texte_scores.x=(ecran->w/2)-(scores->w/2);
  pos_texte_scores.y=(ecran->h/1.21)-(scores->h/5);
  pos_texte_scores.w=texte_scores->w;
  pos_texte_scores.h=texte_scores->h;
  
  SDL_BlitSurface(texte_scores, NULL, ecran, &pos_texte_scores);
  
  //position du texte menu principal
  pos_texte_menu.x=(ecran->w/2)-(menu->w/2);
  pos_texte_menu.y=(ecran->h/1.07)-(menu->h/5);
  pos_texte_menu.w=texte_menu->w;
  pos_texte_menu.h=texte_menu->h;
  
  SDL_BlitSurface(texte_menu, NULL, ecran, &pos_texte_menu);
 
  //Libération des surfaces de texte
  SDL_FreeSurface(texte_rejouer);
  SDL_FreeSurface(texte_scores);
  SDL_FreeSurface(texte_menu);
  TTF_CloseFont(police);
  
  SDL_Flip(ecran);//Mise à jour de l'écran
 
  //Gestion d'evenement de la souris
  while(continuer){
    SDL_WaitEvent(&event);
    switch(event.type){
    case SDL_QUIT:
      continuer=0;
      break;
    case SDL_MOUSEBUTTONUP:
      if(event.button.x>(ecran->w/2)-(rejouer->w/1.8) && event.button.x<=(ecran->w/2)-(rejouer->w/1.8)+LARGEUR && event.button.y>(ecran->h/1.4)-(rejouer->h/5) && event.button.y<=(ecran->h/1.4)-(rejouer->h/5)+HAUTEUR){
	continuer=0;
	joue_apres_parametrage(param);//Appel de la fonction joue_apres_parametrage pour pouvoir rejouer la partie avec les meme parametres
      }else if(event.button.x>(ecran->w/2)-(menu->w/2) && event.button.x<=(ecran->w/2)-(menu->w/2)+350 && event.button.y>(ecran->h/1.07)-(menu->h/5) && event.button.y<=(ecran->h/1.07)-(menu->h/5)+HAUTEUR){
	continuer=0;       
	Affichage_menu();//Appel de la fonction Affichage_menu pour retourner au menu principal
      }else 
	continuer=1; 
      break;
    }
  }
 
  SDL_FreeSurface(fond);//Libération de la surface
  SDL_FreeSurface(rejouer);//Liberation de la surface
  SDL_FreeSurface(scores);//Liberation de la surface
  SDL_FreeSurface(menu);//Liberation de la surface 
  TTF_Quit();//Arrête SDL_ttf
  SDL_Quit();//Libère la SDL de la mémoire
}

/**
 *\author Massinissa MOHANDI 
 *\brief Cette fonction verifie si on a gagné la partie.
 *\param parametre parametres de la grille 
 *\param ma_grille le tableau d'affichage des elements de notre ecran graphique durant le jeu
 *\return 1 si on a gagné la partie et 0 sinon 
*/

int Gagne(parametre_grille parametre,display_matrix ma_grille){
  int i,j,total_cases,nb_mines,nb_cases_devoilee;
  int nb_lignes=parametre->nb_lignes;
  int nb_colonnes=parametre->nb_colonnes;
  total_cases=nb_lignes*nb_colonnes;
  nb_mines=parametre->nb_mines;
  nb_cases_devoilee=0;
  for(i=0;i<nb_lignes;i++)//Double boucle qui verifie le nombre de cases devoilées 
    for(j=0;j<nb_colonnes;j++){
      if((ma_grille->tab[i][j]!=CARRE_CLAIR) && (ma_grille->tab[i][j]!=_MINE))
	nb_cases_devoilee++;
    }
  if(nb_cases_devoilee==total_cases-nb_mines){
    SDL_Delay(3500);
    Gagner_partie(parametre);//Appel a la fenetre Gagné
    return 1;
  }
  return 0;
}

/**
 *\author Massinissa MOHANDI 
 *\brief Cette fonction affiche la fenetre Gagné.
 *\param param parametres de la grille
 */

void Gagner_partie(parametre_grille param){
  putenv("SDL_VIDEO_WINDOW_POS=center");//Position de la fenetre
  SDL_Surface *ecran=NULL, *fond=NULL, *rejouer=NULL, *scores=NULL, *menu=NULL, *texte_rejouer=NULL, *texte_scores=NULL, *texte_menu=NULL;
  SDL_Rect pos_fond, pos_rejouer, pos_texte_rejouer, pos_scores, pos_texte_scores, pos_menu, pos_texte_menu; 
  SDL_Event event;
  TTF_Font *police=NULL;
  SDL_Color texte_couleur={255, 255, 0};
  int continuer=1;
  
  //Position de l'image de fond
  pos_fond.x=0; 
  pos_fond.y=0;
  
  SDL_Init(SDL_INIT_VIDEO);//Charge le système d'affichage
  TTF_Init();//démarre SDL_ttf
  
  ecran=SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);//Taille et Type de fenetre
  rejouer=SDL_CreateRGBSurface(SDL_HWSURFACE, LARGEUR, HAUTEUR, 32, 0, 0, 0, 0);//Taille et couleur du bouton
  scores=SDL_CreateRGBSurface(SDL_HWSURFACE, LARGEUR, HAUTEUR, 32, 0, 0, 0, 0);
  menu=SDL_CreateRGBSurface(SDL_HWSURFACE, 350, HAUTEUR, 32, 0, 0, 0, 0);
  
  SDL_WM_SetCaption("Bravo Vous Avez Gagné", NULL);// Nom de la fenetre
  
  fond=IMG_Load("Gagné.png");//Chargement de l'image de fond
  SDL_BlitSurface(fond, NULL, ecran, &pos_fond);
  
  //Position du bouton rejouer
  pos_rejouer.x=(ecran->w)-(rejouer->w/0.55);
  pos_rejouer.y=(ecran->h/2.3)-(rejouer->h/5);
  SDL_FillRect(rejouer, NULL, SDL_MapRGB(ecran->format, 255, 255, 255));//Cette fonction effectue un remplissage rapide du bouton rejouer
  SDL_SetColorKey(rejouer, SDL_SRCCOLORKEY, SDL_MapRGB(rejouer->format, 255, 255, 255));//Rendre la couleur du bouton transparente
  SDL_BlitSurface(rejouer, NULL, ecran, &pos_rejouer);
  
  //Position du bouton scores
  pos_scores.x=(ecran->w)-(scores->w/0.56);
  pos_scores.y=(ecran->h/1.8)-(scores->h/5);
  SDL_FillRect(scores, NULL, SDL_MapRGB(ecran->format, 255, 0, 255));//Cette fonction effectue un remplissage rapide du bouton scores
  SDL_SetColorKey(scores, SDL_SRCCOLORKEY, SDL_MapRGB(scores->format, 255, 0, 255));//Rendre la couleur du bouton transparente
  SDL_BlitSurface(scores, NULL, ecran, &pos_scores);
  
  //Position du bouton retour au menu principal
  pos_menu.x=(ecran->w)-(menu->w/0.92);
  pos_menu.y=(ecran->h/1.5)-(menu->h/5);
  SDL_FillRect(menu, NULL, SDL_MapRGB(ecran->format, 255, 255, 0));//Cette fonction effectue un remplissage rapide du bouton menu
  SDL_SetColorKey(menu, SDL_SRCCOLORKEY, SDL_MapRGB(menu->format, 255, 255, 0));//Rendre la couleur du bouton transparente
  SDL_BlitSurface(menu, NULL, ecran, &pos_menu);
  
  //Police du texte des boutons 
  police=TTF_OpenFont("BlackAsylumDEMO-KCFonts.ttf", 50);
  TTF_SetFontStyle(police, TTF_STYLE_BOLD);
  texte_rejouer=TTF_RenderText_Solid(police, "Rejouer", texte_couleur);
  texte_scores=TTF_RenderText_Solid(police, "Scores", texte_couleur);
  texte_menu=TTF_RenderText_Solid(police, "Menu Principal", texte_couleur);
  
  //position du texte rejouer
  pos_texte_rejouer.x=(ecran->w)-(rejouer->w/0.55);
  pos_texte_rejouer.y=(ecran->h/2.3)-(rejouer->h/5);
  pos_texte_rejouer.w=texte_rejouer->w;
  pos_texte_rejouer.h=texte_rejouer->h;
  
  SDL_BlitSurface(texte_rejouer, NULL, ecran, &pos_texte_rejouer);

  //position du texte scores
  pos_texte_scores.x=(ecran->w)-(scores->w/0.55);
  pos_texte_scores.y=(ecran->h/1.8)-(scores->h/5);
  pos_texte_scores.w=texte_scores->w;
  pos_texte_scores.h=texte_scores->h;
  
  SDL_BlitSurface(texte_scores, NULL, ecran, &pos_texte_scores);
  
  //position du texte menu principal
  pos_texte_menu.x=(ecran->w)-(menu->w/0.92);
  pos_texte_menu.y=(ecran->h/1.5)-(menu->h/5);
  pos_texte_menu.w=texte_menu->w;
  pos_texte_menu.h=texte_menu->h;
  
  SDL_BlitSurface(texte_menu, NULL, ecran, &pos_texte_menu);
  
  //Libération des surfaces de texte
  SDL_FreeSurface(texte_rejouer);
  SDL_FreeSurface(texte_scores);
  SDL_FreeSurface(texte_menu);
  TTF_CloseFont(police);
  
  SDL_Flip(ecran);//Mise à jour de l'écran
  
  //Gestion d'evenement de la souris
  while(continuer){
    SDL_WaitEvent(&event);
    switch(event.type){
    case SDL_QUIT:
      continuer=0;
      break;
    case SDL_MOUSEBUTTONUP:
      if(event.button.x>(ecran->w)-(rejouer->w/0.55) && event.button.x<=(ecran->w)-(rejouer->w/0.55)+LARGEUR && event.button.y>(ecran->h/2.3)-(rejouer->h/5) && event.button.y<=(ecran->h/2.3)-(rejouer->h/5)+HAUTEUR){
	continuer=0;       
	joue_apres_parametrage(param);//Appel de la fonction joue_apres_parametrage pour pouvoir rejouer la partie avec les meme parametres
      }else if(event.button.x>(ecran->w)-(menu->w/0.92) && event.button.x<=(ecran->w)-(menu->w/0.92)+350 && event.button.y>(ecran->h/1.5)-(menu->h/5) && event.button.y<=(ecran->h/1.5)-(menu->h/5)+HAUTEUR){
	continuer=0;       
	Affichage_menu();//Appel de la fonction Affichage_menu pour retourner au menu principal
      }else 
	continuer=1; 
      break;
    }
  }
  
  
  SDL_FreeSurface(fond);//Libération de la surface
  SDL_FreeSurface(rejouer);
  SDL_FreeSurface(scores);
  SDL_FreeSurface(menu);
  TTF_Quit();//Arrête SDL_ttf
  SDL_Quit();//Libère la SDL de la mémoire
}

/**
 *\author Massinissa MOHANDI 
 *\brief Fonction d'affichage des regles du jeu. 
*/

void Regles(){
  putenv("SDL_VIDEO_WINDOW_POS=center");//Position de la fenetre
  SDL_Surface *ecran=NULL, *fond=NULL, *menu=NULL, *texte_menu=NULL;
  SDL_Rect pos_fond, pos_menu, pos_texte_menu; 
  SDL_Event event;
  TTF_Font *police=NULL;
  SDL_Color noir={1, 9, 10};
  SDL_Color texte_couleur={53, 94, 138};
  int continuer=1;
  
  //Position de l'image de fond
  pos_fond.x=0; 
  pos_fond.y=0;

  SDL_Init(SDL_INIT_VIDEO);//Charge le système d'affichage
  TTF_Init();//démarre SDL_ttf
  
  ecran=SDL_SetVideoMode(800, 600, 32, SDL_HWSURFACE);//Taille et Type de fenetre
  menu=SDL_CreateRGBSurface(SDL_HWSURFACE, 350, HAUTEUR, 32, 0, 0, 0, 0);
  
  SDL_WM_SetCaption("Regles du jeu", NULL);// Nom de la fenetre
  
  fond=IMG_Load("Regles.jpg");//Chargement de l'image de fond
  SDL_BlitSurface(fond, NULL, ecran, &pos_fond);

  //Position du bouton retour au menu principal
  pos_menu.x=(ecran->w/2)-(menu->w/2);
  pos_menu.y=(ecran->h/1.1)-(menu->h/5);
  SDL_FillRect(menu, NULL, SDL_MapRGB(ecran->format, 255, 255, 0));//Cette fonction effectue un remplissage rapide du bouton menu
  SDL_SetColorKey(menu, SDL_SRCCOLORKEY, SDL_MapRGB(menu->format, 255, 255, 0));//Rendre la couleur du bouton transparente
  SDL_BlitSurface(menu, NULL, ecran, &pos_menu);
  
  //Police du texte des boutons 
  police=TTF_OpenFont("BlackAsylumDEMO-KCFonts.ttf", 50);
  TTF_SetFontStyle(police, TTF_STYLE_BOLD);
  texte_menu=TTF_RenderText_Solid(police, "Menu Principal", texte_couleur);
  
  //position du texte menu principal
  pos_texte_menu.x=(ecran->w/2)-(menu->w/2);
  pos_texte_menu.y=(ecran->h/1.1)-(menu->h/5);
  pos_texte_menu.w=texte_menu->w;
  pos_texte_menu.h=texte_menu->h;
  
  SDL_BlitSurface(texte_menu, NULL, ecran, &pos_texte_menu);
 
  //Libération des surfaces de texte
  SDL_FreeSurface(texte_menu);
  TTF_CloseFont(police);
  
  SDL_Flip(ecran);//Mise à jour de l'écran
 
  //Gestion d'evenement de la souris
  while(continuer){
    SDL_WaitEvent(&event);
    switch(event.type){
    case SDL_QUIT:
      continuer=0;
      break;
    case SDL_MOUSEBUTTONUP:
      if(event.button.x>(ecran->w/2)-(menu->w/2) && event.button.x<=(ecran->w/2)-(menu->w/2)+350 && event.button.y>(ecran->h/1.1)-(menu->h/5) && event.button.y<=(ecran->h/1.1)-(menu->h/5)+HAUTEUR){
	continuer=0;       
	Affichage_menu();//Appel de la fonction Affichage_menu pour retourner au menu principal
      }else 
	continuer=1; 
      break;
    }
  }
  
  SDL_FreeSurface(fond);//Libération de la surface
  SDL_FreeSurface(menu);//Liberation de la surface 
  TTF_Quit();//Arrête SDL_ttf
  SDL_Quit();//Libère la SDL de la mémoire
}
