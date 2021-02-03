/*
  Library support for FlexRadio 6000 Rigs
  Copyright (C)2015 Vincenzo Stefanazzi - IW7DMH. All right reserved

  This library is free software; you can redistribute it and/or
  modify it under the terms of the CC BY-NC-SA 3.0 license.
  https://creativecommons.org/licenses/by-nc-sa/3.0/
  
  The license applies to all part of the library including the 
  examples and tools supplied with the library.
*/
#include "CommandList.h"

CommandList::CommandList() { 
	
	front = back = -1;
    count = 0;
	char space=' ';
	char emptyEntry[COMMAND_LEGTH];
	for (int i=0;i<COMMAND_LEGTH;i++)
	    emptyEntry[i]=space;
    
    for(int i=0; i < COMMAND_LIST_SIZE; i++) {
    	CommandEntry[i] = String(emptyEntry);
    }

}


void CommandList::add(String entry) {
	if (front == 0 && back == COMMAND_LIST_SIZE-1 || front == back + 1) {
        Serial.println(F("Command List full!"));
    } else if (front == -1 && back == -1) {  //se è vuota
	    front = 0;
	    back = 0;
	    CommandEntry[front] = entry;
	    count++;
    } else if (back == COMMAND_LIST_SIZE-1) {
    	back = 0;
    	CommandEntry[back] = entry;
    	count++;
    } else {
    	back++;
    	CommandEntry[back] = entry;
    	count++;
    }
	
	/*Serial.print(F("ADD    - front=")); Serial.print(front);
	Serial.print(F(" - back=")); Serial.print(back);
	Serial.print(F(" - count=")); Serial.println(count);*/
	
}

String CommandList::remove()
{
  String element;
 
	if (front == -1 && back == -1) {
		Serial.println(F("Command List is empty"));
	} else {
			if (front == back) {
			element=CommandEntry[front];
			front = -1;
			back = -1;
			count--;
		}
		else if (front == COMMAND_LIST_SIZE-1) {
			element=CommandEntry[front];
			front = 0;
			count--;
		}
		else {
			element=CommandEntry[front];
			front++;
			count--;
		}
    }

  	/*Serial.print(F("REMOVE - front=")); Serial.print(front);
	Serial.print(F(" - back=")); Serial.print(back);
	Serial.print(F(" - count=")); Serial.println(count);*/
	
  return element;
}

int CommandList::getCount() {
	return count;
}