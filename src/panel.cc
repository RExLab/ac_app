#include <nan.h>
#include <unistd.h>
#include <v8.h>
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "gpioclass.h"

#define nSwitches 4

using namespace std;
using namespace v8;

GPIOClass* gpio[nSwitches];

NAN_METHOD(Setup) {
    NanScope();
	int i= 0;
	
	gpio[0] = new GPIOClass("2"); //create new GPIO object to be attached to  GPIO2
	gpio[1] = new GPIOClass("3"); //create new GPIO object to be attached to  GPIO3
	gpio[2] = new GPIOClass("4"); //create new GPIO object to be attached to  GPIO4
    gpio[3] = new GPIOClass("17"); //create new GPIO object to be attached to  GPIO17
	
	for(i=0; i< nSwitches; i++){
		gpio[i]->export_gpio(); 
		gpio[i]->setdir_gpio("out");		
	}
	
    NanReturnValue(NanNew("1"));
}

NAN_METHOD(Update) {
	NanScope();
	char argv[40];
	char value[10];
    string str_argv = *v8::String::Utf8Value(args[0]->ToString()); 
    strcpy(argv, str_argv.c_str());

    int switches = atoi(argv); 

	if(switches < 0 || switches > 15){
		 NanReturnValue(NanNew("{'error':'invalid input'}"));
	}
	int i =0;
	for(i=0;i<nSwitches;i++){
		sprintf( value, "%i", switches >> i & 1);
		gpio[i]->setval_gpio(string(value));
	}		

	
    NanReturnValue(NanNew("ok"));	

}

NAN_METHOD(GetValues) {
	NanScope();
	int i; 
	string buffer_sw = string("\"sw\":[");
	string swstate;
	for(i =0; i < nSwitches ; i++){
		
	    gpio[i]->getval_gpio(swstate);
		 
		if(i == nSwitches-1)
			buffer_sw = buffer_sw +  swstate ;
		else
			buffer_sw = buffer_sw +  swstate+ string(",");		
							
	}
	buffer_sw= buffer_sw + string("]");
	
    NanReturnValue(NanNew("{" + buffer_sw+ "}"));	

}




NAN_METHOD(Exit) {
	NanScope();
	int i;
	for(i=0; i< nSwitches; i++){
		gpio[i] = NULL;		
	}
	NanReturnValue(NanNew("1"));
}


void Init(Handle<Object> exports) { // cria funções para serem invocadas na aplicação em nodejs
	exports->Set(NanNew("setup"), NanNew<FunctionTemplate>(Setup)->GetFunction());
	exports->Set(NanNew("update"), NanNew<FunctionTemplate>(Update)->GetFunction());
	exports->Set(NanNew("exit"), NanNew<FunctionTemplate>(Exit)->GetFunction());
	exports->Set(NanNew("getvalues"), NanNew<FunctionTemplate>(GetValues)->GetFunction());

}


NODE_MODULE(panel, Init)

