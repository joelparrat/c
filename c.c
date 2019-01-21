
// nom:C
// version:0.1
// long:Lancement compilateur

#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>
#include <dirent.h>
#include <time.h>
#include <errno.h>

#ifndef FALSE
#define FALSE 0
#endif
#ifndef TRUE
#define TRUE !FALSE
#endif
#ifndef false
#define false 0
#endif
#ifndef true
#define true !false
#endif

#define CNF "/var/local/cnf"
#define NUM "0123456789."
#define GCC "gcc"

#define LNGSTR 256
#define LNGLGN 80
#define LNGPRJ 11
#define LNGVRS 11

#ifndef LG_SYS
#define LG_SYS 0
#endif
#ifndef LG_ERR
#define LG_ERR 1
#endif
#ifndef LG_ATT
#define LG_ATT 2
#endif
#ifndef LG_INF
#define LG_INF 3
#endif

// .asm

#ifndef LXV_ERREUR
#define LXV_ERREUR -1
#endif
#ifndef LXV_FIN
#define LXV_FIN 0
#endif
#ifndef LXV_BLANC
#define LXV_BLANC 1
#endif
#ifndef LXV_SEPARATEUR
#define LXV_SEPARATEUR 2
#endif
#ifndef LXV_OPERATEUR
#define LXV_OPERATEUR 3
#endif
#ifndef LXV_PREPROCESSEUR
#define LXV_PREPROCESSEUR 4
#endif
#ifndef LXV_INCLUDE_SYS
#define LXV_INCLUDE_SYS 5
#endif
#ifndef LXV_INCLUDE_FCH
#define LXV_INCLUDE_FCH 6
#endif
#ifndef LXV_ENTIER
#define LXV_ENTIER 7
#endif
#ifndef LXV_ENTIER_BINAIRE
#define LXV_ENTIER_BINAIRE 8
#endif
#ifndef LXV_ENTIER_OCTAL
#define LXV_ENTIER_OCTAL 9
#endif
#ifndef LXV_ENTIER_HEXA
#define LXV_ENTIER_HEXA 10
#endif
#ifndef LXV_REEL
#define LXV_REEL 11
#endif
#ifndef LXV_CONST_CAR
#define LXV_CONST_CAR 12
#endif
#ifndef LXV_CONST_TEXTE
#define LXV_CONST_TEXTE 13
#endif
#ifndef LXV_IDENTIFIANT
#define LXV_IDENTIFIANT 14
#endif
#ifndef LXV_INSTRUCTION
#define LXV_INSTRUCTION 15
#endif
#ifndef LXV_LABEL
#define LXV_LABEL 16
#endif
#ifndef LXV_REGISTRE
#define LXV_REGISTRE 17
#endif
#ifndef LXV_MACRO
#define LXV_MACRO 18
#endif
#ifndef LXV_ADRESSE
#define LXV_ADRESSE 19
#endif
#ifndef LXV_COMMENTAIRE
#define LXV_COMMENTAIRE 20
#endif
#ifndef LXV_FONCTION
#define LXV_FONCTION 21
#endif

#ifndef LXV_TLLULX
#define LXV_TLLULX 256
#endif
#ifndef LXV_TLLNOM
#define LXV_TLLNOM 256
#endif

#define LGTSTR 255
#define LGTBUF 64000
#define LGTEQU 64
#define NBREQU 255
#define LGTDEF 64
#define NBRDEF 255
#define LGTLBL 64
#define NBRLBL 255
#define LGTLNK 64
#define NBRLNK 255
#define MMYPRG 4000
#define NBRINS 255
#define VALLGN 8

#define UL_FN -1	// fin
#define UL_ER 0		// erreur (inconnu)
#define UL_TX 1		// texte
#define UL_LB 2		// label
#define UL_NB 3		// nombre
#define UL_VR 4		// virgule (separateur)
#define UL_EG 5		// egal (affectation)
#define UL_OP 6		// operation (+ - * / < > << >> | & || && == ~ ^)
#define UL_PT 9		// point (directive)
#define UL_DI 10	// diese (directive)
#define UL_GU 11	// contenu des guillements
#define UL_PG 12	// parenthese gauche
#define UL_PD 13	// parenthese droite
#define UL_RG 14	// registre general de R0 a R15
#define UL_RW 15	// registre de travail de R16 a R31
#define UL_RL 16	// registre double pour adressage x, x+, -x : R26&R27 et y, y+, -y : R28&R29 et z, z+, -z : R30&R31
#define UL_IN 17	// instruction du language

#define OP_PL 0		// +
#define OP_MN 1		// -
#define OP_ML 2		// *
#define OP_DV 3		// /
#define OP_IN 4		// <
#define OP_SP 5		// >
#define OP_DG 6		// <<
#define OP_DD 7		// >>
#define OP_AN 8		// &
#define OP_OR 9		// |
#define OP_ET 10	// &&
#define OP_OU 11	// ||
#define OP_EG 12	// ==
#define OP_TL 13	// ~
#define OP_XR 14	// ^

// .c ou .h

#ifndef LXC_ERREUR
#define LXC_ERREUR -1
#endif
#ifndef LXC_FIN
#define LXC_FIN 0
#endif
#ifndef LXC_BLANC
#define LXC_BLANC 1
#endif
#ifndef LXC_SEPARATEUR
#define LXC_SEPARATEUR 2
#endif
#ifndef LXC_OPERATEUR
#define LXC_OPERATEUR 3
#endif
#ifndef LXC_COMMENTAIRE_CPP
#define LXC_COMMENTAIRE_CPP 4
#endif
#ifndef LXC_COMMENTAIRE_C
#define LXC_COMMENTAIRE_C 5
#endif
#ifndef LXC_PREPROCESSEUR
#define LXC_PREPROCESSEUR 6
#endif
#ifndef LXC_INCLUDE_SYS
#define LXC_INCLUDE_SYS 7
#endif
#ifndef LXC_INCLUDE_FCH
#define LXC_INCLUDE_FCH 8
#endif
#ifndef LXC_ENTIER
#define LXC_ENTIER 9
#endif
#ifndef LXC_ENTIER_BINAIRE
#define LXC_ENTIER_BINAIRE 10
#endif
#ifndef LXC_ENTIER_OCTAL
#define LXC_ENTIER_OCTAL 11
#endif
#ifndef LXC_ENTIER_HEXA
#define LXC_ENTIER_HEXA 12
#endif
#ifndef LXC_REEL
#define LXC_REEL 13
#endif
#ifndef LXC_CONST_CAR
#define LXC_CONST_CAR 14
#endif
#ifndef LXC_CONST_TEXTE
#define LXC_CONST_TEXTE 15
#endif
#ifndef LXC_IDENTIFIANT
#define LXC_IDENTIFIANT 16
#endif
#ifndef LXC_MOT_CLEF
#define LXC_MOT_CLEF 17
#endif
#ifndef LXC_TYPE_C
#define LXC_TYPE_C 18
#endif
#ifndef LXC_TYPE_LIBC
#define LXC_TYPE_LIBC 19
#endif
#ifndef LXC_TYPE_GTK
#define LXC_TYPE_GTK 20
#endif
#ifndef LXC_TYPE_SDL
#define LXC_TYPE_SDL 21
#endif
#ifndef LXC_CONST_C
#define LXC_CONST_C 22
#endif
#ifndef LXC_CONST_LIBC
#define LXC_CONST_LIBC 23
#endif
#ifndef LXC_CONST_GTK
#define LXC_CONST_GTK 24
#endif
#ifndef LXC_CONST_SDL
#define LXC_CONST_SDL 25
#endif
#ifndef LXC_FONCTION_C
#define LXC_FONCTION_C 26
#endif
#ifndef LXC_FONCTION_LIBC
#define LXC_FONCTION_LIBC 27
#endif
#ifndef LXC_FONCTION_GTK
#define LXC_FONCTION_GTK 28
#endif
#ifndef LXC_FONCTION_SDL
#define LXC_FONCTION_SDL 29
#endif
#ifndef LXC_FONCTION
#define LXC_FONCTION 30
#endif

#ifndef LXC_TLL
#define LXC_TLL 256
#endif

// .hex

#ifndef LXX_DXP
#define LXX_DXP 0
#endif
#ifndef LXX_LNG
#define LXX_LNG 1
#endif
#ifndef LXX_ADR
#define LXX_ADR 2
#endif
#ifndef LXX_TYP
#define LXX_TYP 3
#endif
#ifndef LXX_DNN
#define LXX_DNN 4
#endif
#ifndef LXX_CHC
#define LXX_CHC 5
#endif
#ifndef LXX_NWL
#define LXX_NWL 6
#endif

typedef struct _lxc
{
	int  ul;
	char *ulx;
	char *bff;
	char *motclf;
	char *typc;
	char *typlbc;
	char *typgtk;
	char *typsdl;
	char *cnsc;
	char *cnslbc;
	char *cnsgtk;
	char *cnssdl;
	char *fncc;
	char *fnclbc;
	char *fncgtk;
	char *fncsdl;
} LXC;

// Unite lexicale

typedef struct _ulv
{
	int ul;
	char *ulx;//n[LGTSTR];
	//int v;
} ULV;

// .equ

typedef struct _equ
{
	char n[LGTEQU];
	int v;
} EQU;//equ[NBREQU];

// .def

typedef struct _def
{
	char n[LGTDEF];
	char v[LGTDEF];
} DEF;//def[NBRDEF];

// Label

typedef struct _lbl
{
	char n[LGTLBL];
	int v;
} LBL;//lbl[NBRLBL];

// lien

typedef struct _lnk
{
	char n[LGTLNK];
	int v;
	int i;
} LNK;//tbllnk[NBRLNK];

// Parametre des instructions

typedef struct _prm
{
	char nom[8];
	int val;
	char nbr;
	int msk[4];
	int shf[4];
} PRM;

// Instruction

typedef struct _ins
{
	char syn[32];			// syntaxe de l'instruction
	char ins[16];			// instruction en minuscule ou majuscule en fonction de g_mM
	char nbr;				// nombre de parametres
	PRM  strprm[2];   		// parametre de l'instruction 0=destination 1=source
	int opc;				// opcode
	char mch[48];			// code machine
} INS;//strins[NBRINS];

// nom de fichier

typedef struct _fch
{
	char *nins;				// nom fichier inst.cnf
	char *nasm;				// nom fichier *.asm
	char *nhex;				// nom fichier *.hex
	char *ninc;				// nom dossier *.inc
	char *nlst;				// nom fichier *.lst
	char *nmap;				// nom fichier *.map
	char *nstd;				// nom fichier *.asm (standardise)
} FCH;

// Erreur

typedef struct _err
{
	char n[32];		// nom du fichier en cours
	int v;			// numero de ligne
	char sn[32];	// sauvegarde nom du fichier precedent
	int sv;			// sauvegarde numero de ligne precedente
} ERR;

// Toute la partie lexicale

typedef struct _lxv
{
	int  ul;
	char *ulx;
	//ULV  *ulv;
	EQU  **equ;
	DEF  **def;
	LBL  **lbl;
	LNK  **lnk;
	PRM  *prm;
	INS  **ins;
	FCH  *fch;
	ERR  *err;
	char *bff;
	char *avrins;
	char *avrmcr;
	char *avrppr;
	char *avrrgs;
	char *avradr;
	char gtr, gmM;
	int  gpc, indequ, inddef, indlbl, indlnk, indins;
	unsigned int tblins[MMYPRG];
	char tblmap[MMYPRG][32];
} LXV;
LXV *lxv;

typedef struct _lxr
{
	int  ul;
	char *ulx;
	char *bff;
	char *motclf;
	char *typc;
	char *typlbc;
	char *typgtk;
	char *typsdl;
	char *cnsc;
	char *cnslbc;
	char *cnsgtk;
	char *cnssdl;
	char *fncc;
	char *fnclbc;
	char *fncgtk;
	char *fncsdl;
} LXR;

typedef struct _en
{
	int  oto;	// -auto
	int  ntr;	// niveau trace
	int  tll;	// taille de mmr (pour ne pas deborder et realloc)
	char *mmr;	// zone memoire pour stockage en.* (debut pour free)
	char *lbr;	// zone memoire libre de mmr (pour strcpy et debordement)
	char *hom;	// chemin HOME
	char *usr;	// nom USER
	char *prj;	// nom projet
	char *vrs;	// nom version
	char *cnf;	// chemin configuration
	char *icn;	// chemin icon
	char *fch;	// chemin fichier
	char *log;	// chemin log
	char *bin;	// chemin binaire
	char *app;	// chemin application
	char *out;	// chemin output
	char *err;	// chemin error
	char *gtk;	// chemin dvl/gtk
	char *sdl;	// chemin dvl/sdl
	char *wnd;	// chemin dvl/windows
	char *avrc;	// chemin dvl/avr/c
	char *avrasm;	// chemin dvl/avr/asm
	char *avrhex;	// chemin dvl/avr/hex
	char *avrinc;	// chemin dvl/avr/hex
	char *armc;	// chemin dvl/arm/c
	char *armasm;	// chemin dvl/arm/asm
	char *armhex;	// chemin dvl/arm/hex
	char *www;	// chemin dvl/www
} EN;
EN en;

typedef struct _iv
{
	char db[5];
	char nm[11];
	char vr[9];
	char dt[8];
	char fn[7];
} IV;
IV iv = {"joel", "c", "0.1", "10/2014", "parrat"};

typedef struct _ch
{
	struct _ch *prior;	// precedent
	struct _ch *next;	// suivant
	char *texte1;
	char *texte2;
	char *texte3;
	int  nombre;
	char caractere;
} CH;

typedef struct _ls
{
	CH *first;		// premier
	CH *current;	// courant
	CH *last;		// dernier
} LS;

typedef struct _el
{
	struct _el *prior;	// precedent
	struct _el *next;	// suivant
	char *fichier;
	off_t taille;
	time_t modif;
} EL;

typedef struct _dr
{
	EL *first;		// premier
	EL *current;	// courant
	EL *last;		// dernier
} DR;

typedef struct _lg
{
	FILE *log;
	int  ntr;
	int  grv;
	char nom[32];
	char prj[32];
	char unt[32];
	char fnc[32];
	char mss[128];
	char err[128];
	int  tll;
	char nmb;
} LG;
LG lg;

// nom: bbles
// long: Bibliotheque gestion sequence escape

void es_cld(void);
void es_cls(void);
void es_clf(void);
void es_gotoxy(int, int);
void es_efd(void);
void es_efl(void);
void es_eff(void);
void es_encre(char *);
void es_fond(char *);

// string (nom complet)
struct _str
{
	char bin[256];	// les bin unix
	//char app[256];	// mon appli
	char src[256];	// les sources
	char lnc[256];	// pour execv (fi_lance)
	char dir[256];	// pour chdir
	char out[256];	// redirection sortie
	char err[256];	// redirection erreur
} str;

// Declaration des fonctions

int  fi_init(int, char **, char **);
int  fi_trtprj(void);
int fi_lance(char *p_cmd, int p_att, char *p_out, char *p_err, char **p_arg);
void fv_link(char *, LS *, LS *, LS *);
void fv_printf(char *, char *, char *, ...);
void fv_prglog(void);
void fv_compile(void);

LS  *ls_cns(void);				// Creation d'une liste
void ls_adc(LS *, char *, ...);	// add avec double tri croissant
void ls_add(LS *, char *, ...);	// add avec double tri decroissant
void ls_adp(LS *, char *, ...);	// add avec double sans tri en debut de liste
void ls_adf(LS *, char *, ...);	// add avec double sans tri en fin de liste
void ls_asc(LS *, char *, ...);	// add sans double tri croissant
void ls_asd(LS *, char *, ...);	// add sans double tri decroissant
void ls_asp(LS *, char *, ...);	// add sans double sans tri en debut de liste
int  ls_asf(LS *, char *, ...);	// add sans double sans tri en fin de liste
void ls_spp(LS *, int);			// Supprime un texte de la liste a la position p
void ls_vid(LS *);				// Vide toute la liste
void ls_nth(LS *, int);			// Positionnement sur le nieme texte de la liste
int  ls_txt1(LS *, char *);		// Recherche un texte1 dans la liste
int  ls_txt2(LS *, char *);		// Recherche un texte2 dans la liste
int  ls_txt3(LS *, char *);		// Recherche un texte3 dans la liste
int  ls_mrq(LS *, char);			// Recherche un caractere dans la liste (marque)
int  ls_mtx(LS *, char *, char);	// Marque un texte dans la liste
int  ls_mps(LS *, int, char);		// Marque une position dans la liste
void ls_prn(LS *);				// Vide dans stdout le contenu de la liste
void ls_dst(LS *);				// Detruit la liste

DR  *dr_cns(void);
void dr_add(DR *, char *, off_t, time_t);
void dr_spp(DR *, int);
void dr_vid(DR *);
int  dr_nom(DR *, char *);
int  dr_tll(DR *, off_t);
int	 dr_mdf(DR *, time_t);
void dr_prn(DR *);
void dr_dst(DR *);

int  en_get(int, char **, char **);

int  lg_cns(void);
void lg_ecr(void);
void lg_dst(void);
void lg_strcpy(char *dst, char *src);
void lg_strcat(char *dst, char *src);
void lg_strncpy(char *dst, char *src, int lng);

// c = c (ubuntu avr arm)
LXC  *lxc_cns(char *);
int  lxc_anl(LXC *);
void lxc_dst(LXC *);
// v = avr asm
LXV *lxv_cns(void);
int  lxv_lbl(LXV *, LS *);
int  lxv_anl(LXV *, LS *);
void lxv_dst(LXV *);
// r = arm asm
LXR *lxr_cns(char *);
int  lxr_anl(LXR *);
void lxr_dst(LXR *);
int  fct_cp(char *src, char *dst);

char *io_bfffch(char *, int *);
LS   *io_lstfch(char *, char);
int  io_ecrbff(char *, char *, int);
void io_frebff(char *);
int  io_cpsd(char *, char *);
int  io_mvsd(char *, char *);

int  iv_info(char *, int, char *, char *, char *);

// MAIN

int main(int argc, char *argv[], char *envv[])
{
	int ret;
	
	// Initialisation	
	if (ret = fi_init(argc, argv, envv))
		return(ret);

	// Traitement du projet
	if (ret = fi_trtprj())
		return(ret);
	
	// Purge le dossier log (supprime tous les fichiers vides)
	fv_prglog();
	
	// Liberation memoire
	if (en.mmr)
		free(en.mmr);
	
	return(0);
}

// Initialisation

int fi_init(int argc, char **argv, char **envv)
{
	FILE *lo;
	char *p, ligne[LNGLGN];

	es_cls();
	es_gotoxy(1, 1);
	
	if (argc == 1)
	{
		fv_printf("Cyan", "Syntaxe:", "c projet [version]\n");
		return(1);
	}
	
	// Init du log

	lg.ntr = 3;
	lg.grv = LG_INF;
	lg_strcpy(lg.prj, "c");
	lg_strcpy(lg.unt, "c");
	lg_strcpy(lg.fnc, "fi_init");
	lg.nmb = 0;
	lg.tll = 0;
	lg_cns();

	//lg_strcpy(lg.mss, "en.prj =");
	//lg_strcpy(lg.err, en.prj);
	//lg_ecr();

	// Les variables d'environements

	if (en_get(argc, argv, envv))	// attention vide la structure en avant de garnir
		return(-1);
	
	// Si les variables d'environements n'existent pas
	// Lecture du fichier de config
	
	if (en.cnf == NULL)
	{
		en.cnf = CNF;
		sprintf(ligne, "%s/c", en.cnf);	
		if ((lo = fopen(ligne, "r")) == NULL)
		{
			fv_printf("Jaune", "Erreur ouverture CNF:", "%s\n", strerror(errno));
			return(-1);
		}
		
		while (fgets(ligne, sizeof(ligne), lo))
		{
			if ((p = strchr(ligne, '\n')) != NULL)
				*p = 0;
			if ((p = strchr(ligne, '\r')) != NULL)
				*p = 0;
//printf("reste=%d %d %d\n", en.tll, (int)(en.lbr-en.mmr), en.tll-(int)(en.lbr-en.mmr));
			if (strlen(&ligne[4]) > (en.tll-(en.lbr-en.mmr)))
			{
				fv_printf("Jaune", "Erreur:", "manque de place pour copie la CNF\n");
				fclose(lo);
				return(-1);
			}
			if (strncmp(ligne, "gtk=", 4) == 0)
			{
				strcpy(en.lbr, &ligne[4]);
				en.gtk = en.lbr;
				en.lbr += strlen(&ligne[4]) + 1;
			}
			if (strncmp(ligne, "sdl=", 4) == 0)
			{
				strcpy(en.lbr, &ligne[4]);
				en.sdl = en.lbr;
				en.lbr += strlen(&ligne[4]) + 1;
			}
			if (strncmp(ligne, "icn=", 4) == 0)
			{
				strcpy(en.lbr, &ligne[4]);
				en.icn = en.lbr;
				en.lbr += strlen(&ligne[4]) + 1;
			}
			if (strncmp(ligne, "bin=", 4) == 0)
			{
				strcpy(en.lbr, &ligne[4]);
				en.bin = en.lbr;
				en.lbr += strlen(&ligne[4]) + 1;
			}
			if (strncmp(ligne, "app=", 4) == 0)
			{
				strcpy(en.lbr, &ligne[4]);
				en.app = en.lbr;
				en.lbr += strlen(&ligne[4]) + 1;
			}
			if (strncmp(ligne, "out=", 4) == 0)
			{
				strcpy(en.lbr, &ligne[4]);
				en.out = en.lbr;
				en.lbr += strlen(&ligne[4]) + 1;
			}
			if (strncmp(ligne, "err=", 4) == 0)
			{
				strcpy(en.lbr, &ligne[4]);
				en.err = en.lbr;
				en.lbr += strlen(&ligne[4]) + 1;
			}
			//if (strncmp(ligne, "cnf=", 4) == 0)
			//{
			//	strcpy(en.lbr, &ligne[4]);
			//	en.cnf = en.lbr;
			//	en.lbr += strlen(&ligne[4]) + 1;
			//}
		}
		fclose(lo);
	}
	
	if (argc > 1)
		en.prj = *(argv+1);
	if (argc > 2)
	{
		if (strlen(*(argv+2)) > (LNGVRS-1))
		{
			fv_printf("Jaune", "Version demandee:", "nom trop long (>%d)\n", LNGVRS-1);
			return(-1);
		}
		if (strlen(*(argv+2)) > (en.tll-(en.lbr-en.mmr)))
		{
			fv_printf("Jaune", "Erreur:", "manque de place pour copie la version\n");
			return(-1);
		}
		strcpy(en.lbr, *(argv+2));
		en.vrs = en.lbr;
		en.lbr += strlen(*(argv+2)) + 1;
	}
	
	return(0);
}

