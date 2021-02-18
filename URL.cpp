#include "URL.hpp"
#include <iostream>
#include <curl/curl.h>
#include <cstring>

using namespace std;

URL::URL(string stringURL)
{
    this->stringURL = stringURL;
    this->charURL = &this->stringURL[0];
}

string contents = "";

size_t handle_data(void *ptr, size_t size, size_t nmemb, void *stream)
{
    contents.append((char *)ptr);
    return size*nmemb;
}

string URL::getContents()
{
    CURL* curl = curl_easy_init();
    if(curl)
    {
        curl_easy_setopt(curl,CURLOPT_URL, this->charURL);
        curl_easy_setopt(curl,CURLOPT_WRITEFUNCTION,handle_data);
        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
        if (res == 0) //if the error code is 0, everything went well
        {
            return contents;
        }
        else
        {
            cerr << "Error: " << res << endl;
        }
    }
    return "";
}