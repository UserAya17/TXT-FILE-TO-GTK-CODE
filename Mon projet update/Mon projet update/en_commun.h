#pragma once
#ifndef NEW_TABLE_FRAME_PROG_H
#define NEW_TABLE_FRAME_PROG_H
#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>
#include <ctype.h>

#define TOKEN_BUFFER_SIZE 100
char token_buffer[TOKEN_BUFFER_SIZE];
static int i = 0;  // variable statique pour conserver l'index du tableau entre les appels




typedef struct
{
    GtkWidget* container; //conteneur d'une entrÃƒÂ©e.
    int posx; //position selon axe x
    int posy; //position selon axe y
    //int height; //la longueur d'entrÃƒÂ©e.
    //int width; //largeur.
}commune;

typedef struct
{
    int width; //longueur
    int height; //largeur
}taille;

typedef struct
{
    char nom[9];
    GtkWidget* info;
}cell;
typedef struct Cel
{
    cell* cell;
    struct Cel* suivant;
}Cellule;

Cellule* CreeCellule(GtkWidget* widget, char tab[10])
{
    Cellule* NE = g_new(Cellule, 1);
    //cell* contenu = g_new(cell, 1);
    cell* contenu = (cell*)malloc(sizeof(cell));
    strcpy(contenu->nom, tab);
    contenu->info = widget;

    NE->cell = contenu;
    NE->suivant = NULL;
    /*strcpy(NE->cell->nom, tab);
    NE->suivant = NULL;
    NE->cell->info = widget;*/

    return (Cellule*)NE;
}
typedef struct cellule_propriete
{
    char attribut[20];
    char valeur[20];
    struct cellule_propriete* suivant;
}cellule_propriete;

cellule_propriete* ajouter_propriete(cellule_propriete* liste, char attribut[20], char valeur[20])
{
    cellule_propriete* NE = g_new(cellule_propriete, 1);
    strcpy(NE->attribut, attribut);
    strcpy(NE->valeur, valeur);
    NE->suivant = liste;

    //ajout
    liste = NE;

    return liste;
}
Cellule* Empiler(Cellule* Pile, GtkWidget* widget, char tab[10])
{
    Cellule* NE = CreeCellule(widget, tab);
    NE->suivant = Pile;
    Pile = NE;
    return (Cellule*)Pile;
}
GtkWidget* create_window()
{
    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Exemple de window");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_widget_set_size_request(window, 800, 800);
    return window;
}
//int check_reserved()
//{
//    //printf("\n on verifie le mot : %s \n",token_buffer);
//    if (strcmp(token_buffer, "<window>") == 0) return 1;
//    if (strcmp(token_buffer, "<button>") == 0) return 2;
//    if (strcmp(token_buffer, "<progressbar>") == 0) return 3;
//    if (strcmp(token_buffer, "<frame>") == 0)   return ((int)4);
//    if (strcmp(token_buffer, "<\\window>") == 0) return 5;
//    if (strcmp(token_buffer, "<\\button>") == 0) return 6;
//    if (strcmp(token_buffer, "<\\progressbar>") == 0) return 7;
//    if (strcmp(token_buffer, "<\\frame>") == 0)   return ((int)8);
//    if (strcmp(token_buffer, "<table>") == 0) return 9;
//    if (strcmp(token_buffer, "<\\table>") == 0)   return ((int)10);
//    if (strcmp(token_buffer, "<label>") == 0)   return ((int)11);
//    if (strcmp(token_buffer, "<\\label>") == 0)   return ((int)12);
//    if (strcmp(token_buffer, "<textview>") == 0)   return ((int)13);
//    if (strcmp(token_buffer, "<\\textview>") == 0)   return ((int)14);
//    if (strcmp(token_buffer, "<zone de texte>") == 0)   return ((int)15);
//    if (strcmp(token_buffer, "<\\zone de texte>") == 0)   return ((int)16);
//    if (strcmp(token_buffer, "<combo>") == 0)   return ((int)17);
//    if (strcmp(token_buffer, "<\\combo>") == 0)   return ((int)18);
//
//    return ((int)0);
//}



