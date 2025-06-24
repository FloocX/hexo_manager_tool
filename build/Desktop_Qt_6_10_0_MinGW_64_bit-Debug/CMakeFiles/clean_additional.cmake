# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\hexo_blogs_tools_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\hexo_blogs_tools_autogen.dir\\ParseCache.txt"
  "hexo_blogs_tools_autogen"
  )
endif()
