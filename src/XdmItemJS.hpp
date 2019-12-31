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
#include "XdmAtomicValue.h"

#include "XdmValueJS.hpp"

namespace saxon_node {

    class SaxonProcessorJS;
    //class XdmValueJS;
    //class XdmNodeJS;
    //class XdmAtomicValueJS;
    
    class XdmItemJS : public XdmValueJS {
        friend class XdmValueJS;
        friend class XdmNodeJS;
        friend class XdmAtomicValueJS;
        friend class Xslt30ProcessorJS;
        friend class XsltProcessorJS;
        friend class XPathProcessorJS;
        friend class SaxonProcessorJS;
    protected:

    public:

        static void Initialize(v8::Local<v8::Object> target) {
            v8::Isolate* isolate = v8::Isolate::GetCurrent();
            v8::Local<v8::Context> context = isolate->GetCurrentContext();
            // instantiate constructor function template
            v8::Local<v8::FunctionTemplate> t = v8::FunctionTemplate::New(v8::Isolate::GetCurrent(), New);
            t->SetClassName(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), "XdmItem", v8::NewStringType::kInternalized).ToLocalChecked());
            t->InstanceTemplate()->SetInternalFieldCount(1);
            Constructor.Reset(v8::Isolate::GetCurrent(), t);
            // member method prototypes
            NODE_SET_PROTOTYPE_METHOD(t, "getStringValue", getStringValue);
            NODE_SET_PROTOTYPE_METHOD(t, "getHead", getHead);
            NODE_SET_PROTOTYPE_METHOD(t, "itemAt", itemAt);
            NODE_SET_PROTOTYPE_METHOD(t, "size", size);
            // append this function to the target object
            target->Set(context, v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), "XdmItem", v8::NewStringType::kInternalized).ToLocalChecked(), t->GetFunction(context).ToLocalChecked());
        };

        static v8::Local<v8::Object> Instantiate(v8::Local<v8::Object> proc) {
            v8::Isolate* isolate = v8::Isolate::GetCurrent();
            v8::Local<v8::Context> context = isolate->GetCurrentContext();
            const unsigned        argc       = 1;
            v8::Local<v8::Value> argv[1] = {

                proc

            };

            // return new group instance
            return v8::Local<v8::FunctionTemplate>::New(isolate, Constructor)->GetFunction(context).ToLocalChecked()->NewInstance(isolate->GetCurrentContext(), argc, argv).ToLocalChecked();

        };
    protected:

        XdmItemJS() : XdmItemJS(false) {

        };

        XdmItemJS(bool l) {

        };

        ~XdmItemJS() {
        };
    private:

        static v8::Persistent<v8::FunctionTemplate> Constructor;

        static void New(const v8::FunctionCallbackInfo<v8::Value>& args) {
            v8::Isolate* isolate = v8::Isolate::GetCurrent();
            v8::Local<v8::Context> context = isolate->GetCurrentContext();
            // Xdm value object
            XdmItemJS* xp;
            if (args.Length() < 1)
                xp = new XdmItemJS();
            else
                xp = new XdmItemJS(args[1]->ToBoolean(isolate)->Value());

            //xp->procJS = args[0]->ToObject(context).ToLocalChecked();
            // unwrap processor object
            //xp->proc = ObjectWrap::Unwrap<SaxonProcessorJS>(args[0]->ToObject(context).ToLocalChecked());

            xp->xdmItem.reset(new XdmItem());
            // extend target object with processor
            xp->Wrap(args.This());

            // attach various properties
            //args.This()->Set(context, String::NewFromUtf8(v8::Isolate::GetCurrent(), "parameters", v8::NewStringType::kInternalized).ToLocalChecked(), Object::New(v8::Isolate::GetCurrent()));
            //args.This()->Set(context, String::NewFromUtf8(v8::Isolate::GetCurrent(), "properties", v8::NewStringType::kInternalized).ToLocalChecked(), Object::New(v8::Isolate::GetCurrent()));
        };

        static void getStringValue(const v8::FunctionCallbackInfo<v8::Value>& args);

        static void getHead(const v8::FunctionCallbackInfo<v8::Value>& args);

        static void itemAt(const v8::FunctionCallbackInfo<v8::Value>& args);

        static void size(const v8::FunctionCallbackInfo<v8::Value>& args);

    protected:
        //Local<Object> procJS;
        SaxonProcessorJS* proc;
        std::shared_ptr<XdmItem> xdmItem;
        XdmItem* value;

    };
}
