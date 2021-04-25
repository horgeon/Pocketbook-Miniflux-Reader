//------------------------------------------------------------------
// util.h
//
// Author:           JuanJakobo
// Date:             04.08.2020
// Description:      Various utility methods
//-------------------------------------------------------------------

#ifndef UTIL
#define UTIL

#include "inkview.h"
#include "eventHandler.h"

#include <string>

using std::string;

class Util
{
public:
    /**
    * Handles the return of curl command
    * 
    */
    static size_t writeCallback(void *contents, size_t size, size_t nmemb, void *userp);

    /**
    * Saves the return of curl command
    * 
    */
    static size_t writeData(void *ptr, size_t size, size_t nmemb, FILE *stream);

    /**
    * Checks if a network connection can be established
    * 
    * @return true - network access succeeded, false - network access failed
    */
    static bool connectToNetwork();

    /**
    * Reads an string from the config file 
    *
    * @param name name of the config that shall be read
    *  
    * @return string that has been found in the config file 
    */
    static string readFromConfig(string name);

private:
    Util() {}
};
#endif