// Recuperation de la liste des versions
// Recuperation de la liste des fichiers

int fi_trtprj(void)
{
	CH *vs, *fc;
	LS *lsv, *lsc, *lsh, *lsa;
	DIR *lsd;
	struct dirent *lse;
	struct stat sb;
	FILE *lol, *loa, *lor;
	char *p, *q, *lpbff, lrdss[LNGSTR], lrvrs[LNGVRS];
	char lrsrc[LNGSTR], lrdst[LNGSTR];
	int linv, lind, linf, linc;	// nombre version dossier_cache fichier fichier_cache
	int lisc, lish, lisa;	// nombre source c entete h source asm
	int licv, licr, limv, limr, lilus, i;

	lg_strcpy(lg.fnc, "fi_trtprj");
	
	lsv = ls_cns();	// version
	lsc = ls_cns();	// source c
	lsh = ls_cns();	// entete h
	lsa = ls_cns();	// source asm
	
	linv = lind = linf = linc = 0;
	lisc = lish = lisa = 0;
	limv = limr = -1;

	if (!en.vrs)
	{
		// ------------------------------------- VERSION -----------------------------------
	
		sprintf(lrsrc, "%s/%s", en.gtk, en.prj);
		fv_printf("Cyan", "Dossier source:", "%s\n", lrsrc);	
		chdir(lrsrc);
		
		if ((lsd = opendir(".")) == NULL)
		{
			lg_strcpy(lg.mss, lrsrc);
			lg_strcpy(lg.err, "Erreur");
			lg_ecr();
			return(-1);
		}
		
		while ((lse = readdir(lsd)) != NULL)
		{
			if (strcmp(lse->d_name, ".") == 0)
				continue;
			if (strcmp(lse->d_name, "..") == 0)
				continue;
		
			/*
				DT_BLK      This is a block device.
				DT_CHR      This is a character device.
				DT_DIR      This is a directory.
				DT_FIFO     This is a named pipe (FIFO).
				DT_LNK      This is a symbolic link.
				DT_REG      This is a regular file.
				DT_SOCK     This is a UNIX domain socket.
				DT_UNKNOWN  The file type is unknown.
			*/

			if (lse->d_type == DT_DIR)
			{
				if ((lse->d_name[0] == '.') ||
						(lse->d_name[strlen(lse->d_name)-1] == '~'))
				{
					lind++;
					fv_printf("Cyan", "Dossier cache:", "%s\n", lse->d_name);
				}
				else
				{
					linv++;
					ls_asc(lsv, lse->d_name);
				}
			}
			if ((lse->d_type == DT_REG) || (lse->d_type == DT_LNK))
			{
				if ((lse->d_name[0] == '.') ||
						(lse->d_name[strlen(lse->d_name)-1] == '~'))
				{
					linc++;
					fv_printf("Cyan", "Fichier cache:", "%s\n", lse->d_name);
				}
				else
				{
					linf++;
					if (strlen(lse->d_name) > 2)
					{
						if (strcmp(&lse->d_name[strlen(lse->d_name)-2], ".c") == 0)
						{
							lisc++;
							ls_asc(lsc, lse->d_name);
						}
						if (strcmp(&lse->d_name[strlen(lse->d_name)-2], ".h") == 0)
						{
							lish++;
							ls_asc(lsh, lse->d_name);
						}
					}
					if (strlen(lse->d_name) > 4)
						if (strcmp(&lse->d_name[strlen(lse->d_name)-4], ".asm") == 0)
						{
							lisa++;
							ls_asc(lsa, lse->d_name);
						}
				}
			}
		}
		closedir(lsd);
	}
	else
	{
		linv = 1;
		ls_asc(lsv, en.vrs);
	}
	
	if (linc != 0)
		fv_printf("Cyan", "ATTENTION:", "%d fichier%s cache%s\n", linc, (linc==1)?"":"s", (linc==1)?"":"s");
	if (lind != 0)
		fv_printf("Cyan", "ATTENTION:", "%d version%s cachee%s\n", lind, (lind==1)?"":"s", (lind==1)?"":"s");

	//if (((linf != 0) || (linc != 0)) && ((linv == 0) && (lind == 0)))
	if ((linf != 0) && (linv == 0))
	{
		lg_strcpy(lg.mss, "Traitement source !!!");
		lg_strcpy(lg.err, "fichier");
		lg_ecr();
	}
	else
	{
		if ((linf == 0) && (linv != 0))
		{
			vs = lsv->first;

			while (vs)
			{
				for (i=0; i<strlen(vs->texte1); i++)
					if (strchr(NUM, vs->texte1[i]) == NULL)
						break;
				if (vs->texte1[i] == 0)
				{
					sscanf(vs->texte1, "%d.%d", &licv, &licr);
					if (licv > limv)
					{
						limv = licv;
						limr = licr;
					}
					else
					{
						if (licv == limv)
						{
							if (licr > limr)
							{
								limr = licr;
							}
						}
					}
				}
 				else
				{
					if (strlen(vs->texte1) > (LNGVRS-1))
					{
						fv_printf("Jaune", "Version trouvee:", "nom trop long (>%d)\n", LNGVRS-1);
						return(-1);
					}
					if (strlen(vs->texte1) > (en.tll-(en.lbr-en.mmr)))
					{
						fv_printf("Jaune", "Erreur:", "manque de place pour copie la version\n");
						return(-1);
					}
					strcpy(en.lbr, vs->texte1);
					en.vrs = en.lbr;
					en.lbr += strlen(vs->texte1) + 1;
				}

				vs = vs->next;
			}

			if (limv != -1)
			{
				sprintf(lrvrs, "%d.%d", limv, limr);
				if (strlen(lrvrs) > (LNGVRS-1))
				{
					fv_printf("Jaune", "Version trouvee:", "nom trop long (>%d)\n", LNGVRS-1);
					return(-1);
				}
				if (strlen(lrvrs) > (en.tll-(en.lbr-en.mmr)))
				{
					fv_printf("Jaune", "Erreur:", "manque de place pour copie la version\n");
					return(-1);
				}
				strcpy(en.lbr, lrvrs);
				en.vrs = en.lbr;
				en.lbr += strlen(lrvrs) + 1;
			}
			else
			{
				if (linv != 1)
				{
					fv_printf("Jaune", "ATTENTION:", "manque la version en parametre\nc projet version\n");
					return(-2);
				}
			}
			//lg_strcpy(lg.mss, "Traitement version !!!");
			//lg_strcpy(lg.err, en.vrs);
			//lg_ecr();
	
			// ----------------------------------- SOURCE ---------------------------------

			sprintf(lrsrc, "%s/%s/%s", en.gtk, en.prj, en.vrs);	
			chdir(lrsrc);
		
			if ((lsd = opendir(".")) == NULL)
			{
				lg_strcpy(lg.mss, lrsrc);
				lg_strcpy(lg.err, "Erreur");
				lg_ecr();
				return(-1);
			}
		
			lisc = lish = lisa = 0;
			while ((lse = readdir(lsd)) != NULL)
			{
				if (strcmp(lse->d_name, ".") == 0)
					continue;
				if (strcmp(lse->d_name, "..") == 0)
					continue;
		
				/*
					DT_BLK      This is a block device.
					DT_CHR      This is a character device.
					DT_DIR      This is a directory.
					DT_FIFO     This is a named pipe (FIFO).
					DT_LNK      This is a symbolic link.
					DT_REG      This is a regular file.
					DT_SOCK     This is a UNIX domain socket.
					DT_UNKNOWN  The file type is unknown.
				*/

				if ((lse->d_type == DT_REG) || (lse->d_type == DT_LNK))
				{
					if ((lse->d_name[0] != '.') && (lse->d_name[strlen(lse->d_name)-1] != '~'))
					{
						//printf("%s\n", lse->d_name);
						// ne pas traiter les noms <<* (*copie)*>>
						
						if (strlen(lse->d_name) > 10)
						{
							if ((strstr(lse->d_name, " (")) && (strstr(lse->d_name, "copie).")))
								continue;
						}
						
						linf++;
						if (strlen(lse->d_name) > 2)
						{
							if (strcmp(&lse->d_name[strlen(lse->d_name)-2], ".c") == 0)
							{
								lisc++;
								ls_asc(lsc, lse->d_name);
							}
							if (strcmp(&lse->d_name[strlen(lse->d_name)-2], ".h") == 0)
							{
								lish++;
								ls_asc(lsh, lse->d_name);
							}
						}
						if (strlen(lse->d_name) > 4)
							if (strcmp(&lse->d_name[strlen(lse->d_name)-4], ".asm") == 0)
							{
								lisa++;
								ls_asc(lsa, lse->d_name);
							}
					}
				}
			}
			closedir(lsd);
		}
		else
		{
			lg_strcpy(lg.mss, "Fichier et Dossier !!!");
			lg_strcpy(lg.err, "Fait rien");
			lg_ecr();
		}
	}

	// --------------------------------------- LINK --------------------------------------
			
	sprintf(lrdss, "%s/%s/%s", en.gtk, en.prj, en.vrs);
	fv_link(lrdss, lsc, lsh, lsa);
		
	ls_dst(lsv);
	ls_dst(lsc);
	ls_dst(lsh);
	ls_dst(lsa);
	
	return(0);
}

// Traite les versions d'un projet

int fi_trtvrs(FILE *pow, char *prprj, LS *psvrs)
{
	CH   *vs;
	char *p, *lpbff, lrlgn[LNGSTR], lrvrs[LNGSTR], lrbln[6], lrmdt[26], prj[11], vrs[9], dat[8], lrlng[80];
	int  lilus;
	struct dirent *lse;
	struct stat sb;
	struct tm *dathrs;
	
	strcpy(lrbln, "     ");
	vs = psvrs->first;
	while (vs)
	{
		sprintf(lrlgn, "/usr/local/bin/%s", prprj);
		if (stat(lrlgn, &sb) == 0)	// l'exe existe
		{
			dathrs = localtime(&sb.st_mtime);
			sprintf(lrmdt, "%2d/%02d/%04d %2d:%02d:%02d", dathrs->tm_mday, dathrs->tm_mon, dathrs->tm_year+1900, 
			dathrs->tm_hour, dathrs->tm_min, dathrs->tm_sec);	// date de derniere modif
			if ((p = strchr(lrmdt, '\n')) != NULL)
				*p = 0;
			if ((lpbff = io_bfffch(lrlgn, &lilus)) != NULL)	// lecture de l'exe
			{
				iv_info(lpbff, lilus, prj, vrs, dat);
				io_frebff(lpbff);
			}
		}
		else
		{
			strcpy(lrmdt, "");
			strncpy(prj, prprj, 10);
			prj[10] = 0;
			strncpy(vrs, vs->texte1, 8);
			vrs[8] = 0;
		}
		strcpy(lrvrs, vs->texte1);
		lrvrs[LNGVRS-1] = 0;
		//fi_anllsz(prprj, lrvrs, lrlng);
		fprintf(pow, "%32s%c%s%s%s%c%s%20s  %s\n", 
			prprj, (strcmp(prprj, prj))?'*':' ', &lrbln[strlen(lrvrs)/2], (strlen(lrvrs)%2)?"":" ", 
			lrvrs, (strcmp(vs->texte1, vrs))?'*':' ', &lrbln[strlen(lrvrs)/2], lrmdt, lrlng);
		
		vs = vs->next;

	}
	
	return(0);
}

//
// Creation .mk et .op
//

void fv_mkop(LS *ls, int nmb)
{
	CH *ch;
	FILE *mk, *op;
	int no;
	char *p, prj[64], nmk[128], nop[128], txt[256];

	if (ls->first != NULL)
	{
		ch = ls->first;
		no= 0;
		do
		{
			if (no == 0)
			{
				no = 1;
				strcpy(prj, ch->texte1);
				if ((p = strchr(prj, '/')) != NULL)
					*p = 0;
				sprintf(nmk, "%s/%s.mk", ch->texte1, prj);
				unlink(nmk);
				sprintf(nop, "%s/%s.op", ch->texte1, prj);
				unlink(nop);
				ch = ch->next;
				continue;
			}
			if (ch->texte1[0] == '<')
			{
				//sprintf(txt, "%s.op %s\n", prj, ch->texte1);
				//gtk_text_buffer_set_text(tbf, txt, -1);
				op = fopen(nop, "a");
				fprintf(op, "%s\n", ch->texte1);
				fclose(op);
			}
			else
			{
				if (nmb > 1)
				{
					//sprintf(txt, "%s.mk %s\n", prj, ch->texte1);
					//gtk_text_buffer_set_text(tbf, txt, -1);
					mk = fopen(nmk, "a");
					fprintf(mk, "%s\n", ch->texte1);
					fclose(mk);
				}
			}
			ch = ch->next;
		} while (ch != NULL);
	}
}

void fv_compile(void)
{
	//Wnd *wnd = &WND;
	//GdkRGBA color;
	LXC *lxc;
	LS *ls;
	CH *ch;
	int lus, inc;
	char *v, txt[256], nomsrc[64];
	char **argv = NULL, *vrb = NULL, **s_argv;
	char *bff;
	
	// Lecture du source
	
	if ((bff = io_bfffch(str.src, &lus)) == NULL)
	{
		fv_printf("Jaune", "Erreur", "lecture source\n");
		
		lg_strcpy(lg.mss, "Erreur lecture source");
		lg_strcpy(lg.err, str.src); 
		lg_ecr();
		
		return;
	}
	*(bff+lus) = 0;
	
	// Analyse source
	
	inc = 0;
	ls = ls_cns();
	lxc = lxc_cns(bff);
	while ((lxc_anl(lxc)) > 0)
	{
		if (lxc->ul == LXC_INCLUDE_SYS)
		{
			if (strcmp(lxc->ulx, "<math.h>") == 0)
				inc |= 1;
			if (strcmp(lxc->ulx, "<SDL2/SDL.h>") == 0)
				inc |= 2;
			if (strcmp(lxc->ulx, "<gtk/gtk.h>") == 0)
				inc |= 4;
			if (strcmp(lxc->ulx, "<GL/gl.h>") == 0)
				inc |= 8;
			if (strcmp(lxc->ulx, "<GL/glu.h>") == 0)
				inc |= 0x10;
			if (strcmp(lxc->ulx, "<SDL2/SDL_image.h>") == 0)
				inc |= 0x20;
			if (strcmp(lxc->ulx, "<SDL2/SDL_ttf.h>") == 0)
				inc |= 0x40;
			if (strcmp(lxc->ulx, "<SDL2/SDL_mixer.h>") == 0)
				inc |= 0x80;
			if (strcmp(lxc->ulx, "<aio.h>") == 0)
				inc |= 0x100;
			if (strcmp(lxc->ulx, "<pthread.h>") == 0)
				inc |= 0x200;
			if (strcmp(lxc->ulx, "<mysql/mysql.h>") == 0)
				inc |= 0x400;
		}
		if (lxc->ul == LXC_INCLUDE_FCH)
			ls_asf(ls, lxc->ulx);
	}
	
	if (lxc->ul == LXC_ERREUR)
	{
		fv_printf("Jaune", "Erreur", "analyse source\n");

		lg_strcpy(lg.mss, "Erreur analyse source");
		lg_strcpy(lg.err, str.src); 
		lg_ecr();
	}
	lxc_dst(lxc);
	io_frebff(bff);

	if ((inc & 6) == 0)		// trouve ni SDL ni GTK
	{
		ch = ls->first;		// Analyse tous les includes locaux (#include "...")
		while (ch != NULL)
		{
			bff = io_bfffch(ch->texte1, &lus);
			
			lxc = lxc_cns(bff);
			while ((lxc_anl(lxc)) > 0)
			{
				if (lxc->ul == LXC_INCLUDE_SYS)
				{
					if (strcmp(lxc->ulx, "<math.h>") == 0)
						inc |= 1;
					if (strcmp(lxc->ulx, "<SDL2/SDL.h>") == 0)
						inc |= 2;
					if (strcmp(lxc->ulx, "<gtk/gtk.h>") == 0)
						inc |= 4;
					if (strcmp(lxc->ulx, "<GL/gl.h>") == 0)
						inc |= 8;
					if (strcmp(lxc->ulx, "<GL/glu.h>") == 0)
						inc |= 0x10;
					if (strcmp(lxc->ulx, "<SDL2/SDL_image.h>") == 0)
						inc |= 0x20;
					if (strcmp(lxc->ulx, "<SDL2/SDL_ttf.h>") == 0)
						inc |= 0x40;
					if (strcmp(lxc->ulx, "<SDL2/SDL_mixer.h>") == 0)
						inc |= 0x80;
					if (strcmp(lxc->ulx, "<aio.h>") == 0)
						inc |= 0x100;
					if (strcmp(lxc->ulx, "<pthread.h>") == 0)
						inc |= 0x200;
					if (strcmp(lxc->ulx, "<mysql/mysql.h>") == 0)
						inc |= 0x400;
				}
				if (lxc->ul == LXC_INCLUDE_FCH)
					ls_asf(ls, lxc->ulx);
			}
	
			if (lxc->ul == LXC_ERREUR)
			{
				fv_printf("Jaune", "Erreur", "analyse include\n");

				lg_strcpy(lg.mss, "Erreur analyse include");
				lg_strcpy(lg.err, ch->texte1); 
				lg_ecr();
			}
			lxc_dst(lxc);
			io_frebff(bff);
			
			ch = ch->next;
		}
	}
	ls_dst(ls);

	chdir(str.dir);

	sprintf(str.bin, "%s/%s", en.bin, GCC);

	argv = (char **) malloc(400);
	s_argv = argv;
	vrb = (char *) malloc(2048);
	v = vrb;
	
	// Compilation source
	
	sprintf(str.out, "%s/%so", en.log, nomsrc);
	sprintf(str.err, "%s/%se", en.log, nomsrc);
	
	strcpy(v, GCC);
	*argv++ = v;
	v += strlen(v) + 1;
	
	strcpy(v, "-g");
	*argv++ = v;
	v += strlen(v) + 1;
	
	strcpy(v, "-c");
	*argv++ = v;
	v += strlen(v) + 1;

	strcpy(v, nomsrc);
	*argv++ = v;
	v += strlen(v) + 1;

	if ((inc & 0xC2) != 0)		// SDL
	{
		strcpy(v, "-I/usr/include/SDL2");	// /usr/local/include/SDL
		*argv++ = v;
		v += strlen(v) + 1;
	}
	
/*
ATTENTION different en 32 (i386) et 64 bits  (x86_64) 
jojo@i54670:~$ pkg-config --cflags gtk+-3.0
-pthread -I/usr/include/gtk-3.0 -I/usr/include/atk-1.0 -I/usr/include/at-spi2-atk/2.0 -I/usr/include/pango-1.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/cairo -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/glib-2.0 -I/usr/lib/i386-linux-gnu/glib-2.0/include -I/usr/include/harfbuzz -I/usr/include/freetype2 -I/usr/include/pixman-1 -I/usr/include/libpng12
*/

	if ((inc & 4) == 4)		// GTK
	{
		strcpy(v, "-I/usr/include/gtk-3.0");
		*argv++ = v;
		v += strlen(v) + 1;
		
		strcpy(v, "-I/usr/include/atk-1.0");
		*argv++ = v;
		v += strlen(v) + 1;
		
		strcpy(v, "-I/usr/include/at-spi2-atk/2.0");
		*argv++ = v;
		v += strlen(v) + 1;
		
		strcpy(v, "-I/usr/include/pango-1.0");
		*argv++ = v;
		v += strlen(v) + 1;
		
		strcpy(v, "-I/usr/include/gio-unix-2.0/");
		*argv++ = v;
		v += strlen(v) + 1;
		
		strcpy(v, "-I/usr/include/cairo");
		*argv++ = v;
		v += strlen(v) + 1;
		
		strcpy(v, "-I/usr/include/gdk-pixbuf-2.0");
		*argv++ = v;
		v += strlen(v) + 1;
		
		strcpy(v, "-I/usr/include/glib-2.0");
		*argv++ = v;
		v += strlen(v) + 1;
		
		strcpy(v, "-I/usr/lib/x86_64-linux-gnu/glib-2.0/include");
		*argv++ = v;
		v += strlen(v) + 1;
		
		strcpy(v, "-I/usr/include/harfbuzz");
		*argv++ = v;
		v += strlen(v) + 1;
		
		strcpy(v, "-I/usr/include/freetype2");
		*argv++ = v;
		v += strlen(v) + 1;
		
		strcpy(v, "-I/usr/include/pixman-1");
		*argv++ = v;
		v += strlen(v) + 1;
		
		strcpy(v, "-I/usr/include/libpng12");
		*argv++ = v;
		v += strlen(v) + 1;			
	}

	if ((inc & 0x18) != 0)		// GL
	{
		strcpy(v, "-I/usr/include/GL");
		*argv++ = v;
		v += strlen(v) + 1;
	}

	if ((inc & 0x400) != 0)		// MYSQL
	{
		strcpy(v, "-I/usr/include/mysql");
		*argv++ = v;
		v += strlen(v) + 1;
	}
	
	*argv = NULL;
	
	strcpy(txt, nomsrc);
	argv = s_argv;
	if (fi_lance(str.bin, TRUE, str.out, str.err, argv) == 0)
	{
		strcat(txt, " ok");
		fv_printf("Vert", "txt =", "%s\n", txt);
	}
	else
	{
		strcat(txt, " KO");
		fv_printf("Rouge", "txt =", "%s\n", txt);
	}

	free(argv);
	free(vrb);
}

