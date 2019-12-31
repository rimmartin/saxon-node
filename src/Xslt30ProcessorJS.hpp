#pragma once
#include <map>

#include <v8.h>
#include <uv.h>
#include <node.h>
#include <node_object_wrap.h>
#include <node_buffer.h>
#include <string>
#include <cstring>
#include <memory>
#include <vector>
#include <jni.h>

#include "XdmItem.h"
#include "XdmValue.h"
#include "XsltProcessor.h"

#include "XdmValueJS.hpp"

namespace saxon_node {

    using namespace v8;

    class SaxonProcessorJS;

    class Xslt30ProcessorJS : public node::ObjectWrap {
    protected:

    public:

        static void Initialize(v8::Local<v8::Object> target) {
            v8::Isolate* isolate = v8::Isolate::GetCurrent();
            v8::Local<v8::Context> context = isolate->GetCurrentContext();
            // instantiate constructor function template
            Local<FunctionTemplate> t = FunctionTemplate::New(v8::Isolate::GetCurrent(), New);
            t->SetClassName(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Xslt30Processor", v8::NewStringType::kInternalized).ToLocalChecked());
            t->InstanceTemplate()->SetInternalFieldCount(1);
            Constructor.Reset(v8::Isolate::GetCurrent(), t);
            // member method prototypes
            NODE_SET_PROTOTYPE_METHOD(t, "setSourceFromString", setSourceFromString);
            NODE_SET_PROTOTYPE_METHOD(t, "setGlobalContextFromFile", setGlobalContextFromFile);
            NODE_SET_PROTOTYPE_METHOD(t, "setOutputfile", setOutputfile);
            NODE_SET_PROTOTYPE_METHOD(t, "setParameter", setParameter);
            NODE_SET_PROTOTYPE_METHOD(t, "getParameter", getParameter);
            NODE_SET_PROTOTYPE_METHOD(t, "removeParameter", removeParameter);
            NODE_SET_PROTOTYPE_METHOD(t, "setProperty", setProperty);
            NODE_SET_PROTOTYPE_METHOD(t, "getProperty", getProperty);
            NODE_SET_PROTOTYPE_METHOD(t, "clearParameters", clearParameters);
            NODE_SET_PROTOTYPE_METHOD(t, "transformFileToFile", transformFileToFile);
            NODE_SET_PROTOTYPE_METHOD(t, "transformFileToString", transformFileToString);
            NODE_SET_PROTOTYPE_METHOD(t, "transformToString", transformToString);
            NODE_SET_PROTOTYPE_METHOD(t, "transformToValue", transformToValue);
            NODE_SET_PROTOTYPE_METHOD(t, "compileFromFile", compileFromFile);
            NODE_SET_PROTOTYPE_METHOD(t, "compileFromString", compileFromString);
            // append this function to the target object
            target->Set(context, String::NewFromUtf8(v8::Isolate::GetCurrent(), "Xslt30Processor", v8::NewStringType::kInternalized).ToLocalChecked(), t->GetFunction(context).ToLocalChecked());
        };

        static Local<Object> Instantiate(Local<Object> proc) {
            v8::Isolate* isolate = v8::Isolate::GetCurrent();
            v8::Local<v8::Context> context = isolate->GetCurrentContext();
            const unsigned        argc       = 1;
            Local<Value> argv[1] = {

                proc

            };

            // return new group instance
            return Local<FunctionTemplate>::New(isolate, Constructor)->GetFunction(context).ToLocalChecked()->NewInstance(isolate->GetCurrentContext(), argc, argv).ToLocalChecked();

        };
    private:

        Xslt30ProcessorJS() : Xslt30ProcessorJS(false) {

        };

        Xslt30ProcessorJS(bool l) {

        };

        ~Xslt30ProcessorJS() {
        };
        static Persistent<FunctionTemplate> Constructor;

        static void New(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate* isolate = v8::Isolate::GetCurrent();
            v8::Local<v8::Context> context = isolate->GetCurrentContext();
            // create hdf file object
            Xslt30ProcessorJS* xp;
            if (args.Length() < 1)
                xp = new Xslt30ProcessorJS();
            else
                xp = new Xslt30ProcessorJS(args[1]->ToBoolean(isolate)->Value());

            xp->procJS = args[0]->ToObject(context).ToLocalChecked();
            // unwrap processor object
            xp->proc = ObjectWrap::Unwrap<SaxonProcessorJS>(args[0]->ToObject(context).ToLocalChecked());

            xp->xsltProcessor.reset(xp->proc->processor->newXslt30Processor());
            // extend target object with processor
            xp->Wrap(args.This());

            // attach various properties
            args.This()->Set(context, String::NewFromUtf8(v8::Isolate::GetCurrent(), "parameters", v8::NewStringType::kInternalized).ToLocalChecked(), Object::New(v8::Isolate::GetCurrent()));
            args.This()->Set(context, String::NewFromUtf8(v8::Isolate::GetCurrent(), "properties", v8::NewStringType::kInternalized).ToLocalChecked(), Object::New(v8::Isolate::GetCurrent()));
        };

        static void setSourceFromString(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate* isolate = v8::Isolate::GetCurrent();
            v8::Local<v8::Context> context = isolate->GetCurrentContext();
            if (args.Length() != 1 || !args[0]->IsString()) {

                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::Error(String::NewFromUtf8(v8::Isolate::GetCurrent(), "expected xml as string", v8::NewStringType::kInternalized).ToLocalChecked()));
                args.GetReturnValue().SetUndefined();
                return;

            }
            // the source
            String::Utf8Value source(isolate, args[0]->ToString(context).ToLocalChecked());
            //std::cout<<(*source)<<std::endl;
            // unwrap xsltProcessor object
            Xslt30ProcessorJS* xp = ObjectWrap::Unwrap<Xslt30ProcessorJS>(args.This());

            //xp->xsltProcessor->setSourceFromXdmNode(xp->xsltProcessor->getSaxonProcessor()->parseXmlFromString(*source));
            //std::cout<<"exceptionOccurred "<<xp->xsltProcessor->exceptionOccurred()<<std::endl;
            if(xp->xsltProcessor->exceptionOccurred() || xp->xsltProcessor->exceptionCount()>0){
                if(xp->xsltProcessor->exceptionCount()==0)xp->xsltProcessor->checkException();
                std::ostringstream ss;
                ss<<"# of exceptions: "<<std::to_string(xp->xsltProcessor->exceptionCount())<<std::endl;
                for(unsigned int exceptionIndex=0;exceptionIndex<xp->xsltProcessor->exceptionCount();exceptionIndex++){
                    ss<<xp->xsltProcessor->getErrorMessage(exceptionIndex)<<std::endl;
                }
                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::Error(String::NewFromUtf8(v8::Isolate::GetCurrent(), ss.str().c_str(), v8::NewStringType::kInternalized).ToLocalChecked()));
                args.GetReturnValue().SetUndefined();
                return;
                
            }
            args.GetReturnValue().SetUndefined();
        };

