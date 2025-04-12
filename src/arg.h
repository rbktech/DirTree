#ifndef SINGLETON_H
#define SINGLETON_H

#include <vector>

#include "variant.h"

#define SIZE_BUFFER 250

class CArg
{
private:
    CArg(const CArg&) = default;
    CArg& operator=(const CArg&) = default;

    static CArg* mInstance;

    CVariant* mObjKey;

    std::vector<CVariant*> mListKey;
    std::vector<const char*> mListInput;
    std::vector<const char*> mListException;
    char* mPath;

    CArg();
    ~CArg();

    bool addInput(ARG);
    bool addException(ARG);
    bool setPath(ARG);
    bool setCmp(ARG);

    bool find(const char* value, const char* sub, int& findBegin, int& findEnd);

    int (*mCmpFunc)(const char*, const char*);

public:
    static CArg* getInstance();

    void addKey(CVariant* variant);

    CVariant* getKey(const char* value, bool& findKey);

    char* getPath();

    bool checkInput(const char* value, int& findBegin, int& findEnd);

    bool checkException(const char* name);

    static int cmpType(const char* a, const char* b);
    static int cmpName(const char* a, const char* b);
};

#endif // SINGLETON_H