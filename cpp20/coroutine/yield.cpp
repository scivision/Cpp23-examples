// https://www.scs.stanford.edu/~dm/blog/c++-coroutines.html

#include <coroutine>
#include <iostream>
#include <cstdlib>

struct ReturnObject4 {
  struct promise_type {
    unsigned value_;

    ReturnObject4 get_return_object() {
      return {
        .h_ = std::coroutine_handle<promise_type>::from_promise(*this)
      };
    }
    std::suspend_never initial_suspend() { return {}; }
    std::suspend_never final_suspend() noexcept { return {}; }
    void unhandled_exception() {}
    std::suspend_always yield_value(unsigned value) {
      value_ = value;
      return {};
    }
    void return_void() noexcept {}
  };

  std::coroutine_handle<promise_type> h_;
};

ReturnObject4
counter()
{
  for (unsigned i = 0;; ++i)
    co_yield i;       // co yield i => co_await promise.yield_value(i)
}

void
main4()
{
  auto h = counter().h_;
  auto &promise = h.promise();
  for (int i = 0; i < 3; ++i) {
    std::cout << "counter: " << promise.value_ << "\n";
    h();
  }
  h.destroy();
}

int main(){
    main4();
    return EXIT_SUCCESS;
}
