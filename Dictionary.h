#ifndef MATCHFINDER_H
#define MATCHFINDER_H

#include <QFile>
#include <QObject>
#include <QVector2D>

#include "Range.h"

class Dictionary : public QObject
{
public:
    Dictionary(const QByteArray& data, QObject* parent = nullptr);
    Dictionary(const QString& filePath, QObject* parent = nullptr);

    ~Dictionary();

    QStringList find(const QString& pattern, const Range& range) const;
    QStringList find(const QString& pattern, int begin, int end) const;

    int size() const;

private:
    Dictionary(QFile* sourceFile, QObject* parent = nullptr);

    Range defineSearchRange(const Range& range) const;
    Range defineWordRange(int pos) const;

    QByteArray mData;
    QFile* mSourceFile = nullptr;
};

#endif // MATCHFINDER_H
