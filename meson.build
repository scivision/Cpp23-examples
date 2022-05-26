project('CXX20examples', 'cpp',
meson_version: '>= 0.57.0',
default_options : ['cpp_std=c++20'])

cpp = meson.get_compiler('cpp')

if cpp.get_id() == 'msvc'
  modules_exe = executable('modules', 'modules/main.cpp', 'modules/math.ixx')
  test('C++ Modules', modules_exe, suite: '20')
endif

# --- C++20 numbers
numbers_exe = executable('numbers', 'src/numbers.cpp')
test('numbers', numbers_exe, suite: '20')

# --- C++17 folding ---
folding_exe = executable('folding', 'src/folding.cpp')
test('Folding', folding_exe, suite: '17')

# --- C++17 filesystem ---
subdir('filesystem')

# --- C++20 coroutine
coro_exe = executable('coro', 'src/coroutine.cpp')
test('Coroutine', coro_exe, suite: '20')

# --- threads
count_exe = executable('thread_count', 'src/thread_count.cpp')
test('ThreadCount', count_exe, suite: '14')
