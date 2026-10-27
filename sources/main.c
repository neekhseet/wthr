#include <stdio.h>
#include <curl/curl.h>
#include "cJSON.h"
#include "http.h"
#include "content.h"

int main(void)
{
    int rc = 1;
    curl_global_init(CURL_GLOBAL_ALL);

    char *ip_body = http_get("http://ip-api.com/json/");
    if (!ip_body)
        goto out;

    cJSON *ip = cJSON_Parse(ip_body);
    free(ip_body);
    if (!ip)
    {
        fprintf(stderr, "bad ip-api JSON\n");
        goto out;
    }

    const cJSON *lat = cJSON_GetObjectItemCaseSensitive(ip, "lat");
    const cJSON *lon = cJSON_GetObjectItemCaseSensitive(ip, "lon");
    const cJSON *city = cJSON_GetObjectItemCaseSensitive(ip, "city");

    if (!cJSON_IsNumber(lat) || !cJSON_IsNumber(lon))
    {
        fprintf(stderr, "no coordinates in ip-api response\n");
        cJSON_Delete(ip);
        goto out;
    }

    printf(
        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⠀\n"
        "⠀⠀⠀⠀⠀⠀⠠⠠⡰⠐⠕⢀⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
        "⠀⠀⠀⡀⣠⠶⡊⠃⠀⠀⠀⠀⢈⡁⢀⡀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⣄⢄⢤⡀\n"
        "⠀⠀⣄⠇⠁⠀⠀⠀⠀⠀⠀⠀⠠⠎⠀⠀⠈⠑⣄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠀⣴⠋⠀⠀⠀⠀\n"
        "⠀⠂⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⠟⠕⠦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠤⢆⡋⠰⠸⠗⠀⠀⠀⠀⠀\n"
        "⡁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢼⣱⠁⠀⠀⠀⠀⢀⢠⠏⠒⠀\n"
        "⠁⠐⠐⠄⠀⠀⠀⠀⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡀⠖⠛⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⠰⠺⡁⡛⠁⠀⠀⠀⠀⣜⠀⠀⠀⠀⠀\n"
        "⠀⠀⠀⠙⠁⠄⠆⡸⠓⡆⠠⠀⠀⢀⡞⠤⠠⠐⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⠐⡷⡾⡃⠉⠀⠀⠀⠀⠀⢠⠰⠰⢇⠨⠦⡵⠀⠀\n"
        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠀⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣴⠋⠉⠀⠉⠟⠀⠀⠀⠀⣄⡃⠉⠀⠀⠀⠀⠀⠀⠁⠀⠀\n"
        "⠀⠀⠀⡀⠀⡀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠠⢅⠃⠀⠀⠀⠀⠀⠀⠀⠀⣠⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
        "⡀⡵⠁⠁⠉⠘⠁⢢⣰⠀⠄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠽⣯⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
        "⠁⠀⠀⠀⠀⠀⠀⠀⠀⠉⣥⡕⢀⠀⡀⢀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠪⡯⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠊⡟⠭⠊⠊⠉⠓⠥⠰⡀⠀⠀⠀⠀⠀⠀⠀⠐⡅⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
        "⡄⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⢯⠄⠀⠀⡀⠀⠀⠀⠀⠉⣦⠄⠠⠠⠠⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
        "⠉⠋⠻⢖⣤⢥⡦⣤⠷⣀⢄⡀⠀⠀⠀⠀⠀⠀⣰⡽⠃⠈⠁⠙⠁⣅⡠⠀⠀⠀⠀⠀⠀⠁⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
        "⠀⢀⣿⠃⠁⠀⠀⠀⠀⠀⠉⠛⠯⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⢎⠂⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡀⠀⣀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠄⡈⠡⢁⡀⡄⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣔⣝⣃⠭⠓⠊⠋⠛⠿⠀⠀⠀⠀⠀⠉⠀⠀⠀⠀⠀⠀⠙⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n"
        "⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
    double la = lat->valuedouble, lo = lon->valuedouble;
    printf("City: %s\n",
           cJSON_IsString(city) ? city->valuestring : "?");
    cJSON_Delete(ip);

    char url[512];
    snprintf(url, sizeof url,
             "https://api.open-meteo.com/v1/forecast"
             "?latitude=%.4f&longitude=%.4f"
             "&current=temperature_2m,relative_humidity_2m,wind_speed_10m"
             "&wind_speed_unit=ms&timezone=auto",
             la, lo);

    char *w_body = http_get(url);
    if (!w_body)
        goto out;

    cJSON *w = cJSON_Parse(w_body);
    free(w_body);
    if (!w)
    {
        fprintf(stderr, "bad open-meteo JSON\n");
        goto out;
    }

    const cJSON *cur = cJSON_GetObjectItemCaseSensitive(w, "current");
    const cJSON *temp = cJSON_GetObjectItemCaseSensitive(cur, "temperature_2m");
    const cJSON *hum = cJSON_GetObjectItemCaseSensitive(cur, "relative_humidity_2m");
    const cJSON *wind = cJSON_GetObjectItemCaseSensitive(cur, "wind_speed_10m");

    if (cJSON_IsNumber(temp))
        printf("Temperature: %.1f °C\n", temp->valuedouble);
    if (cJSON_IsNumber(hum))
        printf("Humidity:   %.0f %%\n", hum->valuedouble);
    if (cJSON_IsNumber(wind))
        printf("Wind:       %.1f m/s\n", wind->valuedouble);

    cJSON_Delete(w);
    rc = 0;

out:
    curl_global_cleanup();
    return rc;
}