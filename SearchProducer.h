#ifndef SEARCHWORKER_H
#define SEARCHWORKER_H

#include <QMutex>
#include <QThread>
#include <QWaitCondition>

#include "Dictionary.h"

class SearchProducer : public QThread
{
    Q_OBJECT
public:
    SearchProducer(const Dictionary* dictionary,
                   int searchLen,
                   QObject* parent = nullptr);

    void setPattern(const QString& pattern);

    void run() override;

    QString getChunk();
    void cancel();

signals:
    void chunkReady();

private:
    const Dictionary* mDictionary;
    QString mPattern;
    int mSearchLen;

    QString mPreparedChunk;
    QWaitCondition mReceivedCondition;
    QMutex mLock;
};
#endif // SEARCHWORKER_H
