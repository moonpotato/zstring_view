//  This file is part of moonpotato/zstring_view
//  zstring_view: A non-owning reference to a null-terminated part of a string
//
//   Copyright 2018 moonpotato <git@funnelweb.xyz>
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

#ifndef ZSTRING_VIEW_INCLUDED
#define ZSTRING_VIEW_INCLUDED

#include <cstddef>
#include <ostream>
#include <string_view>

namespace mpt
{
    template <typename CharT, typename Traits = std::char_traits<CharT>>
    class basic_zstring_view;

    using zstring_view = basic_zstring_view<char>;
    using wzstring_view = basic_zstring_view<wchar_t>;
    using u16zstring_view = basic_zstring_view<char16_t>;
    using u32zstring_view = basic_zstring_view<char32_t>;

    template <typename CharT, typename Traits>
    class basic_zstring_view
    {
    public:
        using underlying_type        = std::basic_string_view<CharT, Traits>;

        using traits_type            = typename underlying_type::traits_type;
        using value_type             = typename underlying_type::value_type;
        using pointer                = typename underlying_type::pointer;
        using const_pointer          = typename underlying_type::const_pointer;
        using reference              = typename underlying_type::reference;
        using const_reference        = typename underlying_type::const_reference;
        using const_iterator         = typename underlying_type::const_iterator;
        using iterator               = typename underlying_type::iterator;
        using const_reverse_iterator = typename underlying_type::const_reverse_iterator;
        using reverse_iterator       = typename underlying_type::reverse_iterator;
        using size_type              = typename underlying_type::size_type;
        using difference_type        = typename underlying_type::difference_type;

        static constexpr size_type npos = -1;

        constexpr basic_zstring_view() noexcept = default;
        constexpr basic_zstring_view(const basic_zstring_view& other) noexcept = default;
        constexpr basic_zstring_view(const CharT* s) : m_view{s} {}

        // Needed as a workaround for gcc bug #61648
        // Allows non-friend string literal operators the ability to indirectly call the private constructor
        // Safe calling of this requires *certainty* that s[count] is a null character
        // Has to be public thusly, but don't call this
        static constexpr basic_zstring_view _INTERNAL_unsafe_make_from_string_range(const CharT* s, size_type count)
        {
            return {s, count};
        }

        constexpr basic_zstring_view& operator =(const basic_zstring_view& view) noexcept = default;

        constexpr const_iterator begin() const noexcept
        {
            return m_view.begin();
        }

        constexpr const_iterator cbegin() const noexcept
        {
            return m_view.cbegin();
        }

        constexpr const_iterator end() const noexcept
        {
            return m_view.end();
        }

        constexpr const_iterator cend() const noexcept
        {
            return m_view.cend();
        }

        constexpr const_reverse_iterator rbegin() const noexcept
        {
            return m_view.rbegin();
        }

        constexpr const_reverse_iterator crbegin() const noexcept
        {
            return m_view.crbegin();
        }

        constexpr const_reverse_iterator rend() const noexcept
        {
            return m_view.rend();
        }

        constexpr const_reverse_iterator crend() const noexcept
        {
            return m_view.crend();
        }

        constexpr const_reference operator [](size_type pos) const
        {
            return m_view[pos];
        }

        constexpr const_reference at(size_type pos) const
        {
            return m_view.at(pos);
        }

        constexpr const_reference front() const
        {
            return m_view.front();
        }

        constexpr const_reference back() const
        {
            return m_view.back();
        }

        constexpr const_pointer data() const noexcept
        {
            return m_view.data();
        }

        // Additional function
        constexpr const_pointer c_str() const noexcept
        {
            return m_view.data();
        }

        constexpr size_type size() const noexcept
        {
            return m_view.size();
        }

        constexpr size_type length() const noexcept
        {
            return m_view.length();
        }

        constexpr size_type max_size() const noexcept
        {
            return m_view.max_size();
        }

