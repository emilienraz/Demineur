#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_getenv.h>


#define NB_LIGNES_MAX 24
#define NB_COLONNES_MAX 30
#define HAUTEUR 50
#define LARGEUR 155
#define VRAI 1
#define FAUX 0

struct parametre_grilles{
  int nb_lignes;
  int nb_colonnes;
  int nb_mines;
};
typedef struct parametre_grilles *parametre_grille;

struct tableau{
  int matrice[NB_LIGNES_MAX][NB_COLONNES_MAX];
};
typedef struct tableau *tableau;



// lie au font
enum{FONTCOMIC};

//grille de calcul //lie a grille->matrice
enum{_VIDE,_MINE,_UN,_DEUX,_TROIS,_QUATRE,_CINQ,_SIX,_SEPT,_HUIT};

// Au lieu d'utiliser des nombres on utilise des constantes de valeur toutes differentes pour representer les elements de notre zone de jeu
enum {MUR, MINE_, VIDE_, UN_, DEUX_, TROIS_, QUATRE_, CINQ_, SIX_, SEPT_, HUIT_, DRAPEAU_, LIBRE_, DEVOILER};

//carre clair est le carre non clique, le fonce est le clique et le vide est le carre decouvert et sans chiffre ni voisins.
enum{CARRE_CLAIR,CARRE_FONCE,VIDE,UN,DEUX,TROIS,QUATRE,CINQ,SIX,SEPT,HUIT,MINE,DRAPEAU,GRANDE_MINE,CLOCK,BONHOMME_SOURIT,FOND_ECRAN,PAUSE_FOND_ECRAN};
enum{RECTANGLE_CHRONO,RECTANGLE_DRAPEAU};  // les rectangles de fonds de textes
enum{DRAPEAU_RESTANT_TEXT,TIME_TEXT,PAUSE_TEXT};  // les textes a coller sur l'ecran
enum{DRAPEAU_RESTANT,TIME,PAUSE,RETOUR_MENU}; //les surfaces liees aux textes


struct Timer{
  int startTicks;
  int pausedTicks;
  int paused;
  int started;
};
typedef struct Timer* Timer;

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


struct Input{
  char key[SDLK_LAST];
  char mousebuttons[8];
  int mousex,mousey; 
  char quit;
};
typedef struct Input* Input;


struct grille{
  int** matrice;
};
typedef struct grille* grille;

struct display_matrix{
  int** tab;
};
typedef struct display_matrix* display_matrix;



void Initialise(tableau,parametre_grille);
void Pose_mines(tableau,parametre_grille);
void Calcule_voisins(tableau,parametre_grille);
void Facile(parametre_grille);
void Moyen(parametre_grille);
void Difficile(parametre_grille);
void Affichage_parametres(parametre_grille);
void Nouvelle_grille(parametre_grille,tableau);
grille Conversion(parametre_grille, tableau);
int joue_apres_parametrage(parametre_grille);
void personnalise(parametre_grille);
void clean_stdin(void);


void Affichage_menu();
void Perdu(Context,display_matrix,grille,parametre_grille);
void Perdre_partie(parametre_grille);
int Gagne(parametre_grille,display_matrix);
void Gagner_partie(parametre_grille);
void Regles();


Timer init_Timer();
void start(Timer);
int get_time(Timer);
int  is_paused(Timer);
int is_started(Timer);
void pause(Timer);
void unpause(Timer);
void actualise_pause(Context,Timer);
void *my_malloc(size_t);
void *my_realloc(void*, size_t);
grille new_grille_exemple(parametre_grille);
parametre_grille new_param_exemple();
int Init(Context, int, int);
int Release(Context);
int LoadAll(Context);
SDL_Surface* LoadImageSDL(char*);
display_matrix new_display_matrix(parametre_grille);
void jouer(Context, grille, parametre_grille);
void init_jeu(display_matrix, parametre_grille);
void actualise_ecran(Context, grille, parametre_grille, display_matrix);
void affiche_case(int, int, Context, display_matrix, SDL_Rect*);
void UpdateEvents(Input);
void deploiement(int , int , display_matrix, grille , parametre_grille);
void sous_deploiement(int, int, display_matrix, grille, parametre_grille);
void actualise_grille(display_matrix, grille, parametre_grille);
void placer_le_bon_carre(int, int, display_matrix, grille);
TTF_Font* Load_font(char*, int);
void devoiler_toutes_mines(display_matrix, grille, parametre_grille);
int nouvelle_partie();
