#include "Common.h"
#include <assert.h>

char *Common::fileRead(const char *file_name)
{
    SDL_RWops *rw = SDL_RWFromFile(file_name, "rb");
    if (rw == nullptr) return nullptr;

    Sint64 res_size = SDL_RWsize(rw);
    char *res = (char *)malloc(res_size + 1);

    Sint64 nb_read_total = 0, nb_read = 1;
    char *buf = res;
    while (nb_read_total < res_size && nb_read != 0) {
        nb_read = SDL_RWread(rw, buf, 1, (res_size - nb_read_total));
        nb_read_total += nb_read;
        buf += nb_read;
    }
    SDL_RWclose(rw);
    if (nb_read_total != res_size) {
        free(res);
        return nullptr;
    }
    // Modulo 5 - Comportamento default
    else {
        // There's nothing to do
    }

    res[nb_read_total] = '\0';
    return res;
}

void Common::readJson(json &j, const std::string &file)
{
    char *data = Common::fileRead(file.c_str());
    if (data == nullptr) exit(0);
    // Modulo 5 - Comportamento default
    else {
        // There's nothing to do
    }

    j = json::parse(data, data + strlen(data));
    free(data);
}