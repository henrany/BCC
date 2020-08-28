datatype exp = iconst of int | Div of exp*exp | Mult of exp*exp | Plus of exp *exp | Minus of exp*exp;

fun eval(iconst b) = b
  | eval(Div(e1, e2)) = 
        if eval(e1) = 0 orelse eval(e2) = 0
        then 0
        else eval(e1) div eval(e2)
  |  eval(Mult(e1,e2)) = eval(e1) * eval(e2)
  |  eval(Plus(e1,e2)) = eval(e1) + eval(e2)
  |  eval(Minus(e1,e2)) = eval(e1) -  eval(e2);