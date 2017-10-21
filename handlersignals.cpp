#include "handlersignals.h"

HandlerSignals::HandlerSignals(QObject *parent) : QObject(parent)
{

}

void HandlerSignals::changeField(const QString &msg, const QString &pos) {
    qDebug() << msg;
    QObject* mmm = this->parent()->findChild<QObject*>("mmm");
    QMetaObject::invokeMethod(mmm, "changecolor", Q_ARG(QVariant, pos), Q_ARG(QVariant, msg));
}

void HandlerSignals::changeAnimation(const QString &name, const QString &anim, const QString &pos, const QString &idshka) {
    QObject* planescaper = this->parent()->findChild<QObject*>(name);

    if (name == "sorcer2")
    {
//        planescaper->children()[1]->children()[0]->setProperty("target", name); //для солдиеров - idhska
//        planescaper->children()[1]->children()[1]->setProperty("target", name);
        planescaper->children()[1]->children()[0]->setProperty("to", 30*(pos.toInt()%24)-60);
        planescaper->children()[1]->children()[1]->setProperty("to", 30*floor(pos.toInt()/24)-45);
        planescaper->children()[1]->setProperty("running", true);

        QEventLoop looop; QTimer::singleShot(1500, &looop, SLOT(quit())); looop.exec(); //yobanarot, bez zaderzhki vse nepoporyadku

        planescaper->children()[0]->children()[0]->setProperty("source", "qrc:/" + anim + ".png");
        planescaper->children()[0]->children()[0]->setProperty("frameCount", 15);
        planescaper->children()[0]->children()[0]->setProperty("loops", 1);

        QEventLoop loop; QTimer::singleShot(500, &loop, SLOT(quit())); loop.exec(); //yobanarot, bez zaderzhki vse nepoporyadku

        QMetaObject::invokeMethod(planescaper->children()[0]->children()[0], "restart");
    }
    else
    {
        planescaper->children()[0]->children()[0]->setProperty("source", "qrc:/" + anim + ".png");
        planescaper->children()[0]->children()[0]->setProperty("frameCount", 15);
        planescaper->children()[0]->children()[0]->setProperty("loops", 1);

        QEventLoop loop; QTimer::singleShot(500, &loop, SLOT(quit())); loop.exec(); //yobanarot, bez zaderzhki vse nepoporyadku

        QMetaObject::invokeMethod(planescaper->children()[0]->children()[0], "restart");

//        planescaper->children()[1]->children()[0]->setProperty("target", name); //для солдиеров - idhska
//        planescaper->children()[1]->children()[1]->setProperty("target", name);
        planescaper->children()[1]->children()[0]->setProperty("to", 30*(pos.toInt()%24)+30);
        planescaper->children()[1]->children()[1]->setProperty("to", 30*floor(pos.toInt()/24)-30);
        planescaper->children()[1]->setProperty("running", true);
    }
}

void HandlerSignals::createSoldier(const QString &pos) {
    if (field[pos.toInt() / 24][pos.toInt() % 24] != 1)
    {
        qDebug() << pos;
        if (pos < 528)
        {
            sorc1.append(sorcIDMaker);
            QObject* mmm = this->parent()->findChild<QObject*>("mmm");
            QMetaObject::invokeMethod(mmm, "createsoldier", Q_ARG(QVariant, pos), Q_ARG(QVariant, "f"+ QString::number(sorcIDMaker)));
            sorcIDMaker++;
        }
        else
        {
            sorc2.append(sorcIDMaker);
            QObject* mmm = this->parent()->findChild<QObject*>("mmm");
            QMetaObject::invokeMethod(mmm, "createsoldier", Q_ARG(QVariant, pos), Q_ARG(QVariant, "f" + QString::number(sorcIDMaker)));
            sorcIDMaker++;
        }
    }
}

void HandlerSignals::engine() {

}

