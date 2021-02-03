/*
  Library support for FlexRadio 6000 Rigs
  Copyright (C)2015 Vincenzo Stefanazzi - IW7DMH. All right reserved

  This library is free software; you can redistribute it and/or
  modify it under the terms of the CC BY-NC-SA 3.0 license.
  https://creativecommons.org/licenses/by-nc-sa/3.0/

  The license applies to all part of the library including the
  examples and tools supplied with the library.
*/
#include "Cwx.h"

Cwx::Cwx() {

	front=0;

    for (int i=0;i<MACRO_INFO_LIST_SIZE;i++){
		mInfoElem[i].macroId=0;
		mInfoElem[i].commandId=0;
		mInfoElem[i].from=0;
		mInfoElem[i].to=0;
	}

	upd_wpm=true;
	upd_break_in_delay=true;
	upd_macro1=true;
	upd_macro2=true;
	upd_macro3=true;
	upd_sent=true;
	upd_erase=true;

	updated=false;

}

void Cwx::updateStatus(String msg) {
	//Serial.println(msg);
	updated=true;
	int oldi=0;
	int i=msg.indexOf('"',oldi);
	if (i>0) {
		//Serial.println("trovata stringa macro!!!!!!!!!!!!!!!!!!!!!!!!!!");
		int m=msg.indexOf('=',oldi);
	    int macroId=msg.substring(5,m).toInt();
		//Serial.print("macroId:"); Serial.println(macroId);
		int e=msg.indexOf('"',m+2);
		//Serial.println(e);
        //Serial.println(msg.substring(m+2,e));
        String mac=msg.substring(m+2,e);
		switch(macroId) {
				case 1:
				        set_macro1(mac);
				        break;
				case 2:
						set_macro2(mac);
				        break;
				case 3:
						set_macro3(mac);
				        break;
				default:
						break;
					//Serial.print(F("Unhandled macroId:"));
					//Serial.println(macroId);
		}

	} else {
		oldi=0;
		i=msg.indexOf(' ',oldi);
		while (i>0) {
			setValue(msg.substring(oldi,i));
			oldi=i+1;
			i=msg.indexOf(' ',oldi+1);
		}
		//get the last element
		i=msg.indexOf('\n',oldi);
		setValue(msg.substring(oldi,i));
	}
}

void Cwx::setValue(String msg){
	int i=msg.indexOf('=');
	if (i>0) {
	    String var=msg.substring(0,i);
		//Serial.println("+++++++++++++++++++++++++++++++++++++++++++++++");
		//Serial.print(var); Serial.print(F("="));Serial.println(msg.substring(i+1));
		//Serial.println("+++++++++++++++++++++++++++++++++++++++++++++++");

		if (var.equals(F("wpm"))) {
			//Serial.println("+++++++++++++++++++++++++++++++++++++++++++++++");
			//Serial.print(var); Serial.print(F("="));Serial.println(msg.substring(i+1));
			//Serial.println("+++++++++++++++++++++++++++++++++++++++++++++++");
			set_wpm(msg.substring(i+1).toInt());
			return;
		}

		if (var.equals(F("break_in_delay"))) {
			set_break_in_delay(msg.substring(i+1).toInt());
			return;
		}

		if (var.equals(F("macro1"))) {
			set_macro1(msg.substring(i+1));
			return;
		}

		if (var.equals(F("macro2"))) {
			set_macro2(msg.substring(i+1));
			return;
		}

		if (var.equals(F("macro3"))) {
			set_macro3(msg.substring(i+1));
			return;
		}

		if (var.equals(F("sent"))) {
			set_sent(msg.substring(i+1).toInt());
			return;
		}

		if (var.equals(F("erase"))) {
			set_erase(msg.substring(i+1));
			return;
		}

	}
}

void Cwx::set_wpm(int newval) {
	if (newval!=wpm) {
		wpm=newval;
		upd_wpm=true;
	}
}



void Cwx::set_break_in_delay(int newval) {
	if (newval!=break_in_delay) {
		break_in_delay=newval;
		upd_break_in_delay=true;
	}
}

void Cwx::set_macro1(String newval) {
	if (!newval.equals(macro1)) {
			macro1=newval;
			upd_macro1=true;
	}
}

void Cwx::set_macro2(String newval) {
	if (!newval.equals(macro2)) {
			macro2=newval;
			upd_macro2=true;
	}
}

void Cwx::set_macro3(String newval) {
	if (!newval.equals(macro3)) {
			macro3=newval;
			upd_macro3=true;
	}
}

void Cwx::set_sent(int newval){
	if (newval!=sent) {
		sent=newval;
		upd_sent=true;
	}

	// inserire codice per generare eventi macroActive, macroStopped

	for (int i=0;i<MACRO_INFO_LIST_SIZE;i++){
		if (mInfoElem[i].commandId!=0) {
			if (sent==mInfoElem[i].to) {
				//genera evento fineMacro(id)
				//Serial.print("Stopped macroId:");Serial.println(mInfoElem[i].macroId);
				if (do_macro_stopped_event!=NULL) {
					do_macro_stopped_event(mInfoElem[i].macroId);
				}
				removeFromInfoList(mInfoElem[i].commandId);
				return;
			}
			if (sent>=mInfoElem[i].from && sent<mInfoElem[i].to) {
				//Serial.print("Active macroId:");Serial.println(mInfoElem[i].macroId);
				if (do_macro_active_event!=NULL) {
					do_macro_active_event(mInfoElem[i].macroId);
				}
				return;
			}

		}
	}

}

