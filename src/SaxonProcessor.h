////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2014 Saxonica Limited.
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
// If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
// This Source Code Form is "Incompatible With Secondary Licenses", as defined by the Mozilla Public License, v. 2.0.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef SAXON_PROCESSOR_H
#define SAXON_PROCESSOR_H
#include <jni.h>

	
#ifdef __linux__
#include <stdlib.h>
        #include <string.h>
        #include <dlfcn.h>
    
        #define HANDLE void*
        #define LoadLibrary(x) dlopen(x, RTLD_LAZY)
        #define GetProcAddress(x,y) dlsym(x,y)
#else
    #include <windows.h>
#endif


extern "C" char dllname[];

#include <string>
#include <iostream>
#include <sstream>  
#include <map>	
#include <vector>
//#include <thread>         // std::thread
//#include <mutex>          // std::mutex, std::lock_guard
#include <stdexcept>      // std::logic_error

#include "XdmValue.h"
class XsltProcessor;
class XQueryProcessor;


using namespace std;
// The Saxon XSLT interface class

//std::mutex mtx;
/*! <code>MyException</code>. This struct captures details of the Java exception thrown from Saxon s9api API (Java).
 * <p/>
 */
typedef struct {
		string errorCode;
		string errorMessage;
		int linenumber;
	    	bool isType;
	    	bool isStatic;
	    	bool isGlobal;
	}MyException;




/*! <code>SaxonApiException</code>. An exception thrown by the Saxon s9api API (Java). This is always a C++ wrapper for some other underlying exception in Java
 * <p/>
 */
class SaxonApiException {

public:

    /**
     * A default Constructor. Create a SaxonApiException
     */
     SaxonApiException(){}

    /**
     * A Copy constructor. Create a SaxonApiException
     * @param ex - The exception object to copy
     */
	SaxonApiException(const SaxonApiException &ex){
		exceptions = ex.exceptions;
	}

    /**
     * A constructor. Create a SaxonApiException
     * @param ec - The error code of the underlying exception thrown, if known
     * @param exM - The error message of the underlying exception thrown, if known
     */
	SaxonApiException(const char * ec, const char * exM){
		MyException newEx;	
		if(ec != NULL){
			newEx.errorCode =   string(ec);
		} else {
			newEx.errorCode ="Unknown";	
		}
		if(exM != NULL){
			newEx.errorMessage =  string(exM);
		} else {
			newEx.errorMessage="Unkown";		
		}
		newEx.isType = false;
	    	newEx.isStatic = false;
	    	newEx.isGlobal = false;
		newEx.linenumber = 0;
		exceptions.push_back(newEx);
	}

    /**
     * A constructor. Create a SaxonApiException
     * @param ec - The error code of the underlying exception thrown, if known
     * @param exM - The error message of the underlying exception thrown, if known
     * @param typeErr - Flag indicating if the error is a type error
     * @param stat - Flag indicating a static error
     * @param glob - Flag for if the error is global
     * @param l - Line number information of where the error occurred
     */
	SaxonApiException(const char * ec, const char * exM, bool typeErr, bool stat, bool glob, int l){
		MyException newEx;
		if(ec != NULL){
			newEx.errorCode =   string(ec);
		} else {
			newEx.errorCode ="ERROR1";	
		}
		if(exM != NULL){
			newEx.errorMessage =  string(exM);
		} else {
			newEx.errorMessage="ERROR2";		
		}
		newEx.isType = typeErr;
	    	newEx.isStatic = stat;
	    	newEx.isGlobal = glob;
		newEx.linenumber = l;
		exceptions.push_back(newEx);
	}

    /**
     * Creates a SaxonApiException and adds it to a vector of exceptions
     * @param ec - The error code of the underlying exception thrown, if known
     * @param exM - The error message of the underlying exception thrown, if known
     * @param typeErr - Flag indicating if the error is a type error
     * @param stat - Flag indicating a static error
     * @param glob - Flag for if the error is global
     * @param l - Line number information of where the error occurred
     */
	void add(const char * ec, const char * exM, bool typeErr, bool stat, bool glob, int l){
		MyException newEx;
		if(ec != NULL){
			newEx.errorCode =   string(ec);
		} else {
			newEx.errorCode ="ERROR1";	
		}
		if(exM != NULL){
			newEx.errorMessage =  string(exM);
		} else {
			newEx.errorMessage="ERROR2";		
		}
		newEx.isType = typeErr;
	    	newEx.isStatic = stat;
	    	newEx.isGlobal = glob;
		newEx.linenumber = l;
		exceptions.push_back(newEx);
	}


