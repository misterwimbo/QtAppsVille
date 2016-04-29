#include "fenetre.h"
#include "connect.h"
#include "mytextedit.h"

#define QT_USE_FAST_CONCATENATION
#define QT_USE_FAST_OPERATOR_PLUS

// le constructeur
fenetre::fenetre() : QWidget()
{

    /*declaration des widgets  */
    maFenetre              =  new QWidget;
    layout                 =  new QVBoxLayout;
    layout2                =  new QVBoxLayout;
    layout_requeteBox      =  new QVBoxLayout;
    layout_bouton          =  new QVBoxLayout;
    layout_principal       =  new QHBoxLayout;
    search                 =  new QLineEdit;
    model                  =  new QSqlQueryModel;
    view                   =  new QTableView;
    requeteBox             =  new MyTextEdit;
    b_infos                =  new QPushButton; // ce bouton n'est pas cliquable
    infos                  =  new QLabel;
    vide                   =  new QLabel;
    grille                 =  new QModelIndex;




     Connection *db         =  new Connection;



    //////////////////////////////////////////////////////////////////////////////////////////
    /*connection base de donnée */
    QString driver("QMYSQL");
    QString dbname("codepostal");    //changer les infos de connexion si besoin
    QString dbuser("root");
    QString dbpass("guitares");
    QString dbhost("localhost");

    if(!db->setConnection(driver,dbname,dbhost,dbuser,dbpass))
    {
        QMessageBox::critical(this,"Erreur","imposssible de se connecter à la base de donnée");
        qApp->quit();
    }

    ////////////////////////////////////////////////////////////////////////////////////////////

    else{

        view->setModel(model);
        model->setQuery(" SELECT nom ,cp,nom_departement,nom_region,lat,lon "
                        "FROM maps_ville INNER JOIN departement "
                        "ON maps_ville.id_departement=departement.id_departement "
                        "INNER JOIN region "
                        "ON departement.id_region=region.id_region");

        model->setHeaderData(0, Qt::Horizontal, "Nom Ville");
        model->setHeaderData(1, Qt::Horizontal, "Code Postal");
        model->setHeaderData(2, Qt::Horizontal, "Nom Departement");
        model->setHeaderData(3, Qt::Horizontal, "region");
        model->setHeaderData(4, Qt::Horizontal, "latitude");
        model->setHeaderData(5, Qt::Horizontal, "longitude");





        view->resizeColumnsToContents();
        //Affichage des données en adaptant le delegué du modele dans la vue
        view->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        // on charge le modèle
        view->setParent(this);

        /*reglages de la barre de recherche*/
        search->setPlaceholderText("SAISIR UNE VILLE A RECHERCHER...");

        /*reglages requete box */
        requeteBox->setPlaceholderText("TAPER ICI VOS REQUETES SQL...");



        /*reglages du layout */
        infos->setText("<center><H1><b>SQL Command</b></H1><BR>"
                       "<h3><b>La barre de recherche en haut à gauche permet de faire une recherche de ville<BR><BR>"
                       "<BR><font color = red>options:</font></b><BR><BR>"
                       "<i><font color = blue>region:NOM DE VILLE    <BR>"
                       "                     >>> liste les villes par region<BR><BR>"
                       "dep:NOM DE VILLE       <BR>"
                       ">>> liste les villes par departements<BR><BR>"
                       "cp:CODE POSTAL<BR>"
                       ">>> recherche les villes par code postal"
                       "</font></i><BR><BR>"
                       "<BR><BR><BR><BR><BR>"
                       "<b>La fenetre ci dessous permet de faire des requetes sql<BR>"
                       "<BR><font color = red>LES COMMANDES CREATE, UPDATE, INSERT, DELETE, DROP SONT DESACTIVEES<BR>"
                       "</font></b><h3>");

        vide->setText("<br>"
                       "<br><br><br><br><br><br><br>"
                      "<br><br><br><br><br><br><br><br><br><br><br>");



        /*reglages bouton */
        b_infos->setDisabled(true);
        b_infos->setText("TAPER CI DESSOUS VOS REQUETES SQL , APPUYER SUR ENTREE POUR VALIDER");



        /* placement des widgets */
        layout->addWidget(search); //layout vertival
        layout->addWidget(view);
        layout_bouton->addStretch();
        layout_bouton->addWidget(infos);
        layout_bouton->addStretch();
        layout_bouton->addWidget(vide);
        layout_bouton->addStretch();
        layout_bouton->addStretch();
        layout_bouton->addWidget(b_infos);
        layout_requeteBox->addStretch();
        layout_requeteBox->addLayout(layout_bouton);
        layout_requeteBox->addWidget(requeteBox);
        layout_principal->addLayout(layout);
        layout_principal->addLayout(layout_requeteBox);
        setLayout(layout_principal);



      /* signals et slots*/
        connect(search,SIGNAL(textChanged(QString)),this,SLOT(RechercheVille(QString))); // cherche une ville
        connect(requeteBox,SIGNAL(returnPressed()),this,SLOT(Requete()));
        connect(view,SIGNAL(clicked(QModelIndex)),this,SLOT(orderby(QModelIndex)));

}
}

