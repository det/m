#pragma once

#if __has_include(<string_view>)
    #include <string_view>
    namespace stdx {
        using std::basic_string_view;
        using std::string_view;
        using std::u16string_view;
        using std::u32string_view;
        using std::wstring_view;
    }
#elif __has_include(<experimental/string_view>)
    #include <experimental/string_view>
    namespace stdx {
        using std::experimental::basic_string_view;
        using std::experimental::string_view;
        using std::experimental::u16string_view;
        using std::experimental::u32string_view;
        using std::experimental::wstring_view;
    }
#else
    #error no implementation of string_view found
#endif
