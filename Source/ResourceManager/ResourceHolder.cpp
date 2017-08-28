#include "ResourceHolder.h"

ResourceHolder& ResourceHolder::get()
{
    static ResourceHolder holder;
    return holder;
}

ResourceHolder::ResourceHolder()
:   fonts           ("Fonts", "ttf")
,   textures        ("Textures", "png")
{ }