void fv_link(char *ppdss, LS *lsc, LS *lsh, LS *lsa)
{
	EL *elmsrc;
	LXC *lxc;
	CH *ch;
	int lus, inc, err, lngvrb;
	char *v, txt[LNGSTR], src[LNGLGN], dst[LNGLGN];
	char **argv = NULL, *vrb = NULL, **s_argv;
	char *bff;
	
	lg_strcpy(lg.fnc, "fv_link");

	argv = (char **) malloc(400);
	s_argv = argv;
	vrb = (char *) malloc(2048);
	v = vrb;
	lngvrb = 2048;
	
	sprintf(str.bin, "%s/%s", en.bin, GCC);

	inc = 0;

	// Analyse fichier h (boucle)

	ch = lsh->first;

	while (ch)
	{
		sprintf(txt, "%s/%s", ppdss, ch->texte1);
//printf("h %s\n", txt);
		bff = io_bfffch(txt, &lus);
		*(bff+lus) = 0;
		if ((lxc = lxc_cns(bff)) == NULL)
		{
			fv_printf("Jaune", "Erreur", "lxc_cns()\n");
			ch = ch->next;
			continue;
		}
		while ((lxc_anl(lxc)) > 0)
		{
			if (lxc->ul == LXC_INCLUDE_FCH)
			{
				if (strlen(lxc->ulx) == 9)
				{
					if (strncmp(lxc->ulx, "\"bbl", 4) == 0)
					{
						if (strcmp(&lxc->ulx[6], ".h\"") == 0)
						{
							sprintf(src, "%s/bbl%c%c/0.0/bbl%c%c.h", en.gtk, 
								lxc->ulx[4], lxc->ulx[5], lxc->ulx[4], lxc->ulx[5]);  
							sprintf(dst, "%s/%s/%s/bbl%c%c.h", en.gtk, en.prj, 
								en.vrs, lxc->ulx[4], lxc->ulx[5]);  
							if (access(dst, F_OK) != 0)
								link(src, dst);
							sprintf(src, "%s/bbl%c%c/0.0/bbl%c%c.c", en.gtk, 
								lxc->ulx[4], lxc->ulx[5], lxc->ulx[4], lxc->ulx[5]);  
							sprintf(dst, "%s/%s/%s/bbl%c%c.c", en.gtk, en.prj, 
								en.vrs, lxc->ulx[4], lxc->ulx[5]);  
							if (access(dst, F_OK) != 0)
								link(src, dst);
						}
					}
				}
			}
			if (lxc->ul == LXC_INCLUDE_SYS)
			{
				if (strcmp(lxc->ulx, "<math.h>") == 0)
					inc |= 1;
				if (strcmp(lxc->ulx, "<SDL2/SDL.h>") == 0)
					inc |= 2;
				if (strcmp(lxc->ulx, "<gtk/gtk.h>") == 0)
					inc |= 4;
				if (strcmp(lxc->ulx, "<GL/gl.h>") == 0)
					inc |= 8;
				if (strcmp(lxc->ulx, "<GL/glu.h>") == 0)
					inc |= 0x10;
				if (strcmp(lxc->ulx, "<SDL2/SDL_image.h>") == 0)
					inc |= 0x20;
				if (strcmp(lxc->ulx, "<SDL2/SDL_ttf.h>") == 0)
					inc |= 0x40;
				if (strcmp(lxc->ulx, "<SDL2/SDL_mixer.h>") == 0)
					inc |= 0x80;
				if (strcmp(lxc->ulx, "<aio.h>") == 0)
					inc |= 0x100;
				if (strcmp(lxc->ulx, "<pthread.h>") == 0)
					inc |= 0x200;
				if (strcmp(lxc->ulx, "<mysql/mysql.h>") == 0)
					inc |= 0x400;
			}
		}
		
		if (lxc->ul == LXC_ERREUR)
		{
//printf("Erreur analyse %s\n", ch->texte1);
			lg_strcpy(lg.mss, "Erreur analyse");
			lg_strcpy(lg.err, ch->texte1); 
			lg_ecr();
		}
		io_frebff(bff);
		lxc_dst(lxc);
		ch = ch->next;
	}

	// Analyse fichier c (boucle)

	ch = lsc->first;

	while (ch)
	{
		sprintf(txt, "%s/%s", ppdss, ch->texte1);
//printf("c %s\n", txt);
		bff = io_bfffch(txt, &lus);
		*(bff+lus) = 0;
		lxc = lxc_cns(bff);
		while ((lxc_anl(lxc)) > 0)
		{
			//if (strcmp(ch->texte1, "xsync.c") == 0) printf("%s\n", lxc->ulx);
			if (lxc->ul == LXC_INCLUDE_FCH)
			{
				if (strlen(lxc->ulx) == 9)
				{
					if (strncmp(lxc->ulx, "\"bbl", 4) == 0)
					{
						if (strcmp(&lxc->ulx[6], ".h\"") == 0)
						{
							sprintf(src, "%s/bbl%c%c/0.0/bbl%c%c.h", en.gtk, 
								lxc->ulx[4], lxc->ulx[5], lxc->ulx[4], lxc->ulx[5]);  
							sprintf(dst, "%s/%s/%s/bbl%c%c.h", en.gtk, en.prj, 
								en.vrs, lxc->ulx[4], lxc->ulx[5]);  
							if (access(dst, F_OK) != 0)
								link(src, dst);
							sprintf(src, "%s/bbl%c%c/0.0/bbl%c%c.c", en.gtk, 
								lxc->ulx[4], lxc->ulx[5], lxc->ulx[4], lxc->ulx[5]);  
							sprintf(dst, "%s/%s/%s/bbl%c%c.c", en.gtk, en.prj, 
								en.vrs, lxc->ulx[4], lxc->ulx[5]);  
							if (access(dst, F_OK) != 0)
								link(src, dst);
						}
					}
				}
			}
			if (lxc->ul == LXC_INCLUDE_SYS)
			{
				if (strcmp(lxc->ulx, "<math.h>") == 0)
					inc |= 1;
				if (strcmp(lxc->ulx, "<SDL2/SDL.h>") == 0)
					inc |= 2;
				if (strcmp(lxc->ulx, "<gtk/gtk.h>") == 0)
					inc |= 4;
				if (strcmp(lxc->ulx, "<GL/gl.h>") == 0)
					inc |= 8;
				if (strcmp(lxc->ulx, "<GL/glu.h>") == 0)
					inc |= 0x10;
				if (strcmp(lxc->ulx, "<SDL2/SDL_image.h>") == 0)
					inc |= 0x20;
				if (strcmp(lxc->ulx, "<SDL2/SDL_ttf.h>") == 0)
					inc |= 0x40;
				if (strcmp(lxc->ulx, "<SDL2/SDL_mixer.h>") == 0)
					inc |= 0x80;
				if (strcmp(lxc->ulx, "<aio.h>") == 0)
					inc |= 0x100;
				if (strcmp(lxc->ulx, "<pthread.h>") == 0)
					inc |= 0x200;
				if (strcmp(lxc->ulx, "<mysql/mysql.h>") == 0)
					inc |= 0x400;
			}
		}
		
		if (lxc->ul == LXC_ERREUR)
		{
			lg_strcpy(lg.mss, "Erreur analyse");
			lg_strcpy(lg.err, ch->texte1); 
			lg_ecr();
		}
		io_frebff(bff);
		lxc_dst(lxc);
		ch = ch->next;
	}
	fv_printf("Cyan", en.prj, "%s", en.vrs);
	if (inc & 1)
		fv_printf("Cyan", "", "math");
	if (inc & 0xE2)
		fv_printf("Cyan", "", "SDL");
	if (inc & 4)
		fv_printf("Cyan", "", "GTK");
	if (inc & 0x18)
		fv_printf("Cyan", "", "GL");
	if (inc & 0x100)
		fv_printf("Cyan", "", "AIO");
	if (inc & 0x200)
		fv_printf("Cyan", "", "THREAD");
	if (inc & 0x400)
		fv_printf("Cyan", "", "MYSQL");
	printf("\n");

	// Compilation (Boucle fichier c)
	
	err = 0;
	ch = lsc->first;
	while (ch)
	{
		v = vrb;
		
		sprintf(str.out, "%s/%so", en.log, ch->texte1);
		sprintf(str.err, "%s/%se", en.log, ch->texte1);
		
		strcpy(v, GCC);
		*argv++ = v;
		v += strlen(v) + 1;
		if ((v-vrb) >= lngvrb)
		{
			lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
			sprintf(lg.err, "%ld", v-vrb);
			lg_ecr();
			break;
		}
		
		strcpy(v, "-g3");
		*argv++ = v;
		v += strlen(v) + 1;
		if ((v-vrb) >= lngvrb)
		{
			lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
			sprintf(lg.err, "%ld", v-vrb);
			lg_ecr();
			break;
		}
		
		strcpy(v, "-c");
		*argv++ = v;
		v += strlen(v) + 1;
		if ((v-vrb) >= lngvrb)
		{
			lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
			sprintf(lg.err, "%ld", v-vrb);
			lg_ecr();
			break;
		}

		strcpy(v, ch->texte1);
		*argv++ = v;
		v += strlen(v) + 1;
		if ((v-vrb) >= lngvrb)
		{
			lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
			sprintf(lg.err, "%ld", v-vrb);
			lg_ecr();
			break;
		}

		if ((inc & 0xC2) != 0)		// SDL
		{
			strcpy(v, "-I/usr/include/SDL2");
			*argv++ = v;
			v += strlen(v) + 1;
			if ((v-vrb) >= lngvrb)
			{
				lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
				sprintf(lg.err, "%ld", v-vrb);
				lg_ecr();
				break;
			}
		}
		
/*
jojo@i54670:~$ pkg-config --cflags gtk+-3.0
-pthread -I/usr/include/gtk-3.0 -I/usr/include/atk-1.0 -I/usr/include/at-spi2-atk/2.0 -I/usr/include/pango-1.0 -I/usr/include/gio-unix-2.0/ -I/usr/include/cairo -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/glib-2.0 -I/usr/lib/i386-linux-gnu/glib-2.0/include -I/usr/include/harfbuzz -I/usr/include/freetype2 -I/usr/include/pixman-1 -I/usr/include/libpng12
*/
		
		//	strcpy(v, "`pkg-config --cflags --libs gtk+-3.0`");
		if ((inc & 4) == 4)		// GTK
		{
			strcpy(v, "-I/usr/include/gtk-3.0");
			*argv++ = v;
			v += strlen(v) + 1;
			if ((v-vrb) >= lngvrb)
			{
				lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
				sprintf(lg.err, "%ld", v-vrb);
				lg_ecr();
				break;
			}
			
			strcpy(v, "-I/usr/include/atk-1.0");
			*argv++ = v;
			v += strlen(v) + 1;
			if ((v-vrb) >= lngvrb)
			{
				lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
				sprintf(lg.err, "%ld", v-vrb);
				lg_ecr();
				break;
			}
			
			strcpy(v, "-I/usr/include/at-spi2-atk/2.0");
			*argv++ = v;
			v += strlen(v) + 1;
			if ((v-vrb) >= lngvrb)
			{
				lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
				sprintf(lg.err, "%ld", v-vrb);
				lg_ecr();
				break;
			}
			
			strcpy(v, "-I/usr/include/pango-1.0");
			*argv++ = v;
			v += strlen(v) + 1;
			if ((v-vrb) >= lngvrb)
			{
				lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
				sprintf(lg.err, "%ld", v-vrb);
				lg_ecr();
				break;
			}
			
			strcpy(v, "-I/usr/include/gio-unix-2.0/");
			*argv++ = v;
			v += strlen(v) + 1;
			if ((v-vrb) >= lngvrb)
			{
				lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
				sprintf(lg.err, "%ld", v-vrb);
				lg_ecr();
				break;
			}
			
			strcpy(v, "-I/usr/include/cairo");
			*argv++ = v;
			v += strlen(v) + 1;
			if ((v-vrb) >= lngvrb)
			{
				lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
				sprintf(lg.err, "%ld", v-vrb);
				lg_ecr();
				break;
			}
			
			strcpy(v, "-I/usr/include/gdk-pixbuf-2.0");
			*argv++ = v;
			v += strlen(v) + 1;
			if ((v-vrb) >= lngvrb)
			{
				lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
				sprintf(lg.err, "%ld", v-vrb);
				lg_ecr();
				break;
			}
			
			strcpy(v, "-I/usr/include/glib-2.0");
			*argv++ = v;
			v += strlen(v) + 1;
			if ((v-vrb) >= lngvrb)
			{
				lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
				sprintf(lg.err, "%ld", v-vrb);
				lg_ecr();
				break;
			}
			strcpy(v, "-I/usr/lib/x86_64-linux-gnu/glib-2.0/include");
			*argv++ = v;
			v += strlen(v) + 1;
			if ((v-vrb) >= lngvrb)
			{
				lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
				sprintf(lg.err, "%ld", v-vrb);
				lg_ecr();
				break;
			}
			
			strcpy(v, "-I/usr/include/harfbuzz");
			*argv++ = v;
			v += strlen(v) + 1;
			if ((v-vrb) >= lngvrb)
			{
				lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
				sprintf(lg.err, "%ld", v-vrb);
				lg_ecr();
				break;
			}
			
			strcpy(v, "-I/usr/include/freetype2");
			*argv++ = v;
			v += strlen(v) + 1;
			if ((v-vrb) >= lngvrb)
			{
				lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
				sprintf(lg.err, "%ld", v-vrb);
				lg_ecr();
				break;
			}
			
			strcpy(v, "-I/usr/include/pixman-1");
			*argv++ = v;
			v += strlen(v) + 1;
			if ((v-vrb) >= lngvrb)
			{
				lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
				sprintf(lg.err, "%ld", v-vrb);
				lg_ecr();
				break;
			}
			
			strcpy(v, "-I/usr/include/libpng12");
			*argv++ = v;
			v += strlen(v) + 1;			
			if ((v-vrb) >= lngvrb)
			{
				lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
				sprintf(lg.err, "%ld", v-vrb);
				lg_ecr();
				break;
			}
		}

		if ((inc & 0x18) != 0)		// GL
		{
			strcpy(v, "-I/usr/include/GL");
			*argv++ = v;
			v += strlen(v) + 1;
			if ((v-vrb) >= lngvrb)
			{
				lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
				sprintf(lg.err, "%ld", v-vrb);
				lg_ecr();
				break;
			}
		}

		if ((inc & 0x400) != 0)		// MYSQL
		{
			strcpy(v, "-I/usr/include/mysql");
			*argv++ = v;
			v += strlen(v) + 1;
			if ((v-vrb) >= lngvrb)
			{
				lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
				sprintf(lg.err, "%ld", v-vrb);
				lg_ecr();
				break;
			}
		}
		
		*argv = NULL;
		
		strcpy(txt, ch->texte1);
		argv = s_argv;
		if (fi_lance(str.bin, TRUE, str.out, str.err, argv) == 0)
		{
			strcat(txt, " ok");
			fv_printf("Vert", "Compile", "%s\n", txt);
		}
		else
		{
			err = 1;
			strcat(txt, " KO");
			fv_printf("Rouge", "Compile", "%s\n", txt);
		}
			
		ch = ch->next;
	}
	
	// Link (Boucle fichier .o)
	
	if (err == 1)
	{
		strcpy(txt, en.prj);
		strcat(txt, " KO");
		fv_printf("Rouge", "link", "%s\n", txt);

		free(argv);
		free(vrb);
		
		return;
	}
	
	argv = s_argv;
	v = vrb;

	sprintf(str.out, "%s/%s.lo", en.log, en.prj);
	sprintf(str.err, "%s/%s.le", en.log, en.prj);
	
	strcpy(v, GCC);
	*argv++ = v;
	v += strlen(v) + 1;
	if ((v-vrb) >= lngvrb)
	{
		lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
		sprintf(lg.err, "%ld", v-vrb);
		lg_ecr();
	}
	
	strcpy(v, "-o");
	*argv++ = v;
	v += strlen(v) + 1;
	if ((v-vrb) >= lngvrb)
	{
		lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
		sprintf(lg.err, "%ld", v-vrb);
		lg_ecr();
	}

	sprintf(v, "%s/%s", en.app, en.prj);
	*argv++ = v;
	v += strlen(v) + 1;
	if ((v-vrb) >= lngvrb)
	{
		lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
		sprintf(lg.err, "%ld", v-vrb);
		lg_ecr();
	}

	ch = lsc->first;
	while (ch != NULL)
	{
		strcpy(v, ch->texte1);
		v[strlen(v)-1] = 'o';
		*argv++ = v;
		v += strlen(v) + 1;
		if ((v-vrb) >= lngvrb)
		{
			lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
			sprintf(lg.err, "%ld", v-vrb);
			lg_ecr();
			break;
		}
			
		ch = ch->next;
	}

	if ((inc & 1) == 1)		// math
	{
		strcpy(v, "-lm");
		*argv++ = v;
		v += strlen(v) + 1;
		if ((v-vrb) >= lngvrb)
		{
			lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
			sprintf(lg.err, "%ld", v-vrb);
			lg_ecr();
		}
	}

	if ((inc & 2) == 2)		// SDL
	{
		strcpy(v, "-lSDL2");
		*argv++ = v;
		v += strlen(v) + 1;
		if ((v-vrb) >= lngvrb)
		{
			lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
			sprintf(lg.err, "%ld", v-vrb);
			lg_ecr();
		}
	}
	if ((inc & 32) == 32)		// SDL
	{
		strcpy(v, "-lSDL2_image");
		*argv++ = v;
		v += strlen(v) + 1;
		if ((v-vrb) >= lngvrb)
		{
			lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
			sprintf(lg.err, "%ld", v-vrb);
			lg_ecr();
		}
	}
	if ((inc & 64) == 64)		// SDL
	{
		strcpy(v, "-lSDL2_ttf");
		*argv++ = v;
		v += strlen(v) + 1;
		if ((v-vrb) >= lngvrb)
		{
			lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
			sprintf(lg.err, "%ld", v-vrb);
			lg_ecr();
		}
	}
	if ((inc & 128) == 128)		// SDL
	{
		strcpy(v, "-lSDL2_mixer");
		*argv++ = v;
		v += strlen(v) + 1;
		if ((v-vrb) >= lngvrb)
		{
			lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
			sprintf(lg.err, "%ld", v-vrb);
			lg_ecr();
		}
	}
	
	if ((inc & 4) == 4)		// GTK
	{
		strcpy(v, "-lgtk-3");
		*argv++ = v;
		v += strlen(v) + 1;
		if ((v-vrb) >= lngvrb)
		{
			lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
			sprintf(lg.err, "%ld", v-vrb);
			lg_ecr();
		}
		
		strcpy(v, "-lgdk-3");
		*argv++ = v;
		v += strlen(v) + 1;
		if ((v-vrb) >= lngvrb)
		{
			lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
			sprintf(lg.err, "%ld", v-vrb);
			lg_ecr();
		}
		
		strcpy(v, "-latk-1.0");
		*argv++ = v;
		v += strlen(v) + 1;
		if ((v-vrb) >= lngvrb)
		{
			lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
			sprintf(lg.err, "%ld", v-vrb);
			lg_ecr();
		}
		
		strcpy(v, "-lgio-2.0");
		*argv++ = v;
		v += strlen(v) + 1;
		if ((v-vrb) >= lngvrb)
		{
			lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
			sprintf(lg.err, "%ld", v-vrb);
			lg_ecr();
		}
		
		strcpy(v, "-lpangocairo-1.0");
		*argv++ = v;
		v += strlen(v) + 1;
		if ((v-vrb) >= lngvrb)
		{
			lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
			sprintf(lg.err, "%ld", v-vrb);
			lg_ecr();
		}
		
		strcpy(v, "-lgdk_pixbuf-2.0");
		*argv++ = v;
		v += strlen(v) + 1;
		if ((v-vrb) >= lngvrb)
		{
			lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
			sprintf(lg.err, "%ld", v-vrb);
			lg_ecr();
		}
		
		strcpy(v, "-lcairo-gobject");
		*argv++ = v;
		v += strlen(v) + 1;
		if ((v-vrb) >= lngvrb)
		{
			lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
			sprintf(lg.err, "%ld", v-vrb);
			lg_ecr();
		}
		
		strcpy(v, "-lpango-1.0");
		*argv++ = v;
		v += strlen(v) + 1;
		if ((v-vrb) >= lngvrb)
		{
			lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
			sprintf(lg.err, "%ld", v-vrb);
			lg_ecr();
		}
		
		strcpy(v, "-lcairo");
		*argv++ = v;
		v += strlen(v) + 1;
		if ((v-vrb) >= lngvrb)
		{
			lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
			sprintf(lg.err, "%ld", v-vrb);
			lg_ecr();
		}
		
		strcpy(v, "-lgobject-2.0");
		*argv++ = v;
		v += strlen(v) + 1;
		if ((v-vrb) >= lngvrb)
		{
			lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
			sprintf(lg.err, "%ld", v-vrb);
			lg_ecr();
		}
		
		strcpy(v, "-lglib-2.0");
		*argv++ = v;
		v += strlen(v) + 1;
		if ((v-vrb) >= lngvrb)
		{
			lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
			sprintf(lg.err, "%ld", v-vrb);
			lg_ecr();
		}
	}

	if ((inc & 8) == 8)		// GL
	{
		strcpy(v, "-lGL");
		*argv++ = v;
		v += strlen(v) + 1;
		if ((v-vrb) >= lngvrb)
		{
			lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
			sprintf(lg.err, "%ld", v-vrb);
			lg_ecr();
		}
	}
	if ((inc & 16) == 16)		// GLU
	{
		strcpy(v, "-lGLU");
		*argv++ = v;
		v += strlen(v) + 1;
		if ((v-vrb) >= lngvrb)
		{
			lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
			sprintf(lg.err, "%ld", v-vrb);
			lg_ecr();
		}
	}
	if ((inc & 0x100) == 0x100)		// AIO
	{
		strcpy(v, "-lrt");
		*argv++ = v;
		v += strlen(v) + 1;
		if ((v-vrb) >= lngvrb)
		{
			lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
			sprintf(lg.err, "%ld", v-vrb);
			lg_ecr();
		}
	}
	if ((inc & 0x200) == 0x200)		// THREAD
	{
		strcpy(v, "-pthread");
		*argv++ = v;
		v += strlen(v) + 1;
		if ((v-vrb) >= lngvrb)
		{
			lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
			sprintf(lg.err, "%ld", v-vrb);
			lg_ecr();
		}
	}
	if ((inc & 0x400) == 0x400)		// MYSQL
	{
		strcpy(v, "-lmysqlclient");
		*argv++ = v;
		v += strlen(v) + 1;
		if ((v-vrb) >= lngvrb)
		{
			lg_strcpy(lg.mss, "Debordement <<vrb>> !!!");
			sprintf(lg.err, "%ld", v-vrb);
			lg_ecr();
		}
	}
	
	*argv = NULL;
	
	strcpy(txt, en.prj);
	argv = s_argv;
	if (fi_lance(str.bin, TRUE, str.out, str.err, argv) == 0)
	{
		strcat(txt, " ok");
		fv_printf("Vert", "link", "%s\n", txt);
	}
	else
	{
		strcat(txt, " KO");
		fv_printf("Rouge", "link", "%s\n", txt);
	}

	free(argv);
	free(vrb);
}

