---
layout: page
title: "SaxonProcessor"
category: ref
date: 2015-08-08 12:55:27
---

~~~ javascript
 var saxon = require('saxonXslt');
~~~

saxon.SaxonProcessor(license)

> Constructs a saxon processor. 
>
> *  license &rarr; a license license is to be used. Default is false


saxon.SaxonProcessor.prototype.**newTransformer**()

>
> * return &larr; a saxon.[XsltProcessor]({{ site.baseurl }}/ref/xsltprocessor.html)

saxon.SaxonProcessor.prototype.**newXQueryProcessor**()

>
> * return &larr; a saxon.[XQueryProcessor]({{ site.baseurl }}/ref/xqueryprocessor.html)


saxon.SaxonProcessor.prototype.**newXPathProcessor**()

>
> * return &larr; a saxon.[XPathProcessor]({{ site.baseurl }}/ref/xpathprocessor.html)

saxon.SaxonProcessor.prototype.**newSchemaValidator**()

>
> * return &larr; a saxon.[SchemaValidator]({{ site.baseurl }}/ref/schemavalidator.html)

saxon.SaxonProcessor.prototype.**makeValue**(value);

> make a value based on the primitive type or string. 
>
> *  value &rarr; can be boolean, integer, float or string
> *  return &larr; a [XdmAtomicValue]({{ site.baseurl }}/ref/xdmatomicvalue.html) representation of the value

saxon.SaxonProcessor.prototype.**makeQNameValue**(value);

> make a qname based on the Clark notation string. 
>
> *  value &rarr; a string representinga qname (e.g. "{http://www.xml-cml.org/schema}cml")
> *  return &larr; a [XdmAtomicValue]({{ site.baseurl }}/ref/xdmatomicvalue.html) representation of the qname

saxon.SaxonProcessor.prototype.**getStringValue**(item);

> get a string representation of a XdmItem. 
>
> *  item &rarr; an XdmItem
> *  return &larr; a string

saxon.SaxonProcessor.prototype.**parseXmlFromString**(xmlString);

> load xml source from string. 
>
> *  value &rarr; string of xml
> *  return &larr; a [XdmNode]({{ site.baseurl }}/ref/xdmnode.html) representation of the xml

saxon.SaxonProcessor.prototype.**parseXmlFromFile**(xmlPath);

> load xml source from file path. 
>
> *  value &rarr; location on filesystem
> *  return &larr; a [XdmNode]({{ site.baseurl }}/ref/xdmnode.html) representation of the xml

saxon.SaxonProcessor.prototype.**parseXmlFromUri**(xmlString);

> load xml source from uri. 
>
> *  value &rarr; uri location of xml
> *  return &larr; a [XdmNode]({{ site.baseurl }}/ref/xdmnode.html) representation of the xml

saxon.SaxonProcessor.prototype.**isSchemaAware**()

>
> * return &larr; true or false

saxon.SaxonProcessor.prototype.**version**()

>
> * return &larr; the version at runtime

saxon.SaxonProcessor.prototype.**release**()

> After use clean up to exit gracefully
> 

