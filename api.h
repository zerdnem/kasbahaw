#include <iostream>

#include <curl/curl.h>
#include <json/json.h>

using namespace std;

namespace
{
    size_t cb(
            const char* in,
            size_t size,
            size_t num,
            string* out)
    {
        const size_t totalBytes(size * num);
        out->append(in, totalBytes);
        return totalBytes;
    };
}

struct Api
{
    static void fetch(string url, string api)
    {
        int httpCode = 0;
        struct curl_slist *chunk = NULL;
        CURL* curl = curl_easy_init();
        chunk = curl_slist_append(chunk, "User-Agent: sickmyduck");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_IPRESOLVE, CURL_IPRESOLVE_V4);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        string *httpData(new string());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, cb);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, httpData);
        curl_easy_perform(curl);
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpCode);
        curl_easy_cleanup(curl);

        if (httpCode == 200)
        {
            Json::Value jsonData;
            Json::Reader jsonReader;

            if (jsonReader.parse(*httpData, jsonData))
            {
                if (api == "social") {
                    const string instagram(jsonData["instagram"].asString());
                    const string twitter(jsonData["twitter"].asString());
                    const string snapchat(jsonData["snapchat"].asString());
                    const string facebook(jsonData["facebook"].asString());
                    const string youtube(jsonData["youtube"].asString());
                    const string google(jsonData["google"].asString());
                    const string twitch(jsonData["twitch"].asString());
                    cout << "[+] Facebook:\t\t" << facebook << endl;
                    cout << "[+] Instagram:\t\t" << instagram << endl;
                    cout << "[+] Twitter:\t\t" << twitter << endl;
                    cout << "[+] Snapchat:\t\t" << snapchat << endl;
                    cout << "[+] Youtube:\t\t" << youtube << endl;
                    cout << "[+] Google:\t\t" << google << endl;
                    cout << "[+] Twitch:\t\t" << twitch << endl;
                } else if (api == "hibp") 
                {
                    //pwned
                    cout << "[+] Pwned:\t\ttrue" << endl;
                } 
                else if (api == "api1")
                {
                    if (jsonData["error"] != 0) 
                    {
                        cout << "[-] " << jsonData["error"].asString() << endl;
                    } else {

                        //verifiy 1
                        cout << "[+] Available: " << jsonData["message"] << endl;
                    }
                }
                else if (api == "api2")
                {

                    //TODO: show error
                        //verify 2
                        cout << "[+] Address:\t\t" << jsonData["address"].asString() << endl;
                        cout << "[+] Username:\t\t" << jsonData["username"].asString() << endl;
                        cout << "[+] Domain:\t\t" << jsonData["domain"].asString() << endl;
                        cout << "[+] Deliverable:\t" << jsonData["deliverable"].asString() << endl;
                        cout << "[+] Host Exists:\t" << jsonData["hostExists"].asString() << endl;

                }
                else if (api == "api3")
                {
                    //TODO: show error
                    //spam
                    const string isSpam(jsonData["spam"].asString());
                    cout << "[+] Spam:\t\t" << isSpam << endl;
                    //disposable
                    const string isDisposable(jsonData["disposable"].asString());
                    cout << "[+] Disposable:\t\t" << isDisposable << endl;
                    //scam
                    const string isScam(jsonData["scam"].asString());
                    cout << "[+] Scam:\t\t" << isScam << endl;
                    //free_provider
                    const string isFreeProvider(jsonData["free_provider"].asString());
                    cout << "[+] Free Provider:\t" << isFreeProvider << endl;
                }
            } 
            else 
            {
                //cout << "[-] Could not parse HTTP data as JSON" << endl;
            }
        }
        else
        {
            //cout << "[-] Couldn't GET from " << url << endl;
        }
    }
};
