#include <v8.h>
#include <node.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include "SaxonProcessorJS.hpp"
#include "XsltProcessorJS.hpp"


v8::Persistent<v8::FunctionTemplate> saxon_node::SaxonProcessorJS::Constructor;

void saxon_node::SaxonProcessorJS::newTransformer(const v8::FunctionCallbackInfo<Value>& args) {
    
    Local<Object> instance = saxon_node::XsltProcessorJS::Instantiate(args.This());

    args.GetReturnValue().Set(instance);

};

v8::Persistent<v8::FunctionTemplate> saxon_node::XsltProcessorJS::Constructor;

