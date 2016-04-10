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
#include "XdmNode.h"

#include "XdmItemJS.hpp"

namespace saxon_node {

    class SaxonProcessorJS;
    //class XdmValueJS;
    //class XdmItemJS;
    
    class XdmNodeJS : public XdmItemJS {
        //friend class XdmValueJS;
        friend class XdmItemJS;
        friend class XsltProcessorJS;
        friend class XPathProcessorJS;
        friend class SaxonProcessorJS;
        friend class SchemaValidatorJS;
        
    protected:

    public:

        static void Initialize(v8::Handle<v8::Object> target) {
            // instantiate constructor function template
            v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(v8::Isolate::GetCurrent(), New);
            t->SetClassName(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), "XdmNode"));
            t->InstanceTemplate()->SetInternalFieldCount(1);
            Constructor.Reset(v8::Isolate::GetCurrent(), t);
            // member method prototypes
            NODE_SET_PROTOTYPE_METHOD(t, "getStringValue", getStringValue);
            NODE_SET_PROTOTYPE_METHOD(t, "getHead", getHead);
            NODE_SET_PROTOTYPE_METHOD(t, "itemAt", itemAt);
            NODE_SET_PROTOTYPE_METHOD(t, "size", size);
            //        Local<Function> f=t->GetFunction();
            // append this function to the target object
            target->Set(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), "XdmNode"), t->GetFunction());
        };

        static v8::Local<v8::Object> Instantiate(v8::Local<v8::Object> proc) {
            v8::Local<v8::Value> argv[1] = {

                proc

            };

            // return new group instance
            return v8::Local<v8::FunctionTemplate>::New(v8::Isolate::GetCurrent(), Constructor)->GetFunction()->NewInstance(1, argv);

        };
    private:

        XdmNodeJS() : XdmNodeJS(false) {

        };

        XdmNodeJS(bool l) {

        };

        ~XdmNodeJS() {
        };
    private:

        static v8::Persistent<v8::FunctionTemplate> Constructor;

        static void New(const v8::FunctionCallbackInfo<v8::Value>& args) {
            // Xdm value object
            XdmNodeJS* xp;
            if (args.Length() < 1)
                xp = new XdmNodeJS();
            else
                xp = new XdmNodeJS(args[1]->ToBoolean()->BooleanValue());

            //xp->procJS = args[0]->ToObject();
            // unwrap processor object
            //xp->proc = ObjectWrap::Unwrap<SaxonProcessorJS>(args[0]->ToObject());

            //xp->xdmItem.reset(new XdmNode());
            std::cout<<"extend target object with processor"<<std::endl;
            // extend target object with processor
            xp->Wrap(args.This());

            // attach various properties
            //args.This()->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "parameters"), Object::New(v8::Isolate::GetCurrent()));
            //args.This()->Set(String::NewFromUtf8(v8::Isolate::GetCurrent(), "properties"), Object::New(v8::Isolate::GetCurrent()));
        };

        static void getStringValue(const v8::FunctionCallbackInfo<v8::Value>& args) {
            XdmNodeJS* xdmValue = node::ObjectWrap::Unwrap<XdmNodeJS>(args.This());
            const char* buffer=xdmValue->value->getStringValue();
            args.GetReturnValue().Set(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(),(char*)buffer));
        };

        static void getHead(const v8::FunctionCallbackInfo<v8::Value>& args);

        static void itemAt(const v8::FunctionCallbackInfo<v8::Value>& args);

        static void size(const v8::FunctionCallbackInfo<v8::Value>& args) {
            XdmNodeJS* xdmValue = node::ObjectWrap::Unwrap<XdmNodeJS>(args.This());
            int num=xdmValue->value->size();
            args.GetReturnValue().Set(v8::Uint32::New(v8::Isolate::GetCurrent(), num));
        };

    protected:
        XdmNode* value;

    };
}
