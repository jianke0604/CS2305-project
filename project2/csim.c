// Xiaohan Qin
// 521021910604

#include "cachelab.h"
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <string.h>

int h, v, s, E, b, S;

int hits, misses, evictions;

char t[100];

typedef struct
{
    int valid;
    int tag;
    int stamp;
} cache_line, *cache_asso, **cache;

cache cache_sim = NULL;

void printUsage()
{
    printf("Usage: ./csim [-hv] -s <num> -E <num> -b <num> -t <file>\n");
    printf("Options:\n");
    printf("  -h         Print this help message.\n");
    printf("  -v         Optional verbose flag.\n");
    printf("  -s <num>   Number of set index bits.\n");
    printf("  -E <num>   Number of lines per set.\n");
    printf("  -b <num>   Number of block offset bits.\n");
    printf("  -t <file>  Trace file.\n");
    printf("\n");
    printf("Examples:\n");
    printf("  linux>  ./csim -s 4 -E 1 -b 4 -t traces/yi.trace\n");
    printf("  linux>  ./csim -v -s 8 -E 2 -b 4 -t traces/yi.trace\n");
}

void init_cache()
{
    cache_sim = (cache)malloc(sizeof(cache_asso) * S);
    for (int i = 0; i < S; i++)
    {
        cache_sim[i] = (cache_asso)malloc(sizeof(cache_line) * E);
        for (int j = 0; j < E; j++)
        {
            cache_sim[i][j].valid = 0;
            cache_sim[i][j].tag = -1;
            cache_sim[i][j].stamp = -1;
        }
    }
}

void update(unsigned int address)
{
    int setindex_add = (address >> b) & ((1 << s) - 1);
	int tag_add = address >> (b + s);
	
	int max_stamp = -1;
	int max_stamp_index = -1;

	for(int i = 0; i < E; ++i) 
	{
		if(cache_sim[setindex_add][i].tag == tag_add && cache_sim[setindex_add][i].valid == 1)
		{
			cache_sim[setindex_add][i].stamp = 0;
			++hits;
			return ;
		}
	}
	
	for(int i = 0; i < E; ++i) 
	{
		if(cache_sim[setindex_add][i].valid == 0)
		{
			cache_sim[setindex_add][i].valid = 1;
			cache_sim[setindex_add][i].tag = tag_add;
			cache_sim[setindex_add][i].stamp = 0;
			++misses;
			return ;
		}
	}
	++evictions;
	++misses;
	
	for(int i = 0; i < E; ++i)
	{
		if(cache_sim[setindex_add][i].stamp > max_stamp)
		{
			max_stamp = cache_sim[setindex_add][i].stamp;
			max_stamp_index = i;
		}
	}
	cache_sim[setindex_add][max_stamp_index].tag = tag_add;
	cache_sim[setindex_add][max_stamp_index].stamp = 0;
	return ;
}

void update_stamp()
{
	for(int i = 0; i < S; ++i)
		for(int j = 0; j < E; ++j)
			if(cache_sim[i][j].valid == 1)
				++cache_sim[i][j].stamp;
}

void parse_trace()
{
	FILE* fp = fopen(t, "r"); 
	if(fp == NULL)
	{
		printf("open error");
		exit(-1);
	}
	
	char operation;      
	unsigned int address;   
	int size;              
	while(fscanf(fp, " %c %xu,%d\n", &operation, &address, &size) > 0)
	{
		
		switch(operation)
		{
			case 'L':
				update(address);
				break;
			case 'M':
				update(address);  
			case 'S':
				update(address);
		}
		update_stamp();	
	}
	
	fclose(fp);
	for(int i = 0; i < S; ++i)
		free(cache_sim[i]);
	free(cache_sim);            
	
}


int main(int argc, char *argv[])
{
    h = 0;
    v = 0;
    hits = misses = evictions = 0;
    int opt; 
    while((opt = getopt(argc, argv, "hvs:E:b:t:")) != -1)
    {
        switch(opt)
        {
            case 'h':
                h = 1;
                printUsage();
                break;
            case 'v':
                v = 1;
                printUsage();
                break;
            case 's':
                s = atoi(optarg);
                break;
            case 'E':
                E = atoi(optarg);
                break;
            case 'b':
                b = atoi(optarg);
                break;
            case 't':
                strcpy(t, optarg);
                break;
            default:
                printUsage();
                break;
        }
    }

    if (s <= 0 || E <= 0 || b <= 0 || t == NULL)
    {
        printf("Missing required command line argument\n");
        return -1;
    }

    S = 1 << s;
    FILE *fp = fopen(t, "r");
    if (fp == NULL)
    {
        printf("File not found\n");
        return -1;
    }

    init_cache();
    printf("s: %d, E: %d, b: %d, t: %s\n", s, E, b, t);
    parse_trace();
    printSummary(hits, misses, evictions);
    return 0;
}