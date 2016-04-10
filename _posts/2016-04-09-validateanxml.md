---
layout: page
title: "Valdate an Xml"
category: tut
date: 2016-04-09 22:21:12
---

~~~ javascript
 var saxon = require('saxonXslt');
~~~

To validate you need the PEC version of SAxon/C.

~~~ javascript
    try{
        var schemaValidator = saxonProcessor.newSchemaValidator();
        schemaValidator.registerSchemaFromFile("./test/examples/xsd/cml/schema.xsd");
        
        //important to set true to make the getValidationReport work.
        schemaValidator.setProperty("report-node", "true");
        schemaValidator.validate("./test/examples/xml/sodium-icosanoate.xml");
        var vp=schemaValidator.getValidationReport();
        saxonProcessor.release();
    }
    catch (err) {
    console.dir(err.message);
    }
~~~

The var vp is a [XdmNode]({{ site.baseurl }}/ref/xdmnode.html) object 


