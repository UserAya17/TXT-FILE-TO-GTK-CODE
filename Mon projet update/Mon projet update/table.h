#pragma once
#include "en_commun.h"
#ifndef GTK_ELLIPSIZE_END
#define GTK_ELLIPSIZE_END 3
#endif

typedef struct
{
    char style[30];
    char family[30]; //sans-serif arial calibri verdana timesnewroman..
    int size; //longueur
    char weight[30]; //taille des caracteres 
    char color[30];
    char bgcolor[30];
    char underline[30];//single low double
    char underline_color[30];
    char barrer_txt[6];//true false
    char color_bar[30];
    int select;//true false
    int alignement;//left,right,center,fill
} Format;


typedef struct
{
    GtkWidget* label;
    commune position;
    char text[100];
    int width;
    int height;
    Format lab;
} label_object;
/*background-color: inherit;
background-color: initial;
background-color: revert;
background-color: revert-layer;
background-color: unset;*/

Format init_format()
{
    Format format;
    strcpy(format.style, "normal");
    strcpy(format.family, "arial");
    format.size = 12;
    strcpy(format.weight, "normal");
    strcpy(format.color, "black");
    strcpy(format.bgcolor, "none");
    strcpy(format.underline, "none");
    strcpy(format.underline_color, "white");
    strcpy(format.barrer_txt, "false");
    strcpy(format.color_bar, "black");
    format.select = 0;
    format.alignement = 2;
    return format;
}





label_object* initLabelObject()
{
    label_object* obj = NULL;
    //Allocation memoire
    obj = (label_object*)malloc(sizeof(label_object));
    //test d'allocation
    if (!obj)
    {
        printf("Probl�me d'allocation\n");
        exit(-1);
    }
    //Allocation du pointeur titre
    //obj->text = (char*)malloc(500 * sizeof(char));

    //Affectation des champs
    obj->label = NULL;
    obj->position.posx = 0;
    obj->position.posy = 0;
    obj->height = 50;
    obj->width = 50;
    strcpy(obj->text, "");

    return ((label_object*)obj);
}




label_object* createLabelObject(label_object* obj)
{
    // Cr�ation du label avec le texte sp�cifi�
    obj->label = gtk_label_new(NULL);


    gtk_label_set_text(GTK_LABEL(obj->label), obj->text);


    // Utiliser la fonction g_strdup_printf pour formater la cha�ne de caract�res 
    char* markup;
    if (strcmp(obj->lab.bgcolor, "none") != 0)  markup = g_strdup_printf("<span font='%s %d' style='%s'  weight='%s'  background='%s' color='%s' underline='%s' underline_color='%s' strikethrough='%s' strikethrough_color='%s'>%s</span>", obj->lab.family, obj->lab.size, obj->lab.style, obj->lab.weight, obj->lab.bgcolor, obj->lab.color, obj->lab.underline, obj->lab.underline_color, obj->lab.barrer_txt, obj->lab.color_bar, obj->text);
    else markup = g_strdup_printf("<span font='%s %d' style='%s'  weight='%s' color='%s' underline='%s' underline_color='%s' strikethrough='%s' strikethrough_color='%s'>%s</span>", obj->lab.family, obj->lab.size, obj->lab.style, obj->lab.weight, obj->lab.color, obj->lab.underline, obj->lab.underline_color, obj->lab.barrer_txt, obj->lab.color_bar, obj->text);
    //convertir le texte en utf8
    markup = g_locale_to_utf8(markup, -1, NULL, NULL, NULL);

    // Utiliser la fonction gtk_label_set_markup pour d�finir le texte du label avec le texte format�
    gtk_label_set_markup(GTK_LABEL(obj->label), markup);

    // Ne pas oublier de lib�rer la m�moire allou�e pour markup
    g_free(markup);



    // taille minimale en fonction du contenu
    gtk_widget_set_size_request(obj->label, obj->width, obj->height);

    // positionne le label en (x,y)
    gtk_fixed_put(GTK_FIXED(obj->position.container), obj->label, obj->position.posx, obj->position.posy);

    // D�finition de l'alignement du texte dans le label
    switch (obj->lab.alignement)
    {
    case 0: gtk_label_set_justify(GTK_LABEL(obj->label), GTK_ALIGN_START); break;
    case 1: gtk_label_set_justify(GTK_LABEL(obj->label), GTK_ALIGN_END); break;
    case 2: gtk_label_set_justify(GTK_LABEL(obj->label), GTK_ALIGN_CENTER); break;
    case 3: gtk_label_set_justify(GTK_LABEL(obj->label), GTK_ALIGN_CENTER); break;
    }

    switch (obj->lab.select)
    {
    case 0: gtk_label_set_selectable(GTK_LABEL(obj->label), FALSE); break;
    case 1: gtk_label_set_selectable(GTK_LABEL(obj->label), TRUE); break;
    }

    // D�finition du mode de troncature du texte
    gtk_label_set_ellipsize(GTK_LABEL(obj->label), GTK_ELLIPSIZE_END);

    // Affichage du conteneur et de son contenu
    gtk_widget_show_all(obj->position.container);

    return ((label_object*)obj);
}

