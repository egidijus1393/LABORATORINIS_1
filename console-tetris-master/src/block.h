#pragma once

#include <random>
#include <vector>

#include "point.h"
#include "consts.h"

enum MoveDirection {
    LEFT    = -1,
    RIGHT   = 1,
    DOWN    = 0
};

using MT = std::mt19937;

class Block {
    public:
        Block( MT& );
        
        void rotate();
        
        void move( const int, const std::vector<Block>& );
        void jump_to_bottom( const std::vector<Block>& );
        
        bool is_on_surface( const std::vector<Block>& ) const;
        bool is_touching_top() const;
        
        static void incr_score() { ++score; }
        static unsigned get_score() { return score; }
        
        const std::vector<Point>& get_points() const { return points; }
        std::vector<Point>& get_points() { return points; }
    
    private:
        void move_all_points_to( const int );
        
        static unsigned score;
        
        std::vector<Point> points;
        Point* lowest_point;
        const Point* rotation_point;
};