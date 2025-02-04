////////////////////////////////////////////////////////////////////////////////
// Main File:        csim.c
// This File:        csim.c
// Other Files:      None
// Semester:         CS 354 Spring 2023
// Instructor:       Debra Deppeler
//
// Author:           Tom Tan
// Email:            ztan64@wisc.edu
// CS Login:         ttan
// GG#:              8
//                   (See https://canvas.wisc.edu/groups for your GG number)
//
/////////////////////////// OTHER SOURCES OF HELP //////////////////////////////
//                   Fully acknowledge and credit all sources of help,
//                   including family, friencs, classmates, tutors,
//                   Peer Mentors, TAs, and Instructor.
//
// Persons:          None
//
// Online sources:   None
//
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
//
// Copyright 2013,2019-2020
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission for Spring 2023
//
////////////////////////////////////////////////////////////////////////////////

/*
 * csim.c:
 * A cache simulator that can replay traces (from Valgrind) and output
 * statistics for the number of hits, misses, and evictions.
 * The replacement policy is LRU.
 *
 * Implementation and assumptions:
 *  1. Each load/store can cause at most one cache miss plus a possible eviction.
 *  2. Instruction loads (I) are ignored.
 *  3. Data modify (M) is treated as a load followed by a store to the same
 *  address. Hence, an M operation can result in two cache hits, or a miss and a
 *  hit plus a possible eviction.
 */

#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>

/******************************************************************************/
/* DO NOT MODIFY THESE VARIABLES **********************************************/

// Globals set by command line args.
int b = 0; // number of block (b) bits
int s = 0; // number of set (s) bits
int E = 0; // number of lines per set

// Globals derived from command line args.
int B; // block size in bytes: B = 2^b
int S; // number of sets: S = 2^s

// Global counters to track cache statistics in access_data().
int hit_cnt = 0;
int miss_cnt = 0;
int evict_cnt = 0;

// Global to control trace output
int verbosity = 0; // print trace if set
/******************************************************************************/

// Type mem_addr_t: Use when dealing with addresses or address masks.
typedef unsigned long long int mem_addr_t;

// Type cache_line_t: Use when dealing with cache lines.
// TODO - COMPLETE THIS TYPE
typedef struct cache_line
{
    char valid;
    mem_addr_t tag;
    // Add a data member as needed by your implementation for LRU tracking.
    int lru; // using counter method, 0 means most recently used, larger number means less recently used
} cache_line_t;

// Type cache_set_t: Use when dealing with cache sets
// Note: Each set is a pointer to a heap array of one or more cache lines.
typedef cache_line_t *cache_set_t;

// Type cache_t: Use when dealing with the cache.
// Note: A cache is a pointer to a heap array of one or more sets.
typedef cache_set_t *cache_t;

// Create the cache we're simulating.
// Note: A cache is a pointer to a heap array of one or more cache sets.
cache_t cache;

/* TODO - COMPLETE THIS FUNCTION
 * init_cache:
 * Allocates the data structure for a cache with S sets and E lines per set.
 * Initializes all valid bits and tags with 0s.
 */
void init_cache()
{
    // calculate B and S
    B = pow(2, b);
    S = pow(2, s);

    // allocate S sets for cache, each set is a pointer to a cache_line_t
    cache = (cache_set_t *)malloc(S * sizeof(cache_set_t));
    // check if memory allocation failed
    if (cache == NULL)
    {
        exit(1);
    }

    // allocate memory for the cache lines in each set
    for (int set = 0; set < S; set++)
    {
        cache[set] = (cache_line_t *)malloc(E * sizeof(cache_line_t));
        // check if memory allocation failed
        if (cache[set] == NULL)
        {
            exit(1);
        }

        // initialize valid bits and tags
        for (int line = 0; line < E; line++)
        {
            cache[set][line].valid = 0;
            cache[set][line].tag = 0;
            cache[set][line].lru = 0;
        }
    }
}

/* TODO - COMPLETE THIS FUNCTION
 * free_cache:
 * Frees all heap allocated memory used by the cache.
 */