//
// Lecture et affectation des variables d'environement dans la struct en
//

int en_get(int pi_argc, char **pp_argv, char **pp_envv)
{
	int i;
	
	memset(&en, 0, sizeof(en));
	
	en.tll = 1024;
	if (!(en.mmr = malloc(en.tll)))
	{
		fv_printf("Jaune", "Erreur", "MALLOC %s\n", strerror(errno));
		return(-1);
	}
	en.lbr = en.mmr;	

	if (pi_argc > 1)
		if (strcmp(*(pp_argv+1), "-auto") == 0)
			en.oto = 1;
	for (i=0; *(pp_envv+i); i++)
	{
		if (strncmp(*(pp_envv+i), "NIVTRC=", 7) == 0)
			en.ntr = atoi((*(pp_envv+i))+7);
		if (strncmp(*(pp_envv+i), "HOME=", 5) == 0)
			en.hom = (*(pp_envv+i))+5;
		if (strncmp(*(pp_envv+i), "USER=", 5) == 0)
		{
			en.usr = (*(pp_envv+i))+5;
			if (strcmp(en.usr, "jojo") != 0)
			{
				fv_printf("Cyan", "ATTENTION:", "login # jojo !!!\n");
			}
		}
		if (strncmp(*(pp_envv+i), "DSSCNF=", 7) == 0)
			en.cnf = (*(pp_envv+i))+7;
		if (strncmp(*(pp_envv+i), "DSSICN=", 7) == 0)
			en.icn = (*(pp_envv+i))+7;
		if (strncmp(*(pp_envv+i), "DSSFCH=", 7) == 0)
			en.fch = (*(pp_envv+i))+7;
		if (strncmp(*(pp_envv+i), "DSSLOG=", 7) == 0)
			en.log = (*(pp_envv+i))+7;
		if (strncmp(*(pp_envv+i), "UBNGTK=", 7) == 0)
			en.gtk = (*(pp_envv+i))+7;
		if (strncmp(*(pp_envv+i), "UBNSDL=", 7) == 0)
			en.sdl = (*(pp_envv+i))+7;
		if (strncmp(*(pp_envv+i), "WNDCPP=", 7) == 0)
			en.wnd = (*(pp_envv+i))+7;
		if (strncmp(*(pp_envv+i), "AVRC=", 5) == 0)
			en.avrc = (*(pp_envv+i))+5;
		if (strncmp(*(pp_envv+i), "AVRASM=", 7) == 0)
			en.avrasm = (*(pp_envv+i))+7;
		if (strncmp(*(pp_envv+i), "AVRHEX=", 7) == 0)
			en.avrhex = (*(pp_envv+i))+7;
		if (strncmp(*(pp_envv+i), "AVRINC=", 7) == 0)
			en.avrinc = (*(pp_envv+i))+7;
		if (strncmp(*(pp_envv+i), "ARMC=", 5) == 0)
			en.armc = (*(pp_envv+i))+5;
		if (strncmp(*(pp_envv+i), "ARMASM=", 7) == 0)
			en.armasm = (*(pp_envv+i))+7;
		if (strncmp(*(pp_envv+i), "ARMHEX=", 7) == 0)
			en.armhex = (*(pp_envv+i))+7;
		if (strncmp(*(pp_envv+i), "DSSWWW=", 7) == 0)
			en.www = (*(pp_envv+i))+7;
		if (strncmp(*(pp_envv+i), "EXEBIN=", 7) == 0)
			en.bin = (*(pp_envv+i))+7;
		if (strncmp(*(pp_envv+i), "EXEAPP=", 7) == 0)
			en.app = (*(pp_envv+i))+7;
	}
	
	return(0);
}

//
// Creation d'une liste
//

LS *ls_cns(void)
{
	LS *ls;
	
	ls = malloc(sizeof(*ls));
	ls->first = NULL;
	ls->current = NULL;
	ls->last = NULL;
	
	return(ls);
}

//
// Ajoute un texte dans la liste (sans double, tri croissant)
//
// pour un texte simple ls_add(texte)
// pour un texte et une caractere ls_add("%s %c", texte, caractere)
// si c'est un nombre ls_add("%d", nombre)
// idem avec caractere ls_add("%d %c", nombre, caractere)
//

void ls_asc(LS *liste, char *texte, ...)
{
	CH *nv, *prc, *crt;
	va_list ap;
	char *chn;
	int  i, nmb;
	char car;
	
   	nv = malloc(sizeof(*nv));
	nv->texte1 = NULL;
	nv->texte2 = NULL;
	nv->texte3 = NULL;
	nv->nombre = -1;
	nv->caractere = ' ';

	if (strchr(texte, '%') == NULL)
	{
		nv->texte1 = malloc(strlen(texte)+1);
		strcpy(nv->texte1, texte);
	}
	else
	{
		va_start(ap, texte);
		i = 0;
		while (*texte)
		{
			if (*texte != '%')
			{
				texte++;
				continue;
			}
			texte++;
			switch (*texte)
			{
				case 's':              /* string */
					if (i == 0)
					{
						chn = va_arg(ap, char *);
						nv->texte1 = malloc(strlen(chn)+1);
						strcpy(nv->texte1, chn);
					}
					if (i == 1)
					{
						chn = va_arg(ap, char *);
						nv->texte2 = malloc(strlen(chn)+1);
						strcpy(nv->texte2, chn);
					}
					if (i == 2)
					{
						chn = va_arg(ap, char *);
						nv->texte3 = malloc(strlen(chn)+1);
						strcpy(nv->texte3, chn);
					}
					i++;
					break;
				case 'd':              /* int */
					nmb = va_arg(ap, int);
					nv->nombre = nmb;
					break;
				case 'c':              /* char */
					/* need a cast here since va_arg only takes fully promoted types */
					car = (char) va_arg(ap, int);
					nv->caractere = car;
					break;
			}
			texte++;
		}
		va_end(ap);
	}
	
	if (liste->last == NULL)	// creation premier
	{
		nv->prior = NULL;
		nv->next = NULL;
		liste->first = nv;
		liste->current = nv;
		liste->last = nv;
	}
	else					// ajout en fin de liste
	{
		//liste->last->next = nv;
		//nv->prior = liste->last;
		//nv->next = NULL;
		//liste->current = nv;
		//liste->last = nv;

		prc = crt = liste->first;		// Insertion triee
		while (crt != NULL)
		{
			if (strcmp(crt->texte1, nv->texte1) > 0)
			{
				//printf("%s > %s\n", crt->texte1, nv->texte1);
				break;
			}
			//printf("%s < %s\n", crt->texte1, nv->texte1);
		
			prc = crt;
			crt = crt->next;
		}
		if (crt == NULL)
		{
			//printf("dernier %s\n", nv->texte1);
			prc->next = nv;
			nv->prior = prc;
			nv->next = NULL;
			liste->last = nv;
			liste->current = nv;
		}
		else
		{
			if (crt == prc)
			{
				//printf("nouveau premier %s\n", nv->texte1);
				liste->first = nv;
				crt->prior = nv;
				nv->next = crt;
				nv->prior = NULL;
			}
			else
			{
				//printf("trie %s\n", nv->texte1);
				prc->next = nv;
				crt->prior = nv;
				nv->prior = prc;
				nv->next = crt;
			}
		}
	}
}

//
// Supprime un texte de la liste a la position p
//

void ls_spp(LS *liste, int position)
{
	CH *crn;
	int numero;
	
	for (numero = 0, crn = liste->first; crn != NULL; crn = crn->next, numero++)
	{
		if (position == numero)
		{
			if (numero == 0)	// efface le premier
			{
				if (crn->next == NULL)	// premier et unique
				{
					if (crn->texte1)
						free(crn->texte1);
					if (crn->texte2)
						free(crn->texte2);
					if (crn->texte3)
						free(crn->texte3);
					free(crn);
					liste->first = NULL;
					liste->current = NULL;
					liste->last = NULL;
				}
				else			// le suivant devient premier et courant ?
				{
					liste->first = crn->next;
					if (liste->current == crn)
						liste->current = crn->next;
					crn->next->prior = NULL;
					if (crn->texte1)
						free(crn->texte1);
					if (crn->texte2)
						free(crn->texte2);
					if (crn->texte3)
						free(crn->texte3);
					free(crn);
				}
			}
			else
			{
				if (crn->next == NULL)	// dernier
				{
					if (liste->current == crn)
						liste->current = crn->prior;
					liste->last = crn->prior;
					crn->prior->next = NULL;
					if (crn->texte1)
						free(crn->texte1);
					if (crn->texte2)
						free(crn->texte2);
					if (crn->texte3)
						free(crn->texte3);
					free(crn);
				}
				else			// au milieu
				{
					if (liste->current == crn)
						liste->current = crn->prior;
					crn->prior->next = crn->next;
					crn->next->prior = crn->prior;
					if (crn->texte1)
						free(crn->texte1);
					if (crn->texte2)
						free(crn->texte2);
					if (crn->texte3)
						free(crn->texte3);
					free(crn);
				}
			}
			break;
		}
	}
}

//
// Vide toute la liste
//

void ls_vid(LS *liste)
{
	while (liste->first != NULL)
		ls_spp(liste, 0);
}

//
// Positionnement sur le nieme texte de la liste
//

void ls_nth(LS *liste, int position)
{
	CH *crn;
	int numero;
	
	for (numero = 0, crn = liste->first; crn != NULL; crn = crn->next, numero++)
	{
		if (position == numero)
		{
			liste->current = crn;
			break;
		}
	}
}

//
// Recherche un texte dans la liste
//

int ls_txt1(LS *liste, char *texte)
{
	CH *crn;
	int numero;
	
	for (numero = 0, crn = liste->first; crn != NULL; crn = crn->next, numero++)
	{
		if (strcmp(crn->texte1, texte) == 0)
		{
			liste->current = crn;
			break;
		}
	}
	return((crn==NULL)?-1:numero);
}
int ls_txt2(LS *liste, char *texte)
{
	CH *crn;
	int numero;
	
	for (numero = 0, crn = liste->first; crn != NULL; crn = crn->next, numero++)
	{
		if (strcmp(crn->texte2, texte) == 0)
		{
			liste->current = crn;
			break;
		}
	}
	return((crn==NULL)?-1:numero);
}
int ls_txt3(LS *liste, char *texte)
{
	CH *crn;
	int numero;
	
	for (numero = 0, crn = liste->first; crn != NULL; crn = crn->next, numero++)
	{
		if (strcmp(crn->texte3, texte) == 0)
		{
			liste->current = crn;
			break;
		}
	}
	return((crn==NULL)?-1:numero);
}

//
// Recherche un caractere dans la liste (marque)
//

int ls_mrq(LS *liste, char caractere)
{
	CH *crn;
	int numero;
	
	for (numero = 0, crn = liste->first; crn != NULL; crn = crn->next, numero++)
	{
		if (crn->caractere == caractere)
		{
			liste->current = crn;
			break;
		}
	}
	return((crn==NULL)?-1:numero);
}

//
// Marque un texte dans la liste
//

int ls_mtx(LS *liste, char *texte, char caractere)
{
	CH *crn;
	int numero;
	
	for (numero = 0, crn = liste->first; crn != NULL; crn = crn->next, numero++)
	{
		if (strcmp(crn->texte1, texte) == 0)
		{
			crn->caractere = caractere;
			liste->current = crn;
			break;
		}
	}
	return((crn==NULL)?-1:numero);
}

//
// Marque une position dans la liste
//

int ls_mps(LS *liste, int position, char caractere)
{
	CH *crn;
	int numero;
	
	for (numero = 0, crn = liste->first; crn != NULL; crn = crn->next, numero++)
	{
		if (numero == position)
		{
			crn->caractere = caractere;
			liste->current = crn;
			break;
		}
	}
	return((crn==NULL)?-1:numero);
}

//
// Vide le contenu de la liste
//

void ls_prn(LS *liste)
{
	CH *chn;
	int li_no=0;

	if (liste->first != NULL)
	{
		chn = liste->first;
		do
		{
			printf("LS: %d '%c' %d \"%s\" \"%s\" \"%s\"\n", li_no, chn->caractere, chn->nombre, chn->texte1, 
				(chn->texte2==NULL)?"NULL":chn->texte2, (chn->texte3==NULL)?"NULL":chn->texte3);
			li_no++;
			chn = chn->next;
		} while (chn != NULL);
	}
	else
		printf("Liste VIDE !!!\n");
}

//
// Detruit la liste
//

void ls_dst(LS *liste)
{
	ls_vid(liste);
	free(liste);
}

//
// Creation d'une dr (liste dir)
//

DR *dr_cns(void)
{
	DR *dr;
	
	dr = malloc(sizeof(*dr));
	dr->first = NULL;
	dr->current = NULL;
	dr->last = NULL;
	
	return(dr);
}

//
// Ajoute un fichier avec taille et date de derniere modif dans la liste
//

void dr_add(DR *dr, char *fichier, off_t taille, time_t modif)
{
	EL *prc, *crt, *nouveau;
	
   	nouveau = malloc(sizeof(*nouveau));
	nouveau->fichier = malloc(strlen(fichier)+1);
	strcpy(nouveau->fichier, fichier);
	nouveau->taille = taille;
	nouveau->modif = modif;

	//printf("*** nouveau %s\n", nouveau->fichier);
	if (dr->last == NULL)	// creation premier
	{
		//printf("premier %s\n", nouveau->fichier);
		nouveau->prior = NULL;
		nouveau->next = NULL;
		dr->first = nouveau;
		dr->current = nouveau;
		dr->last = nouveau;
		return;
	}
	
	prc = crt = dr->first;		// Insertion triee
	while (crt != NULL)
	{
		if (strcmp(crt->fichier, nouveau->fichier) > 0)
		{
			//printf("%s > %s\n", crt->fichier, nouveau->fichier);
			break;
		}
		//printf("%s < %s\n", crt->fichier, nouveau->fichier);
		
		prc = crt;
		crt = crt->next;
	}
	if (crt == NULL)
	{
		//printf("dernier %s\n", nouveau->fichier);
		prc->next = nouveau;
		nouveau->prior = prc;
		nouveau->next = NULL;
		dr->last = nouveau;
		dr->current = nouveau;
	}
	else
	{
		if (crt == prc)
		{
			//printf("nouveau premier %s\n", nouveau->fichier);
			dr->first = nouveau;
			crt->prior = nouveau;
			nouveau->next = crt;
			nouveau->prior = NULL;
		}
		else
		{
			//printf("trie %s\n", nouveau->fichier);
			prc->next = nouveau;
			crt->prior = nouveau;
			nouveau->prior = prc;
			nouveau->next = crt;
		}
	}
}

//
// Supprime un texte de la liste
//

void dr_spp(DR *dr, int position)
{
	EL *crn;
	int numero;
	
	for (numero = 0, crn = dr->first; crn != NULL; crn = crn->next, numero++)
	{
		if (position == numero)
		{
			if (numero == 0)	// efface le premier
			{
				if (crn->next == NULL)	// premier et unique
				{
					free(crn->fichier);
					free(crn);
					dr->first = NULL;
					dr->current = NULL;
					dr->last = NULL;
				}
				else			// le suivant devient premier et courant ?
				{
					dr->first = crn->next;
					if (dr->current == crn)
						dr->current = crn->next;
					crn->next->prior = NULL;
					free(crn->fichier);
					free(crn);
				}
			}
			else
			{
				if (crn->next == NULL)	// dernier
				{
					if (dr->current == crn)
						dr->current = crn->prior;
					dr->last = crn->prior;
					crn->prior->next = NULL;
					free(crn->fichier);
					free(crn);
				}
				else			// au milieu
				{
					if (dr->current == crn)
						dr->current = crn->prior;
					crn->prior->next = crn->next;
					crn->next->prior = crn->prior;
					free(crn->fichier);
					free(crn);
				}
			}
			break;
		}
	}
}

//
// Vide toute la liste
//

void dr_vid(DR *dr)
{
	while (dr->first != NULL)
		dr_spp(dr, 0);
}
/*
//
// Positionnement sur le nieme texte de la liste
//

void fv_list_nth(Liste *liste, int position)
{
	Chaine *crn;
	int numero;
	
	for (numero = 0, crn = liste->first; crn != NULL; crn = crn->next, numero++)
	{
		if (position == numero)
		{
			liste->current = crn;
			break;
		}
	}
}

//
// Recherche un texte dans la liste
//

int fi_list_txt(Liste *liste, char *texte)
{
	Chaine *crn;
	int numero;
	
	for (numero = 0, crn = liste->first; crn != NULL; crn = crn->next, numero++)
	{
		if (strcmp(crn->texte, texte) == 0)
		{
			liste->current = crn;
			break;
		}
	}
	return((crn==NULL)?-1:numero);
}

//
// Recherche une marque dans la liste
//

int fi_list_mrq(Liste *liste, char marque)
{
	Chaine *crn;
	int numero;
	
	for (numero = 0, crn = liste->first; crn != NULL; crn = crn->next, numero++)
	{
		if (crn->marque == marque)
		{
			liste->current = crn;
			break;
		}
	}
	return((crn==NULL)?-1:numero);
}

//
// Marque un texte dans la liste
//

int fi_list_mtx(Liste *liste, char *texte, char marque)
{
	Chaine *crn;
	int numero;
	
	for (numero = 0, crn = liste->first; crn != NULL; crn = crn->next, numero++)
	{
		if (strcmp(crn->texte, texte) == 0)
		{
			crn->marque = marque;
			liste->current = crn;
			break;
		}
	}
	return((crn==NULL)?-1:numero);
}

//
// Marque une position dans la liste
//

int fi_list_mps(Liste *liste, int position, char marque)
{
	Chaine *crn;
	int numero;
	
	for (numero = 0, crn = liste->first; crn != NULL; crn = crn->next, numero++)
	{
		if (numero == position)
		{
			crn->marque = marque;
			liste->current = crn;
			break;
		}
	}
	return((crn==NULL)?-1:numero);
}
*/
//
// Vide le contenu de la liste
//