        constexpr bool empty() const noexcept
        {
            return m_view.empty();
        }

        constexpr void remove_prefix(size_type n)
        {
            m_view.remove_prefix(n);
        }

        constexpr void swap(basic_zstring_view& v) noexcept
        {
            swap(m_view, v.m_view);
        }

        size_type copy(CharT* dest, size_type count, size_type pos = 0) const
        {
            return m_view.copy(dest, count, pos);
        }

        constexpr underlying_type substr(size_type pos = 0, size_type count = npos) const
        {
            return m_view.substr(pos, count);
        }

        // Additional function
        constexpr basic_zstring_view suffix(size_type start = 0) const
        {
            return basic_zstring_view{m_view.substr(start, npos)};
        }

        constexpr int compare(underlying_type v) const noexcept
        {
            return m_view.compare(v);
        }

        constexpr int compare(size_type pos1, size_type count1, underlying_type v) const
        {
            return m_view.compare(pos1, count1, v);
        }

        constexpr int compare(size_type pos1, size_type count1, underlying_type v,
                              size_type pos2, size_type count2) const
        {
            return m_view.compare(pos1, count1, v, pos2, count2);
        }

        constexpr int compare(const CharT* s) const
        {
            return m_view.compare(s);
        }

        constexpr int compare(size_type pos1, size_type count1,
                              const CharT* s, size_type count2) const
        {
            return m_view.compare(pos1, count1, s, count2);
        }

        constexpr bool starts_with(underlying_type x) const noexcept
        {
            return m_view.starts_with(x);
        }

        constexpr bool starts_with(CharT x) const noexcept
        {
            return m_view.starts_with(x);
        }

        constexpr bool starts_with(const CharT* x) const
        {
            return m_view.starts_with(x);
        }

        constexpr bool ends_with(underlying_type x) const noexcept
        {
            return m_view.ends_with(x);
        }

        constexpr bool ends_with(CharT x) const noexcept
        {
            return m_view.ends_with(x);
        }

        constexpr bool ends_with(const CharT* x) const
        {
            return m_view.ends_with(x);
        }

        constexpr size_type find(underlying_type v, size_type pos = 0) const noexcept
        {
            return m_view.find(v, pos);
        }

        constexpr size_type find(CharT ch, size_type pos = 0) const noexcept
        {
            return m_view.find(ch, pos);
        }

        constexpr size_type find(const CharT* s, size_type pos, size_type count) const
        {
            return m_view.find(s, pos, count);
        }

        constexpr size_type find(const CharT* s, size_type pos = 0) const
        {
            return m_view.find(s, pos);
        }

        constexpr size_type rfind(underlying_type v, size_type pos = npos) const noexcept
        {
            return m_view.rfind(v, pos);
        }

        constexpr size_type rfind(CharT ch, size_type pos = npos) const noexcept
        {
            return m_view.rfind(ch, pos);
        }

        constexpr size_type rfind(const CharT* s, size_type pos, size_type count) const
        {
            return m_view.rfind(s, pos, count);
        }

        constexpr size_type rfind(const CharT* s, size_type pos = npos) const
        {
            return m_view.rfind(s, pos);
        }

        constexpr size_type find_first_of(underlying_type v, size_type pos = 0) const noexcept
        {
            return m_view.find_first_of(v, pos);
        }

        constexpr size_type find_first_of(CharT c, size_type pos = 0) const noexcept
        {
            return m_view.find_first_of(c, pos);
        }

        constexpr size_type find_first_of(const CharT* s, size_type pos, size_type count) const
        {
            return m_view.find_first_of(s, pos, count);
        }

        constexpr size_type find_first_of(const CharT* s, size_type pos = 0) const
        {
            return m_view.find_first_of(s, pos);
        }

        constexpr size_type find_last_of(underlying_type v, size_type pos = npos) const noexcept
        {
            return m_view.find_last_of(v, pos);
        }

