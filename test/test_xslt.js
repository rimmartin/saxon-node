var fs = require('co-fs');
var saxon = require('saxonXslt');

  describe("Xslt foo", function() {
    var content;
    var saxonProcessor;

    before(function*() {
//      yield setup();
        content = yield fs.readFile("./test/examples/xml/foo.xml", "utf8");
        saxonProcessor = new saxon.SaxonProcessor(false);
    });

    it("should be bar", function*() {
        try
        {
            var xsltProcessor = saxonProcessor.newTransformer();
            xsltProcessor.compile("./test/examples/xsl/baz.xsl");
            xsltProcessor.parseXmlString(content);
            var pdbContent = xsltProcessor.xsltApplyStylesheet();
//            console.dir(pdbContent);
            pdbContent.should.equal("<?xml version=\"1.0\" encoding=\"UTF-8\"?><out><?xml-stylesheet type=\"text/xsl\" href=\"../xsl/foo.xsl\" title=\"default-stylesheet\"?><foo:document xmlns:foo=\"http://apache.org/foo\" xmlns:bar=\"http://apache.org/bar\" file-name=\"test\" file-path=\"work\" creation-date=\"971255692078\">\n<bar:element>MyBar</bar:element>\n</foo:document></out>");
        }
        catch (err) {
        console.dir(err.message);
        }
    });

//    it("should be bar2", function*() {
//        try
//        {
//            var xsltProcessor = saxonProcessor.newTransformer();
//            xsltProcessor.compile("./test/examples/xsl/foo2.xsl");
//            xsltProcessor.parseXmlString(content);
//            var pdbContent = xsltProcessor.xsltApplyStylesheet();
//            console.dir(pdbContent);
//        }
//        catch (err) {
//        console.dir(err.message);
//        }
//    });
//
//    it("should be bar3", function*() {
//        try
//        {
//            var xsltProcessor = saxonProcessor.newTransformer();
//            xsltProcessor.compile("./test/examples/xsl/foo3.xsl");
//            xsltProcessor.parseXmlString(content);
//            var pdbContent = xsltProcessor.xsltApplyStylesheet();
//            console.dir(pdbContent);
//        }
//        catch (err) {
//        console.dir(err.message);
//        }
//    });

    after(function*() {
//      yield teardown();
    });
  });