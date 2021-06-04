{
  'targets': [
    {
      'target_name': 'addon',
      'sources': [ 'addon.cpp' ],
	    'include_dirs':[ 'thirdlib' ],
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