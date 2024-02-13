#include "main.h"

void DragDropWidget::onfeldBINClicked() {           //wir ausgeführt wenn auf das Feld Bin geklickt wird

    QString text = textEdit->toPlainText();          // Einbeziehen der Datei in Textfeld

    textEdit->setVisible(true);                     // Macht Textfeld sichtbar

    QString convertedText;                          // Umwandlung der hochgeladenen Datei in Binärcode
    for (QChar ch : text) {                         // Umwandlung der Zeichen Bin Format und hinzufügen zu 'convertedText'
        convertedText += QString::number(ch.unicode(), 2) + " ";
    }
    textEdit->setPlainText(convertedText);          // Transferiert umgewandelten Text in Textfeld

    feldSAVE->setEnabled(true);
    feldBIN->setVisible(false);                     // Macht Feld unsichtbar
    feldHEX->setVisible(false);                     // Macht Feld unsichtbar
    feldCHAR->setVisible(false);                    // Macht Feld unsichtbar
    infoLabel->setVisible(false);                   // Macht Feld unsichtbar

    currentMode = Mode::Binary;                     // Setzt Mode auf den aktuellen Mode Bin
}