void free_cache()
{
    // free memory for each line and each set
    for (int set = 0; set < S; set++)
    {
        // free memory for each line
        free(cache[set]);
        // set pointer to NULL
        cache[set] = NULL;
    }
    // free memory for the cache
    free(cache);
    // set cache pointer to NULL
    cache = NULL;
}

/* TODO - COMPLETE THIS FUNCTION
 * access_data:
 * Simulates data access at given "addr" memory address in the cache.
 *
 * If already in cache, increment hit_cnt
 * If not in cache, cache it (set tag), increment miss_cnt
 * If a line is evicted, increment evict_cnt
 */
void access_data(mem_addr_t addr)
{
    // extract set index and tag from addr
    // for t bit, simply shift the address to the right by (s + b) bits
    mem_addr_t tag = addr >> (s + b);
    // for s bit, shift the address to the right by b bits, and then mask it with (S - 1) due to the fact that S = 2^s is "1" plus s number of 0 in binary, e.g. S = 8 = 2^3 = 1000, minus this binary by 1, we get 0111, and that can be used as a mask to get the last s bits, so we can use (S - 1) to get the last s bits
    mem_addr_t set = (addr >> b) & (S - 1);

    // check if the line is already in the cache
    for (int line = 0; line < E; line++)
    {
        // if the line match the tag, and is valid, we have a hit
        if (cache[set][line].tag == tag && cache[set][line].valid == 1)
        {
            // increment hit count
            hit_cnt++;
            // update lru to 0 (most recently used)
            cache[set][line].lru = 0;
            // increment all other VALID lines'lru in the set
            for (int other_line = 0; other_line < E; other_line++)
            {
                if (other_line != line && cache[set][other_line].valid == 1)
                {
                    cache[set][other_line].lru++;
                }
            }
            // exit the function
            return;
        }
    }

    // Now are are guaranteed that we have a miss, try loop through all lines in the set, find a not valid line (free line), cache the line
    for (int line = 0; line < E; line++)
    {
        // if the line is not valid
        if (cache[set][line].valid == 0)
        {
            // increment miss count
            miss_cnt++;
            // set the line to valid
            cache[set][line].valid = 1;
            // set the tag to match the tag in the address
            cache[set][line].tag = tag;
            // update lru to 0 (most recently used)
            cache[set][line].lru = 0;
            // increment all other VALID lines'lru in the set
            for (int other_line = 0; other_line < E; other_line++)
            {
                if (other_line != line && cache[set][other_line].valid == 1)
                {
                    cache[set][other_line].lru++;
                }
            }
            // exit the function
            return;
        }
    }

    // If there are no free line in the set, evict the least recently used line
    // first, increment miss count and evict count
    miss_cnt++;
    evict_cnt++;
    // loop through all lines in the set, find the line with the highest lru (least recently used)
    int max_lru = 0;
    int max_lru_line = 0;
    for (int line = 0; line < E; line++)
    {
        if (cache[set][line].lru > max_lru)
        {
            max_lru = cache[set][line].lru;
            max_lru_line = line;
        }
    }

    // evict the line with the highest lru by setting its tag to the input tag and  lru to 0 (most recently used).
    cache[set][max_lru_line].tag = tag;
    cache[set][max_lru_line].lru = 0;
    // increment all other VALID lines'lru in the set
    for (int other_line = 0; other_line < E; other_line++)
    {
        if (other_line != max_lru_line && cache[set][other_line].valid == 1)
        {
            cache[set][other_line].lru++;
        }
    }
}

/* TODO - FILL IN THE MISSING CODE
 * replay_trace:
 * Replays the given trace file against the cache.
 *
 * Reads the input trace file line by line.
 * Extracts the type of each memory access : L/S/M
 * TRANSLATE each "L" as a load i.e. 1 memory access
 * TRANSLATE each "S" as a store i.e. 1 memory access
 * TRANSLATE each "M" as a load followed by a store i.e. 2 memory accesses
 */
