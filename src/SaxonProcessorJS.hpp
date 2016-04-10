#pragma once
#include <map>

#include <v8.h>
#include <uv.h>
#include <node.h>
#include <node_object_wrap.h>
#include <string>
#include <cstring>
#include <memory>

#include "SaxonProcessor.h"

#include "XdmNodeJS.hpp"
#include "XdmAtomicValueJS.hpp"

namespace saxon_node {

    using namespace v8;
    //using namespace node;

    class XsltProcessorJS;
    class XQueryProcessorJS;
    class XPathProcessorJS;
    class SchemaValidatorJS;

    class SaxonProcessorJS : public node::ObjectWrap {
        friend class XsltProcessorJS;
        friend class XQueryProcessorJS;
        friend class XPathProcessorJS;
        friend class SchemaValidatorJS;
    protected:
        std::string cwd;
        std::shared_ptr<SaxonProcessor> processor;
    public:

        static void Initialize(v8::Handle<v8::Object> target) {
            // instantiate constructor function template
            v8::Local<v8::FunctionTemplate> t = FunctionTemplate::New(v8::Isolate::GetCurrent(), New);
            t->SetClassName(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SaxonProcessor"));
            t->InstanceTemplate()->SetInternalFieldCount(1);
            Constructor.Reset(v8::Isolate::GetCurrent(), t);
            // member method prototypes
            NODE_SET_PROTOTYPE_METHOD(t, "newTransformer", newTransformer);
            NODE_SET_PROTOTYPE_METHOD(t, "newXQueryProcessor", newXQueryProcessor);
            NODE_SET_PROTOTYPE_METHOD(t, "newXPathProcessor", newXPathProcessor);
            NODE_SET_PROTOTYPE_METHOD(t, "newSchemaValidator", newSchemaValidator);
            NODE_SET_PROTOTYPE_METHOD(t, "makeValue", makeValue);
            NODE_SET_PROTOTYPE_METHOD(t, "makeQNameValue", makeQNameValue);
            NODE_SET_PROTOTYPE_METHOD(t, "getStringValue", getStringValue);
            NODE_SET_PROTOTYPE_METHOD(t, "parseXmlFromString", parseXmlFromString);
            NODE_SET_PROTOTYPE_METHOD(t, "parseXmlFromFile", parseXmlFromFile);
            NODE_SET_PROTOTYPE_METHOD(t, "parseXmlFromUri", parseXmlFromUri);
            NODE_SET_PROTOTYPE_METHOD(t, "setProperty", setProperty);
            NODE_SET_PROTOTYPE_METHOD(t, "getProperties", getProperties);
            NODE_SET_PROTOTYPE_METHOD(t, "setcwd", setcwd);
            NODE_SET_PROTOTYPE_METHOD(t, "setResourcesDirectory", setResourcesDirectory);
            NODE_SET_PROTOTYPE_METHOD(t, "isSchemaAware", isSchemaAware);
            NODE_SET_PROTOTYPE_METHOD(t, "version", version);
            NODE_SET_PROTOTYPE_METHOD(t, "release", release);
            //        Local<Function> f=t->GetFunction();
            // append this function to the target object
            target->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SaxonProcessor"), t->GetFunction());
        };


    private:

        SaxonProcessorJS() : SaxonProcessorJS(false) {

        };

        SaxonProcessorJS(bool l) : cwd(""), processor (new SaxonProcessor(l)) {
        };
        SaxonProcessorJS(const SaxonProcessorJS& orig) = delete;

        ~SaxonProcessorJS() {
        };
        static Persistent<FunctionTemplate> Constructor;

        static void New(const v8::FunctionCallbackInfo<Value>& args) {
            // create processor object
            SaxonProcessorJS* sp;
            if (args.Length() < 1)
            {
                sp = new SaxonProcessorJS();
            }
            else
            {
                sp = new SaxonProcessorJS(args[0]->ToBoolean()->BooleanValue());
            }
//            std::cout<<"xsl:product-name "<<sp->processor->getProperty("xsl:product-name")<<std::endl;

            // extend target object with file
            sp->Wrap(args.This());

            // attach various properties
            //args.This()->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "path"), String::NewFromUtf8(v8::Isolate::GetCurrent(), f->m_file->getFileName().c_str()));
        };
        static void newTransformer(const v8::FunctionCallbackInfo<Value>& args);

        static void newXQueryProcessor(const v8::FunctionCallbackInfo<Value>& args);

        static void newXPathProcessor(const v8::FunctionCallbackInfo<Value>& args);

        static void newSchemaValidator(const v8::FunctionCallbackInfo<Value>& args);

        static void makeValue(const v8::FunctionCallbackInfo<Value>& args) {
            if (args.Length() != 1) {

                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "expected a value")));
                args.GetReturnValue().SetUndefined();
                return;

            }
            // unwrap xsltProcessor object
            SaxonProcessorJS* xp = ObjectWrap::Unwrap<SaxonProcessorJS>(args.This());

