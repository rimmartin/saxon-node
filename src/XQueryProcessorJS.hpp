#pragma once
#include <map>

#include <v8.h>
#include <uv.h>
#include <node.h>
#include <node_object_wrap.h>
#include <string>
#include <cstring>
#include <memory>
#include <jni.h>

#include "XQueryProcessor.h"

namespace saxon_node {

    using namespace v8;

    class SaxonProcessorJS;

    class XQueryProcessorJS : public node::ObjectWrap {
    protected:

    public:

        static void Initialize(Handle<Object> target) {
            // instantiate constructor function template
            Local<FunctionTemplate> t = FunctionTemplate::New(v8::Isolate::GetCurrent(), New);
            t->SetClassName(String::NewFromUtf8(v8::Isolate::GetCurrent(), "XQueryProcessor"));
            t->InstanceTemplate()->SetInternalFieldCount(1);
            Constructor.Reset(v8::Isolate::GetCurrent(), t);
            // member method prototypes
            NODE_SET_PROTOTYPE_METHOD(t, "setSourceValue", setSourceValue);
            NODE_SET_PROTOTYPE_METHOD(t, "setContextItemFromFile", setContextItemFromFile);
            NODE_SET_PROTOTYPE_METHOD(t, "setOutputfile", setOutputfile);
            NODE_SET_PROTOTYPE_METHOD(t, "setProperty", setProperty);
            NODE_SET_PROTOTYPE_METHOD(t, "getProperty", getProperty);
            NODE_SET_PROTOTYPE_METHOD(t, "clearParameters", clearParameters);
            NODE_SET_PROTOTYPE_METHOD(t, "executeQueryToFile", executeQueryToFile);
            NODE_SET_PROTOTYPE_METHOD(t, "executeQueryToString", executeQueryToString);
            //        Local<Function> f=t->GetFunction();
            // append this function to the target object
            target->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "XQueryProcessor"), t->GetFunction());
        };

        static Local<Object> Instantiate(Local<Object> proc) {
            Local<Value> argv[1] = {

                proc

            };

            // return new group instance
            return Local<FunctionTemplate>::New(v8::Isolate::GetCurrent(), Constructor)->GetFunction()->NewInstance(1, argv);

        };
    private:

        XQueryProcessorJS() : XQueryProcessorJS(false) {

        };

        XQueryProcessorJS(bool l) {

        };

        ~XQueryProcessorJS() {
        };
        static Persistent<FunctionTemplate> Constructor;

        static void New(const v8::FunctionCallbackInfo<Value>& args) {
            // create hdf file object
            XQueryProcessorJS* xp;
            if (args.Length() < 1)
                xp = new XQueryProcessorJS();
            else
                xp = new XQueryProcessorJS(args[1]->ToBoolean()->BooleanValue());

            xp->procJS = args[0]->ToObject();
            // unwrap processor object
            xp->proc = ObjectWrap::Unwrap<SaxonProcessorJS>(args[0]->ToObject());

            xp->xqueryProcessor.reset(xp->proc->processor->newXQueryProcessor());
            // extend target object with processor
            xp->Wrap(args.This());

            // attach various properties
            args.This()->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "parameters"), Object::New(v8::Isolate::GetCurrent()));
            args.This()->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "properties"), Object::New(v8::Isolate::GetCurrent()));
        };

        static void setSourceValue(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

        static void setContextItemFromFile(const v8::FunctionCallbackInfo<Value>& args) {
            if (args.Length() != 1 || !args[0]->IsString()) {

                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "expected xml source as string")));
                args.GetReturnValue().SetUndefined();
                return;

            }
            // the source
            String::Utf8Value source(args[0]->ToString());
            //std::cout<<(*source)<<std::endl;
            // unwrap xqueryProcessor object
            XQueryProcessorJS* xp = ObjectWrap::Unwrap<XQueryProcessorJS>(args.This());
            xp->xqueryProcessor->setContextItemFromFile(*source);
            args.GetReturnValue().SetUndefined();

        };

        static void setOutputfile(const v8::FunctionCallbackInfo<Value>& args) {
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

        static void executeQueryToFile(const v8::FunctionCallbackInfo<Value>& args) {
            if(args.Length()!=3 || !args[0]->IsString() || !args[1]->IsString() || !args[2]->IsString())
            {
                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "not correct arguments")));
                args.GetReturnValue().SetUndefined();
            }
            // unwrap xqueryProcessor object
            XQueryProcessorJS* xp = ObjectWrap::Unwrap<XQueryProcessorJS>(args.This());
            Local<Object> parameters=args.This()->Get(String::NewFromUtf8(v8::Isolate::GetCurrent(), "parameters"))->ToObject();
            Local<Array> parameterNames=parameters->GetOwnPropertyNames();
            for(uint32_t index=0;index<parameterNames->Length();index++)
            {
//                            std::cout<<" "<<parameterNames->IsNull()<<" "<<parameterNames->IsString()<<" "<<parameterNames->IsArray()<<" "<<parameterNames->Length()<<std::endl;
                Local<Object> obj=parameterNames->Get(index)->ToObject();
//                            std::cout<<"obj "<<obj->IsString()<<std::endl;
                String::Utf8Value pn(obj->ToString());
                String::Utf8Value pnValue(parameters->Get(parameterNames->Get(index)->ToString())->ToString());
                //std::cout<<(*pn)<<" "<<(*pnValue)<<std::endl;
                //@todo xp->xqueryProcessor->setParameter(*pn, new XdmValue(*pnValue));
            }
            // the source
            String::Utf8Value sourceFile(args[0]->ToString());
            String::Utf8Value query(args[1]->ToString());
            String::Utf8Value outputfile(args[2]->ToString());
            xp->xqueryProcessor->executeQueryToFile((*sourceFile), (*outputfile), (*query));
            if(xp->xqueryProcessor->exceptionOccurred() || xp->xqueryProcessor->exceptionCount()>0){
                if(xp->xqueryProcessor->exceptionCount()==0)xp->xqueryProcessor->checkException();
                std::ostringstream ss;
                ss<<"# of exceptions: "<<std::to_string(xp->xqueryProcessor->exceptionCount())<<std::endl;
                for(unsigned int exceptionIndex=0;exceptionIndex<xp->xqueryProcessor->exceptionCount();exceptionIndex++){
                    ss<<xp->xqueryProcessor->getErrorMessage(exceptionIndex)<<std::endl;
                }
                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), ss.str().c_str())));
                args.GetReturnValue().SetUndefined();
                return;
                
            }
            args.GetReturnValue().SetUndefined();
        };

        static void executeQueryToString(const v8::FunctionCallbackInfo<Value>& args) {
            Local<Object> parameters=args.This()->Get(String::NewFromUtf8(v8::Isolate::GetCurrent(), "parameters"))->ToObject();
            Local<Array> parameterNames=parameters->GetOwnPropertyNames();
            Local<Object> properties=args.This()->Get(String::NewFromUtf8(v8::Isolate::GetCurrent(), "properties"))->ToObject();
            Local<Array> propertyNames=properties->GetOwnPropertyNames();
            switch(args.Length())
            {
                case 1:
                    if(args[0]->IsString())
                    {
                        // unwrap xqueryProcessor object
                        XQueryProcessorJS* xp = ObjectWrap::Unwrap<XQueryProcessorJS>(args.This());
                        //if(args.This()->IsDirty())
                        {
                            for(uint32_t index=0;index<parameterNames->Length();index++)
                            {
    //                            std::cout<<" "<<parameterNames->IsNull()<<" "<<parameterNames->IsString()<<" "<<parameterNames->IsArray()<<" "<<parameterNames->Length()<<std::endl;
                                Local<Object> obj=parameterNames->Get(index)->ToObject();
    //                            std::cout<<"obj "<<obj->IsString()<<std::endl;
                                String::Utf8Value pn(obj->ToString());
                                String::Utf8Value pnValue(parameters->Get(parameterNames->Get(index)->ToString())->ToString());
                                //std::cout<<(*pn)<<" "<<(*pnValue)<<std::endl;
                                //@todo xp->xqueryProcessor->setParameter(*pn, new XdmValue(*pnValue));
                            }
                        }
                        // the source
                        String::Utf8Value source(args[0]->ToString());
                        const char* buffer=xp->xqueryProcessor->executeQueryToString((*source), NULL);
                        if(xp->xqueryProcessor->exceptionOccurred() || xp->xqueryProcessor->exceptionCount()>0){
                            if(xp->xqueryProcessor->exceptionCount()==0)xp->xqueryProcessor->checkException();
                            std::ostringstream ss;
                            ss<<"# of exceptions: "<<std::to_string(xp->xqueryProcessor->exceptionCount())<<std::endl;
                            for(unsigned int exceptionIndex=0;exceptionIndex<xp->xqueryProcessor->exceptionCount();exceptionIndex++){
                                ss<<xp->xqueryProcessor->getErrorMessage(exceptionIndex)<<std::endl;
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
                        // unwrap xqueryProcessor object
                        XQueryProcessorJS* xp = ObjectWrap::Unwrap<XQueryProcessorJS>(args.This());
                        for(uint32_t index=0;index<parameterNames->Length();index++)
                        {
//                            std::cout<<" "<<parameterNames->IsNull()<<" "<<parameterNames->IsString()<<" "<<parameterNames->IsArray()<<" "<<parameterNames->Length()<<std::endl;
                            Local<Object> obj=parameterNames->Get(index)->ToObject();
//                            std::cout<<"obj "<<obj->IsString()<<std::endl;
                            String::Utf8Value pn(obj->ToString());
                            String::Utf8Value pnValue(parameters->Get(parameterNames->Get(index)->ToString())->ToString());
                            //std::cout<<(*pn)<<" "<<(*pnValue)<<std::endl;
                            //@todo xp->xqueryProcessor->setParameter(*pn, new XdmValue(*pnValue));
                        }
                        for(uint32_t index=0;index<propertyNames->Length();index++)
                        {
                            Local<Object> obj=propertyNames->Get(index)->ToObject();
                            String::Utf8Value pn(obj->ToString());
                            String::Utf8Value pnValue(properties->Get(propertyNames->Get(index)->ToString())->ToString());
                            //std::cout<<(*pn)<<" "<<(*pnValue)<<std::endl;
                            xp->xqueryProcessor->setProperty(*pn, *pnValue);
                        }
                        // the source
                        String::Utf8Value sourceFile(args[0]->ToString());
                        String::Utf8Value query(args[1]->ToString());
                        const char* buffer=xp->xqueryProcessor->executeQueryToString((*sourceFile), (*query));
                        if(xp->xqueryProcessor->exceptionOccurred() || xp->xqueryProcessor->exceptionCount()>0){
                            if(xp->xqueryProcessor->exceptionCount()==0)xp->xqueryProcessor->checkException();
                            std::ostringstream ss;
                            ss<<"# of exceptions: "<<std::to_string(xp->xqueryProcessor->exceptionCount())<<std::endl;
                            for(unsigned int exceptionIndex=0;exceptionIndex<xp->xqueryProcessor->exceptionCount();exceptionIndex++){
                                ss<<xp->xqueryProcessor->getErrorMessage(exceptionIndex)<<std::endl;
                            }
                            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), ss.str().c_str())));
                            args.GetReturnValue().SetUndefined();
                            break;
                            
                        }
                        args.GetReturnValue().Set(node::Buffer::New(v8::Isolate::GetCurrent(), (char*)buffer, std::strlen(buffer)).ToLocalChecked());
                    }
                    break;
                default:
                    // unwrap xqueryProcessor object
                    XQueryProcessorJS* xp = ObjectWrap::Unwrap<XQueryProcessorJS>(args.This());
                    for(uint32_t index=0;index<parameterNames->Length();index++)
                    {
//                            std::cout<<" "<<parameterNames->IsNull()<<" "<<parameterNames->IsString()<<" "<<parameterNames->IsArray()<<" "<<parameterNames->Length()<<std::endl;
                        Local<Object> obj=parameterNames->Get(index)->ToObject();
//                            std::cout<<"obj "<<obj->IsString()<<std::endl;
                        String::Utf8Value pn(obj->ToString());
                        String::Utf8Value pnValue(parameters->Get(parameterNames->Get(index)->ToString())->ToString());
                        //std::cout<<(*pn)<<" "<<(*pnValue)<<std::endl;
                        //@todo xp->xqueryProcessor->setParameter(*pn, new XdmValue(*pnValue));
                    }
                    const char* buffer=xp->xqueryProcessor->executeQueryToString(NULL, NULL);
                    if(xp->xqueryProcessor->exceptionOccurred() || xp->xqueryProcessor->exceptionCount()>0){
                        if(xp->xqueryProcessor->exceptionCount()==0)xp->xqueryProcessor->checkException();
                        std::ostringstream ss;
                        ss<<"# of exceptions: "<<std::to_string(xp->xqueryProcessor->exceptionCount())<<std::endl;
                        for(unsigned int exceptionIndex=0;exceptionIndex<xp->xqueryProcessor->exceptionCount();exceptionIndex++){
                            ss<<xp->xqueryProcessor->getErrorMessage(exceptionIndex)<<std::endl;
                        }
                        v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), ss.str().c_str())));
                        args.GetReturnValue().SetUndefined();
                        break;
                        
                    }
                    args.GetReturnValue().Set(node::Buffer::New(v8::Isolate::GetCurrent(), (char*)buffer, std::strlen(buffer)).ToLocalChecked());
                    break;
            }
//            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "arguments aren't strings")));
//            args.GetReturnValue().SetUndefined();
//            return;
        };

        static void compileString(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

        static void transformToString(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

        static void transformToValue(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

        static void exceptionOccurred(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

    private:
        Local<Object> procJS;
        SaxonProcessorJS* proc;
        std::shared_ptr<XQueryProcessor> xqueryProcessor;
        XdmValue* value;

    };

};
