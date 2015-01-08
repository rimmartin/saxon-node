{
    'targets': [
        {
            'target_name': 'saxonXslt',
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
        }
    ]
}