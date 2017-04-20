# Copyright (c) 2017 Minqi Pan <pmq2001@gmail.com>
# 
# This file is part of libhessian, distributed under the MIT License
# For full terms see the included LICENSE file

{
  'targets': [
    {
      'target_name': 'libhessian',
      'type': 'static_library',
      'sources': [
        'include/hessian.h',
        'include/hessian/encode.h',
        'include/hessian/decode.h',
        'src/date.c',
        'src/int.c',
        'src/long.c',
        'src/string.c',
      ],
      'include_dirs': [
        'include',
      ],
    },
  ],
}
