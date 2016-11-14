#pragma once

#if __has_include(<any>)
    #include <any>
    namespace stdx {
        using std::any;
        using std::any_cast;
        using std::bad_any_cast;
    }
#elif __has_include(<experimental/any>)
    #include <experimental/any>
    namespace stdx {
        using std::experimental::any;
        using std::experimental::any_cast;
        using std::experimental::bad_any_cast;
    }
#else
    #error no implementation of any found
#endif
