datatype bexp = cons of bool | Or of bexp*bexp | And of bexp*bexp; 

datatype exp = iconst of int | Div of exp*exp | Mult of exp*exp | Plus of exp *exp | Minus of exp*exp | Var of string | ite of bexp * exp*exp;


val state = [("a", iconst 10),("b",iconst 20),("c",iconst 30),("d",iconst 40),("e",iconst 50), ("f",iconst 60),("g",iconst 70),("h",iconst 80),("i",iconst 90),("j", iconst 100)];

fun lookup [] id = raise Match
  | lookup ((k:string, v)::t) id = if k = id then v else lookup t id;

fun eval1(cons b) = b
  | eval1(Or(e1,e2)) = eval1(e1) orelse eval1(e2)
  | eval1(And(e1,e2)) = eval1(e1) andalso eval1(e2);

fun eval (iconst b) _ = b
  | eval (Var x) state = eval (lookup state x) state
  | eval (Div(e1, e2)) state = (eval e1 state) div (eval e2 state)
  | eval (Mult(e1, e2)) state = (eval e1 state) * (eval e2 state)
  | eval (Plus(e1, e2)) state = (eval e1 state) + (eval e2 state)
  | eval (Minus(e1, e2)) state = (eval e1 state) - (eval e2 state)
  | eval (ite(c, t, e)) state = if (eval1 c) then (eval t state) else (eval e state);