    /**
     * A destructor.
     */
	~SaxonApiException(){ 
	  exceptions.clear();
	}

    /**
     * Get the error code associated with the ith exception in the vector, if there is one
     * @param i - ith exception in the vector
     * @return the associated error code, or null if no error code is available
     */
	const char * getErrorCode(unsigned int i){
		if(i <= exceptions.size()){
			return exceptions[i].errorCode.c_str();
		}
		return NULL;
	}


	int getLineNumber(unsigned int i){
		if(i <= exceptions.size()){
			return exceptions[i].linenumber;	
		}
		return 0;
	}

	bool isGlobalError(unsigned int i){
		if(i <= exceptions.size()){
			return exceptions[i].isGlobal;
		}
		return false;
	}

	bool isStaticError(unsigned int i){
		if(i <= exceptions.size()){
			return exceptions[i].isStatic;
		}
		return false;
	}

	bool isTypeError(unsigned int i){
		if(i <= exceptions.size()){
			return exceptions[i].isType;
		}
		return NULL;
	}

	void clear(){
	  for(unsigned int i =0; i< exceptions.size();i++) {
		exceptions[i].errorCode.clear();
		exceptions[i].errorMessage.clear();	
	  }
	  exceptions.clear();
	}

	int count(){
		return exceptions.size();	
	}

    /**
     * Returns the detail message string of the ith throwable, if there is one
     * @param i - ith exception in the vector
     * @return the detail message string of this <tt>Throwable</tt> instance
     *         (which may be <tt>null</tt>).
     */
	const char * getErrorMessage(unsigned int i){
		if(i <= exceptions.size()){
			return exceptions[i].errorMessage.c_str();
		}
		return NULL;
	}

    /**
     * Returns the ith Exception added, if there is one
     * @param i - ith exception in the vector
     * @return MyException
     */
	MyException getException(unsigned int i){
		if(i <= exceptions.size()){
			return exceptions[i];	
		}
		throw 0;
	}

private:
	vector<MyException> exceptions; /*!< Capture exceptions in a std:vector */
};










//==========================================



/*! An <code>SaxonProcessor</code> acts as a factory for generating XQuery, XPath, Schema and XSLT compilers
 * In this alpha release only the XSLT compiler is available
 * <p/>
 */
class SaxonProcessor {
friend  class XsltProcessor;
friend  class XQueryProcessor;
friend class XdmValue;
public:

   //! A default constructor.
    /*!
      * Create Saxon Processor.
    */

    SaxonProcessor();


   //! A constructor.
    /*!
      * Create Saxon Processor.
      * @param l - Flag that a license is to be used. Default is false.	
    */
    SaxonProcessor(bool l);

    SaxonProcessor& operator=( const SaxonProcessor& other );

    ~SaxonProcessor(){
    }
	
    void createJVM();
	
    XsltProcessor * newTransformer();

    XQueryProcessor * newXQueryProcessor();

    /**
     * Parse a lexical representation of the source document and return it as an XdmValue
    */
    XdmValue * parseString(const char* source);

    /**
     * Parse a source document file and return it as an XdmValue.
    */
    XdmValue * parseFile(const char* source);

    /**
     * Parse a source document available by URI and return it as an XdmValue.
    */
    XdmValue * parseURI(const char* source);

    /**
     * Set the source document in the Processor.
     * @param value - XdmValue
    */
    void setSourceValue(XdmValue * value);

    /**
     * Set the source from file i nthe Processor.
     * @param filename = const char pointer array
    */
    void setSourceFile(const char * filename);


    /**
     * Set the value of a stylesheet parameter
     *
     * @param name  the name of the stylesheet parameter, as a string. For namespaced parameter use the JAXP solution i.e. "{uri}name"
     * @param value the value of the stylesheet parameter, or null to clear a previously set value
     */
    void setParameter(const char* name, XdmValue*value);

