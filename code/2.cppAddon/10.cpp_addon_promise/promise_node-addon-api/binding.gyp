{
  "targets": [
    {
      "target_name": "addon",
      "sources": [ "addon.cpp" ],
      "cflags!": [ "-fno-exceptions" ],
      "cflags_cc!": [ "-fno-exceptions" ],
      "include_dirs": [ "../../node-addon-api" ],
      'defines': [ 'NAPI_DISABLE_CPP_EXCEPTIONS' ],
    }
  ]
}
