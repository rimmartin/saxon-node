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
#include "XdmNode.h"
#include "SchemaValidator.h"

#include "XdmNodeJS.hpp"

namespace saxon_node {

    using namespace v8;

    class SaxonProcessorJS;

    class SchemaValidatorJS : public node::ObjectWrap {
    protected:

    public:

        static void Initialize(Handle<Object> target) {
            // instantiate constructor function template
            Local<FunctionTemplate> t = FunctionTemplate::New(v8::Isolate::GetCurrent(), New);
            t->SetClassName(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SchemaValidator"));
            t->InstanceTemplate()->SetInternalFieldCount(1);
            Constructor.Reset(v8::Isolate::GetCurrent(), t);
            // member method prototypes
            NODE_SET_PROTOTYPE_METHOD(t, "validate", validate);
            NODE_SET_PROTOTYPE_METHOD(t, "validateToNode", validateToNode);
            NODE_SET_PROTOTYPE_METHOD(t, "setSourceNode", setSourceNode);
            NODE_SET_PROTOTYPE_METHOD(t, "registerSchemaFromFile", registerSchemaFromFile);
            NODE_SET_PROTOTYPE_METHOD(t, "getValidationReport", getValidationReport);
            NODE_SET_PROTOTYPE_METHOD(t, "setParameter", setParameter);
            NODE_SET_PROTOTYPE_METHOD(t, "getParameter", getParameter);
            NODE_SET_PROTOTYPE_METHOD(t, "removeParameter", removeParameter);
            NODE_SET_PROTOTYPE_METHOD(t, "setProperty", setProperty);
            NODE_SET_PROTOTYPE_METHOD(t, "getProperty", getProperty);
            NODE_SET_PROTOTYPE_METHOD(t, "clearParameters", clearParameters);
            //        Local<Function> f=t->GetFunction();
            // append this function to the target object
            target->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "SchemaValidator"), t->GetFunction());
        };

        static Local<Object> Instantiate(Local<Object> proc) {
            Local<Value> argv[1] = {

                proc

            };

            // return new group instance
            return Local<FunctionTemplate>::New(v8::Isolate::GetCurrent(), Constructor)->GetFunction()->NewInstance(1, argv);

        };
    private:

        SchemaValidatorJS() : SchemaValidatorJS(false) {

        };

        SchemaValidatorJS(bool l) {

        };

        ~SchemaValidatorJS() {
        };
        static Persistent<FunctionTemplate> Constructor;

