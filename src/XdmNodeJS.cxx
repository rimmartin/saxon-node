
#include "XdmNodeJS.hpp"

namespace saxon_node {
    
        void XdmNodeJS::getHead(const v8::FunctionCallbackInfo<v8::Value>& args) {
            XdmNodeJS* xdmValue = node::ObjectWrap::Unwrap<XdmNodeJS>(args.This());
            XdmItem* xdmItem=xdmValue->value->getHead();
            v8::Local<v8::Object> instance=XdmItemJS::Instantiate(args.This());
            //XdmItemJS* xv = node::ObjectWrap::Unwrap<XdmItemJS>(instance);
            XdmItemJS* xv = new XdmItemJS();
            xv->value=xdmItem;
            xv->Wrap(instance);
            args.GetReturnValue().Set(instance);
        };

        void XdmNodeJS::itemAt(const v8::FunctionCallbackInfo<v8::Value>& args) {
            if (args.Length() != 1 || !args[0]->IsNumber()) {

                v8::Isolate::GetCurrent()->ThrowException(v8::Exception::SyntaxError(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), "expected an index")));
                args.GetReturnValue().SetUndefined();
                return;

            }
            XdmNodeJS* xdmValue = node::ObjectWrap::Unwrap<XdmNodeJS>(args.This());
            XdmItem* xdmItem=xdmValue->value->itemAt(args[0]->IntegerValue());
            v8::Local<v8::Object> instance=XdmItemJS::Instantiate(args.This());
            //XdmItemJS* xv = node::ObjectWrap::Unwrap<XdmItemJS>(instance);
            XdmItemJS* xv = new XdmItemJS();
            xv->value=xdmItem;
            xv->Wrap(instance);
            args.GetReturnValue().Set(instance);
        };
}

