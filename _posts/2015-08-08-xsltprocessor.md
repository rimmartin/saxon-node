---
layout: page
title: "XsltProcessor"
category: ref
date: 2015-08-08 13:28:17
---

~~~ javascript
 var saxon = require('saxonXslt');
~~~
saxon.XsltProcessor.prototype.**parameters**

> An object that takes parameter name value pairs. They will get passed to the stylesheet

saxon.XsltProcessor.prototype.**<span id="xslt-source-from-file">setSourceFromFile</span>**(xmlFilePath);

> Loads  xml document. 
>
> *  sxmlFilePath &rarr; the path to the xml

saxon.XsltProcessor.prototype.**<span id="xslt-source-from-string">setSorceFromString</span>**(xml);

> Precompiles the string for subsequent transforms. 
>
> *  xml &rarr; xml in a string

saxon.XsltProcessor.prototype.**<span id="xslt-compile-from-file">setSourceFromFile</span>**(stylesheetFilePath);

> Loads  stylesheet and precompiles for subsequent transforms. 
>
> *  stylesheetFilePath &rarr; the path to the stylesheet

saxon.XsltProcessor.prototype.**<span id="xslt-compile-string">compileFromString</span>**(stylesheet);

> Precompiles the string for subsequent transforms. 
>
> *  stylesheet &rarr; stylesheet in a string

saxon.XsltProcessor.prototype.**transformFileToString**(xmlFilePath[, stylesheetFilePath]);

> Performs a transform
>
> *  xmlFilePath &rarr; the path to the xml document
> *  stylesheetFilePath &rarr; the path to the stylesheet is optional if your stylesheet was already in the [**compileFromFile**](#xslt-compile-from-file) or [**compileFromString**](#xslt-compile-from-string) method
> *  return &larr; a node::Buffer with the results

saxon.XsltProcessor.prototype.**transformToString**(xmlFilePath[, stylesheetFilePath]);

> Performs a transform provided the xml and stylesheet have been set and compiled
>
> *  return &larr; a node::Buffer with the results
