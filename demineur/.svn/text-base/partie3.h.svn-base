
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_getenv.h>

int VRAI=1,FAUX=0;

// lie au font
enum{FONTCOMIC};


//grille de calcul //lie a grille->matrice
enum{_VIDE,_MINE,_UN,_DEUX,_TROIS,_QUATRE,_CINQ,_SIX,_SEPT,_HUIT};


// Au lieu d'utiliser des nombres on utilise des constantes de valeur toutes differentes pour representer les elements de notre zone de jeu
enum {MUR, MINE_, VIDE_, UN_, DEUX_, TROIS_, QUATRE_, CINQ_, SIX_, SEPT_, HUIT_, DRAPEAU_, LIBRE_, DEVOILER};

//carre clair est le carre non clique, le fonce est le clique et le vide est le carre decouvert et sans chiffre ni voisins.
enum{CARRE_CLAIR,CARRE_FONCE,VIDE,UN,DEUX,TROIS,QUATRE,CINQ,SIX,SEPT,HUIT,MINE,DRAPEAU,GRANDE_MINE,CLOCK,BONHOMME_PLEURE,BONHOMME_SOURIT,FOND_ECRAN};
enum{RECTANGLE_CHRONO,RECTANGLE_DRAPEAU,RECTANGLE_PAUSE};  // les rectangles de fonds de textes
enum{DRAPEAU_RESTANT_TEXT,TIME_TEXT,PAUSE_TEXT};  // les textes a coller sur l'ecran
enum{DRAPEAU_RESTANT,TIME,PAUSE}; //les surfaces liees aux textes

struct Timer{
  int startTicks;
  int pausedTicks;
  int paused;
  int started;
};
typedef struct Timer* Timer;

Timer init_Timer();

void start(Timer t);

int get_time(Timer t);


int  is_paused(Timer t);

int is_started(Timer T);


//auteur: Nouri Alexandre
struct Context  // Le contexte : c'est le contexte du jeu : tout ce qui définit le jeu.
{
  SDL_Surface* screen;    // la surface screen.
  SDL_Surface** image;   // tableau d'images_a_charger
  SDL_Surface** surface;  // tableau de surfaces
  SDL_Surface** surface_text;
  TTF_Font** font;  // tableau de font
  char** text;
  int XRES,YRES;          // résolution de la fenêtre
  int nbimg;              // nombre d'images (taille du tableau ci-dessus)
  int nbsurface;        // nombre de surfaces
  int nb_text;
  int nb_surface_text;
  int nbfont; // nombre de font
  int compteur; // compteur le temps ecoule en secondes
  int game_start; //renvoie VRAI si le jeu a commence et FAUX sinon
};
typedef struct Context* Context;

void pause(Timer t);
void unpause(Timer t);

void actualise_pause(Context C,Timer t);

//auteur:Nouri
//structure utilisee dans la simplification de l'utilisation de la SDL
struct Input{
  char key[SDLK_LAST];
  char mousebuttons[8];
  int mousex,mousey; 
  char quit;
};
typedef struct Input* Input;

struct parametre{
  int nb_lignes;
  int nb_colonnes;
  int nb_mines;
};
typedef struct parametre* parametre_grille;

struct grille{
  int** matrice;
};
typedef struct grille* grille;

struct display_matrix{
  int** tab;
};
typedef struct display_matrix* display_matrix;

void *my_malloc(size_t size);
void *my_realloc(void *p, size_t size);
grille new_grille_exemple(parametre_grille p);
parametre_grille new_param_exemple();
int Init(Context C,int x, int y);
int Release(Context C);
int LoadAll(Context C);
SDL_Surface* LoadImageSDL(char* fichier);
display_matrix new_display_matrix(parametre_grille p);
void jouer(Context C,grille ma_grille,parametre_grille parametre);
void init_jeu(display_matrix ma_grille,parametre_grille p);
void actualise_ecran(Context C, grille ma_grille,parametre_grille parametre,display_matrix affiche_tab);
void affiche_case(int i, int j, Context C, display_matrix affiche_tab,SDL_Rect* pos);
void UpdateEvents(Input in);
void deploiement(int i, int j,display_matrix  ma_grille_affiche, grille ma_grille,parametre_grille p);
void sous_deploiement(int i, int j,display_matrix  ma_grille_affiche, grille ma_grille,parametre_grille p);
void actualise_grille(display_matrix  ma_grille_affiche,grille ma_grille,parametre_grille param);
void placer_le_bon_carre(int i,int j, display_matrix affiche_tab,grille ma_grille);
TTF_Font* Load_font(char* fichier,int taille);
void devoiler_toutes_mines(display_matrix affiche_tab,grille ma_grille, parametre_grille parametre);

