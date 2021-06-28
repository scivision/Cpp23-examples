project('CXX20examples', 'cpp',
  default_options : ['default_library=static', 'cpp_std=c++17'])

# not yet supported by Meson 0.51
if false
  modules_exe = executable('modules', 'math.cpp', 'math.ixx')
  test('C++20Modules', modules_exe)
endif

# --- C++17 folding ---
folding_exe = executable('folding', 'src/folding.cpp')
test('Folding-17', folding_exe)

# --- C++17 filesystem ---
subdir('filesystem')

# --- C++17 threads ---
count_exe = executable('thread_count', 'src/thread_count.cpp')
test('ThreadCount-11', count_exe)