void fenetre::RechercheVille(QString ville)
{

         if(ville[0]=='r' &&
            ville[1]=='e' &&
            ville[2]=='g' &&
            ville[3]=='i' &&
            ville[4]=='o' &&
            ville[5]=='n' &&
            ville[6]==':' )
    {     //liste les villes par region


        ville=ville.mid(7);
       // QMessageBox::critical(this,town,town);

        model->setQuery("SELECT nom ,cp,nom_departement,nom_region,lat,lon "
                        "FROM maps_ville INNER JOIN departement "
                        "ON maps_ville.id_departement=departement.id_departement "
                        "INNER JOIN region  "
                        "ON departement.id_region=region.id_region WHERE nom LIKE '" + ville + "%' ORDER BY nom_region");
    }

    else if(ville[0]=='d' &&
            ville[1]=='e' &&
            ville[2]=='p' &&
            ville[3]==':' )
    {     //liste les villes par departement

        QString town;
        town=ville.mid(4);

        model->setQuery("SELECT nom ,cp,nom_departement,nom_region,lat,lon "
                        "FROM maps_ville INNER JOIN departement "
                        "ON maps_ville.id_departement=departement.id_departement "
                        "INNER JOIN region  "
                        "ON departement.id_region=region.id_region WHERE nom LIKE '" + town + "%' ORDER BY nom_departement");

    }

         else if(ville[0]=='c' &&
                 ville[1]=='p' &&
                 ville[2]==':' )
         {     //liste les villes par departement

             QString town;
             town=ville.mid(3);

             model->setQuery("SELECT nom ,cp,nom_departement,nom_region,lat,lon "
                             "FROM maps_ville INNER JOIN departement "
                             "ON maps_ville.id_departement=departement.id_departement "
                             "INNER JOIN region  "
                             "ON departement.id_region=region.id_region WHERE cp LIKE '" + town + "%' ORDER BY cp");

         }



    else {
        model->setQuery("SELECT nom ,cp,nom_departement,nom_region,lat,lon "
                        "FROM maps_ville INNER JOIN departement "
                        "ON maps_ville.id_departement=departement.id_departement "
                        "INNER JOIN region  "
                        "ON departement.id_region=region.id_region WHERE nom LIKE '" + ville + "%' ORDER BY nom");

        model->setHeaderData(0, Qt::Horizontal, "Nom Ville");
        model->setHeaderData(1, Qt::Horizontal, "Code Postal");
        model->setHeaderData(2, Qt::Horizontal, "Nom Departement");
        model->setHeaderData(3, Qt::Horizontal, "region");
        model->setHeaderData(4, Qt::Horizontal, "latitude");
        model->setHeaderData(5, Qt::Horizontal, "longitude");



    }
}

void fenetre::Requete()
{
    QSqlQuery query;
    QString req = requeteBox->toPlainText();
    req=req.toUpper();// je met en maj cela va me facilliter la tache pour la fonction  RequeteVerif()
    RequeteVerif(req);


    if(!query.exec(req+";"))
    QMessageBox::critical(this,"Erreur","Requete Non valide! : "+req);
    else
    {

            model->setQuery(req);
            model->setHeaderData(0, Qt::Horizontal, " ",1);
            model->setHeaderData(1, Qt::Horizontal, " ",1);
            model->setHeaderData(2, Qt::Horizontal, " ",1);
            model->setHeaderData(3, Qt::Horizontal, " ");
            model->setHeaderData(4, Qt::Horizontal, " ");
            model->setHeaderData(5, Qt::Horizontal, " ");


    }
}

void fenetre::RequeteVerif(QString &req)
{
    //j'interdis toute modification sur la base de données c'est voulu just de l'affichage pour ce prog */
    req.replace("CREATE","******");
    req.replace("DROP","******");
    req.replace("REVOKE","******");
    req.replace("GRANT","******");
    req.replace("DELETE","******");
    req.replace("INSERT","******");
    req.replace("UPDATE","******");



}
void fenetre::orderby(QModelIndex grille)
{
  //  QMessageBox::warning(this,"test","test");
      qDebug () <<"ligne:"<<grille.row()<<" colonne:"<<grille.column();
      qDebug ()<<"action:"<<grille.internalId();
      qDebug () <<"autre:"<<grille.model();

      int static i=0;       i+=1;  if(i == 2) i=0;
      QString ville;


    if(i == 1)
    {


    model->setQuery("SELECT nom ,cp,nom_departement,nom_region,lat,lon "
                    "FROM maps_ville INNER JOIN departement "
                    "ON maps_ville.id_departement=departement.id_departement "
                    "INNER JOIN region  "
                    "ON departement.id_region=region.id_region WHERE nom LIKE '" + ville + "%' ORDER BY nom DESC");

    }
    else
    {
        model->setQuery("SELECT nom ,cp,nom_departement,nom_region,lat,lon "
                        "FROM maps_ville INNER JOIN departement "
                        "ON maps_ville.id_departement=departement.id_departement "
                        "INNER JOIN region  "
                        "ON departement.id_region=region.id_region WHERE nom LIKE '" + ville + "%' ORDER BY nom ASC");

    }
}

