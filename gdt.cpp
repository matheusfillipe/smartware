#include "gdt.h"

GlobalDescriptorTable::GlobalDescriptorTable()
:nullSegmentSelector(0,0,0), 
unusedSegmentSelector(0,0,0),
codeSegmenteSelector(0,64*1024*1024, 0x9A),
dataSegmenteSelector(0,64*1024*1024, 0x92)

{
    uint32 i[2];

    i[0]=sizeof(GlobalDescriptorTable) << 16;
    i[1]=(uint32)this;   
     
    asm volatile("lgdt (%0)": :"p"(((uint8 *) i)+2));
}

GlobalDescriptorTable::~GlobalDescriptorTable()
{
}

uint16 GlobalDescriptorTable::DataSegmenteSelector()
{
    return (uint8*) &dataSegmenteSelector - (uint8*)this;
}

uint16 GlobalDescriptorTable::CodeSegmenteSelector()
{
    return (uint8*) &codeSegmenteSelector - (uint8*)this;
}

GlobalDescriptorTable::SegmentDescriptor::SegmentDescriptor(uint32 base, uint32 limit, uint8 type)
{
    uint8* target =  (uint8*) this;
    if(limit<=65536){
        target[6]=0x40;
    }
    else{
        if((limit & 0xFFF) != 0xFFF){
            limit = (limit >> 12) -1;
        }
        else{
            limit = limit >> 2;
            
        }
        
        target[6]=0xC0;
        
    }
    
    target[0]=limit & 0xFF;
    target[1]=(limit >> 8) & 0xFF;    
    target[6] |= (limit >> 16) & 0xF;
    
    target[2]= base & 0xFF;
    target[3]= ((base >> 8)) & 0xFF;   
    target[4]= ((base >> 16)) & 0xFF;
    target[7]= ((base >> 24)) & 0xFF;
    
    target[5]= type;
}

uint32 GlobalDescriptorTable::SegmentDescriptor::Base()
{
    
    uint8* target =  (uint8*) this;
    uint32 result = target[7];
    result = (result << 8 ) + target[4];
    result = (result << 8 ) + target[3];
    result = (result << 8 ) + target[2];
    return result;
}

uint32 GlobalDescriptorTable::SegmentDescriptor::Limit()
{
    uint8* target =  (uint8*) this;
    uint32 result = target[6] & 0xF;
    result = (result << 8 ) + target[1];   
    result = (result << 8 ) + target[0];
   
    if((target[6] & 0xC0) == 0xC0)
        result = (result << 12) | 0xFFF;
    return result;
}




