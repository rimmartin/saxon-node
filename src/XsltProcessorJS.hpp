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

    class XsltProcessorJS : public node::ObjectWrap {
    protected:

    public:

        static void Initialize(Handle<Object> target) {
            // instantiate constructor function template
            Local<FunctionTemplate> t = FunctionTemplate::New(v8::Isolate::GetCurrent(), New);
            t->SetClassName(String::NewFromUtf8(v8::Isolate::GetCurrent(), "XsltProcessor"));
            t->InstanceTemplate()->SetInternalFieldCount(1);
            Constructor.Reset(v8::Isolate::GetCurrent(), t);
            // member method prototypes
            NODE_SET_PROTOTYPE_METHOD(t, "setSourceFromString", setSourceFromString);
            NODE_SET_PROTOTYPE_METHOD(t, "setSourceFromFile", setSourceFromFile);
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
            //        Local<Function> f=t->GetFunction();
            // append this function to the target object
            target->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "XsltProcessor"), t->GetFunction());
        };

        static Local<Object> Instantiate(Local<Object> proc) {
            Local<Value> argv[1] = {

                proc

            };

            // return new group instance
            return Local<FunctionTemplate>::New(v8::Isolate::GetCurrent(), Constructor)->GetFunction()->NewInstance(1, argv);

        };
    private:

        XsltProcessorJS() : XsltProcessorJS(false) {

        };

        XsltProcessorJS(bool l) {

        };

        ~XsltProcessorJS() {
        };
        static Persistent<FunctionTemplate> Constructor;

        static void New(const v8::FunctionCallbackInfo<Value>& args) {
            // create hdf file object
            XsltProcessorJS* xp;
            if (args.Length() < 1)
                xp = new XsltProcessorJS();
            else
                xp = new XsltProcessorJS(args[1]->ToBoolean()->BooleanValue());

            xp->procJS = args[0]->ToObject();
            // unwrap processor object
            xp->proc = ObjectWrap::Unwrap<SaxonProcessorJS>(args[0]->ToObject());

            xp->xsltProcessor.reset(xp->proc->processor->newXsltProcessor());
            // extend target object with processor
            xp->Wrap(args.This());

            // attach various properties
            args.This()->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "parameters"), Object::New(v8::Isolate::GetCurrent()));
            args.This()->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "properties"), Object::New(v8::Isolate::GetCurrent()));
        };

        static void setSourceFromString(const v8::FunctionCallbackInfo<Value>& args) {
            if (args.Length() != 1 || !args[0]->IsString()) {

                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "expected xml as string")));
                args.GetReturnValue().SetUndefined();
                return;

            }
            // the source
            String::Utf8Value source(args[0]->ToString());
            //std::cout<<(*source)<<std::endl;
            // unwrap xsltProcessor object
            XsltProcessorJS* xp = ObjectWrap::Unwrap<XsltProcessorJS>(args.This());

            xp->xsltProcessor->setSourceFromXdmValue((XdmItem*)xp->xsltProcessor->getSaxonProcessor()->parseXmlFromString(*source));
            //std::cout<<"exceptionOccurred "<<xp->xsltProcessor->exceptionOccurred()<<std::endl;
            if(xp->xsltProcessor->exceptionOccurred() || xp->xsltProcessor->exceptionCount()>0){
                if(xp->xsltProcessor->exceptionCount()==0)xp->xsltProcessor->checkException();
                std::ostringstream ss;
                ss<<"# of exceptions: "<<std::to_string(xp->xsltProcessor->exceptionCount())<<std::endl;
                for(unsigned int exceptionIndex=0;exceptionIndex<xp->xsltProcessor->exceptionCount();exceptionIndex++){
                    ss<<xp->xsltProcessor->getErrorMessage(exceptionIndex)<<std::endl;
                }
                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), ss.str().c_str())));
                args.GetReturnValue().SetUndefined();
                return;
                
            }
            args.GetReturnValue().SetUndefined();
        };

        static void setOutputfile(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

        static void setParameter(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

        static void getParameter(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

        static void removeParameter(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

        static void setProperty(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

        static void getProperty(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

        static void clearParameters(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

        static void clearProperties(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

        static void transformFileToFile(const v8::FunctionCallbackInfo<Value>& args) {
            if(args.Length()!=3 || !args[0]->IsString() || !args[1]->IsString() || !args[2]->IsString())
            {
                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "not correct arguments")));
                args.GetReturnValue().SetUndefined();
            }
            // unwrap xsltProcessor object
            XsltProcessorJS* xp = ObjectWrap::Unwrap<XsltProcessorJS>(args.This());
            Local<Object> parameters=args.This()->Get(String::NewFromUtf8(v8::Isolate::GetCurrent(), "parameters"))->ToObject();
            Local<Array> parameterNames=parameters->GetOwnPropertyNames();
            for(uint32_t index=0;index<parameterNames->Length();index++)
            {
                String::Utf8Value pn(parameterNames->Get(index)->ToObject());
                xp->xsltProcessor->setParameter(*pn, (XdmValue*)xp->makeParameter(xp, parameters->Get(parameterNames->Get(index)->ToString())));
            }
            // the source
            String::Utf8Value sourceFile(args[0]->ToString());
            String::Utf8Value stylesheetfile(args[1]->ToString());
            String::Utf8Value outputfile(args[2]->ToString());
            xp->xsltProcessor->transformFileToFile((*sourceFile), (*stylesheetfile), (*outputfile));
            args.GetReturnValue().SetUndefined();
        };

        static void transformFileToString(const v8::FunctionCallbackInfo<Value>& args) {
            if (args.Length() < 1 || !args[0]->IsString()) {

                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "expected at least xml source file as string")));
                args.GetReturnValue().SetUndefined();
                return;

            }
            Local<Object> parameters=args.This()->Get(String::NewFromUtf8(v8::Isolate::GetCurrent(), "parameters"))->ToObject();
            Local<Array> parameterNames=parameters->GetOwnPropertyNames();
            Local<Object> properties=args.This()->Get(String::NewFromUtf8(v8::Isolate::GetCurrent(), "properties"))->ToObject();
            Local<Array> propertyNames=properties->GetOwnPropertyNames();
            switch(args.Length())
            {
                case 1:
                    if(args[0]->IsString())
                    {
                        // unwrap xsltProcessor object
                        XsltProcessorJS* xp = ObjectWrap::Unwrap<XsltProcessorJS>(args.This());
                        for(uint32_t index=0;index<parameterNames->Length();index++)
                        {
                            String::Utf8Value pn(parameterNames->Get(index)->ToObject());
                            xp->xsltProcessor->setParameter(*pn, (XdmValue*)xp->makeParameter(xp, parameters->Get(parameterNames->Get(index)->ToString())));
                        }
                        // the source
                        String::Utf8Value source(args[0]->ToString());
                        const char* buffer=xp->xsltProcessor->transformFileToString((*source), NULL);
                        //std::cout<<"exceptionOccurred "<<xp->xsltProcessor->exceptionOccurred()<<std::endl;
                        if(xp->xsltProcessor->exceptionOccurred() || xp->xsltProcessor->exceptionCount()>0){
                            if(xp->xsltProcessor->exceptionCount()==0)xp->xsltProcessor->checkException();
                            std::ostringstream ss;
                            ss<<"# of exceptions: "<<std::to_string(xp->xsltProcessor->exceptionCount())<<std::endl;
                            for(unsigned int exceptionIndex=0;exceptionIndex<xp->xsltProcessor->exceptionCount();exceptionIndex++){
                                ss<<xp->xsltProcessor->getErrorMessage(exceptionIndex)<<std::endl;
                            }
                            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), ss.str().c_str())));
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
                        XsltProcessorJS* xp = ObjectWrap::Unwrap<XsltProcessorJS>(args.This());
                        //if(args.This()->IsDirty())
                        {
                        for(uint32_t index=0;index<parameterNames->Length();index++)
                        {
                            String::Utf8Value pn(parameterNames->Get(index)->ToObject());
                            xp->xsltProcessor->setParameter(*pn, (XdmValue*)xp->makeParameter(xp, parameters->Get(parameterNames->Get(index)->ToString())));
                        }
                        for(uint32_t index=0;index<propertyNames->Length();index++)
                        {
                            Local<Object> obj=propertyNames->Get(index)->ToObject();
                            String::Utf8Value pn(obj->ToString());
                            String::Utf8Value pnValue(properties->Get(propertyNames->Get(index)->ToString())->ToString());
//                            std::cout<<(*pn)<<" "<<(*pnValue)<<std::endl;
                            xp->xsltProcessor->setProperty(*pn, *pnValue);
                        }
                        }
                        // the source
                        String::Utf8Value sourceFile(args[0]->ToString());
                        String::Utf8Value stylesheetfile(args[1]->ToString());
                        const char* buffer=xp->xsltProcessor->transformFileToString((*sourceFile), (*stylesheetfile));
                        //std::cout<<"exceptionOccurred "<<xp->xsltProcessor->exceptionOccurred()<<std::endl;
                        if(xp->xsltProcessor->exceptionOccurred() || xp->xsltProcessor->exceptionCount()>0){
                            if(xp->xsltProcessor->exceptionCount()==0)xp->xsltProcessor->checkException();
                            std::ostringstream ss;
                            ss<<"# of exceptions: "<<std::to_string(xp->xsltProcessor->exceptionCount())<<std::endl;
                            for(unsigned int exceptionIndex=0;exceptionIndex<xp->xsltProcessor->exceptionCount();exceptionIndex++){
                                ss<<xp->xsltProcessor->getErrorMessage(exceptionIndex)<<std::endl;
                            }
                            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), ss.str().c_str())));
                            args.GetReturnValue().SetUndefined();
                            break;
                            
                        }
                        args.GetReturnValue().Set(node::Buffer::New(v8::Isolate::GetCurrent(), (char*)buffer, std::strlen(buffer)).ToLocalChecked());
                    }
                    break;
            }
        };

        static void setSourceFromFile(const v8::FunctionCallbackInfo<Value>& args) {
            if (args.Length() != 1 || !args[0]->IsString()) {

                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "expected xml source as string")));
                args.GetReturnValue().SetUndefined();
                return;

            }
            // the source
            String::Utf8Value source(args[0]->ToString());
            //std::cout<<(*source)<<std::endl;
            // unwrap xsltProcessor object
            XsltProcessorJS* xp = ObjectWrap::Unwrap<XsltProcessorJS>(args.This());
            xp->xsltProcessor->setSourceFromFile(*source);
            //std::cout<<"exceptionOccurred "<<xp->xsltProcessor->exceptionOccurred()<<std::endl;
            if(xp->xsltProcessor->exceptionOccurred() || xp->xsltProcessor->exceptionCount()>0){
                if(xp->xsltProcessor->exceptionCount()==0)xp->xsltProcessor->checkException();
                std::ostringstream ss;
                ss<<"# of exceptions: "<<std::to_string(xp->xsltProcessor->exceptionCount())<<std::endl;
                for(unsigned int exceptionIndex=0;exceptionIndex<xp->xsltProcessor->exceptionCount();exceptionIndex++){
                    ss<<xp->xsltProcessor->getErrorMessage(exceptionIndex)<<std::endl;
                }
                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), ss.str().c_str())));
                args.GetReturnValue().SetUndefined();
                return;
                
            }
            args.GetReturnValue().SetUndefined();
        };

        static void compileFromFile(const v8::FunctionCallbackInfo<Value>& args) {
            if (args.Length() != 1 || !args[0]->IsString()) {

                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "expected stylesheet as string")));
                args.GetReturnValue().SetUndefined();
                return;

            }
            // the stylesheet
            String::Utf8Value stylesheet(args[0]->ToString());
            //std::cout<<(*stylesheet)<<std::endl;
            // unwrap xsltProcessor object
            XsltProcessorJS* xp = ObjectWrap::Unwrap<XsltProcessorJS>(args.This());
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
                    v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), ss.str().c_str())));
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
            if (args.Length() != 1 || !args[0]->IsString()) {

                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "expected stylesheet as string")));
                args.GetReturnValue().SetUndefined();
                return;

            }
            // the stylesheet
            String::Utf8Value stylesheet(args[0]->ToString());
            //std::cout<<(*stylesheet)<<std::endl;
            // unwrap xsltProcessor object
            XsltProcessorJS* xp = ObjectWrap::Unwrap<XsltProcessorJS>(args.This());
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
                    v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), ss.str().c_str())));
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
            if (args.Length() != 0) {

                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "no arg(s) expected")));
                args.GetReturnValue().SetUndefined();
                return;

            }
            Local<Object> parameters=args.This()->Get(String::NewFromUtf8(v8::Isolate::GetCurrent(), "parameters"))->ToObject();
            Local<Array> parameterNames=parameters->GetOwnPropertyNames();
            Local<Object> properties=args.This()->Get(String::NewFromUtf8(v8::Isolate::GetCurrent(), "properties"))->ToObject();
            Local<Array> propertyNames=properties->GetOwnPropertyNames();
            // unwrap xsltProcessor object
            XsltProcessorJS* xp = ObjectWrap::Unwrap<XsltProcessorJS>(args.This());
            for(uint32_t index=0;index<parameterNames->Length();index++)
            {
                String::Utf8Value pn(parameterNames->Get(index)->ToObject());
                xp->xsltProcessor->setParameter(*pn, (XdmValue*)xp->makeParameter(xp, parameters->Get(parameterNames->Get(index)->ToString())));
            }
            const char* buffer=xp->xsltProcessor->transformToString();
            //std::cout<<"exceptionOccurred "<<xp->xsltProcessor->exceptionOccurred()<<std::endl;
            if(xp->xsltProcessor->exceptionOccurred() || xp->xsltProcessor->exceptionCount()>0){
                if(xp->xsltProcessor->exceptionCount()==0)xp->xsltProcessor->checkException();
                std::ostringstream ss;
                ss<<"# of exceptions: "<<std::to_string(xp->xsltProcessor->exceptionCount())<<std::endl;
                for(unsigned int exceptionIndex=0;exceptionIndex<xp->xsltProcessor->exceptionCount();exceptionIndex++){
                    ss<<xp->xsltProcessor->getErrorMessage(exceptionIndex)<<std::endl;
                }
                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), ss.str().c_str())));
                args.GetReturnValue().SetUndefined();
                return;
                
            }
            args.GetReturnValue().Set(node::Buffer::New(v8::Isolate::GetCurrent(), (char*)buffer, std::strlen(buffer)).ToLocalChecked());
        };

        static void transformToValue(const v8::FunctionCallbackInfo<Value>& args) {
            if (args.Length() != 0) {

                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "no arg(s) expected")));
                args.GetReturnValue().SetUndefined();
                return;

            }
            Local<Object> parameters=args.This()->Get(String::NewFromUtf8(v8::Isolate::GetCurrent(), "parameters"))->ToObject();
            Local<Array> parameterNames=parameters->GetOwnPropertyNames();
            Local<Object> properties=args.This()->Get(String::NewFromUtf8(v8::Isolate::GetCurrent(), "properties"))->ToObject();
            Local<Array> propertyNames=properties->GetOwnPropertyNames();
            // unwrap xsltProcessor object
            XsltProcessorJS* xp = ObjectWrap::Unwrap<XsltProcessorJS>(args.This());
            for(uint32_t index=0;index<parameterNames->Length();index++)
            {
                String::Utf8Value pn(parameterNames->Get(index)->ToObject());
                xp->xsltProcessor->setParameter(*pn, (XdmValue*)xp->makeParameter(xp, parameters->Get(parameterNames->Get(index)->ToString())));
            }
            XdmValue* buffer=xp->xsltProcessor->transformToValue();
            //std::cout<<"exceptionOccurred "<<xp->xsltProcessor->exceptionOccurred()<<std::endl;
            if(xp->xsltProcessor->exceptionOccurred() || xp->xsltProcessor->exceptionCount()>0){
                if(xp->xsltProcessor->exceptionCount()==0)xp->xsltProcessor->checkException();
                std::ostringstream ss;
                ss<<"# of exceptions: "<<std::to_string(xp->xsltProcessor->exceptionCount())<<std::endl;
                for(unsigned int exceptionIndex=0;exceptionIndex<xp->xsltProcessor->exceptionCount();exceptionIndex++){
                    ss<<xp->xsltProcessor->getErrorMessage(exceptionIndex)<<std::endl;
                }
                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), ss.str().c_str())));
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
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

    inline XdmAtomicValue* makeParameter(XsltProcessorJS* xp, v8::Local<v8::Value> p){
        if(p->IsBoolean()){
            return xp->xsltProcessor->getSaxonProcessor()->makeBooleanValue(p->BooleanValue());
        }
        else if(p->IsInt32() || p->IsUint32()){
            return xp->xsltProcessor->getSaxonProcessor()->makeIntegerValue(p->IntegerValue());
        }
        else if(p->IsNumber()){
            return xp->xsltProcessor->getSaxonProcessor()->makeDoubleValue(p->NumberValue());
        }
        else{
                String::Utf8Value pnValue(p->ToString());
//                        std::cout<<(*pn)<<" "<<(*pnValue)<<std::endl;
            return xp->xsltProcessor->getSaxonProcessor()->makeStringValue(*pnValue);
        }
    }
    
    private:
        Local<Object> procJS;
        SaxonProcessorJS* proc;
        std::shared_ptr<XsltProcessor> xsltProcessor;
        XdmValue* value;

    };

};
