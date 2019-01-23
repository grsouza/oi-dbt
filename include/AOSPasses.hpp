#ifndef AOS_PASSES
#define AOS_PASSES

#define OPT_MIN 0 
#define OPT_MAX 20 

#define _NONE 0
#define DCE 1
#define SIMPLIFYCFG 2
#define REASSOCIATE 3
#define GVN 4
#define DIE 5
#define MEM2REG 6
#define LICM 7
#define MEMCPYOPT 8
#define LOOP_UNSWITCH 9
#define INDVARS 10
#define LOOP_DELETION 11
#define LOOP_PREDICATION 12
#define LOOP_UNROLL 13
#define INSTCOMBINE 14
#define DSE 15
#define ADCE 16
#define LOOP_IDIOM 17
#define BASICAA 18
#define DOMTREE 19
#define LOOP_ROTATE 20

#endif
