#include "mpc.h"

#include "xx_ast.h"

static char const* RULES[] = {
    "ident", /* 1 */
    "int_radix", "int_digits", "int_ty", "int", /* 4 */
    "float_digits", "float_ty", "float", /* 3 */
    "num_sign", "num", /* 2 */
    "lit", /* 1 */
    "wsp", "wsp1", /* 2 */
    "expr1", "expr2", "expr3", "expr4", "expr5", "expr6", "expr7", "expr8", "expr9", "expr10", "expr11", "expr", /* 12 */
    "stmnt_expr", "stmnt_declare", "stmnt_define", "stmnt_assign", "stmnt_return", "stmnt_block", "stmnt", /* 7 */
};

static size_t NUM_RULES = sizeof(RULES) / sizeof(char const*);

static size_t GetRuleIdx(char const* name){
    size_t i;
    for (i = 0; i < NUM_RULES; ++i) {
        if (strcmp(RULES[i], name) == 0) {
            return i;
        }
    }
    return -1; /* TODO */
}

typedef struct {
    mpc_parser_t ** rules;
} XxParser;

XxParser XxParser_New(){
    mpc_parser_t ** rules = (mpc_parser_t **) malloc(NUM_RULES * sizeof(mpc_parser_t *));
    size_t i;
    XxParser this;
    mpc_err_t * err;

    this.rules = rules;

    for (i = 0; i < NUM_RULES; ++i) {
        rules[i] = mpc_new(RULES[i]);
    }

    err = mpca_lang_contents(
        MPCA_LANG_WHITESPACE_SENSITIVE, 
        "syntax", 
        rules[0], 
        rules[1], rules[2], rules[3], rules[4],
        rules[5], rules[6], rules[7],
        rules[8], rules[9],
        rules[10],
        rules[11], rules[12],
        rules[13], rules[14], rules[15], rules[16], rules[17], rules[18], rules[19], rules[20], rules[21], rules[22], rules[23], rules[24],
        rules[25], rules[26], rules[27], rules[28], rules[29], rules[30], rules[31],
        NULL
    );

    if (err != NULL){
        mpc_err_print(err);
        mpc_err_delete(err);
    }

    return this;
}

void XxParser_Destroy(XxParser * this){
    mpc_cleanup(NUM_RULES, this->rules);
}

char const* INPUT = 
    "{ nix:nux:bux(2 + 2); }"
;

int main(){
    XxParser parser = XxParser_New();
    mpc_result_t res;
    mpc_ast_t * ast_next;
    mpc_ast_trav_t * ast_trav;

    if ((mpc_parse("input", INPUT, parser.rules[GetRuleIdx("stmnt")], &res))) {
      mpc_ast_print(res.output);
    } else {
      mpc_err_print(res.error);
      return 1;
    }

    ast_trav = mpc_ast_traverse_start(res.output, mpc_ast_trav_order_post);

    ast_next = mpc_ast_traverse_next(&ast_trav);
    while (ast_next != NULL){
        /* printf("Tag: %s; Contents: %s\n", ast_next->tag, ast_next->contents); */
        ast_next = mpc_ast_traverse_next(&ast_trav);

    }
    while ((ast_next = mpc_ast_traverse_next(&ast_trav)) != NULL) {

    }

    return 0;
}

