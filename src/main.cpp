#include <dirent.h>
#include <windows.h>

#include "arg.h"

#include <string>

enum ConsoleColor {
    Black = 0,
    Blue = 1,
    Green = 2,
    Cyan = 3,
    Red = 4,
    Magenta = 5,
    Brown = 6,
    LightGray = 7,
    DarkGray = 8,
    LightBlue = 9,
    LightGreen = 10,
    LightCyan = 11,
    LightRed = 12,
    LightMagenta = 13,
    Yellow = 14,
    White = 15
};

void SetTextColor(ConsoleColor text, ConsoleColor background = Black)
{
    HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsoleHandle, (WORD)((background << 4) | text));
}

/*short row = 0;

void SetPosition(const short& x, const short& y)
{
    COORD coord { x, y };
    HANDLE hConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsoleHandle, coord);
}*/

bool round(char* path)
{
    int iBegin = 0;
    int iEnd = 0;

    int iPath = 0;
    int iName = 0;
    DIR* dir = nullptr;
    struct dirent* ent = nullptr;

    // std::string list_files;

    if((dir = opendir(path)) != nullptr) {

        for(; dir->dd_name[iPath] != '*'; iPath++)
            path[iPath] = dir->dd_name[iPath];

        while((ent = readdir(dir)) != nullptr) {

            if(CArg::getInstance()->checkException(ent->d_name) == true) {

                // std::string dd = dir->dd_name;
                // std::string d = ent->d_name;

                for(iName = 0; ent->d_name[iName] != '\0'; iName++, iPath++)
                    path[iPath] = ent->d_name[iName];

                if(round(path) == false && CArg::getInstance()->checkInput(ent->d_name, iBegin, iEnd) == true) {

                    iBegin = iPath - iName + iBegin;
                    iEnd = iPath - iName + iEnd;

                    for(int i = 0; path[i] != '\0'; i++) {

                        if(i == iBegin)
                            SetTextColor(Green);

                        printf("%c", path[i]);

                        if(i == iEnd)
                            SetTextColor(White);
                    }
                    printf("\n");

                    // list_files.append(path);
                    // list_files.append("\n");
                }

                for(; iName != 0; iName--)
                    path[--iPath] = '\0';
            }
        }

        path[--iPath] = '\0';

        // printf("%s", list_files.data());

        closedir(dir);

        return true;
    }

    return false;
}

class CPrint
{
private:
    int (*mFuncClose)(const char*) = nullptr;

public:
    int endApp()
    {
        if(mFuncClose != nullptr)
            mFuncClose("PAUSE");

        return 0;
    }

    bool help(ARG)
    {
        printf("-i\tinput files\n");
        printf("-e\texclude folder\n");
        printf("-p\tpath dir\n");
        printf("-t\tfind type\n");
        printf("-c\tdo not close console\n");

        printf("-h\thelp\n");

        // printf("-d  dir\n");
        // printf("-t  type\n");
        // printf("-n  name\n");
        // printf("-pn path name\n");
        // printf("-np name path\n");

        return true;
    }

    bool closeConsole(ARG)
    {
        mFuncClose = &system;
        return true;
    }

} gPrint;

int main(int argc, char** argv)
{
    bool findKey = false;

    CArg::getInstance()->addKey(new V("-h", false, &CPrint::help, &gPrint));
    CArg::getInstance()->addKey(new V("-c", false, &CPrint::closeConsole, &gPrint));

    for(int i = 1; i < argc; i++) {

        const char* keyArg = argv[i];

        CVariant* objKey = CArg::getInstance()->getKey(argv[i], findKey);

        if(objKey != nullptr) {

            const char* keyCurrent = objKey->key();

            // if(CArg::cmp(keyArg, keyCurrent) == false && objKey->checkAfter() == false)
            // printf("false && false\n");

            if(CArg::cmpName(keyArg, keyCurrent) == -1 && objKey->checkAfter() == true)
                objKey->get(argv, i, argc);

            if(CArg::cmpName(keyArg, keyCurrent) != -1 && objKey->checkAfter() == false)
                objKey->get(argv, i, argc);

            // if(CArg::cmp(keyArg, keyCurrent) == true && objKey->checkAfter() == true)
            // printf("true && true\n");
        }

        // 1 - add input lll -i true
        // 2 - close console -c -c false
        // 3 - next -i -i true
        // 4 - add input .txt -i true
        // 5 - next -p -p true
        // 6 - add path test -p true
        // 7 - next -e -e true
        // 8 - add exclude go -e true
    }

    if(round(CArg::getInstance()->getPath()) == false)
        printf("error: open dir");

    return gPrint.endApp();
}