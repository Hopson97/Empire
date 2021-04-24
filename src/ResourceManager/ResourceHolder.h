#ifndef RESOURCEHOLDER_H_INCLUDED
#define RESOURCEHOLDER_H_INCLUDED

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "../Util/NonCopyable.h"
#include "../Util/NonMoveable.h"
#include "ResourceManager.h"

class ResourceHolder : public NonCopyable, public NonMovable {
  public:
    static ResourceHolder& get();

    ResourceManager<sf::Font> fonts;
    ResourceManager<sf::Texture> textures;

  private:
    ResourceHolder();
};

#endif // RESOURCEHOLDER_H_INCLUDED
