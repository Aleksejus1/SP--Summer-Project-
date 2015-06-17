#ifndef ITEM_H
#define ITEM_H
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "SDL_syswm.h"
#include <tchar.h>
#include <windows.h>
#include <stdio.h>
#include <string>
#include <memory.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <cmath>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <commdlg.h>
#include "layer.h"

class item
{
    public:
        item();
        layer image;
        friend bool operator==(item &a, item &b);
        std::string name;
        std::string type;
        float damage;
        struct affect{std::string statName; float ammount;};
        std::vector<affect> affectedStats;
        void reset();
};

#endif // ITEM_H
