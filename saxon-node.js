/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

var co = require('co');
var fs = require('co-fs');
var saxon = require('saxonXslt');
global.inputXmlPath = process.argv[2];
global.xslPath = process.argv[3];
co(function * (){
try
{
    var content = yield fs.readFile(global.inputXmlPath, "utf8");
    var saxonProcessor = new saxon.SaxonProcessor(false);
    var xsltProcessor = saxonProcessor.newTransformer();
    xsltProcessor.compile(global.xslPath);
    xsltProcessor.parseXmlString(content);
    var pdbContent = xsltProcessor.xsltApplyStylesheet();
    console.dir(pdbContent);
}
catch (err) {
console.dir(err.message);
}
});