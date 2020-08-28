datatype exp = iconst of int | Div of exp*exp | Mult of exp*exp | Plus of exp *exp | Minus of exp*exp;

fun eval(iconst b) = b
  | eval(Div(e1, e2)) = 
        if eval(e1) = 0 orelse eval(e2) = 0
        then 0
        else eval(e1) div eval(e2)
  |  eval(Mult(e1,e2)) = eval(e1) * eval(e2)
  |  eval(Plus(e1,e2)) = eval(e1) + eval(e2)
  |  eval(Minus(e1,e2)) = eval(e1) -  eval(e2);
  
  val a = Minus(Plus(iconst 30, iconst 8), iconst 3);
  val b = Minus(Plus(Div(iconst 20, iconst 4), iconst 3), iconst 5);
  val c = Minus((Plus(iconst 7, iconst 3)), Div(iconst 10, iconst 2));
  val d = Plus((Mult(iconst 2, iconst 2)), Div(iconst 25,  iconst 5));
  val e = Plus(Mult(iconst 5, iconst 20),Minus(Minus(iconst 10, iconst 7),Div(iconst 21, iconst 3)));
  
  val a1 = eval a;
  val b1 = eval b;
  val c1 = eval c;
  val d1 = eval d;
  val e1 = eval e;
  