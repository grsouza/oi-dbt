#ifndef AOS_PASSES
#define AOS_PASSES

#define _NONE 0
#define AA_EVAL 1
#define DCE 2 
#define SIMPLIFYCFG 3 
#define REASSOCIATE 4
#define GVN 5 
#define DIE 6
#define MEM2REG 7
#define LICM 8 
#define MEMCPYOPT 9
#define LOOP_UNSWITCH 10
#define INDVARS 11
#define LOOP_DELETION 12
#define LOOP_PREDICATION 13
#define LOOP_UNROLL 14
#define INSTCOMBINE 15
#define ALWAYS_INLINE 16
#define DSE 17
#define PRUNE_EH 18
#define ADCE 19
#define LOOP_IDIOM 20
#define BASICAA 21
#define DOMTREE 22
#define LOOP_ROTATE 23
#define GLOBALOPT 24

#endif
