# saxon-node

An exploration of binding Saxon/C http://www.saxonica.com/html/saxon-c/index.html (XSLT 2.0 and XQuery 1.0).  

Note: release v0.1.1 is built with nodejs v4.2.x [v4.2.x has Buffer acting like Uint8Array and currently is indistinguishable on the native side yet seems to work for this project]. If you want v0.12.x compatibility stay with v0.0.5. npm will continue with
nodejs v4.2.x line and any fixes or features needed by prior versions will be from github branches.

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
For the build phase, as with integrating Saxon/C interface code in c/c++ applications the jni.h is needed.  Set JAVA_HOME and the binding.gyp locates the jni.h from there. Only the headers are used; libsaxon that comes wth Saxon/C is loaded from it's home folder.
The libsaxon.so depends on $SAXON_HOME/rt during runtime an it needs library paths $SAXON_HOME:$SAXON_HOME/rt/lib/amd64/jetvm:$SAXON_HOME/rt/lib/amd64.  rt is the runtime http://www.excelsiorjet.com/ that Saxon/C provides.

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

Documentation: <a href="http://rimmartin.github.io/saxon-node/">Saxon Node API</a>

