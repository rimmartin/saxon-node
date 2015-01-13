# saxon-node

An exploration of binding Saxon/C http://www.saxonica.com/html/saxon-c/index.html

To tell it where the Saxon/C is set the environment variable SAXON_HOME to path:

```bash
export SAXON_HOME=/home/user/Software/Saxonica/Saxon-HEC0.3.1
```
For the build phase, as with integrating Saxon/C interface code the jni.h is needed.  Set JAVA_HOME and the binding.gyp locates the jni.h from there.

To run it needs the harmony switch and at least nodejs v0.11.x http://blog.nodejs.org/2014/09/24/node-v0-11-14-unstable/

```bash
node --harmony saxon-node.js /home/user/testing-grounds/BCL/analyze.xml /home/user/NetBeansProjects/OOBackbone/stylesheets/divconIsSpecies.xsl
```

To test
```bash
mocha --harmony --require should
```

To code for xslt
```node
    var saxonProcessor = new saxon.SaxonProcessor(false);
    var xsltProcessor = saxonProcessor.newTransformer();
    var results = xsltProcessor.xsltApplyStylesheet("./test/examples/xml/foo.xml", "./test/examples/xsl/baz.xsl");
```

```node
    var saxonProcessor = new saxon.SaxonProcessor(false);
    var xsltProcessor = saxonProcessor.newTransformer();
    xsltProcessor.compile("./test/examples/xsl/baz.xsl");
    var results = xsltProcessor.xsltApplyStylesheet("./test/examples/xml/foo.xml");
```

```node
    var saxonProcessor = new saxon.SaxonProcessor(false);
    var xsltProcessor = saxonProcessor.newTransformer();
    xsltProcessor.compile("./test/examples/xsl/baz.xsl");
    xsltProcessor.parseXmlString(content);
    var results = xsltProcessor.xsltApplyStylesheet();
```

Parameters can be passed to the xsl by putting value pairs on the parameters object of the XsltProcessor

```node
    var xsltProcessor = saxonProcessor.newTransformer();
    xsltProcessor.parameters[ "elements-of-interest" ]="Na, O, C, H";
```

To code for xquery
```node
    var xqueryProcessor = saxonProcessor.newXQueryProcessor();
    var query = yield fs.readFile("./test/examples/query/books-to-html.xq", "utf8");
    var htmlContent = xqueryProcessor.executeQueryToString("./test/examples/query/books.xml", query);
```
