#ifndef _XX_PARSER_H
#define _XX_PARSER_H

#include "xx_ast.h"

typedef struct NotcParser NotcParser;

extern XxParser XxParser_New();
extern void XxParser_Destroy(XxParser * this);

extern XxLit XxParser_ParseLit(XxParser *this, char const* input);
extern XxExpr XxParser_ParseExpr(XxParser *this, char const* input);

#endif /* _XX_PARSER_H */
