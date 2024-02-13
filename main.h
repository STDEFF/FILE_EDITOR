#ifndef MAIN_H
#define MAIN_H
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QFileInfo>
#include <QMessageBox>
#include <QFileDialog>
#include <QRegularExpression>
#include <QVBoxLayout>
#include <QPainter>
#include <QWidget>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QLabel>


class DragDropWidget : public QWidget {                     //definiert alle Felder sowie Aktionen im Drag and Drop
    Q_OBJECT

public:
    explicit DragDropWidget(QWidget *parent = nullptr);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void clearImportedFile();

private slots:                               //Variablen Deklaration
    void onfeldBINClicked();
    void onfeldHEXClicked();
    void onfeldCHARClicked();
    void onfeldSAVEClicked();
    void onfeldCLEARClicked();
    bool validedit();

private:
    QLabel *label;                            // Label zur Anzeige von Informationen
    QLabel *infoLabel;                        // Textfeld für Datei Information
    QPushButton *feldBIN;                     // Button für BIN
    QPushButton *feldHEX;                     // Button für HEX
    QPushButton *feldCHAR;                    // Button für CHAR
    QPushButton *feldSAVE;                    // Button Speichern
    QPushButton *feldCLEAR;                   // Button Zurücksetzen
    QTextEdit *textEdit;                      // Textfeld für Eingabe/Ausgabe
    QString originalFileExtension;            // Ursprüngliche Dateierweiterung
    enum class Mode { Normal, Binary, Hexadecimal } currentMode = Mode::Normal; // Hier wird definiert in welchem Modus sich das Programm befindet zur Zeichenüberprüfung
};

#endif // MAIN_H
