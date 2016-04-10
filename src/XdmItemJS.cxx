
#include "XdmItemJS.hpp"

namespace saxon_node {
    
        void XdmItemJS::getStringValue(const v8::FunctionCallbackInfo<v8::Value>& args) {
            XdmItemJS* xdmValue = node::ObjectWrap::Unwrap<XdmItemJS>(args.This());
            const char* buffer=xdmValue->value->getStringValue();
            args.GetReturnValue().Set(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(),(char*)buffer));
        };

        void XdmItemJS::getHead(const v8::FunctionCallbackInfo<v8::Value>& args) {
            XdmItemJS* xdmValue = node::ObjectWrap::Unwrap<XdmItemJS>(args.This());
            XdmItem* xdmItem=xdmValue->value->getHead();
            v8::Local<v8::Object> instance=XdmItemJS::Instantiate(args.This());
            //XdmItemJS* xv = node::ObjectWrap::Unwrap<XdmItemJS>(instance);
            XdmItemJS* xv = new XdmItemJS();
            xv->value=xdmItem;
            xv->Wrap(instance);
            args.GetReturnValue().Set(instance);
        };

        void XdmItemJS::itemAt(const v8::FunctionCallbackInfo<v8::Value>& args) {
            if (args.Length() != 1 || !args[0]->IsNumber()) {

                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), "expected an index")));
                args.GetReturnValue().SetUndefined();
                return;

            }
            XdmItemJS* xdmValue = node::ObjectWrap::Unwrap<XdmItemJS>(args.This());
            XdmItem* xdmItem=xdmValue->value->itemAt(args[0]->IntegerValue());
            v8::Local<v8::Object> instance=XdmItemJS::Instantiate(args.This());
            //XdmItemJS* xv = node::ObjectWrap::Unwrap<XdmItemJS>(instance);
            XdmItemJS* xv = new XdmItemJS();
            xv->value=xdmItem;
            xv->Wrap(instance);
            args.GetReturnValue().Set(instance);
        };

        void XdmItemJS::size(const v8::FunctionCallbackInfo<v8::Value>& args) {
            XdmItemJS* xdmValue = node::ObjectWrap::Unwrap<XdmItemJS>(args.This());
            int num=xdmValue->value->size();
            args.GetReturnValue().Set(v8::Uint32::New(v8::Isolate::GetCurrent(), num));
        };

}
