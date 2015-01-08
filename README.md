# saxon-node

An exploration of binding Saxon/C

To tell it where the Saxon/C is set the environment variable SAXON_HOME to path:

```bash
export SAXON_HOME=/home/user/Software/Saxonica/Saxon-HEC0.3.1
```
For the build phase, as with integrating Saxon/C interface code the jni.h is needed.  Set JAVA_HOME and the binding.gyp locates the jni.h from there.

To run it needs the harmony switch and at least nodejs v0.11.x

```bash
node --harmony saxon-node.js /home/user/testing-grounds/BCL/analyze.xml /home/user/NetBeansProjects/OOBackbone/stylesheets/divconIsSpecies.xsl
```

To test
```bash
mocha --harmony --require should
```
