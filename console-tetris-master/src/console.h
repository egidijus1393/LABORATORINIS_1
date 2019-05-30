#pragma once

#include <windows.h>
#include <vector>

#include "block.h"
#include "consts.h"

class Console {
    public:
        Console( const SHORT width = CONSOLE_WIDTH, const SHORT height = CONSOLE_HEIGHT );
        ~Console();
        
        void set_size( const SHORT, const SHORT );
        void display_end_screen( const Block& );
        void clear_screen();
        
        bool read_input( Block&, std::vector<Block>& );
        
        void update( const Block&, std::vector<Block>& );
        
        HWND                        window;
        HANDLE                      std_out;
        HANDLE                      std_in;
        CONSOLE_SCREEN_BUFFER_INFO  csbi;
    
    private:
        void display_footer( const Block& );
        void display_play_area( const Block&, std::vector<Block>& );
        
        bool key_down = false;
};