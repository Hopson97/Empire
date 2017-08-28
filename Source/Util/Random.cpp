#include "Random.h"

#include <ctime>

Random& Random::get()
{
    static Random r;
    return r;
}

Random::Random()
{
    m_rng.seed (std::time(nullptr));
}

int Random::intInRange(int low, int high)
{
    std::uniform_int_distribution<int> dist(low, high);
    return dist(m_rng);
}

float Random::floatInRange(int low, int high)
{
    std::uniform_real_distribution<float> dist(low, high);
    return dist(m_rng);
}
