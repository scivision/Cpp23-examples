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

foreach(t IN ITEMS coroutine execution_policy)
  if(have_${t})
    string(JSON j SET ${j} ${t} true)
  else()
    string(JSON j SET ${j} ${t} false)
  endif()
endforeach()

string(JSON j SET ${j} compiler "{}")
string(JSON j SET ${j} compiler vendor \"${CMAKE_CXX_COMPILER_ID}\")
string(JSON j SET ${j} compiler version \"${CMAKE_CXX_COMPILER_VERSION}\")
string(JSON j SET ${j} compiler system \"${CMAKE_SYSTEM_NAME}\")
string(JSON j SET ${j} compiler system_version \"${CMAKE_SYSTEM_VERSION}\")
string(JSON j SET ${j} compiler target \"${CMAKE_SYSTEM_PROCESSOR}\")
string(JSON j SET ${j} compiler flags \"${CMAKE_CXX_FLAGS}\")
string(JSON j SET ${j} compiler sysroot \"${CMAKE_OSX_SYSROOT}\")

set(feature_file ${CMAKE_CURRENT_BINARY_DIR}/features.json)

file(WRITE ${feature_file} ${j})

message(STATUS "See ${feature_file} for features enabled by standard")
