#pragma once

#include <stdint.h>

#define BLAKE3_KEY_LEN 32
#define BLAKE3_OUT_LEN 32
#define BLAKE3_BLOCK_LEN 64
#define BLAKE3_CHUNK_LEN 2048
#define BLAKE3_MAX_DEPTH 53
#define BLAKE3_MAX_SIMD_DEGREE 16

typedef struct {
  uint8_t cv[32];
  uint8_t key[BLAKE3_KEY_LEN];
  uint64_t offset;
  uint16_t count;
  uint8_t buf[BLAKE3_BLOCK_LEN];
  uint8_t buf_len;
  uint8_t flags;
} blake3_chunk_state;

typedef struct {
  blake3_chunk_state chunk;
  uint8_t subtree_hashes_len;
  uint8_t subtree_hashes[BLAKE3_MAX_DEPTH * BLAKE3_OUT_LEN];
} blake3_hasher;

void blake3_hasher_init(blake3_hasher *self);
void blake3_hasher_init_keyed(blake3_hasher *self,
                              const uint8_t key[BLAKE3_KEY_LEN]);
void blake3_hasher_init_derive_key(blake3_hasher *self,
                                   const uint8_t key[BLAKE3_KEY_LEN]);
void blake3_hasher_update(blake3_hasher *self, const void *input,
                          size_t input_len);
void blake3_hasher_finalize(const blake3_hasher *self,
                            uint8_t out[BLAKE3_OUT_LEN]);