# saxon-node

An exploration of binding Saxon/C http://www.saxonica.com/html/saxon-c/index.html (XSLT 2.0 and XQuery 1.0).  

Note: release v0.1.1 is built with nodejs v4.2.x [v4.2.x has Buffer acting like Uint8Array and currently is indistinguishable on the native side yet seems to work for this project]. If you want v0.12.x compatibility stay with v0.0.5. npm will continue with
nodejs v4.2.x line and any fixes or features needed by prior versions will be from github branches.

Documentation: http://rimmartin.github.io/saxon-node/

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

To run it needs the harmony switch and at least nodejs v4.2.x. Make sure there isn't a java path to jvm in front of the Excelsior JET tool in rt folder:

```bash
export LD_LIBRARY_PATH=$SAXON_HOME:$SAXON_HOME/rt/lib/amd64/jetvm:$SAXON_HOME/rt/lib/amd64:$LD_LIBRARY_PATH
node --harmony saxon-node.js /home/user/testing-grounds/BCL/analyze.xml /home/user/NetBeansProjects/OOBackbone/stylesheets/divconIsSpecies.xsl
```
Yet this isn't the purpose to run xslt as this small app.  The intention is the calling of the API from your applications.

####To test
```bash
export LD_LIBRARY_PATH=$SAXON_HOME:$SAXON_HOME/rt/lib/amd64/jetvm:$SAXON_HOME/rt/lib/amd64:$LD_LIBRARY_PATH
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
