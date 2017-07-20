#ifndef _XX_AST_H
#define _XX_AST_H

#include <stdlib.h>

typedef struct XxExpr XxExpr;

/* ++++++++++++++++++++ Ident ++++++++++++++++++++ */

typedef struct {
    char * data;
    size_t len;
} XxIdent;

extern void XxIdent_Destroy(XxIdent * this);

/* ++++++++++++++++++++ Num ++++++++++++++++++++ */

/* typedef enum { */
/*     XX_I8, XX_I16, XX_I32, XX_I64, */ 
/*     XX_U8, XX_U16, XX_U32, XX_U64, */ 
/*     XX_F32, XX_F64, */
/* } XxNumType; */

typedef enum {
    XX_HEX, XX_OCT, XX_BIN, XX_DEC,
} XxNumRadix;

typedef struct {
    /* XxNumType type; */
    char const* type;
    XxNumRadix radix;
    char const* digits;
} XxNum;

/* ++++++++++++++++++++ Lit ++++++++++++++++++++ */

typedef enum {
    XX_IDENT,
    XX_NUM,
    XX_TRUE,
    XX_FALSE,
    XX_VOID,
} XxLitType;

typedef struct {
    XxLitType type;
    union {
        XxIdent ident;
        XxNum num;
    } data;
} XxLit;

/* ++++++++++++++++++++ UnaryOp ++++++++++++++++++++ */

typedef enum {
    XX_ADDRESS, XX_INDIRECT, XX_NEG, XX_NOT,
} XxUnaryOpType;

typedef struct {
    XxUnaryOpType type;
    XxExpr * arg;
} XxUnaryOp;

extern void XxUnaryOp_Destroy(XxUnaryOp * this);

/* void XxUnaryOp_Destroy(XxUnaryOp * this){ */
/*     XxExpr_Destroy(this->arg); */
/* } */

/* ++++++++++++++++++++ BinaryOp ++++++++++++++++++++ */

typedef enum {
    XX_AND, XX_OR,
    XX_EQ, XX_NE, XX_LE, XX_GE, XX_LT, XX_GT,
    XX_BITAND, XX_BITOR, XX_BITXOR,
    XX_LSHIFT, XX_RSHIFT,
    XX_ADD, XX_SUB,
    XX_MUL, XX_DIV,
    XX_NS_ACCESS, XX_REC_ACCESS,
} XxBinaryOpType;
    
typedef struct {
    XxBinaryOpType type;
    XxExpr * arg1;
    XxExpr * arg2;
} XxBinaryOp;

extern void XxBinaryOp_Destroy(XxBinaryOp * this);

/* void XxBinaryOp_Destroy(XxBinaryOp * this){ */
/*     XxExpr_Destroy(this->arg1); */
/*     XxExpr_Destroy(this->arg2); */
/* } */

/* ++++++++++++++++++++ VariadicOp ++++++++++++++++++++ */

typedef enum {
    XX_CALL,
    XX_SUBSCRIPT, 
} XxVariadicOpType;

typedef struct {
    XxVariadicOpType type;
    size_t num_args;
    XxExpr ** args;
} XxVariadicOp;

extern void XxVariadicOp_Destroy(XxVariadicOp * this);

/* void XxVariadicOp_Destroy(XxVariadicOp * this){ */
/*     size_t i; */
/*     for (i = 0; i < this->num_args; ++i) { */
/*         XxExpr_Destroy(this->args[i]); */
/*     } */
/* } */

/* ++++++++++++++++++++ Expr ++++++++++++++++++++ */

typedef enum {
    XX_LIT,
    XX_IDENTITY,
    XX_UNARY_OP,
    XX_BINARY_OP,
    XX_VARIADIC_OP,
} XxExprType;

struct XxExpr {
    XxExprType type;
    union {
        XxLit lit;
        XxExpr * expr;
        XxUnaryOp unary_op;
        XxBinaryOp binary_op;
        XxVariadicOp variadic_op;
    } data;
};

extern void XxExpr_Destroy(XxExpr * this);

/* void XxExpr_Destroy(XxExpr * this){ */
/*     switch (this->type) { */
/*         case XX_LIT: XxLit_Destroy(&this->data.lit); break; */
/*         case XX_IDENTITY: XxExpr_Destroy(this->data.expr); break; */
/*         case XX_UNARY_OP: XxUnaryOp_Destroy(&this->data.unary_op); break; */
/*         case XX_BINARY_OP: XxBinaryOp_Destroy(&this->data.binary_op); break; */
/*         case XX_VARIADIC_OP: XxVariadicOp_Destroy(&this->data.variadic_op); break; */
/*     } */
/* } */


/* typedef struct { */
/*     XxIdent idents; */
/*     XxExpr types; */
/*     XxExpr rhs; */
/* } XxStmntDeclare; */

/* typedef struct { */
/*     XxIdent idents; */
/*     XxExpr types; */
/*     XxExpr rhs; */
/* } XxStmntDefine; */

/* typedef struct { */
/*     XxExpr lhs; */
/*     XxExpr rhs; */
/* } XxStmntAssign; */

#endif /* _XX_AST_H */
