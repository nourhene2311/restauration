#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gtk/gtk.h> 

#include "callbacks.h"
#include "interface.h"
#include "support.h"
#include <string.h>
#include <time.h>
#include "menu.h"




int x1;//
int t1[2]={0,0};//modifier
int x;//
int t[2]={0,0};//ajouter


///////////// AFFICHE  ( 2 eme tache ) //////////////////
void
on_affi_nb_clicked                     (GtkWidget       *button,
                                        gpointer         user_data)
{
GtkWidget *message;


int nb1=0;
int nb2=0;
int nb3=0;
int min,x,y;

	char id[30];
	char type[30];
	int nb;
	char plat[30];
	char ing[30];
	char date[30];
	char groupetr[30];
	char modetr [30];

	char resultat [30];
      
  FILE* F;

F=fopen("menu.txt","r");
if(F!=NULL)
{

    
    while(fscanf(F,"%s %s %s %s %s %d %s %s\n",id,type,ing,plat,date,&nb,groupetr ,modetr)!=EOF)
    {
        if((strcmp(plat,"Petit_déjeuner")==0))
        nb1+=nb;
                                             
 if(strcmp(plat,"déjeuner")==0)
{
      nb2+=nb;
 }
 if(strcmp(plat,"Diner")==0)
{
      nb3+=nb;
 }

if(nb1<nb2)
x=nb1;
else
{
    x=nb2;
}

y=nb3;

if(x<y)
min=x;
else
{
    min=y;
}

if(min==nb1){
    strcpy(resultat,id);
}
if(min==nb2){
    strcpy(resultat,id);
}
if(min==nb3){
    strcpy(resultat,id);
}


}

fclose(F);
message = lookup_widget(button, "label11");
gtk_label_set_text(GTK_LABEL(message),resultat);



}
}






//////////////////// ACTUALISATION   /////////////////////// 
void
on_actu_nb_clicked                     (GtkWidget       *objet,             
                                        gpointer         user_data)
{

        GtkTreeModel     *model;
        GtkTreeSelection *selection;
        GtkTreeIter iter;
        GtkWidget* p=lookup_widget(objet,"treeview1");
	gchar *type;
        gchar *plat;
        gchar *etat;
        gchar *date;
  	gchar *nb;
        gchar *id;//gchar* type gtk ==> chaine en c car la fonction gtk_tree_model_get naccepte que gchar*
        selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(p));
        if (gtk_tree_selection_get_selected(selection, &model, &iter))//test sur la ligne selectionnée
        {  gtk_tree_model_get (model,&iter,0,&id,1,&type,2,&plat,3,&etat,4,&date,5,&nb,-1);
  
 gtk_entry_set_text(GTK_ENTRY(lookup_widget(objet,"entryid_nb")),id);

GtkWidget *dd,*type,*plat,*ing,*date,*ty,*se,*da,*po;

	dd = lookup_widget (objet,"entryid_nb");
	type = lookup_widget(objet,"labelchef_nb");
	plat = lookup_widget(objet,"labeling_nb");
	ing = lookup_widget(objet, "labelplat_nb");
	date = lookup_widget(objet, "labeldate_nb");

	ty = lookup_widget (objet,"entrychef_nb");
	se = lookup_widget (objet,"entrying_nb");
	da = lookup_widget (objet,"comboboxplat_nb");
	po = lookup_widget (objet,"entrydate_nb");

	strcpy(id,gtk_entry_get_text(GTK_ENTRY(dd)));
	nutri A= rech_nb(id);

	gtk_label_set_text(GTK_LABEL(type),A.type); 
	gtk_label_set_text(GTK_LABEL(plat),A.plat);
	gtk_label_set_text(GTK_LABEL(ing),A.ing);
	gtk_label_set_text(GTK_LABEL(date),A.date);

	gtk_entry_set_text(GTK_LABEL(ty),A.type);  
	gtk_entry_set_text(GTK_LABEL(se),A.plat);
	gtk_label_set_text(GTK_LABEL(da),A.ing);
	gtk_entry_set_text(GTK_LABEL(po),A.date);
			
                gtk_notebook_prev_page(GTK_NOTEBOOK(lookup_widget(objet,"notebook1")));
}
//mise a jour treeview
afficher_nb(p ,"menu.txt");
}





