#include "main.h"


DragDropWidget::DragDropWidget(QWidget *parent) : QWidget(parent) {             // Definiert die Benutzerschnittstelle
    setAcceptDrops(true);                                                       // Erlaubt die Drag and Drop Funktion

    infoLabel = new QLabel("MP3-Datei \n (via Drag and Drop ablegen)", this);   // Zeigt Information an wie Datei einbezogen werden kann
    infoLabel->setAlignment(Qt::AlignCenter);                                   // Positioniert Textfeld
    infoLabel->setVisible(true);                                                    // Informationsfeld sichtbar

    textEdit = new QTextEdit(this);                                             // Definiert Bearbeitungstextfeld
    textEdit->setFrameStyle(QFrame::Sunken | QFrame::Panel);                    // Setzt Anzeigeeigenschaft
    textEdit->setVisible(false);                                                // Bearbeitungstextfeld unsichtbar

    feldBIN = new QPushButton("BIN-Format-Editierung", this);                   // Schaltflächen erstellen/ mit Funktion clicked verknüpfen
    connect(feldBIN, &QPushButton::clicked, this, &DragDropWidget::onfeldBINClicked);
    feldBIN->setEnabled(false);
    feldBIN->setGeometry(0,350,200,50);

    feldHEX = new QPushButton("HEX-Format-Editierung", this);                      // Schaltflächen erstellen mit Funktion clicked verknüpfen
    connect(feldHEX, &QPushButton::clicked, this, &DragDropWidget::onfeldHEXClicked);
    feldHEX->setEnabled(false);
    feldHEX->setGeometry(200,350,200,50);

    feldCHAR = new QPushButton("CHAR-Format-Editierung", this);                   // Schaltflächen erstellen mit Funktion clicked verknüpfen
    connect(feldCHAR, &QPushButton::clicked, this, &DragDropWidget::onfeldCHARClicked);
    feldCHAR->setEnabled(false);
    feldCHAR->setGeometry(400,350,200,50);

    feldSAVE = new QPushButton("SAVE->", this);                                   // Schaltflächen erstellen mit Funktion clicked verknüpfen
    connect(feldSAVE, &QPushButton::clicked, this, &DragDropWidget::onfeldSAVEClicked);
    feldSAVE->setEnabled(false);
    feldSAVE->setGeometry(550,0,60,25);

    feldCLEAR = new QPushButton("<-Return", this);                                // Schaltflächen erstellen mit Funktion clicked verknüpfen
    connect(feldCLEAR, &QPushButton::clicked, this, &DragDropWidget::onfeldCLEARClicked);
    feldCLEAR->setEnabled(false);
    feldCLEAR->setGeometry(0,0,60,25);


    QVBoxLayout *layout = new QVBoxLayout(this);                                  // legt Layout für Drag and Drop Hinweis und Textfeld
    layout->addWidget(infoLabel, 0, Qt::AlignCenter);
    layout->addWidget(textEdit);
}




void DragDropWidget::dragEnterEvent(QDragEnterEvent *event) {       // Drag and Drop Aktion getriggert

    if (event->mimeData()->hasUrls()) {                             // Überprüft einbezogene Datei ob richtiges Datei Format enthält
        QList<QUrl> urls = event->mimeData()->urls();
        bool datafile = false;
        QStringList supportedFormats = {".mp3"};                    //Es kann hier nur eine MP3 Datei einbezogen werden

        for (const QUrl &url : urls) {                              //Überprüfung des Dateiformats
            QString path = url.toLocalFile();
            QFileInfo fileinfo(path);
            QString filedetail = fileinfo.suffix().toLower();

            if (supportedFormats.contains("." + filedetail)) {   //Einbezogene Dateiname und Größe wird bei korrekten Format in Widget angezeigt
                datafile = true;
                infoLabel->setText("Datei: " + fileinfo.fileName() + " - Dateigröße: " + QString::number(fileinfo.size()) + " Bytes");
                break;
            }
        }
        if (datafile) {                                             //Bestätigung der Datei
            event->acceptProposedAction();
        }
    }
}

void DragDropWidget::dropEvent(QDropEvent *event) {                 //einlesen der ausgewählen Datei
    if (event->mimeData()->hasUrls()) {
        QUrl url = event->mimeData()->urls().first();
        QString filePath = url.toLocalFile();
        originalFileExtension = QFileInfo(filePath).suffix();

        QFile file(filePath);
        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {     //öffnet die Datei speichert das Zeichenformat zwischen
            QTextStream in(&file);
            QString fileContent = in.readAll();
            textEdit->setPlainText(fileContent);
            file.close();

            feldBIN->setEnabled(true);                              // Felder aktivieren da Datei eingelesen ist
            feldHEX->setEnabled(true);
            feldCHAR->setEnabled(true);
            feldCLEAR->setEnabled(true);
        } else {
            qInfo() << "Fehler beim Öffnen der Datei";              //Fehlermeldung wenn Datei einlesen fehlschlägt
        }
    }
}


void DragDropWidget::onfeldSAVEClicked() {                                //Funktion wird geöffnet wenn der Button Speichern selektiert wird
    if (!validedit()) {                                                   //springt in charactercheck.cpp um Text auf richtige Zeichen zu überprüfen
        QMessageBox::warning(this, "ERROR!!!!!", "Ungültige Editierung"); //wenn nicht korrekt Fehlermeldung
        return;
    }
    QString filter = "Text Files (*.txt);;All Files (*)";                 // Filtern der Dateien vor dem Speichern
    if (!originalFileExtension.isEmpty()) {
        filter = QString("%1 Files (*.%2);;").arg(originalFileExtension.toUpper(), originalFileExtension) + filter;
    }

    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "/home/untitled." + originalFileExtension,filter);
                                                                     // Festlegen  des Speicherorts und Name
    if (fileName.isEmpty())
        return;

    QFile file(fileName);                                            // Text wird in das gewünschte Output File geschrieben
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        out << textEdit->toPlainText();
        file.close();
    }
}


void DragDropWidget::onfeldCLEARClicked() {        //Wenn Button Return ausgewählt wird Abfragebox geöffnet
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Warnung", "Sind Sie sicher, dass Sie zurückspringen möchten? Alle Änderungen gehen verloren!",
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::Yes) {               // Wenn bei Abfrage Box ja dann wird zum Subprogramm clearimportantFile gewechselt
        clearImportedFile();
    }
    }

void DragDropWidget::clearImportedFile() {          // Forstetzung wenn bei Return Abfrage Ja selektriert wird
    textEdit->clear();                              // Löscht den Textinhalt im Textfeld
    infoLabel->setText("Datei hier ablegen");       // Setzt den Infotext zurück
    originalFileExtension.clear();
                                                    // Macht Buttons wieder sichtbar bzw unselktierbar ->keine Datei mehr vorhanden ->Ausgangszustand
    feldBIN->setEnabled(false);
    feldHEX->setEnabled(false);
    feldCHAR->setEnabled(false);
    feldSAVE->setEnabled(false);
    feldCLEAR->setEnabled(false);
    feldBIN->setVisible(true);
    feldHEX->setVisible(true);
    feldCHAR->setVisible(true);
    textEdit->setVisible(false);
    infoLabel->setVisible(true);
    currentMode = Mode::Normal;                     // Setzt den Modus auf Normal zurück
}


