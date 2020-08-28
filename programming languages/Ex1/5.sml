datatype exp = iconst of int | Div of exp*exp | Mult of exp*exp | Plus of exp *exp | Minus of exp*exp;

fun eval (iconst b) n = b mod n
  | eval (Div(e1, e2)) n = if (eval e1 n) = 0 orelse (eval e2 n) = 0
        then 0
        else (eval e1 n) div (eval e2 n)
  | eval (Mult(e1, e2)) n = (eval e1 n) * (eval e2 n)
  | eval (Plus(e1, e2)) n = (eval e1 n) + (eval e2 n)
  | eval (Minus(e1, e2)) n = (eval e1 n) - (eval e2 n)