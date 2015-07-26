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
                'cflags!': [ '-fno-exceptions' ],
                'cflags_cc!': [ '-fno-exceptions' ],
                'cflags': ["-fPIC", "-O4", "/m 3", "-DCPP_ONLY", "-std=c++11", "-fexceptions"],
                'include_dirs': [
                    '%SAXON_HOME%/Saxon-C-API',
                    '%JAVA_HOME%/include',
                    '%JAVA_HOME%/include/win32',
                    './src',
                    'C:\Software\node-v0.11.14\src'
                ],
                'sources': [
                    'src\SaxonProcessor.cpp',
                    'src\SaxonProcessorJS.cxx',
                    'src\saxonXslt.cxx'
                ],
                    'libraries': [
                        '%SAXON_HOME%/libsaxon.dll'
                    ],
                'link_settings': {
                    'libraries': [
                        '%SAXON_HOME%/libsaxon.dll'
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
                        '$(SAXON_HOME)/libsaxon.dylib'
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