---
layout: page
title: "Pass in Parameters"
category: tut
date: 2015-11-25 22:06:47
---

Parameters can be passed to the xsl by putting value pairs on the parameters object of the XsltProcessor

~~~ javascript
    var xsltProcessor = saxonProcessor.newTransformer();
    xsltProcessor.parameters[ "elements-of-interest" ]="Na, O, C, H";
~~~
where elements-of-interest is a global stylesheet parameter and in this case is an array
