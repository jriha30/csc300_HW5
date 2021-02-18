#include <iostream>
#include "URL.hpp"

using namespace std;
int main(int argc, char** argv)
{
    URL* u1 = new URL("https://www.google.com/");
    URL* u2 = new URL("https://www.yahoo.com");
    URL* u3 = new URL("https://api.hearthstonejson.com/v1/25770/enUS/cards.json");
    cout << u1->getContents() << endl;
    cout << u2->getContents() << endl;
}