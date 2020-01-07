declare module 'saxon-node' {
  class SaxonProcessor {
    /**
     * Constructs a saxon processor.
     * @param license a license license is to be used. Default is false
     */
    constructor(license?: boolean);
    
    newTransformer(): XsltProcessor;
    newXQueryProcessor(): XQueryProcessor;
    newXPathProcessor(): XPathProcessor;
    newSchemaValidator(): SchemaValidator;
    newXsltProcessor(): XsltProcessor;
    newXslt30Processor(): Xslt30Processor;

    /**
     * make a value based on the primitive type or string.
     * @param value can be boolean, integer, float or string
     * @returns a XdmAtomicValue representation of the value
     */
    makeValue(value: boolean | number | string): XdmAtomicValue;
    
    /**
     * make a qname based on the Clark notation string.
     * @param value a string representinga qname (e.g. "{http://www.xml-cml.org/schema}cml")
     * @returns a XdmAtomicValue representation of the qname
     */
    makeQNameValue(value: string): XdmAtomicValue;

    /**
     * get a string representation of a XdmItem.
     * @param item an XdmItem
     * @returns a string
     */
    getStringValue(item: XdmItem): string;

    /**
     * load xml source from string.
     * @param xmlString string of xml
     * @returns a XdmNode representation of the xml
     */
    parseXmlFromString(xmlString: string): XdmNode;

    /**
     * load xml source from file path.
     * @param xmlPath location on filesystem
     * @returns a XdmNode representation of the xml
     */
    parseXmlFromFile(xmlPath: string): XdmNode;

    /**
     * load xml source from uri.
     * @param xmlString uri location of xml
     * @returns a XdmNode representation of the xml
     */
    parseXmlFromUri(xmlString: string): XdmNode;

    isSchemaAware(): boolean;

    /**
     * @returns the version at runtime
     */
    version(): string;

    /**
     * After use clean up to exit gracefully
     */
    release(): void;

    setcwd(path: string): void;
  }



  class XsltProcessor {
    /**
     * An object that takes parameter name value pairs. They will get passed to the stylesheet
     */
    parameters: { [key: string]: any };

    /**
     * Loads xml document.
     * @param xmlFilePath the path to the xml
     */
    setSourceFromFile(xmlFilePath: string): void;

    /**
     * Precompiles the string for subsequent transforms.
     * @param xml xml in a string
     */
    setSourceFromString(xml: string): void;

    /**
     * Loads stylesheet and precompiles for subsequent transforms.
     * @param stylesheetFilePath the path to the stylesheet
     */
    setSourceFromFile(stylesheetFilePath: string): void;

    /**
     * Precompiles the string for subsequent transforms.
     * @param stylesheet stylesheet in a string
     */
    compileFromString(stylesheet: string): void;

    compileFromFile(stylesheetFilePath: string): void;
    
    /**
     * Performs a transform
     * @param xmlFilePath the path to the xml document
     * @param stylesheetFilePath the path to the stylesheet is optional if your stylesheet was already in the compileFromFile or compileFromString method
     * @returns a node::Buffer with the results
     */
    transformFileToString(
      xmlFilePath: string,
      stylesheetFilePath?: string
    ): Buffer;
    
    /**
     * Performs a transform provided the xml and stylesheet have been set and compiled
     */
    transformToString(): Buffer;

    transformToValue(): XdmValue;
  }

  class Xslt30Processor {
    /**
     * An object that takes parameter name value pairs. They will get passed to the stylesheet
     */
    parameters: { [key: string]: any };

    /**
     * Loads xml document.
     * @param xmlFilePath the path to the xml
     */
    setSourceFromFile(xmlFilePath: string): void;

    /**
     * Precompiles the string for subsequent transforms.
     * @param xml xml in a string
     */
    setSourceFromString(xml: string): void;

    /**
     * Loads stylesheet and precompiles for subsequent transforms.
     * @param stylesheetFilePath the path to the stylesheet
     */
    setSourceFromFile(stylesheetFilePath: string): void;

    /**
     * Precompiles the string for subsequent transforms.
     * @param stylesheet stylesheet in a string
     */
    compileFromString(stylesheet: string): void;
    
    compileFromFile(stylesheetFilePath: string): void;

    /**
     * Performs a transform
     * @param xmlFilePath the path to the xml document
     * @param stylesheetFilePath the path to the stylesheet is optional if your stylesheet was already in the compileFromFile or compileFromString method
     * @returns a node::Buffer with the results
     */
    transformFileToString(
      xmlFilePath: string,
      stylesheetFilePath?: string
    ): Buffer;
    
    /**
     * Performs a transform provided the xml and stylesheet have been set and compiled
     * @param source 
     */
    transformToString(source: XdmNode): Buffer;

    setGlobalContextFromFile(xml: string): void;
    
    transformToValue(source: XdmNode): XdmValue;
  }

  class XQueryProcessor {
    /**
     * Loads context item for subsequent queries.
     * @param filename the path to the context item document
     */
    setContextItemFromFile(filename: string): void;

    /**
     * Loads executes a query.
     * @param xmlFilePath the path to the xml document
     * @param query the query in string
     * @returns a node::Buffer with the results
     */
    executeQueryToString(xmlFilePath: string, query: string): Buffer;
  }

  class XPathProcessor {
    /**
     * Evaluates the xpath.
     * @param xPath the xpath
     */
    evaluate(xPath: string): XdmValue;

    /**
     * Evaluates the xpath.
     * @param xPath the xpath
     */
    evaluateSingle(xPath: string): XdmValue;

    /**
     * Loads xml for subsequent xpath evaluations.
     * @param xmlFilePath the path to the xml document
     */
    setContextFile(xmlFilePath: string): void;

    /**
     * Loads xml for subsequent xpath evaluations.
     * @param prefix the namespace prefix
     * @param uri the namespace uri
     */
    declareNamespace(prefix: string, uri: string): void;
  }

  class SchemaValidator {
    /**
     * Loads schema for subsequent validations.
     * @param xsdFilePath the path to the schema document
     */
    registerSchemaFromFile(xsdFilePath: string): void;


    setProperty(propertyName: string, value: string): void;
    
    /**
     * Loads executes a query.
     * @param xmlFilePath the path to the xml document
     */
    validate(xmlFilePath: string): void;

    /**
     * Loads executes a query.
     * @param xmlFilePath the path to the xml document
     */
    validateToNode(xmlFilePath: string): void;

    /**
     * get report.
     * @returns a node::Buffer with the results (Incorrect?)
     */
    getValidationReport(): XdmValue; // Buffer in docs
  }

  class XdmValue {
    /**
     * get XdmItem that is at the head.
     * @returns the head XdmItem
     */
    getHead(): XdmItem;

    /**
     * get the nth item.
     * @param index 
     * @returns he nth XdmItem
     */
    itemAt(index: number): XdmItem;

    /**
     * the number of items or children.
     */
    size(): number;
  }

  class XdmAtomicValue extends XdmItem {}

  class XdmItem extends XdmValue {
    /**
     * get representative value.
     */
    getStringValue(): string;
  }

  class XdmNode extends XdmItem {}
}