            XdmAtomicValue* xmlNode;
            if(args[0]->IsString()){
                String::Utf8Value str(args[0]->ToString());
                xmlNode=xp->processor->makeStringValue(*str);
            }
            else if(args[0]->IsBoolean()){
                xmlNode=xp->processor->makeBooleanValue(args[0]->BooleanValue());
            }
            else if(args[0]->IsInt32() ){
                xmlNode=xp->processor->makeIntegerValue(args[0]->Int32Value());
            }
            else if(args[0]->IsUint32()){
                xmlNode=xp->processor->makeIntegerValue(args[0]->Uint32Value());
            }
            else if(args[0]->IsNumber()){
                xmlNode=xp->processor->makeDoubleValue(args[0]->NumberValue());
            }
            else{
                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "Type unspported")));
                args.GetReturnValue().SetUndefined();
                return;
            }
            //std::cout<<"exceptionOccurred "<<xp->xsltProcessor->exceptionOccurred()<<std::endl;
            if(xp->processor->exceptionOccurred() && xp->processor->getException()->count()>0){
                //if(xp->processor->getException()->count()==0)xp->processor->checkException();
                std::ostringstream ss;
                ss<<"# of exceptions: "<<std::to_string(xp->processor->getException()->count())<<std::endl;
                for(unsigned int exceptionIndex=0;exceptionIndex<xp->processor->getException()->count();exceptionIndex++){
                    ss<<xp->processor->getException()->getErrorMessage(exceptionIndex)<<std::endl;
                }
                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), ss.str().c_str())));
                args.GetReturnValue().SetUndefined();
                return;
                
            }
            Local<Object> instance=XdmAtomicValueJS::Instantiate(args.This());
            XdmAtomicValueJS* xv = node::ObjectWrap::Unwrap<XdmAtomicValueJS>(instance);
            xv->value=xmlNode;
            //xdmValue->Wrap(instance);
            args.GetReturnValue().Set(instance);
        };

        static void makeQNameValue(const v8::FunctionCallbackInfo<Value>& args) {
            if (args.Length() != 1 || !args[0]->IsString()) {

                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "expected a qname string")));
                args.GetReturnValue().SetUndefined();
                return;

            }
            // unwrap xsltProcessor object
            SaxonProcessorJS* xp = ObjectWrap::Unwrap<SaxonProcessorJS>(args.This());

                std::string  str(*v8::String::Utf8Value(args[0]->ToString()));
                std::cout<<"makeQNameValue "<<(str)<<std::endl;
            XdmAtomicValue* xmlNode=xp->processor->makeQNameValue(str);
            //std::cout<<"exceptionOccurred "<<xp->xsltProcessor->exceptionOccurred()<<std::endl;
            if(xp->processor->exceptionOccurred() && xp->processor->getException()->count()>0){
                //if(xp->processor->getException()->count()==0)xp->processor->checkException();
                std::ostringstream ss;
                ss<<"# of exceptions: "<<std::to_string(xp->processor->getException()->count())<<std::endl;
                for(unsigned int exceptionIndex=0;exceptionIndex<xp->processor->getException()->count();exceptionIndex++){
                    ss<<xp->processor->getException()->getErrorMessage(exceptionIndex)<<std::endl;
                }
                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), ss.str().c_str())));
                args.GetReturnValue().SetUndefined();
                return;
                
            }
            Local<Object> instance=XdmAtomicValueJS::Instantiate(args.This());
            XdmAtomicValueJS* xv = node::ObjectWrap::Unwrap<XdmAtomicValueJS>(instance);
            xv->value=xmlNode;
            //xdmValue->Wrap(instance);
            args.GetReturnValue().Set(instance);
        };

        static void getStringValue(const v8::FunctionCallbackInfo<Value>& args) {
            if (args.Length() != 1 || !args[0]->IsObject()) {

                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "expected an XdmItem")));
                args.GetReturnValue().SetUndefined();
                return;

            }
            // unwrap xsltProcessor object
            SaxonProcessorJS* xp = ObjectWrap::Unwrap<SaxonProcessorJS>(args.This());

            
            std::string cn(*v8::String::Utf8Value(args[0]->ToObject()->GetConstructorName()));
            const char* str;
            if(cn.compare("XdmAtomicValue")==0){
                XdmAtomicValueJS* xi = ObjectWrap::Unwrap<XdmAtomicValueJS>(args[0]->ToObject());
                str=xp->processor->getStringValue(xi->value);
            }
            else if(cn.compare("XdmNode")==0){
                XdmNodeJS* xi = ObjectWrap::Unwrap<XdmNodeJS>(args[0]->ToObject());
                str=xp->processor->getStringValue(xi->value);
            }
            else{
                XdmItemJS* xi = ObjectWrap::Unwrap<XdmItemJS>(args[0]->ToObject());
                str=xp->processor->getStringValue(xi->value);
            }
            //std::cout<<"exceptionOccurred "<<xp->xsltProcessor->exceptionOccurred()<<std::endl;
            if(xp->processor->exceptionOccurred() && xp->processor->getException()->count()>0){
                //if(xp->processor->getException()->count()==0)xp->processor->checkException();
                std::ostringstream ss;
                ss<<"# of exceptions: "<<std::to_string(xp->processor->getException()->count())<<std::endl;
                for(unsigned int exceptionIndex=0;exceptionIndex<xp->processor->getException()->count();exceptionIndex++){
                    ss<<xp->processor->getException()->getErrorMessage(exceptionIndex)<<std::endl;
                }
                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), ss.str().c_str())));
                args.GetReturnValue().SetUndefined();
                return;
                
            }
            args.GetReturnValue().Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), str));
        };

        static void parseXmlFromString(const v8::FunctionCallbackInfo<Value>& args) {
            if (args.Length() != 1 || !args[0]->IsString()) {

                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "expected xml as string")));
                args.GetReturnValue().SetUndefined();
                return;

            }
            // the source
            String::Utf8Value source(args[0]->ToString());
            //std::cout<<(*source)<<std::endl;
            // unwrap xsltProcessor object
            SaxonProcessorJS* xp = ObjectWrap::Unwrap<SaxonProcessorJS>(args.This());

            XdmNode* xmlNode=xp->processor->parseXmlFromString(*source);
            //std::cout<<"exceptionOccurred "<<xp->xsltProcessor->exceptionOccurred()<<std::endl;
            if(xp->processor->exceptionOccurred() && xp->processor->getException()->count()>0){
                //if(xp->processor->getException()->count()==0)xp->processor->checkException();
                std::ostringstream ss;
                ss<<"# of exceptions: "<<std::to_string(xp->processor->getException()->count())<<std::endl;
                for(unsigned int exceptionIndex=0;exceptionIndex<xp->processor->getException()->count();exceptionIndex++){
                    ss<<xp->processor->getException()->getErrorMessage(exceptionIndex)<<std::endl;
                }
                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), ss.str().c_str())));
                args.GetReturnValue().SetUndefined();
                return;
                
            }
            Local<Object> instance=XdmNodeJS::Instantiate(args.This());
            XdmNodeJS* xv = node::ObjectWrap::Unwrap<XdmNodeJS>(instance);
            xv->value=xmlNode;
            //xdmValue->Wrap(instance);
            args.GetReturnValue().Set(instance);
        };

        static void parseXmlFromFile(const v8::FunctionCallbackInfo<Value>& args) {
            if (args.Length() != 1 || !args[0]->IsString()) {

                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "expected xml as filePath")));
                args.GetReturnValue().SetUndefined();
                return;

            }
            // the source
            String::Utf8Value source(args[0]->ToString());
            std::cout<<(*source)<<std::endl;
            // unwrap xsltProcessor object
            SaxonProcessorJS* xp = ObjectWrap::Unwrap<SaxonProcessorJS>(args.This());

            XdmNode* xmlNode=xp->processor->parseXmlFromFile(*source);
            //std::cout<<"exceptionOccurred "<<xp->processor->exceptionOccurred()<<std::endl;
            if(xp->processor->exceptionOccurred() && xp->processor->getException()->count()>0){
                //if(xp->processor->getException()->count()==0)xp->processor->checkException();
                std::ostringstream ss;
                ss<<"# of exceptions: "<<std::to_string(xp->processor->getException()->count())<<std::endl;
                for(unsigned int exceptionIndex=0;exceptionIndex<xp->processor->getException()->count();exceptionIndex++){
                    ss<<xp->processor->getException()->getErrorMessage(exceptionIndex)<<std::endl;
                }
                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), ss.str().c_str())));
                args.GetReturnValue().SetUndefined();
                return;
                
            }
            std::cout<<(*source)<<std::endl;
            Local<Object> instance=XdmNodeJS::Instantiate(args.This());
            //XdmNodeJS* xv = node::ObjectWrap::Unwrap<XdmNodeJS>(instance);
            XdmNodeJS* xv = new XdmNodeJS();
            xv->value=xmlNode;
            xv->Wrap(instance);
            std::cout<<"set ret "<<std::endl;
            args.GetReturnValue().Set(instance);
        };

        static void parseXmlFromUri(const v8::FunctionCallbackInfo<Value>& args) {
            if (args.Length() != 1 || !args[0]->IsString()) {

                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "expected xml as uri")));
                args.GetReturnValue().SetUndefined();
                return;

            }
            // the source
            String::Utf8Value source(args[0]->ToString());
            std::cout<<(*source)<<std::endl;
            // unwrap xsltProcessor object
            SaxonProcessorJS* xp = ObjectWrap::Unwrap<SaxonProcessorJS>(args.This());

            XdmNode* xmlNode=xp->processor->parseXmlFromUri(*source);
            //std::cout<<"exceptionOccurred "<<xp->xsltProcessor->exceptionOccurred()<<std::endl;
            if(xp->processor->exceptionOccurred() && xp->processor->getException()->count()>0){
                //if(xp->processor->getException()->count()==0)xp->processor->checkException();
                std::ostringstream ss;
                ss<<"# of exceptions: "<<std::to_string(xp->processor->getException()->count())<<std::endl;
                for(unsigned int exceptionIndex=0;exceptionIndex<xp->processor->getException()->count();exceptionIndex++){
                    ss<<xp->processor->getException()->getErrorMessage(exceptionIndex)<<std::endl;
                }
                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), ss.str().c_str())));
                args.GetReturnValue().SetUndefined();
                return;
                
            }
            Local<Object> instance=XdmNodeJS::Instantiate(args.This());
            XdmNodeJS* xv = node::ObjectWrap::Unwrap<XdmNodeJS>(instance);
            xv->value=xmlNode;
            //xdmValue->Wrap(instance);
            args.GetReturnValue().Set(instance);
        };

        static void setProperty(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

        static void getProperties(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

        static void setcwd(const v8::FunctionCallbackInfo<Value>& args) {
            if(args.Length()==1 && args[0]->IsString())
            {
                SaxonProcessorJS* sp = ObjectWrap::Unwrap<SaxonProcessorJS>(args.This());
                String::Utf8Value cwd(args[0]->ToString());
                sp->processor->setcwd((*cwd));
                args.GetReturnValue().SetUndefined();
            }
        };

        static void setResourcesDirectory(const v8::FunctionCallbackInfo<Value>& args) {
            if(args.Length()==1 && args[0]->IsString())
            {
                SaxonProcessorJS* sp = ObjectWrap::Unwrap<SaxonProcessorJS>(args.This());
                String::Utf8Value resourcesDirectory(args[0]->ToString());
                sp->processor->setResourcesDirectory((*resourcesDirectory));
                args.GetReturnValue().SetUndefined();
            }
        };

        static void isSchemaAware(const v8::FunctionCallbackInfo<v8::Value>& args) {
                SaxonProcessorJS* sp = ObjectWrap::Unwrap<SaxonProcessorJS>(args.This());
            args.GetReturnValue().Set(sp->processor->isSchemaAware());
        };

        static void version(const v8::FunctionCallbackInfo<Value>& args) {
                SaxonProcessorJS* sp = ObjectWrap::Unwrap<SaxonProcessorJS>(args.This());
                const char* buffer=sp->processor->version();
                args.GetReturnValue().Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), buffer, String::kNormalString, std::strlen(buffer)));
        };

        static void release(const v8::FunctionCallbackInfo<Value>& args) {
                SaxonProcessorJS* sp = ObjectWrap::Unwrap<SaxonProcessorJS>(args.This());
                sp->processor->release();
                args.GetReturnValue().SetUndefined();
        };

    protected:

    };

};