    /**
     * Get a parameter value by name
     * @param name - Specified paramater name to get
     * @return XdmValue
    */
     XdmValue* getParameter(const char* name);


     /**
      * Get all parameters 
     */
     map<string,XdmValue*>& getParameters();

     /**
      * Get all properties 
     */
     map<string,string>& getProperties();


    /**
     * Remove a parameter (name, value) pair from a stylesheet
     *
     * @param namespacei currently not used
     * @param name  the name of the stylesheet parameter
     * @return bool - outcome of the romoval
     */
    bool removeParameter(const char* name);

    /**
     * Set a property.
     *
     * @param name of the property
     * @param value of the property
     */
    void setProperty(const char* name, const char* value);

    /**
     * Get a property value by name
     * @param name - Specified paramater name to get
     * @return string - Get string of the property as char pointer array
    */
    const char* getProperty(const char* name);

    /**
     * Clear parameter values set
     */
    void clearParameters();

    /**
     * Clear property values set
     */
    void clearProperties();

    /**
     * Count of parameters in map
     */
    int parameterSize(){return parameters.size();}	

    /**
     * Count of properties in map
     */
    int propertiesSize(){return properties.size();}

   //! Internal.
    /*!
      * Interface to JNI methods to find a Java class in Saxon.
      * @param env - JNI environment
      * @param name - Name of the class	
    */
    static jclass lookForClass (JNIEnv* env, const char* name);

   //! Internal.
    /*!
      * Interface to JNI methods to find the constructor for a Java class.
      * @param env - JNI environment
      * @param myClassInDll -  Class definition in library
      * @param arguments - Signature of the method 
    */
    static jmethodID findConstructor (JNIEnv* env, jclass myClassInDll, string arguments);

   //! Internal.
    /*!
      * interface to JNI methods to create a JNI Java class.
      * @param env - JNI environment
      * @param myClassInDll - Class definition in library
      * @param arguments - Signature of the method 
      * @param l - Presence of license file - not usage in Saxon/C-HE version
    */
    static jobject createObject (JNIEnv* env, jclass myClassInDll, string arguments, bool l);

    static jobject createObject2 (JNIEnv* env, jclass myClassInDll, string arguments, jobject obj, bool l);
 

    /**
     * Checks for pending exceptions without creating a local reference to the exception object
     * @return bool - true when there is a pending exception; otherwise return false
    */
    bool exceptionOccurred();

    /**
     * Checks for pending exceptions and creates a SaxonApiException object, which handles one or more local exceptions objects
     * @param env
     * @param callingClass
     * @param callingObject
     * @return SaxonApiException
    */
    SaxonApiException * checkForException(JNIEnv* env, jclass callingClass,  jobject callingObject);

    /**
    * close method not currently used. Available in next release
    */
    static void close();

    /**
     * set the current working directory
    */
   void setcwd(const char* cwd);


    /**
     * set saxon resources directory
    */
   void setResourcesDirectory(const char* dir);
	

    /**
     * get saxon resources directory
    */
   const char * getResourcesDirectory();

    /**
     * Get the Saxon version
     * @return char array
     */
    const char * version();


//	XPathEngine
//	XQueryEngine
//	SchemaManager


    static int jvmCreated;
    static JNIEnv *env;
    static JavaVM *jvm;
protected:

	jclass  versionClass;
	jclass  procClass;
	jclass  saxonCAPIClass;
	string cwd; /*!< current working directory */
        std::string dllName;
	string resources_dir; /*!< current Saxon resources directory */
	jobject proc; /*!< Java Processor object */
	HANDLE myDllHandle;
	std::map<string,XdmValue*> parameters; /*!< map of parameters used for the transformation as (string, value) pairs */
	std::map<string,string> properties; /*!< map of properties used for the transformation as (string, string) pairs */	 
	bool license; /*!< indicates whether the Processor requires a Saxon that needs a license file (i.e. Saxon-EE) other a Saxon-HE Processor is created  */
	bool closed;
	SaxonApiException* exception; /*!< Pointer to any potential exception thrown */

private:
};

//===============================================================================================

#endif /* SAXON_PROCESSOR_H */
