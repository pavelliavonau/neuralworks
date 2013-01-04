#include "logtextevent.h"

LogTextEvent::LogTextEvent(QObject *parent) :
    QEvent((Type)(QEvent::User + 1))
{

}

void LogTextEvent::setText(QString _text)
{
    m_text = _text;
}

QString LogTextEvent::getText()
{
    return m_text;
}
