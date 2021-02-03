/*
  Library support for FlexRadio 6000 Rigs
  Copyright (C)2015 Vincenzo Stefanazzi - IW7DMH. All right reserved

  This library is free software; you can redistribute it and/or
  modify it under the terms of the CC BY-NC-SA 3.0 license.
  https://creativecommons.org/licenses/by-nc-sa/3.0/
  
  The license applies to all part of the library including the 
  examples and tools supplied with the library.
*/
#ifndef CommandList_h
#define CommandList_h
#include "Arduino.h"

#define COMMAND_LIST_SIZE 20
#define COMMAND_LEGTH 80

class CommandList
{
    private:
        int front, back, count;
        String CommandEntry[COMMAND_LIST_SIZE];
		
    public:
        CommandList();
        void add(String);
        String remove();
		int getCount();

};
#endif
