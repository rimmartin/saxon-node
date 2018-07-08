var fs = require('fs');
var saxon = require('saxonXslt');

  describe("Xquery foo", function() {
    var content;
    var saxonProcessor;

    before(function(done) {
//      yield setup();
        content = fs.readFileSync("./test/examples/query/books.xml", "utf8");
        saxonProcessor = new saxon.SaxonProcessor(true);
        console.dir("saxonProcessor "+saxonProcessor.version());
        saxonProcessor.setcwd(".");
        done();
    });

    it("should be from memory buffer", function(done) {
        try
        {
            var xqueryProcessor = saxonProcessor.newXQueryProcessor();
            var query = fs.readFileSync("./test/examples/query/books-to-html.xq", "utf8");
            var htmlContent = xqueryProcessor.executeQueryToString("./test/examples/query/books.xml", query);
            htmlContent.toString().should.equal("<html>\n   <head>\n      <title>A list of books</title>\n   </head>\n   <body>\n      <h1>A list of books</h1>\n      <p>Here are some interesting books:</p>\n      <ul>\n         <li>\n            <i>Jude the Obscure</i> by Thomas Hardy</li>\n         <li>\n            <i>Pride and Prejudice</i> by Jane Austen</li>\n         <li>\n            <i>Tess of the d\'Urbervilles</i> by Thomas Hardy</li>\n         <li>\n            <i>The Big Over Easy</i> by Jasper Fforde</li>\n         <li>\n            <i>The Eyre Affair</i> by Jasper Fforde</li>\n         <li>\n            <i>Wuthering Heights</i> by Charlotte Brontë</li>\n      </ul>\n   </body>\n</html>");
//             console.dir(htmlContent);
        }
        catch (err) {
        console.dir(err.message);
        }
        done();
    });

    after(function(done) {
//      yield teardown();
        done();
    });
  });