////////////////////////  RECHERCHE   ////////////////////////////
void
on_rech_nb_clicked                     (GtkWidget      *button,
                                        gpointer         user_data)
{




GtkWidget *dd,*type,*plat,*ing,*date,*ty,*se,*da,*po,*lb;
char idd[20];

int x=-1;
char type1[20];
char plat1[20];
char date1[20];
char nb1[20];
char id[20];
char ing1[20];

FILE *F;
dd = lookup_widget (button,"entryid_nb");
type = lookup_widget(button, "labelchef_nb");
plat = lookup_widget(button, "labeling_nb");
ing = lookup_widget(button, "labelplat_nb");
date = lookup_widget(button, "labeldate_nb");
lb= lookup_widget(button, "labelid");

ty = lookup_widget (button,"entrychef_nb");
se = lookup_widget (button,"entrying_nb");
da = lookup_widget (button,"comboboxplat_nb");
po = lookup_widget (button,"entrydate_nb");




strcpy(idd,gtk_entry_get_text(GTK_ENTRY(dd)));

F = fopen ("menu.txt", "r");

/////////////////////////////////////////////
if (F!=NULL)
 {
  while (fscanf (F,"%s %s %s %s %s %s \n",id,type1,plat1,ing1,date1,nb1) != EOF)
  {
  
    if (strcmp (idd,id) == 0)
      {
      x=1;
      } 
     } 
    
     fclose (F);
  }

if(x==-1)
{
gtk_label_set_text(GTK_LABEL(lb),"l'id n'existe pas ");

}else
{
    nutri A= rech_nb(idd);
    gtk_label_set_text(GTK_LABEL(lb),"1 trouvé");
    gtk_label_set_text(GTK_LABEL(type),A.type);
    gtk_label_set_text(GTK_LABEL(plat),A.plat);
    gtk_label_set_text(GTK_LABEL(ing),A.ing);
    gtk_label_set_text(GTK_LABEL(date),A.date);


    gtk_entry_set_text(GTK_LABEL(ty),A.type);
    gtk_entry_set_text(GTK_LABEL(se),A.plat);
    gtk_label_set_text(GTK_LABEL(da),A.ing);
    gtk_entry_set_text(GTK_LABEL(po),A.date);
}
}




///////////////// MODIFIER //////////////////////////////////
void
on_Modif_nb_clicked                     (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *dd,*ty,*se,*da,*po,*nb,*lb;
int v=-1;
char id[20];
char idd[20];
char type1[20];
char plat1[20];
char ing1[20];
char date1[20];
char groupe1[20];
char mode1[20];
char nb1[20];
nutri U ;

dd = lookup_widget (objet_graphique,"entryid_nb");
ty = lookup_widget (objet_graphique,"entrychef_nb");
se = lookup_widget (objet_graphique,"entrying_nb");
da = lookup_widget (objet_graphique,"comboboxplat_nb");
po = lookup_widget (objet_graphique,"entrydate_nb");
nb = lookup_widget (objet_graphique,"spinbuttondechet_nb");
lb = lookup_widget (objet_graphique,"labelid");


if (x1==1) 
strcpy(U.modetr,"Mode_jour");
 if (x1==2) 
strcpy(U.modetr,"Mode_nuit");
 if (x1==0) 
strcpy(U.modetr,"NULL");

 if (t1[0]==1)
 strcat(U.groupetr,"GroupeB"); 
if(t1[1]==1)
 strcat (U.groupetr,"GroupeA");
if((t1[1]==0)&&(t1[0]==0))
 strcpy (U.groupetr,"NULL");




FILE *F;
F = fopen ("menu.txt", "r");

/////////////////////////////////////////////
if (F!=NULL)
 {
  while (fscanf (F,"%s %s %s %s %s %s %s %s  \n",id,type1,plat1,ing1,date1,nb1,groupe1,mode1) != EOF)
  {
  
    if (strcmp (idd,id) == 0)
      {
      v=1;
      } 
     } 
    
     fclose (F);
  }

    
    gtk_label_set_text(GTK_LABEL(lb),"Modification valiée");/* code */

U.nb=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(nb));
strcpy(id,gtk_entry_get_text(GTK_ENTRY(dd)));
strcpy(U.type,gtk_entry_get_text(GTK_ENTRY(ty)));
strcpy(U.plat,gtk_entry_get_text(GTK_ENTRY(se)));
strcpy(U.ing,gtk_combo_box_get_active_text(GTK_COMBO_BOX(da)));
strcpy(U.date,gtk_entry_get_text(GTK_ENTRY(po)));
//U.modetr=ch2;
//U.groupetr=ch3;

