#include <random>
#include <vector>
#include <memory>
#include <windows.h>
#include <chrono>

#include "block.h"
#include "console.h"

int main() {
    /*
     * Seed using time, since the implementation of std::random_device on GCC seems to be
     * broken.
     */
    std::mt19937 mt( static_cast<long unsigned>(
                     std::chrono::high_resolution_clock::now().time_since_epoch().count() ) );
    
    std::shared_ptr<Block> active_block = std::make_shared<Block>( mt );
    std::vector<Block> fixed_blocks;
    
    Console con;
    
    while ( true ) {
        if ( !con.read_input( *active_block, fixed_blocks ) ) {
            break;
        }
        
        if ( active_block->is_on_surface( fixed_blocks ) ) {
            if ( active_block->is_touching_top() ) {
                con.display_end_screen( *active_block );
                
                break;
            }
            
            fixed_blocks.push_back( *active_block );
            active_block = std::make_shared<Block>( mt );
        }
        
        con.update( *active_block, fixed_blocks );
        active_block->move( MoveDirection::DOWN, fixed_blocks );
        
        Sleep( GAME_SPEED );
    }
    
    return 0;
}