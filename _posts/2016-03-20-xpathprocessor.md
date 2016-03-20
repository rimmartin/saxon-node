---
layout: page
title: "XPathProcessor"
category: ref
date: 2016-03-20 14:36:19
---


~~~ javascript
 var saxon = require('saxonXslt');
~~~

saxon.XPathProcessor.prototype.**evaluate**(xPath);

> Evaluates the xpath. 
>
> *  xPath &rarr; the xpath
> *  return &larr; XdmValue

saxon.XPathProcessor.prototype.**evaluateSingle**(xPath);

> Evaluates the xpath. 
>
> *  xPath &rarr; the xpath
> *  return &larr; XdmValue

saxon.XPathProcessor.prototype.**setContextFile**(xmlFilePath);

> Loads  xml for subsequent xpath evaluations. 
>
> *  xmlFilePath &rarr; the path to the xml document
> *  return &larr; void

saxon.XPathProcessor.prototype.**declareNamespace**(prefix, uri);

> Loads  xml for subsequent xpath evaluations. 
>
> *  prefix &rarr; the namespace prefix
> *  prefix &rarr; the namespace uri
> *  return &larr; void

