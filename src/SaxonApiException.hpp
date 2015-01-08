#pragma once

#include <string>
#include <vector>

namespace saxon {

//std::mutex mtx;
/*! <code>MyException</code>. This struct captures details of the Java exception thrown from Saxon s9api API (Java).
 * <p/>
 */
typedef struct {
		std::string errorCode;
		std::string errorMessage;
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
			newEx.errorCode =   std::string(ec);
		} else {
			newEx.errorCode ="Unknown";	
		}
		if(exM != NULL){
			newEx.errorMessage =  std::string(exM);
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
			newEx.errorCode =   std::string(ec);
		} else {
			newEx.errorCode ="ERROR1";	
		}
		if(exM != NULL){
			newEx.errorMessage =  std::string(exM);
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
			newEx.errorCode =   std::string(ec);
		} else {
			newEx.errorCode ="ERROR1";	
		}
		if(exM != NULL){
			newEx.errorMessage =  std::string(exM);
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

	unsigned int count(){
		return exceptions.size();	
	}

    /**
     * Returns the detail message std::string of the ith throwable, if there is one
     * @param i - ith exception in the vector
     * @return the detail message std::string of this <tt>Throwable</tt> instance
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
	std::vector<MyException> exceptions; /*!< Capture exceptions in a std:vector */
};
}
