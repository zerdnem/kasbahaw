//Compile with g++ check.cpp -ljsoncpp -lcurl verify
#include <iostream>
#include <map> 

#include "api.h"

using namespace std;

struct M
{
    static map<string, string> g()
    {
        map<string, string> m;
        m["social"] = "http://35.197.145.18:5000/api?email=";
        m["hibp"] = "https://haveibeenpwned.com/api/v2/breachedaccount/";
        //m["api1"] = "https://y78n51qcpj.execute-api.us-east-1.amazonaws.com/dev?to_email="; //slow
        m["api2"] = "https://api.trumail.io/v2/lookups/json?email=";
        m["api3"] = "https://api.antideo.com/email/";
        return m;
    }
    static const map<string, string> a;
    static void usage(string n)
    {
        //TODO: add usage
        cerr << "Usage: " << n << " <option(s)> EMAIL\n" 
            << "Options:\n"
            << "\t-h, --help\t\tShow this help message\n"
            << "\t-d, --email EMAIL\tEmail address you want to check"
            << endl;

    }
};


void get(string url, string api, string email)
{
    string furl;
    if (api == "social") {
        //cout << "[!] Running email-enum...this may take a while." << endl;
        furl = url + email;
        Api::fetch(furl, api);
    } else if (api == "hibp") {
        furl = url;
        Api::fetch(furl, api);
    } else {
        furl = url + email;
        Api::fetch(furl, api);
    }
}

int main(int argc, char *argv [])
{
    map<string, string> nm;
    nm = M::g();
    if (argc < 3) {
        M::usage(argv[0]);
        return 1;
    }
    string arg = argv[1];

    if (arg == "-h" || arg == "--help") {
        M::usage(argv[0]);
        return 0;
    } else if (arg == "-e" || arg == "--email") {
        string email = argv[2];
        map<string, string>::iterator u = nm.begin();
        while(u != nm.end())
        {
            get(u->second, u->first, email);
            u++;
        }
    }

    return 0;
}
