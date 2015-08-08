---
layout: page
title: "SaxonProcessor"
category: ref
date: 2015-08-08 12:55:27
---

```javascript
var saxon = require('saxonXslt');
```

saxon.SaxonProcessor(license)
> Constructs a saxon processor. 
>
> *  license &rarr; a license license is to be used. Default is false


saxon.SaxonProcessor.prototype.**version**()
>
> * return &larr; the version at runtime

saxon.SaxonProcessor.prototype.**newTransformer**()
>
> * return &larr; a saxon.[XsltProcessor]({{ site.baseurl }}/ref/xsltprocessor.html)

saxon.SaxonProcessor.prototype.**newXQueryProcessor**()
>
> * return &larr; a saxon.[XQueryProcessor]({{ site.baseurl }}/ref/xqueryprocessor.html)


