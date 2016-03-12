#include <node.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include "SaxonProcessorJS.hpp"
#include "XsltProcessorJS.hpp"
#include "XQueryProcessorJS.hpp"
#include "XPathProcessorJS.hpp"
#include "SchemaValidatorJS.hpp"

using namespace v8;

extern "C" {

    static void init (Handle<Object> target) {
        
        // initialize wrapped objects
        saxon_node::SaxonProcessorJS::Initialize(target);
        saxon_node::XsltProcessorJS::Initialize(target);
        saxon_node::XQueryProcessorJS::Initialize(target);
        saxon_node::XPathProcessorJS::Initialize(target);
        saxon_node::SchemaValidatorJS::Initialize(target);
        saxon_node::XdmValueJS::Initialize(target);
        saxon_node::XdmItemJS::Initialize(target);
        saxon_node::XdmNodeJS::Initialize(target);
        saxon_node::XdmAtomicValueJS::Initialize(target);
        
    }
    
    NODE_MODULE(saxonXslt, init)

}


