#ifndef HANDLERSIGNALS_H
#define HANDLERSIGNALS_H

#include <QObject>
#include <QVariant>
#include <QDebug>
#include <QVector>
#include <cstdlib>
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <QEventLoop>
#include <QTimer>

class HandlerSignals : public QObject
{
    Q_OBJECT
public:
    explicit HandlerSignals(QObject *parent = 0);

signals:

public slots:
    void changeField(const QString &msg, const QString &pos);
    void generation();
    void engine();
    void createSoldier(const QString &pos);
    void changeAnimation(const QString &name, const QString &anim, const QString &pos, const QString &idshka);


private:
    int field [44][24];
    QVector<int> sorc1;
    QVector<int> sorc2;
    QVector<int> trees;
    int treeID = 1;
    int sorcIDMaker = 1;

};

#endif // HANDLERSIGNALS_H