void replay_trace(char *trace_fn)
{
    char buf[1000];
    mem_addr_t addr = 0;
    unsigned int len = 0;
    FILE *trace_fp = fopen(trace_fn, "r");

    if (!trace_fp)
    {
        fprintf(stderr, "%s: %s\n", trace_fn, strerror(errno));
        exit(1);
    }

    while (fgets(buf, 1000, trace_fp) != NULL)
    {
        if (buf[1] == 'S' || buf[1] == 'L' || buf[1] == 'M')
        {
            sscanf(buf + 3, "%llx,%u", &addr, &len);

            if (verbosity)
                printf("%c %llx,%u ", buf[1], addr, len);

            // TODO - MISSING CODE
            // GIVEN: 1. addr has the address to be accessed
            //        2. buf[1] has type of acccess(S/L/M)
            // call access_data function here depending on type of access
            // if the access is a load or store, call access_data once
            if (buf[1] == 'S' || buf[1] == 'L')
            {
                access_data(addr);
            }
            // if the access is a modify, call access_data twice
            else if (buf[1] == 'M')
            {
                access_data(addr);
                access_data(addr);
            }

            if (verbosity)
                printf("\n");
        }
    }

    fclose(trace_fp);
}

/*
 * print_usage:
 * Print information on how to use csim to standard output.
 */
void print_usage(char *argv[])
{
    printf("Usage: %s [-hv] -s <num> -E <num> -b <num> -t <file>\n", argv[0]);
    printf("Options:\n");
    printf("  -h         Print this help message.\n");
    printf("  -v         Optional verbose flag.\n");
    printf("  -s <num>   Number of s bits for set index.\n");
    printf("  -E <num>   Number of lines per set.\n");
    printf("  -b <num>   Number of b bits for block offsets.\n");
    printf("  -t <file>  Trace file.\n");
    printf("\nExamples:\n");
    printf("  linux>  %s -s 4 -E 1 -b 4 -t traces/yi.trace\n", argv[0]);
    printf("  linux>  %s -v -s 8 -E 2 -b 4 -t traces/yi.trace\n", argv[0]);
    exit(0);
}

/*
 * print_summary:
 * Prints a summary of the cache simulation statistics to a file.
 */
void print_summary(int hits, int misses, int evictions)
{
    printf("hits:%d misses:%d evictions:%d\n", hits, misses, evictions);
    FILE *output_fp = fopen(".csim_results", "w");
    assert(output_fp);
    fprintf(output_fp, "%d %d %d\n", hits, misses, evictions);
    fclose(output_fp);
}

/*
 * main:
 * Main parses command line args, makes the cache, replays the memory accesses
 * free the cache and print the summary statistics.
 */
int main(int argc, char *argv[])
{
    char *trace_file = NULL;
    char c;

    // Parse the command line arguments: -h, -v, -s, -E, -b, -t
    while ((c = getopt(argc, argv, "s:E:b:t:vh")) != -1)
    {
        switch (c)
        {
        case 'b':
            b = atoi(optarg);
            break;
        case 'E':
            E = atoi(optarg);
            break;
        case 'h':
            print_usage(argv);
            exit(0);
        case 's':
            s = atoi(optarg);
            break;
        case 't':
            trace_file = optarg;
            break;
        case 'v':
            verbosity = 1;
            break;
        default:
            print_usage(argv);
            exit(1);
        }
    }

    // Make sure that all required command line args were specified.
    if (s == 0 || E == 0 || b == 0 || trace_file == NULL)
    {
        printf("%s: Missing required command line argument\n", argv[0]);
        print_usage(argv);
        exit(1);
    }

    // Initialize cache.
    init_cache();

    // Replay the memory access trace.
    replay_trace(trace_file);

    // Free memory allocated for cache.
    free_cache();

    // Print the statistics to a file.
    // DO NOT REMOVE: This function must be called for test_csim to work.
    print_summary(hit_cnt, miss_cnt, evict_cnt);
    return 0;
}

// Spring 202301
