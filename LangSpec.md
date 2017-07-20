# Syntax


## Identifier

```
ident : /[a-zA-Z_][a-zA-Z0-9_]+/;
```

Atomic, must not start with a number.

Examples:

```
FOOBAR FooBar foo_bar f00_b4r _foo_bar
```

## Integer

```
int_radix : ("0x" | "0o" | "0b")?;
int_digits : /[a-fA-F0-9_]+/;
int_ty : ("i8" | "i16" | "i32" | "i64" | "u8" | "u16" | "u32" | "u64")?;
int: <int_radix> <int_digits> <int_ty>;
```

Integers may start with a radix, which specifies what base your digits may be in.
This is followed by one or more digits or underscore.
Followed by an optional data-type suffix, which specifies what data-type this
integer is supposed to be.

Examples:

```
0 123 1_000_000 123i32 0xFFAA 0o0808 0b0011_000 0xFFu8 0b0u64
```


## Literals

* Identifier
* Integer
* Float
* `true`
* `false`
* `void`

## Expressions

An expression... a tree, with operators as nodes and literals as leafs.

```
a - 10 + b
```

In tree form:

```
     +
    / \
   -   b
  / \
 a   10
```

For how this tree is build, see Operator Precedence.

### Unary Operators

| Name | Syntax | Description
|--|--|--
| Identity | `(x)` | Returns an expression. Useful for working around operator precedence.
| Address | `&x` | Takes the address of a location. 
| Indirect | `*x` | Dereferences an address (TODO?).
| Neg | `-x` | Negates an arithmetic expression.
| Not | `!x` | Negates an logical expression.

### Binary Operators

| Name | Syntax | Description
|--|--|--
| NsAccess | `x:y` | Accesses `y` in namespace `x`... If `x` is a record instance, desugars to `(|...| X:y(x, ...))`... TODO
| RecAccess | `x.y` | Accesses `x` in record `x`... TODO
| Mul | `x * y` | Multiples `x` with `y`.
| Div | `x / y` | Divides `x` by `y`.
| Rem | `x % y` | TODO
| Add | `x + y` | Adds `y` to `x`.
| Sub | `x - y`| Substracts `y` from `x`.
| LShr | `x << y`| Bitwise leftward shift. TODO
| RShr | `x >> y` | Bitwise rightward shift. TODO
| BitAnd | `x & y` |
| BitOr | `x \| y` |
| Eq | `x == y` |
| Ne | `x != y` |
| Le | `x <= y` |
| Ge | `x >= y` |
| Lt | `x < y` |
| Gt | `x > y` |
| And | `x && y` |
| Or | `x \|\| y` |

### Variadic Operators

| Name | Syntax
|--|--
| Subscript | `x[y, z]`
| Call | `x(y, z)`

### Operator Precedence

| Precedence | Unary| Binary| Variadic
|--|--|--|--
| 1 | Identity | |
| 2 | | NsAccess | Subscript
| 3 | | RecAccess |
| 4 | | | Call
| 5 | Address, Indirect, Neg, Not | |
| 6 | | Mul, Div, Rem |
| 7 | | Add, Sub |
| 8 | | LShr, RShr |
| 9 | | BitAnd, BitOr, BitXor |
| 10 | | Eq, Ne, Le, Ge, Lt, Gt |
| 11 | | And, Or |
