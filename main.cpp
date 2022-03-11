extern int Main(int argc, char const*const argv[]);

#include <string>   // Bug workaround for gcc 9.2 - include before diagnostic_information.hpp
#include <boost/exception/diagnostic_information.hpp>
#include <cool/Args.h>
#include <cool/chrono.h>
#include <cool/Stopwatch.h>
#include <iostream>

int main(int argc, char* argv[])
{
    using cool::chrono::system_clock::operator<<;

    std::cerr
        << "Built " <<  __FILE__ << " on " << __DATE__ << ' ' << __TIME__
        << "\nStarted " << cool::Args(argv)
        << " at " << std::chrono::system_clock{}
        << std::endl;

    cool::Stopwatch<> sw{true};
    int status;
	try { status = Main(argc, argv); }
    catch (...)
    {
        std::cerr << cool::Args(argv) << '\n'
                << __PRETTY_FUNCTION__ << '\n'
                << boost::current_exception_diagnostic_information() << std::endl;
        status = 1;
    }

    std::cerr
        << "Stopped " << cool::Args(argv)
        << " at " << std::chrono::system_clock{}
        << " (" << sw
        << ") with status=" << status
        << std::endl;

    return status;
}