        static void setOutputfile(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::Error(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method", v8::NewStringType::kInternalized).ToLocalChecked()));
            args.GetReturnValue().SetUndefined();
        };

        static void setParameter(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::Error(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method", v8::NewStringType::kInternalized).ToLocalChecked()));
            args.GetReturnValue().SetUndefined();
        };

        static void getParameter(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::Error(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method", v8::NewStringType::kInternalized).ToLocalChecked()));
            args.GetReturnValue().SetUndefined();
        };

        static void removeParameter(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::Error(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method", v8::NewStringType::kInternalized).ToLocalChecked()));
            args.GetReturnValue().SetUndefined();
        };

        static void setProperty(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::Error(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method", v8::NewStringType::kInternalized).ToLocalChecked()));
            args.GetReturnValue().SetUndefined();
        };

        static void getProperty(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::Error(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method", v8::NewStringType::kInternalized).ToLocalChecked()));
            args.GetReturnValue().SetUndefined();
        };

        static void clearParameters(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::Error(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method", v8::NewStringType::kInternalized).ToLocalChecked()));
            args.GetReturnValue().SetUndefined();
        };

        static void clearProperties(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::Error(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method", v8::NewStringType::kInternalized).ToLocalChecked()));
            args.GetReturnValue().SetUndefined();
        };

        static void transformFileToFile(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate* isolate = v8::Isolate::GetCurrent();
            v8::Local<v8::Context> context = isolate->GetCurrentContext();
            if(args.Length()!=3 || !args[0]->IsString() || !args[1]->IsString() || !args[2]->IsString())
            {
                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::Error(String::NewFromUtf8(v8::Isolate::GetCurrent(), "not correct arguments", v8::NewStringType::kInternalized).ToLocalChecked()));
                args.GetReturnValue().SetUndefined();
            }
            // unwrap xsltProcessor object
            Xslt30ProcessorJS* xp = ObjectWrap::Unwrap<Xslt30ProcessorJS>(args.This());
            Local<Object> parameters=args.This()->Get(context, String::NewFromUtf8(v8::Isolate::GetCurrent(), "parameters", v8::NewStringType::kInternalized).ToLocalChecked()).ToLocalChecked()->ToObject(context).ToLocalChecked();
            Local<Array> parameterNames=parameters->GetOwnPropertyNames(context).ToLocalChecked();
            for(uint32_t index=0;index<parameterNames->Length();index++)
            {
                String::Utf8Value pn(isolate, parameterNames->Get(context, index).ToLocalChecked()->ToObject(context).ToLocalChecked());
                xp->xsltProcessor->setParameter(*pn, (XdmValue*)xp->makeParameter(xp, parameters->Get(context, parameterNames->Get(context, index).ToLocalChecked()->ToString(context).ToLocalChecked()).ToLocalChecked()));
            }
            // the source
            String::Utf8Value sourceFile(isolate, args[0]->ToString(context).ToLocalChecked());
            String::Utf8Value stylesheetfile(isolate, args[1]->ToString(context).ToLocalChecked());
            String::Utf8Value outputfile(isolate, args[2]->ToString(context).ToLocalChecked());
            xp->xsltProcessor->transformFileToFile((*sourceFile), (*stylesheetfile), (*outputfile));
            args.GetReturnValue().SetUndefined();
        };

        static void transformFileToString(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate* isolate = v8::Isolate::GetCurrent();
            v8::Local<v8::Context> context = isolate->GetCurrentContext();
            if (args.Length() < 1 || !args[0]->IsString()) {

                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::Error(String::NewFromUtf8(v8::Isolate::GetCurrent(), "expected at least xml source file as string", v8::NewStringType::kInternalized).ToLocalChecked()));
                args.GetReturnValue().SetUndefined();
                return;

            }
            Local<Object> parameters=args.This()->Get(context, String::NewFromUtf8(v8::Isolate::GetCurrent(), "parameters", v8::NewStringType::kInternalized).ToLocalChecked()).ToLocalChecked()->ToObject(context).ToLocalChecked();
            Local<Array> parameterNames=parameters->GetOwnPropertyNames(context).ToLocalChecked();
            Local<Object> properties=args.This()->Get(context, String::NewFromUtf8(v8::Isolate::GetCurrent(), "properties", v8::NewStringType::kInternalized).ToLocalChecked()).ToLocalChecked()->ToObject(context).ToLocalChecked();
            Local<Array> propertyNames=properties->GetOwnPropertyNames(context).ToLocalChecked();
            switch(args.Length())
            {
                case 1:
                    if(args[0]->IsString())
                    {
                        // unwrap xsltProcessor object
                        Xslt30ProcessorJS* xp = ObjectWrap::Unwrap<Xslt30ProcessorJS>(args.This());
                        for(uint32_t index=0;index<parameterNames->Length();index++)
                        {
                            String::Utf8Value pn(isolate, parameterNames->Get(context, index).ToLocalChecked()->ToObject(context).ToLocalChecked());
                            xp->xsltProcessor->setParameter(*pn, (XdmValue*)xp->makeParameter(xp, parameters->Get(context, parameterNames->Get(context, index).ToLocalChecked()->ToString(context).ToLocalChecked()).ToLocalChecked()));
                        }
                        // the source
                        String::Utf8Value source(isolate, args[0]->ToString(context).ToLocalChecked());
                        const char* buffer=xp->xsltProcessor->transformFileToString((*source), NULL);
                        //std::cout<<"exceptionOccurred "<<xp->xsltProcessor->exceptionOccurred()<<std::endl;
                        if(xp->xsltProcessor->exceptionOccurred() || xp->xsltProcessor->exceptionCount()>0){
                            if(xp->xsltProcessor->exceptionCount()==0)xp->xsltProcessor->checkException();
                            std::ostringstream ss;
                            ss<<"# of exceptions: "<<std::to_string(xp->xsltProcessor->exceptionCount())<<std::endl;
                            for(unsigned int exceptionIndex=0;exceptionIndex<xp->xsltProcessor->exceptionCount();exceptionIndex++){
                                ss<<xp->xsltProcessor->getErrorMessage(exceptionIndex)<<std::endl;
                            }
                            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::Error(String::NewFromUtf8(v8::Isolate::GetCurrent(), ss.str().c_str(), v8::NewStringType::kInternalized).ToLocalChecked()));
                            args.GetReturnValue().SetUndefined();
                            break;
                            
                        }
                        args.GetReturnValue().Set(node::Buffer::New(v8::Isolate::GetCurrent(), (char*)buffer, std::strlen(buffer)).ToLocalChecked());
                    }
                    break;
                case 2:
                    if(args[0]->IsString() && args[1]->IsString())
                    {
                        // unwrap xsltProcessor object
                        Xslt30ProcessorJS* xp = ObjectWrap::Unwrap<Xslt30ProcessorJS>(args.This());
                        //if(args.This()->IsDirty())
                        {
                        for(uint32_t index=0;index<parameterNames->Length();index++)
                        {
                            String::Utf8Value pn(isolate, parameterNames->Get(context, index).ToLocalChecked()->ToObject(context).ToLocalChecked());
                            xp->xsltProcessor->setParameter(*pn, (XdmValue*)xp->makeParameter(xp, parameters->Get(context, parameterNames->Get(context, index).ToLocalChecked()->ToString(context).ToLocalChecked()).ToLocalChecked()));
                        }
                        for(uint32_t index=0;index<propertyNames->Length();index++)
                        {
                            Local<Object> obj=propertyNames->Get(context, index).ToLocalChecked()->ToObject(context).ToLocalChecked();
                            String::Utf8Value pn(isolate, obj->ToString(context).ToLocalChecked());
                            String::Utf8Value pnValue(isolate, properties->Get(context, propertyNames->Get(context, index).ToLocalChecked()->ToString(context).ToLocalChecked()).ToLocalChecked()->ToString(context).ToLocalChecked());
//                            std::cout<<(*pn)<<" "<<(*pnValue)<<std::endl;
                            xp->xsltProcessor->setProperty(*pn, *pnValue);
                        }
                        }
                        // the source
                        String::Utf8Value sourceFile(isolate, args[0]->ToString(context).ToLocalChecked());
                        String::Utf8Value stylesheetfile(isolate, args[1]->ToString(context).ToLocalChecked());
                        const char* buffer=xp->xsltProcessor->transformFileToString((*sourceFile), (*stylesheetfile));
                        //std::cout<<"exceptionOccurred "<<xp->xsltProcessor->exceptionOccurred()<<std::endl;
                        if(xp->xsltProcessor->exceptionOccurred() || xp->xsltProcessor->exceptionCount()>0){
                            if(xp->xsltProcessor->exceptionCount()==0)xp->xsltProcessor->checkException();
                            std::ostringstream ss;
                            ss<<"# of exceptions: "<<std::to_string(xp->xsltProcessor->exceptionCount())<<std::endl;
                            for(unsigned int exceptionIndex=0;exceptionIndex<xp->xsltProcessor->exceptionCount();exceptionIndex++){
                                ss<<xp->xsltProcessor->getErrorMessage(exceptionIndex)<<std::endl;
                            }
                            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::Error(String::NewFromUtf8(v8::Isolate::GetCurrent(), ss.str().c_str(), v8::NewStringType::kInternalized).ToLocalChecked()));
                            args.GetReturnValue().SetUndefined();
                            break;
                            
                        }
                        args.GetReturnValue().Set(node::Buffer::New(v8::Isolate::GetCurrent(), (char*)buffer, std::strlen(buffer)).ToLocalChecked());
                    }
                    break;
            }
        };

        static void setGlobalContextFromFile(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate* isolate = v8::Isolate::GetCurrent();
            v8::Local<v8::Context> context = isolate->GetCurrentContext();
            if (args.Length() != 1 || !args[0]->IsString()) {

                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::Error(String::NewFromUtf8(v8::Isolate::GetCurrent(), "expected xml source as string", v8::NewStringType::kInternalized).ToLocalChecked()));
                args.GetReturnValue().SetUndefined();
                return;

            }
            // the source
            String::Utf8Value source(isolate, args[0]->ToString(context).ToLocalChecked());
            //std::cout<<(*source)<<std::endl;
            // unwrap xsltProcessor object
            Xslt30ProcessorJS* xp = ObjectWrap::Unwrap<Xslt30ProcessorJS>(args.This());
            xp->xsltProcessor->setGlobalContextFromFile(*source);
            //std::cout<<"exceptionOccurred "<<xp->xsltProcessor->exceptionOccurred()<<std::endl;
            if(xp->xsltProcessor->exceptionOccurred() || xp->xsltProcessor->exceptionCount()>0){
                if(xp->xsltProcessor->exceptionCount()==0)xp->xsltProcessor->checkException();
                std::ostringstream ss;
                ss<<"# of exceptions: "<<std::to_string(xp->xsltProcessor->exceptionCount())<<std::endl;
                for(unsigned int exceptionIndex=0;exceptionIndex<xp->xsltProcessor->exceptionCount();exceptionIndex++){
                    ss<<xp->xsltProcessor->getErrorMessage(exceptionIndex)<<std::endl;
                }
                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::Error(String::NewFromUtf8(v8::Isolate::GetCurrent(), ss.str().c_str(), v8::NewStringType::kInternalized).ToLocalChecked()));
                args.GetReturnValue().SetUndefined();
                return;
                
            }
            args.GetReturnValue().SetUndefined();
        };

        static void compileFromFile(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate* isolate = v8::Isolate::GetCurrent();
            v8::Local<v8::Context> context = isolate->GetCurrentContext();
            if (args.Length() != 1 || !args[0]->IsString()) {

                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::Error(String::NewFromUtf8(v8::Isolate::GetCurrent(), "expected stylesheet as string", v8::NewStringType::kInternalized).ToLocalChecked()));
                args.GetReturnValue().SetUndefined();
                return;

            }
            // the stylesheet
            String::Utf8Value stylesheet(isolate, args[0]->ToString(context).ToLocalChecked());
            //std::cout<<(*stylesheet)<<std::endl;
            // unwrap xsltProcessor object
            Xslt30ProcessorJS* xp = ObjectWrap::Unwrap<Xslt30ProcessorJS>(args.This());
            try{
                xp->xsltProcessor->compileFromFile(*stylesheet);
                //std::cout<<"exceptionOccurred "<<xp->xsltProcessor->exceptionOccurred()<<std::endl;
                if(xp->xsltProcessor->exceptionOccurred() || xp->xsltProcessor->exceptionCount()>0){
                    if(xp->xsltProcessor->exceptionCount()==0)xp->xsltProcessor->checkException();
                    std::ostringstream ss;
                    ss<<"# of exceptions: "<<std::to_string(xp->xsltProcessor->exceptionCount())<<std::endl;
                    for(unsigned int exceptionIndex=0;exceptionIndex<xp->xsltProcessor->exceptionCount();exceptionIndex++){
                        ss<<xp->xsltProcessor->getErrorMessage(exceptionIndex)<<std::endl;
                    }
                    v8::Isolate::GetCurrent()->ThrowException(v8::Exception::Error(String::NewFromUtf8(v8::Isolate::GetCurrent(), ss.str().c_str(), v8::NewStringType::kInternalized).ToLocalChecked()));
                    args.GetReturnValue().SetUndefined();
                    return;
                    
                }
            }
            catch(SaxonApiException& ex){
 	            for(unsigned int i =0; i< ex.count();i++) {
 	                std::cout<<"std::exception "<<ex.getErrorCode(i)<<std::endl;
 	            }
            }
            catch(std::exception& ex){
                std::cout<<"std::exception "<<ex.what()<<std::endl;
            }
            catch(...){
                std::cout<<"compiled failed "<<std::endl;
            }
            args.GetReturnValue().SetUndefined();

        };

        static void compileFromString(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate* isolate = v8::Isolate::GetCurrent();
            v8::Local<v8::Context> context = isolate->GetCurrentContext();
                if (args.Length() != 1 || !args[0]->IsString()) {

                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::Error(String::NewFromUtf8(v8::Isolate::GetCurrent(), "expected stylesheet as string", v8::NewStringType::kInternalized).ToLocalChecked()));
                args.GetReturnValue().SetUndefined();
                return;

            }
            // the stylesheet
            String::Utf8Value stylesheet(isolate, args[0]->ToString(context).ToLocalChecked());
            //std::cout<<(*stylesheet)<<std::endl;
            // unwrap xsltProcessor object
            Xslt30ProcessorJS* xp = ObjectWrap::Unwrap<Xslt30ProcessorJS>(args.This());
            try{
                xp->xsltProcessor->compileFromString(*stylesheet);
                //std::cout<<"exceptionOccurred "<<xp->xsltProcessor->exceptionOccurred()<<std::endl;
                if(xp->xsltProcessor->exceptionOccurred() || xp->xsltProcessor->exceptionCount()>0){
                    if(xp->xsltProcessor->exceptionCount()==0)xp->xsltProcessor->checkException();
                    std::ostringstream ss;
                    ss<<"# of exceptions: "<<std::to_string(xp->xsltProcessor->exceptionCount())<<std::endl;
                    for(unsigned int exceptionIndex=0;exceptionIndex<xp->xsltProcessor->exceptionCount();exceptionIndex++){
                        ss<<xp->xsltProcessor->getErrorMessage(exceptionIndex)<<std::endl;
                    }
                    v8::Isolate::GetCurrent()->ThrowException(v8::Exception::Error(String::NewFromUtf8(v8::Isolate::GetCurrent(), ss.str().c_str(), v8::NewStringType::kInternalized).ToLocalChecked()));
                    args.GetReturnValue().SetUndefined();
                    return;
                    
                }
            }
            catch(SaxonApiException& ex){
 	            for(unsigned int i =0; i< ex.count();i++) {
 	                std::cout<<"std::exception "<<ex.getErrorCode(i)<<std::endl;
 	            }
            }
            catch(std::exception& ex){
                std::cout<<"std::exception "<<ex.what()<<std::endl;
            }
            catch(...){
                std::cout<<"compiled failed "<<std::endl;
            }
            args.GetReturnValue().SetUndefined();
        };

