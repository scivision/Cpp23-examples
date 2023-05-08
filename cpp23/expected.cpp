// modified  from https://mariusbancila.ro/blog/2022/08/17/using-the-cpp23-expected-type/

#include <iostream>
#include <expected>
#include <vector>
#include <algorithm>
#include <cstdlib>

#if __has_include(<format>)
#include <format>
#endif

enum class Status
{
   Ok,
   AccessDenied,
   DataSourceError,
   DataError,
};
bool HasAcccess() { return true; }
int OpenConnection() { return 0; }
int Fetch() { return 0; }
Status ReadData(std::vector<int>& data)
{
   if (!HasAcccess())
      return Status::AccessDenied;
   if (OpenConnection() != 0)
      return Status::DataSourceError;
   if (Fetch() != 0)
      return Status::DataError;
   data.push_back(42);
   return Status::Ok;
}

void print_value(int const v)
{
   std::cout << v << '\n';
}


std::expected<std::vector<int>, Status> ReadData()
{
   if (!HasAcccess())
      return std::unexpected<Status> { Status::AccessDenied };
   if (OpenConnection() != 0)
      return std::unexpected<Status> {Status::DataSourceError};
   if (Fetch() != 0)
      return std::unexpected<Status> {Status::DataError};
   std::vector<int> data;
   data.push_back(42);
   return data;
}

int main()
{
   auto result = ReadData();
   if (result)
   {
      std::ranges::for_each(result.value(), print_value);
   }
   else
   {
#ifdef __cpp_lib_format
      std::cout << std::format("Error code: {}", (int)result.error()) << std::endl;
#else
      std::cout << "Error code: " << (int)result.error() << std::endl;
#endif
   }

   return EXIT_SUCCESS;
}
