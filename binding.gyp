{
    'targets': [
        {
            'target_name': 'saxonXslt',
            'conditions': [
            ['OS=="linux"', {
                'cflags!': [ '-fno-exceptions' ],
                'cflags_cc!': [ '-fno-exceptions' ],
                'cflags': ["-fPIC", "-O4", "-DCPP_ONLY", "-std=c++11", "-fexceptions", "-Wl,--allow-multiple-definition"],
                'include_dirs': [
                    '../$(SAXONC_HOME)/Saxon.C.API',
                    '$(JAVA_HOME)/include',
                    '$(JAVA_HOME)/include/linux',
                    'src/'
                ],
                'sources': [
                    '$(SAXONC_HOME)/Saxon.C.API/SaxonCGlue.c',
                    '$(SAXONC_HOME)/Saxon.C.API/SaxonCXPath.c',
                    '$(SAXONC_HOME)/Saxon.C.API/SaxonProcessor.cpp',
                    '$(SAXONC_HOME)/Saxon.C.API/XsltProcessor.cpp',
                    '$(SAXONC_HOME)/Saxon.C.API/XQueryProcessor.cpp',
                    '$(SAXONC_HOME)/Saxon.C.API/XPathProcessor.cpp',
                    '$(SAXONC_HOME)/Saxon.C.API/SchemaValidator.cpp',
                    '$(SAXONC_HOME)/Saxon.C.API/XdmItem.cpp',
                    '$(SAXONC_HOME)/Saxon.C.API/XdmValue.cpp',
                    '$(SAXONC_HOME)/Saxon.C.API/XdmNode.cpp',
                    '$(SAXONC_HOME)/Saxon.C.API/XdmAtomicValue.cpp',
                    'src/XdmValueJS.cxx',
                    'src/XdmItemJS.cxx',
                    'src/XdmNodeJS.cxx',
                    'src/XdmAtomicValueJS.cxx',
                    'src/SaxonProcessorJS.cxx',
                    'src/saxonXslt.cxx'
                ],
                'link_settings': {
                    'libraries': [
                    ],
                    'ldflags': [
                        '-L$(SAXONC_HOME)'
                    ]
                }
            }],
            ['OS=="win"', {
                'include_dirs': [
                    "<!(echo %SAXONC_HOME%)/Saxon-C-API",
                    "<!(echo %JAVA_HOME%)/include",
                    "<!(echo %JAVA_HOME%)/include/win32",
                    "./src",
                    "C:\\Software\\node-v0.12.7\\src",
                    "C:\\Software\\node-v0.12.7\\deps\\v8\\include"
                ],
                'sources': [
                    'src/SaxonProcessor.cpp',
                    'src/SaxonProcessorJS.cxx',
                    'src/saxonXslt.cxx'
                ],
                'msbuild_toolset': 'v120',
                "configurations": {
                            "Release": {
                'msvs_settings':
                {
                    'VCCLCompilerTool':
                    {
                        'RuntimeLibrary': 2,        # shared release
                        'ExceptionHandling': 1,     # /EHsc
                        "PreprocessorDefinitions" :
                        [
                            "CPP_ONLY"
                        ],
                        'AdditionalOptions': 
                        [
                            '/EHsc' # Enable unwind semantics for Exception Handling.  This one actually does the trick - and no warning either.
                        ]
                    }
                }
              }
              },
                'link_settings': {
                    'libraries': [
                    ]
                }
            }],
            ['OS=="mac"', {
                'xcode_settings': {
                    'OTHER_CPLUSPLUSFLAGS': ["-fPIC", "-O3", "-DCPP_ONLY", "-std=c++11", "-fexceptions","-v"],
                    'OTHER_LDFLAGS': []
                },
                'include_dirs': [
                    '../$(SAXONC_HOME)/Saxon.C.API',
                    '$(JAVA_HOME)/include',
                    '$(JAVA_HOME)/include/darwin',
                    'src/'
                ],
                'sources': [
                    '$(SAXONC_HOME)/Saxon.C.API/SaxonCGlue.c',
                    '$(SAXONC_HOME)/Saxon.C.API/SaxonCXPath.c',
                    '$(SAXONC_HOME)/Saxon.C.API/SaxonProcessor.cpp',
                    '$(SAXONC_HOME)/Saxon.C.API/XsltProcessor.cpp',
                    '$(SAXONC_HOME)/Saxon.C.API/XQueryProcessor.cpp',
                    '$(SAXONC_HOME)/Saxon.C.API/XPathProcessor.cpp',
                    '$(SAXONC_HOME)/Saxon.C.API/SchemaValidator.cpp',
                    '$(SAXONC_HOME)/Saxon.C.API/XdmItem.cpp',
                    '$(SAXONC_HOME)/Saxon.C.API/XdmValue.cpp',
                    '$(SAXONC_HOME)/Saxon.C.API/XdmNode.cpp',
                    '$(SAXONC_HOME)/Saxon.C.API/XdmAtomicValue.cpp',
                    'src/XdmValueJS.cxx',
                    'src/XdmItemJS.cxx',
                    'src/XdmNodeJS.cxx',
                    'src/XdmAtomicValueJS.cxx',
                    'src/SaxonProcessorJS.cxx',
                    'src/saxonXslt.cxx'
                ],
                'link_settings': {
                    'libraries': [
                    ],
                    'ldflags': [
                        '-L$(SAXONC_HOME)'
                    ]
                }
            }]
           ]
        },
        {
            "target_name": "action_after_build",
            "type": "none",
            "dependencies": [ "<(module_name)" ],
            "copies": [
            {
              "files": [ "<(PRODUCT_DIR)/<(module_name).node" ],
              "destination": "<(module_path)"
            }
            ]
        }        
    ]
}
