#ifndef CONSOLE_H
#define CONSOLE_H
#include <common/types.h>

 namespace smartware{
    namespace common{
/**
 * @todo write docs
 */
class Console
{
    uint8 x, y;
    uint16* VideoMemory;
    
  
public:
    /**
     * Default constructor
     */
    Console();

    /**
     * Destructor
     */
    ~Console();
    void print(int8*);
    void clear();
 
};
    }
}

#endif // CONSOLE_H