void dr_prn(DR *dr)
{
	EL *elm;
	char texte[64];
	int li_no=0;

	if (dr->first != NULL)
	{
		elm = dr->first;
		do
		{
			printf("Liste: %d %s %lld %lld\n", li_no, elm->fichier, (long long) elm->taille, (long long) elm->modif);
			li_no++;
			elm = elm->next;
		} while (elm != NULL);
	}
}

//
// Detruit la dr (liste dir)
//

void dr_dst(DR *dr)
{
	dr_vid(dr);
	free(dr);
}

int lg_cns()
{
	struct stat st;
	int i;
	
	if (lg.prj[0] == 0)
	{
		strcpy(lg.err, "lg.prj n'a pas ete initialise");
		return(-1);
	}
	if ((lg.nmb != 0) && (lg.tll == 0))
	{
		strcpy(lg.err, "lg.tll n'a pas ete initialise");
		return(-1);
	}
		
	lg_strcpy(lg.nom, "/var/local/log/");
	lg_strcat(lg.nom, lg.prj);
	if (lg.nmb == 0)
	{
		lg_strcat(lg.nom, ".0");
		if ((lg.log = fopen(lg.nom, "w")) != NULL)
			fclose(lg.log);
	}
	else
	{
		lg_strcat(lg.nom, ".0");
		for (i=1; i<=lg.nmb; i++)
		{
			lg.nom[strlen(lg.nom)-1] = '0' + i;
			if (stat(lg.nom, &st) != 0)
				break;
			if (st.st_size < lg.tll)
				break;
		}
		if (st.st_size >= lg.tll)
		{
			lg.nom[strlen(lg.nom)-1] = '1';
			if ((lg.log = fopen(lg.nom, "w")) != NULL)
				fclose(lg.log);
		}
	}
		
	return(0);
}

void lg_ecr()
{
	time_t tt;
	struct tm *tm;
	struct stat st;
	int i;
	char sdt[20], etl[]="***\0+++\0---\0...";
		
	if (lg.grv > lg.ntr)
		return;
	
	// ouverture fichier log
	
	if ((lg.log = fopen(lg.nom, "a")) == NULL)
		return;
		
	tt = time(NULL);
	tm = localtime(&tt);

	strftime(sdt, sizeof(sdt), "%d/%m/20%y %H:%M:%S", tm);
	fprintf(lg.log, "%s %3s - %s - %s - %s - %s %s\n", sdt, &etl[lg.grv*4], 
							lg.prj, lg.unt, lg.fnc, lg.mss, lg.err);
	
	// fermeture fichier log
	
	if (lg.log != NULL)
		fclose(lg.log);
		
	if (lg.nmb != 0)
	{
		if (stat(lg.nom, &st) == 0)
		{
			if (st.st_size >= lg.tll)
			{
				i = lg.nom[strlen(lg.nom)-1] - '0';
				i++;
				if (i > lg.nmb)
					i = 1;
				lg.nom[strlen(lg.nom)-1] = '0' + i;
				if ((lg.log = fopen(lg.nom, "w")) != NULL)
					fclose(lg.log);
			}
		}
	}
}

void lg_dst()
{
}

void lg_strcpy(char *dst, char *src)
{
	int l = 31;

	if (src == NULL)
	{
		dst[0] = 0;
		return;
	}

	if ((lg.mss == dst) || (lg.err == dst))
		l = 127;
	strncpy(dst, src, l);
	dst[l] = 0;
}

void lg_strcat(char *dst, char *src)
{
	int t, l = 31;
	if ((lg.mss == dst) ||
		(lg.err == dst))
		l = 127;
	t = strlen(dst);
	strncpy(dst+t, src, l-t);
	dst[t+strlen(src)] = 0;
}

void lg_strncpy(char *dst, char *src, int lng)
{
	int l = 31;
	if ((lg.mss == dst) ||
		(lg.err == dst))
		l = 127;
	if (lng < l)
		l = lng;
	strncpy(dst, src, l);
	dst[l] = 0;
}

//
// Constructeur c ========================= c & h ==========================
//

LXC *lxc_cns(char *pp_bff)
{
	LXC *lxc;
	int nmblus;
	
	if ((lxc = malloc(sizeof(*lxc))) == NULL)
		return(NULL);
		
	lxc->ul = LXC_FIN;
	if ((lxc->ulx = malloc(LXC_TLL)) == NULL)
	{
		free(lxc);
		lxc = NULL;
		return(NULL);
	}
	
	lxc->motclf = io_bfffch("/var/local/cnf/motclf.lxc", &nmblus);
	lxc->typc   = io_bfffch("/var/local/cnf/typc.lxc",   &nmblus);
	lxc->typlbc = io_bfffch("/var/local/cnf/typlbc.lxc", &nmblus);
	lxc->typgtk = io_bfffch("/var/local/cnf/typgtk.lxc", &nmblus);
	lxc->typsdl = io_bfffch("/var/local/cnf/typsdl.lxc", &nmblus);
	lxc->cnsc   = io_bfffch("/var/local/cnf/cnsc.lxc",   &nmblus);
	lxc->cnslbc = io_bfffch("/var/local/cnf/cnslbc.lxc", &nmblus);
	lxc->cnsgtk = io_bfffch("/var/local/cnf/cnsgtk.lxc", &nmblus);
	lxc->cnssdl = io_bfffch("/var/local/cnf/cnssdl.lxc", &nmblus);
	lxc->fncc   = io_bfffch("/var/local/cnf/fncc.lxc",   &nmblus);
	lxc->fnclbc = io_bfffch("/var/local/cnf/fnclbc.lxc", &nmblus);
	lxc->fncgtk = io_bfffch("/var/local/cnf/fncgtk.lxc", &nmblus);
	lxc->fncsdl = io_bfffch("/var/local/cnf/fncsdl.lxc", &nmblus);
	
	lxc->bff = pp_bff;
	
	return(lxc);
}

//
// Analyse lexicale pour decouper le c en unite lexicale
//
// retour: ul pour la coloration
//

int lxc_anl(LXC *ps_lxc)
{
	char lr_nm1[] = "0123456789";
	char lr_hex[] = "0123456789abcdefABCDEF";
	char lr_an1[] = "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char lr_an2[] = "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	char lr_spr[] = "()[]{}.,;:?";
	char lr_opr[] = "*/+-&|~^%!=<>";
	char *lp_ulx, *lp_d, *lp_f;
	char *p;
	int  n;
	
	*ps_lxc->ulx = 0;
	lp_d = ps_lxc->bff;
	lp_f = lp_d;
	
	while ((*lp_f==' ') || (*lp_f=='\t') || (*lp_f=='\r') || (*lp_f=='\n')) // supprime les blancs
		lp_f++;
		
	if ((lp_f-lp_d) > 0)		// blanc ...
	{
		if ((lp_f-lp_d) > LXC_TLL)
		{
			*ps_lxc->ulx = 0;
			ps_lxc->bff = lp_f;
			ps_lxc->ul = LXC_ERREUR;
			return(LXC_ERREUR);
		}
		strncpy(ps_lxc->ulx, lp_d, lp_f-lp_d);
		*(ps_lxc->ulx+(lp_f-lp_d)) = 0;
		ps_lxc->bff = lp_f;
		if (ps_lxc->ul != LXC_PREPROCESSEUR)
			ps_lxc->ul = LXC_BLANC;
		return(LXC_BLANC);
	}

	if (*lp_f == 0)			// fin de fichier
	{
		ps_lxc->ul = LXC_FIN;
		return(LXC_FIN);
	}

	if (ps_lxc->ul == LXC_PREPROCESSEUR)
	{
		if (*lp_f == '<')
		{
			while ((*lp_f != '>') && (*lp_f != 0))
				lp_f++;
			if (*lp_f == 0)
			{
				ps_lxc->bff = lp_f;
				ps_lxc->ul = LXC_ERREUR;
				return(LXC_ERREUR);
			}
			lp_f++;
			if ((lp_f-lp_d) > LXC_TLL)
			{
				*ps_lxc->ulx = 0;
				ps_lxc->bff = lp_f;
				ps_lxc->ul = LXC_ERREUR;
				return(LXC_ERREUR);
			}
			strncpy(ps_lxc->ulx, lp_d, lp_f-lp_d);
			ps_lxc->ulx[lp_f-lp_d] = 0;
			ps_lxc->bff = lp_f;
			ps_lxc->ul = LXC_INCLUDE_SYS;
			return(LXC_INCLUDE_SYS);
		}
		if (*lp_f == '"')
		{
			lp_f++;
			while ((*lp_f != '"') && (*lp_f != 0))
				lp_f++;
			if (*lp_f == 0)
			{
				ps_lxc->bff = lp_f;
				ps_lxc->ul = LXC_ERREUR;
				return(LXC_ERREUR);
			}
			lp_f++;
			if ((lp_f-lp_d) > LXC_TLL)
			{
				if ((lp_ulx = realloc(ps_lxc->ulx, lp_f-lp_d+1)) != NULL)
				{
					ps_lxc->ul = LXC_ERREUR;
					return(LXC_ERREUR);
				}
				ps_lxc->ulx = lp_ulx;
			}
			strncpy(ps_lxc->ulx, lp_d, lp_f-lp_d);
			ps_lxc->ulx[lp_f-lp_d] = 0;
			ps_lxc->bff = lp_f;
			ps_lxc->ul = LXC_INCLUDE_FCH;
			return(LXC_INCLUDE_FCH);
		}
	}
		
	if (*lp_f == '/')
	{
		if (*(lp_f+1)=='/')	// commentaire // ... \n
		{
			while ((*lp_f!='\n') && (*lp_f!=0))
				lp_f++;
			if (*lp_f == 0)
			{
				ps_lxc->bff = lp_f;
				ps_lxc->ul = LXC_ERREUR;
				return(LXC_ERREUR);
			}
			if ((lp_f-lp_d) > LXC_TLL)
			{
				if ((lp_ulx = realloc(ps_lxc->ulx, lp_f-lp_d+1)) == NULL)
				{
					ps_lxc->ul = LXC_ERREUR;
					return(LXC_ERREUR);
				}
				ps_lxc->ulx = lp_ulx;
			}
			strncpy(ps_lxc->ulx, lp_d, lp_f-lp_d);
			*(ps_lxc->ulx+(lp_f-lp_d)) = 0;
			ps_lxc->bff = lp_f;
			ps_lxc->ul = LXC_COMMENTAIRE_CPP;
			return(LXC_COMMENTAIRE_CPP);
		}
		if (*(lp_f+1)=='*')	// commentaire /* ... */
		{
			lp_f += 3;
			while ((*lp_f!=0) && ((*(lp_f-1)!='*') || (*lp_f!='/')))
				lp_f++;
			if (*lp_f == 0)
			{
				ps_lxc->bff = lp_f;
				ps_lxc->ul = LXC_ERREUR;
				return(LXC_ERREUR);
			}
			lp_f++;
			if ((lp_f-lp_d) > LXC_TLL)
			{
				if ((lp_ulx = realloc(ps_lxc->ulx, lp_f-lp_d+1)) == NULL)
				{
					ps_lxc->ul = LXC_ERREUR;
					return(LXC_ERREUR);
				}
				ps_lxc->ulx = lp_ulx;
			}
			strncpy(ps_lxc->ulx, lp_d, lp_f-lp_d);
			*(ps_lxc->ulx+(lp_f-lp_d)) = 0;
			ps_lxc->bff = lp_f;
			ps_lxc->ul = LXC_COMMENTAIRE_C;
			return(LXC_COMMENTAIRE_C);
		}
	}
		
	if (*lp_f == '\'')		// constante caractere
	{
		lp_f++;
		while ((*lp_f!=0) && ((*(lp_f-2)!='\\') || (*(lp_f-1)!='\\') || (*lp_f!='\'')) && ((*(lp_f-1)=='\\') || (*lp_f!='\'')))
			lp_f++;
		if (*lp_f == 0)
		{
			ps_lxc->bff = lp_f;
			ps_lxc->ul = LXC_ERREUR;
			return(LXC_ERREUR);
		}
		lp_f++;
		if ((lp_f-lp_d) > LXC_TLL)
		{
			*ps_lxc->ulx = 0;
			ps_lxc->bff = lp_f;
			ps_lxc->ul = LXC_ERREUR;
			return(LXC_ERREUR);
		}
		strncpy(ps_lxc->ulx, lp_d, lp_f-lp_d);
		*(ps_lxc->ulx+(lp_f-lp_d)) = 0;
		ps_lxc->bff = lp_f;
		ps_lxc->ul = LXC_CONST_CAR;
		return(LXC_CONST_CAR);
	}
		
	if (*lp_f == '"')		// constante texte
	{
		lp_f++;
		/*
		exemple
		"abc"
		"\"abc\""
		"abc\\"
		"abc\"\\\""
		"abc\\\\"
		quitte la boucle si
		.1.
		0 <==> fin de fichier 
		|| (OU)
		.2. 
		le nombre d'\ devant le " est paire 
		|| (OU)
		.3.
		le nombre d'\ devant le " est impaire && (ET) derriere le " il ya un "
		*/
		while (1)
		{
			while ((*lp_f != 0) && (*lp_f != '"'))
				lp_f++;
			
			if (*lp_f == 0)
			{
				ps_lxc->bff = lp_f;
				ps_lxc->ul = LXC_ERREUR;
				return(LXC_ERREUR);
			}
			
			n = 0;
			p = lp_f - 1;
			while (*p == '\\')
			{
				n++;
				p--;
				if (p == lp_d)
					break;
			}
			n %= 2;
			
			if (!n)
				break;
				
			lp_f++;
			if (*(lp_f) == '"')
				break;
		}
		
		lp_f++;
		if ((lp_f-lp_d) > LXC_TLL)
		{
			if ((lp_ulx = realloc(ps_lxc->ulx, lp_f-lp_d+1)) == NULL)
			{
				ps_lxc->ul = LXC_ERREUR;
				return(LXC_ERREUR);
			}
			ps_lxc->ulx = lp_ulx;
		}
		strncpy(ps_lxc->ulx, lp_d, lp_f-lp_d);
		*(ps_lxc->ulx+(lp_f-lp_d)) = 0;
		ps_lxc->bff = lp_f;
		ps_lxc->ul = LXC_CONST_TEXTE;
		return(LXC_CONST_TEXTE);
	}
		
	if (*lp_f == '#')		// commande preprocesseur
	{
		if (strncmp(lp_d, "#include", 8) == 0)
		{
			strcpy(ps_lxc->ulx, "#include");
			lp_f = lp_d + 8;
			ps_lxc->bff = lp_f;
			ps_lxc->ul = LXC_PREPROCESSEUR;
			return(LXC_PREPROCESSEUR);
		}
		if (strncmp(lp_d, "#define", 7) == 0)
		{
			strcpy(ps_lxc->ulx, "#define");
			lp_f = lp_d + 7;
			ps_lxc->bff = lp_f;
			ps_lxc->ul = LXC_PREPROCESSEUR;
			return(LXC_PREPROCESSEUR);
		}
		if (strncmp(lp_d, "#ifdef", 6) == 0)
		{
			strcpy(ps_lxc->ulx, "#ifdef");
			lp_f = lp_d + 6;
			ps_lxc->bff = lp_f;
			ps_lxc->ul = LXC_PREPROCESSEUR;
			return(LXC_PREPROCESSEUR);
		}
		if (strncmp(lp_d, "#ifndef", 7) == 0)
		{
			strcpy(ps_lxc->ulx, "#ifndef");
			lp_f = lp_d + 7;
			ps_lxc->bff = lp_f;
			ps_lxc->ul = LXC_PREPROCESSEUR;
			return(LXC_PREPROCESSEUR);
		}
		if (strncmp(lp_d, "#else", 5) == 0)
		{
			strcpy(ps_lxc->ulx, "#else");
			lp_f = lp_d + 5;
			ps_lxc->bff = lp_f;
			ps_lxc->ul = LXC_PREPROCESSEUR;
			return(LXC_PREPROCESSEUR);
		}
		if (strncmp(lp_d, "#endif", 6) == 0)
		{
			strcpy(ps_lxc->ulx, "#endif");
			lp_f = lp_d + 6;
			ps_lxc->bff = lp_f;
			ps_lxc->ul = LXC_PREPROCESSEUR;
			return(LXC_PREPROCESSEUR);
		}
		while ((*lp_f!='\n') && (*lp_f!=0))
			lp_f++;
		if (*lp_f == 0)
		{
			ps_lxc->bff = lp_f;
			ps_lxc->ul = LXC_ERREUR;
			return(LXC_ERREUR);
		}
		if ((lp_f-lp_d) > LXC_TLL)
		{
			if ((lp_ulx = realloc(ps_lxc->ulx, lp_f-lp_d+1)) == NULL)
			{
				ps_lxc->ul = LXC_ERREUR;
				return(LXC_ERREUR);
			}
			ps_lxc->ulx = lp_ulx;
		}
		strncpy(ps_lxc->ulx, lp_d, lp_f-lp_d);
		*(ps_lxc->ulx+(lp_f-lp_d)) = 0;
		ps_lxc->bff = lp_f;
		ps_lxc->ul = LXC_ERREUR;
		return(LXC_ERREUR);
	}
	
	if (strchr(lr_nm1, *lp_f) != NULL)		// nombre (entier hexa reel)
	{
		if ((*lp_f == '0') && ((*(lp_f+1) == 'x') || (*(lp_f+1) == 'X')))
		{
			lp_f += 2;
			while (strchr(lr_hex, *lp_f) != NULL)
			{
				lp_f++;
				if (*lp_f == 0)
					break;
			}
			if ((lp_f-lp_d) > LXC_TLL)
			{
				*ps_lxc->ulx = 0;
				ps_lxc->bff = lp_f;
				ps_lxc->ul = LXC_ERREUR;
				return(LXC_ERREUR);
			}
			strncpy(ps_lxc->ulx, lp_d, lp_f-lp_d);
			ps_lxc->ulx[lp_f-lp_d] = 0;
			ps_lxc->bff = lp_f;
			ps_lxc->ul = LXC_ENTIER_HEXA;
			return(LXC_ENTIER_HEXA);
		}
		if (*(lp_f+1) == '.')
		{
			lp_f += 2;
			while (strchr(lr_nm1, *lp_f) != NULL)
			{
				lp_f++;
				if (*lp_f == 0)
					break;
			}
			if ((lp_f-lp_d) > LXC_TLL)
			{
				*ps_lxc->ulx = 0;
				ps_lxc->bff = lp_f;
				ps_lxc->ul = LXC_ERREUR;
				return(LXC_ERREUR);
			}
			strncpy(ps_lxc->ulx, lp_d, lp_f-lp_d);
			ps_lxc->ulx[lp_f-lp_d] = 0;
			ps_lxc->bff = lp_f;
			ps_lxc->ul = LXC_REEL;
			return(LXC_REEL);
		}
		lp_f++;
		while (strchr(lr_nm1, *lp_f) != NULL)
		{
			lp_f++;
			if (*lp_f == 0)
				break;
		}
		if ((lp_f-lp_d) > LXC_TLL)
		{
			*ps_lxc->ulx = 0;
			ps_lxc->bff = lp_f;
			ps_lxc->ul = LXC_ERREUR;
			return(LXC_ERREUR);
		}
		strncpy(ps_lxc->ulx, lp_d, lp_f-lp_d);
		ps_lxc->ulx[lp_f-lp_d] = 0;
		ps_lxc->bff = lp_f;
		ps_lxc->ul = LXC_ENTIER;
		return(LXC_ENTIER);
	}
	
	if (strchr(lr_an1, *lp_f) != NULL)	// texte
	{
		lp_f++;
		while (strchr(lr_an2, *lp_f) != NULL)
		{
			lp_f++;
			if (*lp_f == 0)
				break;
		}
		if ((lp_f-lp_d) > LXC_TLL)
		{
			if ((lp_ulx = realloc(ps_lxc->ulx, lp_f-lp_d+1)) == NULL)
			{
				ps_lxc->ul = LXC_ERREUR;
				return(LXC_ERREUR);
			}
			ps_lxc->ulx = lp_ulx;
		}
		strncpy(ps_lxc->ulx, lp_d, lp_f-lp_d);
		ps_lxc->ulx[lp_f-lp_d] = 0;
		ps_lxc->bff = lp_f;
		
		if ((lp_ulx = malloc(strlen(ps_lxc->ulx)+3)) == NULL)
		{
			ps_lxc->ul = LXC_ERREUR;
			return(LXC_ERREUR);
		}
		sprintf(lp_ulx, "\n%s\n", ps_lxc->ulx);
		if (ps_lxc->motclf != NULL)
			if (strstr(ps_lxc->motclf, lp_ulx) != NULL)
			{
				free(lp_ulx);
				ps_lxc->ul = LXC_MOT_CLEF;
				return(LXC_MOT_CLEF);
			}
		if (ps_lxc->typc != NULL)
			if (strstr(ps_lxc->typc, lp_ulx) != NULL)
			{
				free(lp_ulx);
				ps_lxc->ul = LXC_TYPE_C;
				return(LXC_TYPE_C);
			}
		if (ps_lxc->typlbc != NULL)
			if (strstr(ps_lxc->typlbc, lp_ulx) != NULL)
			{
				free(lp_ulx);
				ps_lxc->ul = LXC_TYPE_LIBC;
				return(LXC_TYPE_LIBC);
			}
		if (ps_lxc->typgtk != NULL)
			if (strstr(ps_lxc->typgtk, lp_ulx) != NULL)
			{
				free(lp_ulx);
				ps_lxc->ul = LXC_TYPE_GTK;
				return(LXC_TYPE_GTK);
			}
		if (ps_lxc->cnsc != NULL)
			if (strstr(ps_lxc->cnsc, lp_ulx) != NULL)
			{
				free(lp_ulx);
				ps_lxc->ul = LXC_CONST_C;
				return(LXC_CONST_C);
			}
		if (ps_lxc->cnslbc != NULL)
			if (strstr(ps_lxc->cnslbc, lp_ulx) != NULL)
			{
				free(lp_ulx);
				ps_lxc->ul = LXC_CONST_LIBC;
				return(LXC_CONST_LIBC);
			}
		if (ps_lxc->cnsgtk != NULL)
			if (strstr(ps_lxc->cnsgtk, lp_ulx) != NULL)
			{
				free(lp_ulx);
				ps_lxc->ul = LXC_CONST_GTK;
				return(LXC_CONST_GTK);
			}
		if (ps_lxc->fncc != NULL)
			if (strstr(ps_lxc->fncc, lp_ulx) != NULL)
			{
				free(lp_ulx);
				ps_lxc->ul = LXC_FONCTION_C;
				return(LXC_FONCTION_C);
			}
		if (ps_lxc->fnclbc != NULL)
			if (strstr(ps_lxc->fnclbc, lp_ulx) != NULL)
			{
				free(lp_ulx);
				ps_lxc->ul = LXC_FONCTION_LIBC;
				return(LXC_FONCTION_LIBC);
			}
		if (ps_lxc->fncgtk != NULL)
			if (strstr(ps_lxc->fncgtk, lp_ulx) != NULL)
			{
				free(lp_ulx);
				ps_lxc->ul = LXC_FONCTION_GTK;
				return(LXC_FONCTION_GTK);
			}
		free(lp_ulx);

		while ((*lp_f==' ') || (*lp_f=='\t') || (*lp_f=='\r') || (*lp_f=='\n'))
			lp_f++;
		if (*lp_f == '(')
		{
			ps_lxc->ul = LXC_FONCTION;
			return(LXC_FONCTION);
		}
		else
		{
			ps_lxc->ul = LXC_IDENTIFIANT;
			return(LXC_IDENTIFIANT);
		}
	}
	
	while (strchr(lr_spr, *lp_f) != NULL)
	{
		lp_f++;
		if (*lp_f == 0)
			break;
	}
	if ((lp_f-lp_d) > 0)
	{
		if ((lp_f-lp_d) > LXC_TLL)
		{
			*ps_lxc->ulx = 0;
			ps_lxc->bff = lp_f;
			ps_lxc->ul = LXC_ERREUR;
			return(LXC_ERREUR);
		}
		strncpy(ps_lxc->ulx, lp_d, lp_f-lp_d);
		ps_lxc->ulx[lp_f-lp_d] = 0;
		ps_lxc->bff = lp_f;
		ps_lxc->ul = LXC_SEPARATEUR;
		return(LXC_SEPARATEUR);
	}
	
	while (strchr(lr_opr, *lp_f) != NULL)
	{
		lp_f++;
		if (*lp_f == 0)
			break;
	}
	if ((lp_f-lp_d) > 0)
	{
		if ((lp_f-lp_d) > LXC_TLL)
		{
			*ps_lxc->ulx = 0;
			ps_lxc->bff = lp_f;
			ps_lxc->ul = LXC_ERREUR;
			return(LXC_ERREUR);
		}
		strncpy(ps_lxc->ulx, lp_d, lp_f-lp_d);
		ps_lxc->ulx[lp_f-lp_d] = 0;
		ps_lxc->bff = lp_f;
		ps_lxc->ul = LXC_OPERATEUR;
		return(LXC_OPERATEUR);
	}
		
	sprintf(ps_lxc->ulx, "Caractere '%c' (0x%x) invalide", *lp_f, *lp_f);
	ps_lxc->bff = lp_f+1;
	ps_lxc->ul = LXC_ERREUR;
	return(LXC_ERREUR);
}

