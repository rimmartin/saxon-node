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
    if(process.argv.length>4)
    {
        for(var index=4;index<process.argv.length;index++)
        {
            var pair = process.argv[index].split("=");
            xsltProcessor.parameters[pair[0]]=pair[1];
        }
    }
    xsltProcessor.compileFromFile(global.xslPath);
            for(var i=0;i<10;i++)
            {
    xsltProcessor.setSourceFromString(content);
    var pdbContent = xsltProcessor.transformToString();
    console.dir(pdbContent.toString());
            }
}
catch (err) {
console.dir("caught "+err.message);
}
});