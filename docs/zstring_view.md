# mpt::basic_zstring_view

Compatible with C++17 and higher, defined in header
`zstring_view.hpp`. This documentation is based on the documentation
for `std::basic_string_view` available on `cppreference.com`.

```C++
template <
    typename CharT,
    typename Traits = std::char_traits<CharT>
> class basic_zstring_view;
```

The class template `basic_zstring_view` refers to a constant,
contiguous sequence of `char`-like objects with a null character in
the 'one-past-the-end' position.

It is implemented as a wrapper around `std::basic_string_view`.

Typedefs for common character types are provided, as with
`basic_string_view`:

| **Type**                   | **Definition**                      |
| -------------------------- | ----------------------------------- |
| **`mpt::zstring_view`**    | `mpt::basic_zstring_view<char>`     |
| **`mpt::wzstring_view`**   | `mpt::basic_zstring_view<wchar_t>`  |
| **`mpt::u16zstring_view`** | `mpt::basic_zstring_view<char16_t>` |
| **`mpt::u32zstring_view`** | `mpt::basic_zstring_view<char32_t>` |

## Template parameters

**CharT** - Underlying character type  
**Traits** - CharTraits class specifying the operations on the
  character type. `Traits::char_type` must be the same as `CharT`, or
  behaviour is undefined.

## Member types

In the code, most of these typedefs are resolved with reference to
`underlying_type` the templated type of the `std::basic_string_view`.
This ensures they always work together in the same way.

Effective types:

| **Member type**          | **Definition**                          |
| ------------------------ | --------------------------------------- |
| `underlying_type`        | `std::basic_string_view<CharT, Traits>` |
| `traits_type`            | `Traits`                                |
| `value_type`             | `CharT`                                 |
| `pointer`                | `CharT*`                                |
| `const_pointer`          | `const CharT*`                          |
| `reference`              | `CharT&`                                |
| `const_reference`        | `const CharT&`                          |
| `const_iterator`         | `underlying_type::const_iterator`       |
| `iterator`               | `const_iterator`                        |
| `const_reverse_iterator` | `std::reverse_iterator<const_iterator>` |
| ` reverse_iterator`      | `const_reverse_iterator`                |
| `size_type`              | `std::size_t`                           |
| `difference_type`        | `std::ptrdiff_t`                        |

Note: `iterator` and `const_iterator` are the same because the view is
into a constant character sequence.

## Constants
