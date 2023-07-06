{
  'targets': [
    {
      'target_name': 'addon',
      'sources': [ 'addon.cpp' ],
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "include_dirs": [ ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
	    'include_dirs':[ 
        "../../node-addon-api",
        'thirdlib' 
      ],
      'libraries':[ '-lmyadd' ],
      # 'library_dirs':[ '<(module_root_dir)/thirdlib/bin_win/Debug' ]
      'conditions': [
          ['OS=="win"',{
              'library_dirs':[ '<(module_root_dir)/thirdlib/bin_win/Debug' ]
          }],
          ['OS=="linux"',{
              'library_dirs':[ '<(module_root_dir)/thirdlib/bin_unix' ]
          }],
          ['OS=="mac"',{ # not test
              'library_dirs':[ '<(module_root_dir)/thirdlib/bin_unix' ]
          }]
      ]
    }
  ]
}