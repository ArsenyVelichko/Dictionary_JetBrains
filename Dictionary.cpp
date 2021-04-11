#include "Dictionary.h"

#include <QByteArrayMatcher>

Dictionary::Dictionary(const QByteArray& data, QObject* parent)
    : QObject(parent), mData(data) {}

Dictionary::Dictionary(const QString &filePath, QObject *parent)
    : QObject(parent)
{
    mSourceFile = new QFile(filePath);
    if (!mSourceFile->open(QFile::ReadOnly)) { return; }

    qint64 size = mSourceFile->size();

    uchar* rawData = mSourceFile->map(0, size);
    mData = QByteArray::fromRawData((char*)rawData, size);
}

Dictionary::~Dictionary()
{
    delete mSourceFile;
}

QStringList Dictionary::find(const QString& pattern, const Range& range) const
{
    QStringList words;
    if (pattern.isEmpty()) { return words; }

    const auto& searchRange = defineSearchRange(range);
    if (!searchRange.isValid()) { return words; }

    QByteArrayMatcher matcher(pattern.toLatin1());
    const char* rawData = mData.constData();

    int currBegin = searchRange.begin();
    while (true) {
        int foundIdx = matcher.indexIn(rawData, searchRange.end(), currBegin);

        if (foundIdx == -1) { break; }

        const auto& wordRange = defineWordRange(foundIdx);
        QString word = mData.mid(wordRange.begin(), wordRange.length());
        if (word.endsWith('\r')) { word.chop(1); }

        words.append(word);

        currBegin = wordRange.end() + 1;
    }
    return words;
}

QStringList Dictionary::find(const QString& pattern, int begin, int end) const
{
    return find(pattern, Range(begin, end));
}

int Dictionary::size() const
{
    return mData.size();
}

Range Dictionary::defineSearchRange(const Range& range) const
{
    int chunkBegin = 0;
    if (range.begin() > 0) {
        chunkBegin = mData.indexOf('\n', range.begin());

        if (chunkBegin == -1) { return Range(); }
        chunkBegin++;
    }

    int chunkEnd = mData.indexOf('\n', range.end());
    if (chunkEnd == -1) {
        chunkEnd = mData.size();
    }

    return Range(chunkBegin, chunkEnd);
}

Range Dictionary::defineWordRange(int pos) const
{
    if (pos < 0 || pos >= mData.size()) { return Range(); }

    int wordBegin = mData.lastIndexOf('\n', pos);
    wordBegin++;

    int wordEnd = mData.indexOf('\n', pos);
    if (wordEnd == -1) {
        wordEnd = mData.size();
    }

    return Range(wordBegin, wordEnd);
}
