#include<stdio.h>
#include<stdint.h>
#include<stdlib.h>

typedef enum tokenTypeE { NUM, OP, PARAN, FLOAT } tokenType;
typedef struct tokenS {
    tokenType type;
    void *data;
    uint8_t len;
    struct tokenS *prev;
    struct tokenS *next;
} token;

void calc( char *str );
token *parse( char *str );
token *token__new( token *prev, tokenType type );
void token__dumpChain( token *head );

int main( int argc, char *argv[] ) {
    calc( "2+4-(1.4-3)" ); // should be 7.6
}

void calc( char *str ) {
    token *head = parse( str );
    token__dumpChain( head );
}

token *parse( char *str ) {
    token *prev = NULL;
    token *tok = NULL;
    token *head = NULL;
    uint8_t done = 0;
    char *pos = str;
    uint8_t depth = 0;
    while( !done ) {
        char let = *pos;
        switch( let ) {
            case '(':
                depth++;
            case ')':
                tok = token__new( tok, PARAN );
                tok->data = ( void * ) pos;
                tok->len = depth;
                if( let == ')' ) depth--;
                break;
            case 0x00:
                done = 1;
                break;
            case '*':
            case '/':
            case '+':
            case '-':
                tok = token__new( tok, OP );
                tok->data = pos;
                break;
            case '.':
                if( tok && tok->type == NUM ) {
                    tok->type = FLOAT;
                    tok->len++;
                }
                break;
            default:
                if( let >= '0' && let <= '9' ) {
                    if( tok && tok->type == NUM ) {
                        tok->len++;
                    }
                    else if( tok && tok->type == FLOAT ) {
                        tok->len++;
                    }
                    else {
                        tok = token__new( tok, NUM );
                        tok->data = ( void * ) pos;
                        tok->len = 1; // happens automatically due to calloc
                    }
                }
                break; // doesn't actually accomplish anything
        }
        if( !head ) head = tok;
        pos++;
    }
    return head;
}

void token__dump( token *node ) {
    tokenType type = node->type;
    switch( type ) {
        case PARAN:
            printf( "PARAN: %c, depth=%i\n", ( (char *) node->data )[0], node->len );
            break;
        case OP:
            printf( "OP: %c\n", ( (char *) node->data  )[0] );
            break;
        case NUM:
            printf( "NUM: %.*s\n", node->len, ( char * ) node->data );
            break;
        case FLOAT:
            printf( "FLOAT: %.*s\n", node->len, ( char * ) node->data );
            break;
        default:
            printf( "UNKNOWN NODE: type=%i\n", node->type );
            break;
    }
}

void token__dumpChain( token *head ) {
    if( !head ) {
        printf( "EMPTY CHAIN\n" );
        return;
    }
    token *cur = head;
    while( cur ) {
        token__dump( cur );
        cur = cur->next;
    }
}

token *token__new( token *cur, tokenType type ) {
    token *tok = ( token * ) calloc( sizeof( token ), 1 );
    if( cur ) {
        cur->next = tok;
        tok->prev = cur;
    }
    tok->type = type;
    return tok;
}