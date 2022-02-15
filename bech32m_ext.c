/* SPDX-License-Identifier: MIT
 *
 * Copyright (c) 2022 xchdata.io
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include <sqlite3ext.h>
SQLITE_EXTENSION_INIT1

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

extern int bech32_encode(
  char *output,
  const char *hrp,
  const uint8_t *data,
  size_t data_len
);

extern int convert_bits(
  uint8_t* out,
  size_t* outlen,
  int outbits,
  const uint8_t* in,
  size_t inlen,
  int inbits,
  int pad
);

static void bech32m_encode_fn(
  sqlite3_context *ctx,
  int argc,
  sqlite3_value **argv
) {
  int ok;
  assert(argc == 2);

  const char *hrp = sqlite3_value_text(argv[0]);

  const char *input = sqlite3_value_blob(argv[1]);
  size_t input_len = sqlite3_value_bytes(argv[1]);

  uint8_t data[64];
  size_t data_len = 0;
  ok = convert_bits(data, &data_len, 5, input, input_len, 8, 1);
  assert(ok);  // convert_bits with padding cannot fail.

  char output[92];
  ok = bech32_encode(output, hrp, data, data_len);
  if (!ok) {
    sqlite3_result_error(ctx, "bech32 encoding failed. Invalid char in prefix? Too long?", -1);
    return;
  }

  sqlite3_result_text(ctx, output, -1, SQLITE_TRANSIENT);
}

#ifdef _WIN32
__declspec(dllexport)
#endif
int sqlite3_bechm_init(
  sqlite3 *db,
  char **pzErrMsg,
  const sqlite3_api_routines *pApi
) {
  int rc = SQLITE_OK;
  SQLITE_EXTENSION_INIT2(pApi);
  rc = sqlite3_create_function(
      db, "bech32m_encode", 2,
      SQLITE_UTF8|SQLITE_INNOCUOUS|SQLITE_DETERMINISTIC,
      NULL, bech32m_encode_fn, NULL, NULL
  );
  return rc;
}