modi_nb(id,U);

/////////////////////////////////////////////////////////////////////////////////




//mise a jour treeview
 GtkWidget* p=lookup_widget(objet_graphique,"treeview1");
afficher_nb(p ,"menu.txt");
}





///////////////// AJOUTER ///////////////////////
void
on_ajout_nb_clicked                     (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *ty,*se,*da,*po,*nb,*Ajouter,*labeldate,*labelmain,*labelty;
Ajouter=lookup_widget(objet_graphique,"Ajouter");
nutri A ;
char id[30];
int i, longueurChaine = 0;
char chaine[] = "1a2z3e4r5t6y7u8i9opqsdfghjklmwxcvbn";
int b=1;

ty = lookup_widget (objet_graphique,"chef_nb");
se = lookup_widget (objet_graphique,"ing_nb");
da = lookup_widget (objet_graphique,"plat_nb");
po = lookup_widget (objet_graphique,"date_nb");
nb = lookup_widget (objet_graphique,"dechet_nb");


A.nb=gtk_spin_button_get_value_as_int(GTK_SPIN_BUTTON(nb));


strcpy(A.type,gtk_entry_get_text(GTK_ENTRY(ty)));
strcpy(A.plat,gtk_entry_get_text(GTK_ENTRY(se)));
strcpy(A.ing,gtk_combo_box_get_active_text(GTK_COMBO_BOX(da)));
strcpy(A.date,gtk_entry_get_text(GTK_ENTRY(po)));

labelty=lookup_widget(objet_graphique,"labelchef");
labelmain=lookup_widget(objet_graphique,"labeling");
labeldate=lookup_widget(objet_graphique,"labeldate");

if (x==1) 
strcpy(A.modetr,"Mode_jour");
 if (x==2) 
strcpy(A.modetr,"Mode_nuit");
 if (x==0) 
strcpy(A.modetr,"NULL");

 if (t[0]==1)
 strcat(A.groupetr,"GroupeB"); 
if(t[1]==1)
 strcat (A.groupetr,"GroupeA");
if((t[1]==0)&&(t[0]==0))
 strcpy (A.groupetr,"NULL");


    longueurChaine = strlen(chaine);//random
 
    srand(time(NULL));
 
    for(i=0; i < 4; i++)
        {
            id[i] = chaine[rand()%longueurChaine];
        }

//A.modetr=ch2;
//A.groupetr=ch3;
 strcpy(A.id,id);

// controle saisie
if(strcmp(A.type,"")==0){
		 
          gtk_label_set_text(GTK_LABEL(labelty),"saisir Chef !");
b=0;
}
else {
		  
          gtk_label_set_text(GTK_LABEL(labelty),"");
}

if(strcmp(A.plat,"")==0){
		  
          gtk_label_set_text(GTK_LABEL(labelmain),"saisir Ingrédient !");
b=0;
}
else {
		  
          gtk_label_set_text(GTK_LABEL(labelmain),"");
}


if(strcmp(A.date,"")==0){
		  
          gtk_label_set_text(GTK_LABEL(labeldate),"saisir date !");
b=0;
}
else {
		  
          gtk_label_set_text(GTK_LABEL(labeldate),"");
}


if(b==1){

ajouter_nb(A);
}
//mise a jour treeview
 GtkWidget* p=lookup_widget(objet_graphique,"treeview1");
afficher_nb(p ,"menu.txt");
}




