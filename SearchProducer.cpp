#include "SearchProducer.h"

SearchProducer::SearchProducer(const Dictionary* dictionary,
                               int searchLen, QObject* parent)
    : QThread(parent), mDictionary(dictionary), mSearchLen(searchLen) {}

void SearchProducer::setPattern(const QString &pattern)
{
    mPattern = pattern;
}

void SearchProducer::run()
{
    int chunkNumber = (mDictionary->size() + mSearchLen - 1) / mSearchLen;
    int currChunk = 0;

    while (currChunk < chunkNumber)  {
        int searchBegin = currChunk * mSearchLen;
        int searchEnd = searchBegin + mSearchLen;
        QStringList searchResult = mDictionary->find(mPattern, searchBegin, searchEnd);

        QString resultStr = searchResult.join('\n');

        currChunk++;
        if (resultStr.isEmpty()) { continue; }

        mPreparedChunk = resultStr;

        mLock.lock();
        emit chunkReady();
        mReceivedCondition.wait(&mLock);
        mLock.unlock();

        if (isInterruptionRequested()) { break; }
    }
}

QString SearchProducer::getChunk()
{
    mLock.lock();
    QString chunk = mPreparedChunk;
    mReceivedCondition.wakeOne();
    mLock.unlock();
    return chunk;
}
