#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

#include <vector>

template<typename T>
class Grid
{
    public:
        Grid(unsigned width, unsigned height): m_width(width), m_height(height), m_data(width*height) {}
        Grid(unsigned width, unsigned height, const T& fill): Grid(width, height) { fill(fill); }
        template<typename F>
        Grid(unsigned width, unsigned height, F action): Grid(width, height) { fill_action(action); }
        
        void fill(const T& fill) { m_data.assign(m_data.size(), fill); }
        
        template<typename F>
        void fill_action(F action)
        {
            for(unsigned x = 0; x < width(); x++) 
            { 
                for(unsigned y = 0; y < height(); y++)
                {
                    auto& e = operator()(x, y);
                    e = fillAction(e, x, y);
                }
            }
        }
        
        unsigned width() const { return m_width; }
        unsigned height() const { return m_height; }
        unsigned size() const { return m_data.size(); }
        
        bool empty() const { return m_data.empty(); }
        
        T& operator()(unsigned x, unsigned y) { return m_data[y * m_width + x]; }
        const T& operator()(unsigned x, unsigned y) const { return this->operator()(x,y); }
        
    private:
        unsigned        m_width;
        unsigned        m_height;
        std::vector<T>  m_data;
        
};

#endif // GRID_H_INCLUDED
