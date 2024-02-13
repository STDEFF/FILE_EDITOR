#include "main.h"

void DragDropWidget::onfeldCHARClicked() {          //wir ausgeführt wenn auf das Feld Char geklickt wird

    QString text = textEdit->toPlainText();         // Den Text aus dem Textfeld holen

    textEdit->setVisible(true);                     // Das Textfeld sichtbar machen und den Text setzen
    textEdit->setPlainText(text);                   //setzt Text ein
    feldSAVE->setEnabled(true);                     // Macht Button unsichtbar
    feldBIN->setVisible(false);                     // Macht Button unsichtbar
    feldHEX->setVisible(false);                     // Macht Button unsichtbar
    feldCHAR->setVisible(false);                    // Macht Button unsichtbar
    infoLabel->setVisible(false);                   // Macht Feld unsichtbar

    currentMode = Mode::Normal;                     // Setzt Mode auf den aktuellen Mode Bin
}
