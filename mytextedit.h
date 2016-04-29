#ifndef DEF_EDITEUR
#define DEF_EDITEUR

#include <QTextEdit>
#include <QWidget>
#include <QKeyEvent>


class MyTextEdit : public QTextEdit
{
    Q_OBJECT


    public:

    QTextEdit *myRequetBox;

  /*  MyTextEdit();*/
    ~MyTextEdit()  {delete myRequetBox;}
    void keyPressEvent(QKeyEvent *event);       //Gerer les evenements

    public slots:

    signals:
    void returnPressed();  //j'ai crée cette classe pour avoir acces à cette methode :)
};



#endif