void HandlerSignals::generation() {

    //reset();
    for (int s1 = 0; s1 < sorc1.size(); ++s1) {
        QObject* sold1 = this->parent()->findChild<QObject*>("f" + QString::number(sorc1.at(s1)));
        QMetaObject::invokeMethod(sold1, "hello");
    }
    for (int s2 = 0; s2 < sorc2.size(); ++s2) {
        QObject* sold2 = this->parent()->findChild<QObject*>("f" + QString::number(sorc2.at(s2)));
        QMetaObject::invokeMethod(sold2, "hello");
    }
    for (int t = 0; t < trees.size(); ++t) {
        QObject* treee = this->parent()->findChild<QObject*>("t" + QString::number(trees.at(t)));
        QMetaObject::invokeMethod(treee, "hello");
    }
    sorc1.clear();
    sorc2.clear();
    trees.clear();

    QObject* sorca1 = this->parent()->findChild<QObject*>("sorcer1");
    QMetaObject::invokeMethod(sorca1, "hello");
    QObject* sorca2 = this->parent()->findChild<QObject*>("sorcer2");
    QMetaObject::invokeMethod(sorca2, "hello");

    for (auto i = 0; i < 44; i+=2)
    {
        for (auto j = 0; j < 24; j+=2)
        {
            if (rand() % 4)
            {
                int pixcolor = rand() % 2; //0 - пустота, 1 - кирпич
                int doublepixcolor = (pixcolor + (rand() % 2)) * pixcolor; //0 - пустота, 1 - кирпич, 2 - трава
                field[i][j] = doublepixcolor;
                field[i][j+1] = doublepixcolor;
                field[i+1][j] = doublepixcolor;
                field[i+1][j+1] = doublepixcolor;
            }
            else
            {
                field[i][j] = field[i-1][j];
                field[i+1][j] = field[i-1][j];
                field[i][j+1] = field[i-1][j+1];
                field[i+1][j+1] = field[i-1][j+1];
            }
        }
    }

    for (auto m = 0; m < 44; ++m)
        for (auto n = 0; n < 24; ++n)
        {
            if (field[m][n] == 0)
                changeField("road" + QString::number(rand() % 5 + 1), QString::number(m*24 + n));

            if (field[m][n] == 1)
                changeField("firebrick5", QString::number(m*24 + n));

            if (field[m][n] == 1 && field[m-1][n] != 1)
                changeField("firebrick2", QString::number(m*24 + n));
            if (field[m][n] == 1 && field[m+1][n] != 1)
                changeField("firebrick8", QString::number(m*24 + n));
            if (field[m][n] == 1 && field[m][n-1] != 1)
                changeField("firebrick4", QString::number(m*24 + n));
            if (field[m][n] == 1 && field[m][n+1] != 1)
                changeField("firebrick6", QString::number(m*24 + n));

            if (field[m][n] == 1 && field[m-1][n] != 1 && field[m][n-1] != 1)
                changeField("firebrick1", QString::number(m*24 + n));
            if (field[m][n] == 1 && field[m+1][n] != 1 && field[m][n+1] != 1)
                changeField("firebrick9", QString::number(m*24 + n));
            if (field[m][n] == 1 && field[m][n-1] != 1 && field[m+1][n] != 1)
                changeField("firebrick7", QString::number(m*24 + n));
            if (field[m][n] == 1 && field[m][n+1] != 1 && field[m-1][n] != 1)
                changeField("firebrick3", QString::number(m*24 + n));

            if (field[m][n] == 2)
            {
                changeField("road" + QString::number(rand() % 5 + 1), QString::number(m*24 + n));
                trees.append(treeID);
                QObject* mmm = this->parent()->findChild<QObject*>("mmm");
                QMetaObject::invokeMethod(mmm, "createtree", Q_ARG(QVariant, QString::number(m*24 + n)), Q_ARG(QVariant, "t"+ QString::number(treeID)));
                //очень важная херабора в две строки, ей можно делать реплэйсмент координат и смену сурсов тайлов
                QObject* treee = this->parent()->findChild<QObject*>("t" + QString::number(treeID));
                treee->children()[0]->children()[0]->setProperty("source", "qrc:/tree" + QString::number(rand() % 4 + 1) + ".png");
                treeID++;
            }
        }

    QObject* mmm = this->parent()->findChild<QObject*>("mmm");
    QMetaObject::invokeMethod(mmm, "createsorcerers");
}