////////////////// SUPPRIMER /////////////////////////
void
on_supp_nb_clicked                     (GtkWidget       *objet_graphique,
                                        gpointer         user_data)
{
GtkWidget *dd,*lb;

char idd[20];
FILE *F;
int x=-1;
char type[20];
char plat[20];
char date[20];
char ing[20];
char id[20];
char nb [20];

lb = lookup_widget (objet_graphique,"labelid"); 
dd = lookup_widget (objet_graphique,"entryid_nb");
strcpy(idd,gtk_entry_get_text(GTK_ENTRY(dd)));

F = fopen ("menu.txt", "r");


  if (F!=NULL)
 {
  while (fscanf (F,"%s %s %s %s %s %s \n",id,type,plat,ing,date,nb) != EOF)
  {
  
    if (strcmp (idd,id) == 0)
      {
      x=1;
      } 
     } 
    
     fclose (F);
  }

if(x==-1)
{
gtk_label_set_text(GTK_LABEL(lb),"l'id n'existe pas ");
}else
{
    supp_nb(idd);
    gtk_label_set_text(GTK_LABEL(lb),"supprimer avec succes");/* code */
}


//mise a jour treeview
 GtkWidget* p=lookup_widget(objet_graphique,"treeview1");
afficher_nb(p ,"menu.txt");
}



////////////////// SUPPRIMER PAR SELECTION A PARTIR DE TREEVIEW ////////////////
void
on_supp_tree_nb_clicked                (GtkWidget       *objet,
                                        gpointer         user_data)
{
   GtkTreeModel     *model;
        GtkTreeSelection *selection;
        GtkTreeIter iter;
        GtkWidget* p=lookup_widget(objet,"treeview1");;

        gchar *id;//gchar* type gtk ==> chaine en c car la fonction gtk_tree_model_get naccepte que gchar*
        selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(p));
        if (gtk_tree_selection_get_selected(selection, &model, &iter))//test sur la ligne selectionnée
        {  gtk_tree_model_get (model,&iter,0,&id,-1);
           gtk_list_store_remove(GTK_LIST_STORE(model),&iter);//supprimer la ligne du treeView

            supp_nb( id);// supprimer la ligne du fichier
}
}

///////////////////////// les boutons de checkbutton ///////////////////



void
on_checkbutton2_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
   if (gtk_toggle_button_get_active(togglebutton)) //gp A

   {t[1]=1;}    
}


void
on_checkbutton1_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
  if (gtk_toggle_button_get_active(togglebutton)) //gp B
  {t[0]=1;}   
}





////////////////////// les boutons radios  ////////////////
void
on_radiobutton1_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
 if (gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
 {x=1;} 
}


void
on_radiobutton2_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
 if (gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton))) 
{x=2;} 
}






//////////////// les boutons des sites webs //////////////////	

void
on_Facebook_clicked                    (GtkButton       *button,
                                        gpointer         user_data)
{
system("firefox https://www.facebook.com/");
}


void
on_youtube_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
system("firefox https://www.youtube.com/");
}


void
on_Instagram_clicked                   (GtkButton       *button,
                                        gpointer         user_data)
{
system("firefox https://www.instagram.com/");
}


void
on_checkbutton4_toggled                (GtkToggleButton *togglebutton,//groupeB
                                        gpointer         user_data)
{
   if (gtk_toggle_button_get_active(togglebutton)) //gp A

   {t1[0]=1;} 
else 
   {t1[0]=0;} 
}


void
on_checkbutton3_toggled                (GtkToggleButton *togglebutton,//groupeA
                                        gpointer         user_data)
{
   if (gtk_toggle_button_get_active(togglebutton)) //gp A

   {t1[1]=1;} 
else 
   {t1[1]=0;} 
}


void
on_radiobutton4_toggled                (GtkToggleButton *togglebutton,
                                        gpointer         user_data)
{
 if (gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton))) //mode nuit
{x1=2;} 
else 
{x1=0;} 

}

void
on_radiobutton3_toggled                (GtkToggleButton *togglebutton,//mode jour
                                        gpointer         user_data)
{
 if (gtk_toggle_button_get_active(GTK_RADIO_BUTTON (togglebutton)))
 {x1=1;} 
else 
{x1=0;}  

}

