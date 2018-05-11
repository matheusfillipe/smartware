#include <drivers/mouse.h>



using namespace smartware::drivers;
using namespace smartware::common;
using namespace smartware::hardwarecom;
using namespace smartware;

void printf(char* str);

mouseEventHandler::mouseEventHandler()
{
}
void mouseEventHandler::OnKeyDown(uint8 button)
{
}
void mouseEventHandler::OnkeyUp(uint8 button)
{
}
void mouseEventHandler::OnMove(int x, int y)
{
}



void mouseEventHandler::OnActivate()
{
}


MouseDriver::MouseDriver(InterruptManager* manager, mouseEventHandler* handler): InterruptHandler(0x2C, manager), dataport(0x60), commandport(0x64)
{
   this->handler = handler;
   
    
}

void MouseDriver::Activate()
{
   offset=0;
    buttons=0;
               static uint16* VideoMemory = (uint16*) 0xb8000;  

               static int8 x=40, y=12;
    
              VideoMemory[80*y+x] = ((VideoMemory[80*y+x] & 0xF000) >> 4)
                                |((VideoMemory[80*y+x] & 0x0F00) << 4)
                                |(VideoMemory[80*y+x] & 0x00FF);
 
    
    commandport.Write(0xA8); //activate interrupts
    commandport.Write(0x20); //tell me your current state
    uint8 status = (dataport.Read() | 2);
    commandport.Write(0x60); //set State
    dataport.Write(status);
    
    commandport.Write(0xD4);
    dataport.Write(0xF4);
    
    dataport.Read();
    
}


MouseDriver::~MouseDriver()
{
}

uint32 MouseDriver::HandleInterrupt(uint32 esp)
{
    uint8 status = commandport.Read();
    
    if(!(status & 0x20))
        return esp;
    
    
    static int16 x=40, y=12;
    
    buffer[offset] = dataport.Read();
    
    if(handler==0)
        return esp;
    offset=(offset+1)%3;
    
    if(offset == 0 ){
        
        

        
            
        if(buffer[1]!=0 || buffer[2]!=0){
            handler->OnMove(buffer[1],buffer[2]);
        

        }
        
  for(uint8 i=0; i<3; i++){
            if((buffer[0] & (0x1 << i)) != (buttons & (0x1 << i))){
                    if(buttons & (0x1<<i))
                        handler->OnkeyUp(i+1);
                    else
                        handler->OnKeyDown(i+1);
                
            }  
        
        }
        buttons=buffer[0];
    }
    
    return esp;
        
    
}
