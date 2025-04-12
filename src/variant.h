#ifndef VARIANT_H
#define VARIANT_H

#define ARG char **argv, int &argi, const int &argc

class CVariant
{
public:
    virtual bool get(ARG) = 0;
    virtual const char* key() = 0;
    virtual bool checkAfter() = 0;

    CVariant() = default;
    virtual ~CVariant() = default;
};

template <class T> class V : public CVariant
{
private:
    typedef bool (T::*Func)(ARG);

    const char* mKey = nullptr;
    const bool mArgumentAfter;
    Func mFunc = nullptr;
    T* mObj = nullptr;

    bool get(ARG) override
    {
        return (mObj->*mFunc)(argv, argi, argc);
    }

    const char* key() override
    {
        return mKey;
    }

    bool checkAfter() override
    {
        return mArgumentAfter;
    }

public:
    V(const char* key, const bool argumentAfter, Func func, T* obj)
        : mKey(key)
        , mArgumentAfter(argumentAfter)
    {
        mFunc = func;
        mObj = obj;
    }
};

#endif // VARIANT_H