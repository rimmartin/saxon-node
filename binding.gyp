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
                    '$(SAXON_HOME)/include',
                    '$(JAVA_HOME)/include',
                    '$(JAVA_HOME)/include/linux',
                    'src/'
                ],
                'sources': [
                    'src/SaxonProcessor.cpp',
                    'src/SaxonProcessorJS.cxx',
                    'src/saxonXslt.cxx'
                ],
                'link_settings': {
                    'libraries': [
                        '-lsaxon'
                    ],
                    'ldflags': [
                        '-L$(SAXON_HOME)'
                    ]
                }
            }],
            ['OS=="win"', {
                'include_dirs': [
                    "<!(echo %SAXON_HOME%)/Saxon-C-API",
                    "<!(echo %JAVA_HOME%)/include",
                    "<!(echo %JAVA_HOME%)/include/win32",
                    "./src",
                    "C:\\Software\\node-v0.12.7\\src",
                    "C:\\Software\\node-v0.12.7\\deps\\v8\\include"
                ],
                'sources': [
                    'src\SaxonProcessor.cpp',
                    'src\SaxonProcessorJS.cxx',
                    'src\saxonXslt.cxx'
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
                        '<!(echo %SAXON_HOME%)/libsaxon.dll'
                    ]
                }
            }],
            ['OS=="mac"', {
                'cflags': ["-fPIC", "-O4", "-DCPP_ONLY", "-std=c++11", "-fexceptions", "-Wl,--allow-multiple-definition"],
                'xcode_settings': {
                    'OTHER_CFLAGS': ["-fPIC", "-O4", "-DCPP_ONLY", "-std=c++11", "-fexceptions"]
                },
                'include_dirs': [
                    '$(SAXON_HOME)/include',
                    '$(JAVA_HOME)/include',
                    '$(JAVA_HOME)/include/darwin',
                    'src/'
                ],
                'sources': [
                    'src/SaxonProcessor.cpp',
                    'src/SaxonProcessorJS.cxx',
                    'src/saxonXslt.cxx'
                ],
                'link_settings': {
                    'libraries': [
                    ],
                    'ldflags': [
                        '-L$(SAXON_HOME)'
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
