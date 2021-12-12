#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h>
#include <stdlib.h>
#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include "menu.h"
#include <string.h>
#include <time.h>

#include <stdio.h>


/////////////////    AJOUTER    //////////////
void ajouter_nb(nutri A)
{
    FILE *F=NULL;

F=fopen("menu.txt","a");
if(F!=NULL)
{

    fprintf(F,"%s %s %s %s %s %d %s %s \n",A.id,A.type,A.plat,A.ing,A. date,A.nb,A.groupetr,A.modetr);// on va les saisir ds literface ajouter
    fclose(F);
    

}

}
/////////////////// SUPPRIMER   ////////////
void supp_nb(char id[])
{
  
   FILE *F, *FW;
  nutri D ;
  
F = fopen ("menu.txt", "r");
FW = fopen ("tr.txt", "w");

  if ((F!=NULL)&&(FW!=NULL))
 {


  while (fscanf (F, "%s %s %s %s %s %d %s %s",D.id,D.type,D.plat,D.ing,D. date,&D.nb,D.groupetr,D.modetr) == 8)//8 le nbr des attributs / ou bien on ecrit !=EOF
    if (strcmp (D.id, id) != 0)// id que jai ectrit au niveau de entry et D.id cest au niveau du fichier 
      fprintf (FW, "%s %s %s %s %s %d %s %s \n", D.id,D.type,D.plat,D.ing,D. date,D.nb,D.groupetr,D.modetr);// il va l faire qd ils sont #
}
  fclose (F);
  fclose (FW);
remove("menu.txt");
rename("tr.txt", "menu.txt");




}
//////////////  RECHERCHER    ///////////////
nutri rech_nb(char id[])
{
char ch;// on l'a pas utuliser
FILE *F;
  nutri Q;
  nutri A;
  
F = fopen ("menu.txt", "r");


  if (F!=NULL)// il existe
{
  while (fscanf (F, "%s %s %s %s %s %d %s %s", Q.id,Q.type,Q.plat,Q.ing,Q. date, &Q.nb,Q.groupetr,Q.modetr) != EOF)// il va continer a lire jusqu'a ce quil atteint la fin du fichier
    if (strcmp (Q.id, id) == 0) //si lid existe
        {
        strcpy(A.type,Q.type); // jai besoin de 2 var de type nutri
        strcpy(A.plat,Q.plat);
        strcpy(A.ing,Q.ing);
        strcpy(A.date,Q.date);
	strcpy(A.groupetr,Q.groupetr);
	strcpy(A.modetr,Q.modetr);
	
        }

  }
  return (A);
  fclose (F);  
}


///////////////  MODIFICATION   /////////////////
void modi_nb(char id [] , nutri U) 
{
   FILE *F, *FW;
  nutri c; 
  
F = fopen ("menu.txt", "r");
FW = fopen ("tr.txt", "w");

  if ((F!=NULL)&&(FW!=NULL)) 
{
  while (fscanf (F, "%s %s  %s %s %s %d %s %s",c.id,c.type,c.plat,c.ing,c. date,&c.nb,c.groupetr,c.modetr) ==8) // c cest celui quon souhaite changer ses info ds le cas ou les id =
	
    if (strcmp (c.id, id) == 0)
     {

fprintf (FW, "%s %s %s %s %s %d %s %s\n",id,U.type,U.plat,U.ing,U.date,U.nb,U.groupetr,U.modetr);// u contenant les nouvelles donnees(apres la modification) quon les a entrer au niveau de linterface

     }
     else
     {

       fprintf (FW, "%s %s %s %s %s %d %s %s\n", c.id,c.type,c.plat,c.ing,c. date,c.nb,c.groupetr,c.modetr);
     }
}    

  fclose (F);
  fclose (FW);
remove("menu.txt");
rename("tr.txt", "menu.txt");

}

//////////////////   AFFICHER    ///////////////////
void afficher_nb (GtkWidget *treeview1, char*l )

