{
    'targets': [
        {
            'target_name': 'saxonXslt',
            'cflags!': [ '-fno-exceptions' ],
            'cflags_cc!': [ '-fno-exceptions' ],
            'cflags': ["-fPIC", "-O4", "-std=c++11", "-fexceptions"],
            'include_dirs': [
                '$(SAXON_HOME)/include',
                '$(JAVA_HOME)/include',
                '$(JAVA_HOME)/include/linux'
            ],
            'sources': [
                'src/XdmValue.cpp',
                'src/SaxonProcessor.cxx',
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