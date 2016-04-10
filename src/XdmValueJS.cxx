
#include "XdmItemJS.hpp"
#include "XdmValueJS.hpp"

namespace saxon_node {
    
        void XdmValueJS::getHead(const v8::FunctionCallbackInfo<v8::Value>& args) {
            XdmValueJS* xdmValue = node::ObjectWrap::Unwrap<XdmValueJS>(args.This());
            XdmItem* xdmItem=xdmValue->value->getHead();
            v8::Local<v8::Object> instance=XdmItemJS::Instantiate(args.This());
            //XdmItemJS* xv = node::ObjectWrap::Unwrap<XdmItemJS>(instance);
            XdmItemJS* xv = new XdmItemJS();
            xv->value=xdmItem;
            xv->Wrap(instance);
            args.GetReturnValue().Set(instance);
        };
        
        void XdmValueJS::itemAt(const v8::FunctionCallbackInfo<v8::Value>& args) {
            XdmValueJS* xdmValue = node::ObjectWrap::Unwrap<XdmValueJS>(args.This());
            XdmItem* xdmItem=xdmValue->value->getHead();
            v8::Local<v8::Object> instance=XdmItemJS::Instantiate(args.This());
            //XdmItemJS* xv = node::ObjectWrap::Unwrap<XdmItemJS>(instance);
            XdmItemJS* xv = new XdmItemJS();
            xv->value=xdmItem;
            xv->Wrap(instance);
            args.GetReturnValue().Set(instance);
        };

        void XdmValueJS::size(const v8::FunctionCallbackInfo<v8::Value>& args) {
            XdmValueJS* xdmValue = node::ObjectWrap::Unwrap<XdmValueJS>(args.This());
            int num=xdmValue->value->size();
            args.GetReturnValue().Set(v8::Uint32::New(v8::Isolate::GetCurrent(), num));
        };

}

