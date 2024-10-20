#include <gtk/gtk.h>
#include <stdio.h>
#include "Fenetre.h"
#include "Box.h"
#include "RadioButton.h"
#include "CheckButton.h"
#include "SimpleButton.h"
#include "zonedetexte.h"
#include "Image.h"
#include "combobox.h"
#include "textView.h"
#include "label.h"
#include "frame.h"
#include "prog_bar.h"
//#include "table.h"
#include "scale.h"
#include "Menu.h"
#include "Fichier.h"





int main(int argc, char* argv[])
{
    gtk_init(&argc, &argv);

    cellule_window* windows = scanner();

    while (windows != NULL)
    {
        afficher_fenetre(&windows->var);
        // printf("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ dans main id %d", windows->var.id);

        windows = windows->suivant;
    }

    gtk_main();
    return 0;
}

//void show_dialog(GtkWidget* parent)
//{
//	GtkWidget* dialog;
//
//	// Cr�er une nouvelle bo�te de dialogue
//	dialog = gtk_message_dialog_new(
//		GTK_WINDOW(parent),
//		GTK_DIALOG_DESTROY_WITH_PARENT,
//		GTK_MESSAGE_INFO,
//		GTK_BUTTONS_CLOSE,
//		"Ceci est une bo�te de dialogue GTK3 en C."
//	);
//
//	// Afficher la bo�te de dialogue
//	gtk_dialog_run(GTK_DIALOG(dialog));
//
//	// D�truire la bo�te de dialogue
//	gtk_widget_destroy(dialog);
//}
//
//
//void on_button_clicked(GtkWidget* widget, gpointer data)
//{
//	show_dialog(GTK_WIDGET(data));
//}
//
//int main(int argc, char* argv[])
//{
//	GtkWidget* window;
//	GtkWidget* button;
//
//	// Initialiser GTK
//	gtk_init(&argc, &argv);
//
//	// Cr�er une fen�tre
//	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
//	gtk_window_set_title(GTK_WINDOW(window), "Ma fen�tre");
//
//	// Cr�er un bouton
//	button = gtk_button_new_with_label("Afficher la bo�te de dialogue");
//	gtk_container_add(GTK_CONTAINER(window), button);
//
//	// Connecter l'�v�nement de clic � la fonction de la bo�te de dialogue
//	g_signal_connect(button, "clicked", G_CALLBACK(on_button_clicked), window);
//
//	// Afficher la fen�tre
//	gtk_widget_show_all(window);
//
//	// Lancer la boucle principale GTK
//	gtk_main();
//
//	return 0;
//}
 