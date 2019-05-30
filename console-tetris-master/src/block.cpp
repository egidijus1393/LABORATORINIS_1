#include <random>
#include <algorithm>

#include "block.h"
#include "consts.h"
#include "point.h"

unsigned Block::score = 0;

Block::Block( MT& mt ) {
    /*
     * Generate a random type of block from the below:
     *  1. +++
     *  2. +++
     *      +
     *  3. ++++
     *  4. ++
     *  5. ++++
     *        +
     */
    
    std::uniform_int_distribution<unsigned> type_dis( 1, 5 );
    
    switch( type_dis( mt ) ) {
        case 1: {
            points =
            {
                { 0, 0 },
                { 1, 0 },
                { 2, 0 }
            };
            
            lowest_point    = &points[ 0 ];
            rotation_point  = &points[ 1 ];
            
            break;
        }
        
        case 2: {
            points =
            {
                { 0, 0 },
                { 1, 0 },
                { 2, 0 },
                { 1, 1 }
            };
            
            lowest_point    = &points[ 3 ];
            rotation_point  = &points[ 1 ];
        
            break;
        }
        
        case 3: {
            points =
            {
                { 0, 0 },
                { 1, 0 },
                { 2, 0 },
                { 3, 0 }
            };
            
            lowest_point    = &points[ 0 ];
            rotation_point  = &points[ 1 ];
            
            break;
        }
        
        case 4: {
            points =
            {
                { 0, 0 },
                { 1, 0 }
            };
            
            lowest_point    = &points[ 0 ];
            rotation_point  = &points[ 1 ];
            
            break;
        }
        
        case 5: {
            points =
            {
                { 0, 0 },
                { 1, 0 },
                { 2, 0 },
                { 3, 0 },
                { 3, 1 }
            };
            
            lowest_point    = &points[ 4 ];
            rotation_point  = &points[ 1 ];
            
            break;
        }
    }
    
    /*
     * Offset the block a random amount (in the range [1; CONSOLE_WIDTH - 5]) of characters on the
     * X axis.
     */
    std::uniform_int_distribution<unsigned> offset_dis( 1, CONSOLE_WIDTH - 5 );
    const unsigned x_offset = offset_dis( mt );
    
    for ( auto& point : points ) {
        point.x += x_offset;
    }
}

void Block::rotate() {
    for ( auto& point : points ) {
        const int temp_y = point.y;
        
        point.y = rotation_point->y + ( point.x - rotation_point->x );
        point.x = rotation_point->x - ( temp_y - rotation_point->y );
        
        /* Readjust lowest_point so that it points to the new lowest point. */
        if ( lowest_point->y < point.y ) {
            lowest_point = &point;
        }
    }
}

void Block::move( const int dir, const std::vector<Block>& fixed_blocks ) {
    if ( MoveDirection::DOWN == dir ) {
        for ( auto& point : points ) {
            ++point.y;
        }
    } else {
        /* Find the first and last points of a block on the X axis. */
        int beg_point = points[ 0 ].x;
        int end_point = beg_point;
        
        for ( const auto& point : points ) {
            if ( beg_point > point.x ) {
                beg_point = point.x;
            }
            
            if ( end_point < point.x ) {
                end_point = point.x;
            }
        }
        
        /* If touching either wall, stop moving. */
        if ( ( 1 == beg_point && MoveDirection::LEFT == dir ) ||
             ( ( CONSOLE_WIDTH - 2 ) == end_point && MoveDirection::RIGHT == dir ) ) {
            return;
        }
        
        /* If touching another blocks' side, stop moving. */
        for ( int i = fixed_blocks.size() - 1; 0 <= i; --i ) {
            for ( const auto& point : points ) {
                for ( const auto& fixed_point : fixed_blocks[ i ].get_points() ) {
                    if ( fixed_point.y == point.y &&
                         ( ( ( fixed_point.x - 1 ) == point.x && MoveDirection::RIGHT == dir ) ||
                         ( ( fixed_point.x + 1 ) == point.x && MoveDirection::LEFT == dir ) ) ) {
                        return;
                    }
                }
            }
        }
        
        for ( auto& point : points ) {
            point.x += dir;
        }
    }
}


void Block::jump_to_bottom( const std::vector<Block>& fixed_blocks ) {
    /*
     * Sort all points based on their Y coordinate (points with the lowest value will be placed on
     * top).
     */
    std::sort( points.begin(), points.end(), []( const Point& lhs, const Point& rhs ) {
        return lhs.y > rhs.y;
    } );
    
    lowest_point = &points[ 0 ];
    
    /*
     * 1. Loop through all blocks from the end of the vector.
     * 2. Check, if coordinates match on the X axis.
     * 3. If so, check if it is lower than lowest_y.
     * 4. Jump to lowest_y - 1.
     */
    int lowest_y = PLAY_AREA_HEIGHT;
    
    for ( const auto& fixed_block : fixed_blocks ) {
        for ( const auto& point : points ) {
            for ( const auto& fixed_point : fixed_block.get_points() ) {
                if ( fixed_point.x == point.x && lowest_y > fixed_point.y ) {
                    lowest_y = fixed_point.y;
                }
            }
        }
    }
    
    move_all_points_to( lowest_y - 1 );
    lowest_point->y = lowest_y - 1;
}

bool Block::is_on_surface( const std::vector<Block>& fixed_blocks ) const {
    /* If on the ground. */
    if ( ( PLAY_AREA_HEIGHT - 1 ) == lowest_point->y ) {
        return true;
    }
    
    /* If on a block. */
    for ( int i = fixed_blocks.size() - 1; 0 <= i; --i ) {
        for ( const auto& point : points ) {
            for ( const auto& fixed_point : fixed_blocks[ i ].get_points() ) {
                if ( ( fixed_point.y - 1 ) == point.y && fixed_point.x == point.x ) {
                    return true;
                }
            }
        }
    }
    
    return false;
}

bool Block::is_touching_top() const {
    for ( const auto& point : points ) {
        if ( point.y <= 0 ) {
            return true;
        }
    }
    
    return false;
}

void Block::move_all_points_to( const int y ) {
    for ( unsigned i = 1; points.size() != i; ++i ) {
        points[ i ].y = y - ( lowest_point->y - points[ i ].y );
    }
}