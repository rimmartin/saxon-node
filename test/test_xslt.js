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

    it("should be from memory buffer", function*() {
        try
        {
            saxonProcessor = new saxon.SaxonProcessor(false);
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

    it("should use direct xml file", function*() {
        try
        {
            saxonProcessor = new saxon.SaxonProcessor(false);
            var xsltProcessor = saxonProcessor.newTransformer();
            xsltProcessor.compile("./test/examples/xsl/baz.xsl");
            var pdbContent = xsltProcessor.xsltApplyStylesheet("./test/examples/xml/foo.xml");
            pdbContent.should.equal("<?xml version=\"1.0\" encoding=\"UTF-8\"?><out><?xml-stylesheet type=\"text/xsl\" href=\"../xsl/foo.xsl\" title=\"default-stylesheet\"?><foo:document xmlns:foo=\"http://apache.org/foo\" xmlns:bar=\"http://apache.org/bar\" file-name=\"test\" file-path=\"work\" creation-date=\"971255692078\">\n<bar:element>MyBar</bar:element>\n</foo:document></out>");
        }
        catch (err) {
        console.dir(err.message);
        }
    });

    it("should use direct xml and xsl files", function*() {
        try
        {
            saxonProcessor = new saxon.SaxonProcessor(false);
            var xsltProcessor = saxonProcessor.newTransformer();
            var pdbContent = xsltProcessor.xsltApplyStylesheet("./test/examples/xml/foo.xml", "./test/examples/xsl/baz.xsl");
            pdbContent.should.equal("<?xml version=\"1.0\" encoding=\"UTF-8\"?><out><?xml-stylesheet type=\"text/xsl\" href=\"../xsl/foo.xsl\" title=\"default-stylesheet\"?><foo:document xmlns:foo=\"http://apache.org/foo\" xmlns:bar=\"http://apache.org/bar\" file-name=\"test\" file-path=\"work\" creation-date=\"971255692078\">\n<bar:element>MyBar</bar:element>\n</foo:document></out>");
        }
        catch (err) {
        console.dir(err.message);
        }
    });

    after(function*() {
//      yield teardown();
    });
  });