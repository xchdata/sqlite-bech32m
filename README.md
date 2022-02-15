# sqlite-bech32m

An extension for SQLite that provides a bech32m encoding function. Given
a sequence of bytes either as TEXT or BLOB, a Bech32m-encoded string is
returned.

## Installation

Compilation requires SQLite headers. On Debian-derived Linux distributions,
install `libsqlite3-dev`.

Run `make` to build a shared library loadable as SQLite extension.

## Example Usage

```
$ sqlite3
sqlite> .load ./libbech32m.so
sqlite> select bech32m_encode('xch', x'f4f6ca53d56211869b1705ce29726bad7a67d30ebe002a65450b13adbb05a669');
xch17nmv5574vggcdxchqh8zjunt44ax05cwhcqz5e29pvf6mwc95e5s27yfa4
```

## References

Bech32m is specified in [BIP-350].

The actual Bech32m encoding code is taken from the [reference implementation by
Pieter Wuille][1], which is MIT-licensed.

[BIP-350]: https://github.com/bitcoin/bips/blob/master/bip-0350.mediawiki
[1]: https://github.com/sipa/bech32/tree/master/ref/c

## License

SPDX-License-Identifier: MIT

Copyright (C) 2022 xchdata.io

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
