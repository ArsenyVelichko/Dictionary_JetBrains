#ifndef RANGE_H
#define RANGE_H

class Range {
public:
    Range();
    Range(int begin, int end);

    int begin() const;
    int end() const;

    int length() const;
    int isValid() const;

private:
    int mBegin;
    int mEnd;
};

#endif // RANGE_H