int check_reserved()
{
    //printf("\n on verifie le mot : %s \n",token_buffer);
    if (strcmp(token_buffer, "<window>") == 0) return 1;
    if (strcmp(token_buffer, "<button>") == 0) return 2;
    if (strcmp(token_buffer, "<Checkbutton>") == 0)   return ((int)4);
    if (strcmp(token_buffer, "<\\window>") == 0) return 5;
    if (strcmp(token_buffer, "<\\button>") == 0) return 6;
    if (strcmp(token_buffer, "<\\Checkbutton>") == 0)   return ((int)8);
    if (strcmp(token_buffer, "<body>") == 0)   return ((int)9);
    if (strcmp(token_buffer, "<\\body>") == 0)   return ((int)10);
    if (strcmp(token_buffer, "<ButtonRadioGroupe>") == 0)   return ((int)11);
    if (strcmp(token_buffer, "<\\ButtonRadioGroupe>") == 0)   return ((int)12);
    if (strcmp(token_buffer, "<BarreMenu>") == 0)   return ((int)13);
    if (strcmp(token_buffer, "<\\BarreMenu>") == 0)   return ((int)14);
    if (strcmp(token_buffer, "<header>") == 0)   return ((int)15);
    if (strcmp(token_buffer, "<\\header>") == 0)   return ((int)16);
    if (strcmp(token_buffer, "<image>") == 0)   return ((int)17);
    if (strcmp(token_buffer, "<\\image>") == 0)   return ((int)18);
    if (strcmp(token_buffer, "<progressbar>") == 0) return 19;
    if (strcmp(token_buffer, "<frame>") == 0)   return ((int)20);
    if (strcmp(token_buffer, "<\\progressbar>") == 0) return 21;
    if (strcmp(token_buffer, "<\\frame>") == 0)   return ((int)22);
    if (strcmp(token_buffer, "<table>") == 0) return 23;
    if (strcmp(token_buffer, "<\\table>") == 0)   return ((int)24);
    if (strcmp(token_buffer, "<label>") == 0)   return ((int)25);
    if (strcmp(token_buffer, "<\\label>") == 0)   return ((int)26);
    if (strcmp(token_buffer, "<textview>") == 0)   return ((int)27);
    if (strcmp(token_buffer, "<\\textview>") == 0)   return ((int)28);
    if (strcmp(token_buffer, "<zonetxt>") == 0)   return ((int)29);
    if (strcmp(token_buffer, "<\\zonetxt>") == 0)   return ((int)30);
    if (strcmp(token_buffer, "<combo>") == 0)   return ((int)31);
    if (strcmp(token_buffer, "<\\combo>") == 0)   return ((int)32);
    if (strcmp(token_buffer, "<onglet>") == 0)   return ((int)33);
    if (strcmp(token_buffer, "<\\onglet>") == 0)   return ((int)34);
    if (strcmp(token_buffer, "<page>") == 0)   return ((int)35);
    if (strcmp(token_buffer, "<\\page>") == 0)   return ((int)36);
    if (strcmp(token_buffer, "<scale>") == 0)   return ((int)37);
    if (strcmp(token_buffer, "<\\scale>") == 0)   return ((int)38);
    return ((int)0);
}



void clear_buffer()
{
    //Effacer le tampon
    memset(token_buffer, 0, TOKEN_BUFFER_SIZE);
    i = 0;
}
Cellule* Depiler(Cellule* Pile)
{
    if (!Pile) (Cellule*)NULL;
    if (!Pile) return (Cellule*)NULL;
    Pile = Pile->suivant;
    return (Cellule*)Pile;
}
void traiter(char tab[20], char attribut[20], char valeur[20])
{
    int k = 0;
    int m = 0;
    while (tab[k] != ':')
    {
        attribut[m++] = tab[k++];
    }
    attribut[m] = '\0';
    m = 0;

    while (tab[k] != '\0')
    {
        valeur[m++] = tab[++k];
    }
    valeur[m] = '\0';
}
cellule_propriete* lire(FILE* fp_in, cellule_propriete* liste)
{
    // printf(" \n la fonction lire : \n");
    char c;
    char tab[40];
    char left[40]; char right[40];
    int j = 0;
    c = fgetc(fp_in);
    while (c != '<')
    {
        while (c != ':')
        {
            if (c != ' ' && c != '\t' && c != '\n')
            {
                tab[j] = c;
                j++;
            }
            c = fgetc(fp_in);
        }
        while (c != ';')
        {

            tab[j] = c;
            j++;

            c = fgetc(fp_in);
        }
        tab[j] = '\0';
        // printf("\nc a la fin de semi while: .%c.", c);
         //sÃ¯Â¿Â½parer
        traiter(tab, right, left);
        //printf("\n lue : %s \n", tab);
        //split_string(tab,':', right, left);
       // printf("\n right : .%s. ", right);
        //printf("\n left : .%s. ", left);

        liste = ajouter_propriete(liste, right, left);

        tab[0] = '\0';
        j = 0;
        // c = fgetc(fp_in);
        c = fgetc(fp_in);
        while (c == ' ' || c == '\t' || c == '\n')
        {
            c = fgetc(fp_in);
        }
        // printf("\nc a la fin de big while : .%c.", c);
    }
    ungetc(c, fp_in);
    return liste;
}


#endif //NEW_TABLE_FRAME_PROG_H