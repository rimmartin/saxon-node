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
            saxonProcessor.setcwd(__dirname);
            var xml2 = saxonProcessor.parseXmlFromFile("./examples/xml/foo.xml");
            //xml2.size().should.equal(1);
            //console.dir("xml:\n"+xml2.getStringValue());
            //var xml3 = saxonProcessor.parseXmlFromUri("file://"+__dirname+"/examples/query/books.xml");
            //xml3.size().should.equal(1);
        }
        catch (err) {
        console.dir(err.message);
        }
    });

    it("making atomic values", function*() {
        try
        {
            var xdmAtomicValue = saxonProcessor.makeValue("2theta");
            var vp=saxonProcessor.getStringValue(xdmAtomicValue);
            vp.should.equal("2theta");
            xdmAtomicValue = saxonProcessor.makeValue(20);
            vp=saxonProcessor.getStringValue(xdmAtomicValue);
            vp.should.equal("20");
            xdmAtomicValue = saxonProcessor.makeValue(1.46);
            vp=saxonProcessor.getStringValue(xdmAtomicValue);
            vp.should.equal("1.46");
            //xdmAtomicValue = saxonProcessor.makeQNameValue("{http://www.xml-cml.org/schema}cml");
            //console.dir(xdmAtomicValue.size());
            //var vi=xdmAtomicValue.getHead();
            //console.dir(vi.size());
            //var title=vi.getHead();
            //console.dir(title.getStringValue());
            //vp=saxonProcessor.getStringValue(xdmAtomicValue);
            //vp.should.equal("pmc");
        }
        catch (err) {
        console.dir(err.message);
        }
    });

    after(function*() {
        saxonProcessor.release();
//      yield teardown();
    });
  });
