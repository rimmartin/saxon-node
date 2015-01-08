#include <jni.h>

#include "SaxonApiException.hpp"
#include "SaxonProcessor.hpp"
#include "XsltProcessor.hpp"
#include "XdmValue.h"


/*
* XdmNode Class implementation
*/

        jobject makeXdmValue(saxon::SaxonProcessor *proc, JNIEnv *env){
	 if(env == NULL) {
		std::cerr<<"Error: env is null\n"<<std::endl;
	 }
	   jclass xdmValueClass = proc->lookForClass(env, "net/sf/saxon/option/cpp/XdmValueForCpp");
	   jmethodID MID_init = proc->findConstructor (env, xdmValueClass, "()V");
 	   jobject xdmValue = (jobject)env->NewObject(xdmValueClass, MID_init);
      		if (!xdmValue) {
	        	std::cerr<<"Error: failed to allocate an object\n"<<std::endl;
        		return NULL;
      		}

	
	 return xdmValue;
	}


	jobject makeXdmValue(saxon::SaxonProcessor *proc, JNIEnv *env, bool b){ 
	 if(env == NULL) {
		std::cerr<<"Error: env is null\n"<<std::endl;
	 }
		jclass xdmValueClass = proc->lookForClass(env, "net/sf/saxon/option/cpp/XdmValueForCpp");
	        jmethodID MID_init = proc->findConstructor (env, xdmValueClass, "(Z)V");
 		jobject xdmValue = (jobject)(env->NewObject(xdmValueClass, MID_init, (jboolean)b));
      		if (!xdmValue) {
	        	std::cerr<<"Error: failed to allocate an object\n"<<std::endl;
        		return NULL;
      		}
		return xdmValue;
	}

	jobject makeXdmValue(saxon::SaxonProcessor *proc, JNIEnv *env, int i){ 
	 if(env == NULL) {
		std::cerr<<"Error: env is null\n"<<std::endl;
	 }
		jclass xdmValueClass = proc->lookForClass(env, "net/sf/saxon/option/cpp/XdmValueForCpp");
	        jmethodID MID_init = proc->findConstructor (env, xdmValueClass, "(I)V");
 		jobject xdmValue = (jobject)(env->NewObject(xdmValueClass, MID_init, (jint)i));
      		if (!xdmValue) {
	        	std::cerr<<"Error: failed to allocate an XdmValueForCpp object \n"<<std::endl;
        		return NULL;
      		}
		return xdmValue;
	}


	jobject makeXdmValue(saxon::SaxonProcessor *proc, JNIEnv *env, std::string type, std::string valueStr){ 
	 if(env == NULL) {
		std::cerr<<"Error: env is null\n"<<std::endl;
	 }
		jclass xdmValueClass = proc->lookForClass(env, "net/sf/saxon/option/cpp/XdmValueForCpp");
	        jmethodID MID_init = proc->findConstructor (env, xdmValueClass, "(Ljava/lang/String;Ljava/lang/String;)V");
		if(!MID_init) {
			std::cerr<<"methodID not found"<<std::endl;
		}
 		jobject xdmValue = (jobject)(env->NewObject(xdmValueClass, MID_init, env->NewStringUTF(type.c_str()), env->NewStringUTF(valueStr.c_str())));
		
	
      		if (xdmValue==NULL) {
			proc->checkForException(env, xdmValueClass, xdmValue);
	        	std::cerr<<"Error: failed to allocate an XdmValueForCpp object \n"<<std::endl;
        		return NULL;
      		}
		return xdmValue;
	}


	jobject makeXdmValue(saxon::SaxonProcessor *proc, JNIEnv *env, std::string valueStr){ 
	 if(env == NULL) {
		std::cerr<<"Error: env is null\n"<<std::endl;
	 }
		jclass xdmValueClass = proc->lookForClass(env, "net/sf/saxon/option/cpp/XdmValueForCpp");
	        jmethodID MID_init = proc->findConstructor (env, xdmValueClass, "(Ljava/lang/String;Ljava/lang/String;)V");
 		jobject xdmValue = (jobject)(env->NewObject(xdmValueClass, MID_init, env->NewStringUTF("std::string"), env->NewStringUTF(valueStr.c_str())));
		proc->checkForException(env, xdmValueClass, xdmValue);
	
      		if (xdmValue==NULL) {
	        	std::cerr<<"Error: failed to allocate an XdmValueForCpp object \n"<<std::endl;
        		return NULL;
      		}
		return xdmValue;
	}


namespace saxon {

    const char * XdmValue::getErrorMessage(int i){
	if(exception== NULL) return NULL;
	return exception->getErrorMessage(i);
    }

    const char * XdmValue::getErrorCode(int i) {
	if(exception== NULL) return NULL;
	return exception->getErrorCode(i);
     }

	int XdmValue::exceptionCount(){
		return exception->count();
	}

	//TODO : this is broken, need to save jobject created in xdmValue
	const char * XdmValue::getStringValue(SaxonProcessor * proc){
		if(processor != NULL && proc == NULL) {
			proc= processor;		
		}
		switch(valueType) {
			case 'I' :
				return ""+valueInt;
			case 'B' :
				return (valueBool ? "true" : "false");
			case 'S' :
				return valueStr.c_str();
			case 'U' :
				return valueStr.c_str();
			case 'O' :{
				 jmethodID mID;

			          std::string methodName = "getStringValue";
			          std::string args = "()Ljava/lang/String;";
		 		jclass xdmValueClass = proc->lookForClass(proc->env, "net/sf/saxon/option/cpp/XdmValueForCpp");
				  mID = (jmethodID)(proc->env)->GetMethodID(xdmValueClass, methodName.c_str(), args.c_str());
			          if (!mID) {
				    std::cout<<"\nError: MyClassInDll "<<methodName<<"()"<<" not found"<<std::endl;
			            return std::string("ERROR: Method Not Found: "+methodName).c_str();
         			}
				   jstring valueStr1 = (jstring)(proc->env)->CallObjectMethod(xdmValuei, mID);
				   if(valueStr1){
				  	const char * str = proc->env->GetStringUTFChars(valueStr1, NULL);
	       				//return "result should be ok";            
					return str;
	   			  }
				return NULL;}
			default :
				return "XdmValue type unknown or NULL";
		}
	}

	jobject XdmValue::getUnderlyingValue(SaxonProcessor *p){
		switch(valueType) {
			case 'I' :
				return makeXdmValue(p, p->env, valueInt);
			case 'B' :
				return makeXdmValue(p, p->env, valueBool);				
			case 'S' :
				return makeXdmValue(p, p->env, valueStr);
			case 'U' :
				return makeXdmValue(p, p->env, typeStr, valueStr);
			case 'O' :
				return xdmValuei;
			default :
				//cerr<<"XdmValue type unknown"<<endl;
				return makeXdmValue(p, p->env);
		


		}
	}

	void XdmValue::releaseXdmValue(SaxonProcessor *proc){
		/*if(processor != NULL && proc == NULL) {
			processor->env->DeleteLocalRef(xdmValuei);		
		}
		if(xdmValuei != NULL && proc != NULL) {
			proc->env->DeleteLocalRef(xdmValuei);
		}*/
		int len = valueStr.length();
		if(len>0) {
			valueStr.erase(0, len);
		}
	
	}
}
