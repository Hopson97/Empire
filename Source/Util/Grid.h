#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

#include <vector>

template<typename T>
class Grid
{
    public:
        Grid(unsigned width, unsigned height): m_width(width), m_height(height), m_data(width*height) {}
        
        unsigned width() const { return m_width; }
        unsigned height() const { return m_height; }
        
        T& operator()(unsigned x, unsigned y) { return m_data[y * m_width + x]; }
        const T& operator()(unsigned x, unsigned y) const { return m_data[y * m_width + x]; }
        
    private:
        unsigned        m_width;
        unsigned        m_height;
        std::vector<T>  m_data;
        
};

#endif // GRID_H_INCLUDED
