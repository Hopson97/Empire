#ifndef RANDOM_H_INCLUDED
#define RANDOM_H_INCLUDED

#include <random>

class Random
{
    public:
        static Random& get();

        Random              (const Random& other)    = delete;
        Random& operator=   (const Random& other)   = delete;

        int intInRange(int low, int high);
        float floatInRange(float low, float high);

    private:
        Random();

        std::mt19937 m_rng;
};

#endif // RANDOM_H_INCLUDED
