/*PL/0����ϵͳC�汾ͷ�ļ�pl0.h*/

#include <stdio.h>

typedef enum
{
	false,
	true
} bool;

#define norw 17	  /* �ؼ��ָ��� */
#define txmax 100 /* ���ֱ����� */
#define nmax 14	  /* number �����λ�� */
#define al 10	  /* ���ŵ���󳤶� */
#define amax 2047 /* ��ַ�Ͻ� */
#define levmax 3  /* ����������Ƕ���������� [0, levmax] */
#define cxmax 200 /* ��������������� */

/* ���� */
enum symbol
{
	nul,
	ident,
	number,
	plus,
	minus,
	times,
	slash,
	oddsym,
	eql,
	neq,
	lss,
	leq,
	gtr,
	geq,
	lparen,
	rparen,
	comma,
	semicolon,
	period,
	becomes,
	beginsym,
	endsym,
	ifsym,
	thensym,
	whilesym,
	writesym,
	readsym,
	dosym,
	callsym,
	constsym,
	varsym,
	procsym,
    plusbecomes,
    minusbecomes,
    selfincrease,
    selfdecrease,
    downtosym,
    forsym,
    tosym,
    returnsym,
};

#define symnum 40

/* ���ֱ��е����� */
enum object
{
	constant,
	variable,
	procedur,
};

/* ��������� */
enum fct
{
	lit,
	opr,
	lod,
	sto,
	cal,
	inte,
	jmp,
	jpc,
};

#define fctnum 8

/* ���������ṹ */
struct instruction
{
	enum fct f; /* ���������ָ�� */
	int l;		/* ���ò���������Ĳ�β� */
	int a;		/* ���� f �Ĳ�ͬ����ͬ */
};

FILE* fas; /* ������ֱ� */
FILE* fa;  /* ������������ */
FILE* fa1; /* ���Դ�ļ�������ж�Ӧ���׵�ַ */
FILE* fa2; /* ������ */

bool listswitch;  /* ��ʾ������������ */
bool tableswitch; /* ��ʾ���ֱ���� */

char ch;		 /* ��ȡ�ַ��Ļ�������getch ʹ�� */
enum symbol sym; /* ��ǰ���� */
char id[al + 1]; /* ��ǰ ident �������һ���ֽ����ڴ�� 0 */
int num;		 /* ��ǰ number */

int cc, ll; /* getch ʹ�õļ�������cc ��ʾ��ǰ�ַ� ch ��λ�� */
int cx;		/* ���������ָ�룬ȡֵ��ΧΪ [0, cxmax - 1] */

char line[81];	/* ��ȡ�л����� */
char a[al + 1]; /* ��ʱ���ţ������һ���ֽ����ڴ�� 0 */

struct instruction code[cxmax]; /* ����������������� */
char word[norw][al];			/* ������ */
enum symbol wsym[norw];			/* �����ֶ�Ӧ�ķ���ֵ */
enum symbol ssym[256];			/* ���ַ��ķ���ֵ */
char mnemonic[fctnum][5];		/* ���������ָ������ */

bool declbegsys[symnum]; /* ����������ʼ�ķ��ż��� */
bool statbegsys[symnum]; /* ������俪ʼ�ķ��ż��� */
bool facbegsys[symnum];	 /* �������ӿ�ʼ�ķ��ż���*/

/* ���ֱ�ṹ */
struct tablestruct
{
	char name[al];	  /* ���� */
	enum object kind; /* ���ͣ� const/var/array/procedure */
	int val;		  /* ��ֵ���� const ʹ�� */
	int level;		  /* �����㣬�� const ��ʹ�� */
	int adr;		  /* ��ַ���� const ��ʹ�� */
	int size;		  /* ��Ҫ������������ռ䣬�� procedure ʹ�� */
};

struct tablestruct table[txmax]; /* ���ֱ� */

FILE* fin;
FILE* fout;
char fname[al];
int err; /* ��������� */

/* �������лᷢ�� fatal error ʱ������ -1 ��֪�������ĺ����������˳����� */
#define getsymdo                        if (-1 == getsym()) return -1
#define getchdo                         if (-1 == getch()) return -1
#define testdo(a, b, c)                 if (-1 ==  test(a, b, c)) return -1
#define gendo(a, b, c)                  if (-1 == gen(a, b, c)) return -1
#define expressiondo(a, b, c)           if (-1 == expression(a, b, c)) return -1
#define factordo(a, b, c)               if (-1 == factor(a, b, c)) return -1
#define termdo(a, b, c)                 if (-1 == term(a, b, c)) return -1
#define conditiondo(a, b, c)            if (-1 == condition(a, b, c)) return -1
#define statementdo(a, b, c)            if (-1 ==  statement(a, b, c)) return -1
#define constdeclarationdo(a, b, c)     if (-1 == constdeclaration(a, b, c)) return -1
#define vardeclarationdo(a, b, c)       if (-1 ==  vardeclaration(a, b, c)) return -1

void error(int n);
int getsym();
int getch();
void init();
int gen(enum fct x, int y, int z);
int test(bool* s1, bool* s2, int n);
int inset(int e, bool* s);
int addset(bool* sr, bool* s1, bool* s2, int n);
int subset(bool* sr, bool* s1, bool* s2, int n);
int mulset(bool* sr, bool* s1, bool* s2, int n);
int block(int lev, int tx, bool* fsys);
void interpret();
int factor(bool* fsys, int* ptx, int lev);
int term(bool* fsys, int* ptx, int lev);
int condition(bool* fsys, int* ptx, int lev);
int expression(bool* fsys, int* ptx, int lev);
int statement(bool* fsys, int* ptx, int lev);
void listcode(int cx0);
int vardeclaration(int* ptx, int lev, int* pdx);
int constdeclaration(int* ptx, int lev, int* pdx);
int position(char* idt, int tx);
void enter(enum object k, int* ptx, int lev, int* pdx);
int base(int l, int* s, int b);
