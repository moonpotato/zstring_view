# zstring_view

A non-owning reference to a null-terminated part of a string

## Rationale

**TL;DR:** `mpt::zstring_view` extends the benefits of
`std::string_view` to code that requires strings that are
null-terminated. For full documentation, see the `docs/` directory.

The introduction of `std::string_view` into C++ provides a better way
to pass around non-owning references to (parts of) strings. For
example, it can return its length in `O(1)` time, compared to `O(N)`
with bare pointers. It avoids the need to create unnecessary
temporaries that can occur when using `const std::string&`s but still
supports a number of useful operations as methods and operator
overloads.

For more on the rationale and design of `std::string_view`, see
[proposal N3762][N3762] or the [cppreference.com page on
`std::basic_string_view`][basic_string_view].

[N3762]: http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2013/n3762.html
[basic_string_view]: https://en.cppreference.com/w/cpp/string/basic_string_view

However, `std::string_view` does not require the (sub-)string to
which it refers to be null-terminated. In fact, in order to support
some operations (`substr()` and `remove_suffix()`, particularly), it
cannot.  This prevents its use in several places where it might
otherwise be useful.

Many C APIs, and C++ code that interacts with them, need to be passed
null-terminated strings. As `std::string_view` cannot be used, we are
back to passing around bare pointers or `const std::string&`s and
potentially requiring unnecessary copies. Either that, or we must
write several overloads of functions that do the same thing but with
different string representations.

This is where `mpt::zstring_view` comes in. It can only be constructed
from a null-terminated string of some kind, and allows only operations
that preserve that property. It can also be implicitly cast to a plain
`std::string_view`, and operations that cause null-termination to be
potentially sacrificed also return `std::string_view`s.

## Usage

zstring_view is a header only library (and will remain so, even when
more files are introduced). Simply include the repository path in your
project's include path and include `zstring_view.hpp` where required.

## License

All code in the project is licensed under the Apache License 2.0. A
full copy of the license document is provided in `LICENSE.txt`. All
project documentation is licensed under the GNU Free Documentation
License, a copy of which is provided in `docs/LICENSE.txt`. Much of
this is based on content from the `cppreference.com` wiki, whose
information is often helpful and is much appreciated.
