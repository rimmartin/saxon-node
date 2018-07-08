{
    "variables": {
        "saxonc_home%": "../Saxonica/Saxon-HEC1.1.0",
    },
    'targets': [
        {
            'target_name': 'saxonXslt',
            'conditions': [
            ['OS=="linux"', {
                'cflags!': [ '-fno-exceptions' ],
                'cflags_cc!': [ '-fno-exceptions' ],
                'cflags': ["-fPIC", "-O4", "-DCPP_ONLY", "-std=c++11", "-fexceptions", "-Wl,--allow-multiple-definition"],
                'include_dirs': [
                    '<(saxonc_home)/Saxon.C.API',
                    '$(JAVA_HOME)/include',
                    '$(JAVA_HOME)/include/linux',
                    'src/'
                ],
                'sources': [
                    '<(saxonc_home)/Saxon.C.API/SaxonCGlue.c',
                    '<(saxonc_home)/Saxon.C.API/SaxonCXPath.c',
                    '<(saxonc_home)/Saxon.C.API/SaxonProcessor.cpp',
                    '<(saxonc_home)/Saxon.C.API/XsltProcessor.cpp',
                    '<(saxonc_home)/Saxon.C.API/XQueryProcessor.cpp',
                    '<(saxonc_home)/Saxon.C.API/XPathProcessor.cpp',
                    '<(saxonc_home)/Saxon.C.API/SchemaValidator.cpp',
                    '<(saxonc_home)/Saxon.C.API/XdmItem.cpp',
                    '<(saxonc_home)/Saxon.C.API/XdmValue.cpp',
                    '<(saxonc_home)/Saxon.C.API/XdmNode.cpp',
                    '<(saxonc_home)/Saxon.C.API/XdmAtomicValue.cpp',
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
                        '-L<(saxonc_home)'
                    ]
                }
            }],
            ['OS=="win"', {
                'include_dirs': [
                    "<!(echo %SAXONC_HOME%)/Saxon-C-API",
                    "<!(echo %JAVA_HOME%)/include",
                    "<!(echo %JAVA_HOME%)/include/win32",
                    "./src"
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
                    '<(saxonc_home)/Saxon.C.API',
                    '$(JAVA_HOME)/include',
                    '$(JAVA_HOME)/include/darwin',
                    'src/'
                ],
                'sources': [
                    '<(saxonc_home)/Saxon.C.API/SaxonCGlue.c',
                    '<(saxonc_home)/Saxon.C.API/SaxonCXPath.c',
                    '<(saxonc_home)/Saxon.C.API/SaxonProcessor.cpp',
                    '<(saxonc_home)/Saxon.C.API/XsltProcessor.cpp',
                    '<(saxonc_home)/Saxon.C.API/XQueryProcessor.cpp',
                    '<(saxonc_home)/Saxon.C.API/XPathProcessor.cpp',
                    '<(saxonc_home)/Saxon.C.API/SchemaValidator.cpp',
                    '<(saxonc_home)/Saxon.C.API/XdmItem.cpp',
                    '<(saxonc_home)/Saxon.C.API/XdmValue.cpp',
                    '<(saxonc_home)/Saxon.C.API/XdmNode.cpp',
                    '<(saxonc_home)/Saxon.C.API/XdmAtomicValue.cpp',
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
                        '-L<(saxonc_home)'
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
