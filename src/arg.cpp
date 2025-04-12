#include "arg.h"

CArg* CArg::mInstance = nullptr;

CArg::CArg()
{
    addKey(new V("-i", true, &CArg::addInput, this));
    addKey(new V("-e", true, &CArg::addException, this));
    addKey(new V("-p", true, &CArg::setPath, this));
    addKey(new V("-t", false, &CArg::setCmp, this));

    mPath = new char[SIZE_BUFFER] { '.' };
    mObjKey = mListKey[0];

    mListException.push_back(".");
    mListException.push_back("..");

    mCmpFunc = cmpName;
}

CArg::~CArg()
{
    for(auto& p : mListKey)
        delete p;
}

CArg* CArg::getInstance()
{
    if(mInstance == nullptr)
        mInstance = new CArg();
    return mInstance;
}

bool CArg::find(const char* value, const char* sub, int& findBegin, int& findEnd)
{
    while(*value != '\0') {
        if((findEnd = mCmpFunc(value++, sub)) != -1) {

            findEnd += findBegin - 1;
            return true;
        }

        findBegin++;
    }

    return false;
}

int CArg::cmpType(const char* a, const char* b)
{
    int i = 0;

    for(; a[i] != '\0'; i++)
        if(a[i] != b[i] || a[i + 1] != b[i + 1])
            return -1;

    return i;
}

int CArg::cmpName(const char* a, const char* b)
{
    int i = 0;

    for(; b[i] != '\0'; i++)
        if(a[i] != b[i])
            return -1;

    return i;
}

void CArg::addKey(CVariant* variant)
{
    mListKey.push_back(variant);
}

CVariant* CArg::getKey(const char* value, bool& findKey)
{
    findKey = false;

    for(auto& p : mListKey) {
        if(cmpName(p->key(), value) != -1) {
            mObjKey = p;
            findKey = true;
            break;
        }
    }

    return mObjKey;
}

char* CArg::getPath()
{
    return mPath;
}

// -----------------------------------------------------------------------

bool CArg::checkInput(const char* value, int& findBegin, int& findEnd)
{
    for(auto& p : mListInput) {
        findBegin = 0;
        findEnd = 0;
        if(find(value, p, findBegin, findEnd) == true)
            return true;
    }

    return false;
}

bool CArg::checkException(const char* name)
{
    for(auto& p : mListException)
        if(cmpName(name, p) != -1)
            return false;

    return true;
}

// -----------------------------------------------------------------------

bool CArg::addException(ARG)
{
    mListException.push_back(argv[argi]);
    return false;
}

bool CArg::addInput(ARG)
{
    mListInput.push_back(argv[argi]);
    return false;
}

bool CArg::setPath(ARG)
{
    for(int i = 0; argv[argi][i] != '\0'; i++)
        mPath[i] = argv[argi][i];
    return true;
}

bool CArg::setCmp(ARG)
{
    mCmpFunc = cmpType;
    return true;
}