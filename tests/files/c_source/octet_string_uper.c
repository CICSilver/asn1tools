/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2018-2019 Erik Moqvist
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy,
 * modify, merge, publish, distribute, sublicense, and/or sell copies
 * of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/**
 * This file was generated by asn1tools version 0.145.2 Thu Jan 24 07:11:56 2019.
 */

#include <string.h>

#include "octet_string_uper.h"

struct encoder_t {
    uint8_t *buf_p;
    ssize_t size;
    ssize_t pos;
};

struct decoder_t {
    const uint8_t *buf_p;
    ssize_t size;
    ssize_t pos;
};

static void encoder_init(struct encoder_t *self_p,
                         uint8_t *buf_p,
                         size_t size)
{
    self_p->buf_p = buf_p;
    self_p->size = (8 * (ssize_t)size);
    self_p->pos = 0;
}

static ssize_t encoder_get_result(struct encoder_t *self_p)
{
    if (self_p->size >= 0) {
        return ((self_p->pos + 7) / 8);
    } else {
        return (self_p->pos);
    }
}

static void encoder_abort(struct encoder_t *self_p,
                          ssize_t error)
{
    if (self_p->size >= 0) {
        self_p->size = -error;
        self_p->pos = -error;
    }
}

static ssize_t encoder_alloc(struct encoder_t *self_p,
                             size_t size)
{
    ssize_t pos;

    if (self_p->pos + (ssize_t)size <= self_p->size) {
        pos = self_p->pos;
        self_p->pos += (ssize_t)size;
    } else {
        pos = -ENOMEM;
        encoder_abort(self_p, ENOMEM);
    }

    return (pos);
}

static void encoder_append_bytes(struct encoder_t *self_p,
                                 const uint8_t *buf_p,
                                 size_t size)
{
    size_t i;
    ssize_t pos;
    size_t byte_pos;
    size_t pos_in_byte;

    pos = encoder_alloc(self_p, 8 * size);

    if (pos < 0) {
        return;
    }

    byte_pos = ((size_t)pos / 8);
    pos_in_byte = ((size_t)pos % 8);

    if (pos_in_byte == 0) {
        memcpy(&self_p->buf_p[byte_pos], buf_p, size);
    } else {
        for (i = 0; i < size; i++) {
            self_p->buf_p[byte_pos + i] |= (buf_p[i] >> pos_in_byte);
            self_p->buf_p[byte_pos + i + 1] = (buf_p[i] << (8 - pos_in_byte));
        }
    }
}

static void decoder_init(struct decoder_t *self_p,
                         const uint8_t *buf_p,
                         size_t size)
{
    self_p->buf_p = buf_p;
    self_p->size = (8 * (ssize_t)size);
    self_p->pos = 0;
}

static ssize_t decoder_get_result(struct decoder_t *self_p)
{
    if (self_p->size >= 0) {
        return ((self_p->pos + 7) / 8);
    } else {
        return (self_p->pos);
    }
}

static void decoder_abort(struct decoder_t *self_p,
                          ssize_t error)
{
    if (self_p->size >= 0) {
        self_p->size = -error;
        self_p->pos = -error;
    }
}

static ssize_t decoder_free(struct decoder_t *self_p,
                            size_t size)
{
    ssize_t pos;

    if (self_p->pos + (ssize_t)size <= self_p->size) {
        pos = self_p->pos;
        self_p->pos += (ssize_t)size;
    } else {
        pos = -EOUTOFDATA;
        decoder_abort(self_p, EOUTOFDATA);
    }

    return (pos);
}

static void decoder_read_bytes(struct decoder_t *self_p,
                               uint8_t *buf_p,
                               size_t size)
{
    size_t i;
    ssize_t pos;
    size_t byte_pos;
    size_t pos_in_byte;

    pos = decoder_free(self_p, 8 * size);

    if (pos < 0) {
        return;
    }

    byte_pos = ((size_t)pos / 8);
    pos_in_byte = ((size_t)pos % 8);

    if (pos_in_byte == 0) {
        memcpy(buf_p, &self_p->buf_p[byte_pos], size);
    } else {
        for (i = 0; i < size; i++) {
            buf_p[i] = (self_p->buf_p[byte_pos + i] << pos_in_byte);
            buf_p[i] |= (self_p->buf_p[byte_pos + i + 1] >> (8 - pos_in_byte));
        }
    }
}

static void octet_string_uper_octet_string_a_encode_inner(
    struct encoder_t *encoder_p,
    const struct octet_string_uper_octet_string_a_t *src_p)
{
    encoder_append_bytes(encoder_p,
                         &src_p->buf[0],
                         3);
}

static void octet_string_uper_octet_string_a_decode_inner(
    struct decoder_t *decoder_p,
    struct octet_string_uper_octet_string_a_t *dst_p)
{
    decoder_read_bytes(decoder_p,
                       &dst_p->buf[0],
                       3);
}

ssize_t octet_string_uper_octet_string_a_encode(
    uint8_t *dst_p,
    size_t size,
    const struct octet_string_uper_octet_string_a_t *src_p)
{
    struct encoder_t encoder;

    encoder_init(&encoder, dst_p, size);
    octet_string_uper_octet_string_a_encode_inner(&encoder, src_p);

    return (encoder_get_result(&encoder));
}

ssize_t octet_string_uper_octet_string_a_decode(
    struct octet_string_uper_octet_string_a_t *dst_p,
    const uint8_t *src_p,
    size_t size)
{
    struct decoder_t decoder;

    decoder_init(&decoder, src_p, size);
    octet_string_uper_octet_string_a_decode_inner(&decoder, dst_p);

    return (decoder_get_result(&decoder));
}
