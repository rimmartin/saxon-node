---
layout: page
title: "XQueryProcessor"
category: ref
date: 2015-08-08 13:38:41
---


```javascript
var saxon = require('saxonXslt');
```

saxon.XQueryProcessor.prototype.**setContextItemFromFile**(filename);
> Loads  context item for subsequent queries. 
>
> *  filename &rarr; the path to the context item document
> *  return &larr; void

saxon.XQueryProcessor.prototype.**executeQueryToString**(xmlFilePath, query);
> Loads  executes a query. 
>
> *  xmlFilePath &rarr; the path to the xml document
> *  query &rarr; the query in  string
> *  return &larr; a node::Buffer with the results

