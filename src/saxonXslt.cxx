#include <node.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include "SaxonProcessorJS.hpp"
#include "XsltProcessorJS.hpp"
#include "XQueryProcessorJS.hpp"

using namespace v8;

extern "C" {

    static void init (Handle<Object> target) {
        
        // initialize wrapped objects
        saxon_node::SaxonProcessorJS::Initialize(target);
        saxon_node::XsltProcessorJS::Initialize(target);
        saxon_node::XQueryProcessorJS::Initialize(target);
        
    }
    
    NODE_MODULE(saxonXslt, init)

}


