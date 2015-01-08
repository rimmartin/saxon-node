////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Copyright (c) 2013 Saxonica Limited.
// This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0.
// If a copy of the MPL was not distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
// This Source Code Form is "Incompatible With Secondary Licenses", as defined by the Mozilla Public License, v. 2.0.
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef SAXON_XQUERY_H
#define SAXON_XQUERY_H



#include "SaxonProcessor.h"
#include "XdmValue.h"
#include <string>


/*! An <code>XsltProcessor</code> represents factory to compile, load and execute stylesheet.
 * IT is possible to cache the context and the stylesheet in the <code>XsltProcessor</code>.
 * <p/>
 */
class XQueryProcessor {
public:

    //! A constructor.
    /*!
      license flag not required in Saxon-HE product
      cwd - set the current working directory
    */
    XQueryProcessor(SaxonProcessor *p, bool license=false, string cwd="");

    ~XQueryProcessor(){}

    /**
     * Set the source document for the query
    */
    void setSourceValue(XdmValue * value);

    /**
     * Set the output file where the result is sent
    */
    void setOutputfile(const char* outfile);

    /**
     * Set the source from file for the query.
    */
    void setSourceFile(const char * filename);

    /**
     * Set a parameter value used in the query
     *s
     * @param name  of the parameter, as a string. For namespaced parameter use the JAXP solution i.e. "{uri}name"
     * @param value of the query parameter, or null to clear a previously set value
     */
    void setParameter(const char * name, XdmValue*value);


    /**
     * Remove a parameter (name, value) pair
     *
     * @param namespacei currently not used
     * @param name  of the parameter
     * @return bool - outcome of the romoval
     */
    bool removeParameter(const char * name);
    /**
     * Set a property.
     *
     * @param name of the property
     * @param value of the property
     */
    void setProperty(const char * name, const char * value);

    /**
     * Clear parameter values set
     */
    void clearParameters();

    /**
     * Clear property values set
     */
    void clearProperties();


    /**
     * Perform the Query. The result is is saved to file
     *
     * @param infilename - The file name of the source document
     * @param ofilename - The file name of where result will be stored
     * @param query - The query as string representation
     */
    void executeQueryToFile(const char * infilename, const char * ofilename, const char * query);

    /**
     * Perform the Query to a XdmValue representation.
     *
     * @param infilename - The file name of the source document
     * @param ofilename - The file name of where result will be stored
     * @param query - The query as string representation
     * @return XdmValue - result of the the query as a XdmValue 
     */
    XdmValue * executeQueryToValue(const char * infilename, const char * query);

    /**
     * Perform the Query to a string representation.
     *
     * @param infilename - The file name of the source document
     * @param query - The query as string representation
     * @return char array - result of as a string
     */
    const char * executeQueryToString(const char * infilename, const char * query);

    void setQueryFile(const char* filename);

    void setBaseURI(const char * baseURI);

    SaxonApiException* checkException();

    /**
     * Checks for pending exceptions without creating a local reference to the exception object
     * @return bool - true when there is a pending exception; otherwise return false
    */
    bool exceptionOccurred();

    void exceptionClear();
    int exceptionCount();
    const char * getErrorMessage(int i);
    const char * getErrorCode(int i);
    

private:
	SaxonProcessor * proc;
	jclass  cppClass;
	jobject cpp;
	string outputfile1; /*!< output file where result will be saved */
	bool queryFileExists;
	string failure; //for testing

};

#endif /* SAXON_XQUERY_H */
