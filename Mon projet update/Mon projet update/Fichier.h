#include<stdio.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>
#include <ctype.h>
#include "en_commun.h"


void add_elem_to_widget(GtkWidget* fixed, GtkWidget* elem, gint x, gint y)
{
    gtk_fixed_put(GTK_FIXED(fixed), elem, x, y);
}

typedef struct cellule_window
{
    fenetre var;
    struct cellule_window* suivant;
}cellule_window;

cellule_window* ajouter_window(cellule_window* liste, fenetre wn)
{
    cellule_window* NE = g_new(cellule_window, 1);
    NE->var = wn;
    NE->suivant = NULL;


    if (!liste) return (cellule_window*)NE;
    cellule_window* tmp = liste;
    while (tmp->suivant)
        tmp = tmp->suivant;
    //ajout
    tmp->suivant = NE;

    return (cellule_window*)liste;
}

cellule_window* scanner()
{
    cellule_window* windows = NULL;
    fenetre window;
    GtkWidget* vbox = NULL, * fix = NULL, * header = NULL;
    ToogleButton* Checkbutton = NULL, * RadioButton = NULL, * scrolled_window = NULL;
    ButtonItem* button = NULL;
    Cellule* pile = NULL;
    image* im = NULL;
    zonetxt_object* zn = NULL;
    TextView_object* tv = NULL;
    Combo_box_object* cmb = NULL;
    label_object* lb = NULL;
    ProgressBar_object* p_bar = NULL;
    Frame_object* frame = NULL;
    Scale_object* scale = NULL;
    //Table_object * table=NULL;
    FILE* fp_in = NULL;
    cellule_propriete* listew = NULL;
    int etat;
    GList* group = NULL, * group2 = NULL, * group3 = NULL, * group4 = NULL;
    fix = gtk_fixed_new();
    char* fileSource = "Texte.txt";
    int c, res;

    fp_in = fopen(fileSource, "r");

    if (fp_in == NULL)
    {
        printf("Erreur: impossible d'ouvrir le fichier d'entree.\n");
    }
    while ((c = fgetc(fp_in)) != EOF)
    {
        if (isalpha(c) || c == '<')
        {
            while (isalnum(c) || c == '<' || c == '>' || c == '\\')
            {
                token_buffer[i] = (char)c;
                i++;
                if (c == '>')
                    break;
                c = fgetc(fp_in);
            }
            ungetc(c, fp_in);
            res = check_reserved();
            clear_buffer();
            switch (res)
            {
            case 1:
                //initialiser les valeurs de la fenetre
                window = initialiser_valeurs_fenetre();
                c = fgetc(fp_in);
                listew = NULL;
                listew = lire(fp_in, listew); //lecture des attributs depuis le fichier
                set_propriety_fenetre(&window, listew);//changements des attributs
                ajouter_fenetre(&window);
                //creation de scroll bar
                scrolled_window = gtk_scrolled_window_new(NULL, NULL);
                //format de scroll bar selon la valeur d'attribut scroll
                add_scroll_bar(&scrolled_window, window.scroll);
                //ajouter scroll bar a la fenetre
                gtk_container_add(GTK_CONTAINER(window.window), scrolled_window);
                //empiler scroll bar dans la pile
                pile = Empiler(pile, scrolled_window, "window");
                // ajouter fenetre dans la liste des fenetres 
                windows = ajouter_window(windows, window);
                break;


            case 2:
                //initialiser un button
                button = init_button();
                c = fgetc(fp_in);
                //une liste pour contenir les propri�tes de button
                cellule_propriete* liste3 = NULL;
                //lire les propriet�s 
                liste3 = lire(fp_in, liste3);
                //affecation des propriet�s
                button = set_propriety_ButtonItem(button, liste3);
                //on cr�e le button en utilisant cette liste 
                button = cree_Button(button);
                //ajouter le button � l'objet conteneur
                add_elem_to_widget(pile->cell->info, button->widget, button->positionnement.posx, button->positionnement.posy);
                //ajouter les signales pour les buttons radio , chekcbutton , zone de text, scale 
                if (strcmp(button->signal, "on_button_signal") == 0)
                {
                    g_signal_connect(button->widget, "clicked", G_CALLBACK(on_button_signal), group);
                }
                else if (strcmp(button->signal, "on_button_clicked2") == 0)
                {

                    g_signal_connect(button->widget, "clicked", G_CALLBACK(on_button_clicked2), group2);
                }
                else if (strcmp(button->signal, "on_button_clicked3") == 0)
                {
                    g_signal_connect(button->widget, "clicked", G_CALLBACK(on_button_clicked3), group3);
                }
                else if (strcmp(button->signal, "onbuttontxtview") == 0)
                {
                    g_signal_connect(button->widget, "clicked", G_CALLBACK(onbuttontxtview), tv->textview);
                }
                else if (strcmp(button->signal, "add_element") == 0)
                {
                    g_signal_connect(button->widget, "clicked", G_CALLBACK(add_element), cmb);
                }
                else if (strcmp(button->signal, "on_button_combo") == 0)
                {
                    g_signal_connect(button->widget, "clicked", G_CALLBACK(on_button_combo), group4);
                }
                else if (strcmp(button->signal, "remove_element") == 0)
                {
                    g_signal_connect(button->widget, "clicked", G_CALLBACK(remove_element), cmb);
                }
                else if (strcmp(button->signal, "on_button_scale") == 0)
                {
                    g_signal_connect(button->widget, "clicked", G_CALLBACK(on_button_scale), scale->scale);
                }
                else if (strcmp(button->signal, "on_button") == 0)
                {
                    g_signal_connect(button->widget, "clicked", G_CALLBACK(on_button_signal), group);
                    g_signal_connect(button->widget, "clicked", G_CALLBACK(on_button_clicked2), group2);
                    g_signal_connect(button->widget, "clicked", G_CALLBACK(on_button_clicked3), group3);
                    g_signal_connect(button->widget, "clicked", G_CALLBACK(onbuttontxtview), tv->textview);

                    g_signal_connect(button->widget, "clicked", G_CALLBACK(on_button_combo), group4);
                    g_signal_connect(button->widget, "clicked", G_CALLBACK(on_button_scale), scale->scale);
                }
                else if (strcmp(button->signal, "close") == 0)
                {

                    cellule_window* windows2 = windows;

                    while (windows2->suivant != NULL)
                    {
                        // afficher_fenetre(&windows->var);
                        windows2 = windows2->suivant;
                    }

                    g_signal_connect(button->widget, "clicked", G_CALLBACK(close), windows2->var.window);
                }

                break;
            case 4:
                //initialiser le button checkbutton
                Checkbutton = init_Button_checkBox();
                c = fgetc(fp_in);
                //initialiser la liste des attributs
                cellule_propriete* liste = NULL;
                //lire les attributs de la liste 
                liste = lire(fp_in, liste);
                //ajouter les attibuts � la liste 
                Checkbutton = set_propriety(Checkbutton, liste);
                //cr�e le button checkbutton
                Checkbutton = create_Button_checkBox(Checkbutton);
                //ajouter le button au conteneur 
                add_elem_to_widget(pile->cell->info, Checkbutton->widget, Checkbutton->positionnement.posx, Checkbutton->positionnement.posy);
                //ajouter le button � la liste qui va etre utiliser pour r�cup�rer les buttons coch�s
                group3 = g_list_append(group3, Checkbutton);
                break;

            case 5:  pile = Depiler(pile); break; //depiler la pile
            case 6: break;
            case 8: break;
            case 9: vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
                gtk_container_add(GTK_CONTAINER(pile->cell->info), vbox);
                GtkWidget* fix2 = gtk_fixed_new();
                gtk_container_add(GTK_CONTAINER(vbox), fix2);
                pile = Empiler(pile, fix2, "box");
                break;

            case 10: pile = Depiler(pile); //depiler la pile
                break;
            case 11:
            {
                //on a une balise button radio 
                char buffer[255];
                GtkWidget* pere = NULL;
                int tmp;
                fscanf(fp_in, "%s\n", buffer);
                //tant que n'est encore dans le meme button radio group 
                ToogleButton* bouttonpere = NULL;
                while (strcmp(buffer, "<\\ButtonRadioGroupe>") != 0)
                {
                    if (strcmp(buffer, "<ButtonRadio>") == 0)
                    {
                        //on cr�e le premiere button radio 
                        RadioButton = init_radio_button();
                        //on cr�e la liste des attributs 
                        cellule_propriete* liste2 = NULL;
                        //lire les attributs du fichier
                        liste2 = lire(fp_in, liste2);
                        //affectation
                        RadioButton = set_propriety_RadioButtonItem(RadioButton, liste2, &tmp);
                        if (tmp == 1)
                        {
                            /*si ce button s'agit d'un button pere qui represente le group
                            on cr�e le button est on l'affecte au button radio */
                            RadioButton = cree_radio_button(RadioButton);
                            pere = RadioButton->widget;
                            RadioButton->positionnement.container = pile->cell->info;
                            add_elem_to_widget(pile->cell->info, RadioButton->widget, RadioButton->positionnement.posx, RadioButton->positionnement.posy);
                            //ajouter dans la liste pour r�cupere le button radio coch� 
                            group2 = g_list_append(group2, RadioButton->widget);
                            //printf(" \n Le bouton radio '%s' est s�lectionn�\n", gtk_button_get_label(GTK_RADIO_BUTTON(RadioButton->widget)));
                        }
                        else if (tmp == 0)
                        {
                            //si le button s'agit un button qui doit �tre dans un group du button p�re
                            RadioButton->ButtonPere = pere;
                            RadioButton = cree_radio_button(RadioButton);
                            RadioButton->positionnement.container = pile->cell->info;
                            add_elem_to_widget(pile->cell->info, RadioButton->widget, RadioButton->positionnement.posx, RadioButton->positionnement.posy);
                            //ajouter dans la liste pour r�cupere le button radio coch� 
                            //group2 = g_list_append(group2, RadioButton);
                        }
                        fscanf(fp_in, "%s\n", buffer);

                    }
                    //group2 = g_list_append(group2, RadioButton->widget);
                    fscanf(fp_in, "%s\n", buffer);
                }

                //group2 = g_list_append(group2, RadioButton);
               // group2 = g_list_append(group2, RadioButton->widget);
                break;
            }
            case 12: break;
            case 13:
            {
                char buffer[255];
                int tmp;
                //initialisation de la barre menu 
                Menu_Gtk* MenuPrincipale = init_menu();
                c = fgetc(fp_in);
                //initialisation de la liste des attributs 
                cellule_propriete* listeA = NULL;
                listeA = lire(fp_in, listeA);
                //on applique les attributs du fichier sur la structure 
                MenuPrincipale = set_propriety_Menu(MenuPrincipale, listeA);
                //on cr�e le menu 
                MenuPrincipale = cree_menu(MenuPrincipale);
                MenuPrincipale->position.container = pile->cell->info;
                //on ajoute le menu au conteneur qui lui correspond 
                add_elem_to_widget(pile->cell->info, MenuPrincipale->Barre_menu, MenuPrincipale->position.posx, MenuPrincipale->position.posy);
                fscanf(fp_in, "%s\n", buffer);
                while (strcmp(buffer, "<\\BarreMenu>") != 0)
                {
                    //on trouve un �lement du menu 
                    if (strcmp(buffer, "<item>") == 0)
                    {
                        Item_menu* nv_item = init_item(); //on initialise un menu item
                        cellule_propriete* liste4 = NULL;
                        liste4 = lire(fp_in, liste4); //extraction des attributs
                        nv_item = set_propriety_itemMenu(nv_item, liste4);
                        nv_item = cree_item(nv_item); //la cr�ation de menu item
                        MenuPrincipale = add_item(MenuPrincipale, nv_item);
                        fscanf(fp_in, "%s\n", buffer);
                        //si le menu contient un sous menu en fait appele � une fonction qui va traiter ce cas r�cursivement 
                        if (strcmp(buffer, "<subMenu>") == 0) traiter_subMenu(nv_item, fp_in);
                    }
                    fscanf(fp_in, "%s\n", buffer);
                }
                break;
            }
            case 14: break;
            case 15:
                //creation de header 
                header = create_header(&window, 1);
                GtkWidget* fixed_header = gtk_fixed_new();
                //ajouter fixedau header
                gtk_container_add(GTK_CONTAINER(header), fixed_header);
                //ajouter header a l'objet de la sommet de la pile
                add_elem_to_widget(pile->cell->info, header, 5, 5);
                //empiler header 
                pile = Empiler(pile, fixed_header, "header");
                break;

            case 16: pile = Depiler(pile); break; // depiler la pile
            case 17:
                //initialiser les valeurs de l'image
                im = initialiser_valeurs_image();
                c = fgetc(fp_in);
                liste = NULL;
                //lecture des attributs depuis le fichier 
                liste = lire(fp_in, liste);
                //changements des attributs
                im = set_propriety_image(im, liste);
                //ajouter l'image a l'objet de la sommet de la pile
                add_image(im, pile->cell->info);
                break;

            case 18: break;
            case 19:   p_bar = init_prog_bar_default(); //initialisation du progress bar
                p_bar->commune.container = pile->cell->info; //affectation du contenaire
                c = fgetc(fp_in);
                liste = NULL; //initialiser la liste
                liste = lire(fp_in, liste); //lecture des attributs depuis le fichier
                p_bar = set_propriety_prog(p_bar, liste, &etat); //changements des attributs
                p_bar = create_progress_bar(p_bar); //creation de l'objet
                //ajouter l'objet dans le sommet de la pile (son contenaire)
                add_elem_to_widget(pile->cell->info, p_bar->progressbar, p_bar->commune.posx, p_bar->commune.posy);
                if (p_bar->etat == 1) un_seul_parcours(p_bar, p_bar->progress);
                if (p_bar->etat == 2) transaction(p_bar);
                if (p_bar->etat == 3) deplacement(p_bar);
                break;
            case 20:
                frame = init_frame_default(); //initialisation du frame
                frame->commune.container = pile->cell->info; //affectation du contenaire
                c = fgetc(fp_in);
                liste = NULL; //initialiser la liste
                liste = lire(fp_in, liste); //lecture des attributs depuis le fichier
                frame = set_propriety_frame(frame, liste); //changements des attributs
                frame = create_frame(frame); //creation de l'objet
                //fixer le frame dans son contenaire
                add_elem_to_widget(pile->cell->info, frame->frame, frame->commune.posx, frame->commune.posy);
                //creer un fixed et l'empiler - c'est là ou on va mettre le contenu du frame
                GtkWidget* fix3 = gtk_fixed_new();
                gtk_container_add(GTK_CONTAINER(frame->frame), fix3);
                pile = Empiler(pile, fix3, "frame");
                break;
            case 21: break;
            case 22:  pile = Depiler(pile); break;//depiler la pile
            case 23:
                //table = init_table_default(); //initialisation du scale
                //table->commune.container=pile->cell->info; //affectation du contenaire
                //c = fgetc(fp_in);
                //liste=NULL;
                //liste = lire(fp_in,liste); //lescture des attributs
                //table = set_propriety_table(table, liste); //changemant des proprietes
                //table= create_table(table); //creation de l'objet
                // //ajouter la table dans son contenaire
                //add_elem_to_widget(pile->cell->info, table->table, table->x, table->y);
                //pile = Empiler(pile, table->table, "table");
                //}

                break;
            case 24://pile = Depiler(pile);
                break;
            case 25:
            {
                Format frm = init_format();
                //initialise le label
                lb = initLabelObject();
                lb->lab = frm;
                //configure la position du label en la plaçant dans le conteneur de la cellule de la pile
                lb->position.container = pile->cell->info;
                // lire le prochain caractère du flux d'entrée
                c = fgetc(fp_in);
                liste = NULL;
                liste = lire(fp_in, liste);
                //configure les propriétés du label
                lb = set_proprietylabel(lb, liste);
                //crée le label
                lb = createLabelObject(lb);
                break;
            }
            case 26: break;
            case 27:
                //initialise la zone de texte multiligne
                tv = init_text_view();
                //configure la position de la zone de texte multiligne en la plaçant dans le conteneur de la cellule de la pile
                tv->position.container = pile->cell->info;
                // lire le prochain caractère du flux d'entrée
                c = fgetc(fp_in);
                liste = NULL;
                liste = lire(fp_in, liste);
                //configure les propriétés de la zone de texte multiligne
                tv = set_proprietyview(tv, liste);
                //crée la zone de texte multiligne
                tv = create_text_view(tv);
                break;
            case 28: break;
            case 29:
                //initialise la zone de texte
                zn = zonetxt_init();
                // lire le prochain caractère du flux d'entrée
                c = fgetc(fp_in);
                liste = NULL;
                liste = lire(fp_in, liste);
                //configure les propriétés de la zone de texte
                zn = set_proprietyzone(zn, liste);
                //configure la position de la zone de texte en la plaçant dans le conteneur de la cellule de la pile
                zn->position.container = pile->cell->info;
                //crée la zone de texte
                zn = zonetxt_create(zn);
                //ajoute la zone de texte à la liste de widgets
                group = g_list_append(group, zn);
                break;

            case 30: break;
            case 31:
                //initialise la zone de liste déroulante ComboBox
                cmb = init_combo_box();
                //configure la position de la ComboBox en la plaçant dans le conteneur
                cmb->position.container = pile->cell->info;
                //lire le prochain caractère du flux d'entrée
                c = fgetc(fp_in);
                liste = NULL;
                liste = lire(fp_in, liste);
                // configurer les propriétés de la ComboBox
                cmb = set_proprietycombo(cmb, liste);
                // crée la ComboBox
                cmb = create_combo_box(cmb);
                //ajoute la ComboBox à la liste de widgets
                group4 = g_list_append(group4, cmb);
                break;
            case 32:  break;
            case 33: {
                //creation d'un onglet
                GtkWidget* notebook = gtk_notebook_new();
                //ajouter l'onglet a l'objet de la sommet de la pile
                gtk_container_add(GTK_CONTAINER(pile->cell->info), notebook);
                //empiler onglet dans la pile
                pile = Empiler(pile, notebook, "note");
                break;
            }
            case 34:  pile = Depiler(pile); break; //depiler la pile

            case 35: {
                //ajouter un fixed
                GtkWidget* vbox6 = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
                GtkWidget* fix6 = gtk_fixed_new();
                gtk_container_add(GTK_CONTAINER(vbox6), fix6);
                c = fgetc(fp_in);
                liste = NULL;
                liste = lire(fp_in, liste);
                if (liste != NULL)
                {   //ajouter le nom de la page
                    if (strcmp(liste->attribut, "label") == 0)
                    {   //ajouter fixeda la page avec le nom
                        add_onglet(pile->cell->info, vbox6, gtk_label_new(liste->valeur));
                    }
                    liste = liste->suivant;
                }
                //empiler la page dans la pile
                pile = Empiler(pile, fix6, "box");
                break;
            }
            case 36:pile = Depiler(pile); break;
            case 37:scale = init_default_scale(); //initialisation du scale
                scale->commune.container = pile->cell->info; //affectation du contenaire
                c = fgetc(fp_in);
                liste = NULL; //initialiser la liste
                liste = lire(fp_in, liste); //lecture des attributs depuis le fichier
                scale = set_propriety_scale(scale, liste); //changements des attributs
                scale = create_scale(scale); //creation de l'ojet
                //ajouter le scale dans le sommet de la pile (son contenaire)
                gtk_fixed_put(GTK_FIXED(pile->cell->info), scale->scale, scale->commune.posx, scale->commune.posy);
                break;
            case 38: break;
            default: break;
            }
        }
    }//fin de while
    fclose(fp_in);
    return windows;
}

//int main(int argc, char* argv[])
//{
//    gtk_init(&argc, &argv);
//    GtkWidget* window = scanner();
//
//    gtk_widget_show_all(window);
//    gtk_main();
//
//    return 0;
//}