        static void New(const v8::FunctionCallbackInfo<Value>& args) {
            // create hdf file object
            SchemaValidatorJS* xp;
            if (args.Length() < 1)
                xp = new SchemaValidatorJS();
            else
                xp = new SchemaValidatorJS(args[1]->ToBoolean()->BooleanValue());

            xp->procJS = args[0]->ToObject();
            // unwrap processor object
            xp->proc = ObjectWrap::Unwrap<SaxonProcessorJS>(args[0]->ToObject());

            xp->schemaValidator.reset(xp->proc->processor->newSchemaValidator());
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

        static void setSourceNode(const v8::FunctionCallbackInfo<Value>& args) {
            if (args.Length() != 1 || !args[0]->IsString()) {

                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "expected xml source as string")));
                args.GetReturnValue().SetUndefined();
                return;

            }
            // the source
            String::Utf8Value context(args[0]->ToString());
            //std::cout<<(*source)<<std::endl;
            // unwrap schemaValidator object
            SchemaValidatorJS* xp = ObjectWrap::Unwrap<SchemaValidatorJS>(args.This());
            xp->schemaValidator->setSourceNode((XdmNode*)xp->proc->processor->makeStringValue(*context));
            args.GetReturnValue().SetUndefined();

        };

        static void registerSchemaFromFile(const v8::FunctionCallbackInfo<Value>& args) {
            if (args.Length() != 1 || !args[0]->IsString()) {

                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "expected xsd source as path string")));
                args.GetReturnValue().SetUndefined();
                return;

            }
            // the source
            String::Utf8Value xsd(args[0]->ToString());
            //std::cout<<(*source)<<std::endl;
            // unwrap schemaValidator object
            SchemaValidatorJS* xp = ObjectWrap::Unwrap<SchemaValidatorJS>(args.This());
            xp->schemaValidator->registerSchemaFromFile(*xsd);
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
            if (args.Length() != 2 || !args[0]->IsString() || !args[1]->IsString()) {

                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "expected property name an value as strings")));
                args.GetReturnValue().SetUndefined();
                return;

            }
            // the source
            String::Utf8Value properyName(args[0]->ToString());
            String::Utf8Value properyValue(args[1]->ToString());
            //std::cout<<(*source)<<std::endl;
            // unwrap schemaValidator object
            SchemaValidatorJS* xp = ObjectWrap::Unwrap<SchemaValidatorJS>(args.This());
            xp->schemaValidator->setProperty(*properyName, *properyValue);
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

        static void validate(const v8::FunctionCallbackInfo<Value>& args) {
            if(args.Length()>1 || (args.Length()==1 && !args[0]->IsString()))
            {
                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "not correct arguments")));
                args.GetReturnValue().SetUndefined();
            }
            // unwrap schemaValidator object
            SchemaValidatorJS* xp = ObjectWrap::Unwrap<SchemaValidatorJS>(args.This());
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
                //@todo xp->schemaValidator->setParameter(*pn, new XdmValue(*pnValue));
            }
            // the source
            String::Utf8Value sourceFile(args[0]->ToString());
            //String::Utf8Value query(args[1]->ToString());
            //String::Utf8Value outputfile(args[2]->ToString());
            std::cout<<(*sourceFile)<<std::endl;
            xp->schemaValidator->validate((*sourceFile));
            std::cout<<"after "<<std::endl;
            if(xp->schemaValidator->exceptionOccurred() || xp->schemaValidator->exceptionCount()>0){
                if(xp->schemaValidator->exceptionCount()==0)xp->schemaValidator->checkException();
                std::ostringstream ss;
                ss<<"# of exceptions: "<<std::to_string(xp->schemaValidator->exceptionCount())<<std::endl;
                for(unsigned int exceptionIndex=0;exceptionIndex<xp->schemaValidator->exceptionCount();exceptionIndex++){
                    ss<<xp->schemaValidator->getErrorMessage(exceptionIndex)<<std::endl;
                }
                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), ss.str().c_str())));
                args.GetReturnValue().SetUndefined();
                return;
                
            }
            args.GetReturnValue().SetUndefined();
        };

        static void validateToNode(const v8::FunctionCallbackInfo<Value>& args) {
            if(args.Length()<=1 || !args[0]->IsString())
            {
                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "not correct arguments")));
                args.GetReturnValue().SetUndefined();
            }
            // unwrap schemaValidator object
            SchemaValidatorJS* xp = ObjectWrap::Unwrap<SchemaValidatorJS>(args.This());
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
                //@todo xp->schemaValidator->setParameter(*pn, new XdmValue(*pnValue));
            }
            // the source
            String::Utf8Value sourceFile(args[0]->ToString());
            //String::Utf8Value query(args[1]->ToString());
            //String::Utf8Value outputfile(args[2]->ToString());
            XdmNode* xdmNode=xp->schemaValidator->validateToNode((*sourceFile));
            if(xp->schemaValidator->exceptionOccurred() || xp->schemaValidator->exceptionCount()>0){
                if(xp->schemaValidator->exceptionCount()==0)xp->schemaValidator->checkException();
                std::ostringstream ss;
                ss<<"# of exceptions: "<<std::to_string(xp->schemaValidator->exceptionCount())<<std::endl;
                for(unsigned int exceptionIndex=0;exceptionIndex<xp->schemaValidator->exceptionCount();exceptionIndex++){
                    ss<<xp->schemaValidator->getErrorMessage(exceptionIndex)<<std::endl;
                }
                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), ss.str().c_str())));
                args.GetReturnValue().SetUndefined();
                return;
                
            }
            Local<Object> instance=XdmNodeJS::Instantiate(args.This());
            //XdmNodeJS* xv = node::ObjectWrap::Unwrap<XdmNodeJS>(instance);
            XdmNodeJS* xv = new XdmNodeJS();
            xv->value=xdmNode;
            xv->Wrap(instance);
            std::cout<<"set ret "<<std::endl;
            args.GetReturnValue().Set(instance);
        };

        static void getValidationReport(const v8::FunctionCallbackInfo<Value>& args) {
            if(args.Length()!=0)
            {
                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "expected base uri as string")));
                args.GetReturnValue().SetUndefined();
            }
            // unwrap schemaValidator object
            SchemaValidatorJS* xp = ObjectWrap::Unwrap<SchemaValidatorJS>(args.This());
            // the base uri
            //String::Utf8Value xPathStr(args[0]->ToString());
            XdmNode* report=xp->schemaValidator->getValidationReport();
            if(xp->schemaValidator->exceptionOccurred() || xp->schemaValidator->exceptionCount()>0){
                if(xp->schemaValidator->exceptionCount()==0)xp->schemaValidator->checkException();
                std::ostringstream ss;
                ss<<"# of exceptions: "<<std::to_string(xp->schemaValidator->exceptionCount())<<std::endl;
                for(unsigned int exceptionIndex=0;exceptionIndex<xp->schemaValidator->exceptionCount();exceptionIndex++){
                    ss<<xp->schemaValidator->getErrorMessage(exceptionIndex)<<std::endl;
                }
                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), ss.str().c_str())));
                args.GetReturnValue().SetUndefined();
                return;
                
            }
            Local<Object> instance=XdmNodeJS::Instantiate(args.This());
            //XdmNodeJS* xv = node::ObjectWrap::Unwrap<XdmNodeJS>(instance);
            XdmNodeJS* xv = new XdmNodeJS();
            xv->value=report;
            xv->Wrap(instance);
            args.GetReturnValue().Set(instance);
        };

        static void exceptionOccurred(const v8::FunctionCallbackInfo<Value>& args) {
            v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(String::NewFromUtf8(v8::Isolate::GetCurrent(), "unsupported method")));
            args.GetReturnValue().SetUndefined();
        };

    private:
        Local<Object> procJS;
        SaxonProcessorJS* proc;
        std::shared_ptr<SchemaValidator> schemaValidator;
        XdmValue* value;

    };

};
