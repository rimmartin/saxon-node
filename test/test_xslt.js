var fs = require('co-fs');
var saxon = require('saxonXslt');

  describe("Xslt foo", function() {
    var content;
    var saxonProcessor;

    before(function*() {
//      yield setup();
        content = yield fs.readFile("./test/examples/xml/foo.xml", "utf8");
        saxonProcessor = new saxon.SaxonProcessor(true);
        console.dir("saxonProcessor "+saxonProcessor.version());
        saxonProcessor.setcwd(".");
    });

    it("should be from memory buffer", function*() {
        try
        {
            var xsltProcessor = saxonProcessor.newTransformer();
            xsltProcessor.compileFromFile("./test/examples/xsl/baz.xsl");
//            xsltProcessor.parseXmlString(content);
//            var pdbContent = xsltProcessor.xsltApplyStylesheet();
//            pdbContent.should.equal("<?xml version=\"1.0\" encoding=\"UTF-8\"?><out><?xml-stylesheet type=\"text/xsl\" href=\"../xsl/foo.xsl\" title=\"default-stylesheet\"?><foo:document xmlns:foo=\"http://apache.org/foo\" xmlns:bar=\"http://apache.org/bar\" file-name=\"test\" file-path=\"work\" creation-date=\"971255692078\">\n<bar:element>MyBar</bar:element>\n</foo:document></out>");
        }
        catch (err) {
        console.dir(err.message);
        }
    });

    it("should use direct xml file", function*() {
        try
        {
            var xsltProcessor = saxonProcessor.newTransformer();
            xsltProcessor.compileFromFile("./test/examples/xsl/baz.xsl");
            var pdbContent = xsltProcessor.transformFileToString("./test/examples/xml/foo.xml");
            pdbContent.toString().should.equal("<?xml version=\"1.0\" encoding=\"UTF-8\"?><out><?xml-stylesheet type=\"text/xsl\" href=\"../xsl/foo.xsl\" title=\"default-stylesheet\"?><foo:document xmlns:foo=\"http://apache.org/foo\" xmlns:bar=\"http://apache.org/bar\" file-name=\"test\" file-path=\"work\" creation-date=\"971255692078\">\n<bar:element>MyBar</bar:element>\n</foo:document></out>");
        }
        catch (err) {
        console.dir(err.message);
        }
    });

    it("should use direct xml file and an in memory xslt", function*() {
        try
        {
            var xsltProcessor = saxonProcessor.newTransformer();
            var xslt = yield fs.readFile("./test/examples/xsl/baz.xsl", "utf8");
            xsltProcessor.compileFromString(xslt);
            var pdbContent = xsltProcessor.transformFileToString("./test/examples/xml/foo.xml");
            pdbContent.toString().should.equal("<?xml version=\"1.0\" encoding=\"UTF-8\"?><out><?xml-stylesheet type=\"text/xsl\" href=\"../xsl/foo.xsl\" title=\"default-stylesheet\"?><foo:document xmlns:foo=\"http://apache.org/foo\" xmlns:bar=\"http://apache.org/bar\" file-name=\"test\" file-path=\"work\" creation-date=\"971255692078\">\n<bar:element>MyBar</bar:element>\n</foo:document></out>");
        }
        catch (err) {
        console.dir(err.message);
        }
    });

    it("should use source from xml file and in memory xslt to string", function*() {
        try
        {
            var xsltProcessor = saxonProcessor.newTransformer();
            xsltProcessor.setSourceFromFile("./test/examples/xml/foo.xml");
            var xslt = yield fs.readFile("./test/examples/xsl/baz.xsl", "utf8");
            xsltProcessor.compileFromString(xslt);
            var pdbContent = xsltProcessor.transformToString();
            pdbContent.toString().should.equal("<?xml version=\"1.0\" encoding=\"UTF-8\"?><out><?xml-stylesheet type=\"text/xsl\" href=\"../xsl/foo.xsl\" title=\"default-stylesheet\"?><foo:document xmlns:foo=\"http://apache.org/foo\" xmlns:bar=\"http://apache.org/bar\" file-name=\"test\" file-path=\"work\" creation-date=\"971255692078\">\n<bar:element>MyBar</bar:element>\n</foo:document></out>");
        }
        catch (err) {
        console.dir(err.message);
        }
    });

    it("should use source from xml file and in memory xslt to value", function*() {
        try
        {
            var xsltProcessor = saxonProcessor.newTransformer();
            xsltProcessor.setSourceFromFile("./test/examples/xml/foo.xml");
            var xslt = yield fs.readFile("./test/examples/xsl/baz.xsl", "utf8");
            xsltProcessor.compileFromString(xslt);
            var pdbContent = xsltProcessor.transformToValue();
            pdbContent.size().should.equal(1);
            var pdbItem=pdbContent.getHead();
            pdbItem.size().should.equal(1);
            //console.dir(pdbItem.getStringValue());
        }
        catch (err) {
        console.dir(err.message);
        }
    });

    it("should use direct xml and xsl files", function*() {
        try
        {
            var xsltProcessor = saxonProcessor.newTransformer();
            var pdbContent = xsltProcessor.transformFileToString("./test/examples/xml/foo.xml", "./test/examples/xsl/baz.xsl");
//            pdbContent.should.equal("<?xml version=\"1.0\" encoding=\"UTF-8\"?><out><?xml-stylesheet type=\"text/xsl\" href=\"../xsl/foo.xsl\" title=\"default-stylesheet\"?><foo:document xmlns:foo=\"http://apache.org/foo\" xmlns:bar=\"http://apache.org/bar\" file-name=\"test\" file-path=\"work\" creation-date=\"971255692078\">\n<bar:element>MyBar</bar:element>\n</foo:document></out>");
        }
        catch (err) {
        console.dir(err.message);
        }
    });

    it("should be compiled and applied to file multiple times", function*() {
        try
        {
            var xsltProcessor = saxonProcessor.newTransformer();
//            xsltProcessor.compile("./test/examples/xsl/baz.xsl");
            for(var i=0;i<10;i++)
            {
                var pdbContent = xsltProcessor.transformFileToString("./test/examples/xml/foo.xml", "./test/examples/xsl/baz.xsl");
                pdbContent.toString().should.equal("<?xml version=\"1.0\" encoding=\"UTF-8\"?><out><?xml-stylesheet type=\"text/xsl\" href=\"../xsl/foo.xsl\" title=\"default-stylesheet\"?><foo:document xmlns:foo=\"http://apache.org/foo\" xmlns:bar=\"http://apache.org/bar\" file-name=\"test\" file-path=\"work\" creation-date=\"971255692078\">\n<bar:element>MyBar</bar:element>\n</foo:document></out>");
            }
        }
        catch (err) {
        console.dir(err.message);
        }
    });

    it("should set xslt parameter to check if al elements are in the list", function*() {
        try
        {
            var xsltProcessor = saxonProcessor.newTransformer();
            xsltProcessor.parameters[ "elements-of-interest" ]="C,H";
            var pdbContent = xsltProcessor.transformFileToString("./test/examples/xml/sodium-icosanoate.xml", "./test/examples/xsl/IsSpecies.xsl");
            pdbContent.toString().should.equal("false");
        }
        catch (err) {
        console.dir(err.message);
        }
    });

    it("should set xslt parameter elements-of-interests to all the elements in the molecule", function*() {
        try
        {
            var xsltProcessor = saxonProcessor.newTransformer();
            xsltProcessor.parameters[ "elements-of-interest" ]="Na, O, C, H";
            var pdbContent = xsltProcessor.transformFileToString("./test/examples/xml/sodium-icosanoate.xml", "./test/examples/xsl/IsSpecies.xsl");
            pdbContent.toString().should.equal("true");
            console.dir(pdbContent.toString());
        }
        catch (err) {
        console.dir(err.message);
        }
    });

    it("should throw exception for bad function", function*() {
        try
        {
            var xsltProcessor = saxonProcessor.newTransformer();
            console.dir('compile...');
            xsltProcessor.compileFromFile("./test/examples/xsl/badbaz.xsl").should.throw();
            console.dir("shouldn't see this");
//            xsltProcessor.parseXmlString(content);
//            var pdbContent = xsltProcessor.xsltApplyStylesheet();
//            pdbContent.should.equal("<?xml version=\"1.0\" encoding=\"UTF-8\"?><out><?xml-stylesheet type=\"text/xsl\" href=\"../xsl/foo.xsl\" title=\"default-stylesheet\"?><foo:document xmlns:foo=\"http://apache.org/foo\" xmlns:bar=\"http://apache.org/bar\" file-name=\"test\" file-path=\"work\" creation-date=\"971255692078\">\n<bar:element>MyBar</bar:element>\n</foo:document></out>");
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