        constexpr size_type find_last_of(CharT c, size_type pos = npos) const noexcept
        {
            return m_view.find_last_of(c, pos);
        }

        constexpr size_type find_last_of(const CharT* s, size_type pos, size_type count) const
        {
            return m_view.find_last_of(s, pos, count);
        }

        constexpr size_type find_last_of(const CharT* s, size_type pos = npos) const
        {
            return m_view.find_last_of(s, pos);
        }

        constexpr size_type find_first_not_of(underlying_type v, size_type pos = 0) const noexcept
        {
            return m_view.find_first_not_of(v, pos);
        }

        constexpr size_type find_first_not_of(CharT c, size_type pos = 0) const noexcept
        {
            return m_view.find_first_not_of(c, pos);
        }

        constexpr size_type find_first_not_of(const CharT* s, size_type pos, size_type count) const
        {
            return m_view.find_first_not_of(s, pos, count);
        }

        constexpr size_type find_first_not_of(const CharT* s, size_type pos = 0) const
        {
            return m_view.find_first_not_of(s, pos);
        }

        constexpr size_type find_last_not_of(underlying_type v, size_type pos = npos) const noexcept
        {
            return m_view.find_last_not_of(v, pos);
        }

        constexpr size_type find_last_not_of(CharT c, size_type pos = npos) const noexcept
        {
            return m_view.find_last_not_of(c, pos);
        }

        constexpr size_type find_last_not_of(const CharT* s, size_type pos, size_type count) const
        {
            return m_view.find_last_not_of(s, pos, count);
        }

        constexpr size_type find_last_not_of(const CharT* s, size_type pos = npos) const
        {
            return m_view.find_last_not_of(s, pos);
        }

        constexpr const underlying_type& view() const noexcept
        {
            return m_view;
        }

        constexpr operator underlying_type() const noexcept
        {
            return m_view;
        }

    private:
        // Private constructor, called by the string literal operators
        constexpr basic_zstring_view(const CharT* s, size_type count) : m_view{s, count} {}

        // Private constructor, needed by suffix()
        explicit constexpr basic_zstring_view(const underlying_type& v) noexcept : m_view{v} {}

        underlying_type m_view;
    };

    template <typename CharT, typename Traits>
    constexpr bool operator ==(basic_zstring_view<CharT, Traits> lhs,
                               basic_zstring_view<CharT, Traits> rhs) noexcept
    {
        return lhs.view() == rhs.view();
    }

    template <typename CharT, typename Traits>
    constexpr bool operator ==(basic_zstring_view<CharT, Traits> lhs,
                               std::basic_string_view<CharT, Traits> rhs) noexcept
    {
        return lhs.view() == rhs;
    }

    template <typename CharT, typename Traits>
    constexpr bool operator ==(std::basic_string_view<CharT, Traits> lhs,
                               basic_zstring_view<CharT, Traits> rhs) noexcept
    {
        return lhs == rhs.view();
    }

    template <typename CharT, typename Traits>
    constexpr bool operator !=(basic_zstring_view<CharT, Traits> lhs,
                               basic_zstring_view<CharT, Traits> rhs) noexcept
    {
        return lhs.view() != rhs.view();
    }

    template <typename CharT, typename Traits>
    constexpr bool operator !=(basic_zstring_view<CharT, Traits> lhs,
                               std::basic_string_view<CharT, Traits> rhs) noexcept
    {
        return lhs.view() != rhs;
    }

    template <typename CharT, typename Traits>
    constexpr bool operator !=(std::basic_string_view<CharT, Traits> lhs,
                               basic_zstring_view<CharT, Traits> rhs) noexcept
    {
        return lhs != rhs.view();
    }

    template <typename CharT, typename Traits>
    constexpr bool operator <(basic_zstring_view<CharT, Traits> lhs,
                              basic_zstring_view<CharT, Traits> rhs) noexcept
    {
        return lhs.view() < rhs.view();
    }