// Destructeur c

void lxc_dst(LXC *ps_lxc)
{
	if (ps_lxc->ulx)
		free(ps_lxc->ulx);
	
	io_frebff(ps_lxc->motclf);
	io_frebff(ps_lxc->typc);
	io_frebff(ps_lxc->typlbc);
	io_frebff(ps_lxc->typgtk);
	io_frebff(ps_lxc->typsdl);
	io_frebff(ps_lxc->cnsc);
	io_frebff(ps_lxc->cnslbc);
	io_frebff(ps_lxc->cnsgtk);
	io_frebff(ps_lxc->cnssdl);
	io_frebff(ps_lxc->fncc);
	io_frebff(ps_lxc->fnclbc);
	io_frebff(ps_lxc->fncgtk);
	io_frebff(ps_lxc->fncsdl);

	free(ps_lxc);
	ps_lxc = NULL;
}

//
// Constructeur v ========================= avr ======================
//

LXV *lxv_cns(void)
{
	LXV *lxv;
	int err, nmblus;
	
	if ((lxv = malloc(sizeof(*lxv))) == NULL)
		return(NULL);
	memset(lxv, 0, sizeof(*lxv));
	err = false;

	if ((lxv->equ = malloc(sizeof(*lxv->equ))) == NULL)
		err = true;
	else
	{	
		memset(lxv->equ, 0, sizeof(*lxv->equ));
		lxv->ul = LXV_FIN;
		if ((lxv->ulx = malloc(LXV_TLLULX)) == NULL)
			err = true;
	}

	if ((lxv->fch = malloc(sizeof(*lxv->fch))) == NULL)
		err = true;
	else
	{	
		memset(lxv->fch, 0, sizeof(*lxv->fch));
		if ((lxv->fch->nins = malloc(LXV_TLLNOM)) == NULL)
			err = true;
	}
	
	lxv->avrins = io_bfffch("/var/local/cnf/avrins.lxv", &nmblus);
	lxv->avrmcr = io_bfffch("/var/local/cnf/avrmcr.lxv", &nmblus);
	lxv->avrppr = io_bfffch("/var/local/cnf/avrppr.lxv", &nmblus);
	lxv->avrrgs = io_bfffch("/var/local/cnf/avrrgs.lxv", &nmblus);
	lxv->avradr = io_bfffch("/var/local/cnf/avradr.lxv", &nmblus);
	
	if (err == true)
	{
		if (lxv->ulx)
			free(lxv->ulx);
		if (lxv->equ)
			free(lxv->equ);
		if (lxv->def)
			free(lxv->def);
		if (lxv->lbl)
			free(lxv->lbl);
		if (lxv->lnk)
			free(lxv->lnk);
		if (lxv->prm)
			free(lxv->prm);
		if (lxv->ins)
			free(lxv->ins);
		if (lxv->fch)
		{
			if (lxv->fch->nins)
				free(lxv->fch->nins);
			free(lxv->fch);
		}
		if (lxv->err)
			free(lxv->err);
		if (lxv->bff)
			free(lxv->bff);
		if (lxv->avrins)
			free(lxv->avrins);
		if (lxv->avrmcr)
			free(lxv->avrmcr);
		if (lxv->avrppr)
			free(lxv->avrppr);
		if (lxv->avrrgs)
			free(lxv->avrrgs);
		if (lxv->avradr)
			free(lxv->avradr);
		free(lxv);
		
		lxv = NULL;
	}
	
	return(lxv);
}

//
// memorise les labels
//
// retour: ul pour la coloration
//

int lxv_lbl(LXV *ps_lxv, LS *ps_ls)
{
	char lr_nm1[] = "$0123456789";
	char lr_bin[] = "01";
	char lr_hex[] = "0123456789abcdefABCDEF";
	char lr_an1[] = "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char lr_an2[] = "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	char lr_spr[] = "()[]{}.,;?";	// supprime le :
	char lr_opr[] = "*/+-&|~^%!=<>";
	char *lp_ulx, *lp_d, *lp_f;
	char *p;
	int  n;
	
	while (1)
	{
		*ps_lxv->ulx = 0;
		lp_d = ps_lxv->bff;
		lp_f = lp_d;
	
		while ((*lp_f==' ') || (*lp_f=='\t') || (*lp_f=='\r') || (*lp_f=='\n')) // supprime les blancs
			lp_f++;
		
		if ((lp_f-lp_d) > 0)		// blanc ...
		{
			if ((lp_f-lp_d) > LXV_TLLULX)
			{
				*ps_lxv->ulx = 0;
				ps_lxv->bff = lp_f;
				ps_lxv->ul = LXV_ERREUR;
				continue;;
			}
			strncpy(ps_lxv->ulx, lp_d, lp_f-lp_d);
			*(ps_lxv->ulx+(lp_f-lp_d)) = 0;
			ps_lxv->bff = lp_f;
			if (ps_lxv->ul != LXV_PREPROCESSEUR)
				ps_lxv->ul = LXV_BLANC;
			continue;
		}

		if (*lp_f == 0)			// fin de fichier
		{
			ps_lxv->ul = LXV_FIN;
			break;
		}

		if (ps_lxv->ul == LXV_PREPROCESSEUR)	// lecture de la fin de la ligne proprocesseur
		{
			if (*lp_f == '<')
			{
				while ((*lp_f != '>') && (*lp_f != 0))
					lp_f++;
				if (*lp_f == 0)
				{
					ps_lxv->bff = lp_f;
					ps_lxv->ul = LXV_ERREUR;
					continue;
				}
				lp_f++;
				if ((lp_f-lp_d) > LXV_TLLULX)
				{
					*ps_lxv->ulx = 0;
					ps_lxv->bff = lp_f;
					ps_lxv->ul = LXV_ERREUR;
					continue;
				}
				strncpy(ps_lxv->ulx, lp_d, lp_f-lp_d);
				ps_lxv->ulx[lp_f-lp_d] = 0;
				ps_lxv->bff = lp_f;
				ps_lxv->ul = LXV_INCLUDE_SYS;
				continue;
			}
			if (*lp_f == '"')
			{
				lp_f++;
				while ((*lp_f != '"') && (*lp_f != 0))
					lp_f++;
				if (*lp_f == 0)
				{
					ps_lxv->bff = lp_f;
					ps_lxv->ul = LXV_ERREUR;
					continue;
				}
				lp_f++;
				if ((lp_f-lp_d) > LXV_TLLULX)
				{
					if ((lp_ulx = realloc(ps_lxv->ulx, lp_f-lp_d+1)) != NULL)
					{
						ps_lxv->ul = LXV_ERREUR;
						continue;
					}
					ps_lxv->ulx = lp_ulx;
				}
				strncpy(ps_lxv->ulx, lp_d, lp_f-lp_d);
				ps_lxv->ulx[lp_f-lp_d] = 0;
				ps_lxv->bff = lp_f;
				ps_lxv->ul = LXV_INCLUDE_FCH;
				continue;
			}
		}
		
		if (*lp_f == ';')	// commentaire ... \n
		{
			while ((*lp_f!='\n') && (*lp_f!=0))
				lp_f++;
			if (*lp_f == 0)
			{
				ps_lxv->bff = lp_f;
				ps_lxv->ul = LXV_ERREUR;
				continue;
			}
			if ((lp_f-lp_d) > LXV_TLLULX)
			{
				if ((lp_ulx = realloc(ps_lxv->ulx, lp_f-lp_d+1)) == NULL)
				{
					ps_lxv->ul = LXV_ERREUR;
					continue;
				}
				ps_lxv->ulx = lp_ulx;
			}
			strncpy(ps_lxv->ulx, lp_d, lp_f-lp_d);
			*(ps_lxv->ulx+(lp_f-lp_d)) = 0;
			ps_lxv->bff = lp_f;
			ps_lxv->ul = LXV_COMMENTAIRE;
			continue;
		}
		
		if (*lp_f == '\'')		// constante caractere
		{
			lp_f++;
			while ((*lp_f!=0) && ((*(lp_f-2)!='\\') || (*(lp_f-1)!='\\') || (*lp_f!='\'')) && ((*(lp_f-1)=='\\') || (*lp_f!='\'')))
				lp_f++;
			if (*lp_f == 0)
			{
				ps_lxv->bff = lp_f;
				ps_lxv->ul = LXV_ERREUR;
				continue;
			}
			lp_f++;
			if ((lp_f-lp_d) > LXV_TLLULX)
			{
				*ps_lxv->ulx = 0;
				ps_lxv->bff = lp_f;
				ps_lxv->ul = LXV_ERREUR;
				continue;
			}
			strncpy(ps_lxv->ulx, lp_d, lp_f-lp_d);
			*(ps_lxv->ulx+(lp_f-lp_d)) = 0;
			ps_lxv->bff = lp_f;
			ps_lxv->ul = LXV_CONST_CAR;
			continue;
		}
		
		if (*lp_f == '"')		// constante texte
		{
			lp_f++;
			/*
			exemple
			"abc"
			"\"abc\""
			"abc\\"
			"abc\"\\\""
			"abc\\\\"
			quitte la boucle si
			.1.
			0 <==> fin de fichier 
			|| (OU)
			.2. 
			le nombre d'\ devant le " est paire 
			|| (OU)
			.3.
			le nombre d'\ devant le " est impaire && (ET) derriere le " il ya un "
			*/
			while (1)
			{
				while ((*lp_f != 0) && (*lp_f != '"'))
					lp_f++;
			
				if (*lp_f == 0)
				{
					ps_lxv->bff = lp_f;
					ps_lxv->ul = LXV_ERREUR;
					continue;
				}
			
				n = 0;
				p = lp_f - 1;
				while (*p == '\\')
				{
					n++;
					p--;
					if (p == lp_d)
						break;
				}
				n %= 2;
			
				if (!n)
					break;
				
				lp_f++;
				if (*(lp_f) == '"')
					break;
			}
		
			lp_f++;
			if ((lp_f-lp_d) > LXV_TLLULX)
			{
				if ((lp_ulx = realloc(ps_lxv->ulx, lp_f-lp_d+1)) == NULL)
				{
					ps_lxv->ul = LXV_ERREUR;
					continue;
				}
				ps_lxv->ulx = lp_ulx;
			}
			strncpy(ps_lxv->ulx, lp_d, lp_f-lp_d);
			*(ps_lxv->ulx+(lp_f-lp_d)) = 0;
			ps_lxv->bff = lp_f;
			ps_lxv->ul = LXV_CONST_TEXTE;
			continue;
		}
		
		if (*lp_f == '.')		// commande preprocesseur
		{
			while ((*lp_f!=' ') && (*lp_f!='\t') && (*lp_f!='\r') && (*lp_f!='\n') && (*lp_f!=0))
				lp_f++;
			strncpy(ps_lxv->ulx, lp_d, lp_f-lp_d);
			*(ps_lxv->ulx+(lp_f-lp_d)) = 0;
			
			if ((lp_ulx = malloc(strlen(ps_lxv->ulx)+3)) == NULL)
			{
				ps_lxv->ul = LXV_ERREUR;
				continue;
			}
			sprintf(lp_ulx, "\n%s\n", ps_lxv->ulx);
			if (ps_lxv->avrppr != NULL)
				if (strcasestr(ps_lxv->avrppr, lp_ulx) != NULL)
				{
					free(lp_ulx);
					lp_f = lp_d + strlen(ps_lxv->ulx);
					ps_lxv->bff = lp_f;
					ps_lxv->ul = LXV_PREPROCESSEUR;
					continue;
				}
			free(lp_ulx);
			while ((*lp_f!='\n') && (*lp_f!=0))
				lp_f++;
			if (*lp_f == 0)
			{
				ps_lxv->bff = lp_f;
				ps_lxv->ul = LXV_ERREUR;
				continue;
			}
			if ((lp_f-lp_d) > LXV_TLLULX)
			{
				if ((lp_ulx = realloc(ps_lxv->ulx, lp_f-lp_d+1)) == NULL)
				{
					ps_lxv->ul = LXV_ERREUR;
					continue;
				}
				ps_lxv->ulx = lp_ulx;
			}
			strncpy(ps_lxv->ulx, lp_d, lp_f-lp_d);
			*(ps_lxv->ulx+(lp_f-lp_d)) = 0;
			ps_lxv->bff = lp_f;
			ps_lxv->ul = LXV_ERREUR;
			continue;
		}
	
		if (strchr(lr_nm1, *lp_f) != NULL)		// nombre (hexa binaire entier reel)
		{
			if (*lp_f == '$')
			{
				lp_f++;
				while (strchr(lr_hex, *lp_f) != NULL)
				{
					lp_f++;
					if (*lp_f == 0)
						break;
				}
				if ((lp_f-lp_d) > LXV_TLLULX)
				{
					*ps_lxv->ulx = 0;
					ps_lxv->bff = lp_f;
					ps_lxv->ul = LXV_ERREUR;
					continue;
				}
				strncpy(ps_lxv->ulx, lp_d, lp_f-lp_d);
				ps_lxv->ulx[lp_f-lp_d] = 0;
				ps_lxv->bff = lp_f;
				ps_lxv->ul = LXV_ENTIER_HEXA;
				continue;
			}
			if ((*lp_f == '0') && ((*(lp_f+1) == 'x') || (*(lp_f+1) == 'X')))
			{
				lp_f += 2;
				while (strchr(lr_hex, *lp_f) != NULL)
				{
					lp_f++;
					if (*lp_f == 0)
						break;
				}
				if ((lp_f-lp_d) > LXV_TLLULX)
				{
					*ps_lxv->ulx = 0;
					ps_lxv->bff = lp_f;
					ps_lxv->ul = LXV_ERREUR;
					continue;
				}
				strncpy(ps_lxv->ulx, lp_d, lp_f-lp_d);
				ps_lxv->ulx[lp_f-lp_d] = 0;
				ps_lxv->bff = lp_f;
				ps_lxv->ul = LXV_ENTIER_HEXA;
				continue;
			}
			if ((*lp_f == '0') && ((*(lp_f+1) == 'b') || (*(lp_f+1) == 'B')))
			{
				lp_f += 2;
				while (strchr(lr_bin, *lp_f) != NULL)
				{
					lp_f++;
					if (*lp_f == 0)
						break;
				}
				if ((lp_f-lp_d) > LXV_TLLULX)
				{
					*ps_lxv->ulx = 0;
					ps_lxv->bff = lp_f;
					ps_lxv->ul = LXV_ERREUR;
					continue;
				}
				strncpy(ps_lxv->ulx, lp_d, lp_f-lp_d);
				ps_lxv->ulx[lp_f-lp_d] = 0;
				ps_lxv->bff = lp_f;
				ps_lxv->ul = LXV_ENTIER_BINAIRE;
				continue;
			}
			if (*(lp_f+1) == '.')
			{
				lp_f += 2;
				while (strchr(lr_nm1, *lp_f) != NULL)
				{
					lp_f++;
					if (*lp_f == 0)
						break;
				}
				if ((lp_f-lp_d) > LXV_TLLULX)
				{
					*ps_lxv->ulx = 0;
					ps_lxv->bff = lp_f;
					ps_lxv->ul = LXV_ERREUR;
					continue;
				}
				strncpy(ps_lxv->ulx, lp_d, lp_f-lp_d);
				ps_lxv->ulx[lp_f-lp_d] = 0;
				ps_lxv->bff = lp_f;
				ps_lxv->ul = LXV_REEL;
				continue;
			}
			lp_f++;
			while (strchr(lr_nm1, *lp_f) != NULL)
			{
				lp_f++;
				if (*lp_f == 0)
					break;
			}
			if ((lp_f-lp_d) > LXV_TLLULX)
			{
				*ps_lxv->ulx = 0;
				ps_lxv->bff = lp_f;
				ps_lxv->ul = LXV_ERREUR;
				continue;
			}
			strncpy(ps_lxv->ulx, lp_d, lp_f-lp_d);
			ps_lxv->ulx[lp_f-lp_d] = 0;
			ps_lxv->bff = lp_f;
			ps_lxv->ul = LXV_ENTIER;
			continue;
		}
	
		if (strchr(lr_an1, *lp_f) != NULL)	// texte
		{
			lp_f++;
			while (strchr(lr_an2, *lp_f) != NULL)
			{
				lp_f++;
				if (*lp_f == 0)
					break;
			}
			if ((lp_f-lp_d) > LXV_TLLULX)
			{
				if ((lp_ulx = realloc(ps_lxv->ulx, lp_f-lp_d+1)) == NULL)
				{
					ps_lxv->ul = LXV_ERREUR;
					continue;
				}
				ps_lxv->ulx = lp_ulx;
			}
			if (*lp_f == ':')		// label
			{
				strncpy(ps_lxv->ulx, lp_d, lp_f-lp_d);
				ps_lxv->ulx[lp_f-lp_d] = 0;
				ls_asc(ps_ls, ps_lxv->ulx);
				lp_f++;
				ps_lxv->bff = lp_f;

				ps_lxv->ul = LXV_LABEL;
				continue;
			}
		
			strncpy(ps_lxv->ulx, lp_d, lp_f-lp_d);
			ps_lxv->ulx[lp_f-lp_d] = 0;
			ps_lxv->bff = lp_f;

			while ((*lp_f==' ') || (*lp_f=='\t') || (*lp_f=='\r') || (*lp_f=='\n'))
				lp_f++;
			if (*lp_f == '(')
			{
				ps_lxv->ul = LXV_FONCTION;
				continue;
			}
			else
			{
				ps_lxv->ul = LXV_IDENTIFIANT;
				continue;
			}
		}
	
		while (strchr(lr_spr, *lp_f) != NULL)
		{
			lp_f++;
			if (*lp_f == 0)
				break;
		}
		if ((lp_f-lp_d) > 0)
		{
			if ((lp_f-lp_d) > LXV_TLLULX)
			{
				*ps_lxv->ulx = 0;
				ps_lxv->bff = lp_f;
				ps_lxv->ul = LXV_ERREUR;
				continue;
			}
			strncpy(ps_lxv->ulx, lp_d, lp_f-lp_d);
			ps_lxv->ulx[lp_f-lp_d] = 0;
			ps_lxv->bff = lp_f;
			ps_lxv->ul = LXV_SEPARATEUR;
			continue;
		}
	
		while (strchr(lr_opr, *lp_f) != NULL)
		{
			lp_f++;
			if (*lp_f == 0)
				break;
		}
		if ((lp_f-lp_d) > 0)
		{
			if ((lp_f-lp_d) > LXV_TLLULX)
			{
				*ps_lxv->ulx = 0;
				ps_lxv->bff = lp_f;
				ps_lxv->ul = LXV_ERREUR;
				continue;
			}
			strncpy(ps_lxv->ulx, lp_d, lp_f-lp_d);
			ps_lxv->ulx[lp_f-lp_d] = 0;
			ps_lxv->bff = lp_f;
			ps_lxv->ul = LXV_OPERATEUR;
			continue;
		}
		
		sprintf(ps_lxv->ulx, "Caractere '%c' (0x%x) invalide", *lp_f, *lp_f);
		ps_lxv->bff = lp_f+1;
		ps_lxv->ul = LXV_ERREUR;
		continue;
	}
	return(0);
}

