#ifndef LOGTEXTEVENT_H
#define LOGTEXTEVENT_H

//#include <QObject>
#include <QEvent>
#include <QString>


class LogTextEvent : public QEvent
{

  //  Q_OBJECT

public:
    explicit LogTextEvent(QObject *parent = 0);
    
    void setText(QString);
    QString getText();

private:
    QString m_text;
//signals:
    
//public slots:
    
};

#endif // LOGTEXTEVENT_H
