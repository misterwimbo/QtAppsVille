/*

               ,        ,
              /(        )`
              \ \___   / |
              /- _  `-/  '
             (/\/ \ \   /\
             / /   | `    \
             O O   ) /    |
             `-^--'`<     '
            (_.)  _  )   /
             `.___/`    /
               `-----' /
  <----.     __ / __   \
  <----|====O)))==) \) /====
  <----'    `--' `.__,' \
               |        |
                \       /
           ______( (_  / \______
  (BS)   ,'  ,-----'   |        \
         `--{__________)        \/   "SQL COMMAND bertrand szymanski le 8/3/2016" */



#include "connect.h"
#include "fenetre.h"

#define DRIVER "QMYSQL"
#define DBNAME "codepostal"
#define DBUSER "root"
#define DBPASS "guitares"
#define DBHOST "localhost"


int main (int argc, char **argv)
{


    QApplication app(argc, argv);

    fenetre maFenetre;
    maFenetre.setWindowTitle("SQL Command");
    maFenetre.showMaximized();
    maFenetre.show();
    return app.exec();
}
