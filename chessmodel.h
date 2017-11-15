#ifndef CHESSMODEL_H
#define CHESSMODEL_H

#include <QObject>
#include <QQmlListProperty>
#include <QMap>

class Figure;

class ChessModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<Figure> data READ data NOTIFY dataChanged)
    Q_CLASSINFO("DefaultProperty", "data")
public:
    ChessModel(QObject *parent = 0);
    QQmlListProperty<Figure> data();
    Q_INVOKABLE void add(Figure *figure);
    void clear();

signals:
    void dataChanged();

private:
    static void appendData(QQmlListProperty<Figure> *list, Figure *value);
    static int countData(QQmlListProperty<Figure> *list);
    static Figure *atData(QQmlListProperty<Figure> *list, int index);
    static void clearData(QQmlListProperty<Figure> *list);

    QList<Figure*> m_data;
};


#endif
