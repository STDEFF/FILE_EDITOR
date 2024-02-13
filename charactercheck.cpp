#include "main.h"

bool DragDropWidget::validedit() {
    QString text = textEdit->toPlainText();
    QRegularExpression re;

    if (currentMode == Mode::Binary) {
        re.setPattern("^[01 ]*$");                          // Kontrolliert ob die richtigen Zeichen im File sind bei BIN Format
    } else if (currentMode == Mode::Hexadecimal) {
        re.setPattern("^[0-9A-Fa-f ]*$");                  // Kontrolliert ob die richtigen Zeichen im File sind bei HEX Format
    } else {
        return true;                                       // Bei zeichenweiser Darstellung kann es nicht überprüft werden
    }

    return re.match(text).hasMatch();
}
