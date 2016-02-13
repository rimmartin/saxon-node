---
layout: page
title: "Perform  A Transform"
category: tut
date: 2015-11-25 21:27:01
---

```javascript
var saxon = require('saxonXslt');
```

For a single transform or if the stylesheet is changing

```javascript
try{
    var saxonProcessor = new saxon.SaxonProcessor(false);
    var xsltProcessor = saxonProcessor.newTransformer();
    var results = xsltProcessor.transformFileToString("./test/examples/xml/foo.xml", "./test/examples/xsl/baz.xsl");
    console.dir(results.toString());
}
catch (err) {
console.dir(err.message);
}
```

The stylesheet can be compiled from its file path before applying to an xml document

```javascript
try{
    var saxonProcessor = new saxon.SaxonProcessor(false);
    var xsltProcessor = saxonProcessor.newTransformer();
    xsltProcessor.compileFromFile("./test/examples/xsl/baz.xsl");
    var results = xsltProcessor.transformFileToString("./test/examples/xml/foo.xml");
    console.dir(results.toString());
}
catch (err) {
console.dir(err.message);
}
```

or if the styesheet is hauled into memory first

```javascript
try{
    var xsltProcessor = saxonProcessor.newTransformer();
    var xslt = yield fs.readFile("./test/examples/xml/baz.xsl", "utf8");
    xsltProcessor.compileFromString(xslt);
    var results = xsltProcessor.transformFileToString("./test/examples/xml/foo.xml");
    console.dir(results.toString());
}
catch (err) {
console.dir(err.message);
}
```

```javascript
try{
    var saxonProcessor = new saxon.SaxonProcessor(false);
    var xsltProcessor = saxonProcessor.newTransformer();
    var xslt = yield fs.readFile("./test/examples/xml/baz.xsl", "utf8");
    xsltProcessor.compileFromString(xslt);
    xsltProcessor.parseXmlString(content);
    var results = xsltProcessor.transformToString();
    console.dir(results.toString());
}
catch (err) {
console.dir(err.message);
}
```