    template <typename CharT, typename Traits>
    constexpr bool operator <(basic_zstring_view<CharT, Traits> lhs,
                              std::basic_string_view<CharT, Traits> rhs) noexcept
    {
        return lhs.view() < rhs;
    }

    template <typename CharT, typename Traits>
    constexpr bool operator <(std::basic_string_view<CharT, Traits> lhs,
                              basic_zstring_view<CharT, Traits> rhs) noexcept
    {
        return lhs < rhs.view();
    }

    template <typename CharT, typename Traits>
    constexpr bool operator <=(basic_zstring_view<CharT, Traits> lhs,
                               basic_zstring_view<CharT, Traits> rhs) noexcept
    {
        return lhs.view() <= rhs.view();
    }

    template <typename CharT, typename Traits>
    constexpr bool operator <=(basic_zstring_view<CharT, Traits> lhs,
                               std::basic_string_view<CharT, Traits> rhs) noexcept
    {
        return lhs.view() <= rhs;
    }

    template <typename CharT, typename Traits>
    constexpr bool operator <=(std::basic_string_view<CharT, Traits> lhs,
                               basic_zstring_view<CharT, Traits> rhs) noexcept
    {
        return lhs <= rhs.view();
    }

    template <typename CharT, typename Traits>
    constexpr bool operator >(basic_zstring_view<CharT, Traits> lhs,
                              basic_zstring_view<CharT, Traits> rhs) noexcept
    {
        return lhs.view() > rhs.view();
    }

    template <typename CharT, typename Traits>
    constexpr bool operator >(basic_zstring_view<CharT, Traits> lhs,
                              std::basic_string_view<CharT, Traits> rhs) noexcept
    {
        return lhs.view() > rhs;
    }

    template <typename CharT, typename Traits>
    constexpr bool operator >(std::basic_string_view<CharT, Traits> lhs,
                              basic_zstring_view<CharT, Traits> rhs) noexcept
    {
        return lhs > rhs.view();
    }

    template <typename CharT, typename Traits>
    constexpr bool operator >=(basic_zstring_view<CharT, Traits> lhs,
                               basic_zstring_view<CharT, Traits> rhs) noexcept
    {
        return lhs.view() >= rhs.view();
    }

    template <typename CharT, typename Traits>
    constexpr bool operator >=(basic_zstring_view<CharT, Traits> lhs,
                               std::basic_string_view<CharT, Traits> rhs) noexcept
    {
        return lhs.view() >= rhs;
    }

    template <typename CharT, typename Traits>
    constexpr bool operator >=(std::basic_string_view<CharT, Traits> lhs,
                               basic_zstring_view<CharT, Traits> rhs) noexcept
    {
        return lhs >= rhs.view();
    }

    template <typename CharT, typename Traits>
    auto operator << (std::basic_ostream<CharT, Traits>& os,
                      basic_zstring_view<CharT, Traits> v) -> decltype(os)
    {
        return os << v.view();
    }

    inline namespace literals
    {
        inline namespace zstring_view_literals
        {
            constexpr zstring_view operator ""_zsv(const char* str, std::size_t len) noexcept
            {
                return zstring_view::_INTERNAL_unsafe_make_from_string_range(str, len);
            }

            constexpr u16zstring_view operator ""_zsv(const char16_t* str, std::size_t len) noexcept
            {
                return u16zstring_view::_INTERNAL_unsafe_make_from_string_range(str, len);
            }

            constexpr u32zstring_view operator ""_zsv(const char32_t* str, std::size_t len) noexcept
            {
                return u32zstring_view::_INTERNAL_unsafe_make_from_string_range(str, len);
            }

            constexpr wzstring_view operator ""_zsv(const wchar_t* str, std::size_t len) noexcept
            {
                return wzstring_view::_INTERNAL_unsafe_make_from_string_range(str, len);
            }
        }
    }
}

#endif
