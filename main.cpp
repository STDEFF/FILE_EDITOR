#include "main.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);                   //inizialisiert die Q Applikation

    DragDropWidget myWidget;                     //intizialisert Drag and Drop Funktion Widget mit Name myWidget
    QPalette pal = QPalette();                   //intizialisiert Q Palette
    pal.setColor(QPalette::Window, Qt::gray);    //setzt Farbe grau
    myWidget.setAutoFillBackground(true);        //Füllt Hintergrund in gesetzte Farbe
    myWidget.setPalette(pal);                    //definiert pal
    myWidget.resize(600,600);                    // Legt Größe des Widget fest
    myWidget.show();                             // Stellt Widget dar

    return a.exec();
}
