#include "../include/common/console.h"

using namespace smartware::common;

Console::Console(){
      x=0;
        y=0;
        VideoMemory = (uint16*) 0xb8000;
}

Console::~Console(){
    
}
   
    void Console::print(int8* str){
        
     for(int i=0; str[i] !='\0'; ++i){
        
        switch(str[i]){
        
            case '\n':
                x=0;
                y++;
                break;
        
            
            default:
                VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | str[i];
        
        }
        
        x++;
        if(x>=80){
            y++;
            x=0;
        }
        
        if(y>=25){
          // scroll();//y-24);
           //y=24; 
            uint8 xi, yi;
            for(yi=0; yi < y; yi++){
                    uint8 l;
                    l=yi+1;//lines;
                    if(l>=25)
                        break;
            
                for(xi = 0; xi < 80; xi++)
                
                    VideoMemory[80*yi+xi] = VideoMemory[80*l+xi];
                }
                
               yi=24;
                    for(xi = 0; xi < 80; xi++)
                        VideoMemory[80*yi+xi] = (VideoMemory[80*yi+xi] & 0xFF00) | ' ';
            
           
           //clear();
           y--;
            
            }     
    
        }
    }
    
    void Console::clear(){
    
    static uint16* VideoMemory = (uint16*) 0xb8000;    
    static uint8 x=0, y=0;
    
    for(y=0; y < 25; y++)
        for(x = 0; x < 80; x++)
            VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';
}
