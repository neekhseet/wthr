#include "http.h"
#include "content.h"
#include <curl/curl.h>

char *http_get(const char *url)
{
    CURL *curl = curl_easy_init();
    if (!curl)
        return NULL;

    struct MemoryStruct chunk = {.memory = malloc(1), .size = 0};
    if (!chunk.memory)
    {
        curl_easy_cleanup(curl);
        return NULL;
    }
    chunk.memory[0] = '\0';

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &chunk);
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

    CURLcode res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK)
    {
        fprintf(stderr, "GET %s failed: %s\n", url, curl_easy_strerror(res));
        free(chunk.memory);
        return NULL;
    }
    return chunk.memory;
}