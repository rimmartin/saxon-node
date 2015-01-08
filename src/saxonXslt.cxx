#include <node.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include "SaxonApiException.hpp"
#include "SaxonProcessor.hpp"
#include "XsltProcessor.hpp"

using namespace v8;

extern "C" {

    static void init (Handle<Object> target) {
        
        // initialize wrapped objects
        saxon::SaxonProcessor::Initialize(target);
        saxon::XsltProcessor::Initialize(target);
        
    }
    
    NODE_MODULE(saxonXslt, init)

}


