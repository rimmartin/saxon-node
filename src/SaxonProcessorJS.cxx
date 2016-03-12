#include <v8.h>
#include <node.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include "SaxonProcessorJS.hpp"
#include "XsltProcessorJS.hpp"
#include "XQueryProcessorJS.hpp"
#include "XPathProcessorJS.hpp"
#include "SchemaValidatorJS.hpp"


v8::Persistent<v8::FunctionTemplate> saxon_node::SaxonProcessorJS::Constructor;

void saxon_node::SaxonProcessorJS::newTransformer(const v8::FunctionCallbackInfo<v8::Value>& args) {
    
    v8::Local<v8::Object> instance = saxon_node::XsltProcessorJS::Instantiate(args.This());

    args.GetReturnValue().Set(instance);

};

void saxon_node::SaxonProcessorJS::newXQueryProcessor(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Local<v8::Object> instance = saxon_node::XQueryProcessorJS::Instantiate(args.This());

    args.GetReturnValue().Set(instance);

};

void saxon_node::SaxonProcessorJS::newXPathProcessor(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Local<v8::Object> instance = saxon_node::XPathProcessorJS::Instantiate(args.This());

    args.GetReturnValue().Set(instance);

};

void saxon_node::SaxonProcessorJS::newSchemaValidator(const v8::FunctionCallbackInfo<v8::Value>& args) {
    v8::Local<v8::Object> instance = saxon_node::SchemaValidatorJS::Instantiate(args.This());

    args.GetReturnValue().Set(instance);

};


v8::Persistent<v8::FunctionTemplate> saxon_node::XsltProcessorJS::Constructor;
v8::Persistent<v8::FunctionTemplate> saxon_node::XQueryProcessorJS::Constructor;
v8::Persistent<v8::FunctionTemplate> saxon_node::XPathProcessorJS::Constructor;
v8::Persistent<v8::FunctionTemplate> saxon_node::SchemaValidatorJS::Constructor;
v8::Persistent<v8::FunctionTemplate> saxon_node::XdmValueJS::Constructor;
v8::Persistent<v8::FunctionTemplate> saxon_node::XdmItemJS::Constructor;
v8::Persistent<v8::FunctionTemplate> saxon_node::XdmNodeJS::Constructor;
v8::Persistent<v8::FunctionTemplate> saxon_node::XdmAtomicValueJS::Constructor;