//
// Analyse lexicale pour decouper l'assembleur AVR en unite lexicale
//
// retour: ul pour la colorisation
//

int lxv_anl(LXV *ps_lxv, LS *ps_ls)
{
	char lr_nm1[] = "$0123456789";
	char lr_bin[] = "01";
	char lr_hex[] = "0123456789abcdefABCDEF";
	char lr_an1[] = "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char lr_an2[] = "_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	char lr_spr[] = "()[]{}.,;?";	// supprime le :
	char lr_opr[] = "*/+-&|~^%!=<>";
	char *lp_ulx, *lp_d, *lp_f;
	char *p;
	int  n;
	
	*ps_lxv->ulx = 0;
	lp_d = ps_lxv->bff;
	lp_f = lp_d;
	
	while ((*lp_f==' ') || (*lp_f=='\t') || (*lp_f=='\r') || (*lp_f=='\n')) // supprime les blancs
		lp_f++;
		
	if ((lp_f-lp_d) > 0)		// blanc ...
	{
		if ((lp_f-lp_d) > LXV_TLLULX)
		{
			*ps_lxv->ulx = 0;
			ps_lxv->bff = lp_f;
			ps_lxv->ul = LXV_ERREUR;
			return(LXV_ERREUR);
		}
		strncpy(ps_lxv->ulx, lp_d, lp_f-lp_d);
		*(ps_lxv->ulx+(lp_f-lp_d)) = 0;
		ps_lxv->bff = lp_f;
		if (ps_lxv->ul != LXV_PREPROCESSEUR)
			ps_lxv->ul = LXV_BLANC;
		return(LXV_BLANC);
	}

	if (*lp_f == 0)			// fin de fichier
	{
		ps_lxv->ul = LXV_FIN;
		return(LXV_FIN);
	}

	if (ps_lxv->ul == LXV_PREPROCESSEUR)	// lecture de la fin de la ligne proprocesseur
	{
		if (*lp_f == '<')
		{
			while ((*lp_f != '>') && (*lp_f != 0))
				lp_f++;
			if (*lp_f == 0)
			{
				ps_lxv->bff = lp_f;
				ps_lxv->ul = LXV_ERREUR;
				return(LXV_ERREUR);
			}
			lp_f++;
			if ((lp_f-lp_d) > LXV_TLLULX)
			{
				*ps_lxv->ulx = 0;
				ps_lxv->bff = lp_f;
				ps_lxv->ul = LXV_ERREUR;
				return(LXV_ERREUR);
			}
			strncpy(ps_lxv->ulx, lp_d, lp_f-lp_d);
			ps_lxv->ulx[lp_f-lp_d] = 0;
			ps_lxv->bff = lp_f;
			ps_lxv->ul = LXV_INCLUDE_SYS;
			return(LXV_INCLUDE_SYS);
		}
		if (*lp_f == '"')
		{
			lp_f++;
			while ((*lp_f != '"') && (*lp_f != 0))
				lp_f++;
			if (*lp_f == 0)
			{
				ps_lxv->bff = lp_f;
				ps_lxv->ul = LXV_ERREUR;
				return(LXV_ERREUR);
			}
			lp_f++;
			if ((lp_f-lp_d) > LXV_TLLULX)
			{
				if ((lp_ulx = realloc(ps_lxv->ulx, lp_f-lp_d+1)) != NULL)
				{
					ps_lxv->ul = LXV_ERREUR;
					return(LXV_ERREUR);
				}
				ps_lxv->ulx = lp_ulx;
			}
			strncpy(ps_lxv->ulx, lp_d, lp_f-lp_d);
			ps_lxv->ulx[lp_f-lp_d] = 0;
			ps_lxv->bff = lp_f;
			ps_lxv->ul = LXV_INCLUDE_FCH;
			return(LXV_INCLUDE_FCH);
		}
	}
		
	if (*lp_f == ';')	// commentaire ... \n
	{
		while ((*lp_f!='\n') && (*lp_f!=0))
			lp_f++;
		if (*lp_f == 0)
		{
			ps_lxv->bff = lp_f;
			ps_lxv->ul = LXV_ERREUR;
			return(LXV_ERREUR);
		}
		if ((lp_f-lp_d) > LXV_TLLULX)
		{
			if ((lp_ulx = realloc(ps_lxv->ulx, lp_f-lp_d+1)) == NULL)
			{
				ps_lxv->ul = LXV_ERREUR;
				return(LXV_ERREUR);
			}
			ps_lxv->ulx = lp_ulx;
		}
		strncpy(ps_lxv->ulx, lp_d, lp_f-lp_d);
		*(ps_lxv->ulx+(lp_f-lp_d)) = 0;
		ps_lxv->bff = lp_f;
		ps_lxv->ul = LXV_COMMENTAIRE;
		return(LXV_COMMENTAIRE);
	}
		
	if (*lp_f == '\'')		// constante caractere
	{
		lp_f++;
		while ((*lp_f!=0) && ((*(lp_f-2)!='\\') || (*(lp_f-1)!='\\') || (*lp_f!='\'')) && ((*(lp_f-1)=='\\') || (*lp_f!='\'')))
			lp_f++;
		if (*lp_f == 0)
		{
			ps_lxv->bff = lp_f;
			ps_lxv->ul = LXV_ERREUR;
			return(LXV_ERREUR);
		}
		lp_f++;
		if ((lp_f-lp_d) > LXV_TLLULX)
		{
			*ps_lxv->ulx = 0;
			ps_lxv->bff = lp_f;
			ps_lxv->ul = LXV_ERREUR;
			return(LXV_ERREUR);
		}
		strncpy(ps_lxv->ulx, lp_d, lp_f-lp_d);
		*(ps_lxv->ulx+(lp_f-lp_d)) = 0;
		ps_lxv->bff = lp_f;
		ps_lxv->ul = LXV_CONST_CAR;
		return(LXV_CONST_CAR);
	}
		
	if (*lp_f == '"')		// constante texte
	{
		lp_f++;
		/*
		exemple
		"abc"
		"\"abc\""
		"abc\\"
		"abc\"\\\""
		"abc\\\\"
		quitte la boucle si
		.1.
		0 <==> fin de fichier 
		|| (OU)
		.2. 
		le nombre d'\ devant le " est paire 
		|| (OU)
		.3.
		le nombre d'\ devant le " est impaire && (ET) derriere le " il ya un "
		*/
		while (1)
		{
			while ((*lp_f != 0) && (*lp_f != '"'))
				lp_f++;
			
			if (*lp_f == 0)
			{
				ps_lxv->bff = lp_f;
				ps_lxv->ul = LXV_ERREUR;
				return(LXV_ERREUR);
			}
			
			n = 0;
			p = lp_f - 1;
			while (*p == '\\')
			{
				n++;
				p--;
				if (p == lp_d)
					break;
			}
			n %= 2;
			
			if (!n)
				break;
				
			lp_f++;
			if (*(lp_f) == '"')
				break;
		}
		
		lp_f++;
		if ((lp_f-lp_d) > LXV_TLLULX)
		{
			if ((lp_ulx = realloc(ps_lxv->ulx, lp_f-lp_d+1)) == NULL)
			{
				ps_lxv->ul = LXV_ERREUR;
				return(LXV_ERREUR);
			}
			ps_lxv->ulx = lp_ulx;
		}
		strncpy(ps_lxv->ulx, lp_d, lp_f-lp_d);
		*(ps_lxv->ulx+(lp_f-lp_d)) = 0;
		ps_lxv->bff = lp_f;
		ps_lxv->ul = LXV_CONST_TEXTE;
		return(LXV_CONST_TEXTE);
	}
		
	if (*lp_f == '.')		// commande preprocesseur
	{
		while ((*lp_f!=' ') && (*lp_f!='\t') && (*lp_f!='\r') && (*lp_f!='\n') && (*lp_f!=0))
			lp_f++;
		strncpy(ps_lxv->ulx, lp_d, lp_f-lp_d);
		*(ps_lxv->ulx+(lp_f-lp_d)) = 0;
			
		if ((lp_ulx = malloc(strlen(ps_lxv->ulx)+3)) == NULL)
		{
			ps_lxv->ul = LXV_ERREUR;
			return(LXV_ERREUR);
		}
		sprintf(lp_ulx, "\n%s\n", ps_lxv->ulx);
		if (ps_lxv->avrppr != NULL)
			if (strcasestr(ps_lxv->avrppr, lp_ulx) != NULL)
			{
				free(lp_ulx);
				lp_f = lp_d + strlen(ps_lxv->ulx);
				ps_lxv->bff = lp_f;
				ps_lxv->ul = LXV_PREPROCESSEUR;
				return(LXV_PREPROCESSEUR);
			}
		free(lp_ulx);
		while ((*lp_f!='\n') && (*lp_f!=0))
			lp_f++;
		if (*lp_f == 0)
		{
			ps_lxv->bff = lp_f;
			ps_lxv->ul = LXV_ERREUR;
			return(LXV_ERREUR);
		}
		if ((lp_f-lp_d) > LXV_TLLULX)
		{
			if ((lp_ulx = realloc(ps_lxv->ulx, lp_f-lp_d+1)) == NULL)
			{
				ps_lxv->ul = LXV_ERREUR;
				return(LXV_ERREUR);
			}
			ps_lxv->ulx = lp_ulx;
		}
		strncpy(ps_lxv->ulx, lp_d, lp_f-lp_d);
		*(ps_lxv->ulx+(lp_f-lp_d)) = 0;
		ps_lxv->bff = lp_f;
		ps_lxv->ul = LXV_ERREUR;
		return(LXV_ERREUR);
	}
	
	if (strchr(lr_nm1, *lp_f) != NULL)		// nombre (hexa binaire entier reel)
	{
		if (*lp_f == '$')
		{
			lp_f++;
			while (strchr(lr_hex, *lp_f) != NULL)
			{
				lp_f++;
				if (*lp_f == 0)
					break;
			}
			if ((lp_f-lp_d) > LXV_TLLULX)
			{
				*ps_lxv->ulx = 0;
				ps_lxv->bff = lp_f;
				ps_lxv->ul = LXV_ERREUR;
				return(LXV_ERREUR);
			}
			strncpy(ps_lxv->ulx, lp_d, lp_f-lp_d);
			ps_lxv->ulx[lp_f-lp_d] = 0;
			ps_lxv->bff = lp_f;
			ps_lxv->ul = LXV_ENTIER_HEXA;
			return(LXV_ENTIER_HEXA);
		}
		if ((*lp_f == '0') && ((*(lp_f+1) == 'x') || (*(lp_f+1) == 'X')))
		{
			lp_f += 2;
			while (strchr(lr_hex, *lp_f) != NULL)
			{
				lp_f++;
				if (*lp_f == 0)
					break;
			}
			if ((lp_f-lp_d) > LXV_TLLULX)
			{
				*ps_lxv->ulx = 0;
				ps_lxv->bff = lp_f;
				ps_lxv->ul = LXV_ERREUR;
				return(LXV_ERREUR);
			}
			strncpy(ps_lxv->ulx, lp_d, lp_f-lp_d);
			ps_lxv->ulx[lp_f-lp_d] = 0;
			ps_lxv->bff = lp_f;
			ps_lxv->ul = LXV_ENTIER_HEXA;
			return(LXV_ENTIER_HEXA);
		}
		if ((*lp_f == '0') && ((*(lp_f+1) == 'b') || (*(lp_f+1) == 'B')))
		{
			lp_f += 2;
			while (strchr(lr_bin, *lp_f) != NULL)
			{
				lp_f++;
				if (*lp_f == 0)
					break;
			}
			if ((lp_f-lp_d) > LXV_TLLULX)
			{
				*ps_lxv->ulx = 0;
				ps_lxv->bff = lp_f;
				ps_lxv->ul = LXV_ERREUR;
				return(LXV_ERREUR);
			}
			strncpy(ps_lxv->ulx, lp_d, lp_f-lp_d);
			ps_lxv->ulx[lp_f-lp_d] = 0;
			ps_lxv->bff = lp_f;
			ps_lxv->ul = LXV_ENTIER_BINAIRE;
			return(LXV_ENTIER_BINAIRE);
		}
		if (*(lp_f+1) == '.')
		{
			lp_f += 2;
			while (strchr(lr_nm1, *lp_f) != NULL)
			{
				lp_f++;
				if (*lp_f == 0)
					break;
			}
			if ((lp_f-lp_d) > LXV_TLLULX)
			{
				*ps_lxv->ulx = 0;
				ps_lxv->bff = lp_f;
				ps_lxv->ul = LXV_ERREUR;
				return(LXV_ERREUR);
			}
			strncpy(ps_lxv->ulx, lp_d, lp_f-lp_d);
			ps_lxv->ulx[lp_f-lp_d] = 0;
			ps_lxv->bff = lp_f;
			ps_lxv->ul = LXV_REEL;
			return(LXV_REEL);
		}
		lp_f++;
		while (strchr(lr_nm1, *lp_f) != NULL)
		{
			lp_f++;
			if (*lp_f == 0)
				break;
		}
		if ((lp_f-lp_d) > LXV_TLLULX)
		{
			*ps_lxv->ulx = 0;
			ps_lxv->bff = lp_f;
			ps_lxv->ul = LXV_ERREUR;
			return(LXV_ERREUR);
		}
		strncpy(ps_lxv->ulx, lp_d, lp_f-lp_d);
		ps_lxv->ulx[lp_f-lp_d] = 0;
		ps_lxv->bff = lp_f;
		ps_lxv->ul = LXV_ENTIER;
		return(LXV_ENTIER);
	}
	
	if (strchr(lr_an1, *lp_f) != NULL)	// texte
	{
		lp_f++;
		while (strchr(lr_an2, *lp_f) != NULL)
		{
			lp_f++;
			if (*lp_f == 0)
				break;
		}
		if ((lp_f-lp_d) > LXV_TLLULX)
		{
			if ((lp_ulx = realloc(ps_lxv->ulx, lp_f-lp_d+1)) == NULL)
			{
				ps_lxv->ul = LXV_ERREUR;
				return(LXV_ERREUR);
			}
			ps_lxv->ulx = lp_ulx;
		}
		if (*lp_f == ':')		// label
		{
			lp_f++;
			strncpy(ps_lxv->ulx, lp_d, lp_f-lp_d);
			ps_lxv->ulx[lp_f-lp_d] = 0;
			ps_lxv->bff = lp_f;

			ps_lxv->ul = LXV_LABEL;
			return(LXV_LABEL);
		}
		
		strncpy(ps_lxv->ulx, lp_d, lp_f-lp_d);
		ps_lxv->ulx[lp_f-lp_d] = 0;
		ps_lxv->bff = lp_f;
		
		if (ls_txt1(ps_ls, ps_lxv->ulx) != -1)
		{
			ps_lxv->ul = LXV_LABEL;
			return(LXV_LABEL);
		}
		if ((lp_ulx = malloc(strlen(ps_lxv->ulx)+3)) == NULL)
		{
			ps_lxv->ul = LXV_ERREUR;
			return(LXV_ERREUR);
		}
		sprintf(lp_ulx, "\n%s\n", ps_lxv->ulx);
		if (ps_lxv->avrins != NULL)
			if (strcasestr(ps_lxv->avrins, lp_ulx) != NULL)
			{
				free(lp_ulx);
				ps_lxv->ul = LXV_INSTRUCTION;
				return(LXV_INSTRUCTION);
			}
		if (ps_lxv->avrrgs != NULL)
			if (strcasestr(ps_lxv->avrrgs, lp_ulx) != NULL)
			{
				free(lp_ulx);
				ps_lxv->ul = LXV_REGISTRE;
				return(LXV_REGISTRE);
			}
		if (ps_lxv->avrmcr != NULL)
			if (strcasestr(ps_lxv->avrmcr, lp_ulx) != NULL)
			{
				free(lp_ulx);
				ps_lxv->ul = LXV_MACRO;
				return(LXV_MACRO);
			}
		if (ps_lxv->avradr != NULL)
			if (strcasestr(ps_lxv->avradr, lp_ulx) != NULL)
			{
				free(lp_ulx);
				ps_lxv->ul = LXV_ADRESSE;
				return(LXV_ADRESSE);
			}
		free(lp_ulx);

		while ((*lp_f==' ') || (*lp_f=='\t') || (*lp_f=='\r') || (*lp_f=='\n'))
			lp_f++;
		if (*lp_f == '(')
		{
			ps_lxv->ul = LXV_FONCTION;
			return(LXV_FONCTION);
		}
		else
		{
			ps_lxv->ul = LXV_IDENTIFIANT;
			return(LXV_IDENTIFIANT);
		}
	}
	
	while (strchr(lr_spr, *lp_f) != NULL)
	{
		lp_f++;
		if (*lp_f == 0)
			break;
	}
	if ((lp_f-lp_d) > 0)
	{
		if ((lp_f-lp_d) > LXV_TLLULX)
		{
			*ps_lxv->ulx = 0;
			ps_lxv->bff = lp_f;
			ps_lxv->ul = LXV_ERREUR;
			return(LXV_ERREUR);
		}
		strncpy(ps_lxv->ulx, lp_d, lp_f-lp_d);
		ps_lxv->ulx[lp_f-lp_d] = 0;
		ps_lxv->bff = lp_f;
		ps_lxv->ul = LXV_SEPARATEUR;
		return(LXV_SEPARATEUR);
	}
	
	while (strchr(lr_opr, *lp_f) != NULL)
	{
		lp_f++;
		if (*lp_f == 0)
			break;
	}
	if ((lp_f-lp_d) > 0)
	{
		if ((lp_f-lp_d) > LXV_TLLULX)
		{
			*ps_lxv->ulx = 0;
			ps_lxv->bff = lp_f;
			ps_lxv->ul = LXV_ERREUR;
			return(LXV_ERREUR);
		}
		strncpy(ps_lxv->ulx, lp_d, lp_f-lp_d);
		ps_lxv->ulx[lp_f-lp_d] = 0;
		ps_lxv->bff = lp_f;
		ps_lxv->ul = LXV_OPERATEUR;
		return(LXV_OPERATEUR);
	}
		
	sprintf(ps_lxv->ulx, "Caractere '%c' (0x%x) invalide", *lp_f, *lp_f);
	ps_lxv->bff = lp_f+1;
	ps_lxv->ul = LXV_ERREUR;
	return(LXV_ERREUR);
}

// Destructeur v

void lxv_dst(LXV *ps_lxv)
{
	if (ps_lxv == NULL)
		return;
		
	io_frebff(ps_lxv->avrins);
	io_frebff(ps_lxv->avrmcr);
	io_frebff(ps_lxv->avrppr);
	io_frebff(ps_lxv->avrrgs);
	io_frebff(ps_lxv->avradr);

	if (ps_lxv->ulx)
		free(ps_lxv->ulx);
	if (ps_lxv)
		free(ps_lxv);
}

