set(j "{}")

foreach(s IN LISTS stds)

get_property(has_features DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/cpp${s} PROPERTY BUILDSYSTEM_TARGETS)

list(LENGTH cpp${s}features Nf)

math(EXPR N "${Nf} - 1")
string(JSON j SET ${j} cpp${s} "{}")

foreach(i RANGE ${N})
  list(GET cpp${s}features ${i} feature)
  if(feature IN_LIST has_features)
    set(hasf true)
  else()
    set(hasf false)
  endif()

  string(JSON j SET ${j} cpp${s} ${feature} ${hasf})
endforeach()

endforeach()

if(have_coroutine)
  string(JSON j SET ${j} cpp20 coroutine true)
else()
  string(JSON j SET ${j} cpp20 coroutine false)
endif()

string(JSON j SET ${j} compiler "{}")
string(JSON j SET ${j} compiler vendor \"${CMAKE_CXX_COMPILER_ID}\")
string(JSON j SET ${j} compiler version \"${CMAKE_CXX_COMPILER_VERSION}\")

set(feature_file ${CMAKE_CURRENT_BINARY_DIR}/features.json)

file(WRITE ${feature_file} ${j})

message(STATUS "See ${feature_file} for features enabled by standard")
