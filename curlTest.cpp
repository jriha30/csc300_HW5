#include <string>
#include <iostream>
#include <curl/curl.h>

using namespace std;

//
// For this demonstration, the contents of the web page are put
// into this global variable.
//
string contents = "";

//
// This is the callback function that is called by
// curl_easy_perform(curl)
//
size_t handle_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
    //make it so ptr can be treated as a modern string
    int numbytes = size*nmemb;
    // The data is not null-terminated, so get the last character, and replace
    // it with '\0'.
    char lastchar = *((char *) ptr + numbytes - 1);
    *((char *) ptr + numbytes - 1) = '\0';
    //end of ptr manipulation to make it work as a modern string

    contents.append((char *)ptr);
    contents.append(1,lastchar);
    *((char *) ptr + numbytes - 1) = lastchar;  // Might not be necessary.
    return size*nmemb;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cerr << "use: curltest url\n";
        return -1;
    }

    CURL* curl = curl_easy_init();
    if(curl) //if the variable has something in it
    {
        // Tell libcurl the URL
        curl_easy_setopt(curl,CURLOPT_URL, argv[1]);
        // Tell libcurl what function to call when it has data
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,handle_data); //what function should I "callback" when I get data
        // Do it!
        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        if (res == 0) //if the error code is 0, everything went well
        {
            cout << contents << endl;

            string temp = "";
            for(int i = 0; i < 5; i++)
            {
                temp += contents[i];
            }
            cout << temp << endl;
        }
        else
        {
            cerr << "Error: " << res << endl;
        }
    }
    return 0;
}