# saxon-node

An exploration of binding Saxon/C http://www.saxonica.com/html/saxon-c/index.html (XSLT 2.0 and XQuery 1.0).  

Note: Compatible with nodejs v0.12.x
Note: 'xsltApplyStylesheet' and 'executeQueryToString' now return a node::Buffer (http://nodejs.org/docs/v0.12.0/api/buffer.html) with the results. toString() is available.

To tell it where the Saxon/C is set the environment variable SAXON_HOME to path:

```bash
export SAXON_HOME=/home/user/Software/Saxonica/Saxon-HEC0.3.1
```

####Prebuilts

 linux-x64,linux-ia32, darwin-x64 and win32-ia32.

```bash
npm install --fallback-to-build
```
will first try to find a compatible native prebuilt.  If it works you won't need development tools and compilers.

####Building (only if needed; contact me if there is a particular prebuild you would use)
If a compatible prebuilt is not found, a number of environment variables are needed.
For the build phase, as with integrating Saxon/C interface code in c/c++ applications the jni.h is needed.  Set JAVA_HOME and the binding.gyp locates the jni.h from there. Only the headers are used; libsaxon that comes wth Saxon/C is laoded from it's home folder.
The libsaxon.so seems to know where $SAXON_HOME/rt is during runtime.  rt is the runtime http://www.excelsiorjet.com/ that Saxon/C provides.

To run it needs the harmony switch and at least nodejs v0.11.x http://blog.nodejs.org/2014/09/24/node-v0-11-14-unstable/

```bash
export LD_LIBRARY_PATH=$SAXON_HOME:$LD_LIBRARY_PATH
node --harmony saxon-node.js /home/user/testing-grounds/BCL/analyze.xml /home/user/NetBeansProjects/OOBackbone/stylesheets/divconIsSpecies.xsl
```
Yet this isn't the purpose to run xslt as this small app.  The intention is the calling of the API from your applications.

####To test
```bash
export LD_LIBRARY_PATH=$SAXON_HOME:$LD_LIBRARY_PATH
mocha --harmony --require should
```

####To code for xslt
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
    var xsltProcessor = saxonProcessor.newTransformer();
    var xslt = yield fs.readFile("./test/examples/xml/baz.xsl", "utf8");
    xsltProcessor.compileString(xslt);
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

####To code for xquery
```node
    var xqueryProcessor = saxonProcessor.newXQueryProcessor();
    var query = yield fs.readFile("./test/examples/query/books-to-html.xq", "utf8");
    var htmlContent = xqueryProcessor.executeQueryToString("./test/examples/query/books.xml", query);
```
