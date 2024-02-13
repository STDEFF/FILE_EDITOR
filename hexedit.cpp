#include "main.h"

void DragDropWidget::onfeldHEXClicked() {

    QString text = textEdit->toPlainText();                         // Text in Textfeld transferieren

    textEdit->setVisible(true);                                     // Textfeld wird sichtbar

    QString convertedText;                                          // Umwandlung in Hexadezimale Darstellung
    for (QChar ch : text) {
        convertedText += QString::number(ch.unicode(), 16) + " ";    // Jedes Zeichen wird durch einen Hexadezimalen Wert ersetzt
    }

    textEdit->setPlainText(convertedText);                          // Fügt konvertierten Text in Textfeld ein
    feldSAVE->setEnabled(true);                                     // Macht Feld unsichtbar
    feldBIN->setVisible(false);                                     // Macht Feld unsichtbar
    feldHEX->setVisible(false);                                     // Macht Feld unsichtbar
    feldCHAR->setVisible(false);                                    // Macht Feld unsichtbar

    currentMode = Mode::Hexadecimal;                                // Setzen des aktuellen Modus auf Hexadezimal
}
