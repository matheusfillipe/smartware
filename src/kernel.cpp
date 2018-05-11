#include <common/types.h>
#include <gdt.h>
#include <hardwarecom/interrupts.h>
#include <drivers/keyboard.h>
#include <drivers/mouse.h>
#include <drivers/driver.h>

using namespace smartware;
using namespace smartware::drivers;
using namespace smartware::common;
using namespace smartware::hardwarecom;


void clear(){
    
    static uint16* VideoMemory = (uint16*) 0xb8000;    
    static uint8 x=0, y=0;
    
    for(y=0; y < 25; y++)
        for(x = 0; x < 80; x++)
            VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';
}

void printf(char* str)
{
    static uint16* VideoMemory = (uint16*) 0xb8000;
    
    static uint8 x=0, y=0;
    
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
            for(y=0; y < 25; y++)
                for(x = 0; x < 80; x++)
                    VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';
                x=0;
                y=0;
            
            }
    }
}

void printHex(uint8 key){
    
        char* hex = "0123456789ABCDEF";
        char *foo = "0x00";
        foo[2]=hex[(key >> 4) & 0x0F];
        foo[3] = hex[key & 0x0F];
        printf(foo);
        printf("\n");               
 
}


class printKeyboardEventHandler : public keyboardEventHandler{
public:
     void OnKeyDown(char c){
         printf(&c);
   }
    
};


class ConsoleMouse : public mouseEventHandler{
        int8 x,y;
        uint16* VideoMemory;       
    
public:
    
   
    
    ConsoleMouse(){
        this->VideoMemory = (uint16*) 0xb8000;  
    }
    
    void OnMove(int xoffst, int yoffst){

          
          
          this->VideoMemory[80*y+x] = ((this->VideoMemory[80*y+x] & 0xF000) >> 4)
                                |((this->VideoMemory[80*y+x] & 0x0F00) << 4)
                                |(this->VideoMemory[80*y+x] & 0x00FF);
 
          
       
         x += xoffst;//buffer[1] - (0x100 & (buffer[0] << (8-4)));
         y -= yoffst;//buffer[2] - (0x100 & (buffer[0] << (8-5)));
          
        if(x >= 80) x = 79;
        if(x < 0) x = 0;  
        
          if(y >= 25) y = 24;
          if(y < 0) y = 0;
            
          this->VideoMemory[80*y+x] = ((this->VideoMemory[80*y+x] & 0xF000) >> 4)
                                |((this->VideoMemory[80*y+x] & 0x0F00) << 4)
                                |(this->VideoMemory[80*y+x] & 0x00FF);
                                
                        
                                
     
          
                
            
        }

          
        
    
    
    void OnKeyDown(uint8 button){
      
                this->VideoMemory[80*y+x] = ((this->VideoMemory[80*y+x] & 0xF000) >> 4)
                                 |((this->VideoMemory[80*y+x] & 0x0F00) << 4)
                                |(this->VideoMemory[80*y+x] & 0x00FF);
                                
       
    }
    
    void OnkeyUp(uint8 button){
                 this->VideoMemory[80*y+x] = ((VideoMemory[80*y+x] & 0xF000) >> 4)
                                 |((this->VideoMemory[80*y+x] & 0x0F00) << 4)
                                |(this->VideoMemory[80*y+x] & 0x00FF);
                                
       
    }
    
    
};

typedef void (*constructor)();
extern "C" constructor start_ctors;
extern "C" constructor end_ctors;
extern "C" void callConstructors()
{
    for(constructor* i = &start_ctors; i != &end_ctors; i++)
        (*i)();
}

extern "C" void Main(void* multiboot_structure, unsigned int magicnumber)
{
    
    clear(); 
    printf("\n           SMARTWARE\n\n\n");
    printf("             BOOTING\n");
    

    GlobalDescriptorTable gdt;
    InterruptManager interrupts(0x20, &gdt);
    printf("Initializing Drivers ...... .1\n");
    DriverManager driverManager;
    
    printKeyboardEventHandler printHandler;

    KeyboardDriver keyboard(&interrupts, &printHandler);    
    driverManager.AddDriver(&keyboard);
    
    ConsoleMouse mouse;
    MouseDriver mouseDriver(&interrupts, &mouse);
    driverManager.AddDriver(&mouseDriver);
    driverManager.ActivateAll();    
    printf("Drivers Initialized...... .2\n");
    interrupts.Activate();
     printf("Drivers up and running...... .3\n");
    
   
    while(1);
}
