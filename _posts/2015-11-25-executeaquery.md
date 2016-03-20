---
layout: page
title: "Execute a Query"
category: tut
date: 2015-11-25 22:14:32
---



~~~ javascript
    try{
        var xqueryProcessor = saxonProcessor.newXQueryProcessor();
        var query = yield fs.readFile("./test/examples/query/books-to-html.xq", "utf8");
        var htmlContent = xqueryProcessor.executeQueryToString("./test/examples/query/books.xml", query);
        console.dir(htmlContent.toString());
        //send htmlContent on its way to browser
    }
    catch (err) {
    console.dir(err.message);
    }
~~~
