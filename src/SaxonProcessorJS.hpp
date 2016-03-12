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

        static void Initialize(Handle<Object> target) {
            // instantiate constructor function template
            Local<FunctionTemplate> t = FunctionTemplate::New(v8::Isolate::GetCurrent(), New);
            t->SetClassName(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SaxonProcessor"));
            t->InstanceTemplate()->SetInternalFieldCount(1);
            Constructor.Reset(v8::Isolate::GetCurrent(), t);
            // member method prototypes
            NODE_SET_PROTOTYPE_METHOD(t, "newTransformer", newTransformer);
            NODE_SET_PROTOTYPE_METHOD(t, "newXQueryProcessor", newXQueryProcessor);
            NODE_SET_PROTOTYPE_METHOD(t, "newXPathProcessor", newXPathProcessor);
            NODE_SET_PROTOTYPE_METHOD(t, "newSchemaValidator", newSchemaValidator);
            NODE_SET_PROTOTYPE_METHOD(t, "parseXmlFromString", parseXmlFromString);
            NODE_SET_PROTOTYPE_METHOD(t, "parseXmlFromFile", parseXmlFromFile);
            NODE_SET_PROTOTYPE_METHOD(t, "parseXmlFromUri", parseXmlFromUri);
            NODE_SET_PROTOTYPE_METHOD(t, "setProperty", setProperty);
            NODE_SET_PROTOTYPE_METHOD(t, "getProperties", getProperties);
            NODE_SET_PROTOTYPE_METHOD(t, "setcwd", setcwd);
            NODE_SET_PROTOTYPE_METHOD(t, "setResourcesDirectory", setResourcesDirectory);
            NODE_SET_PROTOTYPE_METHOD(t, "isSchemaAware", isSchemaAware);
            NODE_SET_PROTOTYPE_METHOD(t, "version", version);
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

    protected:

    };

};

