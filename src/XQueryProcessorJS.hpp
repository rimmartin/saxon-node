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

        static void Initialize(v8::Local<v8::Object> target) {
            v8::Isolate* isolate = v8::Isolate::GetCurrent();
            v8::Local<v8::Context> context = isolate->GetCurrentContext();
            // instantiate constructor function template
            Local<FunctionTemplate> t = FunctionTemplate::New(v8::Isolate::GetCurrent(), New);
            t->SetClassName(String::NewFromUtf8(v8::Isolate::GetCurrent(), "XQueryProcessor", v8::NewStringType::kInternalized).ToLocalChecked());
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
            // append this function to the target object
            target->Set(context, String::NewFromUtf8(v8::Isolate::GetCurrent(), "XQueryProcessor", v8::NewStringType::kInternalized).ToLocalChecked(), t->GetFunction(context).ToLocalChecked());
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

        XQueryProcessorJS() : XQueryProcessorJS(false) {

        };

        XQueryProcessorJS(bool l) {

        };

        ~XQueryProcessorJS() {
        };
        static Persistent<FunctionTemplate> Constructor;

        static void New(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate* isolate = v8::Isolate::GetCurrent();
            v8::Local<v8::Context> context = isolate->GetCurrentContext();
            // create hdf file object
            XQueryProcessorJS* xp;
            if (args.Length() < 1)
                xp = new XQueryProcessorJS();
            else
                xp = new XQueryProcessorJS(args[1]->ToBoolean(isolate)->Value());

            xp->procJS = args[0]->ToObject(context).ToLocalChecked();
            // unwrap processor object
            xp->proc = ObjectWrap::Unwrap<SaxonProcessorJS>(args[0]->ToObject(context).ToLocalChecked());

            xp->xqueryProcessor.reset(xp->proc->processor->newXQueryProcessor());
            // extend target object with processor
            xp->Wrap(args.This());

            // attach various properties
            args.This()->Set(context, String::NewFromUtf8(v8::Isolate::GetCurrent(), "parameters", v8::NewStringType::kInternalized).ToLocalChecked(), Object::New(v8::Isolate::GetCurrent()));
            args.This()->Set(context, String::NewFromUtf8(v8::Isolate::GetCurrent(), "properties", v8::NewStringType::kInternalized).ToLocalChecked(), Object::New(v8::Isolate::GetCurrent()));
        };

        static void setSourceValue(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::Error(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method", v8::NewStringType::kInternalized).ToLocalChecked()));
            args.GetReturnValue().SetUndefined();
        };

        static void setContextItemFromFile(const v8::FunctionCallbackInfo<Value>& args) {
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
            // unwrap xqueryProcessor object
            XQueryProcessorJS* xp = ObjectWrap::Unwrap<XQueryProcessorJS>(args.This());
            xp->xqueryProcessor->setContextItemFromFile(*source);
            args.GetReturnValue().SetUndefined();

        };

        static void setOutputfile(const v8::FunctionCallbackInfo<Value>& args) {
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

        static void executeQueryToFile(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate* isolate = v8::Isolate::GetCurrent();
            v8::Local<v8::Context> context = isolate->GetCurrentContext();
            if(args.Length()!=3 || !args[0]->IsString() || !args[1]->IsString() || !args[2]->IsString())
            {
                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::Error(String::NewFromUtf8(v8::Isolate::GetCurrent(), "not correct arguments", v8::NewStringType::kInternalized).ToLocalChecked()));
                args.GetReturnValue().SetUndefined();
            }
            // unwrap xqueryProcessor object
            XQueryProcessorJS* xp = ObjectWrap::Unwrap<XQueryProcessorJS>(args.This());
            Local<Object> parameters=args.This()->Get(context, String::NewFromUtf8(v8::Isolate::GetCurrent(), "parameters", v8::NewStringType::kInternalized).ToLocalChecked()).ToLocalChecked()->ToObject(context).ToLocalChecked();
            Local<Array> parameterNames=parameters->GetOwnPropertyNames(context).ToLocalChecked();
            for(uint32_t index=0;index<parameterNames->Length();index++)
            {
//                            std::cout<<" "<<parameterNames->IsNull()<<" "<<parameterNames->IsString()<<" "<<parameterNames->IsArray()<<" "<<parameterNames->Length()<<std::endl;
                Local<Object> obj=parameterNames->Get(context, index).ToLocalChecked()->ToObject(context).ToLocalChecked();
//                            std::cout<<"obj "<<obj->IsString()<<std::endl;
                String::Utf8Value pn(isolate, obj->ToString(context).ToLocalChecked());
                String::Utf8Value pnValue(isolate, parameters->Get(context, parameterNames->Get(context, index).ToLocalChecked()->ToString(context).ToLocalChecked()).ToLocalChecked()->ToString(context).ToLocalChecked());
                //std::cout<<(*pn)<<" "<<(*pnValue)<<std::endl;
                //@todo xp->xqueryProcessor->setParameter(*pn, new XdmValue(*pnValue));
            }
            // the source
            String::Utf8Value sourceFile(isolate, args[0]->ToString(context).ToLocalChecked());
            String::Utf8Value query(isolate, args[1]->ToString(context).ToLocalChecked());
            String::Utf8Value outputfile(isolate, args[2]->ToString(context).ToLocalChecked());
            xp->xqueryProcessor->executeQueryToFile((*sourceFile), (*outputfile), (*query));
            if(xp->xqueryProcessor->exceptionOccurred() || xp->xqueryProcessor->exceptionCount()>0){
                if(xp->xqueryProcessor->exceptionCount()==0)xp->xqueryProcessor->checkException();
                std::ostringstream ss;
                ss<<"# of exceptions: "<<std::to_string(xp->xqueryProcessor->exceptionCount())<<std::endl;
                for(unsigned int exceptionIndex=0;exceptionIndex<xp->xqueryProcessor->exceptionCount();exceptionIndex++){
                    ss<<xp->xqueryProcessor->getErrorMessage(exceptionIndex)<<std::endl;
                }
                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::Error(String::NewFromUtf8(v8::Isolate::GetCurrent(), ss.str().c_str(), v8::NewStringType::kInternalized).ToLocalChecked()));
                args.GetReturnValue().SetUndefined();
                return;
                
            }
            args.GetReturnValue().SetUndefined();
        };

        static void executeQueryToString(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate* isolate = v8::Isolate::GetCurrent();
            v8::Local<v8::Context> context = isolate->GetCurrentContext();
            Local<Object> parameters=args.This()->Get(context, String::NewFromUtf8(v8::Isolate::GetCurrent(), "parameters", v8::NewStringType::kInternalized).ToLocalChecked()).ToLocalChecked()->ToObject(context).ToLocalChecked();
            Local<Array> parameterNames=parameters->GetOwnPropertyNames(context).ToLocalChecked();
            Local<Object> properties=args.This()->Get(context, String::NewFromUtf8(v8::Isolate::GetCurrent(), "properties", v8::NewStringType::kInternalized).ToLocalChecked()).ToLocalChecked()->ToObject(context).ToLocalChecked();
            Local<Array> propertyNames=properties->GetOwnPropertyNames(context).ToLocalChecked();
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
                                Local<Object> obj=parameterNames->Get(context, index).ToLocalChecked()->ToObject(context).ToLocalChecked();
    //                            std::cout<<"obj "<<obj->IsString()<<std::endl;
                                String::Utf8Value pn(isolate, obj->ToString(context).ToLocalChecked());
                                String::Utf8Value pnValue(isolate, parameters->Get(context, parameterNames->Get(context, index).ToLocalChecked()->ToString(context).ToLocalChecked()).ToLocalChecked()->ToString(context).ToLocalChecked());
                                //std::cout<<(*pn)<<" "<<(*pnValue)<<std::endl;
                                //@todo xp->xqueryProcessor->setParameter(*pn, new XdmValue(*pnValue));
                            }
                        }
                        // the source
                        String::Utf8Value source(isolate, args[0]->ToString(context).ToLocalChecked());
                        const char* buffer=xp->xqueryProcessor->executeQueryToString((*source), NULL);
                        if(xp->xqueryProcessor->exceptionOccurred() || xp->xqueryProcessor->exceptionCount()>0){
                            if(xp->xqueryProcessor->exceptionCount()==0)xp->xqueryProcessor->checkException();
                            std::ostringstream ss;
                            ss<<"# of exceptions: "<<std::to_string(xp->xqueryProcessor->exceptionCount())<<std::endl;
                            for(unsigned int exceptionIndex=0;exceptionIndex<xp->xqueryProcessor->exceptionCount();exceptionIndex++){
                                ss<<xp->xqueryProcessor->getErrorMessage(exceptionIndex)<<std::endl;
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
                        // unwrap xqueryProcessor object
                        XQueryProcessorJS* xp = ObjectWrap::Unwrap<XQueryProcessorJS>(args.This());
                        for(uint32_t index=0;index<parameterNames->Length();index++)
                        {
//                            std::cout<<" "<<parameterNames->IsNull()<<" "<<parameterNames->IsString()<<" "<<parameterNames->IsArray()<<" "<<parameterNames->Length()<<std::endl;
                            Local<Object> obj=parameterNames->Get(context, index).ToLocalChecked()->ToObject(context).ToLocalChecked();
//                            std::cout<<"obj "<<obj->IsString()<<std::endl;
                            String::Utf8Value pn(isolate, obj->ToString(context).ToLocalChecked());
                            String::Utf8Value pnValue(isolate, parameters->Get(context, parameterNames->Get(context, index).ToLocalChecked()->ToString(context).ToLocalChecked()).ToLocalChecked()->ToString(context).ToLocalChecked());
                            //std::cout<<(*pn)<<" "<<(*pnValue)<<std::endl;
                            //@todo xp->xqueryProcessor->setParameter(*pn, new XdmValue(*pnValue));
                        }
                        for(uint32_t index=0;index<propertyNames->Length();index++)
                        {
                            Local<Object> obj=propertyNames->Get(context, index).ToLocalChecked()->ToObject(context).ToLocalChecked();
                            String::Utf8Value pn(isolate, obj->ToString(context).ToLocalChecked());
                            String::Utf8Value pnValue(isolate, properties->Get(context, propertyNames->Get(context, index).ToLocalChecked()->ToString(context).ToLocalChecked()).ToLocalChecked()->ToString(context).ToLocalChecked());
                            //std::cout<<(*pn)<<" "<<(*pnValue)<<std::endl;
                            xp->xqueryProcessor->setProperty(*pn, *pnValue);
                        }
                        // the source
                        String::Utf8Value sourceFile(isolate, args[0]->ToString(context).ToLocalChecked());
                        String::Utf8Value query(isolate, args[1]->ToString(context).ToLocalChecked());
                        const char* buffer=xp->xqueryProcessor->executeQueryToString((*sourceFile), (*query));
                        if(xp->xqueryProcessor->exceptionOccurred() || xp->xqueryProcessor->exceptionCount()>0){
                            if(xp->xqueryProcessor->exceptionCount()==0)xp->xqueryProcessor->checkException();
                            std::ostringstream ss;
                            ss<<"# of exceptions: "<<std::to_string(xp->xqueryProcessor->exceptionCount())<<std::endl;
                            for(unsigned int exceptionIndex=0;exceptionIndex<xp->xqueryProcessor->exceptionCount();exceptionIndex++){
                                ss<<xp->xqueryProcessor->getErrorMessage(exceptionIndex)<<std::endl;
                            }
                            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::Error(String::NewFromUtf8(v8::Isolate::GetCurrent(), ss.str().c_str(), v8::NewStringType::kInternalized).ToLocalChecked()));
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
                        Local<Object> obj=parameterNames->Get(context, index).ToLocalChecked()->ToObject(context).ToLocalChecked();
//                            std::cout<<"obj "<<obj->IsString()<<std::endl;
                        String::Utf8Value pn(isolate, obj->ToString(context).ToLocalChecked());
                        String::Utf8Value pnValue(isolate, parameters->Get(context, parameterNames->Get(context, index).ToLocalChecked()->ToString(context).ToLocalChecked()).ToLocalChecked()->ToString(context).ToLocalChecked());
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
                        v8::Isolate::GetCurrent()->ThrowException(v8::Exception::Error(String::NewFromUtf8(v8::Isolate::GetCurrent(), ss.str().c_str(), v8::NewStringType::kInternalized).ToLocalChecked()));
                        args.GetReturnValue().SetUndefined();
                        break;
                        
                    }
                    args.GetReturnValue().Set(node::Buffer::New(v8::Isolate::GetCurrent(), (char*)buffer, std::strlen(buffer)).ToLocalChecked());
                    break;
            }
//            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::Error(String::NewFromUtf8(v8::Isolate::GetCurrent(), "arguments aren't strings", v8::NewStringType::kInternalized).ToLocalChecked()));
//            args.GetReturnValue().SetUndefined();
//            return;
        };

        static void compileString(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::Error(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method", v8::NewStringType::kInternalized).ToLocalChecked()));
            args.GetReturnValue().SetUndefined();
        };

        static void transformToString(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::Error(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method", v8::NewStringType::kInternalized).ToLocalChecked()));
            args.GetReturnValue().SetUndefined();
        };

        static void transformToValue(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::Error(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method", v8::NewStringType::kInternalized).ToLocalChecked()));
            args.GetReturnValue().SetUndefined();
        };

        static void exceptionOccurred(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::Error(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method", v8::NewStringType::kInternalized).ToLocalChecked()));
            args.GetReturnValue().SetUndefined();
        };

    private:
        Local<Object> procJS;
        SaxonProcessorJS* proc;
        std::shared_ptr<XQueryProcessor> xqueryProcessor;
        XdmValue* value;

    };

};
