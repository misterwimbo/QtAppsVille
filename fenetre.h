#ifndef FENETRE_H
#define FENETRE_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QString>
#include <QInputDialog>
#include <QMessageBox>
#include <QTableView>
#include <QHeaderView>
#include <QtSql>
#include <QString>
#include <QTextLine>
#include <QStringRef>
#include <QLabel>
#include <QModelIndex>

#include "mytextedit.h"



class fenetre : public QWidget
{
 Q_OBJECT

private:

    QWidget            *maFenetre;
    QPushButton        *b_infos;
    QVBoxLayout        *layout;
    QVBoxLayout        *layout2;
    QVBoxLayout        *layout_bouton;
    QVBoxLayout        *layout_requeteBox;
    QHBoxLayout        *layout_principal;
    QLineEdit          *search;
    QSqlQueryModel     *model;
    QTableView         *view;
    MyTextEdit         *requeteBox;
    QLabel             *infos;
    QLabel             *vide;
    QModelIndex        *grille;



    /* le programme ne sert qu'a affficher je limite volontairement les modif de la base de donnée
     * avec cette fonction
     * elle verifie si les commandes CREATE,UPDATE,DROP,REVOKE,GRANT,DELETE,INSERT sont presentent
     * dans la requete
     * si oui annulle la requete */

    void RequeteVerif(QString &req);









public:
    fenetre();


signals:

//essayer de mettre le signal de fermeture ici

public slots:

     void RechercheVille(QString ville);
     void Requete();
     void orderby(QModelIndex grille);
};

#endif // FENETRE_H
