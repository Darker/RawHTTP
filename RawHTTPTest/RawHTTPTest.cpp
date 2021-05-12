#include <iostream>
#include <string>
#include <sstream>
#include <array>

#include <RawHttp/Types.h>
#include <RawHttp/Windows/WindowsTCPListener.h>
#include <RawHttp/ITCPSocket.h>

const char* reply = R"D(HTTP/2 200 OK
date: Sat, 17 Apr 2021 09:45:34 GMT
content-type: text/html;charset=utf-8
cache-control: max-age=1800, private
pragma: max-age=1800
expires: Sat, 17 Apr 2021 10:15:34 GMT

<head><title>TEST</title></head><body>HTTP reply!</body>
)D";

int main()
{
    std::cout << "Hello World!\n";
    RawHttp::WindowsTCPListener test({ RawHttp::IPAddress::Type::IPV4, {}, 8080 });
    test.OnClient([](RawHttp::ITCPSocket* s)
      {
        std::stringstream stream;
        std::array<RawHttp::byte, 64> data;
        size_t end = 0;
        while (true)
        {
         
          end = s->Read(data);
          for (size_t i = 0; i < end; ++i)
          {
            stream << data[i];
          }

          if (end == 0 || stream.str().find("\r\n\r\n") != std::string::npos)
          {
            break;
          }
        }
        std::cout << "Data received: \r\n" << stream.str() << "\r\n";


        s->Write((RawHttp::byte*)reply, strlen(reply));
        s->Close();
      });
    std::cout << "Listening on 127.0.0.1:8080" << std::endl;
    test.Start();
}