label_object* set_proprietylabel(label_object* cb, cellule_propriete* liste)
{
    while (liste != NULL)
    {
        if (strcmp(liste->attribut, "x") == 0)  cb->position.posx = atoi(liste->valeur);

        if (strcmp(liste->attribut, "y") == 0)  cb->position.posy = atoi(liste->valeur);

        if (strcmp(liste->attribut, "width") == 0)   cb->width = atoi(liste->valeur);

        if (strcmp(liste->attribut, "height") == 0) cb->height = atoi(liste->valeur);

        if (strcmp(liste->attribut, "text") == 0) strcpy(cb->text, liste->valeur); // copier l'�l�ment dans le tableau

        if (strcmp(liste->attribut, "color") == 0)  strcpy(cb->lab.color, liste->valeur); // copier l'�l�ment dans le tableau

        if (strcmp(liste->attribut, "bgcolor") == 0) strcpy(cb->lab.bgcolor, liste->valeur); // copier l'�l�ment dans le tableau

        if (strcmp(liste->attribut, "alignement") == 0)  cb->lab.alignement = atoi(liste->valeur);

        if (strcmp(liste->attribut, "barrer") == 0)
        {
            //printf("barrer=%s", liste->valeur);
            if (strcmp(liste->valeur, "true") == 0)
            {
                cb->lab.barrer_txt[0] = 't';
                cb->lab.barrer_txt[1] = 'r';
                cb->lab.barrer_txt[2] = 'u';
                cb->lab.barrer_txt[3] = 'e';
                cb->lab.barrer_txt[4] = '\0';
                //strcpy(cb->lab.barrer_txt , TRUE);
            }
            //else if (strcmp(liste->valeur, "false") == 0) strcpy(cb->lab.barrer_txt , FALSE);
        }
        if (strcmp(liste->attribut, "colorBar") == 0) strcpy(cb->lab.color_bar, liste->valeur); // copier l'�l�ment dans le tableau

        if (strcmp(liste->attribut, "police") == 0) strcpy(cb->lab.family, liste->valeur); // copier l'�l�ment dans le tableau

        if (strcmp(liste->attribut, "style") == 0)  strcpy(cb->lab.style, liste->valeur); // copier l'�l�ment dans le tableau

        if (strcmp(liste->attribut, "selection") == 0)  cb->lab.select = atoi(liste->valeur);

        if (strcmp(liste->attribut, "souligner") == 0) strcpy(cb->lab.underline, liste->valeur); // copier l'�l�ment dans le tableau

        if (strcmp(liste->attribut, "taille") == 0)  cb->lab.size = atoi(liste->valeur);

        if (strcmp(liste->attribut, "weight") == 0) strcpy(cb->lab.weight, liste->valeur); // copier l'�l�ment dans le tableau

        if (strcmp(liste->attribut, "ColorLigne") == 0)  strcpy(cb->lab.underline_color, liste->valeur); // copier l'�l�ment dans le tablea

        liste = liste->suivant;
    }
    return cb;
}