{
GtkListStore *adstore;       // une variable intermediare pr pouvoir par la suite iterer enreg par enreg de treeview
GtkTreeViewColumn *adcolumn;      // va corresspondre le contenu du champs a son attribut de la liste
GtkCellRenderer *cellad;  //me permet d'envoyer la saisie de l'utulisateur de chaque champs --> puis les afficher
FILE *f;


	char id[30];
	char type[30];
	char nb[30];// on la changer car treeview accepte que char
	char plat[30];
	char ing[30];
	char date[30];
	char groupetr[30];
	char modetr [30];

        /* Creation du modele de type liste*/
        adstore = gtk_list_store_new(8,
                                     G_TYPE_STRING,
                                     G_TYPE_STRING,
                                     G_TYPE_STRING,
                                     G_TYPE_STRING,
                                     G_TYPE_STRING,
                                     G_TYPE_STRING,
                                     G_TYPE_STRING,
                                     G_TYPE_STRING);
        /* Insertion des elements */
        f=fopen(l,"r");
while(fscanf(f,"%s %s %s %s %s %s %s %s\n",id,type,plat,ing,date,nb,groupetr ,modetr)!= EOF)//lecture ligne par ligne
        {
         GtkTreeIter pIter;

         /* Creation de la nouvelle ligne */
         gtk_list_store_append(adstore, &pIter);
         /* Mise a jour des donnees */
         gtk_list_store_set(adstore, &pIter,
                            0,id,
                            1,type,
                            2,plat,
                            3,ing,
                            4,date,
			    5,nb,
                            6,groupetr,
                            7,modetr,
                            -1);}
        fclose(f);

	/* Creation de la 1ere colonne */
if(o==0)
	{cellad = gtk_cell_renderer_text_new();
        adcolumn = gtk_tree_view_column_new_with_attributes("ID",
                                                            cellad,
                                                            "text", 0,
                                                            NULL);


        /* Ajouter la 1er colonne à la vue */
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), adcolumn);// pour linserer ds le treeview1


	/* Creation de la 2eme colonne */
        cellad = gtk_cell_renderer_text_new();
        adcolumn = gtk_tree_view_column_new_with_attributes("Chef",
                                                            cellad,
                                                            "text", 1,
                                                            NULL);
	/* Ajouter la 2emme colonne à la vue */
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), adcolumn);




	/* Creation de la 4eme colonne */
        cellad = gtk_cell_renderer_text_new();
        adcolumn = gtk_tree_view_column_new_with_attributes("Ingrédient",
                                                            cellad,
                                                            "text", 2,
                                                            NULL);
	/* Ajouter la 4emme colonne à la vue */
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), adcolumn);

	/* Creation de la 5eme colonne */
        cellad = gtk_cell_renderer_text_new();
        adcolumn = gtk_tree_view_column_new_with_attributes("Plat",
                                                            cellad,
                                                            "text", 3,
                                                            NULL);
	/* Ajouter la 5emme colonne à la vue */
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), adcolumn);


        /* Creation de la 5eme colonne */
        cellad = gtk_cell_renderer_text_new();
        adcolumn = gtk_tree_view_column_new_with_attributes("DATE",
                                                            cellad,
                                                            "text", 4,
                                                            NULL);
	/* Ajouter la 5emme colonne à la vue */
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), adcolumn);

	/* Creation de la 3eme colonne */
        cellad = gtk_cell_renderer_text_new();
        adcolumn = gtk_tree_view_column_new_with_attributes("Déchet",
                                                            cellad,
                                                            "text", 5,
                                                            NULL);

	/* Ajouter la 3emme colonne à la vue */
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), adcolumn);

	/* Creation de la 3eme colonne */
        cellad = gtk_cell_renderer_text_new();
        adcolumn = gtk_tree_view_column_new_with_attributes("Groupe",
                                                            cellad,
                                                            "text", 6,
                                                            NULL);

	/* Ajouter la 3emme colonne à la vue */
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), adcolumn);

	/* Creation de la 3eme colonne */
        cellad = gtk_cell_renderer_text_new();
        adcolumn = gtk_tree_view_column_new_with_attributes("Mode",
                                                            cellad,
                                                            "text", 7,
                                                            NULL);

	/* Ajouter la 3emme colonne à la vue */
	gtk_tree_view_append_column(GTK_TREE_VIEW(treeview1), adcolumn);


	o++;}


 	gtk_tree_view_set_model ( GTK_TREE_VIEW (treeview1),
                                  GTK_TREE_MODEL(adstore)  );

}
