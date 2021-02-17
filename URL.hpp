#include <string>

using namespace std;

class URL
{
    private:
        string stringURL;
        char* charURL;

    public:
        URL(string stringURL);
        string getContents();
};