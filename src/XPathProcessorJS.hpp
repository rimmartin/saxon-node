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

#include "XdmItem.h"
#include "XdmValue.h"
#include "XPathProcessor.h"

#include "XdmValueJS.hpp"

namespace saxon_node {

    using namespace v8;

    class SaxonProcessorJS;

    class XPathProcessorJS : public node::ObjectWrap {
    protected:

    public:

        static void Initialize(Handle<Object> target) {
            // instantiate constructor function template
            Local<FunctionTemplate> t = FunctionTemplate::New(v8::Isolate::GetCurrent(), New);
            t->SetClassName(String::NewFromUtf8(v8::Isolate::GetCurrent(), "XPathProcessor"));
            t->InstanceTemplate()->SetInternalFieldCount(1);
            Constructor.Reset(v8::Isolate::GetCurrent(), t);
            // member method prototypes
            NODE_SET_PROTOTYPE_METHOD(t, "setBaseURI", setBaseURI);
            NODE_SET_PROTOTYPE_METHOD(t, "evaluate", evaluate);
            NODE_SET_PROTOTYPE_METHOD(t, "evaluateSingle", evaluateSingle);
            NODE_SET_PROTOTYPE_METHOD(t, "setContextItem", setContextItem);
            NODE_SET_PROTOTYPE_METHOD(t, "setContextFile", setContextFile);
            NODE_SET_PROTOTYPE_METHOD(t, "effectiveBooleanValue", effectiveBooleanValue);
            NODE_SET_PROTOTYPE_METHOD(t, "setParameter", setParameter);
            NODE_SET_PROTOTYPE_METHOD(t, "getParameter", getParameter);
            NODE_SET_PROTOTYPE_METHOD(t, "removeParameter", removeParameter);
            NODE_SET_PROTOTYPE_METHOD(t, "setProperty", setProperty);
            NODE_SET_PROTOTYPE_METHOD(t, "declareNamespace", declareNamespace);
            NODE_SET_PROTOTYPE_METHOD(t, "getProperty", getProperty);
            NODE_SET_PROTOTYPE_METHOD(t, "clearParameters", clearParameters);
            //        Local<Function> f=t->GetFunction();
            // append this function to the target object
            target->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "XPathProcessor"), t->GetFunction());
        };

        static Local<Object> Instantiate(Local<Object> proc) {
            Local<Value> argv[1] = {

                proc

            };

            // return new group instance
            return Local<FunctionTemplate>::New(v8::Isolate::GetCurrent(), Constructor)->GetFunction()->NewInstance(1, argv);

        };
    private:

        XPathProcessorJS() : XPathProcessorJS(false) {

        };

        XPathProcessorJS(bool l) {

        };

        ~XPathProcessorJS() {
        };
        static Persistent<FunctionTemplate> Constructor;

        static void New(const v8::FunctionCallbackInfo<Value>& args) {
            // create hdf file object
            XPathProcessorJS* xp;
            if (args.Length() < 1)
                xp = new XPathProcessorJS();
            else
                xp = new XPathProcessorJS(args[1]->ToBoolean()->BooleanValue());

            xp->procJS = args[0]->ToObject();
            // unwrap processor object
            xp->proc = ObjectWrap::Unwrap<SaxonProcessorJS>(args[0]->ToObject());

            xp->xpathProcessor.reset(xp->proc->processor->newXPathProcessor());
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

        static void setContextItem(const v8::FunctionCallbackInfo<Value>& args) {
            if (args.Length() != 1 || !args[0]->IsString()) {

                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "expected xml source as string")));
                args.GetReturnValue().SetUndefined();
                return;

            }
            // the source
            String::Utf8Value context(args[0]->ToString());
            //std::cout<<(*source)<<std::endl;
            // unwrap xpathProcessor object
            XPathProcessorJS* xp = ObjectWrap::Unwrap<XPathProcessorJS>(args.This());
            xp->xpathProcessor->setContextItem((XdmItem*)xp->proc->processor->makeStringValue(*context));
            args.GetReturnValue().SetUndefined();

        };

        static void setContextFile(const v8::FunctionCallbackInfo<Value>& args) {
            if (args.Length() != 1 || !args[0]->IsString()) {

                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "expected context source as path string")));
                args.GetReturnValue().SetUndefined();
                return;

            }
            // the source
            String::Utf8Value contextFile(args[0]->ToString());
            //std::cout<<(*contextFile)<<std::endl;
            // unwrap xpathProcessor object
            XPathProcessorJS* xp = ObjectWrap::Unwrap<XPathProcessorJS>(args.This());
            xp->xpathProcessor->setContextFile(*contextFile);
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

        static void setBaseURI(const v8::FunctionCallbackInfo<Value>& args) {
            if(args.Length()!=1 || !args[0]->IsString() )
            {
                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "expected base uri as string")));
                args.GetReturnValue().SetUndefined();
            }
            // unwrap xpathProcessor object
            XPathProcessorJS* xp = ObjectWrap::Unwrap<XPathProcessorJS>(args.This());
            // the base uri
            String::Utf8Value baseUri(args[0]->ToString());
            xp->xpathProcessor->setBaseURI((*baseUri));
            if(xp->xpathProcessor->exceptionOccurred() || xp->xpathProcessor->exceptionCount()>0){
                if(xp->xpathProcessor->exceptionCount()==0)xp->xpathProcessor->checkException();
                std::ostringstream ss;
                ss<<"# of exceptions: "<<std::to_string(xp->xpathProcessor->exceptionCount())<<std::endl;
                for(unsigned int exceptionIndex=0;exceptionIndex<xp->xpathProcessor->exceptionCount();exceptionIndex++){
                    ss<<xp->xpathProcessor->getErrorMessage(exceptionIndex)<<std::endl;
                }
                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), ss.str().c_str())));
                args.GetReturnValue().SetUndefined();
                return;
                
            }
            args.GetReturnValue().SetUndefined();
        };

        static void evaluate(const v8::FunctionCallbackInfo<Value>& args) {
            if(args.Length()!=1 || !args[0]->IsString())
            {
                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "expected xpath string")));
                args.GetReturnValue().SetUndefined();
            }
            // unwrap xpathProcessor object
            XPathProcessorJS* xp = ObjectWrap::Unwrap<XPathProcessorJS>(args.This());
            /*Local<Object> parameters=args.This()->Get(String::NewFromUtf8(v8::Isolate::GetCurrent(), "parameters"))->ToObject();
            Local<Array> parameterNames=parameters->GetOwnPropertyNames();
            for(uint32_t index=0;index<parameterNames->Length();index++)
            {
//                            std::cout<<" "<<parameterNames->IsNull()<<" "<<parameterNames->IsString()<<" "<<parameterNames->IsArray()<<" "<<parameterNames->Length()<<std::endl;
                Local<Object> obj=parameterNames->Get(index)->ToObject();
//                            std::cout<<"obj "<<obj->IsString()<<std::endl;
                String::Utf8Value pn(obj->ToString());
                String::Utf8Value pnValue(parameters->Get(parameterNames->Get(index)->ToString())->ToString());
                //std::cout<<(*pn)<<" "<<(*pnValue)<<std::endl;
                //@todo xp->xpathProcessor->setParameter(*pn, new XdmValue(*pnValue));
            }*/
            // the source
            String::Utf8Value xpath(args[0]->ToString());
            //std::cout<<(*xpath)<<std::endl;
            XdmValue * results=xp->xpathProcessor->evaluate((*xpath));
            if(xp->xpathProcessor->exceptionOccurred() || xp->xpathProcessor->exceptionCount()>0){
                if(xp->xpathProcessor->exceptionCount()==0)xp->xpathProcessor->checkException();
                std::ostringstream ss;
                ss<<"# of exceptions: "<<std::to_string(xp->xpathProcessor->exceptionCount())<<std::endl;
                for(unsigned int exceptionIndex=0;exceptionIndex<xp->xpathProcessor->exceptionCount();exceptionIndex++){
                    ss<<xp->xpathProcessor->getErrorMessage(exceptionIndex)<<std::endl;
                }
                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), ss.str().c_str())));
                args.GetReturnValue().SetUndefined();
                return;
                
            }
            
            Local<Object> instance=XdmValueJS::Instantiate(args.This());
            XdmValueJS* xdmValue = new XdmValueJS();
            xdmValue->value=results;
            xdmValue->Wrap(instance);
            args.GetReturnValue().Set(instance);
        };

        static void evaluateSingle(const v8::FunctionCallbackInfo<Value>& args) {
            Local<Object> parameters=args.This()->Get(String::NewFromUtf8(v8::Isolate::GetCurrent(), "parameters"))->ToObject();
            Local<Array> parameterNames=parameters->GetOwnPropertyNames();
            Local<Object> properties=args.This()->Get(String::NewFromUtf8(v8::Isolate::GetCurrent(), "properties"))->ToObject();
            Local<Array> propertyNames=properties->GetOwnPropertyNames();
            switch(args.Length())
            {
                case 1:
                    if(args[0]->IsString())
                    {
                        // unwrap xpathProcessor object
                        XPathProcessorJS* xp = ObjectWrap::Unwrap<XPathProcessorJS>(args.This());
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
                                //@todo xp->xpathProcessor->setParameter(*pn, new XdmValue(*pnValue));
                            }
                        }
                        // the source
                        String::Utf8Value source(args[0]->ToString());
                        XdmItem* buffer=xp->xpathProcessor->evaluateSingle((*source));
                        if(xp->xpathProcessor->exceptionOccurred() || xp->xpathProcessor->exceptionCount()>0){
                            if(xp->xpathProcessor->exceptionCount()==0)xp->xpathProcessor->checkException();
                            std::ostringstream ss;
                            ss<<"# of exceptions: "<<std::to_string(xp->xpathProcessor->exceptionCount())<<std::endl;
                            for(unsigned int exceptionIndex=0;exceptionIndex<xp->xpathProcessor->exceptionCount();exceptionIndex++){
                                ss<<xp->xpathProcessor->getErrorMessage(exceptionIndex)<<std::endl;
                            }
                            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), ss.str().c_str())));
                            args.GetReturnValue().SetUndefined();
                            break;
                            
                        }
                        args.GetReturnValue().Set(node::Buffer::New(v8::Isolate::GetCurrent(), (char*)buffer->getStringValue(), std::strlen((char*)buffer->getStringValue())).ToLocalChecked());
                    }
                    break;
            }
