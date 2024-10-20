#pragma once
#include<stdio.h>
#include <gtk/gtk.h>

typedef struct Item_menu {
	GtkWidget* item_menu;
	char* label;
	char* icon;
	GtkWidget* sous_menu;
	struct Item_menu* fils;
	struct Item_menu* frere;
}Item_menu;

typedef struct Menu
{
	GtkWidget* Barre_menu;
	struct Item_menu* Elements;
	int direction;
	commune position;
}Menu_Gtk;

Item_menu* init_item()
{
	Item_menu* item_Init = (Item_menu*)malloc(sizeof(Item_menu));
	item_Init->fils = NULL;
	item_Init->frere = NULL;
	item_Init->item_menu = NULL;
	item_Init->label = "";
	item_Init->icon = NULL;
	return item_Init;
}

Item_menu* cree_item(Item_menu* Data)
{
	//Item_menu* item1 = (Item_menu*)malloc(sizeof(Item_menu));
	Data->item_menu = gtk_menu_item_new();
	//Data->item_menu = gtk_menu_item_new_with_label(Data->label);
	GtkWidget* box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 6);
	GtkWidget* icon2 = gtk_image_new_from_icon_name(Data->icon, GTK_ICON_SIZE_MENU);
	GtkWidget* label = gtk_label_new(Data->label);
	gtk_label_set_mnemonic_widget(GTK_LABEL(label), Data->item_menu);
	gtk_label_set_use_underline(GTK_LABEL(label), TRUE);

	gtk_container_add(GTK_CONTAINER(box), icon2);
	gtk_container_add(GTK_CONTAINER(box), label);

	gtk_container_add(GTK_CONTAINER(Data->item_menu), box);
	return Data;
}

Menu_Gtk* init_menu()
{
	Menu_Gtk* menu = (Menu_Gtk*)malloc(sizeof(Menu_Gtk));
	menu->Elements = init_item();
	menu->direction = 1;
	menu->position.container = NULL;
	menu->position.posx = 0;
	menu->position.posy = 0;
	return menu;
}
Menu_Gtk* cree_menu(Menu_Gtk* Data)
{
	//barre menu
	Data->Barre_menu = gtk_menu_bar_new();
	switch (Data->direction)
	{
	case 1: gtk_menu_bar_set_pack_direction(Data->Barre_menu, GTK_PACK_DIRECTION_LTR); break;
	case 2: gtk_menu_bar_set_pack_direction(Data->Barre_menu, GTK_PACK_DIRECTION_RTL); break;
	case 3: gtk_menu_bar_set_pack_direction(Data->Barre_menu, GTK_PACK_DIRECTION_TTB); break;
	}
	return Data;
}

Menu_Gtk* add_item(Menu_Gtk* Data, Item_menu* item1)
{
	if (Data->Elements->item_menu == NULL)
	{
		Data->Elements = item1;
		gtk_menu_shell_append(GTK_MENU_SHELL(Data->Barre_menu), item1->item_menu);
	}
	else
	{
		Item_menu* item_tmp = Data->Elements;
		while (item_tmp->frere != NULL)
		{
			item_tmp = item_tmp->frere;
		}
		item_tmp->frere = item1;
		gtk_menu_shell_append(GTK_MENU_SHELL(Data->Barre_menu), item1->item_menu);
	}

	return Data;
}

Item_menu* set_propriety_itemMenu(Item_menu* itemMenu, cellule_propriete* liste)
{
	while (liste != NULL)
	{
		if (strcmp(liste->attribut, "label") == 0)
		{
			itemMenu->label = liste->valeur;
		}
		if (strcmp(liste->attribut, "icon") == 0)
		{
			itemMenu->label = liste->valeur;
		}
		liste = liste->suivant;
	}
	return itemMenu;
}

Item_menu* add_sousMenu(Item_menu* Data, Item_menu* item1)
{
	//GtkWidget* sous_menu = gtk_menu_new();

	if (Data->fils == NULL)
	{
		//Data->Elements->sous_menu = gtk_menu_new();
		Data->fils = item1;
		gtk_menu_shell_append(GTK_MENU_SHELL(Data->sous_menu), item1->item_menu);
	}
	else
	{
		Item_menu* item_tmp = Data->fils;
		while (item_tmp->frere != NULL)
		{
			item_tmp = item_tmp->frere;
		}
		item_tmp->frere = item1;
		gtk_menu_shell_append(GTK_MENU_SHELL(Data->sous_menu), item1->item_menu);
	}
	return Data;
}

void traiter_subMenu(Item_menu* owner, FILE* fp_in)
{
	char buffer[255];
	Item_menu* nv_item_SousMenu = NULL;
	//printf(" \n sous menu \n");
	GtkWidget* sous_menu = gtk_menu_new();
	owner->sous_menu = sous_menu;
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(owner->item_menu), sous_menu);
	fscanf(fp_in, "%s\n", buffer);
	//printf("\n  after %s\n", buffer);

	while (strcmp(buffer, "<\\subMenu>") != 0)
	{
		if (strcmp(buffer, "<item>") == 0)
		{
			nv_item_SousMenu = init_item();
			cellule_propriete* liste5 = NULL;
			liste5 = lire(fp_in, liste5);
			nv_item_SousMenu = set_propriety_itemMenu(nv_item_SousMenu, liste5);
			nv_item_SousMenu = cree_item(nv_item_SousMenu);
			//gtk_menu_shell_append(GTK_MENU_SHELL(sous_menu), nv_item_SousMenu->item_menu);
			owner = add_sousMenu(owner, nv_item_SousMenu);
			fscanf(fp_in, "%s\n", buffer);
		}
		if (strcmp(buffer, "<subMenu>") == 0)
		{
			traiter_subMenu(nv_item_SousMenu, fp_in);
		}
		fscanf(fp_in, "%s\n", buffer);
	}
	return owner;
}

Menu_Gtk* set_propriety_Menu(Menu_Gtk* MenuPrincipale, cellule_propriete* liste)
{
	while (liste != NULL)
	{
		if (strcmp(liste->attribut, "direction") == 0)
		{
			MenuPrincipale->direction = atoi(liste->valeur);
		}
		if (strcmp(liste->attribut, "x") == 0)
		{
			MenuPrincipale->position.posx = atoi(liste->valeur);
		}
		if (strcmp(liste->attribut, "y") == 0)
		{
			MenuPrincipale->position.posy = atoi(liste->valeur);
		}
		liste = liste->suivant;
	}
	return MenuPrincipale;
}