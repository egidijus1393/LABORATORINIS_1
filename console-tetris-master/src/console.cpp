#include <windows.h>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "console.h"
#include "block.h"
#include "point.h"

Console::Console( const SHORT width, const SHORT height ) {
    std_in  = GetStdHandle( STD_INPUT_HANDLE );
    std_out = GetStdHandle( STD_OUTPUT_HANDLE );
    window  = GetConsoleWindow();
    
    GetConsoleScreenBufferInfo( std_out, &csbi );
    
    SetConsoleMode( std_in, ENABLE_WINDOW_INPUT );
    SetConsoleTitle( CONSOLE_TITLE );
    
    /* Prevent window resizing by removing sizebox and max boxes. */
    SetWindowLongPtr( window, GWL_STYLE, GetWindowLongPtr( window, GWL_STYLE ) & ~( WS_SIZEBOX |
                      WS_MAXIMIZEBOX ) );
    
    set_size( width, height );
}

Console::~Console() {
    SetConsoleWindowInfo( std_out, true, &csbi.srWindow );
    SetConsoleTextAttribute( std_out, csbi.wAttributes );
    SetConsoleScreenBufferSize( std_out, csbi.dwSize );
}

void Console::set_size( const SHORT width, const SHORT height ) {
    const SMALL_RECT sr = {
        0,                                  // Left
        0,                                  // Top
        static_cast<SHORT>( width - 1 ),    // Right
        static_cast<SHORT>( height - 1 ),   // Bottom
    };
    
    SetConsoleWindowInfo( std_out, true, &sr );
    SetConsoleScreenBufferSize( std_out, { width, height } );
}

void Console::clear_screen() {
    COORD init_coord    = { 0, 0 };
    DWORD cells         = CONSOLE_WIDTH * CONSOLE_HEIGHT;
    DWORD written;
    
    FillConsoleOutputCharacter( std_out, ' ', cells, init_coord , &written );
    FillConsoleOutputAttribute( std_out, csbi.wAttributes, cells, init_coord, &written );
    
    SetConsoleCursorPosition( std_out, init_coord );
}

bool Console::read_input( Block& active_block, std::vector<Block>& fixed_blocks ) {
    INPUT_RECORD in_buff[ 128 ];
    DWORD event_count;
    
    GetNumberOfConsoleInputEvents( std_in, &event_count );
    
    if ( event_count > 0 ) {
        ReadConsoleInput( std_in, in_buff, 128, &event_count );
        
        for ( unsigned i = 0; event_count != i; ++i ) {
            if ( !key_down ) {
                switch ( in_buff[ i ].Event.KeyEvent.wVirtualKeyCode ) {
                    case VK_ESCAPE:
                        return false;
                        break;
                    
                    case VK_LEFT:
                    case 0x41: // A
                        active_block.move( MoveDirection::LEFT, fixed_blocks );
                        break;
                    
                    case VK_RIGHT:
                    case 0x44: // D
                        active_block.move( MoveDirection::RIGHT, fixed_blocks );
                        break;
                    
                    case VK_PRIOR: // Page Up
                        active_block.rotate();
                        break;
                    
                    case VK_SPACE:
                        active_block.jump_to_bottom( fixed_blocks );
                        break;
                    
                    default:
                        break;
                }
                
                key_down = true;
            } else {
                if ( !in_buff[ i ].Event.KeyEvent.bKeyDown ) {
                    key_down = false;
                }
            }
        }
    }
    
    return true;
}

void Console::display_footer( const Block& active_block ) {
    std::cout << std::string( CONSOLE_WIDTH, '-' ) << std::endl;
    std::cout << "Score: " << active_block.get_score() << std::flush;
}

void Console::display_play_area( const Block& active_block, std::vector<Block>& fixed_blocks ) {
    std::vector<std::string> play_area( PLAY_AREA_HEIGHT, std::string( CONSOLE_WIDTH - 1, ' ' ) );
    
    /* Display active block. */
    for ( const auto& point : active_block.get_points() ) {
        play_area[ point.y ][ point.x ] = '+';
    }
    
    /* Display fixed blocks. */
    for ( const auto& block : fixed_blocks ) {
        for ( const auto& point : block.get_points() ) {
            play_area[ point.y ][ point.x ] = '+';
        }
    }
    
    /* Display play area and test for full lines. */
    for ( unsigned i = 0; play_area.size() != i; ++i ) {
        /* If the line should be cleared. */
        if ( std::count( play_area[ i ].begin(), play_area[ i ].end(), ' ' ) == 1 ) {
            for ( auto& fixed_block : fixed_blocks ) {
                std::vector<Point>& fixed_points = fixed_block.get_points();
                
                /* Remove the points within the full line. */
                fixed_points.erase( std::remove_if( fixed_points.begin(), fixed_points.end(),
                    [ i ]( const Point& p ) { return p.y == static_cast<int>( i ); } ),
                    fixed_points.end()
                );
                
                /* Readjust the rest of the points by lowering their position on the Y axis. */
                for ( auto& fixed_point : fixed_points ) {
                    ++fixed_point.y;
                }
            }
            
            active_block.incr_score();
        } else {
            std::cout << play_area[ i ] << std::endl;
        }
    }
}

void Console::display_end_screen( const Block& active_block ) {
    clear_screen();
    
    std::cout << "Game over. You scored: " << active_block.get_score() << std::endl;
    system( "pause" );
}

void Console::update( const Block& active_block, std::vector<Block>& fixed_blocks ) {
    clear_screen();
    
    display_play_area( active_block, fixed_blocks );
    display_footer( active_block );
}