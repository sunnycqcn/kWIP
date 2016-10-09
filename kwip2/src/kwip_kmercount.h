#ifndef KMERCOUNT_H_VKHVXZLK
#define KMERCOUNT_H_VKHVXZLK

#include "kwip_config.h"
#include "kwip_array.h"

#include <stdlib.h>
#include <stdint.h>
#include <sys/types.h>

#include <clogged/clogged.h>

#include "kwip_kmerhash.h"

#ifndef kc_eltype_t
    #define kc_eltype_t uint8_t
    #define H5T_KMERCOUNT H5T_NATIVE_UINT8
#endif

typedef struct {
    kc_eltype_t *cv;
    size_t cvlen;
    size_t k;
    kmer_iter_t itr;
    clg_logger_t *log;
    size_t num_kmers;
    size_t num_reads;
} kmer_count_t;

void kmer_count_init(kmer_count_t *ctx, size_t len, size_t k, uint64_t seed, bool canonicalise);

void kmer_count_set_logger(kmer_count_t *ctx, clg_logger_t *log);

kc_eltype_t kmer_count_count_h(kmer_count_t *ctx, uint64_t hash);
int kmer_count_count_s(kmer_count_t *ctx, char *seq, size_t n);

kc_eltype_t kmer_count_get_h(kmer_count_t *ctx, uint64_t hash);

int kmer_count_save(kmer_count_t *ctx, const char *filename);
int kmer_count_load(kmer_count_t *ctx, const char *filename);

int kmer_count_consume_readfile(kmer_count_t *ctx, const char *filename);
int kmer_count_consume_fd(kmer_count_t *ctx, int fd);

void kmer_count_destroy(kmer_count_t *ctx);

#endif /* end of include guard: KMERCOUNT_H_VKHVXZLK */