#ifndef SYMTABLE
#define SYMTABLE
#define NHASH 9997

/* struct of symbol table */
typedef struct symbol {
	char * name;
	struct ref * reflist;
}symbol;

/* struct of contents of symbol table */
typedef struct ref {
	struct ref * next;
	char * filename;
	int flags;
	int lineno;
}ref;

/* Function to lookup a string in table symbol */
symbol * lookup(char *);

/* Function to add new ref in a symbol table */
void addref(int, char *, char *, int);

static unsigned symhash(char * sym);

static int symcompare(const void * xa, const void * xb);

void printrefs();

#endif