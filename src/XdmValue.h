////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2014 Saxonica Limited.
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
// If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
// This Source Code Form is "Incompatible With Secondary Licenses", as defined by the Mozilla Public License, v. 2.0.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef SAXON_XDMVALUE_H
#define SAXON_XDMVALUE_H


#include <string.h>
#include "SaxonProcessor.h"
#include <typeinfo> //used for testing only

/*! <code>XdmValue</code>. Value in the XDM data model. A value is a sequence of zero or more items,
 * each item being either an atomic value or a node. This class is a wrapper of the the XdmValue object created in Java.
 * <p/>
 */
using namespace std;
class SaxonApiException;
class SaxonProcessor;

class XdmValue {


public:
/**
     * A default Constructor. Create a empty value
     */
	XdmValue(){
		valueType='U';
	}

    /**
     * A Constructor. Create an xs:boolean value
     * @param val - boolean value
     */
	XdmValue(bool val){
		valueBool= val;
		valueType= 'B';
	} 

    /**
     * A Constructor. Create an xs:string value
     * @param val - string value
     */
	XdmValue(string val){
		valueStr = val;
		valueType= 'S';	
	}

    /**
     * A Constructor. Create a XdmValue based on the target type. Conversion is applied if possible
     * @param type - specify target type of the value  
     * @param val - Value to convert
     */
	XdmValue(string tStr, string val){
		valueStr = val;
		typeStr = tStr;
		valueType= 'U';	
	}


    /**
     * A Constructor. Create an xs:string value
     * @param val - string value
     */
	XdmValue(char * val){
		valueStr = string(val);
		valueType= 'S';
	}

    /**
     * A Constructor. Create an xs:int value
     * @param val - int value
     */
	XdmValue(int val){
		valueType= 'I';
		valueInt = val;
	} 

	//TODO XdmValue with constructor of sequence of values

    /**
     * A Constructor. Wrap an Java XdmValue object.
     * @param val - Java XdmValue object
     */
	XdmValue(jobject val){
		xdmValuei = val;
		valueType='O';
	}


	~XdmValue() {
		//proc->env->ReleaseObject
	}

	void releaseXdmValue(SaxonProcessor *proc);


    /**
     * Get Java XdmValue object.
     * @return jobject - The Java object of the XdmValue in its JNI representation
     */
	jobject getUnderlyingValue(SaxonProcessor *p);

    /**
     * Get the string representation of the XdmValue.
     * @return char array
     */
	const char * getStringValue(SaxonProcessor *p);
	
	void setProcessor(SaxonProcessor *p){processor = p;}

        const char * getErrorMessage(int i);
        const char * getErrorCode(int i);
	int exceptionCount();
	string checkFailures(){return failure;}
	SaxonProcessor *processor;
private:
	string typeStr;/*!< Internal usage.*/
	char valueType;  /*!< Internal usage. The type of the XdmValue, U Null, I Int, Z bool, S String, O jobject */
	string valueStr;  /*!< Internal usage. String representation of the XdmValue, if available */
	int valueInt;
	bool valueBool;
	jobject xdmValuei;
	SaxonApiException * exception;
	string failure;

};

#endif /** SAXON_XDMVALUE_H **/
