---
layout: page
title: "XQueryProcessor"
category: ref
date: 2015-08-08 13:38:41
---


```javascript
var saxon = require('saxonXslt');
```

saxon.XsltProcessor.prototype.**executeQueryToString**(xmlFilePath, query);
> Loads  stylesheet and precompiles for subsequent transforms. 
>
> *  xmlFilePath &rarr; the path to the xml document
> *  query &rarr; the query in  string
> *  return &larr; a node::Buffer with the results