void Cwx::set_erase(String newval){
	//Serial.println(newval.substring(newval.lastIndexOf(F(","))+1));
	/*if (!newval.equals(erase)) {
		erase=newval;
		upd_erase=true;
	}*/
	int t=newval.substring(newval.lastIndexOf(F(","))+1).toInt();
	for (int i=0;i<MACRO_INFO_LIST_SIZE;i++){
		if (mInfoElem[i].commandId!=0) {
			if (t==mInfoElem[i].to) {
				//genera evento fineMacro(id)
				//Serial.print("Stopped macroId:");Serial.println(mInfoElem[i].macroId);
				if (do_erase_event!=NULL) {
					do_erase_event(mInfoElem[i].macroId);
				}
				/*if (do_macro_stopped_event!=NULL) {
					do_macro_stopped_event(mInfoElem[i].macroId);
				}*/
				removeFromInfoList(mInfoElem[i].commandId);
				return;
			}
		}
	}
}



void Cwx::fireEvents() {

	/*  togliere commento quando verranno implementati gli handler
	if (updated)
		updated=false;
	else
		return;

		- la proprietà updated deve diventare privata
	*/

	if ((upd_wpm) && (do_wpm_event!=NULL)) {
			do_wpm_event();
			upd_wpm=false;
	}

	if ((upd_break_in_delay) && (do_break_in_delay_event!=NULL)) {
			do_break_in_delay_event();
			upd_break_in_delay=false;
	}

	if ((upd_macro1) && (do_macro1_event!=NULL)) {
			do_macro1_event();
			upd_macro1=false;
	}

	if ((upd_macro2) && (do_macro2_event!=NULL)) {
			do_macro2_event();
			upd_macro2=false;
	}

	if ((upd_macro3) && (do_macro3_event!=NULL)) {
			do_macro3_event();
			upd_macro3=false;
	}

	if ((upd_sent) && (do_sent_event!=NULL)) {
			do_sent_event();
			upd_sent=false;
	}

	/*if ((upd_erase) && (do_erase_event!=NULL)) {
			do_erase_event();
			upd_erase=false;
	}*/

}

void Cwx::attach_wpm_event(eventHandlerFunction _eventHandler) {
	do_wpm_event=_eventHandler;
}

void Cwx::attach_break_in_delay_event(eventHandlerFunction _eventHandler) {
	do_break_in_delay_event=_eventHandler;
}

void Cwx::attach_macro1_event(eventHandlerFunction _eventHandler) {
	do_macro1_event=_eventHandler;
}

void Cwx::attach_macro2_event(eventHandlerFunction _eventHandler) {
	do_macro2_event=_eventHandler;
}

void Cwx::attach_macro3_event(eventHandlerFunction _eventHandler) {
	do_macro3_event=_eventHandler;
}

void Cwx::attach_sent_event(eventHandlerFunction _eventHandler) {
	do_sent_event=_eventHandler;
}

void Cwx::attach_erase_event(eventHandlerArrFunction _eventHandler) {
	do_erase_event=_eventHandler;
}

void Cwx::attach_macro_active_event(eventHandlerArrFunction _eventHandler) {
	do_macro_active_event=_eventHandler;
}

void Cwx::attach_macro_stopped_event(eventHandlerArrFunction _eventHandler) {
	do_macro_stopped_event=_eventHandler;
}

void Cwx::updateObject(int objectId,int value){
	switch(objectId) {
	//	case RADIO_MIXER_LINEOUT_GAIN:
	//		 break;
		default:
			 Serial.print(F("Interlock::updateObject - Unhandled id:")); Serial.println(objectId);
	}

}

// ======================= Functions ===================
void Cwx::addToInfoList(int macroId, int commandId) {
  if (mInfoElem[front].commandId==0) {
	  mInfoElem[front].macroId=macroId;
	  mInfoElem[front].commandId=commandId;
	  if (front<MACRO_INFO_LIST_SIZE-1) {
		front++;
	  } else {
		front=0;
	  }
  } else {
	Serial.println(F("Cwx::addToInfoList: Error adding cwx info. List not empty!"));
  }
}

int Cwx::getInfoId(int commandId) {
	int result=-1;
	for (int i=0;i<MACRO_INFO_LIST_SIZE;i++){
		if (mInfoElem[i].commandId==commandId) {
			result=i;
			break;
		}
	}
	return result;
}

void Cwx::removeFromInfoList(int commandId) {
    int k=getInfoId(commandId);
	if (k>=0) {
		mInfoElem[k].macroId=0;
		mInfoElem[k].commandId=0;
		mInfoElem[k].from=0;
		mInfoElem[k].to=0;
	} else {
		Serial.println(F("Cwx::removeFromInfoList: Error removing cwx info. CommandId not found!"));
	}

}

void Cwx::setFromToValues(int commandId, int firstCharId) {
    int k=getInfoId(commandId);
	if (k>=0) {
	    int len=0;      //I need macro length to set properly the "to" value
		switch (mInfoElem[k].macroId) {
			case 1:
			    len=macro1.length();
				break;
			case 2:
			    len=macro2.length();
				break;
			case 3:
			    len=macro3.length();
				break;
		}
		mInfoElem[k].from=firstCharId;
		mInfoElem[k].to=firstCharId+len-1;
	} else {
		Serial.println(F("Cwx::setFromToValues: Error. CommandId not found!"));
	}
}

void Cwx::printMacroInfoList(){
    Serial.println("id - macroId - commandId - from - to");
	for (int i=0;i<MACRO_INFO_LIST_SIZE;i++){
		Serial.print(i); Serial.print(" - ");
		Serial.print(mInfoElem[i].macroId); Serial.print(" - ");
		Serial.print(mInfoElem[i].commandId); Serial.print(" - ");
		Serial.print(mInfoElem[i].from); Serial.print(" - ");
		Serial.println(mInfoElem[i].to);
	}
}





