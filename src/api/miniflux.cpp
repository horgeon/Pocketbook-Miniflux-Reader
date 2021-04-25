//------------------------------------------------------------------
// miniflux.cpp
//
// Author:           JuanJakobo
// Date:             22.04.2021
//
//-------------------------------------------------------------------

#include "miniflux.h"

Miniflux::Miniflux(const string &url, const string &token) : _url(url), _token(token)
{
}

vector<entry> Miniflux::getEntries()
{
    nlohmann::json j = get("/v1/entries?starred=true&direction=desc");

    vector<entry> tempItems;

    for (auto &element : j["entries"].items())
    {
        tempItems.push_back({element.value()["id"],
                             element.value()["title"],
                             element.value()["url"],
                             element.value()["comments_url"],
                             element.value()["content"]});
    }
    return tempItems;
}

nlohmann::json Miniflux::get(const string &api)
{
   //TODO test if url and token are empty

    string url = _url + api;

    Log::writeLog(url);
    
    string readBuffer;
    CURLcode res;
    CURL *curl = curl_easy_init();

    if (curl)
    {

        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, ("X-Auth-Token: " + _token).c_str());
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, Util::writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if (res == CURLE_OK)
        {
            long response_code;
            curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);

            //TODO catch further responses
            switch (response_code)
            {
            case 200:
                return nlohmann::json::parse(readBuffer);
            default:
                Log::writeLog("Curl Response Code" + std::to_string(response_code));
            }
        }
        else
        {
            Log::writeLog("Error Code "  + std::to_string(res));
        }
    }
    //TODO write error code here ?
    return {};
}