        static void transformToString(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate* isolate = v8::Isolate::GetCurrent();
            v8::Local<v8::Context> context = isolate->GetCurrentContext();
            if (args.Length() != 1) {

                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::Error(String::NewFromUtf8(v8::Isolate::GetCurrent(), "source expected", v8::NewStringType::kInternalized).ToLocalChecked()));
                args.GetReturnValue().SetUndefined();
                return;

            }
            Local<Object> parameters=args.This()->Get(context, String::NewFromUtf8(v8::Isolate::GetCurrent(), "parameters", v8::NewStringType::kInternalized).ToLocalChecked()).ToLocalChecked()->ToObject(context).ToLocalChecked();
            Local<Array> parameterNames=parameters->GetOwnPropertyNames(context).ToLocalChecked();
            Local<Object> properties=args.This()->Get(context, String::NewFromUtf8(v8::Isolate::GetCurrent(), "properties", v8::NewStringType::kInternalized).ToLocalChecked()).ToLocalChecked()->ToObject(context).ToLocalChecked();
            Local<Array> propertyNames=properties->GetOwnPropertyNames(context).ToLocalChecked();
            // unwrap xsltProcessor object
            Xslt30ProcessorJS* xp = ObjectWrap::Unwrap<Xslt30ProcessorJS>(args.This());
            for(uint32_t index=0;index<parameterNames->Length();index++)
            {
                String::Utf8Value pn(isolate, parameterNames->Get(context, index).ToLocalChecked()->ToObject(context).ToLocalChecked());
                xp->xsltProcessor->setParameter(*pn, (XdmValue*)xp->makeParameter(xp, parameters->Get(context, parameterNames->Get(context, index).ToLocalChecked()->ToString(context).ToLocalChecked()).ToLocalChecked()));
            }
            XdmNodeJS* source = ObjectWrap::Unwrap<XdmNodeJS>(args[0]->ToObject(context).ToLocalChecked());
            const char* buffer=xp->xsltProcessor->transformToString(source->value);
            //std::cout<<"exceptionOccurred "<<xp->xsltProcessor->exceptionOccurred()<<std::endl;
            if(xp->xsltProcessor->exceptionOccurred() || xp->xsltProcessor->exceptionCount()>0){
                if(xp->xsltProcessor->exceptionCount()==0)xp->xsltProcessor->checkException();
                std::ostringstream ss;
                ss<<"# of exceptions: "<<std::to_string(xp->xsltProcessor->exceptionCount())<<std::endl;
                for(unsigned int exceptionIndex=0;exceptionIndex<xp->xsltProcessor->exceptionCount();exceptionIndex++){
                    ss<<xp->xsltProcessor->getErrorMessage(exceptionIndex)<<std::endl;
                }
                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::Error(String::NewFromUtf8(v8::Isolate::GetCurrent(), ss.str().c_str(), v8::NewStringType::kInternalized).ToLocalChecked()));
                args.GetReturnValue().SetUndefined();
                return;
                
            }
            args.GetReturnValue().Set(node::Buffer::New(v8::Isolate::GetCurrent(), (char*)buffer, std::strlen(buffer)).ToLocalChecked());
        };

        static void transformToValue(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate* isolate = v8::Isolate::GetCurrent();
            v8::Local<v8::Context> context = isolate->GetCurrentContext();
            if (args.Length() != 1) {

                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::Error(String::NewFromUtf8(v8::Isolate::GetCurrent(), "source expected", v8::NewStringType::kInternalized).ToLocalChecked()));
                args.GetReturnValue().SetUndefined();
                return;

            }
            Local<Object> parameters=args.This()->Get(context, String::NewFromUtf8(v8::Isolate::GetCurrent(), "parameters", v8::NewStringType::kInternalized).ToLocalChecked()).ToLocalChecked()->ToObject(context).ToLocalChecked();
            Local<Array> parameterNames=parameters->GetOwnPropertyNames(context).ToLocalChecked();
            Local<Object> properties=args.This()->Get(context, String::NewFromUtf8(v8::Isolate::GetCurrent(), "properties", v8::NewStringType::kInternalized).ToLocalChecked()).ToLocalChecked()->ToObject(context).ToLocalChecked();
            Local<Array> propertyNames=properties->GetOwnPropertyNames(context).ToLocalChecked();
            // unwrap xsltProcessor object
            Xslt30ProcessorJS* xp = ObjectWrap::Unwrap<Xslt30ProcessorJS>(args.This());
            for(uint32_t index=0;index<parameterNames->Length();index++)
            {
                String::Utf8Value pn(isolate, parameterNames->Get(context, index).ToLocalChecked()->ToObject(context).ToLocalChecked());
                xp->xsltProcessor->setParameter(*pn, (XdmValue*)xp->makeParameter(xp, parameters->Get(context, parameterNames->Get(context, index).ToLocalChecked()->ToString(context).ToLocalChecked()).ToLocalChecked()));
            }
            XdmNodeJS* source = ObjectWrap::Unwrap<XdmNodeJS>(args[0]->ToObject(context).ToLocalChecked());
            XdmValue* buffer=xp->xsltProcessor->transformToValue(source->value);
            //std::cout<<"exceptionOccurred "<<xp->xsltProcessor->exceptionOccurred()<<std::endl;
            if(xp->xsltProcessor->exceptionOccurred() || xp->xsltProcessor->exceptionCount()>0){
                if(xp->xsltProcessor->exceptionCount()==0)xp->xsltProcessor->checkException();
                std::ostringstream ss;
                ss<<"# of exceptions: "<<std::to_string(xp->xsltProcessor->exceptionCount())<<std::endl;
                for(unsigned int exceptionIndex=0;exceptionIndex<xp->xsltProcessor->exceptionCount();exceptionIndex++){
                    ss<<xp->xsltProcessor->getErrorMessage(exceptionIndex)<<std::endl;
                }
                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::Error(String::NewFromUtf8(v8::Isolate::GetCurrent(), ss.str().c_str(), v8::NewStringType::kInternalized).ToLocalChecked()));
                args.GetReturnValue().SetUndefined();
                return;
                
            }
            Local<Object> instance=XdmValueJS::Instantiate(args.This());
            XdmValueJS* xdmValue = new XdmValueJS();
            xdmValue->value=buffer;
            xdmValue->Wrap(instance);
            args.GetReturnValue().Set(instance);
        };

        static void exceptionOccurred(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::Error(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method", v8::NewStringType::kInternalized).ToLocalChecked()));
            args.GetReturnValue().SetUndefined();
        };

    inline XdmAtomicValue* makeParameter(Xslt30ProcessorJS* xp, v8::Local<v8::Value> p){
        v8::Isolate* isolate = v8::Isolate::GetCurrent();
        v8::Local<v8::Context> context = isolate->GetCurrentContext();
        if(p->IsBoolean()){
            return xp->xsltProcessor->getSaxonProcessor()->makeBooleanValue(p->BooleanValue(isolate));
        }
        else if(p->IsInt32() || p->IsUint32()){
            return xp->xsltProcessor->getSaxonProcessor()->makeIntegerValue(p->IntegerValue(context).ToChecked());
        }
        else if(p->IsNumber()){
            return xp->xsltProcessor->getSaxonProcessor()->makeDoubleValue(p->NumberValue(context).ToChecked());
        }
        else{
                String::Utf8Value pnValue(isolate, p->ToString(context).ToLocalChecked());
//                        std::cout<<(*pn)<<" "<<(*pnValue)<<std::endl;
            return xp->xsltProcessor->getSaxonProcessor()->makeStringValue(*pnValue);
        }
    }
    
    private:
        Local<Object> procJS;
        SaxonProcessorJS* proc;
        std::shared_ptr<Xslt30Processor> xsltProcessor;
        XdmValue* value;

    };

};
