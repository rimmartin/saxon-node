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
#include <jni.h>

#include "XsltProcessor.h"

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
            NODE_SET_PROTOTYPE_METHOD(t, "setSourceValue", setSourceValue);
            NODE_SET_PROTOTYPE_METHOD(t, "setSourceFile", setSourceFile);
            NODE_SET_PROTOTYPE_METHOD(t, "setOutputfile", setOutputfile);
            NODE_SET_PROTOTYPE_METHOD(t, "setParameter", setParameter);
            NODE_SET_PROTOTYPE_METHOD(t, "getParameter", getParameter);
            NODE_SET_PROTOTYPE_METHOD(t, "removeParameter", removeParameter);
            NODE_SET_PROTOTYPE_METHOD(t, "setProperty", setProperty);
            NODE_SET_PROTOTYPE_METHOD(t, "getProperty", getProperty);
            NODE_SET_PROTOTYPE_METHOD(t, "clearParameters", clearParameters);
            NODE_SET_PROTOTYPE_METHOD(t, "xsltSaveResultToFile", xsltSaveResultToFile);
            NODE_SET_PROTOTYPE_METHOD(t, "xsltApplyStylesheet", xsltApplyStylesheet);
            NODE_SET_PROTOTYPE_METHOD(t, "parseXmlString", parseXmlString);
            NODE_SET_PROTOTYPE_METHOD(t, "compile", compile);
            NODE_SET_PROTOTYPE_METHOD(t, "compileString", compileString);
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

            xp->xsltProcessor.reset(xp->proc->processor->newTransformer());
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

        static void setSourceFile(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
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

        static void xsltSaveResultToFile(const v8::FunctionCallbackInfo<Value>& args) {
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
//                            std::cout<<" "<<parameterNames->IsNull()<<" "<<parameterNames->IsString()<<" "<<parameterNames->IsArray()<<" "<<parameterNames->Length()<<std::endl;
                Local<Object> obj=parameterNames->Get(index)->ToObject();
//                            std::cout<<"obj "<<obj->IsString()<<std::endl;
                String::Utf8Value pn(obj->ToString());
                String::Utf8Value pnValue(parameters->Get(parameterNames->Get(index)->ToString())->ToString());
                std::cout<<(*pn)<<" "<<(*pnValue)<<std::endl;
                xp->xsltProcessor->setParameter(*pn, new XdmValue(*pnValue));
            }
            // the source
            String::Utf8Value sourceFile(args[0]->ToString());
            String::Utf8Value stylesheetfile(args[1]->ToString());
            String::Utf8Value outputfile(args[2]->ToString());
            xp->xsltProcessor->xsltSaveResultToFile((*sourceFile), (*stylesheetfile), (*outputfile));
            args.GetReturnValue().SetUndefined();
        };

        static void xsltApplyStylesheet(const v8::FunctionCallbackInfo<Value>& args) {
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
//                            std::cout<<" "<<parameterNames->IsNull()<<" "<<parameterNames->IsString()<<" "<<parameterNames->IsArray()<<" "<<parameterNames->Length()<<std::endl;
                            Local<Object> obj=parameterNames->Get(index)->ToObject();
//                            std::cout<<"obj "<<obj->IsString()<<std::endl;
                            String::Utf8Value pn(obj->ToString());
                            String::Utf8Value pnValue(parameters->Get(parameterNames->Get(index)->ToString())->ToString());
//                            std::cout<<(*pn)<<" "<<(*pnValue)<<std::endl;
                            xp->xsltProcessor->setParameter(*pn, new XdmValue(*pnValue));
                        }
                        // the source
                        String::Utf8Value source(args[0]->ToString());
                        const char* buffer=xp->xsltProcessor->xsltApplyStylesheet((*source), NULL);
                        args.GetReturnValue().Set(node::Buffer::New(v8::Isolate::GetCurrent(), buffer, std::strlen(buffer)));
                    }
                    break;
                case 2:
                    if(args[0]->IsString() && args[1]->IsString())
                    {
                        // unwrap xsltProcessor object
                        XsltProcessorJS* xp = ObjectWrap::Unwrap<XsltProcessorJS>(args.This());
                        if(args.This()->IsDirty())
                        {
                        for(uint32_t index=0;index<parameterNames->Length();index++)
                        {
//                            std::cout<<" "<<parameterNames->IsNull()<<" "<<parameterNames->IsString()<<" "<<parameterNames->IsArray()<<" "<<parameterNames->Length()<<std::endl;
                            Local<Object> obj=parameterNames->Get(index)->ToObject();
//                            std::cout<<"obj "<<obj->IsString()<<std::endl;
                            String::Utf8Value pn(obj->ToString());
                            String::Utf8Value pnValue(parameters->Get(parameterNames->Get(index)->ToString())->ToString());
//                            std::cout<<(*pn)<<" "<<(*pnValue)<<std::endl;
                            xp->xsltProcessor->setParameter(*pn, new XdmValue(*pnValue));
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
                        const char* buffer=xp->xsltProcessor->xsltApplyStylesheet((*sourceFile), (*stylesheetfile));
                        args.GetReturnValue().Set(node::Buffer::New(v8::Isolate::GetCurrent(), buffer, std::strlen(buffer)));
                    }
                    break;
                default:
                    // unwrap xsltProcessor object
                    XsltProcessorJS* xp = ObjectWrap::Unwrap<XsltProcessorJS>(args.This());
                    for(uint32_t index=0;index<parameterNames->Length();index++)
                    {
//                            std::cout<<" "<<parameterNames->IsNull()<<" "<<parameterNames->IsString()<<" "<<parameterNames->IsArray()<<" "<<parameterNames->Length()<<std::endl;
                        Local<Object> obj=parameterNames->Get(index)->ToObject();
//                            std::cout<<"obj "<<obj->IsString()<<std::endl;
                        String::Utf8Value pn(obj->ToString());
                        String::Utf8Value pnValue(parameters->Get(parameterNames->Get(index)->ToString())->ToString());
//                        std::cout<<(*pn)<<" "<<(*pnValue)<<std::endl;
                        xp->xsltProcessor->setParameter(*pn, new XdmValue(*pnValue));
                    }
                    const char* buffer=xp->xsltProcessor->xsltApplyStylesheet(NULL, NULL);
                    args.GetReturnValue().Set(node::Buffer::New(v8::Isolate::GetCurrent(), buffer, std::strlen(buffer)));
                    break;
            }
//            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "arguments aren't strings")));
//            args.GetReturnValue().SetUndefined();
//            return;
        };

        static void parseXmlFile(const v8::FunctionCallbackInfo<Value>& args) {

        };

        static void parseXmlString(const v8::FunctionCallbackInfo<Value>& args) {
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
            xp->value=xp->xsltProcessor->parseXmlString(*source);
            args.GetReturnValue().SetUndefined();
        };

        static void compile(const v8::FunctionCallbackInfo<Value>& args) {
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
            xp->xsltProcessor->compile(*stylesheet);
            args.GetReturnValue().SetUndefined();

        };

        static void compileString(const v8::FunctionCallbackInfo<Value>& args) {
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
            xp->xsltProcessor->compileString(*stylesheet);
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
        std::shared_ptr<XsltProcessor> xsltProcessor;
        XdmValue* value;

    };

};
