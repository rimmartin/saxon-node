#include "XQueryProcessor.h"



    XQueryProcessor::XQueryProcessor(SaxonProcessor *p, bool license, string curr) {
    proc = p;

    /*
     * Look for class.
     */
     cppClass = proc->lookForClass(proc->env, "net/sf/saxon/option/cpp/XQueryEngineForCpp");


    cpp = proc->createObject2 (proc->env, cppClass, "(Lnet/sf/saxon/s9api/Processor;Z)V", proc->proc, license);
    jmethodID mID_proc = (jmethodID)proc->env->GetMethodID (cppClass,"getProcessor", "()Lnet/sf/saxon/s9api/Processor;");
    proc->proc = (jobject)(proc->env->CallObjectMethod(cpp, mID_proc));
    jmethodID debugMID = proc->env->GetStaticMethodID(cppClass, "setDebugMode", "(Z)V");
    if(debugMID){
	proc->env->CallStaticVoidMethod(cppClass, debugMID, (jboolean)false);
    }

    proc->exception = NULL;
    outputfile1 = "";
    if(proc->cwd.compare("")){	
	    proc->cwd = curr;
    }
    queryFileExists = false;
    }


    /**
     * Set the source document for the query
    */
    void XQueryProcessor::setSourceValue(XdmValue * node){
	if(node== NULL){
		proc->setSourceValue(node);

	}
    }


    /**
     * Set the source document for the query
    */
    void XQueryProcessor::setSourceFile(const char * ifile){
	setProperty("s", ifile);
    }

    /**
     * Set the output file where the result is sent
    */
    void XQueryProcessor::setOutputfile(const char* ofile){
       outputfile1 = string(ofile); 
       setProperty("o", ofile);
    }

    /**
     * Set a parameter value used in the query
     *
     * @param name  of the parameter, as a string
     * @param value of the query parameter, or null to clear a previously set value
     */
    void XQueryProcessor::setParameter(const char * name, XdmValue*value){
	return proc->setParameter(name, value);
    }


    /**
     * Remove a parameter (name, value) pair
     *
     * @param namespacei currently not used
     * @param name  of the parameter
     * @return bool - outcome of the romoval
     */
    bool XQueryProcessor::removeParameter(const char * name){
	return proc->removeParameter(name);
    }
    /**
     * Set a property.
     *
     * @param name of the property
     * @param value of the property
     */
    void XQueryProcessor::setProperty(const char * name, const char * value){
	proc->setProperty(name, value);
    }

    void XQueryProcessor::clearParameters(){
	proc->clearParameters();
    }

   void XQueryProcessor::clearProperties(){
	proc->clearProperties();
        outputfile1.clear();
   }




    void XQueryProcessor::setBaseURI(const char * baseURI){
	proc->setProperty("base", baseURI);
    }

    void XQueryProcessor::executeQueryToFile(const char * infilename, const char * ofilename, const char * query){
	setProperty("resources", proc->getResourcesDirectory());  

	jmethodID mID = (jmethodID)proc->env->GetMethodID (cppClass,"executeQueryToFile", "(Ljava/lang/String;Ljava/lang/String;[Ljava/lang/String;[Ljava/lang/Object;)Ljava/lang/String;");
 	if (!mID) {
        cout<<"Error: MyClassInDll."<<"xsltApplyStylesheet"<<" not found\n"<<endl;
    } else {
	std::map<string,XdmValue*> parameters= proc->getParameters();
	std::map<string,string> properties = proc->getProperties();
	jobjectArray stringArray = NULL;
	jobjectArray objectArray = NULL;

	int size = parameters.size() + properties.size();
	if(query!= NULL) size++;
	if(infilename!= NULL) size++;	
	if(size >0) {

	   int i=0;
           jclass objectClass = proc->lookForClass(proc->env, "java/lang/Object");
	   jclass stringClass = proc->lookForClass(proc->env, "java/lang/String");
	   objectArray = proc->env->NewObjectArray( (jint)size, objectClass, 0 );
	   stringArray = proc->env->NewObjectArray( (jint)size, stringClass, 0 );
	   if(query!= NULL) {
	     proc->env->SetObjectArrayElement( stringArray, i, proc->env->NewStringUTF("qs") );
     	     proc->env->SetObjectArrayElement( objectArray, i, proc->env->NewStringUTF(query));
	     i++;	
	   }
	   if(infilename!= NULL) {
	     proc->env->SetObjectArrayElement( stringArray, i, proc->env->NewStringUTF("s") );
     	     proc->env->SetObjectArrayElement( objectArray, i, proc->env->NewStringUTF(infilename));
	     i++;	
	   }
	   for(map<string, XdmValue* >::iterator iter=parameters.begin(); iter!=parameters.end(); ++iter, i++) {
	     proc->env->SetObjectArrayElement( stringArray, i, proc->env->NewStringUTF( (iter->first).c_str() ) );
		bool checkCast = proc->env->IsInstanceOf((iter->second)->getUnderlyingValue(proc), proc->lookForClass(proc->env, "net/sf/saxon/option/cpp/XdmValueForCpp") );
		if(( (bool)checkCast)==false ){
			failure = "FAILURE in  array of XdmValueForCpp";
		} 
	     proc->env->SetObjectArrayElement( objectArray, i, (jobject)((iter->second)->getUnderlyingValue(proc)) );
	   }
  	   for(map<string, string >::iterator iter=properties.begin(); iter!=properties.end(); ++iter, i++) {
	     proc->env->SetObjectArrayElement( stringArray, i, proc->env->NewStringUTF( (iter->first).c_str()  ));
	     proc->env->SetObjectArrayElement( objectArray, i, (jobject)(proc->env->NewStringUTF((iter->second).c_str())) );
	   }
	}

	 proc->env->CallObjectMethod(cpp, mID, proc->env->NewStringUTF(proc->cwd.c_str()), proc->env->NewStringUTF(ofilename), stringArray, objectArray );
	  proc->env->DeleteLocalRef(objectArray);
	  proc->env->DeleteLocalRef(stringArray);
	 
  }


   }


    XdmValue * XQueryProcessor::executeQueryToValue(const char * infilename, const char * query){
	setProperty("resources", proc->getResourcesDirectory()); 
 jmethodID mID = (jmethodID)proc->env->GetMethodID (cppClass,"executeQueryToValue", "(Ljava/lang/String;[Ljava/lang/String;[Ljava/lang/Object;)Ljava/lang/String;");
 if (!mID) {
        cout<<"Error: MyClassInDll."<<"xsltApplyStylesheet"<<" not found\n"<<endl;
    } else {
	std::map<string,XdmValue*> parameters= proc->getParameters();
	std::map<string,string> properties = proc->getProperties();
	jobjectArray stringArray = NULL;
	jobjectArray objectArray = NULL;

	int size = parameters.size() + properties.size();
	if(query!= NULL) size++;
	if(infilename!= NULL) size++;
	if(size >0) {
	   int i=0;
           jclass objectClass = proc->lookForClass(proc->env, "java/lang/Object");
	   jclass stringClass = proc->lookForClass(proc->env, "java/lang/String");
	   objectArray = proc->env->NewObjectArray( (jint)size, objectClass, 0 );
	   stringArray = proc->env->NewObjectArray( (jint)size, stringClass, 0 );

	   if(query!= NULL) {
	     proc->env->SetObjectArrayElement( stringArray, i, proc->env->NewStringUTF("qs") );
     	     proc->env->SetObjectArrayElement( objectArray, i, proc->env->NewStringUTF(query));
	     i++;	
	   }
	   if(infilename!= NULL) {
	     proc->env->SetObjectArrayElement( stringArray, i, proc->env->NewStringUTF("s") );
     	     proc->env->SetObjectArrayElement( objectArray, i, proc->env->NewStringUTF(infilename));
	     i++;	
	   }
	   for(map<string, XdmValue* >::iterator iter=parameters.begin(); iter!=parameters.end(); ++iter, i++) {
	     proc->env->SetObjectArrayElement( stringArray, i, proc->env->NewStringUTF( (iter->first).c_str() ) );
		bool checkCast = proc->env->IsInstanceOf((iter->second)->getUnderlyingValue(proc), proc->lookForClass(proc->env, "net/sf/saxon/option/cpp/XdmValueForCpp") );
		if(( (bool)checkCast)==false ){
			failure = "FAILURE in  array of XdmValueForCpp";
		} 
	     proc->env->SetObjectArrayElement( objectArray, i, (jobject)((iter->second)->getUnderlyingValue(proc)) );
	   }
  	   for(map<string, string >::iterator iter=properties.begin(); iter!=properties.end(); ++iter, i++) {
	     proc->env->SetObjectArrayElement( stringArray, i, proc->env->NewStringUTF( (iter->first).c_str()  ));
	     proc->env->SetObjectArrayElement( objectArray, i, (jobject)(proc->env->NewStringUTF((iter->second).c_str())) );
	   }
	}

	  jobject result = (jobject)(proc->env->CallObjectMethod(cpp, mID, proc->env->NewStringUTF(proc->cwd.c_str()), stringArray, objectArray ));
	  proc->env->DeleteLocalRef(objectArray);
	  proc->env->DeleteLocalRef(stringArray);
    if(result) {
	XdmValue * node = new XdmValue(result);
	node->setProcessor(proc);
	return node;
     }
  }
  return NULL;

}

    const char * XQueryProcessor::executeQueryToString(const char * infilename, const char * query){
	setProperty("resources", proc->getResourcesDirectory()); 
 jmethodID mID = (jmethodID)proc->env->GetMethodID (cppClass,"executeQueryToString", "(Ljava/lang/String;[Ljava/lang/String;[Ljava/lang/Object;)Ljava/lang/String;");
 if (!mID) {
        cout<<"Error: MyClassInDll."<<"xsltApplyStylesheet"<<" not found\n"<<endl;
    } else {
	std::map<string,XdmValue*> parameters= proc->getParameters();
	std::map<string,string> properties = proc->getProperties();
	jobjectArray stringArray = NULL;
	jobjectArray objectArray = NULL;

	int size = parameters.size() + properties.size();
	if(query!= NULL) size++;
	if(infilename!= NULL) size++;
	if(size >0) {
	   int i=0;
           jclass objectClass = proc->lookForClass(proc->env, "java/lang/Object");
	   jclass stringClass = proc->lookForClass(proc->env, "java/lang/String");
	   objectArray = proc->env->NewObjectArray( (jint)size, objectClass, 0 );
	   stringArray = proc->env->NewObjectArray( (jint)size, stringClass, 0 );

	   if(query!= NULL) {
	     proc->env->SetObjectArrayElement( stringArray, i, proc->env->NewStringUTF("qs") );
     	     proc->env->SetObjectArrayElement( objectArray, i, proc->env->NewStringUTF(query));
	     i++;	
	   }
	   if(infilename!= NULL) {
	     proc->env->SetObjectArrayElement( stringArray, i, proc->env->NewStringUTF("s") );
     	     proc->env->SetObjectArrayElement( objectArray, i, proc->env->NewStringUTF(infilename));
	     i++;	
	   }
	   for(map<string, XdmValue* >::iterator iter=parameters.begin(); iter!=parameters.end(); ++iter, i++) {
	     proc->env->SetObjectArrayElement( stringArray, i, proc->env->NewStringUTF( (iter->first).c_str() ) );
		bool checkCast = proc->env->IsInstanceOf((iter->second)->getUnderlyingValue(proc), proc->lookForClass(proc->env, "net/sf/saxon/option/cpp/XdmValueForCpp") );
		if(( (bool)checkCast)==false ){
			failure = "FAILURE in  array of XdmValueForCpp";
		} 
	     proc->env->SetObjectArrayElement( objectArray, i, (jobject)((iter->second)->getUnderlyingValue(proc)) );
	   }
  	   for(map<string, string >::iterator iter=properties.begin(); iter!=properties.end(); ++iter, i++) {
	     proc->env->SetObjectArrayElement( stringArray, i, proc->env->NewStringUTF( (iter->first).c_str()  ));
	     proc->env->SetObjectArrayElement( objectArray, i, (jobject)(proc->env->NewStringUTF((iter->second).c_str())) );
	   }
	}

	  jstring result = (jstring)(proc->env->CallObjectMethod(cpp, mID, proc->env->NewStringUTF(proc->cwd.c_str()), stringArray, objectArray ));
	  proc->env->DeleteLocalRef(objectArray);
	  proc->env->DeleteLocalRef(stringArray);
	  if(result) {
             const char * str = proc->env->GetStringUTFChars(result, NULL);
            //return "result should be ok";            
	    return str;
	   }
  }
  return NULL;


    }

    void XQueryProcessor::setQueryFile(const char * ofile){
	   outputfile1 = string(ofile); 
	   setProperty("q", ofile);
	    queryFileExists = true;
    }



void XQueryProcessor::exceptionClear(){
	if(proc->exception != NULL) {
		delete proc->exception;
		proc->exception = NULL;	
	}
}

bool XQueryProcessor::exceptionOccurred(){
	return proc->exceptionOccurred();

}


const char * XQueryProcessor::getErrorCode(int i) {
	if(proc->exception == NULL) {return NULL;}
	return proc->exception->getErrorCode(i);
}

const char * XQueryProcessor::getErrorMessage(int i ){
	if(proc->exception == NULL) {return NULL;}
	return proc->exception->getErrorMessage(i);
}

SaxonApiException* XQueryProcessor::checkException(){
	if(proc->exception == NULL) {
		proc->exception = proc->checkForException(proc->env, cppClass, cpp);
	}
        return proc->exception;
}



int XQueryProcessor::exceptionCount(){
	if(proc->exception != NULL){
		return proc->exception->count();
	}
	return 0;
}
