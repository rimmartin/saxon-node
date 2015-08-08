---
layout: page
title: "XsltProcessor"
category: ref
date: 2015-08-08 13:28:17
---

```javascript
var saxon = require('saxonXslt');
```
saxon.XsltProcessor.prototype.**parameters**
> An object that takes parameter name value pairs. They will get passed to the stylesheet

saxon.XsltProcessor.prototype.**<span id="xslt-compile">compile</span>**(stylesheetFilePath);
> Loads  stylesheet and precompiles for subsequent transforms. 
>
> *  stylesheetFilePath &rarr; the path to the stylesheet

saxon.XsltProcessor.prototype.**<span id="xslt-compile-string">compileString</span>**(stylesheet);
> Precompiles the string for subsequent transforms. 
>
> *  stylesheetF &rarr; stylesheet in a string

saxon.XsltProcessor.prototype.**xsltApplyStylesheet**(xmlFilePath[, stylesheetFilePath]);
> Performs a transform
>
> *  xmlFilePath &rarr; the path to the xml document
> *  stylesheetFilePath &rarr; the path to the stylesheet is optional if your stylesheet was already in the [**compile**](#xslt-compile) or [**compileString**](#xslt-compile-string) method
> *  return &larr; a node::Buffer with the results
