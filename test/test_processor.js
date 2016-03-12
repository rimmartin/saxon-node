var fs = require('co-fs');
var saxon = require('saxonXslt');

  describe("Saxon Processor foo", function() {
    var content;
    var saxonProcessor;

    before(function*() {
//      yield setup();
        content = yield fs.readFile("./test/examples/query/books.xml", "utf8");
        saxonProcessor = new saxon.SaxonProcessor(true);
        console.dir("saxonProcessor "+saxonProcessor.version());
        saxonProcessor.setcwd(".");
    });

    it("parse xml different ways", function*() {
        try
        {
            var xml = saxonProcessor.parseXmlFromString(content);
            //console.dir("xml:\n"+xml.getStringValue());
            xml.size().should.equal(1);
            saxonProcessor.setcwd(__dirname+"/..");
            var xml2 = saxonProcessor.parseXmlFromFile(__dirname+"/examples/xml/foo.xml");
            //xml2.size().should.equal(1);
            //console.dir("xml:\n"+xml2.getStringValue());
            //var xml3 = saxonProcessor.parseXmlFromUri("file://"+__dirname+"/test/examples/query/books.xml");
            //xml3.size().should.equal(1);
        }
        catch (err) {
        console.dir(err.message);
        }
    });

    it("string value", function*() {
        try
        {
            //var xpathProcessor = saxonProcessor.newXPathProcessor();
            //xpathProcessor.declareNamespace("cml", "http://www.xml-cml.org/schema");
            //xpathProcessor.setContextFile("./test/examples/xml/foo.xml");
            //var vp=xpathProcessor.evaluate("/document/element");
            //console.dir(vp);
        }
        catch (err) {
        console.dir(err.message);
        }
    });

    after(function*() {
//      yield teardown();
    });
  });
