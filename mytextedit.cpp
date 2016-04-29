#include "mytextedit.h"

/*MyTextEdit::MyTextEdit():QTextEdit()
{
    myRequetBox = new MyTextEdit;
}*/


void MyTextEdit::keyPressEvent(QKeyEvent * event)
{

    if(event->key() == Qt::Key_Return)
        emit returnPressed();
        else
            QTextEdit::keyPressEvent(event);
}
