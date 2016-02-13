---
layout: page
title: "SchemaValidator"
category: ref
date: 2016-02-12 23:17:18
---



```javascript
var saxon = require('saxonXslt');
```

saxon.SchemaValidator.prototype.**registerSchemaFromFile**(xsdFilePath);
> Loads  schema for subsequent validations. 
>
> *  xsdFilePath &rarr; the path to the schema document
> *  return &larr; void

saxon.SchemaValidator.prototype.**validate**(xmlFilePath);
> Loads  executes a query. 
>
> *  xmlFilePath &rarr; the path to the xml document
> *  return &larr; void

saxon.SchemaValidator.prototype.**getValidationReport**();
> get report. 
>
> *  return &larr; a node::Buffer with the results