//            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "arguments aren't strings")));
//            args.GetReturnValue().SetUndefined();
//            return;
        };

        static void effectiveBooleanValue(const v8::FunctionCallbackInfo<Value>& args) {
            if(args.Length()!=1 || !args[0]->IsString() )
            {
                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "expected base uri as string")));
                args.GetReturnValue().SetUndefined();
            }
            // unwrap xpathProcessor object
            XPathProcessorJS* xp = ObjectWrap::Unwrap<XPathProcessorJS>(args.This());
            // the base uri
            String::Utf8Value xPathStr(args[0]->ToString());
            bool effective=xp->xpathProcessor->effectiveBooleanValue((*xPathStr));
            if(xp->xpathProcessor->exceptionOccurred() || xp->xpathProcessor->exceptionCount()>0){
                if(xp->xpathProcessor->exceptionCount()==0)xp->xpathProcessor->checkException();
                std::ostringstream ss;
                ss<<"# of exceptions: "<<std::to_string(xp->xpathProcessor->exceptionCount())<<std::endl;
                for(unsigned int exceptionIndex=0;exceptionIndex<xp->xpathProcessor->exceptionCount();exceptionIndex++){
                    ss<<xp->xpathProcessor->getErrorMessage(exceptionIndex)<<std::endl;
                }
                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), ss.str().c_str())));
                args.GetReturnValue().SetUndefined();
                return;
                
            }
            args.GetReturnValue().Set(effective);
        };

        static void declareNamespace(const v8::FunctionCallbackInfo<Value>& args) {
            if(args.Length()!=2 || !args[0]->IsString()|| !args[1]->IsString())
            {
                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "expected prefix and uri strings")));
                args.GetReturnValue().SetUndefined();
            }
            // unwrap xpathProcessor object
            XPathProcessorJS* xp = ObjectWrap::Unwrap<XPathProcessorJS>(args.This());
            /*Local<Object> parameters=args.This()->Get(String::NewFromUtf8(v8::Isolate::GetCurrent(), "parameters"))->ToObject();
            Local<Array> parameterNames=parameters->GetOwnPropertyNames();
            for(uint32_t index=0;index<parameterNames->Length();index++)
            {
//                            std::cout<<" "<<parameterNames->IsNull()<<" "<<parameterNames->IsString()<<" "<<parameterNames->IsArray()<<" "<<parameterNames->Length()<<std::endl;
                Local<Object> obj=parameterNames->Get(index)->ToObject();
//                            std::cout<<"obj "<<obj->IsString()<<std::endl;
                String::Utf8Value pn(obj->ToString());
                String::Utf8Value pnValue(parameters->Get(parameterNames->Get(index)->ToString())->ToString());
                //std::cout<<(*pn)<<" "<<(*pnValue)<<std::endl;
                //@todo xp->xpathProcessor->setParameter(*pn, new XdmValue(*pnValue));
            }*/
            // the source
            String::Utf8Value prefix(args[0]->ToString());
            String::Utf8Value uri(args[0]->ToString());
            xp->xpathProcessor->declareNamespace((*prefix), (*uri));
            if(xp->xpathProcessor->exceptionOccurred() || xp->xpathProcessor->exceptionCount()>0){
                if(xp->xpathProcessor->exceptionCount()==0)xp->xpathProcessor->checkException();
                std::ostringstream ss;
                ss<<"# of exceptions: "<<std::to_string(xp->xpathProcessor->exceptionCount())<<std::endl;
                for(unsigned int exceptionIndex=0;exceptionIndex<xp->xpathProcessor->exceptionCount();exceptionIndex++){
                    ss<<xp->xpathProcessor->getErrorMessage(exceptionIndex)<<std::endl;
                }
                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), ss.str().c_str())));
                args.GetReturnValue().SetUndefined();
                return;
                
            }
            
            args.GetReturnValue().SetUndefined();
        };

        static void exceptionOccurred(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

    private:
        Local<Object> procJS;
        SaxonProcessorJS* proc;
        std::shared_ptr<XPathProcessor> xpathProcessor;
        XdmValue* value;

    };

};
