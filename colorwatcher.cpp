#include "colorwatcher.h"

// std includes
#include <set>

// Qt includes
#include <QDebug> //REMOVEME
#include <QRegularExpression>
#include <QTextBlock>
#include <QTextCursor>

// QtCreator includes
#include <coreplugin/editormanager/editormanager.h>

#include <texteditor/texteditor.h>

// Own includes
#include "colorpickerconstants.h"

using namespace Core;
using namespace TextEditor;

namespace ColorPicker {
namespace Internal {


////////////////////////// ColorWatcherImpl //////////////////////////

class ColorWatcherImpl
{
public:
    ColorWatcherImpl() :
        colorRegexes()
    {
        // Register regexes
        colorRegexes.insert(ColorType::RgbType, Constants::REGEX_RGB);
        colorRegexes.insert(ColorType::RgbaType, Constants::REGEX_RGBA);
        colorRegexes.insert(ColorType::HsvType, Constants::REGEX_HSV);
        colorRegexes.insert(ColorType::HsvaType, Constants::REGEX_HSVA);
        colorRegexes.insert(ColorType::HexType, Constants::REGEX_HEXCOLOR);
    }

    ~ColorWatcherImpl() {}

    /* functions */
    QColor colorFromRegexp(ColorType type, const QRegularExpressionMatch &match) const
    {
        QColor ret;

        if (type == ColorType::RgbType) {
            int r = match.captured(1).toInt();
            int g = match.captured(2).toInt();
            int b = match.captured(3).toInt();

            ret.setRgb(r, g, b);
        }
        else if (type == ColorType::RgbaType) {
            ret.setRed(match.captured(1).toInt());
            ret.setGreen(match.captured(2).toInt());
            ret.setBlue(match.captured(3).toInt());
            ret.setAlphaF(match.captured(4).toFloat());
        }
        else if (type == ColorType::HsvType) {
            int h = match.captured(1).toInt();
            int s = match.captured(2).toInt();
            int v = match.captured(3).toInt();

            ret.setHsv(h, s,v);
        }
        else if (type == ColorType::HsvaType) {
            int h = match.captured(1).toInt();
            int s = match.captured(2).toInt();
            int v = match.captured(3).toInt();
            int a = match.captured(4).toFloat();

            ret.setHsv(h, s, v);
            ret.setAlphaF(a);
        }
        else if (type == ColorType::HexType) {
            ret.setNamedColor(match.captured());
        }

        Q_ASSERT_X(ret.isValid(), Q_FUNC_INFO, "The color cannot be invalid.");

        return ret;
    }

    /* attributes */
    QMap<ColorType, std::string> colorRegexes;
};


////////////////////////// ColorWatcher //////////////////////////

ColorWatcher::ColorWatcher(QObject *parent) :
    QObject(parent),
    d(new ColorWatcherImpl)
{

}

ColorWatcher::~ColorWatcher()
{}

void ColorWatcher::processCurrentTextCursor(TextEditorWidget *textEditor)
{
    Q_ASSERT_X(textEditor, Q_FUNC_INFO, "The current editor is invalid.");

    QTextCursor currentCursor = textEditor->textCursor();
    QString lineText = currentCursor.block().text();

    for (auto it = d->colorRegexes.begin(); it != d->colorRegexes.end(); ++it) {
        std::string rawRegex = it.value();

        QRegularExpression regexp(QString::fromStdString(rawRegex),
                                  QRegularExpression::CaseInsensitiveOption);

        QRegularExpressionMatchIterator matchIt = regexp.globalMatch(lineText);

        while (matchIt.hasNext()) {
            QRegularExpressionMatch match = matchIt.next();

            int cursorPosInLine = currentCursor.positionInBlock();
            int capturedStart =  match.capturedStart();
            int capturedEnd =  match.capturedEnd();

            bool cursorIsUnderColor = (cursorPosInLine >= capturedStart) &&
                    (cursorPosInLine <= capturedEnd);

            if (cursorIsUnderColor) {
                // Select the expression
                currentCursor.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor,
                                           cursorPosInLine - capturedStart);
                currentCursor.movePosition(QTextCursor::Right, QTextCursor::KeepAnchor,
                                           capturedEnd - capturedStart);

                textEditor->setTextCursor(currentCursor);

                //
                ColorType type = it.key();
                QColor color = d->colorFromRegexp(type, match);

                emit colorFound(color, type);
                break;
            }
        }
    }
}

} // namespace Internal
} // namespace ColorPicker