//
// Constructeur r ===================== ARM =======================
//

LXR *lxr_cns(char *pp_bff)
{
	return(NULL);
}

//
// Analyse lexicale pour decouper le c en unite lexicale
//
// retour: ul pour la colorisation
//

int lxr_anl(LXR *ps_lxr)
{
	return(0);
}

// Destructeur

void lxr_dst(LXR *ps_lxr)
{
}

// Bufferise un fichier

char *io_bfffch(char *pr_nomfch, int *pi_crclus)
{
	struct stat ls_stt;
	char *lr_bfffch;
	int  lo_fch;
	
	lg_strcpy(lg.fnc, "io_bfffch");
	
	*pi_crclus = 0;
	if (access(pr_nomfch, F_OK) == -1)
	{
		fprintf(stderr, "c io_bfffch access(\"%s\"): %s\n", pr_nomfch, strerror(errno));
		lg_strcpy(lg.mss, pr_nomfch);
		lg_strcpy(lg.err, strerror(errno));
		lg_ecr();
		return(NULL);
	}
	if (stat(pr_nomfch, &ls_stt) == -1)
	{
		fprintf(stderr, "c io_bfffch stat(\"%s\"): %s\n", pr_nomfch, strerror(errno));
		lg_strcpy(lg.mss, pr_nomfch);
		lg_strcpy(lg.err, strerror(errno));
		lg_ecr();
		return(NULL);
	}
	if ((lr_bfffch = malloc(ls_stt.st_size+1)) == NULL)
	{
		fprintf(stderr, "c io_bfffch malloc(%ld): %s\n", ls_stt.st_size+1, strerror(errno));
		lg_strcpy(lg.mss, pr_nomfch);
		lg_strcpy(lg.err, strerror(errno));
		lg_ecr();
		return(NULL);
	}
	if ((lo_fch = open(pr_nomfch, O_RDONLY)) == -1)
	{
		fprintf(stderr, "c io_bfffch open(\"%s\"): %s\n", pr_nomfch, strerror(errno));
		lg_strcpy(lg.mss, pr_nomfch);
		lg_strcpy(lg.err, strerror(errno));
		lg_ecr();
		free(lr_bfffch);
		return(NULL);
	}
	if ((*pi_crclus = read(lo_fch, lr_bfffch, ls_stt.st_size)) != ls_stt.st_size)
	{
		fprintf(stderr, "c io_bfffch read(\"%s\"): %s\n", pr_nomfch, strerror(errno));
		lg_strcpy(lg.mss, pr_nomfch);
		lg_strcpy(lg.err, strerror(errno));
		lg_ecr();
		close(lo_fch);
		free(lr_bfffch);
		return(NULL);
	}
	lr_bfffch[ls_stt.st_size] = 0;
	close(lo_fch);
	
	//lg_strcpy(lg.mss, pr_nomfch);
	//sprintf(lg.err, "lus=%d", *pi_crclus);
	//lg_ecr();
	
	return(lr_bfffch);
}

//
// garnit une liste avec un fichier
//
// pr_nomfch: nom du fichier a charger dans la liste
// pc: caractere = separateur dans le fichier
//

LS *io_lstfch(char *pr_nomfch, char pc)
{
	FILE *lo_fch;
	char *lr_lgn;
	char *d, *f;
	char txt[8][80];
	int  i;
	LS   *ls;
	
	lg_strcpy(lg.fnc, "io_lstfch");
	
	ls = ls_cns();
	
	if (access(pr_nomfch, F_OK) == -1)
	{
		fprintf(stderr, "c io_lstfch access(\"%s\"): %s\n", pr_nomfch, strerror(errno));
		lg_strcpy(lg.mss, pr_nomfch);
		lg_strcpy(lg.err, strerror(errno));
		lg_ecr();
		return(NULL);
	}
	if ((lr_lgn = malloc(LNGSTR)) == NULL)
	{
		fprintf(stderr, "c io_lstfch malloc(%d): %s\n", LNGSTR, strerror(errno));
		lg_strcpy(lg.mss, pr_nomfch);
		lg_strcpy(lg.err, strerror(errno));
		lg_ecr();
		return(NULL);
	}
	if ((lo_fch = fopen(pr_nomfch, "r")) == NULL)
	{
		fprintf(stderr, "c io_lstfch fopen(\"%s\"): %s\n", pr_nomfch, strerror(errno));
		lg_strcpy(lg.mss, pr_nomfch);
		lg_strcpy(lg.err, strerror(errno));
		lg_ecr();
		return(NULL);
	}
	while (fgets(lr_lgn, LNGSTR, lo_fch))
	{
		printf("c: ");
		if ((d = strchr(lr_lgn, '\n')) != NULL)
			*d = 0;
		if ((d = strchr(lr_lgn, '\r')) != NULL)
			*d = 0;
		if ((lr_lgn[0] == 0) || (lr_lgn[0] == '#'))	// vide || commentaire
		{
			printf("\n");
			continue;
		}
//ADC;ADC Rd, Rs;0001 11sd dddd ssss;Add with Carry Two Registers;2;w				
		for (i=0, d=lr_lgn; f=strchr(d, pc); i++, d=f+1)
		{
			strncpy(txt[i], d, f-d);
			txt[i][f-d] = 0;
			printf("%d=%s ", i, txt[i]);
		}
		strcpy(txt[i], d);
		
		printf("%d=%s\n", i, txt[i]);
		switch (i)
		{
			case 0:
				ls_asc(ls, "%s", txt[0]);
				break;
			case 1:
				ls_asc(ls, "%s %s", txt[0], txt[1]);
				break;
			case 2:
				ls_asc(ls, "%s %s %s", txt[0], txt[1], txt[2]);
				break;
			case 3:
				ls_asc(ls, "%s %s %s %s", txt[0], txt[1], txt[2], txt[3]);
				break;
			case 4:
				ls_asc(ls, "%s %s %s %s %s", txt[0], txt[1], txt[2], txt[3], txt[4]);
				break;
			case 5:
				ls_asc(ls, "%s %s %s %s %s %s", txt[0], txt[1], txt[2], txt[3], txt[4], txt[5]);
				break;
			case 6:
				ls_asc(ls, "%s %s %s %s %s %s %s", txt[0], txt[1], txt[2], txt[3], txt[4], txt[5], txt[6]);
				break;
			case 7:
				ls_asc(ls, "%s %s %s %s %s %s %s %s", txt[0], txt[1], txt[2], txt[3], txt[4], txt[5], txt[6], txt[7]);
				break;
		}
	}
	fclose(lo_fch);
	
	return(ls);
}

// Ecrit un buffer

int io_ecrbff(char *pr_nomfch, char *pr_bfffch, int pi_ecrnmb)
{
	int  lo_fch, li_ecrnmb;
	
	lg_strcpy(lg.fnc, "io_ecrbff");
	
	if ((lo_fch = open(pr_nomfch, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)) == -1)
	{
		fprintf(stderr, "c io_ecrbff open(\"%s\"): %s\n", pr_nomfch, strerror(errno));
		return(0);
	}
	if ((li_ecrnmb = write(lo_fch, pr_bfffch, pi_ecrnmb)) == -1)
	{
		fprintf(stderr, "c io_ecrbff write(\"%s\"): %s\n", pr_nomfch, strerror(errno));
	}
	close(lo_fch);
	return(li_ecrnmb);
}

// Libere la memoire

void io_frebff(char *pr_bfffch)
{
	if (pr_bfffch != NULL)
		free(pr_bfffch);
	//lg_strcpy(lg.mss, "free()");
	//sprintf(lg.err, "ok");
	//lg_ecr();
}

// Copie un fichier source vers un fichier destination
int io_cpsd(char *pr_src, char *pr_dst)
{
	pid_t cpid;
	int stt;
	
	cpid = fork();
	if (cpid == 0)	// child
	{
		execl("/bin/cp", "cp", "--preserve", pr_src, pr_dst, (char *) NULL);
	}
	else	// parent
	{
    	do 
    	{
    		waitpid(cpid, &stt, WUNTRACED | WCONTINUED);
    	} while (!WIFEXITED(stt) && !WIFSIGNALED(stt));
    	
    	if (WIFEXITED(stt)) 
    	{
    		if (WEXITSTATUS(stt) != 0)	// erreur cp
				return(true);
			else
				return(false);
		}
	}	
	return(true);
}
/*
int io_cpsd(char *pr_src, char *pr_dst)
{
	int s, d, lus, ecr;
	struct stat buf;
	char *mmy;
	
	if ((s = open(pr_src, O_RDONLY)) == -1)
		return(true);
	if ((d = open(pr_dst, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR)) == -1)
	{
		close(s);
		return(true);
	}
	if (fstat(s, &buf) != 0)
	{
		close(d);
		close(s);
		return(true);
	}
	if ((mmy = malloc(buf.st_size)) == NULL)
	{
		close(d);
		close(s);
		return(true);
	}
	if ((lus = read(s, mmy, buf.st_size)) == -1)
	{
		free(mmy);
		close(d);
		close(s);
		return(true);
	}
	if (lus != buf.st_size)
	{
		free(mmy);
		close(d);
		close(s);
		return(true);
	}
	if ((ecr = write(d, mmy, lus)) == -1)
	{
		free(mmy);
		close(d);
		close(s);
		return(true);
	}
	free(mmy);
	close(d);
	close(s);
	return(false);
}
*/

// Move un fichier(dossier) source vers un fichier(dossier) destination
int io_mvsd(char *pr_src, char *pr_dst)
{
	pid_t cpid;
	int stt;
	
	cpid = fork();
	if (cpid == 0)	// child
	{
		execl("/bin/mv", "mv", "-n", pr_src, pr_dst, (char *) NULL);
	}
	else	// parent
	{
    	do 
    	{
    		waitpid(cpid, &stt, WUNTRACED | WCONTINUED);
    	} while (!WIFEXITED(stt) && !WIFSIGNALED(stt));
    	
    	if (WIFEXITED(stt)) 
    	{
    		if (WEXITSTATUS(stt) != 0)	// erreur mv
				return(true);
			else
				return(false);
		}
	}	
	return(true);
}

//
// Lecture Information Version
//
// pp_bff: entree, bufferisation du programme ou on lit l'info
// pi_lng: entree, longueur du buffer programme ou on lit l'info
// pp_prj: sortie, nom du projet trouve dans le buffer
// pp_vrs: sortie, version trouvee dans le buffer
// pp_dat: sortie, date de creation trouvee dans le buffer
// retour: 0=trouve 1=pas trouve
//

int iv_info(char *pp_bff, int pi_lng, char *pp_prj, char *pp_vrs, char *pp_dat)
{
	int i, j;
	
	strcpy(pp_prj, "?");
	strcpy(pp_vrs, "?");
	strcpy(pp_dat, "?");
	
	if (pi_lng < 25)
		return(1);
		
	for (i=0, j=32; i<pi_lng; i++)
	{
		if ((*(pp_bff+i+0) == 'j') &&
			(*(pp_bff+i+1) == 'o') &&
			(*(pp_bff+i+2) == 'e') &&
			(*(pp_bff+i+3) == 'l'))
		{
			i += 5;
			for (j=0; j<32; j++)
			{
				if ((*(pp_bff+i+j+0) == 'p') &&
					(*(pp_bff+i+j+1) == 'a') &&
					(*(pp_bff+i+j+2) == 'r') &&
					(*(pp_bff+i+j+3) == 'r') &&
					(*(pp_bff+i+j+4) == 'a') &&
					(*(pp_bff+i+j+5) == 't'))
				{
					switch (j)
					{
						case 28:	// vrai
							strncpy(pp_prj, pp_bff+i, 10);
							pp_prj[10] = 0;
							strncpy(pp_vrs, pp_bff+i+11, 8);
							pp_vrs[8] = 0;
							strncpy(pp_dat, pp_bff+i+20, 7);
							pp_dat[7] = 0;
							break;
						case 20:	// intermediaire
							strncpy(pp_prj, pp_bff+i, 10);
							pp_prj[10] = 0;
							strncpy(pp_vrs, pp_bff+i+11, 8);
							pp_vrs[8] = 0;
							strcpy(pp_dat, "?");
							break;
						case 13:	// ancienne
							strncpy(pp_prj, pp_bff+i, 8);
							pp_prj[8] = 0;
							sprintf(pp_vrs, "%d.%d", *(pp_bff+i+9), *(pp_bff+i+10));
							sprintf(pp_dat, "%d/%d", *(pp_bff+i+11), *(pp_bff+i+12));
							break;
						default:
							strcpy(pp_prj, "???");
							strcpy(pp_vrs, "?.?");
							strcpy(pp_dat, "?/?");
							break;
					}
					break;
				}
			}
			if (j != 32)
				break;
		}
	}
		
	return((j==32)?1:0);
}

//
// Ajoute un texte dans la liste (sans double, sans tri en fin)
//
// pour un texte simple ls_add(texte)
// pour un texte et une caractere ls_add("%s %c", texte, caractere)
// si c'est un nombre ls_add("%d", nombre)
// idem avec caractere ls_add("%d %c", nombre, caractere)
//
// retour: 0=ajoute 1=existe deja rien fait
//

int ls_asf(LS *liste, char *texte, ...)
{
	CH *nv, *crt;
	va_list ap;
	char *chn;
	int  i, nmb;
	char car;
	
   	nv = malloc(sizeof(*nv));
	nv->texte1 = NULL;
	nv->texte2 = NULL;
	nv->texte3 = NULL;
	nv->nombre = -1;
	nv->caractere = ' ';

	if (strchr(texte, '%') == NULL)
	{
		nv->texte1 = malloc(strlen(texte)+1);
		strcpy(nv->texte1, texte);
	}
	else
	{
		va_start(ap, texte);
		i = 0;
		while (*texte)
		{
			if (*texte != '%')
			{
				texte++;
				continue;
			}
			texte++;
			switch (*texte)
			{
				case 's':              /* string */
					if (i == 0)
					{
						chn = va_arg(ap, char *);
						nv->texte1 = malloc(strlen(chn)+1);
						strcpy(nv->texte1, chn);
					}
					if (i == 1)
					{
						chn = va_arg(ap, char *);
						nv->texte2 = malloc(strlen(chn)+1);
						strcpy(nv->texte2, chn);
					}
					if (i == 2)
					{
						chn = va_arg(ap, char *);
						nv->texte3 = malloc(strlen(chn)+1);
						strcpy(nv->texte3, chn);
					}
					i++;
					break;
				case 'd':              /* int */
					nmb = va_arg(ap, int);
					nv->nombre = nmb;
					break;
				case 'c':              /* char */
					/* need a cast here since va_arg only takes fully promoted types */
					car = (char) va_arg(ap, int);
					nv->caractere = car;
					break;
			}
			texte++;
		}
		va_end(ap);
	}
	
	crt = liste->first;
	while (crt != NULL)
	{
		if (strcmp(crt->texte1, nv->texte1) == 0)
			break;
		crt = crt->next;
	}
	if (crt == NULL)
	{
		if (liste->last == NULL)	// creation premier
		{
			nv->prior = NULL;
			nv->next = NULL;
			liste->first = nv;
			liste->current = nv;
			liste->last = nv;
		}
		else					// ajout en fin de liste
		{
			liste->last->next = nv;
			nv->prior = liste->last;
			nv->next = NULL;
			liste->current = nv;
			liste->last = nv;
		}
		return(0);
	}
	
	return(1);
}

// Efface le debut de l'ecran (jusqu'au cursseur)
void es_cld(void)
{
	printf("\033[1J");
}
// Efface tout l'ecran
void es_cls(void)
{
	printf("\033[2J");
}
// Efface la fin de l'ecran (apres le cursseur)
void es_clf(void)
{
	printf("\033[J");
}

// Positionne le cursseur en x, y
void es_gotoxy(int x, int y)
{
	printf("\033[%d;%dH", y, x);
}

// Efface le debut de la ligne (jusqu'au cursseur)
void es_efd(void)
{
	printf("0x1B[1K");
}
// Efface toute la ligne
void es_efl(void)
{
	printf("0x1B[2K");
}
// Efface la fin de la ligne (apres le cursseur)
void es_eff(void)
{
	printf("0x1B[K");
}

// Change la couleur de l'encre
void es_encre(char *couleur)
{
	if (strcmp(couleur, "Rouge") == 0)
		printf("\033[31m");
	if (strcmp(couleur, "Vert") == 0)
		printf("\033[32m");
	if (strcmp(couleur, "Marron") == 0)
		printf("\033[33m");
	if (strcmp(couleur, "Bleu") == 0)
		printf("\033[34m");
	if (strcmp(couleur, "Magenta") == 0)
		printf("\033[35m");
	if (strcmp(couleur, "Cyan") == 0)
		printf("\033[36m");
	if (strcmp(couleur, "Blanc") == 0)
		printf("\033[37m");
	if (strcmp(couleur, "Noir") == 0)
		printf("\033[30m");
}

// change le couleur du fond
void es_fond(char *couleur)
{
	if (strcmp(couleur, "Rouge") == 0)
		printf("\033[41m");
	if (strcmp(couleur, "Vert") == 0)
		printf("\033[42m");
	if (strcmp(couleur, "Marron") == 0)
		printf("\033[43m");
	if (strcmp(couleur, "Bleu") == 0)
		printf("\033[44m");
	if (strcmp(couleur, "Magenta") == 0)
		printf("\033[45m");
	if (strcmp(couleur, "Cyan") == 0)
		printf("\033[46m");
	if (strcmp(couleur, "Blanc") == 0)
		printf("\033[47m");
	if (strcmp(couleur, "Noir") == 0)
		printf("\033[49m");
}

// =============================================== fonction =============================================

void fv_printf(char *pr_clr, char *pr_msg, char *pr_err, ...)
{
	va_list ap;
	
	printf("%s ", pr_msg);
	es_encre(pr_clr);
	va_start(ap, pr_err);
	vprintf(pr_err, ap);
	es_encre("Blanc");
}

// p_att = FALSE lance la commande n'attend pas la fin
// p_att = TRUE  lance la commande attend la fin
// p_out = NULL pas de redirection stdout
// p_err = NULL pas de redirection stderr

int fi_lance(char *p_cmd, int p_att, char *p_out, char *p_err, char **p_arg)
{
	int j, stt;
	pid_t cpid;
	
	lg_strcpy(lg.fnc, "fi_lance");

	lg.mss[0] = 0;
	for (j=0; p_arg[j]!=NULL; j++)
	{
		lg_strcat(lg.mss, p_arg[j]);
		lg_strcat(lg.mss, " ");
	}

	cpid = fork();
	if (cpid == 0)	// child
	{
		if (p_out != NULL) 
			freopen(p_out, "w", stdout);
		if (p_err != NULL)
			freopen(p_err, "w", stderr);
		execv(p_cmd, p_arg);
	}
	else	// parent
	{
		if (p_att != FALSE)
		{ 
			do 
			{
				waitpid(cpid, &stt, WUNTRACED | WCONTINUED);
			} while (!WIFEXITED(stt) && !WIFSIGNALED(stt));
		
			if (WIFEXITED(stt)) 
			{
				if (WEXITSTATUS(stt) != 0)	// erreur compil
					lg_strcpy(lg.err, "KO");
				else
					lg_strcpy(lg.err, "ok");
			
				lg_ecr();
			}
		}
		else
		{
			stt = (int) cpid;
			lg_strcpy(lg.err, "...");
			lg_ecr();
		} 
	}
	return(stt);
}

// Purge dossier log

void fv_prglog(void)
{
	DIR *ld_dss;
	struct dirent *ls_art;
	struct stat sb;
	char lt_blanc[LNGLGN+1];
	char lt_art[LNGLGN+1];
	int  li;
	char lt_chm[LNGLGN+1];
	
	for (li=0; li<LNGLGN; li++)
		lt_blanc[li] = ' ';
	lt_blanc[LNGLGN] = 0;

	if ((ld_dss = opendir(en.log)) == NULL)
	{
		fv_printf("Jaune", "opendir", "(%s): %s\n", en.log, strerror(errno));
		return;
	}
	
	while ((ls_art = readdir(ld_dss)) != NULL)
	{
		if (strcmp(ls_art->d_name, ".") == 0)
			continue;
		if (strcmp(ls_art->d_name, "..") == 0)
			continue;
		
		strcpy(lt_art, lt_blanc);
		
		/*
		   DT_BLK      This is a block device.
		   DT_CHR      This is a character device.
		   DT_DIR      This is a directory.
		   DT_FIFO     This is a named pipe (FIFO).

		   DT_LNK      This is a symbolic link.
		   DT_REG      This is a regular file.
		   DT_SOCK     This is a UNIX domain socket.
		   DT_UNKNOWN  The file type is unknown.
		*/
		
		if (ls_art->d_type == DT_REG)
		{
			sprintf(lt_art, "%s/%s", en.log, ls_art->d_name);
			if (stat(lt_art, &sb) == 0)
			{
				//dr_add(pdr, lt_art, sb.st_size, sb.st_mtime);
				if (sb.st_size == 0)
					unlink(lt_art);
			}
		}
	}
	closedir(ld_dss);
	
	return;
}

